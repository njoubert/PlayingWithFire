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



 /*
  * 
  * 1. Get a stream of events.
  * 
  */
const int pin_button_r = 5;
const int pin_button_g = 6;
const int pin_button_b = 7;

const int pin_knob = 0;

unsigned int fire_output_pins[3] = {11, 10, 9};
unsigned int fire_button_pins[3]   = {2, 3, 4};
unsigned int fire_button_status[3] = {HIGH, HIGH, HIGH};

enum mode {REC, PLAY, PAUSE} mode = PAUSE; 

unsigned int seq_tick[100];
unsigned int seq_idx[100];
unsigned int seq_val[100];
unsigned int seq_i;

unsigned long millis_offset;
unsigned long last_tick;
unsigned long last_event_tick;

void setup() {

  
  Serial.begin(9600);
  while (!Serial) {
    ; //Wait for serial port to connect
  }
  Serial.print("FireControl2000 v2.0\n");

  last_tick = 0;
  last_event_tick = 0;
  millis_offset = 0;
  seq_i = 0;
  
  // put your setup code here, to run once:
  for (int i = 0; i < 3; i++) {
    pinMode(fire_button_pins[i], INPUT_PULLUP);
    pinMode(fire_output_pins[i], OUTPUT);
  }
  pinMode(pin_button_r, INPUT_PULLUP);
  pinMode(pin_button_g, INPUT_PULLUP);
  pinMode(pin_button_b, INPUT_PULLUP);


}

void all_off() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(fire_output_pins[i], LOW);
  }  
}
void reset() {
    all_off();
    for (int i = 0; i < 100; i++) {
      seq_tick[i] = 0;
      seq_idx[i]  = 0;
      seq_val[i]  = 0;
    }
    seq_i = 0;
    last_tick = millis();
    millis_offset = millis();

}
void emit_event(int button_idx, int value) {
  unsigned long current_tick = millis();
  unsigned long delta = current_tick - last_tick;
  last_tick = current_tick;

  if (button_idx < 3) {
    digitalWrite(fire_output_pins[button_idx], value);
  }
  
  Serial.print(button_idx);
  Serial.print(" ");
  Serial.print(value);
  Serial.print("\n");
  
  if (mode == REC) {
    seq_tick[seq_i] = delta;
    seq_idx[seq_i] = button_idx;
    seq_val[seq_i] = value;
    seq_i = (seq_i + 1) % 100;
  }

  
}

void loop() {

  // REC MODE BUTTON
  if (digitalRead(pin_button_r) == LOW) {
    mode = REC;
    Serial.println("Mode Changed to REC");
    reset();
  }
  // PLAY MODE BUTTON
  if (digitalRead(pin_button_g) == LOW) {
    if (mode == REC) {
      emit_event(4, 0);
    }
    mode = PLAY;
    Serial.println("Mode Changed to PLAY");
    seq_i = 0;
    last_tick = millis();
    millis_offset = millis();
    last_event_tick = 0;
  }

  // PAUSE MODE BUTTON
  if (digitalRead(pin_button_b) == LOW) {
    if (mode == REC) {
      emit_event(4, 0);
    }
    mode = PAUSE;
    all_off();
    Serial.println("Mode Changed to PAUSE");
  }
  
  
  // See if we can detect an event.
  // Events are DELTAS thus we need to compare
  for (char i = 0; i < 3; i++) {
    int val = digitalRead(fire_button_pins[i]);
    if (fire_button_status[i] != val) {
      fire_button_status[i] = val;
      
      //Flip, cause pullup resistor means OFF is HIGH
      if (val == LOW) { val = HIGH; } else { val = LOW; }
      
      emit_event(i, val);
    }
  }

  // PAUSE doesn't do anything.
  // REC is handled though EMIT
  // PLAY is handled here:
  
  if (mode == PLAY) {
    unsigned long current_tick = millis() - millis_offset;
    unsigned long delta = current_tick - last_event_tick;

    //trigger event
    if (seq_tick[seq_i] < delta) {
      if (seq_idx[seq_i] == 4) {
        seq_i = 0;
        millis_offset = millis();
        last_event_tick = 0;
      } else {
        emit_event(seq_idx[seq_i], seq_val[seq_i]);
        seq_i += 1;      
        last_event_tick = current_tick;
      }
    }
    
    // we keep going with deltas until we hit the next event, which we will emit
    // when we emit an event, we also update our counters so we reset last_event
    // 
    
    
    
    
  }


}
