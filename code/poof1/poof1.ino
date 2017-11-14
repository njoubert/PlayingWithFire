void setup() {
  // put your setup code here, to run once:
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

void poof(int which, int dur) {
  digitalWrite(which, HIGH);
  delay(dur);
  digitalWrite(which, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  poof(9, 1000);
  delay(50);

  poof(10, 1000);
  delay(50);

  poof(11, 1000);
  delay(50);
  
  poof(10, 500);
  delay(100);
}
