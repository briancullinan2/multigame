// Copyright (C) 1999-2000 Id Software, Inc.
//
//
// ui_team.c
//

#include "ui_local.h"


#define TEAMMAIN_FRAME	"menu/art/cut_frame"

#define INGAME_TEAM_VERTICAL_SPACING 23

#define ID_JOINRED		100
#define ID_JOINBLUE		101
#if defined(USE_ADVANCED_GAMES) || defined(USE_ADVANCED_TEAMS)
#define ID_JOINGOLD		104
#define ID_JOINGREEN		105
#endif
#define ID_JOINGAME		102
#define ID_SPECTATE		103


typedef struct
{
	menuframework_s	menu;
	menubitmap_s	frame;
	menutext_s		joinred;
	menutext_s		joinblue;
#if defined(USE_ADVANCED_GAMES) || defined(USE_ADVANCED_TEAMS)
	menutext_s		joingold;
	menutext_s		joingreen;
#endif
	menutext_s		joingame;
	menutext_s		spectate;
} teammain_t;

static teammain_t	s_teammain;

/*
===============
TeamMain_MenuEvent
===============
*/
static void TeamMain_MenuEvent( void* ptr, int event ) {
	if( event != QM_ACTIVATED ) {
		return;
	}

	switch( ((menucommon_s*)ptr)->id ) {
	case ID_JOINRED:
		trap_Cmd_ExecuteText( EXEC_APPEND, "cmd team red\n" );
		UI_ForceMenuOff();
		break;

	case ID_JOINBLUE:
		trap_Cmd_ExecuteText( EXEC_APPEND, "cmd team blue\n" );
		UI_ForceMenuOff();
		break;

#if defined(USE_ADVANCED_GAMES) || defined(USE_ADVANCED_TEAMS)
	case ID_JOINGOLD:
		trap_Cmd_ExecuteText( EXEC_APPEND, "cmd team gold\n" );
		UI_ForceMenuOff();
		break;

	case ID_JOINGREEN:
		trap_Cmd_ExecuteText( EXEC_APPEND, "cmd team green\n" );
		UI_ForceMenuOff();
		break;

#endif

	case ID_JOINGAME:
		trap_Cmd_ExecuteText( EXEC_APPEND, "cmd team free\n" );
		UI_ForceMenuOff();
		break;

	case ID_SPECTATE:
		trap_Cmd_ExecuteText( EXEC_APPEND, "cmd team spectator\n" );
		UI_ForceMenuOff();
		break;
	}
}


