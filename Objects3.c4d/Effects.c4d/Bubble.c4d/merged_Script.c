/* Luftblase */


protected func Shiver()
  {
  // Bewegung
  SetXDir(Random(21) - 10);
  return(1);
	}

protected func Initialize()
  {
  // Aktion setzen
  SetAction("Bubble");
  SetComDir(COMD_Up());
  // Nicht in Flüssigkeit gestartet: gleich weg
  if (!GBackLiquid(0,0)) 
    Remove();
  return(1);
  }

protected func LiquidCheck()
  {
  if(!InLiquid())
    Remove();
  }
protected func Remove()
  {
  RemoveObject();
  return(1);
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
Bubble = {
	Prototype = Action,
	Name = "Bubble",
	Procedure = DFA_FLOAT,
	Length = 40,
	Delay = 3,
	X = 0,
	Y = 0,
	Wdt = 1,
	Hgt = 1,
	OffX = 0,
	OffY = 0,
	FacetBase = 0,
	EndCall = "Remove",
	PhaseCall = "LiquidCheck",
},

};
