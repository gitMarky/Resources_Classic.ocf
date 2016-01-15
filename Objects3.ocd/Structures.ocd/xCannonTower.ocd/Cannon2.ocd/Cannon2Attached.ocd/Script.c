/*--- Artilleriegeschütz (angeschraubt) ---*/


#include CTW2

/* Einige andere Eigenschaften */

protected func RotationSpeed() { return(1); }
protected func CannonMobileID() { return(CTW5); }
protected func CannonAmmo(object obj) { return((GetOCF(obj) & OCF_Collectible()) || (GetOCF(obj) & OCF_CrewMember()) ); }
protected func CannonPowderNeeded(object obj) { return(2 + 2 * ((GetOCF(obj) & OCF_CrewMember()) != 0) ); }
protected func CannonPower(object obj) { return(20 - 2 * ((GetOCF(obj) & OCF_CrewMember()) != 0) ); }
protected func CannotShootMenuName(object obj) { return Format("$TxtShootsn$", obj->GetName(), CannonPowderNeeded(obj)); }


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Attaching = {
	Prototype = Action,
	Name = "Attaching",
	Procedure = DFA_ATTACH,
	Delay = 15,
	FacetBase = 1,
	NextAction = "Attaching",
},

Rotating = {
	Prototype = Action,
	Name = "Rotating",
	Procedure = DFA_ATTACH,
	Delay = 15,
	FacetBase = 1,
	NextAction = "Rotating",
	Sound = "CannonRotation",
},

};
