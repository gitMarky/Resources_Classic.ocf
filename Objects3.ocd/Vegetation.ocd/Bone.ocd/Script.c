/*-- Knochen --*/
// BBON-Effekt wird ggf. vom Bisonknochen (Western) angehaengt


protected func Hit()
{
  Sound("WoodHit*");
}

func IsAlchemContainer() { if(GetID() != BONE && GetID() != BBON) return(false); return(true); }
func AlchemProcessTime() { if(GetID() != BONE && GetID() != BBON) return(false); if(GetEffect("BBON", this()) || GetID() == BBON) return(140); return(120); }

func IsManaContainer() { if(GetID() != BONE && GetID() != BBON) return(false); return(true); }
func ManaProcessTime() { if(GetID() != BONE && GetID() != BBON) return(false); if(GetEffect("BBON", this()) || GetID() == BBON) return(280); return(240); }

protected func SellTo() {
  if(GetEffect("BBON", this())) return(BBON);
  return(GetID());
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
BBON = {
	Prototype = Action,
	Name = "BBON",
	Length = 1,
	Delay = 0,
	X = 0,
	Y = 0,
	Wdt = 10,
	Hgt = 6,
	OffX = -1,
},

};
