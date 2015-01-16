/*-- Segelboot --*/


protected func Initialize() { SetAction("OnLand"); }

private func Floating()
{
  // Aufrichten
  SetRDir(BoundBy(GetR(),-20,+20)/-5);
  // Nicht mehr im Wasser
  if (!(GetOCF()&OCF_InLiquid())) 
    return(SetAction("OnLand"));
  // Segeln, wenn aufgerichtet
  if (Inside(GetR(),-5,+5))
    { ChangeDef(SLBS); SetAction("LowerSail"); }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local BlastIncinerate = 35;
local BurnTo = SLBB;
local ContactIncinerate = 5;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
OnLand = {
	Prototype = Action,
	Name = "OnLand",
	FacetBase = 1,
	NextAction = "OnLand",
	InLiquidAction = "InWater",
},

InWater = {
	Prototype = Action,
	Name = "InWater",
	Length = 1,
	Delay = 5,
	FacetBase = 1,
	NextAction = "InWater",
	StartCall = "Floating",
},

JustLanded = {
	Prototype = Action,
	Name = "JustLanded",
	Delay = 150,
	FacetBase = 1,
	NextAction = "OnLand",
},

};
