// TCRT5000 using FreeRTOS
// IR detector circuit
// It has an LED to indicate that a detection has been made.
// (c) John Fletcher (john@bunbury28.plus.com)

// This version is using FreeRTOS
// https://www.arduino.cc/reference/en/libraries/freertos/

#include <Arduino_FreeRTOS.h>

void TaskDigitalRead( void *pvParameters );

// The IR signal is pulled high and goes low when there is a detection.
const int Signal_Pin = 5;
const int IR_Pin = 6;
const int LED_Pin = 13;

int ir_signal = 0;
int previous_signal = -1;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(Signal_Pin, INPUT_PULLUP);
  pinMode(IR_Pin, OUTPUT);                                                                                                                                        // with 330R
  pinMode(LED_Pin, OUTPUT); // with 220R

  // For now turn the IR LED on
  digitalWrite(IR_Pin, HIGH);
  digitalWrite(LED_Pin, LOW);

  xTaskCreate(
    TaskDigitalRead
    ,  "DigitalRead"  // A name just for humans
    ,  128  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL );

}

void TaskDigitalRead( void *pvParameters __attribute__((unused)) )  // This is a Task.
{
 for (;;) // A Task shall never return or exit.
 {
  ir_signal = digitalRead(Signal_Pin);
  Serial.println(ir_signal);
  if (ir_signal != previous_signal) {
    previous_signal = ir_signal;
    // Changes to save some code.
    digitalWrite(LED_Pin, !ir_signal);
  }
  vTaskDelay(250 / portTICK_PERIOD_MS);  // one tick delay (15ms) in between reads for stability
 }
}

void loop() {
 
}
