#include "TapTempo.h"
#include <Arduino.h>

const int _milsForMinute = 60 * 1000;

void TapTempo::ResetTaps()
{
	_tapsTimeSum = 0;
	_numberOfTaps = 0;
}

void TapTempo::RegisterTapAction(unsigned long actionTime)
{
	_numberOfTaps++;

	if (_numberOfTaps > 1) {
		int currentTimeDiff = actionTime - _lastTapTime;
		int averageTapsDiff = getAverageTapDiff();

		// prevent to big difference between measuremets
		if (actionTime > averageTapsDiff * 2 || actionTime < averageTapsDiff / 2) {
			ResetTaps();
			_numberOfTaps = 1;
		}
		_tapsTimeSum += currentTimeDiff;
	}

	_lastTapTime = actionTime;

	int averageTapsDiff = getAverageTapDiff();
	if (averageTapsDiff > 0) {
		CalculateCurrentTempo(averageTapsDiff);
	}
}

TapTempo::TapTempo()
{

}

TapTempo::~TapTempo()
{
}

int TapTempo::getAverageTapDiff()
{
	if (_numberOfTaps < 2) {
		return 0;
	}

	return _tapsTimeSum / _numberOfTaps;
}

void TapTempo::CalculateCurrentTempo(int averageTapDiff)
{
	CurrentTempo = _milsForMinute / averageTapDiff;
}

