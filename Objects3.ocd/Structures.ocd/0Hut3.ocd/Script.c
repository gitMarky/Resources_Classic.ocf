/*-- Hütte --*/


#include BAS4
#include DOOR

  
/* Forschung */

public func GetResearchBase() { return(HUT2); }


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local BlastIncinerate = 75;
local ContainBlast = 1;
local BurnTo = HTB3;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
OpenDoor = {
	Prototype = Action,
	Name = "OpenDoor",
	Length = 9,
	Delay = 1,
	X = 0,
	Y = 50,
	Wdt = 10,
	Hgt = 19,
	OffX = 35,
	OffY = 31,
	FacetBase = 1,
	NextAction = "DoorOpen",
	StartCall = "SoundOpenDoor",
},

DoorOpen = {
	Prototype = Action,
	Name = "DoorOpen",
	Delay = 40,
	X = 90,
	Y = 50,
	Wdt = 10,
	Hgt = 19,
	OffX = 35,
	OffY = 31,
	FacetBase = 1,
	NextAction = "CloseDoor",
	StartCall = "OpenEntrance",
	EndCall = "CloseEntrance",
},

};
