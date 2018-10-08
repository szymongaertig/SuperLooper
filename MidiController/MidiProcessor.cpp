#include "MidiProcessor.h"
#include <Arduino.h>

MidiProcessor::MidiProcessor()
{
}

MidiProcessor::~MidiProcessor()
{
}

void MidiProcessor::sendSetTempoCmd(int tempo)
{
}

void MidiProcessor::sendSetVolumeCmd(int volume)
{
	Serial.print(0xB0 | (_channel & 0xf));
	Serial.print(0x07);
	Serial.print(volume & 0x7f);
}

void MidiProcessor::setChannel(unsigned char channel)
{
	channel = channel;
}

void MidiProcessor::noteOn(int cmd, int pitch, int velocity)
{
	Serial.write(cmd);
	Serial.write(pitch);
	Serial.write(velocity);
}
