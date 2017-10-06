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
	SetGameModeText("King Of The Hill [KOTH] DM Server");
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


