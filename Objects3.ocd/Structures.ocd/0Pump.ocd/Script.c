/*-- Pumpe --*/


local Barrel;
local TransferReady;

#include CXEC
#include BAS1

/* Initialisierung */

protected func Initialize()
{
  SetAction("Pump");
  Barrel = CreateContents(BARL);
  TransferReady = 0;
}

/* Status */

public func AcceptTransfer()
{
  return(TransferReady); 
}  

/* Pumpkontrolle */

private func Waiting()
{
  if (ReadyToPump())
  {
    SetAction("Pump");
    TransferReady = 1;
  }
}

private func Pumping()
{
  if (!ReadyToPump())
  {
    SetAction("Wait");
    TransferReady = 0;    
  }
}

private func ReadyToPump()
{
  // Zuflussrohr suchen
  var pSourcePipe = FindObject(SPIP,0,0,0,0,0,"Connect",this());
  // Kein Zuflussrohr da: nicht pumpen
  if (!pSourcePipe) return(0);
  // Zufluss-Leitungsbausatz suchen
  var pPumpSource = GetActionTarget(1, pSourcePipe);
  // Zuflussrohr ist gar nicht oder nicht an einen Leitungsbausatz angeschlossen: strange?!
  if (!pPumpSource || (GetID(pPumpSource)!=LNKT)) return(1);
  // Abflussrohr suchen
  var pDrainPipe = FindObject(DPIP,0,0,0,0,0,"Connect",this());
  // Kein Abflussrohr da: pumpen
  if (!pDrainPipe) return(1);
  // Abfluss-Zielobjekt suchen
  var pPumpTarget = GetActionTarget(1, pDrainPipe);
  // Abflussrohr ist gar nicht oder an einen Leitungsbausatz angeschlossen: pumpen
  if (!pPumpTarget || (GetID(pPumpTarget)==LNKT)) return(1);
  // Kapazit�t f�r gepumptes Material im Zielobjekt pr�fen
  if (!CheckCapacity(pPumpTarget, 12, pPumpSource->GetMaterial(0,1)))
    // Keine ausreichende Kapazit�t: nicht pumpen
    return(0);
  // Ansonsten: pumpen
  return(1);
}

private func CheckCapacity(pTarget, iAmount, iMaterial)
{
  //Log("%s %d %d", pTarget->GetName(), iAmount, iMaterial);
  // Teilweise gef�llte F�sser suchen
  var BarrelID = GetBarrelType(iMaterial);
  var objBarrel;
  // Wenn es keinen Fasstyp f�r diese Fl�ssigkeit gibt, kann auch nicht gepumpt werden!
  if (!BarrelID) return();
  while (objBarrel = FindObject(BarrelID,0,0,0,0,0,0,0,pTarget,objBarrel))
    if (!objBarrel->BarrelIsFull())
      if ((iAmount -= objBarrel->BarrelMaxFill() - objBarrel->GetAmount()) <= 0)
        // Noch Kapazit�t vorhanden
        return(1);
  // Leere F�sser suchen
  BarrelID = EmptyBarrelID();
  objBarrel = 0;
  if (BarrelID)
  {
    while (objBarrel = FindObject(BarrelID,0,0,0,0,0,0,0,pTarget,objBarrel))
      if ((iAmount -= objBarrel->BarrelMaxFill()) <= 0)
        // Noch Kapazit�t vorhanden
        return(1);
  }
  // Keine Kapazit�t vorhanden
  return(0);
}

/* Zerst�rung */

protected func Destruction() { if(Barrel) RemoveObject(Barrel); return(_inherited() ); }
protected func Incineration() { if(Barrel) RemoveObject(Barrel); return(_inherited() ); }
protected func IncinerationEx() { if(Barrel) RemoveObject(Barrel); return(_inherited() ); }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local BlastIncinerate = 50;
local BurnTo = PMPB;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Pump = {
	Prototype = Action,
	Name = "Pump",
	Procedure = DFA_NONE,
	Length = 20,
	Delay = 3,
	X = 0,
	Y = 0,
	Wdt = 28,
	Hgt = 32,
	NextAction = "Pump",
	StartCall = "Pumping",
},

Wait = {
	Prototype = Action,
	Name = "Wait",
	Procedure = DFA_NONE,
	Length = 1,
	Delay = 50,
	X = 0,
	Y = 0,
	Wdt = 28,
	Hgt = 32,
	NextAction = "Wait",
	StartCall = "Waiting",
},

};