/*
===============
TeamMain_MenuInit
===============
*/
void TeamMain_MenuInit( void ) {
	char	info[BIG_INFO_STRING]; // MAX_INFO_STRING
	gametype_t gametype;
	int		y;

	memset( &s_teammain, 0, sizeof(s_teammain) );

	TeamMain_Cache();

	s_teammain.menu.wrapAround = qtrue;
	s_teammain.menu.fullscreen = qfalse;

	s_teammain.frame.generic.type   = MTYPE_BITMAP;
	s_teammain.frame.generic.flags	= QMF_INACTIVE;
	s_teammain.frame.generic.name   = TEAMMAIN_FRAME;
	s_teammain.frame.width			= 300;
	s_teammain.frame.height			= 260;
	s_teammain.frame.generic.x		= (640-s_teammain.frame.width)/2;
	s_teammain.frame.generic.y		= (480-s_teammain.frame.height)/2;

	y = 175; // 188

	s_teammain.joinred.generic.type     = MTYPE_PTEXT;
	s_teammain.joinred.generic.flags    = QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS;
	s_teammain.joinred.generic.id       = ID_JOINRED;
	s_teammain.joinred.generic.callback = TeamMain_MenuEvent;
	s_teammain.joinred.generic.x        = 320;
	s_teammain.joinred.generic.y        = y;
	s_teammain.joinred.string           = "JOIN RED";
	s_teammain.joinred.style            = UI_CENTER|UI_SMALLFONT;
	s_teammain.joinred.color            = colorRed;
	y += INGAME_TEAM_VERTICAL_SPACING;

	s_teammain.joinblue.generic.type     = MTYPE_PTEXT;
	s_teammain.joinblue.generic.flags    = QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS;
	s_teammain.joinblue.generic.id       = ID_JOINBLUE;
	s_teammain.joinblue.generic.callback = TeamMain_MenuEvent;
	s_teammain.joinblue.generic.x        = 320;
	s_teammain.joinblue.generic.y        = y;
	s_teammain.joinblue.string           = "JOIN BLUE";
	s_teammain.joinblue.style            = UI_CENTER|UI_SMALLFONT;
	s_teammain.joinblue.color            = colorBlue;
	y += INGAME_TEAM_VERTICAL_SPACING;

#if defined(USE_ADVANCED_GAMES) || defined(USE_ADVANCED_TEAMS)

	s_teammain.joingold.generic.type     = MTYPE_PTEXT;
	s_teammain.joingold.generic.flags    = QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS;
	s_teammain.joingold.generic.id       = ID_JOINGOLD;
	s_teammain.joingold.generic.callback = TeamMain_MenuEvent;
	s_teammain.joingold.generic.x        = 320;
	s_teammain.joingold.generic.y        = y;
	s_teammain.joingold.string           = "JOIN GOLD";
	s_teammain.joingold.style            = UI_CENTER|UI_SMALLFONT;
	s_teammain.joingold.color            = colorYellow;
	y += INGAME_TEAM_VERTICAL_SPACING;

	s_teammain.joingreen.generic.type     = MTYPE_PTEXT;
	s_teammain.joingreen.generic.flags    = QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS;
	s_teammain.joingreen.generic.id       = ID_JOINGREEN;
	s_teammain.joingreen.generic.callback = TeamMain_MenuEvent;
	s_teammain.joingreen.generic.x        = 320;
	s_teammain.joingreen.generic.y        = y;
	s_teammain.joingreen.string           = "JOIN GREEN";
	s_teammain.joingreen.style            = UI_CENTER|UI_SMALLFONT;
	s_teammain.joingreen.color            = colorGreen;
	y += INGAME_TEAM_VERTICAL_SPACING;

#endif

	s_teammain.joingame.generic.type     = MTYPE_PTEXT;
	s_teammain.joingame.generic.flags    = QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS;
	s_teammain.joingame.generic.id       = ID_JOINGAME;
	s_teammain.joingame.generic.callback = TeamMain_MenuEvent;
	s_teammain.joingame.generic.x        = 320;
	s_teammain.joingame.generic.y        = y;
	s_teammain.joingame.string           = "JOIN GAME";
	s_teammain.joingame.style            = UI_CENTER|UI_SMALLFONT;
	s_teammain.joingame.color            = colorRed;
	y += INGAME_TEAM_VERTICAL_SPACING;

	s_teammain.spectate.generic.type     = MTYPE_PTEXT;
	s_teammain.spectate.generic.flags    = QMF_CENTER_JUSTIFY|QMF_PULSEIFFOCUS;
	s_teammain.spectate.generic.id       = ID_SPECTATE;
	s_teammain.spectate.generic.callback = TeamMain_MenuEvent;
	s_teammain.spectate.generic.x        = 320;
	s_teammain.spectate.generic.y        = y;
	s_teammain.spectate.string           = "SPECTATE";
	s_teammain.spectate.style            = UI_CENTER|UI_SMALLFONT;
	s_teammain.spectate.color            = colorRed;
	y += INGAME_TEAM_VERTICAL_SPACING;

	trap_GetConfigString( CS_SERVERINFO, info, sizeof( info ) );
	gametype = atoi( Info_ValueForKey( info, "g_gametype" ) );
			      
	// set initial states
	switch( gametype ) {
	case GT_SINGLE_PLAYER:
	case GT_FFA:
	case GT_TOURNAMENT:
		s_teammain.joinred.generic.flags  |= QMF_GRAYED;
		s_teammain.joinblue.generic.flags |= QMF_GRAYED;
		break;

	default:
	case GT_TEAM:
	case GT_CTF:
		s_teammain.joingame.generic.flags |= QMF_GRAYED;
		break;
	}

	Menu_AddItem( &s_teammain.menu, (void*) &s_teammain.frame );
	Menu_AddItem( &s_teammain.menu, (void*) &s_teammain.joinred );
	Menu_AddItem( &s_teammain.menu, (void*) &s_teammain.joinblue );
#if defined(USE_ADVANCED_GAMES) || defined(USE_ADVANCED_TEAMS)
	Menu_AddItem( &s_teammain.menu, (void*) &s_teammain.joingold );
	Menu_AddItem( &s_teammain.menu, (void*) &s_teammain.joingreen );
#endif
	Menu_AddItem( &s_teammain.menu, (void*) &s_teammain.joingame );
	Menu_AddItem( &s_teammain.menu, (void*) &s_teammain.spectate );
}


/*
===============
TeamMain_Cache
===============
*/
void TeamMain_Cache( void ) {
	trap_R_RegisterShaderNoMip( TEAMMAIN_FRAME );
}


/*
===============
UI_TeamMainMenu
===============
*/
void UI_TeamMainMenu( void ) {
	TeamMain_MenuInit();
	UI_PushMenu ( &s_teammain.menu );
}
