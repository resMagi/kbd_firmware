#include QMK_KEYBOARD_H
#include "unicode.h"
#include "keymap_german.h"

// Step 1: Define symbolic names
enum alt_number_keys {
    ALT_1 = LALT(KC_1),
    ALT_2 = LALT(KC_2),
    ALT_3 = LALT(KC_3),
    ALT_4 = LALT(KC_4),
    ALT_5 = LALT(KC_5),
};


// Define a struct that maps a key
// to the LED matrix index for your spiral.
typedef struct {
    uint16_t key;      // the key identifier (for example, the keycode from your layout)
    uint8_t led_idx;   // the LED matrix index (0 to 22 for left half)
} key_led_map_t;

// Mapping for the left half
const key_led_map_t left_spiral_map[23] = {
    { KC_SPC,   0 },  // Space
    { KC_B,     1 },  // B
    { KC_G,     2 },  // G
    { KC_T,     3 },  // T
    { KC_R,     4 },  // R
    { KC_F,     5 },  // F
    { KC_V,     6 },  // V
    { MO(2),    7 },  // MO(2)^
    { KC_LGUI,  8 },  // Win
    { KC_C,     9 },  // C#pragma once
// macOS-style Option+hex input
#define UNICODE_SELECTED_MODES UNICODE_MODE_MACOS
    { KC_D,    10 },  // D
    { KC_E,    11 },  // E
    { KC_W,    12 },  // W
    { KC_S,    13 },  // S
    { KC_X,    14 },  // X
    { KC_Y,    15 },  // Y
    { KC_A,    16 },  // A
    { KC_Q,    17 },  // Q
    { KC_TAB,  18 },  // Tab
    { KC_LSFT, 19 },  // Shift
    { KC_LCTL, 20 },  // Ctrl
    { KC_ESC,  21 },  // Esc
    { KC_DEL,  22 }   // Del
};

// Mapping for the right half
const key_led_map_t right_spiral_map[23] = {
    { KC_ENT,   23 },  // Enter
    { KC_N,     24 },  // N
    { KC_H,     25 },  // H
    { KC_Z,     26 },  // Z
    { KC_U,     27 },  // U
    { KC_J,     28 },  // J
    { KC_M,     29 },  // M
    { MO(1),    30 },  // MO(1)
    { KC_LALT,  31 },  // Alt
    { KC_COMM,  32 },  // ,
    { KC_K,     33 },  // K
    { KC_I,     34 },  // I
    { KC_O,     35 },  // O
    { KC_L,     36 },  // L
    { KC_DOT,   37 },  // . 
    { KC_MINS,  38 },  // -
    { DE_UDIA,  39 },  // Ü
    { KC_P,     40 },  // P
    { KC_BSPC,  41 },  // Backspace 
    { DE_ADIA,  42 },  // Ä
    { QK_REP,   43 },  // Repeat
    { KC_HOME,  44 },  // Home
    { KC_END,   45 }   // End
};


