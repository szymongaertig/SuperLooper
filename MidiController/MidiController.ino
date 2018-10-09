#include <EEPROM.h>
#include "VolumePedalInput.h"
#include "ConfigurationManager.h"
#include "TapTempo.h"
#include "SwitchManager.h"
#include "MidiProcessor.h"
#include "LedsManager.h"

short _firmwareVersion = 9;

VolumePedalInput _volumePedalInput;
ConfigurationManager _configurationManager;
TapTempo _tapTempo;
SwitchManager _switchManager;
MidiProcessor _midiProcessor;
LedsManager _ledsManager;

int _ledPin = 13;

// the setup function runs once when you press reset or power the board
void setup() {
	pinMode(_ledPin, OUTPUT);

	Serial.begin(31250);
	InitializeModules();
}

void InitializeModules() {
	_configurationManager.initConfigurationIfNeeded(_firmwareVersion);
	_volumePedalInput.configure(_configurationManager);
	_switchManager.configure(_configurationManager);
	_tapTempo.resetTaps();
}

// the loop function runs over and over again until power down or reset
void loop() {
	// processing pressed switches
	DetectedSwitch* activeSwitch = _switchManager.getActiveSwitch();

	if (activeSwitch) {
		switch (activeSwitch->Function) {
		case SwitchFunction::TapTempoTrigger:
			_tapTempo.registerTapAction(activeSwitch->ActionTime);
			int currentTempo = _tapTempo.getCurrentTempo();
			_configurationManager.activeBank->tempo = currentTempo;
			break;
		case SwitchFunction::BankDown:
			_configurationManager.selectPrevBank();
			break;
		case SwitchFunction::BankUp:
			_configurationManager.selectNextBank();
			break;
		case SwitchFunction::FootSwitchToogle:
			short footSwitchIndex = activeSwitch->FunctionParameter;
			_configurationManager.activeBank->footSwitches[footSwitchIndex] = !_configurationManager.activeBank->footSwitches[footSwitchIndex];
			break;
		case SwitchFunction::Mute:
			_configurationManager.currentConfiguration.mute =
				!_configurationManager.currentConfiguration.mute;
			break;
		case SwitchFunction::SelectInput:
			_configurationManager.activeBank->activeInput =
				!_configurationManager.activeBank->activeInput;
			break;
		case SwitchFunction::LoopToogle:
			short loopIndex = activeSwitch->FunctionParameter;
			break;
		}

		// refresh leds
	}


	// processing menu buttons
	else {
		// todo
	}

	if (_configurationManager.currentConfiguration.isVolumePedalCalibrated
		&& _configurationManager.currentConfiguration.isVolumePedalEnabled) {
		int volumePedalPosition = _volumePedalInput.getNormalizedValue();

		_midiProcessor.sendSetVolumeCmd(volumePedalPosition);
	}
}

void CalibrateVolumePedal() {
	_volumePedalInput.setMaxValueFromCurrentPosition();
	_volumePedalInput.setMinValueFromCurrentPosition();
}


