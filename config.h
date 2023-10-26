// Copyright 2023 D Patrick Seal (@plasticrake)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// clang-format off
#define USER_LAYER_TYPE(LAYER) ( \
    (layer == 0 ? (_BASE_TYPE) : \
    (layer == 1 ? (_FN1_TYPE) : \
    (layer == 2 ? (_FN2_TYPE) : \
    (layer == 3 ? (_FN3_TYPE) : \
    (_BASE_TYPE) \
    )))))
// clang-format on

#if defined(KEYBOARD_keychron_q1v2_ansi_encoder)
#    define USER_DIP_SWITCH_LAYER_COUNT 4
#    define DYNAMIC_KEYMAP_LAYER_COUNT 8

// clang-format off
#    undef USER_LAYER_TYPE
#    define USER_LAYER_TYPE(LAYER) ( \
        (layer == 0 ? (_BASE_TYPE) : \
        (layer == 1 ? (_FN1_TYPE) : \
        (layer == 2 ? (_FN2_TYPE) : \
        (layer == 3 ? (_FN3_TYPE) : \
        (layer == 4 ? (_BASE_TYPE) : \
        (layer == 5 ? (_FN1_TYPE) : \
        (layer == 6 ? (_FN2_TYPE) : \
        (layer == 7 ? (_FN3_TYPE) : \
        (_BASE_TYPE) \
        )))))))))
// clang-format on

#elif defined(KEYBOARD_gmmk_pro_rev1_ansi)

#else

#endif

// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Layer Colors                                                              ┃
// ┡━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┩
#define USER_BASE_LAYER_COLOR_HSV \
    RGB_MATRIX_DEFAULT_HUE, RGB_MATRIX_DEFAULT_SAT, RGB_MATRIX_DEFAULT_VAL
#define USER_FN1_LAYER_COLOR_HSV HUE_GREEN, RGB_MATRIX_DEFAULT_SAT, RGB_MATRIX_DEFAULT_VAL
#define USER_FN2_LAYER_COLOR_HSV HUE_BLUE, RGB_MATRIX_DEFAULT_SAT, RGB_MATRIX_DEFAULT_VAL
#define USER_FN3_LAYER_COLOR_HSV HUE_PURPLE, RGB_MATRIX_DEFAULT_SAT, RGB_MATRIX_DEFAULT_VAL
// └───────────────────────────────────────────────────────────────────────────┘
// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Caps Lock                                                                 ┃
// ┡━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┩
// Indicator Color when Caps Lock is on
#define USER_CAPS_LOCK_INDICATOR_COLOR_HSV HUE_RED, RGB_MATRIX_DEFAULT_SAT, RGB_MATRIX_DEFAULT_VAL
// Also light up alpha keys
#define USER_CAPS_LOCK_INDICATOR_LIGHT_ALPHAS
// └───────────────────────────────────────────────────────────────────────────┘
// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Caps Word                                                                 ┃
// ┡━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┩
#define USER_BOTH_SHIFTS_TURNS_ON_CAPS_WORD
// Indicator Color when Caps Word is on
#define USER_CAPS_WORD_INDICATOR_COLOR_HSV \
    HUE_ORANGE, RGB_MATRIX_DEFAULT_SAT, RGB_MATRIX_DEFAULT_VAL
// Also light up alphanumeric keys
#define USER_CAPS_WORD_INDICATOR_LIGHT_ALPHANUMS
// └───────────────────────────────────────────────────────────────────────────┘
// ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
// ┃ Secrets                                                                   ┃
// ┡━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┩
#if defined(KEYBOARD_keychron_q1v2_ansi_encoder)
#    define USER_SECRET_DEFINITIONS_H "secret_definitions_one.h"
#elif defined(KEYBOARD_gmmk_pro_rev1_ansi)
#    define USER_SECRET_DEFINITIONS_H "secret_definitions_two.h"
#else
#    define USER_SECRET_DEFINITIONS_H "secret_definitions.h"
#endif
// └───────────────────────────────────────────────────────────────────────────┘

