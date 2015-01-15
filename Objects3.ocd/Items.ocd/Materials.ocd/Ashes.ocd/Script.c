/*--- Asche ---*/


func Hit() {
	CastPXS("Ashes",100,20);
	RemoveObject();
}

func IsAlchemContainer() { return(true); }
func AlchemProcessTime() { return(60); }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local Collectible = 1;
