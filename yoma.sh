#!/bin/bash
# Redraw the keymap image, then commit and push this repository.
# The repository lives in qmk_firmware/keyboards/bastardkb/charybdis, so no copying is needed.
set -euo pipefail
cd "$(dirname "$0")"

uv run draw_keymap.py

git add .
git diff --cached --quiet || git commit -m "Sync charybdis updates"
git push origin main
