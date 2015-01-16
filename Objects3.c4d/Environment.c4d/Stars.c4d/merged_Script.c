/*-- Sternenhimmel --*/


/* Locals */

// Maximale Anzahl Sterne
local MaxCount;

protected func Initialize()
{
  SetAction("Initialize");
  SetPosition();
  return(1);
}

private func Initialized()
{
  // Plazierungsfaktor ermitteln
  var iCount = ObjectCount(GetID()) + 1;
  // Andere Objekte des gleichen Typs entfernen
  var pOther;
  while (pOther = FindObject(GetID()))
    RemoveObject(pOther);
  // Maximale Anzahl Sterne berechnen
  MaxCount = (LandscapeWidth() * LandscapeHeight() * iCount) / 20000;
  // Steuerungsaktion
  SetAction("Day");
  return(1);
}
    
private func Day()
{
  // Es wird Nacht
  if (IsNight())
    SetAction("Dusk");
  return(1);
}
    
private func Dusk()
{
  // Alle Sterne plaziert
  if (GetActTime() > MaxCount) 
    return(SetAction("Night"));
  // Sterne hinzufügen
  CreateObject(STAR, Random(LandscapeWidth()), Random(LandscapeHeight()), -1);
  return(1);
}
        
private func Night()
{
  // Es wird Tag
  if (IsDay())
    SetAction("Dawn");
  return(1);
}
    
private func Dawn()
{
  // Alle Sterne entfernt
  var pStar;
  if (!(pStar = FindObject(STAR))) 
    return(SetAction("Day"));
  // Sterne entfernen
  RemoveObject(pStar);
  return(1);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Initialize = {
	Prototype = Action,
	Name = "Initialize",
	Length = 1,
	Delay = 1,
	NextAction = "Idle",
	EndCall = "Initialized",
},

Day = {
	Prototype = Action,
	Name = "Day",
	Length = 1,
	Delay = 30,
	NextAction = "Day",
	StartCall = "Day",
},

Dusk = {
	Prototype = Action,
	Name = "Dusk",
	Length = 1,
	Delay = 1,
	NextAction = "Dusk",
	StartCall = "Dusk",
},

Night = {
	Prototype = Action,
	Name = "Night",
	Length = 1,
	Delay = 30,
	NextAction = "Night",
	StartCall = "Night",
},

Dawn = {
	Prototype = Action,
	Name = "Dawn",
	Length = 1,
	Delay = 1,
	NextAction = "Dawn",
	StartCall = "Dawn",
},

};
