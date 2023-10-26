// Copyright 2023 D Patrick Seal (@plasticrake)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "plasticrake.h"

__attribute__((weak)) void matrix_scan_user_keymap(void) {}

void matrix_scan_user(void) {
#if defined(USER_MOUSE_JIGGLE_ENABLE)
    matrix_scan_mouse_jiggle();
#endif
#if defined(RGB_MATRIX_ENABLE)
    matrix_scan_rgb_matrix();
#endif

    matrix_scan_user_keymap();
}
