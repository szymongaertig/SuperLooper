/*
 Name:		MidiController.ino
 Created:	10/8/2018 8:05:23 PM
 Author:	Garfieldsg
*/

// the setup function runs once when you press reset or power the board
#include <ArduinoUnitMock.h>
#include <ArduinoUnit.h>
#include "../MidiController/TapTempo.h"
#include "../MidiController/TapTempo.cpp"

void setup()
{
	Serial.begin(9600);
	while (!Serial) {} // Portability for Leonardo/Micro
}

void loop()
{
	Test::run();
}

test(TapTempo_WhenSingleTap_ThenReturn0) {
	TapTempo sut;
	sut.resetTaps();
	sut.registerTapAction(1000);
	assertEqual(0, sut.getCurrentTempo());
}

test(TapTempo_WhenTwoTaps_ThenReturnProperTempo) {
	TapTempo sut;
	sut.resetTaps();
	sut.registerTapAction(1000);
	sut.registerTapAction(2000);
	assertEqual(60, sut.getCurrentTempo());
}

test(TapTempo_WithManyTaps_ThenReturnProperTempo) {
	TapTempo sut;
	sut.resetTaps();
	sut.registerTapAction(1000);
	sut.registerTapAction(3000);
	sut.registerTapAction(5000);
	sut.registerTapAction(7000);
	assertEqual(30, sut.getCurrentTempo());
}

test(TapTempo_WithManyTaps_WithDelayInterval_ThenReturnProperTempo) {
	TapTempo sut;
	sut.resetTaps();
	sut.registerTapAction(1000);
	sut.registerTapAction(3000);
	sut.registerTapAction(5000);
	sut.registerTapAction(7000);
	// current tempo 30
	// delay
	sut.registerTapAction(101000);
	sut.registerTapAction(101100);
	sut.registerTapAction(101200);
	assertEqual(60, sut.getCurrentTempo());
}

test(TapTempo_WithManyTaps_WithDelayInterval_ThenReturnProperTempo1) {
	TapTempo sut;
	sut.resetTaps();
	sut.registerTapAction(1000);
	sut.registerTapAction(3000);
	sut.registerTapAction(5000);
	sut.registerTapAction(7000);
	// current tempo 30
	// delay
	sut.registerTapAction(101000);
	sut.registerTapAction(101100);
	sut.registerTapAction(101200);
	// current tempo 60
	// delay
	sut.registerTapAction(201000);
	sut.registerTapAction(203000);
	sut.registerTapAction(205000);
	assertEqual(30, sut.getCurrentTempo());
}