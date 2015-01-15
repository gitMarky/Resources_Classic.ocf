/* Wird abgefeuert */


public func Launch()
{
  SetAction("Travel");
}
  
/* Fliegt */
private func Travel()
{
  // Treffer-Überprüfung
  if(FindObject(0,-5,-5,10,10,OCF_Prey(),0,0,NoContainer())) return(Hit());
  CastObjects(DFLM,1,1);
}
  
/* Treffer */
protected func Hit()
{
  CastObjects(DFLM,10,7);
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
};
