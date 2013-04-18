/**
 * debug.h
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright (C) Pim Vullers, Radboud University Nijmegen, July 2011.
 */

#ifndef __debug_H
#define __debug_H

#ifdef SIMULATOR

#include <stdio.h> // for printf()

#include "types.h"

/**
 * Print a value as debug output.
 *
 * @param label associated with the value in the output.
 * @param value to be printed.
 * @param length in bytes of the value.
 */
void debugValue(const char *label, const void *value,
    unsigned int length);

/**
 * Print an indexed value (from an array) as debug output.
 *
 * @param label associated with the value in the output.
 * @param array containing the value to be printed.
 * @param length in bytes of the values in the array.
 * @param index of the value in the array.
 */
void debugIndexedValue(const char *label, const void *array,
    unsigned int length, unsigned int index);

/**
 * Print the values (from an array) as debug output.
 *
 * @param label associated with the values in the output.
 * @param array containing the values to be printed.
 * @param length in bytes of the values in the array.
 * @param count number of values in the array.
 */
void debugValues(const char *label, const void *array,
    unsigned int length, unsigned int count);

/**
 * Print the (NULL-terminated) string as debug output.
 *
 * @param label associated with the string in the output.
 * @param value of the (NULL-terminated) string to be printed.
 */
#define debugString(label, value) \
  printf("[%s] %s\n", label, value)

/**
 * Print the integer as debug output.
 *
 * @param label associated with the integer in the output.
 * @param value of the integer to be printed.
 */
#define debugInteger(label, value) \
  printf("%s: %d\n", label, value)

/**
 * Print the pointer as debug output.
 *
 * @param label associated with the pointer in the output.
 * @param value of the pointer to be printed.
 */
#define debugPointer(label, value) \
  printf("%s: %p\n", label, value)

#else // SIMULATOR

/*
 * Strip the debug functionality when not building for the simulator.
 */
#define debugValue(label, value, length)
#define debugIndexedValue(label, value, length, index)
#define debugValues(label, value, length, count)
#define debugString(label, value)
#define debugInteger(label, value)
#define debugPointer(label, value)

#endif // SIMULATOR

/**
 * Print the message as debug output.
 *
 * @param value of the message to be printed.
 */
#define debugMessage(value) \
  debugString("MSG", value)

/**
 * Print the warning as debug output.
 *
 * @param value of the warning to be printed.
 */
#define debugWarning(value) \
  debugString("WRN", value)

/**
 * Print the error as debug output.
 *
 * @param value of the error to be printed.
 */
#define debugError(value) \
  debugString("ERR", value)

/**
 * Print the hash as debug output.
 *
 * @param label associated with the hash in the output.
 * @param value of the hash to be printed.
 */
#define debugHash(label, value) \
  debugValue(label, value, sizeof(Hash))

/**
 * Print the nonce as debug output.
 *
 * @param label associated with the nonce in the output.
 * @param value of the nonce to be printed.
 */
#define debugNonce(label, value) \
  debugValue(label, value, sizeof(Nonce))

/**
 * Print the number as debug output.
 *
 * @param label associated with the number in the output.
 * @param value of the number to be printed.
 */
#define debugNumber(label, value) \
  debugValue(label, value, sizeof(Number))

/**
 * Print an indexed number (from an array) as debug output.
 *
 * @param label associated with the number in the output.
 * @param array containing the number to be printed.
 * @param index of the number in the array.
 */
#define debugIndexedNumber(label, value, index) \
  debugIndexedValue(label, value, sizeof(Number), index)

/**
 * Print the hash value as debug output.
 *
 * @param label associated with the hash value in the output.
 * @param value of the hash to be printed.
 */
#define debugNumbers(label, value, count) \
  debugValues(label, value, sizeof(Number), count)

/**
 * Print an indexed CL message (from an array) as debug output.
 *
 * @param label associated with the CL message in the output.
 * @param array containing the CL message to be printed.
 * @param index of the CL message in the array.
 */
#define debugIndexedCLMessage(label, value, index) \
  debugIndexedValue(label, value, sizeof(CLMessage), index)

/**
 * Print the CL messages (from an array) as debug output.
 *
 * @param label associated with the CL messages in the output.
 * @param array containing the CL messages to be printed.
 * @param count number of CL messages in the array.
 */
#define debugCLMessages(label, value, count) \
  debugValues(label, value, sizeof(CLMessage), count)

#endif // __debug_H
