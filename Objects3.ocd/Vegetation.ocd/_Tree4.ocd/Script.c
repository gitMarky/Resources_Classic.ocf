/*-- Nadelbaum --*/


#include TRE1

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local BlastIncinerate = 10;
local BurnTo = TRB4;
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
	Length = 20,
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
	Length = 1,
	Delay = 50,
	X = 0,
	Y = 0,
	Wdt = 40,
	Hgt = 56,
	FacetBase = 0,
	NextAction = "Still",
	StartCall = "Still",
},

};