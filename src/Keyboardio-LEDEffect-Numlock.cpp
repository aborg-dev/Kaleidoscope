#include "Keyboardio-LEDEffect-Numlock.h"
#include "LEDUtils.h"
#include "KeyboardioFirmware.h"
#include "layers.h"

uint8_t NumLock_::previousLEDMode;
uint8_t NumLock_::us;
bool NumLock_::isActive;
byte NumLock_::row = 255, NumLock_::col = 255;

NumLock_::NumLock_ (void) {
}

void
NumLock_::begin (void) {
    us = LEDControl.mode_add (this);
}

void
NumLock_::init (void) {
    if (!isActive) {
        LEDControl.next_mode();
    }
}

void
NumLock_::update (void) {
    for (uint8_t r = 0; r < ROWS; r++) {
        for (uint8_t c = 0; c < COLS; c++) {
            Key k = Layer.lookup (r, c);

            if (k.raw < Key_NumLock.raw || k.raw > Key_KeypadDot.raw)
                continue;

            LEDControl.led_set_crgb_at(r, c, {255, 0, 0});
        }
    }

    if (row > ROWS || col > COLS)
        return;

    cRGB color = breath_compute();
    LEDControl.led_set_crgb_at (row, col, color);
}

const macro_t *
NumLock_::toggle (byte row_, byte col_, uint8_t numPadLayer) {
    row = row_;
    col = col_;

    if (Layer.isOn (numPadLayer)) {
        isActive = false;
        LEDControl.set_mode (previousLEDMode);
        Layer.off (numPadLayer);
    } else {
        isActive = true;
        previousLEDMode = LEDControl.get_mode ();
        LEDControl.set_mode (us);
        Layer.on (numPadLayer);
    }

    return MACRO(T(NumLock), END);
}

NumLock_ NumLock;
