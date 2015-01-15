/*-- Totes Monster --*/


/* Verwesung */

protected func Decaying()
{
  DoCon(-2);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Dead = {
	Prototype = Action,
	Name = "Dead",
	Procedure = DFA_NONE,
	Directions = 2,
	FlipDir = 1,
	Length = 1,
	Delay = 3000,
	X = 0,
	Y = 0,
	Wdt = 48,
	Hgt = 34,
	FacetBase = 0,
	NextAction = "Decay",
},

};
