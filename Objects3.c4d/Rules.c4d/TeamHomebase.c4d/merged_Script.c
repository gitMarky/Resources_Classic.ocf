/*-- Spielregel --*/


protected func Activate(iByPlayer)
{
  MessageWindow(GetDesc(), iByPlayer);
  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
