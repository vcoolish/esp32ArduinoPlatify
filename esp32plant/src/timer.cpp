#include "timer.h"

volatile uint32_t sharedCounter;
// int totalInterruptCounter;

hw_timer_t *timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR onTimer()
{
  portENTER_CRITICAL_ISR(&timerMux);
  if (sharedCounter > 0)
  {
    sharedCounter--;
    digitalWrite(2, true);
  }
  else
  {
    digitalWrite(2, false);
  }
  portEXIT_CRITICAL_ISR(&timerMux);
}

void timerInit()
{
  timer = timerBegin(0, 80, true);
  timerAttachInterrupt(timer, &onTimer, true);
  // 1000000 = alarm each second
  // 1000 = alarm each millisecond
  timerAlarmWrite(timer, 1000, true); 
  timerAlarmEnable(timer);
}

void timerLoop()
{
  // 	if (sharedCounter > 0)
  // 	{
  // 		portENTER_CRITICAL(&timerMux);
  // 		sharedCounter--;
  // 		portEXIT_CRITICAL(&timerMux);

  // 		totalInterruptCounter++;

  // 		Serial.print("An interrupt as occurred. Total number: ");
  // 		Serial.println(totalInterruptCounter);
  // 	}
}
