/*-- Seegras --*/


#include SWD1

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local Placement = 1;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Wiggle = {
	Prototype = Action,
	Name = "Wiggle",
	Procedure = DFA_NONE,
	Length = 8,
	Delay = 3,
	X = 0,
	Y = 0,
	Wdt = 16,
	Hgt = 20,
	NextAction = "Wiggle",
},

Dry = {
	Prototype = Action,
	Name = "Dry",
	Procedure = DFA_NONE,
	Delay = 1,
	X = 0,
	Y = 20,
	Wdt = 16,
	Hgt = 20,
	NextAction = "Hold",
},

};
