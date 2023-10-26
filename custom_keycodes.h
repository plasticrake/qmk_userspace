// Copyright 2023 D Patrick Seal (@plasticrake)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include QMK_KEYBOARD_H

enum user_layer_types { _BASE_TYPE, _FN1_TYPE, _FN2_TYPE, _FN3_TYPE };

enum userspace_custom_keycodes {
    VRSN = SAFE_RANGE,

    // USER_MOUSE_JIGGLE_ENABLE
    MS_JIGL,

    // USER_SECRETS_ENABLE
    K_SECR1,
    K_SECR2,
    K_SECR3,
    K_SECR4,
    K_SECR5,

    NEW_SAFE_RANGE
};

// Windows 10 shortcuts: change desktop to the left/right
#define WN_DSKL SGUI(KC_LEFT)
#define WN_DSKR SGUI(KC_RGHT)

// MS Teams
#define KC_TEAMS_CAM C(S(KC_O))
#define KC_TEAMS_MUTE C(S(KC_M))
