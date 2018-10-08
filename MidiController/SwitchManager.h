#include "SwitchMap.h"
#include "ConfigurationManager.h"
#pragma once

class SwitchManager
{
public:
	void Configure(ConfigurationManager configurationManager);
	DetectedSwitch * GetActiveSwitch();
	SwitchManager();
	~SwitchManager();
private: 
	ConfigurationManager  _configurationManager;
	short DetectActiveSwitchId();
};

