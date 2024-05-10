#include QMK_KEYBOARD_H
#include "keymap_japanese.h"

enum layer_number {
   _EUCALYN = 0,
   _SYMBOL,
   _ARROW,
   _FUNC,
   _NUM
};

enum custom_keycodes {
   EUCALYN = SAFE_RANGE,
   FUNC,
   ENG_SYM,
   JPN_NUM,
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define ENT_ARW LT(_ARROW, KC_ENT)
#define DEL_SHT SFT_T(KC_DEL)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   [_EUCALYN] = LAYOUT(
      KC_TAB,  KC_Q,    KC_W,    KC_COMM, KC_DOT,  JP_SCLN,                   KC_M,    KC_R,    KC_D,    KC_Y,    KC_P,    KC_BSPC, \
      KC_LCTL, KC_A,    KC_O,    KC_E,    KC_I,    KC_U,                      KC_G,    KC_T,    KC_K,    KC_S,    KC_N,    ENT_ARW, \
      DEL_SHT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_F,                      KC_B,    KC_H,    KC_J,    KC_L,    KC_SLSH, DEL_SHT, \
      KC_LGUI, KC_LALT, FUNC,    KC_LCTL,ENG_SYM,  KC_SPC, XXXXXXX, XXXXXXX, KC_SPC,   JPN_NUM, KC_RGUI, FUNC,    KC_LALT, KC_RGUI \
   ),

   [_SYMBOL] = LAYOUT(
      KC_ESC,  JP_LPRN, JP_RPRN, _______, _______, _______,                   _______, JP_AT,   JP_CIRC, JP_YEN,  KC_MINS, _______, \
      _______, JP_LCBR, JP_RCBR, _______, _______, _______,                   _______, _______, JP_COLN, JP_LBRC, JP_RBRC, _______, \
      _______, KC_LABK, KC_RABK, _______, _______, _______,                   _______, _______, JP_SCLN, JP_GRV,  JP_UNDS, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
   ),

   [_ARROW] = LAYOUT(
      _______, _______, _______, KC_UP,   _______, _______,                   _______, _______, KC_UP,   _______, _______, _______, \
      _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______,                   _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, \
      _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
   ),

   [_FUNC] = LAYOUT(
      _______, AG_SWAP, _______, _______, _______, _______,                   _______, _______, _______, _______, KC_VOLU, _______, \
      _______, AG_NORM, _______, _______, _______, _______,                   _______, _______, _______, KC_F15,  KC_VOLD, _______, \
      _______, QK_BOOT, _______, _______, _______, _______,                   _______, _______, _______, KC_F14,  KC_MUTE, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
   ),

      [_NUM] = LAYOUT(
      KC_ESC,  JP_1,    JP_2,    JP_3,    JP_4,    JP_5,                      JP_6,    JP_7,    JP_8,    JP_9,    JP_0,    _______, \
      _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
      _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
   )
};

void persistent_default_layer_set(uint16_t default_layer) {
   eeconfig_update_default_layer(default_layer);
   default_layer_set(default_layer);
}

static bool eng_sym_pressed = false;
static bool jpn_sym_pressed = false;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
   switch (keycode) {
      case FUNC:
         if (record->event.pressed) {
            layer_on(_FUNC);
         } else {
            layer_off(_FUNC);
         }
         return false;
         break;

      case ENG_SYM:
         if (record->event.pressed) {
            eng_sym_pressed = true;
            layer_on(_SYMBOL);
         } else {
            layer_off(_SYMBOL);
            if (eng_sym_pressed) {
               register_code(KC_LNG2);
               unregister_code(KC_LNG2);
           }
           eng_sym_pressed = false;
         }
         return false;
         break;

      case JPN_NUM:
            if (record->event.pressed) {
               jpn_sym_pressed = true;
               layer_on(_NUM);
            } else {
               layer_off(_NUM);
               if (jpn_sym_pressed) {
                  register_code(KC_LNG1);
                  unregister_code(KC_LNG1);
              }
              jpn_sym_pressed = false;
            }
            return false;
            break;

      default:
         if (record->event.pressed) {
            eng_sym_pressed = false;
            jpn_sym_pressed = false;
         }
         break;
   }
   return true;
}