#if defined(TAP_CODE_DELAY)
#    define USER_MACRO_TIMER MAX(TAP_CODE_DELAY, 5)
#else
#    define USER_MACRO_TIMER 5
#endif

#if defined(RGB_MATRIX_ENABLE)

#    define RGB_MATRIX_TIMEOUT 600000 // 10 minutes (10 * 60 * 1000ms)
#    define RGB_DISABLE_WHEN_USB_SUSPENDED

#    define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_COLOR
#    define RGB_MATRIX_DEFAULT_HUE HUE_PINK
#    define RGB_MATRIX_DEFAULT_SAT 255
#    define RGB_MATRIX_DEFAULT_VAL 127
#    define RGB_MATRIX_DEFAULT_SPD 127

#    define ENABLE_RGB_MATRIX_SOLID_COLOR
#    define ENABLE_RGB_MATRIX_BAND_VAL

#endif

// Disable unused RGB Matrix effects
#undef ENABLE_RGB_MATRIX_ALPHAS_MODS
#undef ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#undef ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#undef ENABLE_RGB_MATRIX_BREATHING
#undef ENABLE_RGB_MATRIX_BAND_SAT
#undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#undef ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#undef ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#undef ENABLE_RGB_MATRIX_CYCLE_ALL
#undef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#undef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#undef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#undef ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#undef ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#undef ENABLE_RGB_MATRIX_DUAL_BEACON
#undef ENABLE_RGB_MATRIX_RAINBOW_BEACON
#undef ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#undef ENABLE_RGB_MATRIX_RAINDROPS
#undef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#undef ENABLE_RGB_MATRIX_HUE_BREATHING
#undef ENABLE_RGB_MATRIX_HUE_PENDULUM
#undef ENABLE_RGB_MATRIX_HUE_WAVE
#undef ENABLE_RGB_MATRIX_PIXEL_RAIN
#undef ENABLE_RGB_MATRIX_PIXEL_FLOW
#undef ENABLE_RGB_MATRIX_PIXEL_FRACTAL

#undef RGB_MATRIX_FRAMEBUFFER_EFFECTS
// enabled only if RGB_MATRIX_FRAMEBUFFER_EFFECTS is defined
#undef ENABLE_RGB_MATRIX_TYPING_HEATMAP
#undef ENABLE_RGB_MATRIX_DIGITAL_RAIN

// enabled only of RGB_MATRIX_KEYPRESSES or RGB_MATRIX_KEYRELEASES is defined
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#undef ENABLE_RGB_MATRIX_SPLASH
#undef ENABLE_RGB_MATRIX_MULTISPLASH
#undef ENABLE_RGB_MATRIX_SOLID_SPLASH
#undef ENABLE_RGB_MATRIX_SOLID_MULTISPLASH

#define HUE_RED 0           // 0°
#define HUE_CORAL 11        // 15°
#define HUE_ORANGE 21       // 30°
#define HUE_GOLDENROD 30    // 40°
#define HUE_GOLD 36         // 45°
#define HUE_YELLOW 43       // 60°
#define HUE_CHARTREUSE 64   // 90°
#define HUE_GREEN 85        // 120°
#define HUE_SPRINGGREEN 106 // 150°
#define HUE_TURQUOISE 123   // 174°
#define HUE_TEAL 128        // 180°
#define HUE_CYAN 128        // 180°
#define HUE_AZURE 132       // 195°
#define HUE_BLUE 170        // 240°
#define HUE_PURPLE 191      // 270°
#define HUE_MAGENTA 213     // 300°
#define HUE_PINK 234        // 330°

// This was needed to be included here in order for custom keycodes to be used in the keymap JSON
// file
#ifndef __ASSEMBLER__
#    include "custom_keycodes.h"
#endif
