# FloatToAscii - ftoa-fast
Fast and small IEEE754-single precision float to string conversion, suitable for embedded systems.

- small. about 2 to 3 kbyte.
- checks for buffer overflows
- fast. Does not use float or double. It's all integer math and table lookups.
- plain c, no dependencies
- c++ wrapper for Arduino

## Use

The library can be used on Arduino and other os's, like Zephyr.

### Arduino
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

A comparison of FloatToAscii() output, [Arduino print()](extras/doc/comparison-arduino.md) and [linux printf()](extras/doc/comparison-linux.md).

Code:

```
float f = 6.02214076e23f;
String s;
Serial.print(FloatToAscii(s, f));
```

### Other OS
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

## measurements

This is speed and size of the ftoa() function:

|core      |processor        |speed  |flash     |
| -------- | --------------- | ----- | -------- |
|RISCV     |ESP32-C3 160MHz  |5.6us  |2.0 kbyte |
|Cortex-M4 |STM32F411 100MHz |6.4us  |1.8 kbyte |
|Cortex-M3 |STM32F103 72MHz  |13.3us |2.0 kbyte |
|Cortex-M0 |STM32F072 48MHz  |50.9us |2.8 kbyte |

Speed given is the average time needed for a converting a single float to ascii. Compiled optimizing size.
The Arduino String version FloatToAscii() is about 4us slower than char* ftoa().

## Comparison with snprintf()

Another way to convert float to string on Arduino uses snprintf(). Code:

```
  float f = 6.02214076e23f;
  char s[20];
  int len = snprintf(s, sizeof(s), "%g", f);
  Serial.print(s);
```
To use less flash, on stm32duino Newlib Nano does not have floating point support by default. On stm32duino, to use snprintf() to printf float and double, choose Tools -> C Runtime Library -> Newlib Nano + Float Printf. This is speed and size in kbyte of snprintf():

|core      |processor        |speed    |flash      |
| -------- | --------------- | ------- | --------- |
|RISCV     |ESP32-C3 160MHz  |46.4 us  |17.9 kbyte |
|Cortex-M4 |STM32F411 100MHz |65.0 us  |8.8 kbyte  |
|Cortex-M3 |STM32F103 72MHz  |113.8 us |7.9 kbyte  |
|Cortex-M0 |STM32F072 48MHz  |267.2 us |9.6 kbyte  |

On stm32duino, the size difference corresponds to the difference between choosing Newlib Nano with or without float printf() support.

On ESP32-C3 Arduino prints float and double using snprintf(). Printing a single float or double automatically links in snprintf(), and increases image size.

These measurements indicate FloatToAscii() is faster and smaller than snprintf(). But FloatToAscii only prints a single type - float - while snprintf() prints everything - including float and double - in a large variety of formats.

## stm32duino

Instead of adding a library to your sketch, you can also patch the system libraries.

These are two [patches for stmduino](extras/stm32duino). A patch for print() allows printing floats with exponents; a patch for parseFloat() allows reading floats with exponents.

The code is not specific to stm32duino, the patches are. On other arduinos than stm32duino you'll probably have to add the code by hand.

## testing

```extras/overnight``` checks that after conversion from float to string, calling sscanf() on the string produces the original float.

## credits

[Florian Loitsch](https://florian.loitsch.com/) proposed the [Grisu algorithm](dtoa-pldi2010.pdf) and wrote the [double-precision dtoa()](https://github.com/google/double-conversion) version.  I would like to thank Florian Loitsch for his helpful comments. Peter Barfuss converted dtoa() to 32-bit [single-precision ftoa()](https://github.com/bofh453/ftoa-fast).
