/*-- Zikaden --*/


protected func Initialize()
{
  SetAction("Cicadas");
  SetPhase(Random(20));
  return(1);
}

private func Cicadas()
{
  // Nur bei Nacht aktiv
  if (!IsNight()) return(0);  
  if (!Random(20)) Sound("Cicada*",1);
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
Cicadas = {
	Prototype = Action,
	Name = "Cicadas",
	Length = 1,
	Delay = 25,
	NextAction = "Cicadas",
	StartCall = "Cicadas",
},

};
