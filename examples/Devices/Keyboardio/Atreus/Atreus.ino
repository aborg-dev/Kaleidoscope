/* -*- mode: c++ -*-
 * Atreus -- Chrysalis-enabled Sketch for the Keyboardio Atreus
 * Copyright (C) 2018-2022  Keyboard.io, Inc
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built on " __DATE__ " at " __TIME__
#endif

#include "Kaleidoscope.h"
#include "Kaleidoscope-EEPROM-Settings.h"
#include "Kaleidoscope-EEPROM-Keymap.h"
#include "Kaleidoscope-Escape-OneShot.h"
#include "Kaleidoscope-FirmwareVersion.h"
#include "Kaleidoscope-FocusSerial.h"
#include "Kaleidoscope-Macros.h"
#include "Kaleidoscope-MouseKeys.h"
#include "Kaleidoscope-OneShot.h"
#include "Kaleidoscope-Qukeys.h"
#include "Kaleidoscope-SpaceCadet.h"
#include "Kaleidoscope-DynamicMacros.h"
#include "Kaleidoscope-LayerNames.h"
#include "Kaleidoscope-MagicCombo.h"

enum {
  ESCAPE_COMBO
};

void escapeCombo(uint8_t combo_index) {
  Macros.tap(Key_Escape);
}

USE_MAGIC_COMBOS([ESCAPE_COMBO] = {.action = escapeCombo, .keys = {R1C8, R1C9}});

#define MO(n) ShiftToLayer(n)
#define TG(n) LockLayer(n)

enum {
  MACRO_QWERTY,
  MACRO_VERSION_INFO
};

#define Key_Exclamation LSHIFT(Key_1)
#define Key_At          LSHIFT(Key_2)
#define Key_Hash        LSHIFT(Key_3)
#define Key_Dollar      LSHIFT(Key_4)
#define Key_Percent     LSHIFT(Key_5)
#define Key_Caret       LSHIFT(Key_6)
#define Key_And         LSHIFT(Key_7)
#define Key_Star        LSHIFT(Key_8)
#define Key_Plus        LSHIFT(Key_Equals)
#define Key_Underscore  LSHIFT(Key_Minus)
#define Key_Colon       LSHIFT(Key_Semicolon)
#define Key_LangToggle  LSHIFT(Key_RightAlt)

enum {
  QWERTY,
  NUM,
  NAV,
  DESKTOP
};

// clang-format off
KEYMAPS(
  [QWERTY] = KEYMAP_STACKED
  (
       Key_Q   ,Key_W   ,Key_E       ,Key_R         ,Key_T
      ,Key_A   ,Key_S   ,Key_D       ,CTL_T(F)      ,Key_G
      ,Key_Z   ,Key_X   ,Key_C       ,Key_V         ,Key_B              ,Key_Backtick
      ,___     ,___     ,Key_LeftAlt ,Key_Escape    ,LT(NUM, Backspace) ,Key_Tab

                       ,Key_Y        ,Key_U          ,Key_I          ,Key_O      ,Key_P
                       ,Key_H        ,CTL_T(J)       ,Key_K          ,Key_L      ,Key_Semicolon
      ,Key_Backslash   ,Key_N        ,Key_M          ,Key_Comma      ,Key_Period ,Key_Slash
      ,LT(NAV, Enter)  ,SFT_T(Space) ,Key_LangToggle ,___            ,Key_Quote  ,___
  ),

  [NUM] = KEYMAP_STACKED
  (
       Key_Caret       ,Key_At                  ,Key_Hash         ,Key_Dollar         ,Key_Percent
      ,Key_Exclamation ,Key_LeftCurlyBracket    ,Key_LeftBracket  ,Key_LeftParen      ,Key_Underscore
      ,Key_And         ,Key_RightCurlyBracket   ,Key_RightBracket ,Key_RightParen     ,Key_Colon      ,___
      ,___             ,___                     ,___              ,___                ,XXX            ,___
      
                               ,Key_Star     ,Key_7    ,Key_8   ,Key_9  ,Key_Plus
                               ,Key_Equals   ,CTL_T(4) ,Key_5   ,Key_6  ,Key_Minus
      ,___                     ,Key_0        ,Key_1    ,Key_2   ,Key_3  ,Key_Quote
      ,Key_Enter               ,SFT_T(Space) ,___      ,___     ,___    ,___
   ),

   [NAV] = KEYMAP_STACKED
   (
       ___            ,___                 ,Key_mouseUp   ,___        ,___
      ,___            ,Key_mouseL            ,Key_mouseDn ,Key_mouseR ,___
      ,M(MACRO_VERSION_INFO) ,Consumer_VolumeIncrement ,XXX           ,XXX            ,___ ,___
      ,___                   ,Consumer_VolumeDecrement ,___           ,Key_mouseBtnM, Key_mouseBtnL, Key_mouseBtnR

                ,Key_Home   ,Key_PageDown    ,Key_PageUp          ,Key_End         ,___
                ,Key_LeftArrow ,Key_DownArrow              ,Key_UpArrow          ,Key_RightArrow ,___
      ,___      ,XXX           ,___              ,___          ,___         ,___
      ,___      ,___           ,MoveToLayer(QWERTY) ,Key_PrintScreen ,Key_ScrollLock ,Consumer_PlaySlashPause
   ),

   [DESKTOP] = KEYMAP_STACKED
   (
        Key_Q   ,Key_W   ,Key_E       ,Key_R         ,Key_T
       ,Key_1   ,Key_2   ,Key_3       ,Key_4         ,Key_5
       ,Key_Z   ,Key_X   ,Key_C       ,Key_V         ,Key_B           ,Key_Backtick
       ,Key_Esc ,Key_Tab ,Key_LeftAlt ,SFT_T(Esc)    ,Key_Backspace   ,CTL_T(Enter)
 
                        ,Key_Y        ,Key_U      ,Key_I     ,Key_O      ,Key_P
                        ,Key_H        ,Key_J      ,Key_K     ,Key_L      ,Key_Semicolon
       ,Key_Backslash   ,Key_N        ,Key_M      ,Key_Comma ,Key_Period ,Key_Slash
       ,___             ,SFT_T(Space) ,MO(NUM)    ,Key_Minus ,Key_Quote  ,Key_Enter
   )
)
// clang-format on

KALEIDOSCOPE_INIT_PLUGINS(
  // ----------------------------------------------------------------------
  // Chrysalis plugins

  // The EEPROMSettings & EEPROMKeymap plugins make it possible to have an
  // editable keymap in EEPROM.
  EEPROMSettings,
  EEPROMKeymap,

  // Focus allows bi-directional communication with the host, and is the
  // interface through which the keymap in EEPROM can be edited.
  Focus,

  // FocusSettingsCommand adds a few Focus commands, intended to aid in
  // changing some settings of the keyboard, such as the default layer (via the
  // `settings.defaultLayer` command)
  FocusSettingsCommand,

  // FocusEEPROMCommand adds a set of Focus commands, which are very helpful in
  // both debugging, and in backing up one's EEPROM contents.
  FocusEEPROMCommand,

  // The FirmwareVersion plugin lets Chrysalis query the version of the firmware
  // programmatically.
  FirmwareVersion,

  // The LayerNames plugin allows Chrysalis to display - and edit - custom layer
  // names, to be shown instead of the default indexes.
  LayerNames,

  // ----------------------------------------------------------------------
  // Keystroke-handling plugins

  // The Qukeys plugin enables the "Secondary action" functionality in
  // Chrysalis. Keys with secondary actions will have their primary action
  // performed when tapped, but the secondary action when held.
  Qukeys,

  // SpaceCadet can turn your shifts into parens on tap, while keeping them as
  // Shifts when held. SpaceCadetConfig lets Chrysalis configure some aspects of
  // the plugin.
  SpaceCadet,
  SpaceCadetConfig,

  // Enables the "Sticky" behavior for modifiers, and the "Layer shift when
  // held" functionality for layer keys.
  OneShot,
  OneShotConfig,
  EscapeOneShot,
  EscapeOneShotConfig,

  // The macros plugin adds support for macros
  Macros,

  // Enables dynamic, Chrysalis-editable macros.
  DynamicMacros,

  // The MouseKeys plugin lets you add keys to your keymap which move the mouse.
  MouseKeys,
  MouseKeysConfig,

  // The MagicCombo plugin lets you use key combinations to trigger custom
  // actions - a bit like Macros, but triggered by pressing multiple keys at the
  // same time.
  MagicCombo //,

  // Enables the GeminiPR Stenography protocol. Unused by default, but with the
  // plugin enabled, it becomes configurable - and then usable - via Chrysalis.
  // GeminiPR,
);

const macro_t *macroAction(uint8_t macro_id, KeyEvent &event) {
  if (keyToggledOn(event.state)) {
    switch (macro_id) {
    case MACRO_QWERTY:
      // This macro is currently unused, but is kept around for compatibility
      // reasons. We used to use it in place of `MoveToLayer(QWERTY)`, but no
      // longer do. We keep it so that if someone still has the old layout with
      // the macro in EEPROM, it will keep working after a firmware update.
      Layer.move(QWERTY);
      break;
    case MACRO_VERSION_INFO:
      Macros.type(PSTR("Keyboardio Atreus - Kaleidoscope "));
      Macros.type(PSTR(BUILD_INFORMATION));
      break;
    default:
      break;
    }
  }
  return MACRO_NONE;
}

void setup() {
  QUKEYS(
    kaleidoscope::plugin::Qukey(0, KeyAddr(3, 5), ML(LeftGui, DESKTOP)),
  )
  Qukeys.setOverlapThreshold(60);

  Kaleidoscope.setup();
  EEPROMKeymap.setup(9);

  DynamicMacros.reserve_storage(48);

  LayerNames.reserve_storage(63);

  Layer.move(EEPROMSettings.default_layer());

  // To avoid any surprises, SpaceCadet is turned off by default. However, it
  // can be permanently enabled via Chrysalis, so we should only disable it if
  // no configuration exists.
  SpaceCadetConfig.disableSpaceCadetIfUnconfigured();
}

void loop() {
  Kaleidoscope.loop();
}
