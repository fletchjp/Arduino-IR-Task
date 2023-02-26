// TCRT5000 using Terry Bailey's Method
// I have now had this working.
// John Fletcher (M6777)
//
// 3rd party libraries
#include <Streaming.h>

const byte VER_MAJ  = 1;
const byte VER_MIN  = 0;
const byte VER_DETAIL = 0;

void heading()
{
  Serial << endl << endl << __FILE__ << endl;
  Serial << F("Ver: ") << VER_MAJ << F(".") << VER_MIN << F(".") << VER_DETAIL;
  Serial << F(" compiled on ") << __DATE__ << F(" at ") << __TIME__ << F(" using compiler ") << __cplusplus << endl;
}

// The signal is pulled high and goes low when there is a signal.
#define SIGNAL_PIN 5
#define LED_PIN 6

int ir_signal = 0;

void setup() {
  while(!Serial);
  Serial.begin(115200);
  heading();
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
