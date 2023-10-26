// Copyright 2023 D Patrick Seal (@plasticrake)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#include "plasticrake.h"

// Keychron Q1 has a dip switch that by default swaps the default layers from 0/1 and 2/3 ( 4 layers
// total ) Since we have 8 layers, we can use the dip switch to swap between the first 4 and the
// second 4 And also update the tri layer keys to match
bool dip_switch_update_user(uint8_t index, bool active) {
    if (index == 0) {
        default_layer_set(1UL << (active ? USER_DIP_SWITCH_LAYER_COUNT : 0));
        set_tri_layer_layers(1 + active * USER_DIP_SWITCH_LAYER_COUNT,
                             2 + active * USER_DIP_SWITCH_LAYER_COUNT,
                             3 + active * USER_DIP_SWITCH_LAYER_COUNT);
        return false;
    }
    return true;
}