#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_user(void) {
    
    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        if (i < 23) {
            uint16_t key = left_spiral_map[i].key;
            uint8_t led_idx = left_spiral_map[i].led_idx;
            switch (key) {
                case KC_SPC:
                    rgb_matrix_set_color(led_idx, 157, 124, 216); // violet
                    break;
                case MO(2):
                    rgb_matrix_set_color(led_idx, 61, 89, 161); // blue
                    break;
                case KC_LGUI:
                    rgb_matrix_set_color(led_idx, 61, 89, 161); // blue
                    break;
                case KC_LCTL:
                    rgb_matrix_set_color(led_idx, 61, 89, 161); // blue
                    break;
                case KC_LSFT:
                    rgb_matrix_set_color(led_idx, 61, 89, 161); // blue
                    break;
                case KC_TAB:
                    rgb_matrix_set_color(led_idx, 61, 89, 161); // blue
                    break;
                case KC_DEL:
                    rgb_matrix_set_color(led_idx, 61, 89, 161); // blue
                    break;
                case KC_ESC:
                    rgb_matrix_set_color(led_idx, 255, 0, 124); // pink
                    break;
                default:
                    rgb_matrix_set_color(led_idx, 79, 214, 190); // turquoise
            }
        } else {
            uint16_t key = right_spiral_map[i -23].key;
            uint8_t led_idx = right_spiral_map[i -23].led_idx;
            switch (key) {
                case KC_ENT:
                    rgb_matrix_set_color(led_idx, 94, 74, 130); // violet
                    break;
                case MO(1):
                    rgb_matrix_set_color(led_idx, 61, 89, 161); // blue
                    break;
                case KC_LALT                                                                                                                                                                                                                    :
                    rgb_matrix_set_color(led_idx, 61, 89, 161); // blue
                    break;
                case KC_BSPC:
                    rgb_matrix_set_color(led_idx, 61, 89, 161); // blue
                    break;
                case KC_HOME:
                    rgb_matrix_set_color(led_idx, 61, 89, 161); // blue
                    break;
                case KC_END:
                    rgb_matrix_set_color(led_idx, 61, 89, 161); // blue
                    break;
                case QK_REP:
                    rgb_matrix_set_color(led_idx, 255, 0, 124); // pink
                    break;
                default:
                    rgb_matrix_set_color(led_idx, 79, 214, 190); // turquoise
            }
        }
    }
    return true;
}
void suspend_power_down_user(void) {
    // code will run multiple times while keyboard is suspended
    rgb_matrix_mode(RGB_MATRIX_BAND_VAL);
}
#endif
// Windows
// [1] = LAYOUT_split_3x6_3_ex2(
//     //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
//          KC_TAB, DE_AT  , DE_UNDS, DE_LBRC, DE_RBRC, DE_CIRC,  KC_ESC,    KC_HOME, DE_EXLM, DE_LABK, DE_RABK,  DE_EQL, DE_AMPR, KC_BSPC,
//     //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
//         KC_LSFT, DE_BSLS, DE_SLSH, DE_LCBR, DE_RCBR, DE_ASTR, KC_DEL,      KC_END, DE_QUES, DE_LPRN, DE_RPRN,   DE_SS, DE_COLN, DE_UDIA,
//     //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
//         KC_LCTL, DE_HASH,  DE_DLR, DE_PIPE, DE_TILD,  DE_GRV,                      DE_PLUS, DE_PERC, DE_DQUO, DE_QUOT, DE_SCLN, QK_REP,
//     //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
//                                             KC_LGUI,   MO(3),  KC_SPC,     KC_ENT, XXXXXXX, KC_RGUI
//                                         //`--------------------------'  `--------------------------'
//   )

// [1] = LAYOUT_split_3x6_3_ex2(
//     //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
//         KC_TAB,ALGR(KC_Q),S(KC_MINS),KC_LBRC,KC_RBRC,KC_GRV,  KC_ESC,    KC_HOME,S(KC_1),S(KC_COMM),S(KC_DOT),KC_EQL, S(KC_7), KC_BSPC,
//     //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
//         KC_LSFT,KC_BSLS,KC_SLSH,S(KC_LBRC),S(KC_RBRC),S(KC_8), KC_DEL,    KC_END,S(KC_SLASH),S(KC_9),S(KC_0), U_SZ,  S(KC_SCLN),U_UMLAUT_U,
//     //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
//         KC_LCTL,KC_NUHS,S(KC_4),S(KC_BSLS),S(KC_GRV),KC_GRV,                       KC_PPLS,S(KC_5),S(KC_QUOT),KC_QUOT,KC_SCLN,QK_REP,
//     //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
//                                             KC_LGUI,   MO(3),  KC_SPC,     KC_ENT, XXXXXXX, KC_RGUI
//                                         //`--------------------------'  `--------------------------'
//     ),

//   [1] = LAYOUT_split_3x6_3_ex2(
//   //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
//       KC_TAB,    KC_AT, KC_UNDS, KC_LBRC, KC_RBRC, KC_CIRC, KC_ESC,     KC_HOME, KC_EXLM,   KC_LT,   KC_GT,  KC_EQL,  KC_DLR, KC_BSPC,
//   //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
//       KC_LSFT, KC_BSLS, KC_SLSH, KC_LCBR, KC_RCBR, KC_ASTR,  KC_DEL,     KC_END,  KC_QUES, KC_LPRN, KC_RPRN,UM(U_SZ), KC_COLN,UM(U_UMLAUT_U),
//   //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
//       KC_LCTL,KC_HASH ,  KC_DLR, KC_PIPE, KC_TILD,  KC_GRV,                      KC_PLUS, KC_PERC,  KC_DQT, KC_QUOT, KC_SCLN,  QK_REP,
//   //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
//                                           KC_LGUI,   MO(3),  KC_SPC,     KC_ENT, XXXXXXX, KC_RGUI
//                                       //`--------------------------'  `--------------------------'
//   ),



