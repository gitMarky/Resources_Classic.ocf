/*-- Baum --*/


#include TREE

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local BlastIncinerate = 10;
local BurnTo = TRB1;
local ContactIncinerate = 2;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Initialize = {
	Prototype = Action,
	Name = "Initialize",
	Directions = 2,
	FlipDir = 1,
	Length = 40,
	Delay = 1,
	FacetBase = 1,
	NextAction = "Still",
	PhaseCall = "Initializing",
},

Still = {
	Prototype = Action,
	Name = "Still",
	Directions = 2,
	FlipDir = 1,
	Length = 10,
	Delay = 4,
	X = 0,
	Y = 0,
	Wdt = 73,
	Hgt = 73,
	FacetBase = 0,
	NextAction = "StillSlow",
	StartCall = "Still",
},

StillSlow = {
	Prototype = Action,
	Name = "StillSlow",
	Directions = 2,
	FlipDir = 1,
	Length = 2,
	Delay = 5,
	X = 730,
	Y = 0,
	Wdt = 73,
	Hgt = 73,
	FacetBase = 0,
	NextAction = "StillSlower",
},

StillSlower = {
	Prototype = Action,
	Name = "StillSlower",
	Directions = 2,
	FlipDir = 1,
	Length = 2,
	Delay = 7,
	X = 876,
	Y = 0,
	Wdt = 73,
	Hgt = 73,
	FacetBase = 0,
	NextAction = "StillSlowBack",
},

StillSlowBack = {
	Prototype = Action,
	Name = "StillSlowBack",
	Directions = 2,
	FlipDir = 1,
	Length = 4,
	Reverse = 1,
	Delay = 7,
	X = 730,
	Y = 0,
	Wdt = 73,
	Hgt = 73,
	FacetBase = 0,
	NextAction = "StillBack",
},

StillBack = {
	Prototype = Action,
	Name = "StillBack",
	Directions = 2,
	FlipDir = 1,
	Length = 10,
	Reverse = 1,
	Delay = 4,
	X = 0,
	Y = 0,
	Wdt = 73,
	Hgt = 73,
	FacetBase = 0,
	NextAction = "Still",
},

};
