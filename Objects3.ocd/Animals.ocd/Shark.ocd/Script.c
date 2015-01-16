/*-- Hai --*/

#include ANIM

public func IsPossessible() { return(1); }

/* Initialisierung */

protected func Initialize() { return(Birth()); }

/* TimerCall mit KI-Steuerung */

protected func Activity() 
{
  // Die KI-Steuerung wird bei Besessenheit nicht gebraucht
  if (GetEffect("PossessionSpell", this())) return();

  // Nicht an der Wasseroberfl�che bleiben
  if (!GBackLiquid(0, -8) && GetAction() ne "Walk") 
    return(SetComDir(BoundBy(GetComDir(), COMD_DownRight(), COMD_DownLeft())));

  // Nichts machen
  if (Random(2)) return(1);

  // Nur wenn der Hai schwimmt
  if (GetAction() ne "Swim") return(1);

  // Umdrehen
  if (Random(2)) TurnRight();
  else TurnLeft();

  // Anderen Haien aus dem Weg gehen
  var obj;
  if (obj = FindObject(GetID(), -100, -25, 200, 50, 0, "Swim", 0, NoContainer())) 
  {
    if (GetY(obj) < GetY()) SetComDir(BoundBy(GetComDir(), COMD_DownRight(), COMD_DownLeft()));
    else if (GetComDir() == COMD_Right()) SetComDir(COMD_UpRight());
    else SetComDir(COMD_UpLeft());
  }
}

private func SwimStart() 
{
  // Die KI-Steuerung wird bei Besessenheit nicht gebraucht
  if (GetEffect("PossessionSpell", this())) return();

  // Beute am Maul bei�en
  if (Attack()) return();
  
  // Beute in Entfernung suchen
  var pPrey;
  if (pPrey = FindPrey())
  {
    // Immer von hinten mit einem Abstand angreifen
    var iFromSide = +1; if (GetDir(pPrey)) iFromSide = -1;
    SetCommand(this(), "MoveTo", 0, GetX(pPrey) + 15 * iFromSide, GetY(pPrey));
  }
}

private func Swimming()
{
  // Die KI-Steuerung wird bei Besessenheit nicht gebraucht
  if (GetEffect("PossessionSpell", this())) return();

  // Vertikale Geschwindigkeit begrenzen
  SetYDir(GetYDir(0, 100), 0, 120);
  // Nicht gegen den Beckenrand schwimmen
  if (GBackSolid(+75, 0))
  {
    TurnLeft();
    if (!Random(5)) SetComDir(COMD_UpLeft());
    else if (!Random(6)) SetComDir(COMD_DownLeft());
    else SetComDir(COMD_Left());
    return();
  }
  if (GBackSolid(-75, 0)) 
  {
    TurnRight();
    if (!Random(5)) SetComDir(COMD_UpRight());
    else if (!Random(6)) SetComDir(COMD_DownRight());
    else SetComDir(COMD_Right());
    return();
  }
}

private func FindPrey()
{
  var prey;      
  // Zuerst schwimmende Beute suchen...
  prey = FindObject(0, -250, -100, 500, 200, OCF_Prey(), "Swim", 0, NoContainer());
  // ...dann auch andere Beute im Wasser suchen (z.B. stehende Aquaclonks)
  if (!prey)
  {
    while (prey = FindObject(0, -250, -100, 500, 200, OCF_Prey(), 0, 0, NoContainer(), prey))
      if (GetAlive(prey))
        if (InLiquid(prey))
          break;
  }  
  // Gefundene Beute zur�ckliefern
  return(prey);  
}

/* Kontakte */

protected func ContactLeft()
{
  // Die KI-Steuerung wird bei Besessenheit nicht gebraucht
  if (GetEffect("PossessionSpell", this())) return();

  return(TurnRight());
}
  
protected func ContactRight()
{
  // Die KI-Steuerung wird bei Besessenheit nicht gebraucht
  if (GetEffect("PossessionSpell", this())) return();

  return(TurnLeft());
}

protected func ContactTop()
{
  // Die KI-Steuerung wird bei Besessenheit nicht gebraucht
  if (GetEffect("PossessionSpell", this())) return();

  return(SetComDir(COMD_Down()));
}

protected func ContactBottom()
{
  // Die KI-Steuerung wird bei Besessenheit nicht gebraucht
  if (GetEffect("PossessionSpell", this())) return();

  if (GetAction() ne "Walk") SetComDir(COMD_Up());
  if (Random(10)) SetComDir(COMD_Right());
  if (Random(10)) SetComDir(COMD_Left());
  return(1);
}

/* Aktionen */

private func TurnRight()
{
  if (Stuck() || (GetAction() ne "Walk" && GetAction() ne "Swim")) return();
  if (GetXDir() < 0) SetXDir(0);
  SetDir(DIR_Right());
  SetComDir(COMD_Right());
  return(1);
}

private func TurnLeft()
{
  if (Stuck() || (GetAction() ne "Walk" && GetAction() ne "Swim")) return();
  if (GetXDir() > 0) SetXDir(0);
  SetDir(DIR_Left());
  SetComDir(COMD_Left());
  return(1);
}

