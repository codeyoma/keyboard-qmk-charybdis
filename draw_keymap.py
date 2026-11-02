# /// script
# requires-python = ">=3.11"
# dependencies = ["pyyaml"]
# ///
"""Draw the Charybdis 3x5 keymap with keymap-drawer, combos included.

`qmk c2json` exports the layers but not the combos, so the combos are read from
keymap.c here: each combo's keys are expanded through the keymap's own #defines and
matched to key positions on the base layer. Their legends come from keymap-drawer
itself, by parsing the combo outputs as an extra layer that is dropped afterwards.

Needs the `qmk` and `keymap` (keymap-drawer) commands. Run: uv run draw_keymap.py
"""
import json
import re
import subprocess
import tempfile
from pathlib import Path

import yaml

REPO = Path(__file__).resolve().parent  # keyboards/bastardkb/charybdis inside qmk_firmware
QMK_HOME = REPO.parents[2]
KEYMAP_C = REPO / "3x5/keymaps/default/keymap.c"
CONFIG = REPO / "keymap_drawer.config.yaml"
OUT_YAML = REPO / "charybdis_keymap.yaml"
OUT_SVG = REPO / "charybdis_keymap.ortho.svg"

LAYER_NAMES = ["Base", "Colemak", "Lower", "Raise", "Adjust", "Mouse", "Test"]  # enum order
COMBO_LAYERS = ["Base", "Colemak", "Lower"]  # combo_should_trigger() turns combos off elsewhere
LEGEND_LAYER = "_combo_legends"
ALIASES = {"KC_COMMA": "KC_COMM", "KC_ENTER": "KC_ENT", "KC_SPACE": "KC_SPC", "KC_SLASH": "KC_SLSH",
           "KC_SEMICOLON": "KC_SCLN", "KC_LEFT_SHIFT": "KC_LSFT"}


def run(cmd, cwd=None):
    return subprocess.run([str(c) for c in cmd], cwd=cwd, check=True, capture_output=True, text=True).stdout


def strip_comments(src):
    src = re.sub(r"/\*.*?\*/", "", src, flags=re.S)
    return re.sub(r"//[^\n]*", "", src)


def read_defines(src):
    """Object-like and one-argument function-like #defines."""
    objects, functions = {}, {}
    for name, param, body in re.findall(r"^[ \t]*#define[ \t]+(\w+)(?:\((\w+)\))?[ \t]+(.+?)[ \t]*$", src, re.M):
        if param:
            functions[name] = (param, body)
        else:
            objects[name] = body
    return objects, functions


def expand(text, objects, functions):
    """Expand the keymap's macros in one keycode, e.g. HP(KC_A) -> LCTL_T(KC_A)."""
    for _ in range(10):
        new = text
        for name, (param, body) in functions.items():
            new = re.sub(rf"\b{name}\(([^()]*)\)", lambda m: re.sub(rf"\b{param}\b", m.group(1), body), new)
        new = re.sub(r"\b\w+\b", lambda m: objects.get(m.group(0), m.group(0)), new)
        if new == text:
            return text.replace(" ", "")
        text = new
    raise ValueError(f"macro expansion does not settle: {text}")


def read_combos(src, base_layer):
    """(key positions, output keycode) for every combo in key_combos[]."""
    objects, functions = read_defines(src)
    arrays = {
        name: [k.strip() for k in body.split(",") if k.strip() and k.strip() != "COMBO_END"]
        for name, body in re.findall(r"const\s+uint16_t\s+PROGMEM\s+(\w+)\[\]\s*=\s*\{([^}]*)\}", src)
    }
    table = re.search(r"combo_t\s+key_combos\[\]\s*=\s*\{(.*?)\n\};", src, re.S).group(1)
    base = [k.replace(" ", "") for k in base_layer]
    combos = []
    for array, output in re.findall(r"\[\w+\]\s*=\s*COMBO\(\s*(\w+)\s*,\s*(.+?)\)\s*,?\s*$", table, re.M):
        positions = []
        for key in arrays[array]:
            keycode = expand(key, objects, functions)
            keycode = ALIASES.get(keycode, keycode)
            if keycode not in base:
                raise ValueError(f"combo {array}: {key} ({keycode}) is not on the base layer")
            positions.append(base.index(keycode))
        combos.append((positions, expand(output, objects, functions)))
    return combos


