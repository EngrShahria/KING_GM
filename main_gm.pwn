//THE MAIN GAMEMODE

#include <a_samp>
#include <a_mysql>
#include <YSI\y_hooks>

//REGISTER / LOGIN SYSTEM
#include "/main_data/player_data_reg/core.inc"

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