#pragma once
class TapTempo
{
public:
	void ResetTaps();
	int CurrentTempo;
	void RegisterTapAction(unsigned long actionTime);
	TapTempo();
	~TapTempo();
private:
	unsigned long _lastTapTime = 0;
	int _numberOfTaps = 0;
	int _tapsTimeSum = 0;
	int getAverageTapDiff();
	void CalculateCurrentTempo(int averageTapDiff);
};

