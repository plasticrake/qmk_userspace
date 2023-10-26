// Copyright 2021 Joshua T.
// Copyright 2023 D Patrick Seal (@plasticrake)
// SPDX-License-Identifier: GPL-2.0-or-later

// Before you can compile with this feature, you'll need to manually
// create a file in this directory called "secret_definitions.h"
// containing the data to be added.
//
// Example implementation:
//
// #pragma once
// static const char * const secrets[] = {
//   "secret1",
//   "secret2",
//   "secret3",
//   "secret4",
//   "secret5"
// };

#include "secrets.h"

#include QMK_KEYBOARD_H

#include "plasticrake.h"
#if __has_include(USER_SECRET_DEFINITIONS_H)
#    include USER_SECRET_DEFINITIONS_H
#else
// Do not place your secrets in this file. This is just a placeholder.
static const char *const secrets[] = {"secret1", "secret2", "secret3", "secret4", "secret5"};
#endif

bool process_record_secrets(uint16_t keycode, const keyrecord_t *record) {
    switch (keycode) {
        case K_SECR1 ... K_SECR5:
            if (!record->event.pressed) {
                clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
                send_string_with_delay(secrets[keycode - K_SECR1], USER_MACRO_TIMER);
            }
            return false;
    }

    return true;
}
