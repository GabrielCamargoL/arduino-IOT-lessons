#define PLUV 5
int count = 0;

void contapravaler(){
    count = count + 1;
    Serial.print("Pulsou ");
    Serial.println(count);
    unsigned long i = millis();
    while (i + 200) > millis());
}

void IRAM_ATTR countPluv() {
    noInterrupts();
    contapravaler();
    interrupts();
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(PLUV, INPUT);

  attachInterrupt(digitalPinToInterrupt(PLUV), countPluv, FALLING);
}

void loop() {
  /*
  if (digitalRead(PLUV) == LOW){
    count = count + 1;
    Serial.print("Pulsou ");
    Serial.println(count);
    delay(100);
  }
  */
 delay(20);
}
