
#include <USBComposite.h>

USBHID HID;
const uint8_t reportDescription[] = {
  HID_CONSUMER_REPORT_DESCRIPTOR(),
  HID_KEYBOARD_REPORT_DESCRIPTOR()
};
HIDConsumer Consumer(HID);
HIDKeyboard Keyboard(HID);
USBCompositeSerial CompositeSerial;



/*
   Once uncommented, pins PB12 and PB13 won't be scanned and will be used for status LEDs instead.
   This is useful with the smaller connector to use the unused GPIOs for NUMLOCK and SCRLCK leds
   CAPS led can't be used for scanning - it's sink only.
*/
#define EXTRA_STATUS_LEDS
// LED pins (only used if EXTRA_STATUS_LEDS is defined)
#define CAPSLOCK_LED PC13
#define NUMLOCK_LED PB13
#define SCRLK_LED PB12
/*
    Uncomment this if you want to map keys, you can just open arduino Serial monitor and push all buttons in systematic order.
    Once you're done pushing all buttons, copy the output and paste it to mappedPins variable (line #124)
*/
//#define MAPPING_MODE


/*
   Available keys from USBComposite_stm32f1 library

           BRIGHTNESS_UP = 0x6F,
           BRIGHTNESS_DOWN = 0x70,
           NEXT_TRACK = 0xB5,
           PREVIOUS_TRACK = 0xB6,
           PLAY_OR_PAUSE = 0xCD,
           VOLUME_UP = 0xE9,
           VOLUME_DOWN = 0xEA,
           REWIND = 0xB4,
           FAST_FORWARD = 0xB3,
           MUTE = 0xE2,


  #define KEY_LEFT_CTRL   0x80
  #define KEY_LEFT_SHIFT    0x81
  #define KEY_LEFT_ALT    0x82
  #define KEY_LEFT_GUI    0x83
  #define KEY_RIGHT_CTRL    0x84
  #define KEY_RIGHT_SHIFT   0x85
  #define KEY_RIGHT_ALT   0x86
  #define KEY_RIGHT_GUI   0x87

  #define KEY_HID_OFFSET      0x88

  // The following definitions takes their value from the document at https://www.usb.org/sites/default/files/hut1_22.pdf, starting p82
  // However, their value are augmented by KEY_HID_OFFSET (for example, KEY_F12 real value is 0x45)
  #define KEY_UP_ARROW    0xDA
  #define KEY_DOWN_ARROW    0xD9
  #define KEY_LEFT_ARROW    0xD8
  #define KEY_RIGHT_ARROW   0xD7
  #define KEY_BACKSPACE   0xB2
  #define KEY_TAB       0xB3
  #define KEY_RETURN      0xB0
  #define KEY_ESC       0xB1
  #define KEY_INSERT      0xD1
  #define KEY_DELETE      0xD4
  #define KEY_PAGE_UP     0xD3
  #define KEY_PAGE_DOWN   0xD6
  #define KEY_HOME      0xD2
  #define KEY_END       0xD5
  #define KEY_CAPS_LOCK   0xC1
  #define KEY_F1        0xC2
  #define KEY_F2        0xC3
  #define KEY_F3        0xC4
  #define KEY_F4        0xC5
  #define KEY_F5        0xC6
  #define KEY_F6        0xC7
  #define KEY_F7        0xC8
  #define KEY_F8        0xC9
  #define KEY_F9        0xCA
  #define KEY_F10       0xCB
  #define KEY_F11       0xCC
  #define KEY_F12       0xCD

*/

/*
    Media codes here:
    https://www.usb.org/sites/default/files/documents/hut1_12v2.pdf
    What you're looking for is the "Usage ID", make sure to write it in HEX format with "0x"
    for example System sleep = 0x82
*/

#define KEY_MEDIA_PLAYPAUSE 0xe8
#define KEY_MEDIA_STOPCD 0xe9
#define KEY_MEDIA_PREVIOUSSONG 0xea
#define KEY_MEDIA_NEXTSONG 0xeb
#define KEY_MEDIA_EJECTCD 0xec
#define KEY_MEDIA_VOLUMEUP 0xed
#define KEY_MEDIA_VOLUMEDOWN 0xee
#define KEY_MEDIA_MUTE 0xef
#define KEY_MEDIA_WWW 0xf0
#define KEY_MEDIA_BACK 0xf1
#define KEY_MEDIA_FORWARD 0xf2
#define KEY_MEDIA_STOP 0xf3
#define KEY_MEDIA_FIND 0xf4
#define KEY_MEDIA_SCROLLUP 0xf5
#define KEY_MEDIA_SCROLLDOWN 0xf6
#define KEY_MEDIA_EDIT 0xf7
#define KEY_MEDIA_SLEEP 0x82
#define KEY_MEDIA_CALC 0x192

// Additional HID codes
#define KEY_NO_FUNCTION 0 // Default / empty key... use this for buttons you don't want to do anything
#define KEY_FN -1 // FN code is not sent and is only used for FN detection

#define KEY_PRTSCR 206 // Keyboard Print Screen, 0x46, 
#define KEY_SYSRQ 206 // Keyboard Print Screen
#define KEY_PAUSE 208 // Keyboard Pause, 0x48
#define KEY_SCROLL_LOCK 207 // Keyboard Scroll Lock, 0x47
#define KEY_NUMLOCK 219 // Keyboard Num Lock and Clear

