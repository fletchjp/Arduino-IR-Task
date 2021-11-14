// @file TCRT5000_IOAbs_Cb3
///
/// TCRT5000_IOAbs_Cb3
/// IR detector circuit
/// It has an LED to indicate that a detection has been made.
/// (c) John Fletcher (M6777)
///
/// This version is adapted from an IoAbstraction example
/// exampleDirect with taskmanager additions.
///
/// Extended to use a class for the executable task.
/// This makes it possible to have more than one detector.
///
/// https://www.thecoderscorner.com/products/arduino-libraries/io-abstraction/
///
/// This compiles on UNO and also DUE.

/// @section Program

#include <IoAbstraction.h>
#include <TaskManagerIO.h>

/// arduinoPins is using part of IoAbstraction
IoAbstractionRef arduinoPins = ioUsingArduino();

/// The IR signal is pulled high and goes low when there is a detection.
const int Signal_Pin = 5;
const int IR_Pin = 6;
const int LED_Pin = 7;

/// CheckIRpins implements checking on the pins.
class CheckIRpins : public Executable {
   private:
     int sig_pin;
     int led_pin;
     // These are now local to each instance.
     int ir_signal;
     int previous_signal;
   public:
     CheckIRpins (int s, int p) : sig_pin(s), led_pin(p) { previous_signal = -1;}
     void exec() override {
        ir_signal = ioDeviceDigitalReadS(arduinoPins, sig_pin);
        Serial.println(ir_signal);
        if (ir_signal != previous_signal) {
          previous_signal = ir_signal;
          ioDeviceDigitalWrite(arduinoPins, led_pin, !ir_signal);
        }
     }
};

/// Class instance - this could be used to check different sets of pins.
CheckIRpins checkThesePins(Signal_Pin, LED_Pin);

/// NOTE: I have made the instance declaration global which is what the documentation implies.
/// Examples did work with the declaration inside setup() which should have gone out of scope.
/// I can only assume that the memory location had not been overwritten.

/// Arduino setup routine runs once.
void setup() {
  Serial.begin(9600);

	ioDevicePinMode(arduinoPins, Signal_Pin, INPUT_PULLUP);
  ioDevicePinMode(arduinoPins, IR_Pin, OUTPUT);
	ioDevicePinMode(arduinoPins, LED_Pin, OUTPUT);

  ioDeviceDigitalWrite(arduinoPins, IR_Pin, HIGH);
  ioDeviceDigitalWrite(arduinoPins, LED_Pin, LOW);

  /// Class instance is scheduled - note the & before the name to indicate "address of"
  taskManager.scheduleFixedRate(250, &checkThesePins);
  ///This could be repeated with different instances to check different sets of pins.
}

/// Arduino loop() function has only to run the taskManage.runLoop()
void loop() {
  taskManager.runLoop();
}
