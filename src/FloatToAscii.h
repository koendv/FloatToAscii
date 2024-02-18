#ifndef FLOAT_TO_ASCII_H
#define FLOAT_TO_ASCII_H
#include <Arduino.h>

/*!
  @brief    Converts a float f to characters in the String s.
  @param    s String to store result
  @param    f float to be converted
  @param    precision is the number of decimal places. If not given, defaults to two decimal places. If negative, prints all significant digits.
  @returns  String with the converted float.
  @note     Uses modify-in-place to avoid memory fragmentation.
 */
String &FloatToAscii(String &s, float f, int precision = 2);

#endif
