/*-- Feuermonsterei --*/


/* TimerCall */

private func Breed()
{
  if (!Random(2000)) DoBreak();
  return(1);
}
  
/* Einwirkungen */  

protected func Hit()
{
  if (Random(2)) return(1);
  return(DoBreak());
}

protected func Damage()
{
  return(DoBreak());
}

/* Aktionen */
  
private func DoBreak()
{
  if (!ActIdle()) return(0);
  if (GBackSolid()) return(0);
  Sound("EggBreak");
  SetAction("Break");
  var pMonster = CreateConstruction(FMNS,0,0,-1,40);
  pMonster->Birth();
  return(1);
}
  
private func Destroy()
{
  RemoveObject();
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
Break = {
	Prototype = Action,
	Name = "Break",
	Length = 7,
	Delay = 2,
	X = 48,
	Y = 0,
	Wdt = 6,
	Hgt = 6,
	EndCall = "Destroy",
},

};
