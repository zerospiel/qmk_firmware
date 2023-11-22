SRC += flow.c

EXTRAKEY_ENABLE 		= yes
MOUSEKEY_ENABLE 		= yes
COMBO_ENABLE			= yes
LTO_ENABLE				= yes
TAP_DANCE_ENABLE 		= no
SWAP_HANDS_ENABLE 		= no
AUDIO_ENABLE 			= no
AUTO_SHIFT_ENABLE 		= no
BACKLIGHT_ENABLE 		= no
PHYSICAL_LEDS_ENABLE 	= no
ALT_LAYOUTS_ENABLE 		= no
STENO_ENABLE			= no
BACKLIGHT_ENABLE 	 	= no
PHYSICAL_LEDS_ENABLE 	= no
CAPS_WORD_ENABLE        = no

DEBOUNCE_TYPE 			= sym_defer_g

#Debug options
VERBOSE                	= no
DEBUG_MATRIX_SCAN_RATE 	= no
DEBUG_MATRIX           	= no
CONSOLE_ENABLE 		   	= no

# ifeq ($(strip $(DEBUG_MATRIX)), yes)
#     OPT_DEFS += -DDEBUG_MATRIX
# endif
