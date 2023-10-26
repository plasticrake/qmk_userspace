// Copyright 2023 D Patrick Seal (@plasticrake)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "rgb_matrix_user.h"

#include "rgb_matrix.h"
#include "lib/lib8tion/lib8tion.h"

#include "plasticrake.h"

extern led_config_t g_led_config;

keypos_t led_index_key_position[RGB_MATRIX_LED_COUNT];

void init_user_rgb_matrix(void) {
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            uint8_t led_index = g_led_config.matrix_co[row][col];
            if (led_index != NO_LED) {
                led_index_key_position[led_index] = (keypos_t){.row = row, .col = col};
            }
        }
    }
}

RGB clamp_hsv_value(uint8_t hue, uint8_t sat, uint8_t val, uint8_t min_val, uint8_t max_val) {
    HSV hsv = {hue, sat, val};
    if (hsv.v > max_val) {
        hsv.v = max_val;
    } else if (hsv.v < min_val) {
        hsv.v = min_val;
    }
    return hsv_to_rgb(hsv);
}

void rgb_matrix_set_color_hsv_clamp_value(int index, uint8_t hue, uint8_t sat, uint8_t val) {
    RGB rgb = clamp_hsv_value(hue, sat, val, 0, rgb_matrix_get_val());
    rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
}

void rgb_matrix_set_color_by_keycode(uint8_t led_min, uint8_t led_max, uint8_t layer,
                                     bool (*is_keycode)(uint16_t), uint8_t red, uint8_t green,
                                     uint8_t blue) {
    for (uint8_t i = led_min; i < led_max; i++) {
        uint16_t keycode = keymap_key_to_keycode(layer, led_index_key_position[i]);
        if ((*is_keycode)(keycode)) {
            rgb_matrix_set_color(i, red, green, blue);
        }
    }
}

bool is_caps_lock_indicator(uint16_t keycode) {
    switch (keycode) {
#if defined(USER_CAPS_LOCK_INDICATOR_LIGHT_ALPHAS)
        case KC_A ... KC_Z:
#endif
        case KC_CAPS:
            return true;
        default:
            return false;
    }
}

bool is_caps_word_indicator(uint16_t keycode) {
    switch (keycode) {
#if defined(USER_CAPS_WORD_INDICATOR_LIGHT_ALPHANUMS)
        case KC_A ... KC_Z:
        case KC_1 ... KC_0:
        case KC_MINS:
        case KC_UNDS:
        case KC_DELETE:
        case KC_BACKSPACE:
#endif
#if defined(BOTH_SHIFTS_TURNS_ON_CAPS_WORD)
        case KC_LEFT_SHIFT:
        case KC_RIGHT_SHIFT:
#endif
        case KC_CAPS:
        case QK_CAPS_WORD_TOGGLE:
            return true;
        default:
            return false;
    }
}

void set_color_mapped_keys(uint8_t layer, uint8_t hue, uint8_t sat, uint8_t val, uint8_t led_min,
                           uint8_t led_max) {
    RGB rgb = clamp_hsv_value(hue, sat, val, 0, rgb_matrix_get_val());

    for (uint8_t row = 0; row < MATRIX_ROWS; ++row) {
        for (uint8_t col = 0; col < MATRIX_COLS; ++col) {
            uint8_t index = g_led_config.matrix_co[row][col];

            if (index >= led_min && index < led_max && index != NO_LED &&
                keymap_key_to_keycode(layer, (keypos_t){col, row}) > KC_TRNS) {
                rgb_matrix_set_color(index, rgb.r, rgb.g, rgb.b);
            }
        }
    }
}

__attribute__((weak)) void rgb_matrix_indicator_keymap(void) {}

void keyboard_post_init_rgb_matrix(void) {}

void matrix_scan_rgb_matrix(void) {
    rgb_matrix_indicator_keymap();
}

bool process_record_rgb_matrix(uint16_t keycode, keyrecord_t *record) {
    return true;
}

__attribute__((weak)) bool rgb_matrix_indicators_advanced_keymap(uint8_t led_min, uint8_t led_max) {
    return true;
}

void set_underglow(uint8_t led_min, uint8_t led_max, uint8_t red, uint8_t green, uint8_t blue) {
    for (uint8_t i = led_min; i < led_max; ++i) {
        if (HAS_ANY_FLAGS(g_led_config.flags[i], LED_FLAG_UNDERGLOW)) {
            rgb_matrix_set_color(i, red, green, blue);
        }
    }
}

HSV saved_hsv;

void rgb_matrix_set_color_all_advanced(uint8_t led_min, uint8_t led_max, uint8_t red, uint8_t green,
                                       uint8_t blue) {
    for (uint8_t i = led_min; i < led_max; ++i) {
        rgb_matrix_set_color(i, red, green, blue);
    }
}

void dim_default_layer(uint8_t led_min, uint8_t led_max, uint8_t scale) {
    if (rgb_matrix_get_mode() != RGB_MATRIX_SOLID_COLOR) {
        return;
    }

    HSV current_hsv = rgb_matrix_get_hsv();
    current_hsv.v   = scale8_video(current_hsv.v, scale);
    RGB rgb         = hsv_to_rgb(current_hsv);

    rgb_matrix_set_color_all_advanced(led_min, led_max, rgb.r, rgb.g, rgb.b);
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_keymap(led_min, led_max)) {
        return false;
    }

    if (is_caps_word_on()) {
        RGB rgb = clamp_hsv_value(USER_CAPS_WORD_INDICATOR_COLOR_HSV, 0, rgb_matrix_get_val());
        set_underglow(led_min, led_max, rgb.r, rgb.g, rgb.b);
        rgb_matrix_set_color_by_keycode(led_min, led_max, get_highest_layer(layer_state),
                                        &is_caps_word_indicator, rgb.r, rgb.g, rgb.b);

    } else if (host_keyboard_led_state().caps_lock) {
        RGB rgb = clamp_hsv_value(USER_CAPS_LOCK_INDICATOR_COLOR_HSV, 0, rgb_matrix_get_val());
        set_underglow(led_min, led_max, rgb.r, rgb.g, rgb.b);
        rgb_matrix_set_color_by_keycode(led_min, led_max, get_highest_layer(layer_state),
                                        &is_caps_lock_indicator, rgb.r, rgb.g, rgb.b);
    }

    uint8_t layer = get_highest_layer(layer_state);

    switch (USER_LAYER_TYPE(layer)) {
        case _BASE_TYPE:
            break;
        case _FN1_TYPE:
            dim_default_layer(led_min, led_max, 85);
            set_color_mapped_keys(layer, USER_FN1_LAYER_COLOR_HSV, led_min, led_max);
            break;
        case _FN2_TYPE:
            dim_default_layer(led_min, led_max, 85);
            set_color_mapped_keys(layer, USER_FN2_LAYER_COLOR_HSV, led_min, led_max);
            break;
        case _FN3_TYPE:
            dim_default_layer(led_min, led_max, 85);
            set_color_mapped_keys(layer, USER_FN3_LAYER_COLOR_HSV, led_min, led_max);
            break;
        default:
            break;
    }
    return false;
}

__attribute__((weak)) bool rgb_matrix_indicators_keymap(void) {
    return true;
}

bool rgb_matrix_indicators_user(void) {
    return rgb_matrix_indicators_keymap();
}
