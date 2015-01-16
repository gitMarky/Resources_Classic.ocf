/*-- Aquaclonk --*/


#include CLNK

// Pr�-CE-Aquaclonks hatten schlechtere Physicals
private func UpdatePhysical (string phys) 
  {
  if (GetPhysical (phys, 1) < GetPhysical (phys, 0, 0, GetID ())) SetPhysical (phys, GetPhysical (phys, 0, 0, GetID ()), 1);
  }

protected func Initialize(a,b,c)
  {
  inherited (a,b,c);
  UpdatePhysical ("Breath");
  UpdatePhysical ("Walk");
  UpdatePhysical ("Scale");
  UpdatePhysical ("Hangle");
  UpdatePhysical ("Dig");
  UpdatePhysical ("Push");
  UpdatePhysical ("Fight");
  }

// Zur Sicherheit, damit �berladungen keinen Fehler beim Starten geben
protected func Scaling()
  {
  var szDesiredAction;
  if (GetYDir()>0) szDesiredAction = "ScaleDown"; else szDesiredAction = "Scale";
  if (GetAction() ne szDesiredAction) SetAction(szDesiredAction);
  return(1);   
  }

protected func CheckStuck()
{                   
  // Verhindert Festh�ngen am Mittelvertex
  if(!GetXDir()) if(Abs(GetYDir()) < 5)
    if(GBackSolid(0, 3))
      SetPosition(GetX(), GetY() + 1);
}

protected func ContactBottom()
  {
  if (SEqual(GetAction(), "Swim"))
    SetAction("Walk");
  return(1);
  }
  

/* Status */

public func IsAquaClonk() { return true; }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local NoBurnDecay = 1;
local ContactIncinerate = 1;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Walk = {
	Prototype = Action,
	Name = "Walk",
	Procedure = DFA_WALK,
	Directions = 2,
	FlipDir = 1,
	Length = 16,
	Delay = 15,
	X = 0,
	Y = 0,
	Wdt = 16,
	Hgt = 20,
	NextAction = "Walk",
	StartCall = "None",
},

Scale = {
	Prototype = Action,
	Name = "Scale",
	Procedure = DFA_SCALE,
	Directions = 2,
	FlipDir = 1,
	Length = 16,
	Delay = 15,
	X = 0,
	Y = 20,
	Wdt = 16,
	Hgt = 20,
	NextAction = "Scale",
	StartCall = "Scaling",
},

ScaleDown = {
	Prototype = Action,
	Name = "ScaleDown",
	Procedure = DFA_SCALE,
	Directions = 2,
	FlipDir = 1,
	Length = 16,
	Reverse = 1,
	Delay = 15,
	X = 0,
	Y = 20,
	Wdt = 16,
	Hgt = 20,
	NextAction = "ScaleDown",
	StartCall = "Scaling",
},

Tumble = {
	Prototype = Action,
	Name = "Tumble",
	Procedure = DFA_FLIGHT,
	Directions = 2,
	FlipDir = 1,
	Length = 16,
	Delay = 1,
	X = 0,
	Y = 40,
	Wdt = 16,
	Hgt = 20,
	NextAction = "Tumble",
	EndCall = "CheckStuck",
	InLiquidAction = "Swim",
	ObjectDisabled = 1,
},

Dig = {
	Prototype = Action,
	Name = "Dig",
	Procedure = DFA_DIG,
	Directions = 2,
	FlipDir = 1,
	Length = 16,
	Delay = 15,
	X = 0,
	Y = 60,
	Wdt = 16,
	Hgt = 20,
	NextAction = "Dig",
	StartCall = "Digging",
	DigFree = 11,
},

Bridge = {
	Prototype = Action,
	Name = "Bridge",
	Procedure = DFA_BRIDGE,
	Directions = 2,
	FlipDir = 1,
	Length = 16,
	Delay = 1,
	X = 0,
	Y = 60,
	Wdt = 16,
	Hgt = 20,
	NextAction = "Bridge",
	StartCall = "Digging",
},

Swim = {
	Prototype = Action,
	Name = "Swim",
	Procedure = DFA_SWIM,
	Directions = 2,
	FlipDir = 1,
	Length = 16,
	Delay = 15,
	X = 0,
	Y = 80,
	Wdt = 16,
	Hgt = 20,
	NextAction = "Swim",
},

Hangle = {
	Prototype = Action,
	Name = "Hangle",
	Procedure = DFA_HANGLE,
	Directions = 2,
	FlipDir = 1,
	Length = 11,
	Delay = 16,
	X = 0,
	Y = 100,
	Wdt = 16,
	Hgt = 20,
	NextAction = "Hangle",
},

Jump = {
	Prototype = Action,
	Name = "Jump",
	Procedure = DFA_FLIGHT,
	Directions = 2,
	FlipDir = 1,
	Length = 8,
	Delay = 3,
	X = 0,
	Y = 120,
	Wdt = 16,
	Hgt = 20,
	NextAction = "Hold",
	PhaseCall = "CheckStuck",
	InLiquidAction = "Swim",
},

KneelDown = {
	Prototype = Action,
	Name = "KneelDown",
	Procedure = DFA_KNEEL,
	Directions = 2,
	FlipDir = 1,
	Length = 4,
	Delay = 1,
	X = 0,
	Y = 140,
	Wdt = 16,
	Hgt = 20,
	NextAction = "KneelUp",
	StartCall = "None",
},

KneelUp = {
	Prototype = Action,
	Name = "KneelUp",
	Procedure = DFA_KNEEL,
	Directions = 2,
	FlipDir = 1,
	Length = 4,
	Delay = 1,
	X = 64,
	Y = 140,
	Wdt = 16,
	Hgt = 20,
	NextAction = "Walk",
	StartCall = "None",
},

