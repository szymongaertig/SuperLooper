#include "VolumePedalINput.h"
#include <Arduino.h>

int _volumePedalPin = A0;

// Calibrated values
int _minPositionValue = 0;
int _maxPositionValue = 0;

// Used for volume pedal resistance calculation
float _dividerResistorValue = 1000;
float _volumePedalResistanceValue = 0;
float _volumePedalResistanceBuffer = 0;
int _vIn = 1024;
int _vOut = 0;

short _maxNormalizedValue = 127;

short normalize(float value) {
	float step = (float)(_maxPositionValue - _minPositionValue) / (float)_maxNormalizedValue;
	return (value - _minPositionValue) * step;
}

float readVolumePedalValue() {
	int rawValue = analogRead(_volumePedalPin);
	_volumePedalResistanceBuffer = rawValue * _vIn;

	_vOut = (_volumePedalResistanceBuffer) / 1024.0;
	_volumePedalResistanceBuffer = (_vIn / _vOut) - 1;
	_volumePedalResistanceValue = _dividerResistorValue * _volumePedalResistanceBuffer;
	return _volumePedalResistanceValue;
}

void VolumePedalInput::Configure(ConfigurationManager configurationManager)
{
	Configuration *currentConfiguration = &configurationManager.CurrentConfiguration;

	if (currentConfiguration->IsVolumePedalCalibrated && currentConfiguration->IsVolumePedalEnabled) {
		_minPositionValue = currentConfiguration->MinVolumePedalPosition;
		_maxPositionValue = currentConfiguration->MaxVolumePedalPosition;
	}
}

short VolumePedalInput::getNormalizedValue()
{
	return normalize(readVolumePedalValue());
}

void VolumePedalInput::setMaxValueFromCurrentPosition()
{
	_maxPositionValue = readVolumePedalValue();
}

void VolumePedalInput::setMinValueFromCurrentPosition()
{
	_minPositionValue = readVolumePedalValue();
}

VolumePedalInput::VolumePedalInput()
{
}


VolumePedalInput::~VolumePedalInput()
{
}
