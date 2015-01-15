/*--- Schwefel ---*/


protected func Hit()
{
  Sound("WoodHit*");
  return(1);
}

func Incineration()
{
  SetClrModulation (RGB(96,64,64));
}

func IsAlchemContainer() { return(true); }
func AlchemProcessTime() { return(60); }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local Collectible = 1;
local BlastIncinerate = 50;
