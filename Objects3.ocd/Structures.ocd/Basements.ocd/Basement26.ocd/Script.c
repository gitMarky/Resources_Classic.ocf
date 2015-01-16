/*-- Fundament --*/

/* Alle Fundamente leiten ihre Grundfunktionalit�t von BAS7 ab */


#include BAS7

private func BasementID() { return(BAS1); }
private func BasementWidth() { return(26); }

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
