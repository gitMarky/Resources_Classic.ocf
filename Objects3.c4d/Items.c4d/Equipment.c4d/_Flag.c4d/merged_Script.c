/*-- Flagge --*/


private func Flying()
{
  SetDir(BoundBy(GetWind()/10+4,0,8));
  if (!GetActTime())
  {
    SetCategory(31 & GetCategory(GetActionTarget()));
    SetObjectOrder (GetActionTarget());
  }
  return(1);
}

func ResetCategory()
{
  SetCategory(2576);
  return 1;
}

func OnOwnerChanged(int new_owner, int old_owner)
{
  // Flagge hat den Besitzer verloren? Dann runterfallen!
  if (new_owner == NO_OWNER) SetAction("Idle");
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
FlyBase = {
	Prototype = Action,
	Name = "FlyBase",
	Procedure = DFA_ATTACH,
	Directions = 9,
	Length = 6,
	Delay = 3,
	X = 0,
	Y = 12,
	Wdt = 24,
	Hgt = 12,
	NextAction = "FlyBase",
	StartCall = "Flying",
	AbortCall = "ResetCategory",
},

};
