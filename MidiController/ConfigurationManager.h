#include "SwitchMap.h"

#pragma once
const short NumberOfBanks = 20;
const short NumberOfSwitches = 7;
const short BankNameLenght = 10;

struct BankConfiguration {
public:
	char name[BankNameLenght];
	SwitchMap switchMap[NumberOfSwitches];
	bool activeInput;
	short tempo;
	bool footSwitches[2];
	bool loops[8];
};

struct Configuration {
public:
	short firmwareVersion;
	bool isVolumePedalEnabled;
	bool isVolumePedalCalibrated;
	int maxVolumePedalPosition;
	int minVolumePedalPosition;
	bool mute;
	BankConfiguration banks[NumberOfBanks];
};

class ConfigurationManager
{
public:
	void selectPrevBank();
	void selectNextBank();
	void initConfigurationIfNeeded(short firmwareVersion);
	ConfigurationManager();
	~ConfigurationManager();
	Configuration currentConfiguration;
	BankConfiguration *activeBank;
private:
	short _activeBankIndex;
	Configuration createInitialConfigurationStruct(short firmwareVersion);
};

