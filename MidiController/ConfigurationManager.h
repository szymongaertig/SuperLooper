#include "SwitchMap.h"

#pragma once
struct Configuration {
public:
	short FirmwareVersion;
	bool IsVolumePedalEnabled;
	bool IsVolumePedalCalibrated;
	int MaxVolumePedalPosition;
	int MinVolumePedalPosition;
	SwitchMap SwitchMap[10];
};

class ConfigurationManager
{
public:
	void initConfigurationIfNeeded(short firmwareVersion);
	ConfigurationManager();
	~ConfigurationManager();
	Configuration CurrentConfiguration;
private:
	Configuration createInitialConfigurationStruct(short firmwareVersion);
};

