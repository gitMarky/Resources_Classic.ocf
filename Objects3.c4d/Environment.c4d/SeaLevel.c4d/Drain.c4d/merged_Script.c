/*-- Drain --*/


protected func Initialize()
{
  SetAction("Drain");
  return(1);
}

private func Draining()
{
  if (GBackLiquid())
    ExtractMaterialAmount(0, 0, GetMaterial(), 20);
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
Drain = {
	Prototype = Action,
	Name = "Drain",
	Length = 1,
	Delay = 5,
	NextAction = "Drain",
	StartCall = "Draining",
},

};
