#include "SwitchManager.h"
#include <Arduino.h>

int _switch1Pin = 6;
int _switch2Pin = 7;
int _switch3Pin = 8;
int _switch4Pin = 9;
int _switch5Pin = 10;
int _switch6Pin = 11;
int _switch7Pin = 12;

void SwitchManager::Configure(ConfigurationManager configurationManager)
{
	_configurationManager = configurationManager;
}

DetectedSwitch * SwitchManager::GetActiveSwitch()
{
	DetectedSwitch result;
	result.ActionTime = millis();
	int activeSwitch = DetectActiveSwitchId();

	if (activeSwitch > 0) {
		SwitchMap currentSwitch = _configurationManager.CurrentConfiguration.SwitchMap[activeSwitch];
		result.Function = currentSwitch.Function;
		result.FunctionParameter = currentSwitch.FunctionParameter;

		return &result;
	}

	return nullptr;
}

SwitchManager::SwitchManager()
{
	pinMode(_switch1Pin, OUTPUT);
	pinMode(_switch2Pin, OUTPUT);
	pinMode(_switch3Pin, OUTPUT);
	pinMode(_switch4Pin, OUTPUT);
	pinMode(_switch5Pin, OUTPUT);
	pinMode(_switch6Pin, OUTPUT);
	pinMode(_switch7Pin, OUTPUT);
}

SwitchManager::~SwitchManager()
{
}

short SwitchManager::DetectActiveSwitchId()
{
	if (digitalRead(_switch1Pin) == 1) {
		return 1;
	}
	if (digitalRead(_switch2Pin) == 1) {
		return 2;
	}
	if (digitalRead(_switch3Pin) == 1) {
		return 3;
	}
	if (digitalRead(_switch4Pin) == 1) {
		return 4;
	}
	if (digitalRead(_switch5Pin) == 1) {
		return 5;
	}
	if (digitalRead(_switch6Pin) == 1) {
		return 6;
	}
	if (digitalRead(_switch7Pin) == 1) {
		return 7;
	}
	return -1;
}
