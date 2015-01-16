/*-- Funke --*/


protected func Process()
{
  if (Random(10)+10 < GetActTime()) DoCon(-25);
  return(1);
}

protected func Completion()
{
  DoCon(Random(100));
  SetAction("Sparkle");
  return(1);
}

protected func Hit()
{
  return(DoCon(-50));
}

/* Globaler Funktionsaufruf */

global func Sparkle(int iAmount, int iX, int iY)
{
  CastObjects(SPRK, iAmount/3 +2, iAmount, iX, iY);
  return(1);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local NoBurnDecay = 1;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Sparkle = {
	Prototype = Action,
	Name = "Sparkle",
	Length = 3,
	Delay = 3,
	X = 0,
	Y = 0,
	Wdt = 5,
	Hgt = 5,
	NextAction = "Sparkle",
	EndCall = "Process",
	Sound = "Fire",
},

};
