
func Completion()
{
  SetR(Random(360));
}

func Wind2Turn()
{
  DoEnergy(Abs(GetRDir() * 5), GetActionTarget() );
  SetRDir(GetWind() / 4);
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// properties

local Name = "$Name$";
local Description = "$Description$";
local BlastIncinerate = 30;
local BurnTo = WWNB;
local ContactIncinerate = 4;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// actions

local ActMap = {
Turn = {
	Prototype = Action,
	Name = "Turn",
	Procedure = DFA_ATTACH,
	Delay = 15,
	FacetBase = 1,
	NextAction = "Turn",
	StartCall = "Wind2Turn",
},

};