#define KEY_SPACE 32 // Keyboard Spacebar
#define KEY_MINUS 45 // Keyboard - and _
#define KEY_EQUAL 61 // Keyboard = and +
#define KEY_LEFTBRACE 91 // Keyboard [ and {
#define KEY_RIGHTBRACE 93 // Keyboard ] and }
#define KEY_BACKSLASH 92 // Keyboard \ and |
#define KEY_SEMICOLON 59 // Keyboard ; and :
#define KEY_APOSTROPHE 39 // Keyboard ' and "
#define KEY_GRAVE 96 // Keyboard ` and ~
#define KEY_COMMA 44 // Keyboard , and <
#define KEY_DOT 46 // Keyboard . and >
#define KEY_SLASH 47 // Keyboard / and ?

#define KEY_1 49 // Keyboard 1 and !
#define KEY_2 50 // Keyboard 2 and @
#define KEY_3 51 // Keyboard 3 and #
#define KEY_4 52 // Keyboard 4 and $
#define KEY_5 53 // Keyboard 5 and %
#define KEY_6 54 // Keyboard 6 and ^
#define KEY_7 55 // Keyboard 7 and &
#define KEY_8 56 // Keyboard 8 and *
#define KEY_9 57 // Keyboard 9 and (
#define KEY_0 48 // Keyboard 0 and )

#define KEY_A 97 // Keyboard a and A
#define KEY_B 98 // Keyboard b and B
#define KEY_C 99 // Keyboard c and C
#define KEY_D 100 // Keyboard d and D
#define KEY_E 101 // Keyboard e and E
#define KEY_F 102 // Keyboard f and F
#define KEY_G 103 // Keyboard g and G
#define KEY_H 104 // Keyboard h and H
#define KEY_I 105 // Keyboard i and I
#define KEY_J 106 // Keyboard j and J
#define KEY_K 107 // Keyboard k and K
#define KEY_L 108 // Keyboard l and L
#define KEY_M 109 // Keyboard m and M
#define KEY_N 110 // Keyboard n and N
#define KEY_O 111 // Keyboard o and O
#define KEY_P 112 // Keyboard p and P
#define KEY_Q 113 // Keyboard q and Q
#define KEY_R 114 // Keyboard r and R
#define KEY_S 115 // Keyboard s and S
#define KEY_T 116 // Keyboard t and T
#define KEY_U 117 // Keyboard u and U
#define KEY_V 118 // Keyboard v and V
#define KEY_W 119 // Keyboard w and W
#define KEY_X 120 // Keyboard x and X
#define KEY_Y 121 // Keyboard y and Y
#define KEY_Z 122 // Keyboard z and Z

struct Pins {
  uint8_t number;
  String name;
};
Pins pins[] = {
  {PA0, "PA0"},
  {PA1, "PA1"},
  {PA2, "PA2"},
  {PA3, "PA3"},
  {PA4, "PA4"},
  {PA5, "PA5"},
  {PA6, "PA6"},
  {PA7, "PA7"},
  {PA8, "PA8"},
  {PA9, "PA9"},
  {PA10, "PA10"},
  {PA15, "PA15"},
  {PB0, "PB0"},
  {PB1, "PB1"},
  {PB3, "PB3"},
  {PB4, "PB4"},
  {PB5, "PB5"},
  {PB6, "PB6"},
  {PB7, "PB7"},
  {PB8, "PB8"},
  {PB9, "PB9"},
  {PB10, "PB10"},
  {PB11, "PB11"},
#ifndef EXTRA_STATUS_LEDS
  {PB12, "PB12"},
  {PB13, "PB13"},
#endif
  {PB14, "PB14"}, // This pin is not connected to the smaller connector
  {PB15, "PB15"},
};
int pinsSize = sizeof(pins) / sizeof(pins[0]);

struct KeyMap {
  uint8_t pin1;
  uint8_t pin2;
  uint8_t state;
  int key;
  bool key_consumer;
  int key_alt;
  bool key_alt_consumer;
};

