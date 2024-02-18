#include <FloatToAscii.h>

String s;  // global variable to avoid memory fragmentation

void setup() {
  Serial.println("enter float");
  Serial.setTimeout(1500);
}

void loop() {
  // put your main code here, to run repeatedly:
  float f;
  Serial.print("> ");
  while (!Serial.available())
    ;
  f = Serial.parseFloat();
  Serial.println(FloatToAscii(s, f, -1));
}
