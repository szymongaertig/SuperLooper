#include "SwitchMap.h"
#include "ConfigurationManager.h"
#pragma once

class SwitchManager
{
public:
	void configure(ConfigurationManager configurationManager);
	DetectedSwitch * getActiveSwitch();
	SwitchManager();
	~SwitchManager();
private: 
	ConfigurationManager  *_configurationManager;
	short detectActiveSwitchId();
};