/*
  // Acer Aspire One keyboard (netbook)
  KeyMap mappedPins[] {
  // Pin1, Pin2, Primary function, Secondary function, is consumer key
  {PA7, PB11, 0, KEY_ESC, false, KEY_NO_FUNCTION, false}, // esc
  {PB4, PB11, 0, KEY_F1, false, KEY_NO_FUNCTION, false}, // f1
  {PA9, PB11, 0, KEY_F2, false, KEY_NO_FUNCTION, false}, // f2
  {PA9, PB10, 0, KEY_F3, false, KEY_NO_FUNCTION, false}, // f3 / wifi
  {PB4, PB10, 0, KEY_F4, false, KEY_MEDIA_SLEEP, true}, // f4 / sleep
  {PA3, PB11, 0, KEY_F5, false, KEY_NO_FUNCTION, false}, // f5 / switch screen
  {PB11, PB15, 0, KEY_F6, false, KEY_NO_FUNCTION, false}, // f6 / turn off screen
  {PB10, PB15, 0, KEY_F7, false, KEY_NO_FUNCTION, false}, // f7 / disable touchpad
  {PA3, PB10, 0, KEY_F8, false, HIDConsumer::MUTE, true}, // f8 / mute
  {PA4, PB0, 0, KEY_F9, false, KEY_NO_FUNCTION, false}, // f9
  {PA7, PB0, 0, KEY_F10, false, KEY_NO_FUNCTION, false}, // f10
  {PA7, PB10, 0, KEY_F11, false, KEY_NUMLOCK, false}, // f11 / numlock
  {PA4, PB10, 0, KEY_F12, false, KEY_SCROLL_LOCK, false}, // f12 / scroll lock
  {PA8, PB0, 0, KEY_PRTSCR, false, KEY_NO_FUNCTION, false}, // prtscr
  {PB0, PB15, 0, KEY_PAUSE, false, KEY_NO_FUNCTION, false}, // pause / break
  {PA7, PB1, 0, KEY_INSERT, false, KEY_NO_FUNCTION, false}, // insert
  {PA4, PB1, 0, KEY_DELETE, false, KEY_NO_FUNCTION, false}, // delete
  {PA4, PB11, 0, KEY_GRAVE, false, KEY_NO_FUNCTION, false}, // ~
  {PA8, PB10, 0, KEY_1, false, KEY_NO_FUNCTION, false}, // 1
  {PB0, PB4, 0, KEY_2, false, KEY_NO_FUNCTION, false}, // 2
  {PA1, PB0, 0, KEY_3, false, KEY_NO_FUNCTION, false}, // 3
  {PA4, PB5, 0, KEY_4, false, KEY_NO_FUNCTION, false}, // 4
  {PA7, PB5, 0, KEY_5, false, KEY_NO_FUNCTION, false}, // 5
  {PA4, PB6, 0, KEY_6, false, KEY_NO_FUNCTION, false}, // 6
  {PA7, PB6, 0, KEY_7, false, KEY_NO_FUNCTION, false}, // 7
  {PA4, PB7, 0, KEY_8, false, KEY_NO_FUNCTION, false}, // 8
  {PA7, PB7, 0, KEY_9, false, KEY_NO_FUNCTION, false}, // 9
  {PA4, PB8, 0, KEY_0, false, KEY_NO_FUNCTION, false}, // 0
  {PA7, PB8, 0, KEY_MINUS, false, KEY_NO_FUNCTION, false}, // -
  {PA4, PB9, 0, KEY_EQUAL, false, KEY_NO_FUNCTION, false}, // =
  {PA3, PB0, 0, KEY_BACKSPACE, false, KEY_NO_FUNCTION, false}, // backspace
  {PA1, PB11, 0, KEY_TAB, false, KEY_NO_FUNCTION, false}, // tab
  {PA1, PB10, 0, KEY_Q, false, KEY_NO_FUNCTION, false}, // q
  {PA3, PA10, 0, KEY_W, false, KEY_NO_FUNCTION, false}, // w
  {PA1, PB5, 0, KEY_E, false, KEY_NO_FUNCTION, false}, // e
  {PA3, PB5, 0, KEY_R, false, KEY_NO_FUNCTION, false}, // r
  {PA3, PB6, 0, KEY_T, false, KEY_NO_FUNCTION, false}, // t
  {PA1, PB7, 0, KEY_Y, false, KEY_NO_FUNCTION, false}, // y
  {PA3, PB7, 0, KEY_U, false, KEY_NO_FUNCTION, false}, // u
  {PA1, PB8, 0, KEY_I, false, KEY_NO_FUNCTION, false}, // i
  {PA3, PB8, 0, KEY_O, false, KEY_NO_FUNCTION, false}, // o
  {PA4, PA6, 0, KEY_P, false, KEY_NO_FUNCTION, false}, // p
  {PA6, PA7, 0, KEY_LEFTBRACE, false, KEY_NO_FUNCTION, false}, // [
  {PA3, PB9, 0, KEY_RIGHTBRACE, false, KEY_NO_FUNCTION, false}, // ]
  {PA1, PB9, 0, KEY_RETURN, false, KEY_NO_FUNCTION, false}, // enter
  {PA8, PB11, 0, KEY_CAPS_LOCK, false, KEY_NO_FUNCTION, false}, // caps
  {PA10, PB4, 0, KEY_A, false, KEY_NO_FUNCTION, false}, // a
  {PA1, PA10, 0, KEY_S, false, KEY_NO_FUNCTION, false}, // s
  {PA9, PB5, 0, KEY_D, false, KEY_NO_FUNCTION, false}, // d
  {PB4, PB5, 0, KEY_F, false, KEY_NO_FUNCTION, false}, // f
  {PB4, PB6, 0, KEY_G, false, KEY_NO_FUNCTION, false}, // g
  {PA1, PB6, 0, KEY_H, false, KEY_NO_FUNCTION, false}, // h
  {PB4, PB7, 0, KEY_J, false, KEY_NO_FUNCTION, false}, // j
  {PA9, PB8, 0, KEY_K, false, KEY_NO_FUNCTION, false}, // k
  {PB4, PB8, 0, KEY_L, false, KEY_NO_FUNCTION, false}, // l
  {PA1, PA6, 0, KEY_SEMICOLON, false, KEY_NO_FUNCTION, false}, // ;
  {PA3, PA6, 0, KEY_APOSTROPHE, false, KEY_NO_FUNCTION, false}, // '
  {PB4, PB9, 0, KEY_BACKSLASH, false, KEY_NO_FUNCTION, false}, // baclslash
  {PA0, PA9, 0, KEY_LEFT_SHIFT, false, KEY_NO_FUNCTION, false}, // shift l
  {PB5, PB15, 0, KEY_BACKSLASH, false, KEY_NO_FUNCTION, false}, // backslash
  {PA9, PA10, 0, KEY_Z, false, KEY_NO_FUNCTION, false}, // z
  {PA8, PB5, 0, KEY_X, false, KEY_NO_FUNCTION, false}, // x
  {PA8, PB6, 0, KEY_C, false, KEY_NO_FUNCTION, false}, // c
  {PA9, PB6, 0, KEY_V, false, KEY_NO_FUNCTION, false}, // v
  {PA8, PB7, 0, KEY_B, false, KEY_NO_FUNCTION, false}, // b
  {PA9, PB7, 0, KEY_N, false, KEY_NO_FUNCTION, false}, // n
  {PB8, PB15, 0, KEY_M, false, KEY_NO_FUNCTION, false}, // m
  {PA8, PB8, 0, KEY_COMMA, false, KEY_NO_FUNCTION, false}, // ,
  {PA6, PA9, 0, KEY_DOT, false, KEY_NO_FUNCTION, false}, // .
  {PA6, PB4, 0, KEY_SLASH, false, KEY_NO_FUNCTION, false}, // /
  {PA0, PB4, 0, KEY_RIGHT_SHIFT, false, KEY_NO_FUNCTION, false}, // shift r
  {PA2, PB15, 0, KEY_LEFT_CTRL, false, KEY_NO_FUNCTION, false}, // ctrl l
  {PA10, PB15, 0, KEY_FN, false, KEY_NO_FUNCTION, false}, // fn
  {PA15, PB15, 0, KEY_LEFT_GUI, false, KEY_NO_FUNCTION, false}, // win
  {PB3, PB15, 0, KEY_LEFT_ALT, false, KEY_NO_FUNCTION, false}, // alt l
  {PB6, PB15, 0, KEY_SPACE, false, KEY_NO_FUNCTION, false}, // space
  {PA8, PB3, 0, KEY_RIGHT_ALT, false, KEY_NO_FUNCTION, false}, // alt r
  {PB9, PB15, 0, KEY_RIGHT_GUI, false, KEY_NO_FUNCTION, false}, // options
  {PA2, PA9, 0, KEY_RIGHT_CTRL, false, KEY_NO_FUNCTION, false}, // ctrl r
  {PA1, PB1, 0, KEY_PAGE_UP, false, KEY_NO_FUNCTION, false}, // pg up / home
  {PA9, PB0, 0, KEY_UP_ARROW, false, HIDConsumer::VOLUME_UP, true}, // up / vol up
  {PB1, PB4, 0, KEY_PAGE_DOWN, false, KEY_NO_FUNCTION, false}, // pg down / end
  {PB1, PB15, 0, KEY_LEFT_ARROW, false, HIDConsumer::BRIGHTNESS_DOWN, true}, // left / brightness up
  {PA8, PB1, 0, KEY_DOWN_ARROW, false, HIDConsumer::VOLUME_DOWN, true}, // down / vol down
  {PA9, PB1, 0, KEY_RIGHT_ARROW, false, HIDConsumer::BRIGHTNESS_UP, true} // right / brightness up
  };
*/

