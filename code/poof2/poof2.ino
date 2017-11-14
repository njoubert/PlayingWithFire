/*
 * 
 * FIRECONTROL2000
 * 
 * IDEAS:
 * - state machine for record, pause, play mode
 * - check knob value every time, speed up or slow down.
 * - always shoot fireballs when button is pressed regardless of mode
 * - start-stop record dumps you into playback
 * - need "fancy" compressed data structure for recording sequence - store (event, time).
 * - 
 * 
 * 
 * 
 */
const int pin_button_y1 = 2;
const int pin_button_y2 = 3;
const int pin_button_y3 = 4;

const int pin_button_r = 5;
const int pin_button_g = 6;
const int pin_button_b = 7;

const int pin_knob = 0;

const int pin_fire1 = 11;
const int pin_fire2 = 10;
const int pin_fire3 = 9;



void setup() {
  // put your setup code here, to run once:
  pinMode(pin_button_y1, INPUT_PULLUP);
  pinMode(pin_button_y2, INPUT_PULLUP);
  pinMode(pin_button_y3, INPUT_PULLUP);
  pinMode(pin_button_r, INPUT_PULLUP);
  pinMode(pin_button_g, INPUT_PULLUP);
  pinMode(pin_button_b, INPUT_PULLUP);

  pinMode(pin_fire1, OUTPUT);
  pinMode(pin_fire2, OUTPUT);
  pinMode(pin_fire3, OUTPUT);

}



void loop() {
  int val = analogRead(pin_knob);
  if (digitalRead(pin_button_y1) == LOW) {
    digitalWrite(pin_fire1, HIGH);
    delay(val);
    digitalWrite(pin_fire1, LOW);
  }

  if (digitalRead(pin_button_y2) == LOW) {
    digitalWrite(pin_fire2, HIGH);
    delay(val);
    digitalWrite(pin_fire2, LOW);
  }

  if (digitalRead(pin_button_y3) == LOW) {
    digitalWrite(pin_fire3, HIGH);
    delay(val);
    digitalWrite(pin_fire3, LOW);
  }


  if (digitalRead(pin_button_r) == LOW) {

    digitalWrite(pin_fire3, HIGH);
    delay(val);
    digitalWrite(pin_fire3, LOW);

    delay(val);

    digitalWrite(pin_fire2, HIGH);
    delay(val);
    digitalWrite(pin_fire2, LOW);

    delay(val);
    
    digitalWrite(pin_fire1, HIGH);
    delay(val);
    digitalWrite(pin_fire1, LOW);

    delay(val);
  
    digitalWrite(pin_fire2, HIGH);
    delay(val);
    digitalWrite(pin_fire2, LOW);
  
  }


}
