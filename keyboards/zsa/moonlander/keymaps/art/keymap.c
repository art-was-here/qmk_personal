// art was here

#include QMK_KEYBOARD_H
#include "version.h"

enum layers {
    MASTER,  // default layer
    SLAVE,   // symbols
};

enum custom_keycodes {
    VRSN = SAFE_RANGE,
    CMD_C,  // Command+C macro for macOS
    CMD_V,  // Command+V macro for macOS
    MV_CMD,    // AutoCAD move command
    STR_CMD, // AutoCAD stretch command
    QUIT,    // Command+Q macro for macOS
    CMD_TRM, // AutoCAD trim command
    CMD_EX,  // AutoCAD extend command
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MASTER] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_VOLU,          KC_MNXT,  KC_6,    KC_7,    KC_8,    KC_9,   KC_0,    KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_MUTE,        TO(SLAVE),  KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,     KC_DEL,
        KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_VOLD,          KC_MPRV,  KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT,
        KC_LOPT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                                KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, CMD_TRM,
        KC_LCTL, KC_LALT, CMD_C,  CMD_V,  MV_CMD, STR_CMD,     QUIT,             KC_F3,           KC_UP,    KC_DOWN,KC_LEFT, KC_RGHT,  CMD_EX,
                                          KC_SPC,  KC_BSPC, KC_LGUI,           KC_MINS,  KC_EQL,  KC_ENT
    ),

    [SLAVE] = LAYOUT(
        QK_BOOT,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5, _______,           _______, KC_F6  ,  KC_F7,    KC_F8,   KC_F9,   KC_F10,  KC_F11,
        _______, RM_TOGG, RM_NEXT, RM_PREV, RM_HUEU, RM_HUED, _______,        TO(MASTER), XXXXXXX,   KC_7,     KC_8,    KC_9,  XXXXXXX,  KC_F12,
        _______, RM_SATU, RM_SATD, RM_VALU, RM_VALD,  KC_GRV, _______,           _______, XXXXXXX,   KC_4,     KC_5,    KC_6,  XXXXXXX, KC_LBRC,
        _______, RM_SPDU, RM_SPDD, _______, _______, _______,                             XXXXXXX,   KC_1,     KC_2,    KC_3,  XXXXXXX, KC_RBRC,
        _______, _______, _______, _______, _______,          _______,           _______,            KC_0,     KC_0,    KC_0,  XXXXXXX,  KC_GRV,
                                            _______, _______, _______,           _______, _______, _______
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
        case VRSN:
            SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
            return false;
        case CMD_C:
            register_code(KC_LGUI);
            register_code(KC_C);
            unregister_code(KC_C);
            unregister_code(KC_LGUI);
            return false;
        case CMD_V:
            register_code(KC_LGUI);
            register_code(KC_V);
            unregister_code(KC_V);
            unregister_code(KC_LGUI);
            return false;
        case MV_CMD:
            SEND_STRING("move" SS_TAP(X_ENTER));
            return false;
        case STR_CMD:
            SEND_STRING("stretch" SS_TAP(X_ENTER));
            return false;
        case QUIT:
            register_code(KC_LGUI);
            register_code(KC_Q);
            unregister_code(KC_Q);
            unregister_code(KC_LGUI);
            return false;
        case CMD_TRM:
            SEND_STRING("trim" SS_TAP(X_ENTER));
            return false;
        case CMD_EX:
            SEND_STRING("ex" SS_TAP(X_ENTER));
            return false;
        }
    }
    return true;
}
