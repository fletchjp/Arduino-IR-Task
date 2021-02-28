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


#include <IoAbstraction.h>
#include <TaskManagerIO.h>

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
  Serial.begin(9600);

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
