/*-- Beton --*/


protected func Hit()
{
  CastPXS("Rock",100,30);
  RemoveObject();
  return(1);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local Collectible = 1;
