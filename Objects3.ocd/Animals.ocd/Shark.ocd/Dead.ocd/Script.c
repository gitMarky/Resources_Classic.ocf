/*-- Toter Hai --*/


/* Wird zerlegt */

public func Embowel()
{
  // In Bestandteile zerfallen
  Split2Components(this());
  return(1);
}

/* Verwesung */

private func Decaying()
{
  DoCon(-4);
}
  
/* Aktionen von auﬂen */  
  
public func Eat(pByObject)
{
  ObjectCall(pByObject, "Feed", 100);
  RemoveObject();
  return(1);
}
  

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local Placement = 1;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Dead = {
	Prototype = Action,
	Name = "Dead",
	Procedure = DFA_NONE,
	Directions = 2,
	FlipDir = 1,
	Length = 1,
	Delay = 3000,
	X = 0,
	Y = 0,
	Wdt = 56,
	Hgt = 22,
	NextAction = "Decay",
},

};
