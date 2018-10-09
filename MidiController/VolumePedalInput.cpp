#include "VolumePedalINput.h"
#include <Arduino.h>

int _volumePedalPin = A0;

// Calibrated values
short _maxNormalizedValue = 127;

Configuration *_currentConfiguration;

unsigned short normalize(int value) {
	//Serial.println("Value:");
	Serial.println(value);
	float step = (float)_maxNormalizedValue / (float)(_currentConfiguration->maxVolumePedalPosition 
		- _currentConfiguration->minVolumePedalPosition);
	return (value - _currentConfiguration->minVolumePedalPosition) * step;
}

int VolumePedalInput::readVolumePedalValue() {
	return analogRead(_volumePedalPin);
}

void VolumePedalInput::configure(ConfigurationManager configurationManager)
{
	_currentConfiguration = &configurationManager.currentConfiguration;
}

short VolumePedalInput::getNormalizedValue()
{
	return normalize(readVolumePedalValue());
}

void VolumePedalInput::setMaxValueFromCurrentPosition()
{
	_currentConfiguration->maxVolumePedalPosition = readVolumePedalValue();
}

void VolumePedalInput::setMinValueFromCurrentPosition()
{
	_currentConfiguration->minVolumePedalPosition = readVolumePedalValue();
}

VolumePedalInput::VolumePedalInput()
{
}


VolumePedalInput::~VolumePedalInput()
{
}
