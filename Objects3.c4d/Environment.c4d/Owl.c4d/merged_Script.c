/*-- Eule --*/


protected func Initialize()
{
  SetAction("Owl");
  SetPhase(Random(20));
  return(1);
}

private func Owl()
{
  // Nur bei Nacht aktiv
  if (!IsNight()) return(0);
  if (!Random(30)) Sound("Owl", 1);
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
Owl = {
	Prototype = Action,
	Name = "Owl",
	Length = 1,
	Delay = 60,
	NextAction = "Owl",
	StartCall = "Owl",
},

};
