/*--- Flammenwerfer (angeschraubt) ---*/


#include CTW2

local FillLevel;

protected func RotationSpeed() { return(2); }
protected func CannonMobileID() { return(ACT1); }

/* Turm weg und Munitionscheck */

public func ComEnter(object pAmmo)
{
  // Ölfasser in Munition umwandeln
  if(GetID(pAmmo) == OBRL)
  {
    Sound("Click");
    FillLevel += pAmmo->OBRL::GetAmount();
    pAmmo->OBRL::BarrelDoFill(-pAmmo->OBRL::GetAmount());
    ChangeDef(pAmmo->EmptyBarrelID(),pAmmo);
  }
}

public func ComFire(object pClonk)
{
  // Rotation stoppen
  Sound("Click");
  SetAction("Attaching", GetActionTarget());
  SetRDir(0);
  
  // Öl suchen
  var ammo = FindContents(OBRL,GetActionTarget());
  if(ammo) ComEnter(ammo);
  
  // Muni aus Öl erzeugen
  if(FillLevel < 50) return(Sound("Error") );
  FillLevel -= 50;
  ammo = CreateContents(ADM2);
  
  // Controller setzen (Killverfolgung)
  ammo->SetController(pClonk->GetController());
  
  // Muni ausspucken
  Exit(ammo, Sin(GetR(), 18), -Cos(GetR(), 18), GetR(), Sin(GetR(), 5), -Cos(GetR(), 5), 35);
  ammo->Launch();
  Sound("FlameThrower");
}

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
