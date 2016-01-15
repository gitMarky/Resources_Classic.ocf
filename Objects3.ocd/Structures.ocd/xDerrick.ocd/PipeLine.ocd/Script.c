/*-- Bohrturmleitung --*/


local pDerrick;

public func Init(derrick, pipehead) 
{ 
  pDerrick = derrick; 
  SetAction("Exist", pipehead); 
}

public func Adjust()
{
  if (!GetActionTarget() || !pDerrick)
    return(RemoveObject());
  SetPosition(GetX(pDerrick), GetY(pDerrick) + GetObjHeight(pDerrick) / 2);
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
Exist = {
	Prototype = Action,
	Name = "Exist",
	Procedure = DFA_FLOAT,
	Length = 1,
	Delay = 100,
	X = 0,
	Y = 0,
	Wdt = 3,
	Hgt = 3,
	FacetTargetStretch = 1,
	NextAction = "Exist",
	StartCall = "Adjust",
},

};
