#include "ConfigurationManager.h"

#pragma once
class VolumePedalInput
{
public:
	void configure(ConfigurationManager configurationManager);
	short getNormalizedValue();
	void setMaxValueFromCurrentPosition();
	void setMinValueFromCurrentPosition();
	VolumePedalInput();
	~VolumePedalInput();
private:
	int readVolumePedalValue();
};

