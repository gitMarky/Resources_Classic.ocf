/*-- Nest --*/


local pTree;

protected func Initialize()
{
  SetAction("Be");
  return(1);
}

private func Check4Tree()
{
  // Baum noch da?	
  if(pTree)	
   if(!OnFire(pTree))  
    if(!(GetCategory(pTree) & C4D_Vehicle))
      return(1);      	    
  SetAction("Decay");
  SetCategory(C4D_Vehicle());
  // Ei benachrichtigen
  var pEgg;
  if(pEgg = FindObject(BEGG, 0, 0, 0, 0, 0, 0, this())) pEgg->SetAction("Idle");
  return(1);
}

protected func Incineration()
{
  SetAction("Decay");
  SetCategory(C4D_Vehicle());
  // Ei benachrichtigen
  var pEgg;
  if(pEgg = FindObject(BEGG, 0, 0, 0, 0, 0, 0, this())) pEgg->SetAction("Idle");
  return(1);
}

public func RejectCollect(pObj, pID)
{
  if(pID == BIRD) return(0);
  return(1);
}

public func Breed()
{
  var pBird = FindContents(BIRD);
  if (pBird) pBird->LayEgg(); else SetAction("Be");
}

public func Ejection()
{
  SetAction("Be");	
}

private func Hit()
{
  if (GetAction()!="Decay")  SetAction("Decay");
  return(1);
}

protected func ActivateEntrance()
{
  SetEntrance(1);
  return(1);
}

private func Remove()
{
  return(RemoveObject());
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local BlastIncinerate = 10;
local ContactIncinerate = 1;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Be = {
	Prototype = Action,
	Name = "Be",
	Procedure = DFA_FLOAT,
	Directions = 1,
	Length = 1,
	Delay = 10,
	X = 0,
	Y = 0,
	Wdt = 20,
	Hgt = 11,
	NextAction = "Be",
	InLiquidAction = "Decay",
},

Bird = {
	Prototype = Action,
	Name = "Bird",
	Procedure = DFA_FLOAT,
	Directions = 1,
	Length = 1,
	Delay = 1000,
	X = 0,
	Y = 11,
	Wdt = 30,
	Hgt = 16,
	OffX = -4,
	OffY = -5,
	NextAction = "Be",
	EndCall = "Breed",
	InLiquidAction = "Decay",
},

};
