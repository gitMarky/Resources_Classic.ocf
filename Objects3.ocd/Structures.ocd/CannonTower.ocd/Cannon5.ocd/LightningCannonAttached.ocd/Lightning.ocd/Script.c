/*-- Blitz --*/


public func Advance()
{
  // Letzten Vertex ermitteln
	var iLastVertex = GetVertexNum() - 1;
	// Einschlag im Boden
	if (GBackSemiSolid(GetVertex(iLastVertex, 0) - GetX(), GetVertex(iLastVertex, 1) - GetY()))
		return(Remove());
  // Schon �ber f�nf Schritte fortgeschritten: Schaden an Objekten verursachen
	if (iLastVertex > 5)
		BlastObjects(GetVertex(iLastVertex, 0), GetVertex(iLastVertex, 1), 3);
  // Neuen Schritt durchf�hren
	if (Not(AddVertex(GetVertex(iLastVertex, 0) + Local(0) + Random(Local(1)),
									  GetVertex(iLastVertex, 1) + Local(2) + Random(Local(3)) )))
		return(Remove());
  // Anziehung an ein Zielobjekt pr�fen
	var pTarget;
	iLastVertex = GetVertexNum() - 1;	
	if (iLastVertex > 7)
		if (pTarget = FindObject( 0,
			                        GetVertex(iLastVertex, 0) - GetX() - 50,
															GetVertex(iLastVertex, 1) - GetY() - 50,
															100,
															100,
															OCF_AttractLightning() ))
			Attraction(pTarget);
}

public func Sparkle()
{
	var iLastVertex = GetVertexNum() - 1;
	CastObjects(SPRK, 1, 20, GetVertex(iLastVertex, 0) -  GetX(), GetVertex(iLastVertex, 1) - GetY());
	return(1);
}

public func Attraction(pTarget)
{
	AddVertex(GetVertex(0, 0, pTarget) + GetX(pTarget),
						GetVertex(0, 1, pTarget) + GetY(pTarget));
	ObjectCall(pTarget, "LightningStrike");
	SetAction("Connect");
	return(1);
}

public func Activate(x, y, advanceX, randomX, advanceY, randomY)
{
	AddVertex(x, y);
	SetLocal(0, advanceX);
	SetLocal(1, randomX);
	SetLocal(2, advanceY);
	SetLocal(3, randomY);
	SetAction("Advance");
  return(1);
}

public func Remove()
{
	RemoveObject();
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
Advance = {
	Prototype = Action,
	Name = "Advance",
	Procedure = DFA_NONE,
	Delay = 1,
	NextAction = "Advance",
	StartCall = "Advance",
},

Connect = {
	Prototype = Action,
	Name = "Connect",
	Procedure = DFA_NONE,
	Length = 30,
	Delay = 1,
	NextAction = "Remove",
	PhaseCall = "Sparkle",
},

};
