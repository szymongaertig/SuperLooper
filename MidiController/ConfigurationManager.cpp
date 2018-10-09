#include "ConfigurationManager.h"
#include <EEPROM.h>
#include <Arduino.h>
#include "SwitchMap.h"

void clearEeprom() {
	for (int i = 0; i < EEPROM.length(); i++) {
		EEPROM.write(i, 0);
	}
}

void ConfigurationManager::selectPrevBank()
{
}

void ConfigurationManager::selectNextBank()
{
}

void ConfigurationManager::initConfigurationIfNeeded(short firmwareVersion)
{
	Configuration configurationFromMemory;
	EEPROM.get(0, configurationFromMemory);

	if (configurationFromMemory.firmwareVersion != firmwareVersion) {
		currentConfiguration = createInitialConfigurationStruct(firmwareVersion);
		clearEeprom();
		EEPROM.put(0, currentConfiguration);
	}
	else {
		currentConfiguration = configurationFromMemory;
	}

	_activeBankIndex = 0;
	activeBank = &currentConfiguration.banks[_activeBankIndex];
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
	result.firmwareVersion = firmwareVersion;

	// Banks
	for (short bankIndex = 0; bankIndex < NumberOfBanks; bankIndex++) {
		BankConfiguration *currentBank = &result.banks[bankIndex];

		String bankName = "Bank " + (bankIndex + 1);
		bankName.toCharArray(currentBank->name, BankNameLenght, 0);

		currentBank->activeInput = 0;
		currentBank->tempo = 120;

		currentBank->footSwitches[0] = true;
		currentBank->footSwitches[1] = false;
		
		// Foot switches
		currentBank->loops[0] = true;
		currentBank->loops[1] = true;
		currentBank->loops[2] = true;
		currentBank->loops[3] = true;
		currentBank->loops[4] = true;
		currentBank->loops[5] = true;
		currentBank->loops[6] = true;
		currentBank->loops[7] = true;

		// Switch map
		currentBank->switchMap[0].Function = SwitchFunction::BankDown;
		currentBank->switchMap[0].ReadOnly = true;

		currentBank->switchMap[1].Function = SwitchFunction::BankUp;
		currentBank->switchMap[1].ReadOnly = true;

		currentBank->switchMap[2].Function = SwitchFunction::LoopToogle;
		currentBank->switchMap[2].FunctionParameter = 0;
		currentBank->switchMap[2].ReadOnly = false;

		currentBank->switchMap[3].Function = SwitchFunction::LoopToogle;
		currentBank->switchMap[3].FunctionParameter = 1;
		currentBank->switchMap[3].ReadOnly = false;

		currentBank->switchMap[4].Function = SwitchFunction::LoopToogle;
		currentBank->switchMap[4].FunctionParameter = 2;
		currentBank->switchMap[4].ReadOnly = false;

		currentBank->switchMap[5].Function = SwitchFunction::LoopToogle;
		currentBank->switchMap[5].FunctionParameter = 3;
		currentBank->switchMap[5].ReadOnly = false;

		currentBank->switchMap[6].Function = SwitchFunction::TapTempoTrigger;
		currentBank->switchMap[6].ReadOnly = false;
	}

	// volume pedal
	result.isVolumePedalCalibrated = true;
	result.isVolumePedalEnabled = true;
	result.maxVolumePedalPosition = 928;
	result.minVolumePedalPosition = 464;

	result.mute = false;

	return result;
}
