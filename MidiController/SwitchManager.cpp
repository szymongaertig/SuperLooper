
#include "SwitchManager.h"
#include <Arduino.h>

int _numberOfSwitchPins = 7;

int _switchPins[7] = {
	6,7,8,9,10,11,12
};

void SwitchManager::configure(ConfigurationManager configurationManager)
{
	_configurationManager = &configurationManager;
}

DetectedSwitch * SwitchManager::getActiveSwitch()
{
	DetectedSwitch result;
	result.ActionTime = millis();
	int activeSwitch = detectActiveSwitchId();

	if (activeSwitch > 0) {
		SwitchMap *currentSwitch = _configurationManager->activeBank->switchMap;

		result.Function = currentSwitch->Function;
		result.FunctionParameter = currentSwitch->FunctionParameter;

		Serial.write("Switch detected");
		
		return &result;
	}

	return nullptr;
}

SwitchManager::SwitchManager()
{
	for (short index = 0; index < _numberOfSwitchPins; index++) {
		pinMode(_switchPins[index], OUTPUT);
	}
}

SwitchManager::~SwitchManager()
{
}

short SwitchManager::detectActiveSwitchId()
{
	for (short switchIndex = 0; switchIndex < _numberOfSwitchPins; switchIndex++) {
		if (digitalRead(switchIndex) == 1) {
			return switchIndex;
		}
	}

	return -1;
}
