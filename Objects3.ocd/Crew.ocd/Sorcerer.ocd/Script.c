/* Magier */


#include MCLK

/* Nach dem Zaubern... */  
  
protected func AfterMagic()
{
  // Callback nach Magie-Animation: Nach weiteren Kristallen suchen
  CheckContents();
  // Ursprungs-Funktion aufrufen, wenn vorhanden
  return(_inherited() );
}

protected func AfterMagicJump()
{
  // Geth nicht mit inherited weil sonst nicht obiges AfterMagic aufgerufen wird
  if(idCurSpell && GetAction() S= "Walk")
  {
    SetAction("Magic");
    SetPhase(iCurPhase);
  }
  else AfterMagic();
}

/* Energiegewinnung */

// Dummies
public func GetManaGain() {}
public func IsMagicCrystal() {}


// Dummies
public func GetManaGain() {}
public func IsMagicCrystal() {}

private func ConvertCrystal(object pObj)
  {
  if (!IsConvertReady()) return();
  if (!pObj->~Apply(this()))
    {
    var iManaGain = pObj->~GetManaGain(this());
    if (!iManaGain) iManaGain = 10;
    if (!DoMagicEnergy(iManaGain)) return();
    RemoveObject(pObj);
    }
  SetComDir(COMD_Stop());
  SetMagicAction();
  Sound("Electric");
  PlayerMessage(GetOwner(), "", this());
  }

protected func CheckContents()
  {
  // Walk-Startcall vom MagiClonk
  ReAim();
  // Alle Kristalle konvertieren
  var i=ContentsCount(), o;
  while (i--) if (o=Contents(i)) if (GetID(o)==CRYS || o->~IsMagicCrystal(this()))
    ConvertCrystal(o);
  }
  
/* Aufnahme */

protected func Collection2(object pObj)
  {
  return(CheckContents());
  }


/* Während des Reitens... */

private func Riding()
{
  CheckContents();
  return(_inherited());
}

/* Vom Blitz getroffen */

public func LightningStrike()
{
  // Wenn der Clonk tot ist, zerstört ihn der erste Blitz
  if (GetAction() eq "Dead")
    {
    CastObjects(SPRK,5,20);
    CreateParticle("MSpark", 0,0, 1000, RGBa(50,50,255,150));
    if (!GetAlive()) RemoveObject();
    return(true);
  }
  // Clonk soll anhalten
  SetComDir(COMD_Stop());
  // Energiegewinnung
  for(var i = 0; i < 10; ++ i) DoMagicEnergy(1);
  // Sound
  Sound("Electric");
  // Effekt-Aktion (wenn's gerade passt)
  if (IsConvertReady())
    SetMagicAction();
  // Fertig
  return(1);
}

public func IsConvertReady()
{
  // Im Laufen und Reiten können Kristalle umgewandelt werden
  return(GetAction() S= "Walk" || GetAction() S= "Ride" || GetAction() S= "RideStill");
}  


/* Zur Sicherheit, damit Überladungen keinen Fehler beim Starten geben */

protected func Scaling()
  {
  var szDesiredAction;
  if (GetYDir()>0) szDesiredAction = "ScaleDown"; else szDesiredAction = "Scale";
  if (GetAction() ne szDesiredAction) SetAction(szDesiredAction);
  return(1);   
  }

/* Verhindert das Feststecken */

protected func CheckStuck()
{                   
  // Verhindert Festhängen am Mittelvertex
  if(!GetXDir()) if(Abs(GetYDir()) < 5)
    if(GBackSolid(0, 3))
      SetPosition(GetX(), GetY() + 1);
}


/* Status */

public func IsSorcerer() { return(1); }

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
	StartCall = "CheckContents",
	InLiquidAction = "Swim",
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
	InLiquidAction = "Swim",
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
	InLiquidAction = "Swim",
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
	InLiquidAction = "Swim",
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
	EndCall = "CheckMagicStart",
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

DiveBack = {
	Prototype = Action,
	Name = "DiveBack",
	Procedure = DFA_FLIGHT,
	Directions = 2,
	FlipDir = 1,
	Length = 8,
	Reverse = 1,
	Delay = 1,
	X = 0,
	Y = 160,
	Wdt = 16,
	Hgt = 20,
	NextAction = "Dive",
	StartCall = "None",
	EndCall = "CheckMagicStart",
	PhaseCall = "CheckStuck",
	AbortCall = "AbortSpell",
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
	InLiquidAction = "Swim",
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
	InLiquidAction = "Swim",
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
	InLiquidAction = "Swim",
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
	InLiquidAction = "Swim",
},

Magic = {
	Prototype = Action,
	Name = "Magic",
	Procedure = DFA_THROW,
	Directions = 2,
	FlipDir = 1,
	Length = 16,
	Delay = 1,
	X = 0,
	Y = 260,
	Wdt = 16,
	Hgt = 24,
	OffX = 0,
	OffY = -4,
	NextAction = "Walk",
	EndCall = "AfterMagic",
	PhaseCall = "CheckMagic",
	AbortCall = "AfterMagic",
},

JumpMagic = {
	Prototype = Action,
	Name = "JumpMagic",
	Procedure = DFA_FLIGHT,
	Directions = 2,
	FlipDir = 1,
	Length = 16,
	Delay = 1,
	X = 0,
	Y = 260,
	Wdt = 16,
	Hgt = 24,
	OffX = 0,
	OffY = -4,
	NextAction = "Jump",
	EndCall = "AfterMagic",
	PhaseCall = "CheckMagic",
	AbortCall = "AfterMagicJump",
},

RideMagic = {
	Prototype = Action,
	Name = "RideMagic",
	Procedure = DFA_ATTACH,
	Directions = 2,
	FlipDir = 1,
	Length = 16,
	Delay = 1,
	X = 0,
	Y = 284,
	Wdt = 16,
	Hgt = 24,
	OffX = 0,
	OffY = -4,
	NextAction = "Ride",
	EndCall = "AfterMagic",
	PhaseCall = "CheckMagic",
	AbortCall = "AfterMagic",
	InLiquidAction = "Swim",
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
	InLiquidAction = "Swim",
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
	InLiquidAction = "Swim",
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
	InLiquidAction = "Swim",
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
	Y = 308,
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
	Y = 308,
	Wdt = 16,
	Hgt = 20,
	NextAction = "Walk",
},

AimMagic = {
	Prototype = Action,
	Name = "AimMagic",
	Procedure = DFA_THROW,
	Directions = 2,
	FlipDir = 1,
	Length = 10,
	Delay = 0,
	X = 0,
	Y = 328,
	Wdt = 24,
	Hgt = 20,
	OffX = -4,
	NextAction = "AimMagic",
},

};
