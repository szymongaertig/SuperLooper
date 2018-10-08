#include "ConfigurationManager.h"

#pragma once
class VolumePedalInput
{
public:
	void Configure(ConfigurationManager configurationManager);
	short getNormalizedValue();
	void setMaxValueFromCurrentPosition();
	void setMinValueFromCurrentPosition();
	VolumePedalInput();
	~VolumePedalInput();
};

