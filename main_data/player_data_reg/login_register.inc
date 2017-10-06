
forward LoadUserData( playerid, name[], value[] );
public LoadUserData( playerid, name[], value[] )
{
	INI_Int ( "Password", PlayerInfo [playerid] [pPass] );
	INI_Int ( "Cash", PlayerInfo [playerid] [pCash] );
	INI_Int ( "Admin", PlayerInfo [playerid] [pAdmin] );
	INI_Int ( "Kills", PlayerInfo [playerid] [pKills] );
    INI_Int ( "Deaths", PlayerInfo [playerid] [pDeaths] );

 	return 1;
}


hook:Reg_OnPlayerConnect(playerid)
{
	if(fexist(UserPath(playerid)))
	{
		INI_ParseFile(UserPath(playerid), "LoadUser_%s", .bExtra = true, .extra = playerid);
  		ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_INPUT, "Login", "Type your password below to login.", "Login", "Quit");
	}
	else
	{
 		ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_INPUT, "Registering.", "Type your password below to register a new account.", "Register", "Quit");
	}
	return 1;
}
