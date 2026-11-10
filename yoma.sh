#!/bin/bash
# Build the firmware, redraw the keymap image, then commit and push this repository.
# The repository lives in qmk_firmware/keyboards/bastardkb/charybdis, so no copying is needed.
# The firmware is written to the qmk_firmware root as bastardkb_charybdis_3x5_default.uf2.
# A failed build stops the script before anything is committed.
set -euo pipefail
cd "$(dirname "$0")"

qmk compile -kb bastardkb/charybdis/3x5 -km default
uv run draw_keymap.py

git add .
git diff --cached --quiet || git commit -m "Sync charybdis updates"
git push origin main
