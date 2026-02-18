#include QMK_KEYBOARD_H
#include "os_detection.h"
#include "unicode.h"
#include "keymap_german.h"

// ============================================================
// OS Detection State
// ============================================================
static bool is_mac = false;

// ============================================================
// Custom keycodes for OS-dependent symbols
// Only the 8 keycodes that differ between Mac and Win/Linux
// ============================================================
enum custom_keycodes {
    MY_AT = SAFE_RANGE,   // @
    MY_BSLS,              // Backslash
    MY_LBRC,              // [
    MY_RBRC,              // ]
    MY_LCBR,              // {
    MY_RCBR,              // }
    MY_PIPE,              // |
    MY_TILD,              // ~
};

// ALT+Number shortcuts for Layer 3
#define ALT_1 LALT(KC_1)
#define ALT_2 LALT(KC_2)
#define ALT_3 LALT(KC_3)
#define ALT_4 LALT(KC_4)
#define ALT_5 LALT(KC_5)

// Mac versions (from keymap_german_mac_iso.h):
//   DE_AT   = A(DE_L)        ->  LALT(KC_L)
//   DE_BSLS = S(A(DE_7))     ->  S(LALT(KC_7))
//   DE_LBRC = A(DE_5)        ->  LALT(KC_5)
//   DE_RBRC = A(DE_6)        ->  LALT(KC_6)
//   DE_LCBR = A(DE_8)        ->  LALT(KC_8)
//   DE_RCBR = A(DE_9)        ->  LALT(KC_9)
//   DE_PIPE = A(DE_7)        ->  LALT(KC_7)
//   DE_TILD = A(DE_N)        ->  LALT(KC_N)
//
// Win/Linux versions (from keymap_german.h) — used via DE_ directly:
//   DE_AT   = ALGR(DE_Q)
//   DE_BSLS = ALGR(DE_SS)
//   DE_LBRC = ALGR(DE_8)
//   DE_RBRC = ALGR(DE_9)
//   DE_LCBR = ALGR(DE_7)
//   DE_RCBR = ALGR(DE_0)
//   DE_PIPE = ALGR(DE_LABK)
//   DE_TILD = ALGR(DE_PLUS)

// ============================================================
// OS Detection Callback
// ============================================================
bool process_detected_host_os_user(os_variant_t detected_os) {
    switch (detected_os) {
        case OS_MACOS:
        case OS_IOS:
            is_mac = true;
            set_unicode_input_mode(UNICODE_MODE_MACOS);
            break;
        case OS_WINDOWS:
        case OS_LINUX:
        default:
            is_mac = false;
            set_unicode_input_mode(UNICODE_MODE_LINUX);
            break;
    }
    return true;
}

// ============================================================
// Process custom keycodes — send OS-specific key combos
// ============================================================
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MY_AT:
            if (record->event.pressed) {
                if (is_mac) { tap_code16(LALT(KC_L)); }
                else        { tap_code16(ALGR(KC_Q)); }
            }
            return false;
        case MY_BSLS:
            if (record->event.pressed) {
                if (is_mac) { tap_code16(S(LALT(KC_7))); }
                else        { tap_code16(ALGR(KC_MINS)); } // DE_SS = KC_MINS
            }
            return false;
        case MY_LBRC:
            if (record->event.pressed) {
                if (is_mac) { tap_code16(LALT(KC_5)); }
                else        { tap_code16(ALGR(KC_8)); }
            }
            return false;
        case MY_RBRC:
            if (record->event.pressed) {
                if (is_mac) { tap_code16(LALT(KC_6)); }
                else        { tap_code16(ALGR(KC_9)); }
            }
            return false;
        case MY_LCBR:
            if (record->event.pressed) {
                if (is_mac) { tap_code16(LALT(KC_8)); }
                else        { tap_code16(ALGR(KC_7)); }
            }
            return false;
        case MY_RCBR:
            if (record->event.pressed) {
                if (is_mac) { tap_code16(LALT(KC_9)); }
                else        { tap_code16(ALGR(KC_0)); }
            }
            return false;
        case MY_PIPE:
            if (record->event.pressed) {
                if (is_mac) { tap_code16(LALT(KC_7)); }
                else        { tap_code16(ALGR(KC_NUBS)); } // DE_LABK = KC_NUBS
            }
            return false;
        case MY_TILD:
            if (record->event.pressed) {
                if (is_mac) { tap_code16(LALT(KC_N)); }
                else        { tap_code16(ALGR(KC_RBRC)); } // DE_PLUS = KC_RBRC
            }
            return false;
    }
    return true;
}

