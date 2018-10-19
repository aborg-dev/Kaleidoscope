/* -*- mode: c++ -*-
 * Kaleidoscope-EEPROM-Settings -- Basic EEPROM settings plugin for Kaleidoscope.
 * Copyright (C) 2017  Keyboard.io, Inc
 *
 * This program is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Originally generated by pycrc v0.9, https://pycrc.org
 *
 * using the configuration:
 *    Width         = 16
 *    Poly          = 0x8005
 *    Xor_In        = 0x0000
 *    ReflectIn     = True
 *    Xor_Out       = 0x0000
 *    ReflectOut    = True
 *    Algorithm     = bit-by-bit-fast
 */

#include "crc.h"

void
CRC_::reflect(uint8_t len) {
  uint8_t i;
  uint16_t newCRC;

  newCRC = crc & 0x01;
  for (i = 1; i < len; i++) {
    crc >>= 1;
    newCRC = (newCRC << 1) | (crc & 0x01);
  }

  crc = newCRC;
}

void
CRC_::update(const void *data, uint8_t len) {
  const uint8_t *d = (const uint8_t *)data;
  uint8_t i;
  bool bit;
  uint8_t c;

  while (len--) {
    c = *d++;
    for (i = 0x01; i & 0xff; i <<= 1) {
      bit = crc & 0x8000;
      if (c & i) {
        bit = !bit;
      }
      crc <<= 1;
      if (bit) {
        crc ^= 0x8005;
      }
    }
    crc &= 0xffff;
  }
  crc &= 0xffff;
}

CRC_ CRC;