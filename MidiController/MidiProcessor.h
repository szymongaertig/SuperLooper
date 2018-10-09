#pragma once
class MidiProcessor
{
public:
	MidiProcessor();
	~MidiProcessor();
	void sendSetVolumeCmd(short volume);
private:
	unsigned char _channel;
	void noteOn(int cmd, int pitch, int velocity);
};

