/*-- Windrad --*/


#include BAS1

/* Initialisierung */

protected func Initialize()
{
  CreateWindwing();
}

/* Windrad erzeugen */

private func CreateWindwing()
{
  ObjectSetAction(CreateObject(WWNG,0,0,GetOwner()),"Turn",this());
}

/* TimerCall */

private func CheckWindwing()
{
  // Komplett, aber kein Windrad da: reduzieren für Neuaufbau/Reparatur
  if(GetCon() == 100)
    if(!FindObject(WWNG,0,0,0,0,0,"Turn",this()) )
      DoCon(-1);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local BlastIncinerate = 60;
local BurnTo = WMLB;
local ContactIncinerate = 4;
