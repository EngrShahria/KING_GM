//~~~~~~~~~~~~~~~~~~~~ Forwards ~~~~~~~~~~~~~~~~~~~~~//

forward _On@Account_Check_(playerid, crashID);

//__________________________________________________//
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////
//~~~~~~~~~~~~~~~~~~~~~~~~ DEFINES ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

#if !defined isnull
    #define isnull(%1) ((!(%1[0])) || (((%1[0]) == '\1') && (!(%1[1]))))
#endif


#define MYSQL_HOST "localhost"
#define MYSQL_USER "root"
#define MYSQL_DB "KING_DM"
#define MYSQL_PASSWORD ""


#define DIALOG_LOGIN 1
#define DIALOG_REGISTER 2
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
//~~~~~~~~~~~~~~~~~~ Functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

//__LOCAL__//

/* Password hash
Credits to Dracoblue */
udb_hash(buf[])
{
	static length=strlen(buf), s1 = 1, s2 = 0, n;

	for (n=0; n<length; n++)
	{
		s1 = (s1 + buf[n]) % 65521;
		s2 = (s2 + s1) % 65521;
	}

	return (s2 << 16) + s1;
}

GetPName(playerid)
{
	static playerName[MAX_PLAYER_NAME];
	GetPlayerName(playerid, playerName, sizeof(playerName));
	return playerName;
}
//__Public__//

public _On@Account_Check_(playerid, crashID)
{
	if(++crashID != privateCrash_ID) return Kick(playerid);

	if(privateCrash_ID > 10)
		privateCrash_ID=0;

	static String[150];
	
	if(cache_num_rows() > 0)
	{
		cache_get_value(0, "PASSWORD", player@Info[playerid][pPass], sizeof(e_player@Info[pPass]));

		player@Info[MAX_PLAYERS][pCache] = cache_save();

		format(String, sizeof(String), "{FFFFFF}Welcome back, %s.\n\n{0099FF}This account is already registered.\n\
		{0099FF}Please, input your password below to proceed to the game.\n\n", player@Info[playerid][pName]);
		ShowPlayerDialog(playerid, DIALOG_LOGIN, DIALOG_STYLE_PASSWORD, "Login System", String, "Login", "Leave");
	}
	else
	{
		format(String, sizeof(String), "{FFFFFF}Welcome %s.\n\n{0099FF}This account is not registered.\n\
		{0099FF}Please, input your password below to proceed to the game.\n\n", pInfo[playerid][Name]);
		ShowPlayerDialog(playerid, DIALOG_REGISTER, DIALOG_STYLE_PASSWORD, "Registration System", String, "Register", "Leave");
	}
	return 1;
}
//_____________________________________________________________//
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
//~~~~~~~~~~~~~~~~~~~~ Variables / Enums ~~~~~~~~~~~~~~~~~~~~~~//
static Connection@Handle, privateCrash_ID;

static e_player@Info
{
	uID,
	pName[MAX_PLAYER_NAME],

	pPass[30],
	pPassTry,

	pLevel,
	pCash,

	pAdminL,

	pKills,
	pDeaths,	
	
	bool:pIsBanned,

	bool:pLogged,

	Cache:pCache,
}
static player@Info[MAX_PLAYERS][e_player@Info];
//____________________________________________________________//
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
//~~~~~~~~~~~~~~~~~~~~~~ Callbacks ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

Hook:Logister_OnGameModeInit()
{
	privateCrash_ID = 0;

	static MySQLOpt:option_id = mysql_init_options();
	mysql_set_option(option_id, AUTO_RECONNECT, true);

	Connection@Handle = mysql_connect(MYSQL_HOST, MYSQL_USER, MYSQL_PASS, MYSQL_DATABASE, option_id);

	if(Connection@Handle == MYSQL_INVALID_HANDLE || mysql_errno(Connection@Handle) != 0)
	{
		print("Error in connection to the MySQL database. Closing the server!");

		SendRconCommand("exit");
		return 1;
	}

	print("Successfully connected to the MySQL server.");
	
	mysql_tquery(Connection@Handle, "CREATE TABLE IF NOT EXISTS `PLAYERS` (`ID` int(11) NOT NULL AUTO_INCREMENT,`USERNAME` varchar(24) NOT NULL,`PASSWORD` char(30) NOT NULL,`LEVEL` mediumint(7) NOT NULL DEFAULT '0',`CASH` mediumint(7) NOT NULL DEFAULT '0',`ADMINL` tinyint(1) NOT NULL DEFAULT '0',`KILLS` mediumint(7) NOT NULL DEFAULT '0',`DEATHS` mediumint(7) NOT NULL DEFAULT '0',`BANNED` tinyint(1) NOT NULL '0', PRIMARY KEY (`ID`), UNIQUE KEY `USERNAME` (`USERNAME`))");
	return 1;
}

Hook:Logister_OnGameModeInit()
{
	static i;
	i = 0;

	// Initialize / revert it back manually //

	mysql_close(Connection@Handle);

	Connection@Handle = MYSQL_INVALID_HANDLE;
	privateCrash_ID = 0;

	return 1;
}

Hook:Logister_OnPlayerConnect(playerid)
{
	static DB_query[128], i;

	format(DB_query, sizeof(DB_query), "");

	for(i=0; e_player@Info:i < e_player@Info; i++)
		player@Info[playerid][e_Player@Info:i]=0;

	format(player@Info[playerid][pName], sizeof(player@Info[playerid][pName]), "%s", GetPName(playerid));

	mysql_format(Connection@Handle, DB_query, sizeof(DB_query), "SELECT * FROM `PLAYERS` WHERE `USERNAME` = '%e' LIMIT 1", player@Info[playerid][pName]);
	mysql_tquery(Connection@Handle, DB_query, "_On@Account_Check_", "ii", playerid, privateCrash_ID++);

	return 1;
}

Hook:Logister_OnPlayerDisconnect(playerid, reason)
{
	static DB_query[128], i;

	format(DB_query, sizeof(DB_query), "");

	mysql_format(Connection@Handle, DB_query, sizeof(DB_query), "UPDATE `PLAYERS` SET `LEVEL` = %d, `CASH` = %d, `ADMINL` = %d, `KILLS` = %d, `DEATHS` = %d, `BANNED` = %d WHERE `ID` = %d",
		player@Info[playerid][pLevel], player@Info[playerid][pCash], player@Info[playerid][AdminL], player@Info[playerid][pKills], player@Info[playerid][pDeaths], _:player@Info[playerid][pIsBanned], player@Info[playerid][uID]);

	mysql_tquery(Connection@Handle, DB_query);

	if(player@Info[playerid][pCache] != MYSQL_INVALID_CACHE)
	{
		cache_delete(player@Info[playerid][pCache])
		player@Info[playerid][pCache] = MYSQL_INVALID_CACHE;
	}

	player@Info[playerid][pLogged] = false;

	return 1;
}
//_______________________________________________________________//


// Check line 150 
// Create login / register dialogs.