/*-- Toter Wipf --*/


/* Verwesung */

private func Decaying()
{
  DoCon(-4);
}
  
/* Aktionen von außen */  
  
public func Eat(pBy)
{
  pBy->~Feed(10);
  RemoveObject();
  return(1);
}

/* Zerlegen */

public func Activate(pClonk) {
  [$TxtEmbowel$|Image=KNFE]
  // Der Clonk soll dieses Objekt zerlegen, wenn er kann
  return(ObjectSetAction(pClonk,"Embowel",this()));
}

/* Wird zerlegt */

public func Embowel() {
  // In Bestandteile zerfallen
  Split2Components(this());
  return(1);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local Collectible = 1;
local ContactIncinerate = 1;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Dead = {
	Prototype = Action,
	Name = "Dead",
	Procedure = DFA_NONE,
	Directions = 1,
	Length = 1,
	Delay = 3000,
	X = 0,
	Y = 0,
	Wdt = 24,
	Hgt = 18,
	NextAction = "Decay",
},

};
