// TCRT5000 using Terry's Method
// I have now had this working.
// I now want to add an LED to indicate that a detection has been made.
// (c) John Fletcher (M6777)
//                                                          
// The IR signal is pulled high and goes low when there is a detection.
// This gives a digital signal instead of an analog one.
// I have not seen this documented. It is what Terry Bailey uses.
#define SIGNAL_PIN 5
#define IR_PIN 6
#define LED_PIN 13

int ir_signal = 0;
int previous_signal = -1;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(SIGNAL_PIN, INPUT_PULLUP);
  pinMode(IR_PIN, OUTPUT);                                                                                                                                        // with 330R
  pinMode(LED_PIN, OUTPUT); // with 220R

  // For now turn the IR LED on
  digitalWrite(IR_PIN, HIGH);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  ir_signal = digitalRead(SIGNAL_PIN);
  delayMicroseconds(500);
  // Only do this if signal has changed.
  if (ir_signal != previous_signal) {
    previous_signal = ir_signal;
    Serial.println(ir_signal);
    if (ir_signal == 0) {
      digitalWrite(LED_PIN, HIGH);
    } else {
      digitalWrite(LED_PIN, LOW);
    }
  }
}
