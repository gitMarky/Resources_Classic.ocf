/*-- Baum --*/


#include TRE1

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local BlastIncinerate = 10;
local BurnTo = TRB3;
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
	Length = 40,
	Delay = 10,
	X = 0,
	Y = 0,
	Wdt = 52,
	Hgt = 75,
	FacetBase = 0,
	NextAction = "Still",
	StartCall = "Still",
},

Breeze = {
	Prototype = Action,
	Name = "Breeze",
	Directions = 2,
	FlipDir = 1,
	Length = 40,
	Delay = 2,
	X = 0,
	Y = 0,
	Wdt = 52,
	Hgt = 75,
	FacetBase = 0,
	NextAction = "Breeze",
	StartCall = "Breeze",
},

};
