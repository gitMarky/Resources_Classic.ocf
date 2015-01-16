/*-- Palme --*/


#include TRE1

// Etwas leichter zu fällen
private func TreeStrength() { return(100); }

/* Überladungen für zusätzliche Sturm-Animation */  

private func Breeze()
{
  if (Abs(GetWind()) < 50 + MotionThreshold) SetAction("Still");
  if (Abs(GetWind()) > 74 + MotionThreshold) SetAction("Storm");
}
    
private func Storm()
{
  if (Abs(GetWind()) < 75 + MotionThreshold) SetAction("Breeze");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local BlastIncinerate = 10;
local BurnTo = PLB2;
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
	Wdt = 48,
	Hgt = 65,
	FacetBase = 0,
	NextAction = "Still",
	StartCall = "Still",
},

Breeze = {
	Prototype = Action,
	Name = "Breeze",
	Directions = 2,
	FlipDir = 1,
	Length = 20,
	Delay = 5,
	X = 0,
	Y = 0,
	Wdt = 48,
	Hgt = 65,
	FacetBase = 0,
	NextAction = "Breeze",
	StartCall = "Breeze",
},

Storm = {
	Prototype = Action,
	Name = "Storm",
	Directions = 2,
	FlipDir = 1,
	Length = 20,
	Delay = 3,
	X = 0,
	Y = 65,
	Wdt = 48,
	Hgt = 65,
	FacetBase = 0,
	NextAction = "Storm",
	StartCall = "Storm",
},

};
