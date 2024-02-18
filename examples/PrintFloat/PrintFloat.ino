/*
 Prints numbers with and without FloatToPrint()
 */

#include <Arduino.h>
#include <cfloat>
#include <FloatToAscii.h>

/* uncomment for output on RTT */
#if 0
#include <RTTStream.h>
#undef Serial
RTTStream Serial;
#endif

static float g[] = {
  FLT_MAX,
  -FLT_MAX,
  FLT_MIN,
  -FLT_MIN,
  HUGE_VALF,
  INFINITY,
  NAN,
  0x1.fffffep-1f,
  0x1p-128f,
  0x0.fffffep-126f,
  0x0.000002p-126f,
  0.0f,
  0.5f,
  1.0f,
  -0.0f,
  -0.5f,
  -1.0f,
  /* decimal notation */
  1234567.8f,
  123456.78f,
  12345.678f,
  1234.5678f,
  123.45678f,
  12.345678f,
  1.2345678f,
  0.12345678f,
  /* leading zeroes */
  0.012345678f,
  0.0012345678f,
  0.00012345678f,
  0.000012345678f,
  /* trailing zeroes */
  100000.0f,
  10000.0f,
  1000.0f,
  100.0f,
  10.0f,
  /* rounding */
  99.99999e9f,
  99.99999f,
  9.999999f,
  0.9999999f,
  0.09999999f,
  /* common numbers */
  3.1415926535f,
  6.02214076e23f,
  6.62607015e-34f,
};
String s;

/* print in two columns, on the left with FloatToAscii, on the right without */
void printTwice(float f) {
  int len = Serial.print(FloatToAscii(s, f, -1));
  for (int i = 0; i < 20 - len; i++)
    Serial.print(" ");
  Serial.println(f, 4);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("FloatToAscii()      Arduino print()");
  for (int i = 0; i < sizeof(g) / sizeof(g[0]); i++) {
    printTwice(g[i]);
  }
  Serial.setTimeout(2500);
  Serial.println("enter float");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("> ");
  while (!Serial.available())
    ;
  float f = Serial.parseFloat();
  Serial.println();
  printTwice(f);
}
