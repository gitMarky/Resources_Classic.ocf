/* Kraftfeldbruecke - Segment */

#include FCWS

private func CheckStuck()
{
  var pClonk,iYChange,iX,iY;
  // Alle feststeckenden Clonks in der N�he suchen
  for (pClonk in FindObjects(Find_InRect(-20,-20,40,40), Find_OCF(OCF_CrewMember),Find_NoContainer()))
  {
    iX=GetX(pClonk);
    iY=GetY(pClonk);
    while(Stuck(pClonk) && Inside(GetY(pClonk)-GetY(),-20,20))
    {
      if(!(iYChange=BoundBy(GetY(pClonk)-GetY(),-1,1))) iYChange=1;
      // Zur Sicherheit...
      if(!Inside(GetY(pClonk)+iYChange,-100,LandscapeHeight())) break;
      SetPosition(GetX(pClonk),GetY(pClonk)+iYChange,pClonk);
    }
    // verschieben fehlgeschlagen: r�ckg�ngig machen
    if(Stuck(pClonk)) SetPosition(iX,iY,pClonk);
  }
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
Field = {
	Prototype = Action,
	Name = "Field",
	Procedure = DFA_FLOAT,
	Length = 4,
	X = 0,
	Y = 0,
	Wdt = 18,
	Hgt = 8,
	Sound = "Energy",
},

};
