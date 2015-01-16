/* Magischer Funken */


protected func Initialize()
{
	SetVisibility(VIS_Owner());
	SetAction("Exist");	
}



protected func Destroy()
{
	RemoveObject();
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
Exist = {
	Prototype = Action,
	Name = "Exist",
	Procedure = DFA_FLOAT,
	Length = 8,
	Delay = 2,
	X = 0,
	Y = 0,
	Wdt = 10,
	Hgt = 10,
	NextAction = "Idle",
	EndCall = "Destroy",
},

};
