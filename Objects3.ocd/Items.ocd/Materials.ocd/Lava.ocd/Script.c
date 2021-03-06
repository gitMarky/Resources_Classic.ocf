/*--- Lava ---*/


local mat;

protected func Initialize() {
  SetAction("Evaporate");
  return(1);
}
  
protected func Hit()
{
	if(!mat) mat="Lava";
  CastPXS(mat, GetCon()/2, 35);
  RemoveObject();
  return(1);
}

private func SmokeTrail()
{
  Smoke(0, 0, 5);
  Smoke(0, -5, Random(7));
  if (GetActTime() > 75) Hit();
  return(1);
}
  

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local Collectible = 1;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Evaporate = {
	Prototype = Action,
	Name = "Evaporate",
	Delay = 1,
	X = 0,
	Y = 0,
	Wdt = 10,
	Hgt = 10,
	NextAction = "Evaporate",
	StartCall = "SmokeTrail",
	InLiquidAction = "Hit",
},

};