#ifdef LAYOUT_split_3x6_3_ex2
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,  KC_ESC,     KC_HOME,    KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_A,    KC_S,    KC_D,    KC_F,   KC_G,  KC_DEL ,     KC_END,    KC_H,    KC_J,    KC_K,    KC_L, DE_ODIA, DE_ADIA,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, DE_MINS, QK_REP,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   MO(2),  KC_SPC,     KC_ENT,   MO(1), KC_LALT
                                      //`--------------------------'  `--------------------------'

  ),

[1] = LAYOUT_split_3x6_3_ex2(
    //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
         KC_TAB, DE_AT  , DE_UNDS, DE_LBRC, DE_RBRC, DE_CIRC,  KC_ESC,    KC_HOME, DE_EXLM, DE_LABK, DE_RABK,  DE_EQL, DE_AMPR, KC_BSPC,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
        KC_LSFT, DE_BSLS, DE_SLSH, DE_LCBR, DE_RCBR, DE_ASTR, KC_DEL,      KC_END, DE_QUES, DE_LPRN, DE_RPRN,   DE_SS, DE_COLN, DE_UDIA,
    //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
        KC_LCTL, DE_HASH,  DE_DLR, DE_PIPE, DE_TILD,  DE_GRV,                      DE_PLUS, DE_PERC, DE_DQUO, DE_QUOT, DE_SCLN, QK_REP,
    //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                            KC_LGUI,   MO(3),  KC_SPC,     KC_ENT, XXXXXXX, KC_RGUI
                                        //`--------------------------'  `--------------------------'
  ),

  [2] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
       KC_TAB, KC_BSPC,   KC_UP,  KC_DEL, KC_PGUP, KC_HOME,  KC_ESC,    KC_HOME,    KC_0,    KC_1,    KC_2,    KC_3,    KC_4, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_LEFT,KC_DOWN,KC_RIGHT,  KC_PGDN,  KC_END, KC_DEL,      KC_END,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  QK_REP,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, XXXXXXX,  KC_ENT,     KC_SPC,   MO(3), KC_RGUI
                                      //`--------------------------'  `--------------------------'  
  ),

  [3] = LAYOUT_split_3x6_3_ex2(
  //,--------------------------------------------------------------.  ,--------------------------------------------------------------.
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,  KC_ESC,    KC_HOME,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      RGB_TOG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_DEL,      KC_END,   ALT_1,   ALT_2,   ALT_3,   ALT_4, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_REP,
  //|--------+--------+--------+--------+--------+--------+--------.  ,--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, XXXXXXX,  KC_ENT,     KC_SPC, XXXXXXX, KC_RGUI
                                      //`--------------------------'  `--------------------------'
  )
};
#else
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ESC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, TL_LOWR,  KC_SPC,     KC_ENT, TL_UPPR, KC_RALT
                                      //`--------------------------'  `--------------------------'

  ),

  [1] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [2] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  ),

  [3] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  )
};
#endif

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
  [0] = { ENCODER_CCW_CW(RGB_MOD, RGB_RMOD), ENCODER_CCW_CW(RGB_HUI, RGB_HUD), ENCODER_CCW_CW(RGB_VAI, RGB_VAD), ENCODER_CCW_CW(RGB_SAI, RGB_SAD), },
  [1] = { ENCODER_CCW_CW(RGB_MOD, RGB_RMOD), ENCODER_CCW_CW(RGB_HUI, RGB_HUD), ENCODER_CCW_CW(RGB_VAI, RGB_VAD), ENCODER_CCW_CW(RGB_SAI, RGB_SAD), },
  [2] = { ENCODER_CCW_CW(RGB_MOD, RGB_RMOD), ENCODER_CCW_CW(RGB_HUI, RGB_HUD), ENCODER_CCW_CW(RGB_VAI, RGB_VAD), ENCODER_CCW_CW(RGB_SAI, RGB_SAD), },
  [3] = { ENCODER_CCW_CW(RGB_MOD, RGB_RMOD), ENCODER_CCW_CW(RGB_HUI, RGB_HUD), ENCODER_CCW_CW(RGB_VAI, RGB_VAD), ENCODER_CCW_CW(RGB_SAI, RGB_SAD), },
};
#endif