// ============================================================
// LED spiral maps
// ============================================================
typedef struct {
    uint16_t key;
    uint8_t led_idx;
} key_led_map_t;

const key_led_map_t left_spiral_map[23] = {
    { KC_SPC,   0 },  { KC_B,     1 },  { KC_G,     2 },
    { KC_T,     3 },  { KC_R,     4 },  { KC_F,     5 },
    { KC_V,     6 },  { MO(2),    7 },  { KC_LGUI,  8 },
    { KC_C,     9 },  { KC_D,    10 },  { KC_E,    11 },
    { KC_W,    12 },  { KC_S,    13 },  { KC_X,    14 },
    { KC_Y,    15 },  { KC_A,    16 },  { KC_Q,    17 },
    { KC_TAB,  18 },  { KC_LSFT, 19 },  { KC_LCTL, 20 },
    { KC_ESC,  21 },  { KC_DEL,  22 }
};

const key_led_map_t right_spiral_map[23] = {
    { KC_ENT,   23 },  { KC_N,     24 },  { KC_H,     25 },
    { KC_Z,     26 },  { KC_U,     27 },  { KC_J,     28 },
    { KC_M,     29 },  { MO(1),    30 },  { KC_LALT,  31 },
    { KC_COMM,  32 },  { KC_K,     33 },  { KC_I,     34 },
    { KC_O,     35 },  { KC_L,     36 },  { KC_DOT,   37 },
    { KC_MINS,  38 },  { DE_UDIA,  39 },  { KC_P,     40 },
    { KC_BSPC,  41 },  { DE_ADIA,  42 },  { QK_REP,   43 },
    { KC_HOME,  44 },  { KC_END,   45 }
};

// ============================================================
// RGB Matrix — color per key
// ============================================================
#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_user(void) {

    for (uint8_t i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
        if (i < 23) {
            uint16_t key = left_spiral_map[i].key;
            uint8_t led_idx = left_spiral_map[i].led_idx;
            switch (key) {
                case KC_SPC:
                    rgb_matrix_set_color(led_idx, 157, 124, 216);
                    break;
                case MO(2):
                case KC_LGUI:
                case KC_LCTL:
                case KC_LSFT:
                case KC_TAB:
                case KC_DEL:
                    rgb_matrix_set_color(led_idx, 61, 89, 161);
                    break;
                case KC_ESC:
                    rgb_matrix_set_color(led_idx, 255, 0, 124);
                    break;
                default:
                    rgb_matrix_set_color(led_idx, 79, 214, 190);
            }
        } else {
            uint16_t key = right_spiral_map[i - 23].key;
            uint8_t led_idx = right_spiral_map[i - 23].led_idx;
            switch (key) {
                case KC_ENT:
                    rgb_matrix_set_color(led_idx, 94, 74, 130);
                    break;
                case MO(1):
                case KC_LALT:
                case KC_BSPC:
                case KC_HOME:
                case KC_END:
                    rgb_matrix_set_color(led_idx, 61, 89, 161);
                    break;
                case QK_REP:
                    rgb_matrix_set_color(led_idx, 255, 0, 124);
                    break;
                default:
                    rgb_matrix_set_color(led_idx, 79, 214, 190);
            }
        }
    }
    return true;
}

void suspend_power_down_user(void) {
    rgb_matrix_mode(RGB_MATRIX_BAND_VAL);
}
#endif

// ============================================================
// Keymaps — using MY_ for OS-dependent keys, DE_ for shared
// ============================================================
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
       KC_TAB, MY_AT  , DE_UNDS, MY_LBRC, MY_RBRC, DE_CIRC,  KC_ESC,    KC_HOME, DE_EXLM, DE_LABK, DE_RABK,  DE_EQL, DE_AMPR, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
      KC_LSFT, MY_BSLS, DE_SLSH, MY_LCBR, MY_RCBR, DE_ASTR, KC_DEL,      KC_END, DE_QUES, DE_LPRN, DE_RPRN,   DE_SS, DE_COLN, DE_UDIA,
  //|--------+--------+--------+--------+--------+--------+--------'  `--------+--------+--------+--------+--------+--------+--------|
      KC_LCTL, DE_HASH,  DE_DLR, MY_PIPE, MY_TILD,  DE_GRV,                      DE_PLUS, DE_PERC, DE_DQUO, DE_QUOT, DE_SCLN, QK_REP,
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
      KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, DE_DQUO, DE_QUOT, DE_SCLN,  QK_REP,
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