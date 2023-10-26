# Disable unused features
CONSOLE_ENABLE = no
UNICODE_ENABLE = no
SPACE_CADET_ENABLE = no

# Enable common features
VIA_ENABLE = yes
ENCODER_ENABLE = yes
ENCODER_MAP_ENABLE = yes
MOUSEKEY_ENABLE = yes
LTO_ENABLE = yes
EXTRAKEY_ENABLE = yes
TRI_LAYER_ENABLE = yes

# Userspace features
USER_MOUSE_JIGGLE_ENABLE = yes
USER_SECRETS_ENABLE = yes

SRC += plasticrake.c

# Only load these source files if the features are enabled. Keyboards can
# enable or disable these features in their own rules.mk files.

CAPS_WORD_ENABLE ?= yes

CUSTOM_RGB_MATRIX ?= yes
ifeq ($(strip $(RGB_MATRIX_ENABLE)), yes)
	ifeq ($(strip $(CUSTOM_RGB_MATRIX)), yes)
		SRC += features/rgb_matrix_user.c
		OPT_DEFS += -DCUSTOM_RGB_MATRIX
	endif
endif

USER_MOUSE_JIGGLE_RGB_MATRIX_MODE ?= RGB_MATRIX_BAND_VAL
ifeq ($(strip $(USER_MOUSE_JIGGLE_ENABLE)), yes)
	SRC += features/mouse_jiggle.c
	OPT_DEFS += -DUSER_MOUSE_JIGGLE_ENABLE
	ifeq ($(strip $(USER_MOUSE_JIGGLE_OUTPUT)), yes)
		OPT_DEFS += -DUSER_MOUSE_JIGGLE_OUTPUT
	endif

	ifdef USER_MOUSE_JIGGLE_RGB_MATRIX_MODE
		ifneq ($(strip $(USER_MOUSE_JIGGLE_RGB_MATRIX_MODE)), no)
			OPT_DEFS += -DUSER_MOUSE_JIGGLE_RGB_MATRIX_MODE=$(strip $(USER_MOUSE_JIGGLE_RGB_MATRIX_MODE))
		endif
	endif

endif

ifeq ($(strip $(USER_SECRETS_ENABLE)), yes)
	SRC += features/secrets.c
	OPT_DEFS += -DUSER_SECRETS_ENABLE
endif

ifeq ($(KEYBOARD), keychron/q1v2/ansi_encoder)
	SRC += dip_switch.c
endif

# Define these last so any other logic can set up some defines first
SRC += matrix_scan.c \
		process_records.c
