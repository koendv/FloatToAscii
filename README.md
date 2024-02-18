# FloatToAscii
Fast and small IEEE754-single precision float to string conversion, suitable for embedded systems.

- small. about 2 to 3 kbyte.
- checks for buffer overflows
- fast. Does not use float or double. It's all integer math and table lookups.
- plain c, no dependencies
- c++ wrapper for Arduino

## use

FloatToAscii can be used as an Arduino library or as plain C code.

### arduino
Add the FloatToAscii library to your sketch using the library manager.

```
String &FloatToAscii(String &s, float f, int precision = 2);
```

- Converts a float _f_ to characters in the String _s_.
- _precision_ is the number of decimal places.
- If _precision_ is not given, prints two decimal places.
- If _precision_ is negative, prints all significant digits.
- Uses modify-in-place of String _s_ to avoid memory fragmentation.
- Returns String _s_ with the converted float.

Code:

```
float f = 6.02214076e23f;
String s;
Serial.print(FloatToAscii(s, f));
```

### plain C
Copy src/ftoa.h and src/ftoa.c to your project. There are no library dependencies.
```
uint32_t ftoa(char *s, size_t size, float f, int32_t precision);
```
The ftoa() function converts a floating point number _f_ into a character string _s_. ftoa() checks for buffer overflow.

 - _s_ is the address of a buffer. At most _size_ bytes will be written.
 - _f_ is a 32-bit single precision IEEE754 floating point number.
 - _precision_ is the the number of digits to appear after the decimal point.
 If _precision_ is negative, all digits are printed, and sscanf() of the printed output produces the original float.
- Upon  successful return, returns the number of characters printed (minus terminating 0).

Code:

```
float f = 6.02214076e23f;
char s[20];
int len = ftoa(s, sizeof(s), f, -1);
printf("%s", s);
```
ftoa() prints fixed point for numbers between 1000000 and 0.0001, scientific format otherwise.

## comparison

Various tests:

- A comparison of FloatToAscii() output and [Arduino print()](extras/doc/comparison-arduino.md).
- A comparison of FloatToAscii() output and  [linux printf()](extras/doc/comparison-linux.md).
- A comparison of ftoa() and [snprintf()](extras/doc/speed_comparison.md) speed and code size.

## credits

[Florian Loitsch](https://florian.loitsch.com/) proposed the [Grisu algorithm](dtoa-pldi2010.pdf) and wrote the [double-precision dtoa()](https://github.com/google/double-conversion) version.  I would like to thank Florian Loitsch for his helpful comments. Peter Barfuss converted dtoa() to 32-bit [single-precision ftoa()](https://github.com/bofh453/ftoa-fast).
