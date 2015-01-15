/*--- Kohle ---*/


protected func Initialize()
{
  if (Stuck()) SetPosition(GetX(), GetY() - 2);
  return(1);
}

protected func Hit()
{
  Sound("RockHit*");
  return(1);
}

func IsAlchemContainer() { return(true); }
func AlchemProcessTime() { return(100); }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local Collectible = 1;
