/*-- Sprengpfeil --*/


#include ARRW

local Armed;

/* Abfeuern */

public func Launch(object pByObject)
{
  // Der Sprengpfeil wird nur durch korrektes Abfeuern scharf gemacht
  Armed = 1;    
  return(_inherited() );
}

/* Pfeileigenschaften */
public func PackTo() {  return(XARP); }
public func ArrowStrength() { return(2+Random(2)); }
public func ArrowTumbleRandom() {return(2);}
public func ArrowStopsOnHit() { return(0); }

/* Aufschlag */

protected func Hit()
{
  if (Armed)
    Explode(Random(5) + 10);
}

/* Treffer */

private func HitTarget(pTarget)
{
 if(pTarget->~IsArrowTarget(this())) return(Hit());
 
 return(_inherited(pTarget));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local Collectible = 1;

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

};
