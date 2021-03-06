
public func GetElementColor() { return(RGBa(187,187,221)); }
public func GetClassCombo() { return("5"); }
public func IsSpellClass() { return(1); }
protected func Initialize() { return(SetObjectLayer(this())); }
protected func AttachTargetLost() { return(RemoveObject()); }
protected func MouseSelection(iByPlr) { return(GetActionTarget()->MouseSelection(this())); }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Attach = {
	Prototype = Action,
	Name = "Attach",
	Procedure = DFA_ATTACH,
	Length = 1,
	X = 0,
	Y = 0,
	Wdt = 40,
	Hgt = 40,
	NextAction = "Attach",
},

};
