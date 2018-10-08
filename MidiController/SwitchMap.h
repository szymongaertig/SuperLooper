#pragma once

enum SwitchFunction {
	BankUp,
	BankDown,
	FootSwitchToogle,
	LoopToogle,
	SelectInput,
	Mute,
	TapTempoTrigger
};

struct SwitchMap {
public:
	SwitchFunction Function;
	// optional
	int FunctionParameter;
	bool ReadOnly;
};

struct DetectedSwitch {
public:
	SwitchFunction Function;
	// optional
	int FunctionParameter;
	unsigned long ActionTime;
};