private func Attack()
{
  // W�hrend des Schwimmens kann alle 2 Sekunden einmal gebissen werden
  if (GetEffect("IntAttackDelay", this()) || GetAction() ne "Swim") return();
  
  // Beute suchen
  var pPrey = FindObject2(Find_AtRect(40*GetDir()-25,0,10,10), Find_OCF(OCF_Prey), Find_OCF(OCF_Alive), Find_NoContainer(), Find_Layer(GetObjectLayer()), Find_Exclude(this));
  if (!pPrey) return();
  
  // Bei�en :D
  Punch(pPrey, 8);
  SetAction("Jaw");
  Sound("Munch1");
  AddEffect("IntAttackDelay", this(), 1, 70);
  return(1);
}

/* Einwirkungen */

public func Eat(pByObject)
{
  pByObject->~Feed(100);
  RemoveObject();
  return(1);
}

protected func Death()
{
  SetDir(0);
  ChangeDef(DSHK);
  SetAction("Dead");
  return(1);
}

/* Vermehrung */

private func MaxAnimalCount() { return(4); }

private func SpecialReprodCond()
{
  return(GetAction() eq "Swim");
}

public func Birth()
{
  SetAction("Swim");
  SetComDir(COMD_Left());
  if(Random(2)) SetComDir(COMD_Right());
}

/* Steuerung durch Besessenheit */

protected func ControlCommand(szCommand, pTarget, iTx, iTy)
{
 // Bewegungskommando
 if (szCommand eq "MoveTo")
  return(SetCommand(this(),szCommand, pTarget, iTx, iTy));
 return(0);
}

protected func ContainedLeft(object caller)
{
 [$TxtMovement$]
 SetCommand(this(),"None");
 if(!GetPlrJumpAndRunControl(caller->GetController()))
  TurnLeft();
 return(1);
}

protected func ContainedRight(object caller)
{
 [$TxtMovement$]
 SetCommand(this(),"None");
 if(!GetPlrJumpAndRunControl(caller->GetController()))
  TurnRight();
 return(1);
}

protected func ContainedUp(object caller)
{
 [$TxtMovement$]
 SetCommand(this(),"None");
 if(!GetPlrJumpAndRunControl(caller->GetController()))
  SetComDir(COMD_Up());
 return(1);
}

protected func ContainedDown(object caller)
{
 [$TxtMovement$]
 SetCommand(this(),"None");
 if(Contained()) return SetCommand(this, "Exit");
 if(!GetPlrJumpAndRunControl(caller->GetController()))
  SetComDir(COMD_Down());
 return(1);
}

/* JumpAndRun-Steuerung */

private func ClearDir(bool fX)
{
  if(fX && GetXDir())
  {
    if(GetXDir() > 0) SetXDir(Max(GetXDir() - 2, 0));
    else SetXDir(Min(GetXDir() + 2, 0));
  }
  if(!fX && GetYDir())
  {
    if(GetYDir() > 0) SetYDir(Max(GetYDir() - 2, 0));
    else SetYDir(Min(GetYDir() + 2, 0));
  }
}

public func ContainedUpdate(object self, int comdir)
{
  SetComDir(comdir);
  ClearScheduleCall(this(), "ClearDir");
  if(comdir == COMD_Down || comdir == COMD_Up) ScheduleCall(this(), "ClearDir", 1, (Abs(GetXDir())+1)/2, true);
  if(comdir == COMD_Left || comdir == COMD_Right) ScheduleCall(this(), "ClearDir", 1, (Abs(GetYDir())+1)/2, false);

  return(1);
}

protected func ContainedDig()
{
 [$TxtAttack$]
 Attack();
 return(1);
}

protected func ContainedThrow() { return(1); }

protected func ContainedDigDouble()
{
 [$TxtLeave$]
 RemoveEffect("PossessionSpell", this());
 return(1);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local Placement = 1;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Swim = {
	Prototype = Action,
	Name = "Swim",
	Procedure = DFA_SWIM,
	Directions = 2,
	FlipDir = 1,
	Length = 20,
	Delay = 5,
	X = 0,
	Y = 0,
	Wdt = 56,
	Hgt = 22,
	NextAction = "Swim",
	StartCall = "SwimStart",
	PhaseCall = "Swimming",
},

Turn = {
	Prototype = Action,
	Name = "Turn",
	Procedure = DFA_SWIM,
	Directions = 2,
	FlipDir = 1,
	Length = 20,
	Delay = 3,
	X = 0,
	Y = 22,
	Wdt = 56,
	Hgt = 22,
	NextAction = "Swim",
},

Jaw = {
	Prototype = Action,
	Name = "Jaw",
	Procedure = DFA_SWIM,
	Directions = 2,
	FlipDir = 1,
	Length = 20,
	Delay = 1,
	X = 0,
	Y = 44,
	Wdt = 56,
	Hgt = 22,
	NextAction = "Swim",
},

Walk = {
	Prototype = Action,
	Name = "Walk",
	Procedure = DFA_WALK,
	Directions = 2,
	FlipDir = 1,
	Length = 20,
	Delay = 2,
	X = 0,
	Y = 0,
	Wdt = 56,
	Hgt = 22,
	NextAction = "Swim",
	InLiquidAction = "Swim",
},

};