//frt_Read_and_Blink_stop.ino
// This is an example of the use of the frt library to wrap Arduino_FreeRTOS

#include <frt.h>

namespace
{
	// An anonymous namespace tells the linker that this code is only
	// referenced in this very compilation unit. That's good for larger
	// projects but not necessary for this sketch.

	// Define the blink task and implement run().
	// - final is optional but good practice
	// - run() must be public
	// - sleeping with remainder is optional
	// - inlining run() is optional
	class BlinkTask final :
		public frt::Task<BlinkTask>
	{
	public:
		bool run()
		{
			digitalWrite(LED_BUILTIN, true);
			msleep(500, remainder);
			digitalWrite(LED_BUILTIN, false);
			//msleep(500, remainder);

			return false;
		}

	private:
		unsigned int remainder = 0;
	};

	// Create the static BlinkTask instance
	BlinkTask blink_task;

	// Define the analog read task and implement run().
	// - 84 is the stack size in bytes
	class SerialReadTask final :
		public frt::Task<SerialReadTask>
	{
	public:
		bool run()
		{
      if (Serial.available())
      {
        char c = Serial.read();

        switch (c) {
            
            case 'A':
              blink_task.start(2);
              Serial.println("starting blink_task");
              break;

            default:              
              //Serial.print(c);
              break;
        }
      }

			msleep(100, remainder);
      Serial.print(F("Blink task "));
      Serial.print(blink_task.getUsedStackSize());
      Serial.println(F(" bytes of stack this time."));
			return true;
		}

	private:
		unsigned int remainder = 0;
	};

	// Create the static AnalogReadTask instance
	SerialReadTask serial_read_task;

}

void setup()
{
	pinMode(LED_BUILTIN, OUTPUT);

	Serial.begin(115200);

	while (!Serial);

	// Start the blink task with priority 2
	//blink_task.start(2);
	// Start the analog read task with higher priority 1
	serial_read_task.start(1);
}

// This is called by the idle task (at the lowest priority 0)
void loop()
{
	//static bool stopped = false;

	// Stop analog read task after 5s
  /*
	if (!stopped && millis() > 5000) {
		// Get the stack size used this time. This varies from run to
		// run due to interrupts being served while the analog read task
		// was running. Don't be too conservative!
		Serial.print(F("AnalogReadTask used "));
		Serial.print(blink_read_task.getUsedStackSize());
		Serial.println(F(" bytes of stack this time."));

		Serial.println(F("Stopping"));
		analog_read_task.stopFromIdleTask();
		Serial.println(F("Stopped"));
		stopped = true;
	}
  */
}
