/*-- Lenseflare --*/


local fMaster;
local aFlares;
local iSunX, iSunY;

// Initialisierung
protected func Initialize()
{
	// Nur f�r den Herrn und Meister sichtbar
	SetVisibility (VIS_Owner, this);
	// Das erste Lenseflare-Objekt pr�ft nur, dass jeder Spieler auch sein Umweltobjekt hat
	if(!FindObject2(Find_ID(GetID()), Find_Exclude(this)))
	{
		SetOwner(-1,this); // Unparteiisch sein!
		fMaster = 1;
		// Sind wir noch nicht plaziert?
		if(GetX() == 50 && GetY() == 50)
		{
			// Entweder 1/4 oder 3/4
			var iPosX = LandscapeWidth()*1000/1618;
			if(Random(2)) iPosX = LandscapeWidth()-iPosX;
			// H�he nach Landschaft
			var iPosY;
			for(iPosY = 0; iPosY < LandscapeHeight(); iPosY++)
				if(GBackSolid(iPosX-GetX(), iPosY-GetY())) break;
			SetPosition(iPosX, iPosY/2);
		}
		return;
	}
}

// Neue Benutzer-Spieler bekommen Lenswflares
public func InitializePlayer(int iPlr)
{
	if(!fMaster) return;
	// Lenseflare erstellen
	if(GetPlayerType(iPlr) == C4PT_User)
		CreateObject(GetID(), 0, 0, iPlr)->InitializeLenseflare();
	return true;
}

// Bei gel�schten Spielern die Flares entfernen
public func RemovePlayer(int iPlr)
{
	if(!fMaster) return;
	for(var pFlare in FindObjects(Find_ID(GetID()), Find_Owner(iPlr)))
		RemoveObject(pFlare);
	return true;
}

// Initialisierung als Haupt-Lenseflare
public func InitializeLenseflare()
{ 
	// Position speichern
	iSunX = GetX(); iSunY = GetY();
	SetCategory(C4D_StaticBack | C4D_Background | C4D_MouseIgnore);
	aFlares = CreateArray(LenseflareCount());
	for(var i = 0; i < LenseflareCount(); i++)
	{
		aFlares[i] = CreateObject(GetID(), 0, 0, GetOwner());
		SetCategory(C4D_StaticBack | C4D_MouseIgnore | C4D_Foreground, aFlares[i]);
		ObjectSetAction(aFlares[i],Format("Fleck%d",i%14));
	}
	SetAction("ManageFlares");
}

// Verwaltung der Flares
protected func ManageFlares()
{
	// unskalierten Vektor ermitteln
	var iVectorX = GetVectorX(GetOwner());
	var iVectorY = GetVectorY(GetOwner());
	var iVectorDist = GetVectorDist(GetOwner());
	// Die Modulation ist f�r alle Flares gleich
	var iColorModulation = RGBa(GetColorMod(),GetColorMod(),GetColorMod(),GetAlphaMod(iVectorDist));
	// Genauso auch die Abstandsangabe
	var iDistance = 1000-BoundBy((3000-iVectorDist*10)/3,0,1000);  // Promilleangabe 0 = nahe, 1000 = weit weg; 300 Pixel sind dabei "weit weg"
	var iAbsolutDistanc = (50*iDistance)/10; // Wieviele 1/100 Pixel zwischen den einzelnen Lenseflares sind
	// Ist unsere liebe Sonne �berhaupt sichtbar (also Tag + unverdeckt)
	var fSunVisible = IsDay() && (!GBackSemiSolid(0,0));
	// Tags�ber die Sonne einblenden
	if(IsDay())
		SetVisibility (VIS_Owner);
	else
		SetVisibility (VIS_None);
	// Alle Lenseflares durchgehen
	var i = 0;
	for(var pFlare in aFlares)
	{
		if(fSunVisible)
		{
			// Tags sichtbar
			SetVisibility (VIS_Owner, pFlare);
			SetClrModulation(iColorModulation,pFlare);
			var LensDist = (i*iAbsolutDistanc)/100;
			SetPosition(GibLensPosX(LensDist,iVectorX,iVectorDist), GibLensPosY(LensDist,iVectorY,iVectorDist),pFlare);
		}
		else
			// Nachts unsichtbar ODER bei verdeckter Sonne
			SetVisibility (VIS_None, pFlare);
		i++;
	}
	// Sofern der Spieler alleine ist
	if(GetPlayerCount() == 1)
		if(IsDay())
		{
			var iYellow = BoundBy((500-iVectorDist)/5,0,100); // Prozentangabe 0 = weit weg, 100 = nahe; 500 Pixel sind dabei "weit weg"
			SetGamma (RGB(000+(30*iYellow)/100,000+(30*iYellow)/100,000),
					  RGB(128+(60*iYellow)/100,128+(60*iYellow)/100,128), 
					  RGB(255,255,255), GammaRamp_Lenseflare());
		}
}

