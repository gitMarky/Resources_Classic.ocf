/*-- Säurefass --*/


#include BARL

// Fassdaten
public func BarrelMaterial() { return(Material("Acid")); }
public func BarrelMaterialName() { return("Acid"); }

// Fassermittlungskette
global func GetBarrelType(iMaterial)
{
  if (iMaterial == Material("Acid")) return(ABRL);
  return(_inherited(iMaterial));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local Collectible = 1;
