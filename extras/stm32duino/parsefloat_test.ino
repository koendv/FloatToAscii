void setup() {
  Serial.begin(115200);
}

void loop() {
  float f;
  while (!Serial.available())
    ;
  f = Serial.parseFloat();
  Serial.println(f);
}
