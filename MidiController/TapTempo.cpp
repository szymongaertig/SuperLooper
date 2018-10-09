#include "TapTempo.h"

const int _milsForMinute = 60 * 1000;

void TapTempo::resetTaps()
{
	_tapsTimeSum = 0;
	_numberOfTaps = 0;
}

int TapTempo::getCurrentTempo()
{
	return _currentTempo;
}

void TapTempo::registerTapAction(unsigned long actionTime)
{
	if (_numberOfTaps > 0) {
		int currentTimeDiff = actionTime - _lastTapTime;
		
		// prevent to big difference between measuremets
		int averageTapsDiff = getAverageTapDiff();

		if (currentTimeDiff > averageTapsDiff * 2 
			|| currentTimeDiff < averageTapsDiff / 2) {
			resetTaps();
			_numberOfTaps = 0;
		}
		_tapsTimeSum += currentTimeDiff;
	}

	_numberOfTaps++;

	int averageTapsDiff = getAverageTapDiff();
	calculateCurrentTempo(averageTapsDiff);

	_lastTapTime = actionTime;
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
	
	return _tapsTimeSum / (_numberOfTaps-1);
}

void TapTempo::calculateCurrentTempo(int averageTapDiff)
{
	if (_numberOfTaps > 1) {
		_currentTempo = _milsForMinute / averageTapDiff;
	}
	else {
		_currentTempo = 0;
	}
}

