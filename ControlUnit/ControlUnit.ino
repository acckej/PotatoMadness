/*
 Name:		ControlUnit.ino
 Created:	8/16/2017 11:21:32 PM
 Author:	Acckej
*/
#include "HwCheckSequence.h"

// the setup function runs once when you press reset or power the board
void setup() 
{

}

// the loop function runs over and over again until power down or reset
void loop() 
{
	auto a = HwCheckSequence();	
}

