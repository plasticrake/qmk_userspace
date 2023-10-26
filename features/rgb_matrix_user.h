// Copyright 2023 D Patrick Seal (@plasticrake)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include QMK_KEYBOARD_H

void init_user_rgb_matrix(void);

void keyboard_post_init_rgb_matrix(void);

void matrix_scan_rgb_matrix(void);

bool process_record_rgb_matrix(uint16_t keycode, keyrecord_t *record);

bool rgb_matrix_indicators_advanced_keymap(uint8_t led_min, uint8_t led_max);

bool rgb_matrix_indicators_keymap(void);
