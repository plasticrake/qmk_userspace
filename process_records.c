// Copyright 2021 Joshua T.
// Copyright 2023 D Patrick Seal (@plasticrake)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "process_records.h"

#include QMK_KEYBOARD_H

#include "plasticrake.h"

uint8_t mod_state;

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!(process_record_keymap(keycode, record) &&
#if defined(RGB_MATRIX_ENABLE)
          process_record_rgb_matrix(keycode, record) &&
#endif
#if defined(USER_MOUSE_JIGGLE_ENABLE)
          process_record_mouse_jiggle(keycode, record) &&
#endif
#if defined(USER_SECRETS_ENABLE)
          process_record_secrets(keycode, record) &&
#endif
          true)) {
        return false;
    }

    switch (keycode) {
        case VRSN: // Prints firmware version
            if (record->event.pressed) {
                send_string_with_delay_P(PSTR(QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION
                                                           ", Built on: " QMK_BUILDDATE),
                                         USER_MACRO_TIMER);
            }
            return false;
    }

    return true;
}

__attribute__((weak)) void post_process_record_keymap(uint16_t keycode, keyrecord_t *record) {}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
    post_process_record_keymap(keycode, record);
}
