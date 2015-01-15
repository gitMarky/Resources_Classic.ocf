/*-- Chemiefabrik --*/


/* Nutzt die Grundfunktionalität der Werkstatt. */

#include WRKS
#include BAS3

/* Produkteigenschaften (überladen) */
public func ProductType () {return(C4D_Object());}
public func ProductCondition () {return("IsChemicalProduct");}

/* Produktion */

private func MenuProduction(pCaller) 
{
  // Menü erzeugen und mit Bauplänen des Spielers füllen
  CreateMenu(CHEM,pCaller,this(),1,"$TxtNoconstructionplans$");
  for(var i=0,idKnowledge; idKnowledge=GetPlrKnowledge(GetOwner(pCaller),0,i,ProductType ()); ++i)
    if (DefinitionCall (idKnowledge, ProductCondition ()))
      AddMenuItem("$TxtProductions$", "SelectProduction", idKnowledge, pCaller, 0, pCaller);
  return(1);
}

/* Türsteuerung */

private func SoundOpenDoor()
{
  Sound("SteelGate2");
}
  
private func SoundCloseDoor()
{
  Sound("SteelGate2");
}

/* Aktivität */

private func Smoking()
{
  if (Random(2)) Smoke(+7, -27, 8);
  Smoke(-5, -28, 5 + Random(3));
}

/* Aufnahme */

protected func Collection()
{
  return(Sound("Clonk"));
}

/* Kontext */

public func ContextConstruction(pCaller) 
{
  [$Production$|Image=CH01|Condition=IsBuilt]
  return(MenuProduction(pCaller));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local BlastIncinerate = 100;
local ContainBlast = 1;
local BurnTo = CHMB;

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
	Y = 57,
	Wdt = 14,
	Hgt = 17,
	OffX = 18,
	OffY = 40,
	FacetBase = 1,
	NextAction = "DoorOpen",
	StartCall = "SoundOpenDoor",
},

DoorOpen = {
	Prototype = Action,
	Name = "DoorOpen",
	Delay = 20,
	X = 126,
	Y = 57,
	Wdt = 14,
	Hgt = 17,
	OffX = 18,
	OffY = 40,
	FacetBase = 1,
	NextAction = "CloseDoor",
	StartCall = "OpenEntrance",
	EndCall = "CloseEntrance",
},

CloseDoor = {
	Prototype = Action,
	Name = "CloseDoor",
	Length = 7,
	Reverse = 1,
	Delay = 1,
	X = 0,
	Y = 57,
	Wdt = 14,
	Hgt = 17,
	OffX = 18,
	OffY = 40,
	FacetBase = 1,
	NextAction = "Idle",
	StartCall = "SoundCloseDoor",
	EndCall = "DoorClosed",
},

};
