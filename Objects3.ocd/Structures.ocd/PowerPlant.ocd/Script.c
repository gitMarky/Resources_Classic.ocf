/*-- Kraftwerk --*/


#include DOOR
#include BAS4

/* Initialisierung */

protected func Initialize()
{
  // Netterweise gibt's zu Beginn einmal Kohle
  CreateContents(COAL);
}

/* Eingangssteuerung */

private func SoundOpenDoor()
{
  Sound("GateOpen");
}

private func SoundCloseDoor()
{
  Sound("GateClose");
}
  
protected func Collection(object pObj)
{
  Sound("Clonk");
}

/* Produktion */

private func Burning()
{
  // Rauch
  Smoke(-15,-20,12);
  Smoke(-1,-23,8);
  // Energieerzeugung
  DoEnergy(+25);
  // Weiter
  if(GetActTime() < GetBurnTime()) return(1);
  // Fertig
  SetAction("Idle");
}

/* Inhaltsüberprüfung */

private func ContentsCheck()
{
  // Noch aktiv
  if(!ActIdle()) return(1);
  var i = -1, obj, def;
  while(obj = Contents(++i) )
  {
    if(obj->~IsLorry() )
    {
      SetCommand(obj, "Exit");
    }
  }

  // Erstes Inhaltsobjekt prüfen
  obj = Contents(0);
  def = GetID(obj);
  
  // Alles außer Brennmaterial raus
  if(def != COAL && def != OBRL && def != WOOD)
    SetCommand(obj, "Exit");
    
  // Wird Energie benötigt
  if(!CheckEnergyNeedChain() ) return(1);
  
  // Holz?
  if(ContentsCount(WOOD) > 1)
    return(BurnWood() );
    
  // Öl?
  if(ContentsCount(OBRL) )
    return(BurnOil() );
    
  // Kohle
  if(!(obj = FindContents(COAL)) ) return(1);
  RemoveObject(obj);
  SetAction("Burning");
}

private func BurnWood()
{
  // Zwei Holz löschen
  for(var i = 0; i < 2; ++ i)
    RemoveObject(FindContents(WOOD) );

  // Los gehts
  SetAction("Burning");
}

private func BurnOil()
{
  // Fass entleeren
  var barrel = FindContents(OBRL);
  if(!barrel) return(0);
  ChangeDef(BARL, barrel);
  
  // Los geth.
  SetAction("Burning");
}

/* Brenndauer */
private func GetBurnTime() { return(2000); }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local BlastIncinerate = 130;
local ContainBlast = 1;
local BurnTo = POWB;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
OpenDoor = {
	Prototype = Action,
	Name = "OpenDoor",
	Length = 10,
	Delay = 1,
	X = 0,
	Y = 52,
	Wdt = 17,
	Hgt = 16,
	OffX = 35,
	OffY = 36,
	FacetBase = 1,
	NextAction = "DoorOpen",
	StartCall = "SoundOpenDoor",
},

DoorOpen = {
	Prototype = Action,
	Name = "DoorOpen",
	Delay = 20,
	X = 153,
	Y = 52,
	Wdt = 17,
	Hgt = 16,
	OffX = 35,
	OffY = 36,
	FacetBase = 1,
	NextAction = "CloseDoor",
	StartCall = "OpenEntrance",
	EndCall = "CloseEntrance",
},

CloseDoor = {
	Prototype = Action,
	Name = "CloseDoor",
	Length = 10,
	Reverse = 1,
	Delay = 1,
	X = 0,
	Y = 52,
	Wdt = 17,
	Hgt = 16,
	OffX = 35,
	OffY = 36,
	FacetBase = 1,
	NextAction = "Idle",
	StartCall = "SoundCloseDoor",
},

Burning = {
	Prototype = Action,
	Name = "Burning",
	Length = 8,
	Delay = 1,
	X = 0,
	Y = 68,
	Wdt = 8,
	Hgt = 11,
	OffX = 9,
	OffY = 35,
	FacetBase = 1,
	NextAction = "Burning",
	StartCall = "Burning",
},

};
