/*-- Kleine Burg --*/


#include BAS5
#include DOOR

private func SoundOpenDoor()
{
  Sound("GateOpen");
}
  
private func SoundCloseDoor()
{
  Sound("GateClose");
}

public func IsCastle() { return true; }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local BlastIncinerate = 120;
local ContainBlast = 1;
local BurnTo = CSB1;

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
	Y = 40,
	Wdt = 16,
	Hgt = 20,
	OffX = 22,
	OffY = 20,
	FacetBase = 1,
	NextAction = "DoorOpen",
	StartCall = "SoundOpenDoor",
},

DoorOpen = {
	Prototype = Action,
	Name = "DoorOpen",
	Procedure = DFA_NONE,
	Delay = 60,
	X = 144,
	Y = 40,
	Wdt = 16,
	Hgt = 20,
	OffX = 22,
	OffY = 20,
	FacetBase = 1,
	NextAction = "CloseDoor",
	StartCall = "OpenEntrance",
	EndCall = "CloseEntrance",
},

};
