#define PATH "/Users/%s.ini"

stock UserPath(playerid)
{
	new string[128],
		playername[MAX_PLAYER_NAME];

	GetPlayerName( playerid, playername, sizeof(playername) );
	format( string, sizeof(string), PATH, playername );

	return string;
}

stock udb_hash(buf[]) {
	new length=strlen(buf);
    new s1 = 1;
    new s2 = 0;
    new n;
    for (n=0; n<length; n++)
    {
       s1 = (s1 + buf[n]) % 65521;
       s2 = (s2 + s1)     % 65521;
    }
    return (s2 << 16) + s1;
}

stock REGKICK(playerid)
{
	SendClientMessage(playerid, -1, "{8B0000}Warning:{FFFFFF}You have decided to quit.");
	Kick(playerid);
	return 1;

}
