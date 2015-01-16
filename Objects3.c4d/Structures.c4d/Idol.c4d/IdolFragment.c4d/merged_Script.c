
local living_time;	// Lebenszeit

protected func Initialize() {
  SetAction("Be");
}

public func Set(phase) {
  SetPhase(phase);
  var width = GetDefCoreVal("Width", "DefCore", GetID());
  var height = GetDefCoreVal("Height", "DefCore", GetID());
  SetPicture(width*phase, 0, width, height);
}

protected func SellTo() {
  return(GetComponent(0, 0));
}

// Timercall
protected func Timer() {
  if (living_time++ > 60*5) {
    Split2Components();
  }
}

protected func Hit() {
  Sound("RockHit*");
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
Be = {
	Prototype = Action,
	Name = "Be",
	Length = 3,
	X = 0,
	Y = 0,
	Wdt = 15,
	Hgt = 13,
},

};
