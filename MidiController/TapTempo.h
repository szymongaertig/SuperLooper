#pragma once
class TapTempo
{
public:
	void resetTaps();
	int getCurrentTempo();
	void registerTapAction(unsigned long actionTime);
	TapTempo();
	~TapTempo();
private:
	int _currentTempo;
	unsigned long _lastTapTime = 0;
	int _numberOfTaps = 0;
	int _tapsTimeSum = 0;
	int getAverageTapDiff();
	void calculateCurrentTempo(int averageTapDiff);
};

