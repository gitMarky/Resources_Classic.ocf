/*-- Segelboot --*/


/* Initialisierung */

protected func Initialize() { SetAction("Sailing"); }

/* Steuerung */

protected func ControlLeft(object clonk)
{
  [$TxtLeft$|Image=SLB1:0]
  if(!GetPlrJumpAndRunControl(clonk->GetController()))
    SetComDir(COMD_Left);

  return(1);
}

protected func ControlRight(object clonk)
{
  [$TxtRight$|Image=SLB1:1]
  if(!GetPlrJumpAndRunControl(clonk->GetController()))
    SetComDir(COMD_Right);

  return(1);
}

protected func ControlUpdate(object clonk, int comdir)
{
  if(comdir == COMD_UpLeft || comdir == COMD_Left || comdir == COMD_DownLeft)
    SetComDir(COMD_Left);
  else if(comdir == COMD_UpRight || comdir == COMD_Right || comdir == COMD_DownRight)
    SetComDir(COMD_Right);
  else
    SetComDir(COMD_Stop);
}

protected func ControlUpDouble()
{
  [$TxtLand$|Image=SLB1:2]
  if (GetAction()S="Sailing")
    SetAction("RaiseSail");
  return(1);
}

protected func ControlCommand(string szCommand, object pTarget, int iX, int iY)
{
  // Bewegungskommando (nur links/rechts auswerten)
  if(szCommand eq "MoveTo")
    return(Command2Control(iX,iY));
}

private func Command2Control(int iX, int iY)
{
  // nur X wird ausgewertet
  if(iX>GetX()) SetComDir(COMD_Right);
  if(iX<GetX()) SetComDir(COMD_Left);
  return(1);
}

/* Segeln */

private func Wind2Sail()
{
  // Kein Steuermann
  if (!FindObject(0,0,0,0,0,0,"Push",this()))
    SetComDir(COMD_None());
  // Geschwindigkeit und Bewegung
  var wind_push = BoundBy(GetWind() / 4, -10, +10);
  var xdir = 7 + wind_push / 5; /* windabhängige X-Dir */
  if (GetComDir() == COMD_None())
    SetXDir(wind_push);
  if (GetComDir() == COMD_Left())
    SetXDir(-xdir);
  if (GetComDir() == COMD_Right())
    SetXDir(+xdir);
}

private func LandOn()
{  
  ChangeDef(SLBT);
  SetComDir(COMD_None());
  SetAction("JustLanded");
}

/* Sounds */

private func SoundSailDown() { Sound("SailDown"); }
private func SoundSailUp()   { Sound("SailUp");   }


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local BlastIncinerate = 35;
local BurnTo = SLBB;
local ContactIncinerate = 5;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Sailing = {
	Prototype = Action,
	Name = "Sailing",
	Delay = 20,
	X = 0,
	Y = 0,
	Wdt = 36,
	Hgt = 44,
	NextAction = "Sailing",
	StartCall = "Wind2Sail",
},

LowerSail = {
	Prototype = Action,
	Name = "LowerSail",
	Length = 10,
	Reverse = 1,
	Delay = 1,
	X = 0,
	Y = 0,
	Wdt = 36,
	Hgt = 44,
	NextAction = "Sailing",
	StartCall = "SoundSailDown",
},

RaiseSail = {
	Prototype = Action,
	Name = "RaiseSail",
	Length = 10,
	Delay = 1,
	X = 0,
	Y = 0,
	Wdt = 36,
	Hgt = 44,
	StartCall = "SoundSailUp",
	EndCall = "LandOn",
},

};
