# FloatToAscii Speed Comparison
Fast and small IEEE754-single precision float to string conversion, suitable for embedded systems. Compare the speed and flash usage of ftoa() with speed and flash usage of the C library function snprintf().

## ftoa() speed

This is speed and size of the ftoa() function:

|core      |processor        |speed  |flash     |
| -------- | --------------- | ----- | -------- |
|RISCV     |ESP32-C3 160MHz  |5.6us  |2.0 kbyte |
|Cortex-M4 |STM32F411 100MHz |6.4us  |1.8 kbyte |
|Cortex-M3 |STM32F103 72MHz  |13.3us |2.0 kbyte |
|Cortex-M0 |STM32F072 48MHz  |50.9us |2.8 kbyte |

Speed given is the average time needed for a converting a single float to ascii. Compiled optimizing size.
The Arduino String version FloatToAscii() is about 4us slower than char* ftoa().

## snprintf() speed

Another way to convert float to string on Arduino uses snprintf(). Code:

```
  float f = 6.02214076e23f;
  char s[20];
  int len = snprintf(s, sizeof(s), "%g", f);
  Serial.print(s);
```
To use less flash, on stm32duino Newlib Nano does not have floating point support by default. On stm32duino, to use snprintf() to printf float and double, choose Tools -> C Runtime Library -> Newlib Nano + Float Printf. This increases size of the compiled code:

|core      |processor        |speed    |flash      |
| -------- | --------------- | ------- | --------- |
|RISCV     |ESP32-C3 160MHz  |46.4 us  |17.9 kbyte |
|Cortex-M4 |STM32F411 100MHz |65.0 us  |8.8 kbyte  |
|Cortex-M3 |STM32F103 72MHz  |113.8 us |7.9 kbyte  |
|Cortex-M0 |STM32F072 48MHz  |267.2 us |9.6 kbyte  |

These measurements indicate FloatToAscii() is faster and smaller than snprintf() when printing float.

On stm32duino, the size difference corresponds to the difference between choosing Newlib Nano with or without float printf() support.

On ESP32-C3 Arduino prints float and double using snprintf(). Printing a single float or double automatically links in snprintf(), and increases image size.