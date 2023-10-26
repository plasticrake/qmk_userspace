// Copyright 2021 Joshua T.
// Copyright 2023 D Patrick Seal (@plasticrake)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "mouse_jiggle.h"

#include QMK_KEYBOARD_H

bool is_mouse_jiggle_active = false;

enum rgb_matrix_effects saved_mode = 0;

void matrix_scan_mouse_jiggle(void) {
    if (is_mouse_jiggle_active) {
        tap_code(KC_MS_UP);
        tap_code(KC_MS_DOWN);
    }
}

bool process_record_mouse_jiggle(uint16_t keycode, const keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }

    if (is_mouse_jiggle_active) {
        // If active, quit whenever another key is pressed
        is_mouse_jiggle_active = false;
#if defined(RGB_MATRIX_ENABLE)
        rgb_matrix_mode_noeeprom(saved_mode);
#endif
        return true;
    }

    if (keycode != MS_JIGL) {
        return true;
    }

    is_mouse_jiggle_active = true;

#if defined(USER_MOUSE_JIGGLE_OUTPUT)
    SEND_STRING("Mouse jiggler enabled");
#endif
#if defined(RGB_MATRIX_ENABLE)
    saved_mode = rgb_matrix_get_mode();
    rgb_matrix_mode_noeeprom(USER_MOUSE_JIGGLE_RGB_MATRIX_MODE);
#endif

    return false;
}