def for_drawing(key, layer_index):
    """Rewrite layer keys into forms keymap-drawer understands (numeric layers)."""
    key = re.sub(r"\bTL_LOWR\b", "MO(LAYER_LOWER)", key)  # tri-layer keys are drawn as plain layer keys
    key = re.sub(r"\bTL_UPPR\b", "MO(LAYER_RAISE)", key)
    key = re.sub(r"TG\(MO\((\w+)\)\)", r"TG(\1)", key)  # TG(ARST) expands to TG(MO(LAYER_ARST))
    return re.sub(r"\bLAYER_\w+\b", lambda m: str(layer_index[m.group(0)]), key)


def flatten(rows):
    return [key for row in rows for key in (row if isinstance(row, list) else [row])]


def placement(positions, placed):
    """Where to draw a combo so its box does not hide key legends (10 keys per row, thumbs last)."""
    rows = {p // 10 for p in positions}
    if len(rows) == 1:  # side by side: below the keys, stacked lower where boxes would overlap
        row, center = rows.pop(), sum(p % 10 for p in positions) / len(positions)
        offset = 0.0
        while any(r == row and o == offset and abs(c - center) < 0.75 for r, c, o in placed):
            offset += 0.6
        placed.append((row, center, offset))
        return {"a": "bottom", "o": offset} if offset else {"a": "bottom"}
    if min(rows) == 1:  # home row over bottom row: a flatter box, moved down off the home row mod legend
        return {"s": 0.28, "h": 20}
    return {}


def main():
    src = strip_comments(KEYMAP_C.read_text())
    enum = re.search(r"enum\s+charybdis_keymap_layers\s*\{(.*?)\}", src, re.S).group(1)
    layer_index = {name.split("=")[0].strip(): i for i, name in enumerate(n for n in enum.split(",") if n.strip())}
    if len(layer_index) != len(LAYER_NAMES):
        raise ValueError(f"keymap.c has {len(layer_index)} layers, LAYER_NAMES lists {len(LAYER_NAMES)}")

    keymap = json.loads(run(["qmk", "c2json", KEYMAP_C.relative_to(QMK_HOME)], cwd=QMK_HOME))
    combos = read_combos(src, keymap["layers"][0])

    # Parse the combo outputs as one more layer, so they get the same legends as layer keys.
    size = len(keymap["layers"][0])
    outputs = [for_drawing(output, layer_index) for _, output in combos]
    keymap["layers"] = [[for_drawing(k, layer_index) for k in layer] for layer in keymap["layers"]]
    keymap["layers"].append(outputs + ["KC_NO"] * (size - len(outputs)))
    with tempfile.NamedTemporaryFile("w", suffix=".json") as tmp:
        json.dump(keymap, tmp)
        tmp.flush()
        parsed = yaml.safe_load(run(["keymap", "-c", CONFIG, "parse", "-q", tmp.name, "-c", "10",
                                     "-l", *LAYER_NAMES, LEGEND_LAYER]))
    legends = flatten(parsed["layers"].pop(LEGEND_LAYER))
    placed = []
    parsed["combos"] = [{"p": positions, "k": legend, "l": list(COMBO_LAYERS), **placement(positions, placed)}
                        for (positions, _), legend in zip(combos, legends)]

    OUT_YAML.write_text(yaml.safe_dump(parsed, sort_keys=False, allow_unicode=True, default_flow_style=None, width=120))
    # The physical layout comes from the qmk_keyboard name in the YAML: keymap-drawer has its own
    # bastardkb/charybdis/3x5 layout with the column stagger and the angled thumb keys.
    run(["keymap", "-c", CONFIG, "draw", OUT_YAML, "-o", OUT_SVG])
    # Write non-ASCII legends (the ▽ on transparent keys) as character references: the SVG has no
    # encoding declaration, and viewers that guess Latin-1 would show them as "â–½".
    OUT_SVG.write_text(OUT_SVG.read_text(encoding="utf-8").encode("ascii", "xmlcharrefreplace").decode("ascii"))
    print(f"{len(LAYER_NAMES)} layers, {len(combos)} combos: {OUT_SVG.name}")


if __name__ == "__main__":
    main()