Dive = {
	Prototype = Action,
	Name = "Dive",
	Procedure = DFA_FLIGHT,
	Directions = 2,
	FlipDir = 1,
	Length = 8,
	Delay = 4,
	X = 0,
	Y = 160,
	Wdt = 16,
	Hgt = 20,
	NextAction = "Hold",
	StartCall = "None",
	PhaseCall = "CheckStuck",
	InLiquidAction = "Swim",
	ObjectDisabled = 1,
},

FlatUp = {
	Prototype = Action,
	Name = "FlatUp",
	Procedure = DFA_KNEEL,
	Directions = 2,
	FlipDir = 1,
	Length = 8,
	Delay = 1,
	X = 0,
	Y = 180,
	Wdt = 16,
	Hgt = 20,
	NextAction = "KneelUp",
	ObjectDisabled = 1,
},

Throw = {
	Prototype = Action,
	Name = "Throw",
	Procedure = DFA_THROW,
	Directions = 2,
	FlipDir = 1,
	Length = 8,
	Delay = 1,
	X = 0,
	Y = 200,
	Wdt = 16,
	Hgt = 20,
	NextAction = "Walk",
},

Punch = {
	Prototype = Action,
	Name = "Punch",
	Procedure = DFA_FIGHT,
	Directions = 2,
	FlipDir = 1,
	Length = 8,
	Delay = 2,
	X = 0,
	Y = 220,
	Wdt = 16,
	Hgt = 20,
	NextAction = "Fight",
	EndCall = "Punching",
	ObjectDisabled = 1,
},

Dead = {
	Prototype = Action,
	Name = "Dead",
	Directions = 2,
	FlipDir = 1,
	Length = 6,
	Delay = 3,
	X = 0,
	Y = 240,
	Wdt = 16,
	Hgt = 20,
	NextAction = "Hold",
	NoOtherAction = 1,
	ObjectDisabled = 1,
},

Ride = {
	Prototype = Action,
	Name = "Ride",
	Procedure = DFA_ATTACH,
	Directions = 2,
	FlipDir = 1,
	Length = 4,
	Delay = 3,
	X = 128,
	Y = 120,
	Wdt = 16,
	Hgt = 20,
	NextAction = "Ride",
	StartCall = "Riding",
},

RideStill = {
	Prototype = Action,
	Name = "RideStill",
	Procedure = DFA_ATTACH,
	Directions = 2,
	FlipDir = 1,
	Length = 1,
	Delay = 10,
	X = 128,
	Y = 120,
	Wdt = 16,
	Hgt = 20,
	NextAction = "RideStill",
	StartCall = "Riding",
},

Push = {
	Prototype = Action,
	Name = "Push",
	Procedure = DFA_PUSH,
	Directions = 2,
	FlipDir = 1,
	Length = 8,
	Delay = 15,
	X = 128,
	Y = 140,
	Wdt = 16,
	Hgt = 20,
	NextAction = "Push",
},

Chop = {
	Prototype = Action,
	Name = "Chop",
	Procedure = DFA_CHOP,
	Directions = 2,
	FlipDir = 1,
	Length = 8,
	Delay = 3,
	X = 128,
	Y = 160,
	Wdt = 16,
	Hgt = 20,
	NextAction = "Chop",
	StartCall = "Chopping",
},

Fight = {
	Prototype = Action,
	Name = "Fight",
	Procedure = DFA_FIGHT,
	Directions = 2,
	FlipDir = 1,
	Length = 7,
	Delay = 4,
	X = 128,
	Y = 180,
	Wdt = 16,
	Hgt = 20,
	NextAction = "Fight",
	StartCall = "Fighting",
	ObjectDisabled = 1,
},

GetPunched = {
	Prototype = Action,
	Name = "GetPunched",
	Procedure = DFA_FIGHT,
	Directions = 2,
	FlipDir = 1,
	Length = 8,
	Delay = 3,
	X = 128,
	Y = 200,
	Wdt = 16,
	Hgt = 20,
	NextAction = "Fight",
	ObjectDisabled = 1,
},

Build = {
	Prototype = Action,
	Name = "Build",
	Procedure = DFA_BUILD,
	Directions = 2,
	FlipDir = 1,
	Length = 8,
	Delay = 2,
	X = 128,
	Y = 220,
	Wdt = 16,
	Hgt = 20,
	NextAction = "Build",
	StartCall = "Building",
},

RideThrow = {
	Prototype = Action,
	Name = "RideThrow",
	Procedure = DFA_ATTACH,
	Directions = 2,
	FlipDir = 1,
	Length = 8,
	Delay = 1,
	X = 128,
	Y = 240,
	Wdt = 16,
	Hgt = 20,
	NextAction = "Ride",
	StartCall = "Throwing",
},

Process = {
	Prototype = Action,
	Name = "Process",
	Procedure = DFA_THROW,
	Directions = 2,
	FlipDir = 1,
	Length = 8,
	Delay = 3,
	X = 0,
	Y = 260,
	Wdt = 16,
	Hgt = 20,
	NextAction = "Process",
	EndCall = "Processing",
},

Drink = {
	Prototype = Action,
	Name = "Drink",
	Procedure = DFA_THROW,
	Directions = 2,
	FlipDir = 1,
	Length = 8,
	Delay = 3,
	X = 128,
	Y = 260,
	Wdt = 16,
	Hgt = 20,
	NextAction = "Walk",
},

};
