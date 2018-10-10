#include "LedsManager.h"
#include <Arduino.h>

/*
Leds

Enabled buttons indicators - 5 (SHIFT1: 0,1,2,3,4)
Mute						 (SHIFT1: 5)
Selected input  - 2;		 (SHIFT2 6,7)

*/

const int Shift1DataPin = 2;
const int Shift1LatchPin = 3;
const int Shift1ClockPin = 4;

void LedsManager::RefreshLeds(ConfigurationManager * configurationManager)
{
	//refreshLoopIndicators(configurationManager);
}
void writeValueToShift1(bool value) {
	digitalWrite(Shift1ClockPin, LOW);

	digitalWrite(Shift1DataPin, value);

	digitalWrite(Shift1ClockPin, HIGH);
}

void refreshLoopIndicators(ConfigurationManager * configurationManager) {
	digitalWrite(Shift1LatchPin, LOW);
	// switches
	writeValueToShift1(HIGH);
	writeValueToShift1(HIGH);
	writeValueToShift1(HIGH);
	writeValueToShift1(HIGH);
	writeValueToShift1(HIGH);
	// mute
	writeValueToShift1(configurationManager->currentConfiguration.mute);
	
	// inputs
	writeValueToShift1(!configurationManager->activeBank->activeInput);
	writeValueToShift1(configurationManager->activeBank->activeInput);

	digitalWrite(Shift1LatchPin, HIGH);
}


LedsManager::LedsManager()
{
	pinMode(Shift1ClockPin, OUTPUT);
	pinMode(Shift1DataPin, OUTPUT);
	pinMode(Shift1LatchPin, OUTPUT);
}


LedsManager::~LedsManager()
{
}
