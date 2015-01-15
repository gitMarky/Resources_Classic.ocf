/*-- Flüssig-Granit --*/


protected func Hit()
{
  CastPXS("Granite", 150, 30);
  RemoveObject();
  return(1);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local Collectible = 1;
