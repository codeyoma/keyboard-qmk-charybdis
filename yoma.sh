#!/bin/bash
qmk c2json keyboards/bastardkb/charybdis/3x5/keymaps/default/keymap.c | keymap parse --layer-names Base Colemak Lower Raise Adjust Mouse Test -c 10 -q -> charybdis_keymap.yaml
keymap draw charybdis_keymap.yaml charybdis_combo.yaml > charybdis_keymap.ortho.svg 

rsync -a --delete --exclude=.git ~/projects/keyboard/bastardkb-qmk/keyboards/bastardkb/charybdis/ ~/projects/keyboard/keyboard-qmk-charybdis/
cd ~/projects/keyboard/keyboard-qmk-charybdis
git add .
git commit -m "Sync charybdis updates"
git push origin main