/*
  // HP Compaq keyboard
  KeyMap mappedPins[] = {
  {PA2, PB8, 0, KEY_INSERT, false, KEY_PRTSCR, false},
  {PB8, PB9, 0, KEY_HOME, false, KEY_SCROLL_LOCK, false},
  {PA9, PB12, 0, KEY_PAGE_UP, false, KEY_PAUSE, false},
  {PA2, PB1, 0, KEY_ESC, false, KEY_NO_FUNCTION, false},
  {PA10, PB1, 0, KEY_F1, false, KEY_NO_FUNCTION, false},
  {PA9, PB10, 0, KEY_F2, false, KEY_NO_FUNCTION, false},
  {PA10, PB10, 0, KEY_F3, false, KEY_MEDIA_SLEEP, true},
  {PA9, PA15, 0, KEY_F4, false, KEY_NO_FUNCTION, false},
  {PA8, PB1, 0, KEY_F5, false, KEY_NO_FUNCTION, false},
  {PA1, PB8, 0, KEY_F6, false, KEY_NO_FUNCTION, false},
  {PA9, PB5, 0, KEY_F7, false, KEY_NO_FUNCTION, false},
  {PA9, PB6, 0, KEY_F8, false, KEY_NO_FUNCTION, false},
  {PB9, PB12, 0, KEY_F9, false, HIDConsumer::BRIGHTNESS_DOWN, true},
  {PB3, PB9, 0, KEY_F10, false, HIDConsumer::BRIGHTNESS_UP, true},
  {PA9, PB3, 0, KEY_F11, false, KEY_NO_FUNCTION, false},
  {PA2, PB3, 0, KEY_F12, false, KEY_NO_FUNCTION, false},
  {PA0, PB12, 0, KEY_DELETE, false, KEY_SYSRQ, false},
  {PA2, PB5, 0, KEY_END, false, KEY_NUMLOCK, false},
  {PA10, PB5, 0, KEY_PAGE_DOWN, false, KEY_PAUSE, false},
  {PA2, PB10, 0, KEY_GRAVE, false, KEY_NO_FUNCTION, false},
  {PB9, PB10, 0, KEY_1, false, KEY_NO_FUNCTION, false},
  {PA15, PB9, 0, KEY_2, false, KEY_NO_FUNCTION, false},
  {PB1, PB9, 0, KEY_3, false, KEY_NO_FUNCTION, false},
  {PA1, PB0, 0, KEY_4, false, KEY_NO_FUNCTION, false},
  {PA8, PB0, 0, KEY_5, false, KEY_NO_FUNCTION, false},
  {PA8, PB4, 0, KEY_6, false, KEY_NO_FUNCTION, false},
  {PA1, PB4, 0, KEY_7, false, KEY_NO_FUNCTION, false},
  {PB5, PB9, 0, KEY_8, false, KEY_NO_FUNCTION, false},
  {PB7, PB9, 0, KEY_9, false, KEY_NO_FUNCTION, false},
  {PB6, PB9, 0, KEY_0, false, KEY_NO_FUNCTION, false},
  {PA2, PB6, 0, KEY_MINUS, false, KEY_NO_FUNCTION, false},
  {PA1, PB12, 0, KEY_EQUAL, false, KEY_NO_FUNCTION, false},
  {PA10, PB3, 0, KEY_BACKSPACE, false, KEY_NO_FUNCTION, false},
  {PA9, PB1, 0, KEY_TAB, false, KEY_NO_FUNCTION, false},
  {PA0, PB10, 0, KEY_Q, false, KEY_NO_FUNCTION, false},
  {PA0, PA15, 0, KEY_W, false, KEY_NO_FUNCTION, false},
  {PA0, PB1, 0, KEY_E, false, KEY_NO_FUNCTION, false},
  {PA0, PB0, 0, KEY_R, false, KEY_NO_FUNCTION, false},
  {PA3, PB0, 0, KEY_T, false, KEY_NO_FUNCTION, false},
  {PA3, PB4, 0, KEY_Y, false, KEY_NO_FUNCTION, false},
  {PA0, PB4, 0, KEY_U, false, KEY_NO_FUNCTION, false},
  {PA0, PB5, 0, KEY_I, false, KEY_NO_FUNCTION, false},
  {PA0, PB7, 0, KEY_O, false, KEY_NO_FUNCTION, false},
  {PA0, PB6, 0, KEY_P, false, KEY_NO_FUNCTION, false},
  {PA1, PB3, 0, KEY_LEFTBRACE, false, KEY_NO_FUNCTION, false},
  {PA10, PB6, 0, KEY_RIGHTBRACE, false, KEY_NO_FUNCTION, false},
  {PA3, PB3, 0, KEY_RETURN, false, KEY_NO_FUNCTION, false},
  {PA2, PA15, 0, KEY_CAPS_LOCK, false, KEY_NO_FUNCTION, false},
  {PA1, PB10, 0, KEY_A, false, KEY_NO_FUNCTION, false},
  {PA1, PA15, 0, KEY_S, false, KEY_NO_FUNCTION, false},
  {PA1, PB1, 0, KEY_D, false, KEY_NO_FUNCTION, false},
  {PB0, PB9, 0, KEY_F, false, KEY_NO_FUNCTION, false},
  {PA10, PB0, 0, KEY_G, false, KEY_NO_FUNCTION, false},
  {PA10, PB4, 0, KEY_H, false, KEY_NO_FUNCTION, false},
  {PB4, PB9, 0, KEY_J, false, KEY_NO_FUNCTION, false},
  {PA1, PB5, 0, KEY_K, false, KEY_NO_FUNCTION, false},
  {PA1, PB7, 0, KEY_L, false, KEY_NO_FUNCTION, false},
  {PA1, PB6, 0, KEY_SEMICOLON, false, KEY_NO_FUNCTION, false},
  {PA8, PB5, 0, KEY_APOSTROPHE, false, KEY_NO_FUNCTION, false},
  {PA3, PB6, 0, KEY_BACKSLASH, false, KEY_NO_FUNCTION, false},
  {PA6, PB11, 0, KEY_LEFT_SHIFT, false, KEY_NO_FUNCTION, false},
  {PA8, PB10, 0, KEY_BACKSLASH, false, KEY_NO_FUNCTION, false},
  {PA3, PB10, 0, KEY_Z, false, KEY_NO_FUNCTION, false},
  {PA3, PA15, 0, KEY_X, false, KEY_NO_FUNCTION, false},
  {PA3, PB1, 0, KEY_C, false, KEY_NO_FUNCTION, false},
  {PA9, PB0, 0, KEY_V, false, KEY_NO_FUNCTION, false},
  {PA2, PB0, 0, KEY_B, false, KEY_NO_FUNCTION, false},
  {PA2, PB4, 0, KEY_N, false, KEY_NO_FUNCTION, false},
  {PA9, PB4, 0, KEY_M, false, KEY_NO_FUNCTION, false},
  {PA3, PB5, 0, KEY_COMMA, false, KEY_NO_FUNCTION, false},
  {PA3, PB7, 0, KEY_DOT, false, KEY_NO_FUNCTION, false},
  {PA8, PB6, 0, KEY_SLASH, false, KEY_NO_FUNCTION, false},
  {PB11, PB13, 0, KEY_RIGHT_SHIFT, false, KEY_NO_FUNCTION, false},
  {PA7, PB11, 0, KEY_LEFT_CTRL, false, KEY_NO_FUNCTION, false},
  {PA5, PB11, 0, KEY_FN, false, KEY_NO_FUNCTION, false},
  {PA10, PB7, 0, KEY_LEFT_GUI, false, KEY_NO_FUNCTION, false},
  {PA4, PB11, 0, KEY_LEFT_ALT, false, KEY_NO_FUNCTION, false},
  {PA9, PB8, 0, KEY_SPACE, false, KEY_NO_FUNCTION, false},
  {PB11, PB14, 0, KEY_RIGHT_ALT, false, KEY_NO_FUNCTION, false},
  {PA0, PB3, 0, KEY_RIGHT_GUI, false, KEY_NO_FUNCTION, false},
  {PB11, PB15, 0, KEY_RIGHT_CTRL, false, KEY_NO_FUNCTION, false},
  {PA8, PB3, 0, KEY_UP_ARROW, false, HIDConsumer::VOLUME_UP, true},
  {PA10, PB12, 0, KEY_LEFT_ARROW, false, HIDConsumer::BRIGHTNESS_DOWN, true},
  {PA10, PB8, 0, KEY_DOWN_ARROW, false, HIDConsumer::VOLUME_DOWN, true},
  {PA2, PB12, 0, KEY_RIGHT_ARROW, false, HIDConsumer::BRIGHTNESS_UP, true},
  };
*/


