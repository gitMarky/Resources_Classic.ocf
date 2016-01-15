/*-- Batterie --*/


/* Aufschlag */

protected func Hit()
{
  Sound("MetalHit*");
}

/* Produkteigenschaften */

public func IsChemicalProduct() { return(1); }

/* Forschung */

public func GetResearchBase() { return(ACT3); }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local Collectible = 1;