// F�r die iColorModulation (Entfernung + Nacht)
private func GetIntensity()
{
	var pTimeObject = FindObject(TIME);
	if(!pTimeObject)
		return 100;
	return Local(2, pTimeObject);
}

private func GetSunMod() // D�mmerung 
{
	var iIntensity = GetIntensity();
	// Folgende Farbwerte sind in Promille
	var iRed = 1000;
	var iGreen = 1000;
	var iBlue = 1000;
	if(Inside(iIntensity,1,20)) // D�mmerung -> Rotstich
	{
		var iRedStich = Cos(iIntensity*4,500);
		iGreen -= iRedStich/2;
		iBlue -= iRedStich;
	}
	// Nun die Farbe berechnen
	return RGB((255*iRed)/1000,(255*iGreen)/1000,(255*iBlue)/1000);
}

private func GetColorMod()
{
	return (255*GetIntensity())/100;
}

private func GetAlphaMod(iDistance)
{
	var iStrength = BoundBy((2000-iDistance)/20,75,100); // Prozentangabe 75 = weit weg, 100 = nahe; 2000 Pixel sind dabei "weit weg"
	return 255-(255*iStrength)/100; 
}

// Genutzte Gammarampe
global func GammaRamp_Lenseflare()
{
	return 2;
}

// Den (unskalierten) Vektor. Er wird skaliert, um die Lenseflare-Positionen zu errechnen
private func GetVectorX(iPlayer)
{
	return GetCenterX(iPlayer) - iSunX;
}

private func GetVectorY(iPlayer)
{
	return GetCenterY(iPlayer) - iSunY;
}

// Skaliere den Vektor mit der gew�nschten Entfernung Lenseflare->Sonne
private func GibLensPosX(iDistance, VektorX, iVectorDist)
{
	// Skalierung in Promille
	var iScale = (iDistance*1000) / iVectorDist;
	var TempX = (VektorX * iScale)/1000;
	return TempX + iSunX;
}

private func GibLensPosY(iDistance, VektorY, iVectorDist)
{
	// Skalierung in Promille
	var iScale = (iDistance*1000) / iVectorDist;
	var TempY = (VektorY * iScale)/1000;
	return TempY + iSunY;
}

// Wieviele Lenseflares h�tten's denn gerne
private func LenseflareCount()
{
	// etwa alle 50 Pixel einen Lenseflare
	return LandscapeWidth() / 2 / 50;
}

// Interner Kruscht!
// Bildschirmmittelpunkt
private func GetCenterX(iPlayer)
{
	if(IsNetwork())
		return GetX(GetCursor(iPlayer));
	else
		return GetPlrViewX(iPlayer);
}

private func GetCenterY(iPlayer)
{
	if(IsNetwork())
		return GetY(GetCursor(iPlayer));
	else
		return GetPlrViewY(iPlayer);
}