// Large acer keyboard
KeyMap mappedPins[] = {
  {PA15, PB15, 0, KEY_ESC, false, KEY_NO_FUNCTION, false},
  {PA5, PB15, 0, KEY_F1, false, KEY_NO_FUNCTION, false},
  {PB1, PB15, 0, KEY_F2, false, KEY_NO_FUNCTION, false},
  {PA8, PB1, 0, KEY_F3, false, KEY_NO_FUNCTION, true},
  {PA5, PA8, 0, KEY_F4, false, KEY_MEDIA_SLEEP, true},
  {PB6, PB15, 0, KEY_F5, false, KEY_NO_FUNCTION, false},
  {PB11, PB15, 0, KEY_F6, false, KEY_NO_FUNCTION, false},
  {PA8, PB11, 0, KEY_F7, false, KEY_NO_FUNCTION, false},
  {PA8, PB6, 0, KEY_F8, false, HIDConsumer::MUTE, false},
  {PA10, PB5, 0, KEY_F9, false, KEY_NO_FUNCTION, false},
  {PA10, PA15, 0, KEY_F10, false, KEY_NO_FUNCTION, false},
  {PA8, PA15, 0, KEY_F11, false, KEY_NUMLOCK, false},
  {PA8, PB5, 0, KEY_F12, false, KEY_SCROLL_LOCK, false},
  {PA10, PB10, 0, KEY_PRTSCR, false, KEY_NO_FUNCTION, false},
  {PA10, PB11, 0, KEY_PAUSE, false, KEY_NO_FUNCTION, false},
  {PA9, PA15, 0, KEY_INSERT, false, KEY_NO_FUNCTION, false},
  {PA9, PB5, 0, KEY_DELETE, false, KEY_NO_FUNCTION, false},
  {PB5, PB15, 0, KEY_GRAVE, false, KEY_NO_FUNCTION, false},
  {PA8, PB10, 0, KEY_1, false, KEY_NO_FUNCTION, false},
  {PA5, PA10, 0, KEY_2, false, KEY_NO_FUNCTION, false},
  {PA10, PB8, 0, KEY_3, false, KEY_NO_FUNCTION, false},
  {PA4, PB5, 0, KEY_4, false, KEY_NO_FUNCTION, false},
  {PA4, PA15, 0, KEY_5, false, KEY_NO_FUNCTION, false},
  {PA3, PB5, 0, KEY_6, false, KEY_NO_FUNCTION, false},
  {PA3, PA15, 0, KEY_7, false, KEY_NO_FUNCTION, false},
  {PA2, PB5, 0, KEY_8, false, KEY_NO_FUNCTION, false},
  {PA2, PA15, 0, KEY_9, false, KEY_NO_FUNCTION, false},
  {PA1, PB5, 0, KEY_0, false, KEY_NO_FUNCTION, false},
  {PA1, PA15, 0, KEY_MINUS, false, KEY_NO_FUNCTION, false},
  {PA0, PB5, 0, KEY_EQUAL, false, KEY_NO_FUNCTION, false},
  {PA10, PB6, 0, KEY_BACKSPACE, false, KEY_NO_FUNCTION, false},
  {PA9, PB6, 0, KEY_HOME, false, HIDConsumer::PLAY_OR_PAUSE, true},
  {PB8, PB15, 0, KEY_TAB, false, KEY_NO_FUNCTION, false},
  {PA8, PB8, 0, KEY_Q, false, KEY_NO_FUNCTION, false},
  {PB0, PB6, 0, KEY_W, false, KEY_NO_FUNCTION, false},
  {PA4, PB8, 0, KEY_E, false, KEY_NO_FUNCTION, false},
  {PA4, PB6, 0, KEY_R, false, KEY_NO_FUNCTION, false},
  {PA3, PB6, 0, KEY_T, false, KEY_NO_FUNCTION, false},
  {PA2, PB8, 0, KEY_Y, false, KEY_NO_FUNCTION, false},
  {PA2, PB6, 0, KEY_U, false, KEY_NO_FUNCTION, false},
  {PA1, PB8, 0, KEY_I, false, KEY_NO_FUNCTION, false},
  {PA1, PB6, 0, KEY_O, false, KEY_NO_FUNCTION, false},
  {PB3, PB5, 0, KEY_P, false, KEY_NO_FUNCTION, false},
  {PA15, PB3, 0, KEY_LEFTBRACE, false, KEY_NO_FUNCTION, false},
  {PA0, PB6, 0, KEY_RIGHTBRACE, false, KEY_NO_FUNCTION, false},
  {PA0, PB8, 0, KEY_RETURN, false, KEY_NO_FUNCTION, false},
  {PA9, PB8, 0, KEY_PAGE_UP, false, KEY_MEDIA_STOP, true},
  {PB10, PB15, 0, KEY_CAPS_LOCK, false, KEY_NO_FUNCTION, false},
  {PA5, PB0, 0, KEY_A, false, KEY_NO_FUNCTION, false},
  {PB0, PB8, 0, KEY_S, false, KEY_NO_FUNCTION, false},
  {PA4, PB1, 0, KEY_D, false, KEY_NO_FUNCTION, false},
  {PA4, PA5, 0, KEY_F, false, KEY_NO_FUNCTION, false},
  {PA3, PA5, 0, KEY_G, false, KEY_NO_FUNCTION, false},
  {PA3, PB8, 0, KEY_H, false, KEY_NO_FUNCTION, false},
  {PA2, PA5, 0, KEY_J, false, KEY_NO_FUNCTION, false},
  {PA1, PB1, 0, KEY_K, false, KEY_NO_FUNCTION, false},
  {PA1, PA5, 0, KEY_L, false, KEY_NO_FUNCTION, false},
  {PB3, PB8, 0, KEY_SEMICOLON, false, KEY_NO_FUNCTION, false},
  {PB3, PB6, 0, KEY_APOSTROPHE, false, KEY_NO_FUNCTION, false},
  {PA0, PA5, 0, KEY_BACKSLASH, false, KEY_NO_FUNCTION, false},
  {PA5, PA9, 0, KEY_PAGE_DOWN, false, 0xB6, true},
  {PB1, PB9, 0, KEY_LEFT_SHIFT, false, KEY_NO_FUNCTION, false},
  {PA4, PB11, 0, KEY_BACKSLASH, false, KEY_NO_FUNCTION, false},
  {PB0, PB1, 0, KEY_Z, false, KEY_NO_FUNCTION, false},
  {PA4, PB10, 0, KEY_X, false, KEY_NO_FUNCTION, false},
  {PA3, PB10, 0, KEY_C, false, KEY_NO_FUNCTION, false},
  {PA3, PB1, 0, KEY_V, false, KEY_NO_FUNCTION, false},
  {PA2, PB10, 0, KEY_B, false, KEY_NO_FUNCTION, false},
  {PA2, PB1, 0, KEY_N, false, KEY_NO_FUNCTION, false},
  {PA1, PB11, 0, KEY_M, false, KEY_NO_FUNCTION, false},
  {PA1, PB10, 0, KEY_COMMA, false, KEY_NO_FUNCTION, false},
  {PB1, PB3, 0, KEY_DOT, false, KEY_NO_FUNCTION, false},
  {PA5, PB3, 0, KEY_SLASH, false, KEY_NO_FUNCTION, false},
  {PA5, PB9, 0, KEY_RIGHT_SHIFT, false, KEY_NO_FUNCTION, false},
  {PA0, PB1, 0, KEY_END, false, 0xB5, false},
  {PB7, PB11, 0, KEY_LEFT_CTRL, false, KEY_NO_FUNCTION, false},
  {PB0, PB11, 0, KEY_FN, false, KEY_NO_FUNCTION, false},
  {PA7, PB11, 0, KEY_LEFT_GUI, false, KEY_NO_FUNCTION, false},
  {PA6, PB11, 0, KEY_LEFT_ALT, false, KEY_NO_FUNCTION, false},
  {PA3, PB11, 0, KEY_SPACE, false, KEY_NO_FUNCTION, false},
  {PA6, PB10, 0, KEY_RIGHT_ALT, false, KEY_NO_FUNCTION, false},
  {PA0, PB11, 0, KEY_RIGHT_GUI, false, KEY_NO_FUNCTION, false},
  {PB1, PB7, 0, KEY_RIGHT_CTRL, false, KEY_NO_FUNCTION, false},
  {PA5, PB4, 0, KEY_NO_FUNCTION, false, KEY_NO_FUNCTION, false}, // EURO - code unknown
  {PA10, PB1, 0, KEY_UP_ARROW, false, HIDConsumer::VOLUME_UP, true},
  {PA15, PB7, 0, KEY_NO_FUNCTION, false, KEY_NO_FUNCTION, false}, // USD - code unknown
  {PA9, PB11, 0, KEY_LEFT_ARROW, false, HIDConsumer::BRIGHTNESS_DOWN, true},
  {PA9, PB10, 0, KEY_DOWN_ARROW, false, HIDConsumer::VOLUME_DOWN, true},
  {PA9, PB1, 0, KEY_RIGHT_ARROW, false, HIDConsumer::BRIGHTNESS_UP, true},
};


