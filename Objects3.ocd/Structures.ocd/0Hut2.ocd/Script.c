/*-- Holzhütte --*/


#include DOOR
#include BAS4

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local BlastIncinerate = 45;
local ContainBlast = 1;
local BurnTo = HTB2;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
OpenDoor = {
	Prototype = Action,
	Name = "OpenDoor",
	Procedure = DFA_NONE,
	Length = 10,
	Delay = 1,
	X = 0,
	Y = 50,
	Wdt = 10,
	Hgt = 16,
	OffX = 15,
	OffY = 34,
	FacetBase = 1,
	NextAction = "DoorOpen",
	StartCall = "SoundOpenDoor",
},

DoorOpen = {
	Prototype = Action,
	Name = "DoorOpen",
	Procedure = DFA_NONE,
	Delay = 20,
	X = 90,
	Y = 50,
	Wdt = 10,
	Hgt = 16,
	OffX = 15,
	OffY = 34,
	FacetBase = 1,
	NextAction = "CloseDoor",
	StartCall = "OpenEntrance",
	EndCall = "CloseEntrance",
},

CloseDoor = {
	Prototype = Action,
	Name = "CloseDoor",
	Procedure = DFA_NONE,
	Length = 10,
	Reverse = 1,
	Delay = 1,
	X = 0,
	Y = 50,
	Wdt = 10,
	Hgt = 16,
	OffX = 15,
	OffY = 34,
	FacetBase = 1,
	NextAction = "Idle",
	StartCall = "SoundCloseDoor",
},

};
