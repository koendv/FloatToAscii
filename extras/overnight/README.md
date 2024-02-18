Linux overnight test. Compare output of ftoa() with output of printf().

Checks that after conversion from float to string, calling sscanf() on the string produces the original float.

Numbers that fail the test are printed.

Prints one dot every 10,000,000 floats tested.

This program does not stop, but needs to be halted manually with a ctrl-c.

```
mkdir build
cd build
cmake ..
make
./test
```