int mappedPinsSize = sizeof(mappedPins) / sizeof(mappedPins[0]);

// Some needed variables
int fnButtonId = -1;
int last_i = -1;
int last_ii = -1;
int ledStatus;

int getFnButtonId() {
  for (int i = 0; i < mappedPinsSize; i++) {
    if (mappedPins[i].key == KEY_FN) return i;
  }
  return -1;
}

String getPinName(uint8_t pinNumber) {
  for (int i = 0; i < pinsSize; i++) {
    if (pins[i].number == pinNumber) {
      return pins[i].name;
    }
  }
  return String();
}

void setButtonState(int pin1, int pin2, int state) {

  int fnStatus = -1;
  if (fnButtonId >= 0) {
    fnStatus = mappedPins[fnButtonId].state;
  }

  for (int i = 0; i < mappedPinsSize; i++) {
    if (mappedPins[i].pin1 != pin1 || mappedPins[i].pin2 != pin2) continue;

    if (fnButtonId >= 0 && fnStatus > 0 && mappedPins[i].key_alt != KEY_NO_FUNCTION) {

      if (mappedPins[i].state != state && state > 0) {
        //CompositeSerial.println("PUSH");
        //CompositeSerial.println(mappedPins[i].key_alt);
        if (mappedPins[i].key_alt_consumer) {
          Consumer.press(mappedPins[i].key_alt);
        } else {
          Keyboard.press(mappedPins[i].key_alt);
        }
      }
    } else {
      if (mappedPins[i].state != state && state > 0) {
        //CompositeSerial.println("PUSH");
        //CompositeSerial.println(mappedPins[i].key);
        if (mappedPins[i].key_consumer) {
          Consumer.press(mappedPins[i].key);
        } else {
          Keyboard.press(mappedPins[i].key);
        }
      }
    }

    if (mappedPins[i].state != state && state <= 0) {
      //CompositeSerial.println("RELEASE");
      //CompositeSerial.println(mappedPins[i].key);
      //CompositeSerial.println(mappedPins[i].key_alt);
      if (mappedPins[i].key_consumer) {
        Consumer.release();
      } else {
        Keyboard.release(mappedPins[i].key);
      }
      if (mappedPins[i].key_alt_consumer) {
        Consumer.release();
      } else {
        Keyboard.release(mappedPins[i].key_alt);
      }
    }

    mappedPins[i].state = state;
  }
}

