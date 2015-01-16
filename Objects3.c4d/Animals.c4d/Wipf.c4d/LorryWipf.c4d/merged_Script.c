/*-- Lorenwipf --*/


local count;

public func AttachTo(obj) {
  if (!count) {
    count = 1;
    UpdateGraphic();
  }
  SetAction(GetAction(), obj);
}

public func IncreaseCount() {
  count++;
  UpdateGraphic();
}

public func DecreaseCount() {
  count--;
  UpdateGraphic();
}

public func UpdateGraphic() {
  // Keine Wipfe mehr in der Lore -> Entfernen
  if (count <= 0) return(RemoveObject());
  // Grafik anpassen
  SetAction(Format("Wipf%d", BoundBy(count, 1, 3)));
}

protected func UpdateRotation() {
  var lorry = GetActionTarget();
  // Lore ist verschwunden -> entfernen
  if (!lorry) RemoveObject();
  // Sonst Rotation anpassen
  else SetR(GetR(lorry));
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
Wipf1 = {
	Prototype = Action,
	Name = "Wipf1",
	Procedure = DFA_ATTACH,
	Length = 5,
	Delay = 3,
	X = 0,
	Y = 0,
	Wdt = 24,
	Hgt = 28,
	NextAction = "Wipf1",
},

Wipf2 = {
	Prototype = Action,
	Name = "Wipf2",
	Procedure = DFA_ATTACH,
	Length = 5,
	Delay = 3,
	X = 0,
	Y = 28,
	Wdt = 24,
	Hgt = 28,
	NextAction = "Wipf2",
},

Wipf3 = {
	Prototype = Action,
	Name = "Wipf3",
	Procedure = DFA_ATTACH,
	Length = 5,
	Delay = 3,
	X = 0,
	Y = 56,
	Wdt = 24,
	Hgt = 28,
	NextAction = "Wipf3",
},

};
