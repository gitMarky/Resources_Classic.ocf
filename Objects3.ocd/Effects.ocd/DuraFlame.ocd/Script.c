/* Langzeitflamme */


protected func BurnProcess()
  {
  if (Random(4))
    if (GetActTime()>100) return(RemoveObject());
  if (!OnFire()) return(RemoveObject());
  return(1);
	}

protected func Completion()
  {
  Incinerate();
  SetAction("Burn");
  SetComDir(COMD_Down());
  return(1);
  }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local NoBurnDecay = 1;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
};
