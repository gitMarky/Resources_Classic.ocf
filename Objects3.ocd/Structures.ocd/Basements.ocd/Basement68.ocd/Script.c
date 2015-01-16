/*-- Fundament --*/


/* Alle Fundamente leiten ihre Grundfunktionalität von BAS7 ab */

#include BAS7

private func BasementID() { return(BAS5); }
private func BasementWidth() { return(68); }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Consolidate = {
	Prototype = Action,
	Name = "Consolidate",
	Length = 1,
	Delay = 20,
	FacetBase = 1,
	NextAction = "None",
	EndCall = "Consolidated",
},

};
