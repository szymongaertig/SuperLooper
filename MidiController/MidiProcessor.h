#pragma once
class MidiProcessor
{
public:
	MidiProcessor();
	~MidiProcessor();
	void sendSetTempoCmd(int tempo);
	void sendSetVolumeCmd(int volume);
	void setChannel(unsigned char channel);
private:
	unsigned char _channel;
	void noteOn(int cmd, int pitch, int velocity);
};

