/*-- Stern --*/


local iBrightness;

// Local(0) und Local(1) werden f�r die Parallax-Steuerung verwendet...

protected func Initialize()
{
  iBrightness = Random(10) + 1;
  SetAction("Appear");
  MakeBackground();
  return(1);
}

private func Appearing()
{
  if (GetPhase() == iBrightness)
  {
    SetAction("Shine");
    SetPhase(iBrightness - 1);
  }
  return(0);
}
  
/* Versetzt den Stern in den Hintergrund */

private func MakeBackground()
{
  SetCategory(GetCategory() | C4D_Parallax() | C4D_Background());
  Local(0) = Local(1) = Random(20) + iBrightness * 5 - 5;
  if (Random(3)) SetClrModulation(RGB(Random(100) + 156, Random(100) + 156, Random(100) + 156));
}

/* Versetzt OldGfx-Sterne beim Laden eines Spielstands in den Hintergrund */
  
protected func UpdateTransferZone()
{
  if (~GetCategory() & C4D_Parallax()) 
    MakeBackground();
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
Appear = {
	Prototype = Action,
	Name = "Appear",
	Length = 10,
	Delay = 10,
	X = 0,
	Y = 0,
	Wdt = 3,
	Hgt = 3,
	FacetBase = 0,
	NextAction = "Hold",
	PhaseCall = "Appearing",
},

Shine = {
	Prototype = Action,
	Name = "Shine",
	Length = 10,
	Delay = 0,
	X = 0,
	Y = 0,
	Wdt = 3,
	Hgt = 3,
	FacetBase = 0,
	NextAction = "Hold",
},

};
