/*-- Brandpfeil --*/


#include ARRW

public func Launch()
{
  Incinerate();
  return(_inherited() );
}

public func HitTarget(pObject)
{
 if(!_inherited(pObject))return(0);
 // Objekt moeglicherweise anzuenden?
 var iContactInc=GetDefCoreVal("ContactIncinerate","DefCore",GetID(pObject));
 if(iContactInc && !Random(iContactInc) && !Random(3))
 {
  Incinerate(pObject);
 }
 return(1);
}

/* Pfeileigenschaften */
public func PackTo() { return(FARP); }
public func ArrowStrength() { return(2+Random(2)); }
public func ArrowTumbleRandom() { return(3); }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local Collectible = 1;
local BlastIncinerate = 1;
local ContactIncinerate = 1;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Shot = {
	Prototype = Action,
	Name = "Shot",
	Length = 1,
	Delay = 1,
	FacetBase = 1,
	NextAction = "Hold",
	PhaseCall = "InFlight",
},

Stick = {
	Prototype = Action,
	Name = "Stick",
	Procedure = DFA_FLOAT,
	Length = 1,
	Delay = 1,
	FacetBase = 1,
	NextAction = "Hold",
	PhaseCall = "Sticking",
},

};
