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
#define MYSQL_DB "Community"
#define MYSQL_PASSWORD ""

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
	new length=strlen(buf);
	new s1 = 1;
	new s2 = 0;
	new n;
	for (n=0; n<length; n++)
	{
		s1 = (s1 + buf[n]) % 65521;
		s2 = (s2 + s1) % 65521;
	}
	return (s2 << 16) + s1;
}

//__Public__//

public _On@Account_Check_(playerid, crashID)
{
	return 1;
}
//_____________________________________________________________//
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
//~~~~~~~~~~~~~~~~~~~~ Variables / Enums ~~~~~~~~~~~~~~~~~~~~~~//
static Connection@Handle;

static e_player@Info
{
	pID,
	pName[MAX_PLAYER_NAME],

	pPass[30],
	pPassTry,

	pLevel,
	pCash,

	pAdminL,

	pKills,
	pDeaths,	
	
	bool:pLogged,
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
	
	mysql_tquery(Connection@Handle, "CREATE TABLE IF NOT EXISTS `PLAYERS` (`ID` int(11) NOT NULL AUTO_INCREMENT,`USERNAME` varchar(24) NOT NULL,`PASSWORD` char(30) NOT NULL,`LEVEL` mediumint(7) NOT NULL DEFAULT '0',`CASH` mediumint(7) NOT NULL DEFAULT '0',`ADMINL` tinyint(1) NOT NULL DEFAULT '0',`KILLS` mediumint(7) NOT NULL DEFAULT '0',`DEATHS` mediumint(7) NOT NULL DEFAULT '0', PRIMARY KEY (`ID`), UNIQUE KEY `USERNAME` (`USERNAME`))");
	return 1;
}

Hook:Logister_OnGameModeInit()
{
	static i;
	i = 0;

	foreach(i:Player)
	{
		if(IsPlayerConnected(i) && player@Info[i][pLogged])
			OnPlayerDisconnect(i, 1);
	}

	mysql_close(Connection@Handle);

	Connection@Handle = MYSQL_INVALID_HANDLE;	
	return 1;
}
//_______________________________________________________________//