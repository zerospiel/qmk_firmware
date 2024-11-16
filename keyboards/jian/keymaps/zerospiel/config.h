/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#define IGNORE_MOD_TAP_INTERRUPT

#define TAPPING_TERM 130

#define ONESHOT_TAP_TOGGLE 2
#define ONESHOT_TIMEOUT    1000

#define AUTO_SHIFT_TIMEOUT 140
#define NO_AUTO_SHIFT_NUMERIC

#define MOUSEKEY_INTERVAL            15
#define MOUSEKEY_DELAY               10
#define MOUSEKEY_TIME_TO_MAX         60
#define MOUSEKEY_MAX_SPEED           11
#define MOUSEKEY_WHEEL_TIME_TO_MAX   35
#define MOUSEKEY_WHEEL_DELAY         50

#define COMBO_TERM  60
#define COMBO_COUNT 3