/*
 Name:		Looper.ino
 Created:	10/6/2018 3:26:37 PM
 Author:	Garfieldsg
*/

int ledPin = 13;

// the setup function runs once when you press reset or power the board
void setup() {
	pinMode(ledPin, OUTPUT);
}

// the loop function runs over and over again until power down or reset
void loop() {
	// listen midi messages
	digitalWrite(ledPin, HIGH);
	delay(500);
	digitalWrite(ledPin, LOW);
	delay(500);
	// react them
}
