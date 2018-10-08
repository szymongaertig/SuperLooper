#include <EEPROM.h>
#include "VolumePedalInput.h"
#include "ConfigurationManager.h"
#include "TapTempo.h"
#include "SwitchManager.h"
#include "MidiProcessor.h"

short _firmwareVersion = 3;

VolumePedalInput _volumePedalInput;
ConfigurationManager _configurationManager;
TapTempo _tapTempo;
SwitchManager _switchManager;
MidiProcessor _midiProcessor;

int _ledPin = 13;

// the setup function runs once when you press reset or power the board
void setup() {
	pinMode(_ledPin, OUTPUT);
	Serial.begin(31250);

	InitializeModules();
}

void InitializeModules() {
	_configurationManager.initConfigurationIfNeeded(_firmwareVersion);
	_volumePedalInput.Configure(_configurationManager);
	_switchManager.Configure(_configurationManager);
	_tapTempo.ResetTaps();
}

// the loop function runs over and over again until power down or reset
void loop() {
	// processing pressed switches
	DetectedSwitch* activeSwitch = _switchManager.GetActiveSwitch();
	if (activeSwitch) {
		switch (activeSwitch->Function) {
		case SwitchFunction::TapTempoTrigger:
			_tapTempo.RegisterTapAction(activeSwitch->ActionTime);
			// ustawienie tempa w aktywnym banku
			_midiProcessor.sendSetTempoCmd(_tapTempo.CurrentTempo);
			break;
		case SwitchFunction::BankDown:
			break;
		case SwitchFunction::BankUp:
			break;
		case SwitchFunction::FootSwitchToogle:
			break;
		case SwitchFunction::Mute:
			break;
		case SwitchFunction::SelectInput:
			break;
		}
	}
	// processing menu buttons
	else {

	}

	// processing volume pedal 
	if (_configurationManager.CurrentConfiguration.IsVolumePedalCalibrated
		&& _configurationManager.CurrentConfiguration.IsVolumePedalEnabled) {
		int volumePedalPosition = _volumePedalInput.getNormalizedValue();
		_midiProcessor.sendSetVolumeCmd(volumePedalPosition);
	}
}

void CalibrateVolumePedal() {
	_volumePedalInput.setMaxValueFromCurrentPosition();
	_volumePedalInput.setMinValueFromCurrentPosition();
}