private func GetVectorDist(iPlayer)
{
	return Distance(GetCenterX(iPlayer),GetCenterY(iPlayer),iSunX,iSunY);
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
ManageFlares = {
	Prototype = Action,
	Name = "ManageFlares",
	Procedure = DFA_FLOAT,
	Length = 1,
	Delay = 1,
	X = 0,
	Y = 0,
	Wdt = 192,
	Hgt = 192,
	OffX = -96,
	OffY = -96,
	NextAction = "ManageFlares",
	EndCall = "ManageFlares",
},

Fleck0 = {
	Prototype = Action,
	Name = "Fleck0",
	Procedure = DFA_FLOAT,
	Length = 1,
	Delay = 0,
	X = 0,
	Y = 192,
	Wdt = 39,
	Hgt = 39,
	OffX = -19,
	OffY = -19,
	NextAction = "Hold",
},

Fleck1 = {
	Prototype = Action,
	Name = "Fleck1",
	Procedure = DFA_FLOAT,
	Length = 1,
	Delay = 0,
	X = 58,
	Y = 192,
	Wdt = 89,
	Hgt = 89,
	OffX = -44,
	OffY = -44,
	NextAction = "Hold",
},

Fleck2 = {
	Prototype = Action,
	Name = "Fleck2",
	Procedure = DFA_FLOAT,
	Length = 1,
	Delay = 0,
	X = 29,
	Y = 231,
	Wdt = 20,
	Hgt = 20,
	OffX = -10,
	OffY = -10,
	NextAction = "Hold",
},

Fleck3 = {
	Prototype = Action,
	Name = "Fleck3",
	Procedure = DFA_FLOAT,
	Length = 1,
	Delay = 0,
	X = 0,
	Y = 281,
	Wdt = 61,
	Hgt = 61,
	OffX = -30,
	OffY = -30,
	NextAction = "Hold",
},

Fleck4 = {
	Prototype = Action,
	Name = "Fleck4",
	Procedure = DFA_FLOAT,
	Length = 1,
	Delay = 0,
	X = 0,
	Y = 231,
	Wdt = 29,
	Hgt = 29,
	OffX = -14,
	OffY = -14,
	NextAction = "Hold",
},

Fleck5 = {
	Prototype = Action,
	Name = "Fleck5",
	Procedure = DFA_FLOAT,
	Length = 1,
	Delay = 0,
	X = 192,
	Y = 64,
	Wdt = 19,
	Hgt = 19,
	OffX = -9,
	OffY = -9,
	NextAction = "Hold",
},

Fleck6 = {
	Prototype = Action,
	Name = "Fleck6",
	Procedure = DFA_FLOAT,
	Length = 1,
	Delay = 0,
	X = 192,
	Y = 92,
	Wdt = 6,
	Hgt = 6,
	OffX = -3,
	OffY = -3,
	NextAction = "Hold",
},

Fleck7 = {
	Prototype = Action,
	Name = "Fleck7",
	Procedure = DFA_FLOAT,
	Length = 1,
	Delay = 0,
	X = 192,
	Y = 83,
	Wdt = 9,
	Hgt = 9,
	OffX = -4,
	OffY = -4,
	NextAction = "Hold",
},

Fleck8 = {
	Prototype = Action,
	Name = "Fleck8",
	Procedure = DFA_FLOAT,
	Length = 1,
	Delay = 0,
	X = 147,
	Y = 192,
	Wdt = 38,
	Hgt = 38,
	OffX = -19,
	OffY = -19,
	NextAction = "Hold",
},

Fleck9 = {
	Prototype = Action,
	Name = "Fleck9",
	Procedure = DFA_FLOAT,
	Length = 1,
	Delay = 0,
	X = 354,
	Y = 0,
	Wdt = 70,
	Hgt = 70,
	OffX = -35,
	OffY = -35,
	NextAction = "Hold",
},

Fleck10 = {
	Prototype = Action,
	Name = "Fleck10",
	Procedure = DFA_FLOAT,
	Length = 1,
	Delay = 0,
	X = 39,
	Y = 192,
	Wdt = 19,
	Hgt = 19,
	OffX = -9,
	OffY = -9,
	NextAction = "Hold",
},

Fleck11 = {
	Prototype = Action,
	Name = "Fleck11",
	Procedure = DFA_FLOAT,
	Length = 1,
	Delay = 0,
	X = 211,
	Y = 64,
	Wdt = 28,
	Hgt = 28,
	OffX = -14,
	OffY = -14,
	NextAction = "Hold",
},

Fleck12 = {
	Prototype = Action,
	Name = "Fleck12",
	Procedure = DFA_FLOAT,
	Length = 1,
	Delay = 0,
	X = 256,
	Y = 0,
	Wdt = 98,
	Hgt = 98,
	OffX = -49,
	OffY = -49,
	NextAction = "Hold",
},

};
