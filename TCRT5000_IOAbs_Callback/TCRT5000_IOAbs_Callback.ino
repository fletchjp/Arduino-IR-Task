// TCRT5000_IOAbs_Callback
// IR detector circuit
// It has an LED to indicate that a detection has been made.
// (c) John Fletcher (john@bunbury28.plus.com)

// This version is adapted from an IoAbstraction example
// exampleDirect with taskmanager additions.
//
// https://www.thecoderscorner.com/products/arduino-libraries/io-abstraction/
//
// This compiles on UNO and also DUE.
// It also compiles on a PICO - I have not checked that the pin numbers are correct.

// 3rd party libraries
#include <Streaming.h>
#include <IoAbstraction.h>
#include <TaskManagerIO.h>

const byte VER_MAJ  = 1;
const byte VER_MIN  = 0;
const byte VER_DETAIL = 0;

void heading()
{
  Serial << endl << endl << __FILE__ << endl;
  Serial << F("Ver: ") << VER_MAJ << F(".") << VER_MIN << F(".") << VER_DETAIL;
  Serial << F(" compiled on ") << __DATE__ << F(" at ") << __TIME__ << F(" using compiler ") << __cplusplus << endl;
}

IoAbstractionRef arduinoPins = ioUsingArduino();

// The IR signal is pulled high and goes low when there is a detection.
const int Signal_Pin = 5;
const int IR_Pin = 6;
const int LED_Pin = 7;

int ir_signal = 0;
int previous_signal = -1;

// Check the signal and act if it has changed.
void checkIR()
{
  ir_signal = ioDeviceDigitalReadS(arduinoPins, Signal_Pin);
  Serial.println(ir_signal);
  if (ir_signal != previous_signal) {
    previous_signal = ir_signal;
    // Changes to save some code by passing the reverse value !ir_signal
    ioDeviceDigitalWrite(arduinoPins, LED_Pin, !ir_signal);
  }
}

void setup() {
  while(!Serial);
  Serial.begin(115200);
  heading();

	ioDevicePinMode(arduinoPins, Signal_Pin, INPUT_PULLUP);
  ioDevicePinMode(arduinoPins, IR_Pin, OUTPUT);
	ioDevicePinMode(arduinoPins, LED_Pin, OUTPUT);

  ioDeviceDigitalWrite(arduinoPins, IR_Pin, HIGH);
  ioDeviceDigitalWrite(arduinoPins, LED_Pin, LOW);

  // This is at the end of setup()
  taskManager.scheduleFixedRate(250, checkIR);
}

void loop() {
  taskManager.runLoop(); 
}
