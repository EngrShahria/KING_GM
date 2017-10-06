public OnDialogResponse(playerid, dialogid, response, listitem, inputtext[])
{
    switch( dialogid )
    {
        case DIALOG_REGISTER:
        {
            if (!response) return REGKICK(playerid);
            if(response)
            {
                if(!strlen(inputtext)) return ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_INPUT, "Registering...","You have entered an invalid password.\nType your password below to register a new account.","Register","Quit");
                new INI:File = INI_Open(UserPath(playerid));
                INI_SetTag(File,"data");
                INI_WriteInt(File,"Password",udb_hash(inputtext));
                INI_WriteInt(File,"Cash",0);
                INI_WriteInt(File,"Admin",0);
                INI_WriteInt(File,"Kills",0);
                INI_WriteInt(File,"Deaths",0);
                INI_Close(File);

                SetSpawnInfo(playerid, 0, 0, 1958.33, 1343.12, 15.36, 269.15, 0, 0, 0, 0, 0, 0);
                SpawnPlayer(playerid);
                ShowPlayerDialog(playerid, DIALOG_SUCCESS_1, DIALOG_STYLE_MSGBOX,"Success!","Great! Your Y_INI system works perfectly. Relog to save your stats!","Ok","");
			}
        }

        case DIALOG_LOGIN:
        {
            if ( !response ) return Kick ( playerid );
            if( response )
            {
                if(udb_hash(inputtext) == PlayerInfo[playerid][pPass])
                {
                    INI_ParseFile(UserPath(playerid), "LoadUser_%s", .bExtra = true, .extra = playerid);
                    GivePlayerMoney(playerid, PlayerInfo[playerid][pCash]);
					ShowPlayerDialog(playerid, DIALOG_SUCCESS_2, DIALOG_STYLE_MSGBOX,"Success!","You have successfully logged in!","Ok","");
                }
                else
                {
                    ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_INPUT,"Login","You have entered an incorrect password.\nType your password below to login.","Login","Quit");
                }
                return 1;
            }
        }
    }
    return 1;
}