void setup() {
  HID.begin(CompositeSerial, reportDescription, sizeof(reportDescription));
  while (!USBComposite);
  Keyboard.begin(); // needed for LED support
  Keyboard.setAdjustForHostCapsLock(false); // this needs to be off, otherwise caps lock doesnt work properly for whatever reason

  pinMode(CAPSLOCK_LED, OUTPUT);
  digitalWrite(CAPSLOCK_LED, HIGH); // CAPS LED is sink mode => inverted
#ifdef EXTRA_STATUS_LEDS
  pinMode(NUMLOCK_LED, OUTPUT);
  pinMode(SCRLK_LED, OUTPUT);
#endif

  fnButtonId = getFnButtonId();

  for (int i = 0; i < pinsSize; i++) {
    pinMode(pins[i].number, INPUT_PULLUP);
  }
}

void loop() {
  ledStatus = Keyboard.getLEDs();

  //CompositeSerial.println(Keyboard.getLEDs());

  digitalWrite(CAPSLOCK_LED, !(ledStatus == 2 || ledStatus == 3 || ledStatus == 6 || ledStatus == 7 ));
#ifdef EXTRA_STATUS_LEDS
  digitalWrite(NUMLOCK_LED, ledStatus == 1 || ledStatus == 3 || ledStatus == 5 || ledStatus == 7);
  digitalWrite(SCRLK_LED, ledStatus == 4 || ledStatus == 5 || ledStatus == 6 || ledStatus == 7);
#endif

  for (int i = 0; i < pinsSize; i++) {

    pinMode(pins[i].number, OUTPUT);
    digitalWrite(pins[i].number, LOW);

    for (int ii = 0; ii < pinsSize; ii++) {

      if (i == ii)  continue;

      if (digitalRead(pins[ii].number) == LOW) {
        if (pins[i].number > pins[ii].number) continue;
        //if (last_i == pins[i].number && last_ii == pins[ii].number) continue;
        //last_i = pins[i].number;
        //last_ii = pins[ii].number;

#ifdef MAPPING_MODE
        if (last_i == pins[i].number && last_ii == pins[ii].number) continue;
        CompositeSerial.println("{" + pins[i].name + ", " + pins[ii].name + ", 0, KEY_NO_FUNCTION, false, KEY_NO_FUNCTION, false},");
        last_i = pins[i].number;
        last_ii = pins[ii].number;
#else
        setButtonState(pins[i].number, pins[ii].number, 1);
#endif


      } else {

#ifndef MAPPING_MODE
        setButtonState(pins[i].number, pins[ii].number, 0);
#endif

      }



    }

    pinMode(pins[i].number, INPUT_PULLUP);

  }

  /*
    for (int i = 0; i < sizeof(pins) / sizeof(int); i++) {
      pinMode(pins[i].number, OUTPUT);
      digitalWrite(pins[i].number, HIGH);
      //delay(1);

      for (int ii = 0; ii < sizeof(pins) / sizeof(int); ii++) {

        if (i == ii) continue;

        int keyCode = getValues(pins[i], pins[ii], 2);
        int keyState = getValues(pins[i], pins[ii], 3);
        if (digitalRead(pins[ii]) == HIGH) {

          if (last_i == pins[ii] && last_ii == pins[i]) continue;

          if (keyCode > 0 && keyState == 0) {
            Keyboard.press(keyCode);
            saveButtonState(pins[i], pins[ii], 1);
            digitalWrite(LED_BUILTIN, LOW);
            delay(10);
          }

          last_i = pins[i];
          last_ii = pins[ii];

        }
      }
      pinMode(pins[i], INPUT_PULLDOWN);
      //delay(1);
    }
  */
}
