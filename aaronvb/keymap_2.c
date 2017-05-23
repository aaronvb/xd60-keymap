// XD60 Rev 2.0
// Aaron Van Bokhoven 2017
// KLE: https://goo.gl/Adsg0g
// Source: https://github.com/aaronvb/xd60-keymap

#include "xd60.h"
#include "action_layer.h"
#include "backlight.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  // 0: Base Layer
  KEYMAP(
      F(2),    KC_1,    KC_2,    KC_3,    KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,    KC_0,    KC_MINS,  KC_EQL,  KC_GRV,  KC_BSPC,    \
      KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,    KC_P,    KC_LBRC,  KC_RBRC,          KC_BSLS,    \
      KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,    KC_SCLN, KC_QUOT,  KC_NO,            KC_ENT,     \
      KC_LSFT, KC_LSFT, KC_Z,    KC_X,    KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM, KC_DOT,  KC_NO,    F(1),    KC_UP,   F(0),       \
      KC_LCTL, KC_LALT, KC_LGUI,                          KC_SPC,                          KC_RGUI, KC_RALT,  KC_LEFT, KC_DOWN, KC_RIGHT),

  // 1: Function Layer
  KEYMAP(
      F(2),    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9, KC_F10,  KC_F11, KC_F12, KC_F13, KC_DEL,    \
      BL_STEP, RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_NO, KC_PSCR, KC_NO,  KC_NO,  KC_NO,             \
      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,   KC_NO,  KC_NO,  KC_NO,             \
      KC_NO,   KC_NO,   KC_VOLD, KC_VOLU, KC_MUTE, KC_MPRV, KC_MPLY, KC_MNXT, KC_NO,   KC_NO, KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_TRNS,   \
      KC_NO,   KC_NO,   KC_NO,                            KC_NO,                              KC_NO,   KC_NO,  KC_NO,  KC_NO,  KC_NO),

};

enum function_id {
  ESCAPE
};

// Custom Actions
const uint16_t PROGMEM fn_actions[] = {
    [0] = ACTION_LAYER_MOMENTARY(1),  // to Fn overlay
    [1] = ACTION_MODS_TAP_KEY(MOD_RSFT, KC_SLSH),
    [2] = ACTION_FUNCTION(ESCAPE)
};

// Macros
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {

  // MACRODOWN only works in this function
  switch(id) {
    case 0:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        backlight_step();
      }
      else { unregister_code(KC_RSFT); }
      break;
  }

  return MACRO_NONE;
};

// Loop
void matrix_scan_user(void) {
  // Empty
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
	if(id == ESCAPE) {
		void (*method)(uint8_t) = (record->event.pressed) ? &add_key : &del_key;
		uint8_t commanded = get_mods() & (MOD_BIT(KC_LGUI) | MOD_BIT(KC_RGUI));

		if(layer_state == 0)
			method(commanded ? KC_GRAVE : KC_ESCAPE);
		else
			method(commanded ? KC_ESCAPE : KC_GRAVE);

		send_keyboard_report();
	}
}
