/// @file TCRT5000_IOAbs_Cb3.ino
/// @brief TCRT5000_IOAbs_Cb3 IR detector circuit code 
///
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
  while(!Serial);
  Serial.begin (115200);
  heading();

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
