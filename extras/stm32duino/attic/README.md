This directory contains stm32duino files from `cores/arduino` before and after patching.

file|description
--|--
Print.cpp | with `Print::print(float n, int digits)` patched to print numbers in decimal and scientific notation
Print.cpp.ORIG | original stm32duino file
Stream.cpp | with `Stream::parseFloat()` patched to read numbers in decimal and scientific notation
Stream.cpp.ORIG | original stm32duino file
powers.c | test program to print powers of ten. Notice accuracy decreases for subnormal numbers.
