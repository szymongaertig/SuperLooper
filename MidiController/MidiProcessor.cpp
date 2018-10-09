#include "MidiProcessor.h"
#include <Arduino.h>

MidiProcessor::MidiProcessor()
{
}

MidiProcessor::~MidiProcessor()
{
}

void MidiProcessor::sendSetVolumeCmd(short volume)
{
}

void MidiProcessor::noteOn(int cmd, int pitch, int velocity)
{
	Serial.write(cmd);
	Serial.write(pitch);
	Serial.write(velocity);
}
