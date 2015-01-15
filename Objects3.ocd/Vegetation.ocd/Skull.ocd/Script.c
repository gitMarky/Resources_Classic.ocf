/*-- Schädel --*/


protected func Hit()
{
  Sound("WoodHit*");
}

func IsAlchemContainer() { return(true); }
func AlchemProcessTime() { return(140); }

func IsManaContainer() { return(true); }
func ManaProcessTime() { return(500); }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local Collectible = 1;
