# Reading and Printing float in stm32duino

These are two patches for stmduino. One allows printing floats with exponents; the other allows reading floats with exponents.

The code is not specific to stm32duino, the patches are. On other arduinos than stm32duino 2.7.1 you'll probably have to add the code by hand. The ```attic/``` directory contains already patched files.

## Reading

Stream.cpp.patch is a patch to /cores/arduino/Stream.cpp. The patch allows entering floats with exponent, like 123.456e12. Only one function is modified: `Stream::parseFloat()`

Code:

```
float f;
f = Serial.parseFloat();
```

A small [test program](parsefloat_test.ino) was compiled twice: once with a clean stm32duino, and once patched to accept numbers in scientific notation. Code size decreased after patching.

|mcu      |Arduino parseFloat() |patched parseFloat() |savings |
| ------- | ------------------- | ------------------- | ------ |
|F072CBTx |29064                |27436                |1628    |
|F103CBTx |25988                |24084                |1904    |
|F411CEUx |24132                |22236                |1896    |

Clean STM32duino. Optimize: Smallest (-Os). C runtime library: Newlib Nano (default). USB Support: CDC (generic Serial, supersedes U(S)ART. USART: enabled (generic Serial). USB speed: Low/Full speed.

To install:
```
  cd ~/.arduino15/packages/STMicroelectronics/hardware/stm32/2.7.1/cores/arduino
  cp Stream.cpp Stream.cpp.ORIG
  patch  < ~/FloatToAscii/extras/stm32duino/Stream.cpp.patch
```

## Printing

The standard arduino print() does not print the whole range of float.
Very large numbers are printed as "ovf", very small numbers are printed as 0.
This patch modifies Arduino print() to print the whole range of float. Only one function is modified: `Print::print(float n, int digits)`

- copy ftoa.h and ftoa.c to packages/STMicroelectronics/hardware/stm32/2.7.1/cores/arduino
- patch Print.cpp with Patch.cpp.patch. Directories may vary.
```
  cd ~/.arduino15/packages/STMicroelectronics/hardware/stm32/2.7.1/cores/arduino
  cp ~/FloatToAscii/src/ftoa-fast/ftoa.c .
  cp ~/FloatToAscii/src/ftoa-fast/ftoa.h .
  cp Print.cpp Print.cpp.ORIG
  patch  < ~/FloatToAscii/src/ftoa-fast/stm32duino/Print.cpp.patch
```

- With this patch, in an stm32duino sketch, print(f) will print the whole range of floats, from very small (1e-45) to very large (1e38). This works only for _float_, not _double_.
- to remove the patch:
```
  cd ~/.arduino15/packages/STMicroelectronics/hardware/stm32/2.7.1/cores/arduino
  cp Print.cpp.ORIG Print.cpp
  rm ftoa.h ftoa.c
```

- run sample sketch printfloat.ino before and after to see the difference.

Output before and after modifying Print.cpp:

```
 value             before        after        
 ----------------  ------------  ----------- 
 FLT_MAX           ovf           3.4028e+38   
 -FLT_MAX          ovf           -3.4028e+38  
 FLT_MIN           0.0000        1.1755e-38   
 -FLT_MIN          -0.0000       -1.1755e-38  
 HUGE_VALF         inf           inf          
 INFINITY          inf           inf          
 NAN               nan           nan          
 0x1.fffffep-1f    1.0000        1.0000       
 0x1p-128f         0.0000        2.9387e-39   
 0x0.fffffep-126f  0.0000        1.1755e-38   
 0x0.000002p-126f  0.0000        1.4013e-45   
 0.0f              0.0000        0.0000       
 0.5f              0.5000        0.5000       
 1.0f              1.0000        1.0000       
 -0.0f             0.0000        0.0000       
 -0.5f             -0.5000       -0.5000      
 -1.0f             -1.0000       -1.0000      
 1234567.8f        1234567.7500  1.2346e+06   
 123456.78f        123456.7812   123456.7800  
 12345.678f        12345.6777    12345.6780   
 1234.5678f        1234.5677     1234.5678    
 123.45678f        123.4568      123.4568     
 12.345678f        12.3457       12.3457      
 1.2345678f        1.2346        1.2346       
 0.12345678f       0.1235        0.1235       
 0.012345678f      0.0123        0.0123       
 0.0012345678f     0.0012        0.0012       
 0.00012345678f    0.0001        0.0001       
 0.000012345678f   0.0000        1.2346e-05   
 100000.0f         100000.0000   100000.0000  
 10000.0f          10000.0000    10000.0000   
 1000.0f           1000.0000     1000.0000    
 100.0f            100.0000      100.0000     
 10.0f             10.0000       10.0000      
 99.99999e9f       ovf           1.0000e+11   
 99.99999f         100.0000      100.0000     
 9.999999f         10.0000       10.0000      
 0.9999999f        1.0000        1.0000       
 0.09999999f       0.1000        0.1000       
 3.1415926535f     3.1416        3.1416       
 6.02214076e23f    ovf           6.0221e+23   
 6.62607015e-34f   0.0000        6.6261e-34   
```

## Code size

Code size of  [test program](parsefloat_test.ino) on a clean stm32duino, compared with code size on a stm32duino with patched print() and parseFloat():

|mcu      |clean |patched |savings |
| ------- | ---- | ------ | ------ |
|F072CBTx |29064 |26988   |2076    |
|F103CBTx |25988 |25168   |820     |
|F411CEUx |24132 |23784   |348     |

This means it's possible to add reading and printing numbers in scientific notation to Arduino, and still save a little bit of flash.
