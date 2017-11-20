//THE MAIN GAMEMODE

#include <a_samp>
#include <YSI\y_ini>
#include <YSI\y_hooks>

#include "/main_data/stock.inc"

//CORE ITEMS
#include "/main_data/core_items/_core.inc"

//REGISTER / LOGIN SYSTEM
#include "/main_data/player_data_reg/core.inc"

//SERVERWIDE ITEMS
#include "/main_data/server_wide/core.inc"
main()
{

}

public OnGameModeInit()
{
	DisableInteriorEnterExits();
	ShowPlayerMarkers(0);
	SetGameModeText("King Of The Hill [KOTH]");
	return 1;
}

public OnGameModeExit()
{
	return 1;
}

public OnPlayerConnect(playerid)
{
	return 1;
}
public OnPlayerDisconnect(playerid, reason)
{
	return 1;
}

public OnPlayerRequestClass(playerid, classid)
{
	SetPlayerPos(playerid, -1497.5938,-382.2136,15.7227);
	SetPlayerFacingAngle(playerid, 137.2047);
	SetPlayerCameraPos(playerid, -1506.0388, -391.0155, 20.6097);
	SetPlayerCameraLookAt(playerid, -1505.3280, -390.3090, 20.4046);
	return 1;
}
public OnPlayerSpawn(playerid)
{
	return 1;
}