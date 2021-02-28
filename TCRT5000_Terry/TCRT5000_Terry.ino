// TCRT5000 using Terry Bailey's Method
// I have now had this working.
// John Fletcher (M6777)
//
// The signal is pulled high and goes low when there is a signal.
#define SIGNAL_PIN 5
#define LED_PIN 6

int ir_signal = 0;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(SIGNAL_PIN,INPUT_PULLUP);
  pinMode(LED_PIN,OUTPUT);
  // For now turn the LED on
  digitalWrite(LED_PIN,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  ir_signal = digitalRead(SIGNAL_PIN);
  Serial.println(ir_signal);
  delayMicroseconds(500);
 
}
