#include "alarm.h"
/*
void actions_openDoor(); 
void actions_closeDoor();

void actions_WeeWooWeeWoo(); //Enables the loud thingy
void actions_calmTFDown(); //Disables the loud thingy

int actions_sniff(); //Checks the smoke detector

void actions_bonk(); //Disables everything */

void actions_setup()
{
	pinMode(MOSFET_SOLENOID_THING, OUTPUT);
	pinMode(MOSFET_LOUD_THING, OUTPUT);
	pinMode(MOSFET_BLINKY_THING, OUTPUT);
}

void actions_openDoor()
{
	Serial.println(F("Debug: opening the door"));
	digitalWrite(MOSFET_SOLENOID_THING, HIGH);
}

void actions_closeDoor()
{
	Serial.println(F("Debug: Closing the door"));
	digitalWrite(MOSFET_SOLENOID_THING, LOW);
}

void actions_WeeWooWeeWoo()
{
	Serial.println(F("Debug: enabling the alarm"));
	digitalWrite(MOSFET_LOUD_THING, HIGH);
	digitalWrite(MOSFET_BLINKY_THING, HIGH);
}

void actions_calmTFDown()
{
	Serial.println(F("Debug: disabling the alarm"));
	digitalWrite(MOSFET_LOUD_THING, LOW);
	digitalWrite(MOSFET_BLINKY_THING, LOW);
}

int actions_sniff()
{
	int result = analogRead(FIRE_ALARM_PIN);
	if (result >= 512) {
		if (fsm_getState() == FSM_STATE_ALARMED) {
			Serial.println(F("Debug: oh noes, fire detected"));
			fsm_setState(FSM_STATE_PANIK);
		}
	}
	else {
		if (fsm_getState() == FSM_STATE_PANIK) {
			Serial.println(F("Debug: fire is gone! (or the smoke detector has burned down idk)"));
			fsm_setPreviousState();
		}
	}
}

void actions_bonk()
{
	actions_calmTFDown();
	fsm_setState(FSM_STATE_KALM);
}