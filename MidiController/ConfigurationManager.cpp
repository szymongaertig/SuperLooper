#include "ConfigurationManager.h"
#include <EEPROM.h>
#include <Arduino.h>
#include "SwitchMap.h"
void clearEeprom() {
	for (int i = 0; i < EEPROM.length(); i++) {
		EEPROM.write(i, 0);
	}
}

void ConfigurationManager::initConfigurationIfNeeded(short firmwareVersion)
{
	Configuration configurationFromMemory;
	EEPROM.get(0, configurationFromMemory);

	if (configurationFromMemory.FirmwareVersion != firmwareVersion) {

		CurrentConfiguration = createInitialConfigurationStruct(firmwareVersion);
		clearEeprom();
		EEPROM.put(0, CurrentConfiguration);
	}
	else {
		CurrentConfiguration = configurationFromMemory;
	}
}

ConfigurationManager::ConfigurationManager()
{

}

ConfigurationManager::~ConfigurationManager()
{
}

Configuration ConfigurationManager::createInitialConfigurationStruct(short firmwareVersion)
{
	Configuration result;
	result.FirmwareVersion = firmwareVersion;

	// Switch map
	result.SwitchMap[0].Function = SwitchFunction::BankDown;
	result.SwitchMap[0].ReadOnly = true;

	result.SwitchMap[1].Function = SwitchFunction::BankUp;
	result.SwitchMap[1].ReadOnly = true;

	result.SwitchMap[2].Function = SwitchFunction::LoopToogle;
	result.SwitchMap[2].FunctionParameter = 2;
	result.SwitchMap[2].ReadOnly = false;

	result.SwitchMap[3].Function = SwitchFunction::LoopToogle;
	result.SwitchMap[3].FunctionParameter = 3;
	result.SwitchMap[3].ReadOnly = false;

	result.SwitchMap[4].Function = SwitchFunction::LoopToogle;
	result.SwitchMap[4].FunctionParameter = 4;
	result.SwitchMap[4].ReadOnly = false;

	result.SwitchMap[5].Function = SwitchFunction::LoopToogle;
	result.SwitchMap[5].FunctionParameter = 5;
	result.SwitchMap[5].ReadOnly = false;

	result.SwitchMap[6].Function = SwitchFunction::TapTempoTrigger;
	result.SwitchMap[6].ReadOnly = false;

	// volume pedal
	result.IsVolumePedalCalibrated = false;
	result.IsVolumePedalEnabled = false;
	result.MaxVolumePedalPosition = 0;
	result.MinVolumePedalPosition = 0;

	return result;
}
