


/*
========================
UI_DrawConnectScreen

This will also be overlaid on the cgame info screen during loading
to prevent it from blinking away too rapidly on local or lan games.
========================
*/

void UI_DrawConnectScreen( qboolean overlay ) {
	char			*s;
	uiClientState_t	cstate;
	char			info[MAX_INFO_VALUE];
	char text[256];
	float centerPoint, yStart, scale;
	
	menuDef_t *menu = Menus_FindByName("Connect");


	if ( !overlay && menu ) {
		Menu_Paint(menu, qtrue);
	}

	if (!overlay) {
		centerPoint = 320;
		yStart = 130;
		scale = 0.5f;
	} else {
		return;
	}

	// see what information we should display
	trap_GetClientState( &cstate );

	info[0] = '\0';
	if( trap_GetConfigString( CS_SERVERINFO, info, sizeof(info) ) ) {
		Text_PaintCenter(centerPoint, yStart, scale, colorWhite, va( "Loading %s", Info_ValueForKey( info, "mapname" )), 0);
	}

	if (!Q_stricmp(cstate.servername,"localhost")) {
		Text_PaintCenter(centerPoint, yStart + 48, scale, colorWhite, "Starting up...", ITEM_TEXTSTYLE_SHADOWEDMORE);
	} else {
		Com_sprintf(text, sizeof(text), "Connecting to %s", cstate.servername);
		Text_PaintCenter(centerPoint, yStart + 48, scale, colorWhite,text , ITEM_TEXTSTYLE_SHADOWEDMORE);
	}

	// display global MOTD at bottom
	Text_PaintCenter(centerPoint, 600, scale, colorWhite, Info_ValueForKey( cstate.updateInfoString, "motd" ), 0);
	// print any server info (server full, bad version, etc)
	if ( cstate.connState < CA_CONNECTED ) {
		Text_PaintCenter_AutoWrapped(centerPoint, yStart + 176, 630, 20, scale, colorWhite, cstate.messageString, 0);
	}

	if ( lastConnState > cstate.connState ) {
		lastLoadingText[0] = '\0';
	}
	lastConnState = cstate.connState;

	switch ( cstate.connState ) {
	case CA_CONNECTING:
		s = va("Awaiting connection...%i", cstate.connectPacketCount);
		break;
	case CA_CHALLENGING:
		s = va("Awaiting challenge...%i", cstate.connectPacketCount);
		break;
	case CA_CONNECTED: {
		char downloadName[MAX_INFO_VALUE];

			trap_Cvar_VariableStringBuffer( "cl_downloadName", downloadName, sizeof(downloadName) );
			if (*downloadName) {
				UI_DisplayDownloadInfo( downloadName, centerPoint, yStart, scale );
				return;
			}
		}
		s = "Awaiting gamestate...";
		break;
	case CA_LOADING:
		return;
	case CA_PRIMED:
		return;
	default:
		return;
	}


	if (Q_stricmp(cstate.servername,"localhost")) {
		Text_PaintCenter(centerPoint, yStart + 80, scale, colorWhite, s, 0);
	}

	// password required / connection rejected information goes here
}

/*
=================
UI_DoServerRefresh
=================
*/

static void UI_DoServerRefresh( void )
{
	qboolean wait = qfalse;

	if (!uiInfo.serverStatus.refreshActive) {
		return;
	}
	if (ui_netSource.integer != UIAS_FAVORITES) {
		if (ui_netSource.integer == UIAS_LOCAL) {
			if (!trap_LAN_GetServerCount(AS_LOCAL)) {
				wait = qtrue;
			}
		} else {
			if (trap_LAN_GetServerCount(AS_GLOBAL) < 0) {
				wait = qtrue;
			}
		}
	}

	if (uiInfo.uiDC.realTime < uiInfo.serverStatus.refreshtime) {
		if (wait) {
			return;
		}
	}

	// if still trying to retrieve pings
	if (trap_LAN_UpdateVisiblePings(UI_SourceForLAN())) {
		uiInfo.serverStatus.refreshtime = uiInfo.uiDC.realTime + 1000;
	} else if (!wait) {
		// get the last servers in the list
		UI_BuildServerDisplayList(2);
		// stop the refresh
		UI_StopServerRefresh();
	} else if ( ui_netSource.integer == UIAS_LOCAL ) {
		// no local servers found, check again
		trap_Cmd_ExecuteText( EXEC_NOW, "localservers\n" );
		uiInfo.serverStatus.refreshtime = uiInfo.uiDC.realTime + 5000;
	}
	//
	UI_BuildServerDisplayList(qfalse);
}

/*
=================
UI_StartServerRefresh
=================
*/
static void UI_StartServerRefresh(qboolean full, qboolean force)
{
	char	*ptr;
	int		lanSource;
	qtime_t q;

	// This function is called with force=qfalse when server browser menu opens or net source changes.
	// Automatically update local and favorite servers.
	// Only auto update master server list if there is no server info cache.
	if ( !force && ( ui_netSource.integer >= UIAS_GLOBAL0 && ui_netSource.integer <= UIAS_GLOBAL5 ) ) {
		if ( trap_LAN_GetServerCount( UI_SourceForLAN() ) > 0 ) {
			return; // have cached list
		}
	}

	trap_RealTime(&q);
	trap_Cvar_Set( va("ui_lastServerRefresh_%i", ui_netSource.integer), va("%s-%i, %i at %i:%02i", MonthAbbrev[q.tm_mon],q.tm_mday, 1900+q.tm_year,q.tm_hour,q.tm_min));

	if (!full) {
		UI_UpdatePendingPings();
		return;
	}

	uiInfo.serverStatus.refreshActive = qtrue;
	uiInfo.serverStatus.nextDisplayRefresh = uiInfo.uiDC.realTime + 1000;
	// clear number of displayed servers
	uiInfo.serverStatus.numDisplayServers = 0;
	uiInfo.serverStatus.numPlayersOnServers = 0;

	lanSource = UI_SourceForLAN();
	// mark all servers as visible so we store ping updates for them
	trap_LAN_MarkServerVisible(lanSource, -1, qtrue);
	// reset all the pings
	trap_LAN_ResetPings(lanSource);
	//
	if( ui_netSource.integer == UIAS_LOCAL ) {
		trap_Cmd_ExecuteText( EXEC_NOW, "localservers\n" );
		uiInfo.serverStatus.refreshtime = uiInfo.uiDC.realTime + 5000;
		return;
	}

	uiInfo.serverStatus.refreshtime = uiInfo.uiDC.realTime + 5000;
	if( ui_netSource.integer >= UIAS_GLOBAL0 && ui_netSource.integer <= UIAS_GLOBAL5 ) {

		ptr = UI_Cvar_VariableString("debug_protocol");
		if (strlen(ptr)) {
			trap_Cmd_ExecuteText( EXEC_NOW, va( "globalservers %d %s full empty\n", ui_netSource.integer - UIAS_GLOBAL0, ptr ) );
		}
		else {
			trap_Cmd_ExecuteText( EXEC_NOW, va( "globalservers %d %d full empty\n", ui_netSource.integer - UIAS_GLOBAL0, (int)trap_Cvar_VariableValue( "protocol" ) ) );
		}
	}
}