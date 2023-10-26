// Copyright 2021 Joshua T.
// Copyright 2023 D Patrick Seal (@plasticrake)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include QMK_KEYBOARD_H

#include "custom_keycodes.h"

void matrix_scan_mouse_jiggle(void);

bool process_record_mouse_jiggle(uint16_t keycode, const keyrecord_t *record);
