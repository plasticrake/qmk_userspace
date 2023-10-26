// Copyright 2023 D Patrick Seal (@plasticrake)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include QMK_KEYBOARD_H
#include "version.h"

#include "custom_keycodes.h"

#if defined(CUSTOM_RGB_MATRIX)
#    include "features/rgb_matrix_user.h"
#endif

#if defined(USER_MOUSE_JIGGLE_ENABLE)
#    include "features/mouse_jiggle.h"
#endif

#if defined(USER_SECRETS_ENABLE)
#    include "features/secrets.h"
#endif
