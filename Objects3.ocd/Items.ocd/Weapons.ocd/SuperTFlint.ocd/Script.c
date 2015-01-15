/*-- Super-T-Flint --*/


#include TFLN

public func ExplodeSize() { return(27); }

/* Forschung */

public func GetResearchBase() { return(TFLN); }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local Collectible = 1;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Activated = {
	Prototype = Action,
	Name = "Activated",
	Delay = 120,
	X = 0,
	Y = 6,
	Wdt = 6,
	Hgt = 6,
	NextAction = "TimeOver",
	Sound = "Fusing",
},

};
