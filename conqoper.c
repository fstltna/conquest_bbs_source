#include "c_defs.h"

/************************************************************************
 *
 * $Id$
 *
 * Copyright 1999-2004 Jon Trulson under the ARTISTIC LICENSE. (See LICENSE).
 ***********************************************************************/

/*                               C O N Q O P E R */
/*            Copyright (C)1983-1986 by Jef Poskanzer and Craig Leres */
/*    Permission to use, copy, modify, and distribute this software and */
/*    its documentation for any purpose and without fee is hereby granted, */
/*    provided that this copyright notice appear in all copies and in all */
/*    supporting documentation. Jef Poskanzer and Craig Leres make no */
/*    representations about the suitability of this software for any */
/*    purpose. It is provided "as is" without express or implied warranty. */

/**********************************************************************/
/* Unix/C specific porting and supporting code Copyright (C)1994-1996 */
/* by Jon Trulson <jon@radscan.com> under the same terms and          */
/* conditions of the original copyright by Jef Poskanzer and Craig    */
/* Leres.                                                             */
/*                                                                    */
/**********************************************************************/

#define NOEXTERN_GLOBALS
#include "global.h"

#define NOEXTERN_CONF
#include "conf.h"

#include "conqdef.h"
#include "conqcom.h"
#include "conqlb.h"
#include "conqutil.h"

#define NOEXTERN_CONTEXT
#include "context.h"

#include "global.h"
#include "sem.h"
#include "color.h"
#include "ui.h"
#include "options.h"
#include "cd2lb.h"
#include "iolb.h"
#include "cumisc.h"
#include "cuclient.h"
#include "record.h"
#include "clientlb.h"
#include "clntauth.h"
#include "cuclient.h"
#include "display.h"
#include "conqinit.h"

static char cbuf[MID_BUFFER_SIZE]; /* general purpose buffer */

				/* option masks */
#define OP_NONE (unsigned int)(0x00000000)
#define OP_REGENSYSCONF (unsigned int)(0x00000001)
#define OP_INITSTUFF (unsigned int)(0x00000002)
#define OP_DISABLEGAME (unsigned int)(0x00000004)
#define OP_ENABLEGAME (unsigned int)(0x00000008)

static char operName[MAXUSERNAME];

void DoConqoperSig(int sig);
void astoperservice(int sig);
void EnableConqoperSignalHandler(void);
void operStopTimer(void);
void operSetTimer(void);

void bigbang(void);
void debugdisplay( int snum );
void debugplan(void);
int opPlanetMatch( char str[], int *pnum );
void kiss(int snum, int prompt_flg);
void opback( int lastrev, int *savelin );
void operate(void);
void opinfo( int snum );
void opinit(void);
void opPlanetList(void);
void opresign(void);
void oprobot(void);
void opstats(void);
void opTeamList(void);
void opuadd(void);
void oppedit(void);
void opuedit(void);
void watch(void);
int prompt_ship(char buf[], int *snum, int *normal);
void dowatchhelp(void);
void toggle_line(int snum, int old_snum);
char *build_toggle_str(char snum_str[], int snum);
void menu_item( char *option, char *msg_line, int lin, int col );
int DoInit(char InitChar, int cmdline);


/*  conqoper - main program */
int main(int argc, char *argv[])
{
  int i;
  char msgbuf[128];
  unsigned int OptionAction;

  char InitStuffChar = '\0';

  extern char *optarg;
  extern int optind;

  OptionAction = OP_NONE;

  strncpy(operName, clbGetUserLogname(), MAXUSERNAME);
  operName[MAXUSERNAME - 1] = 0;

  if ( ! isagod(-1) )
    {
      printf( "Poor cretins such as yourself lack the");
      error( " skills necessary to use this program.\n" );
    }

  rndini( 0, 0 );		/* initialize random numbers */
  
  while ((i = getopt(argc, argv, "CDEI:")) != EOF)    /* get command args */
    switch (i)
      {
      case 'C': 
	OptionAction |= OP_REGENSYSCONF;
        break;

      case 'D': 
	OptionAction |= OP_DISABLEGAME;
        break;

      case 'E': 
	OptionAction |= OP_ENABLEGAME;
        break;
	
      case 'I':
	OptionAction |= OP_INITSTUFF;
	InitStuffChar = *optarg; /* first character */
	break;

      case '?':
      default: 
	fprintf(stderr, "usage: %s [-C] [-D] [-E] [-I <what>]\n", argv[0]);
	fprintf(stderr, "       -C \t\trebuild systemwide conquestrc file\n");
	fprintf(stderr, "       -D \t\tdisable the game\n");
	fprintf(stderr, "       -E \t\tenable the game\n");
	fprintf(stderr, "       -I <what> \tInitialize <what>, where <what> is:\n");
	fprintf(stderr, "          e - everything\n");
	fprintf(stderr, "          g - game\n");
	fprintf(stderr, "          l - lockwords\n");
	fprintf(stderr, "          m - messages\n");
	fprintf(stderr, "          p - planets\n");
	fprintf(stderr, "          r - robots\n");
	fprintf(stderr, "          s - ships\n");
	fprintf(stderr, "          u - universe\n");
	fprintf(stderr, "          z - zero common block\n");

	exit(1);
	break;
      }

  if ((ConquestGID = getConquestGID()) == ERR)
    {
      fprintf(stderr, "conqoper: getConquestGID() failed\n");
      exit(1);
    }
  

  if (OptionAction != OP_NONE)
    {
      /* need to be conq grp for these */
      if (setgid(ConquestGID) == -1)
	{
	  fprintf(stderr, "conqoper: setgid(): failed\n");
	  exit(1);
	}

      if (semInit() == ERR)
	{
	  fprintf(stderr, "semInit() failed to get semaphores. exiting.\n");
	  exit(1);
	}

      GetSysConf(TRUE);		/* init defaults... */

      /* load conqinitrc */
      cqiLoadRC(CQI_FILE_CONQINITRC, NULL, 0, 0);

      map_common();		/* Map the conquest universe common block */
  
				/* regen sysconf file? */
      if ((OptionAction & OP_REGENSYSCONF) != 0)
	{
	  if (MakeSysConf() == ERR)
	    exit(1);

	}

				/* initialize something? */
      if ((OptionAction & OP_INITSTUFF) != 0)
	{
	  int rv;

	  rv = DoInit(InitStuffChar, TRUE);

	  if (rv != 0)
	    exit(1);
	}

				/* turn the game on */
      if ((OptionAction & OP_ENABLEGAME) != 0)
	{
	  ConqInfo->closed = FALSE;
	  /* Unlock the lockwords (just in case...) */
	  PVUNLOCK(&ConqInfo->lockword);
	  PVUNLOCK(&ConqInfo->lockmesg);
	  Driver->drivstat = DRS_OFF;
	  Driver->drivpid = 0;
	  Driver->drivowner[0] = EOS;
	  fprintf(stdout, "Game enabled.\n");
	}

				/* turn the game off */
      if ((OptionAction & OP_DISABLEGAME) != 0)
	{
	  ConqInfo->closed = TRUE;
	  fprintf(stdout, "Game disabled.\n");
	}

      /* the process *must* exit in this block. */
      exit(0);

    }

  if (GetSysConf(FALSE) == ERR)
    {
#ifdef DEBUG_CONFIG
      utLog("%s@%d: main(): GetSysConf() returned ERR.", __FILE__, __LINE__);
#endif
      /* */
      ;
    }

  Context.updsec = 2;		/* default upd per sec */

  if (GetConf(0) == ERR)	/* use one if there, else defaults
				   A missing or out-of-date conquestrc file
				   will be ignored */
    {
#ifdef DEBUG_CONFIG
      utLog("%s@%d: main(): GetSysConf() returned ERR.", __FILE__, __LINE__);
#endif
      /* */
      ;
    }
  
  if (setgid(ConquestGID) == -1)
    {
      utLog("conqoper: setgid(%d): %s",
	   ConquestGID,
	   strerror(errno));
      fprintf(stderr, "conqoper: setgid(): failed\n");
      exit(1);
    }
  
  if (semInit() == ERR)
    {
      fprintf(stderr, "semInit() failed to get semaphores. exiting.\n");
      exit(1);
    }
  
  /* load conqinitrc */
  cqiLoadRC(CQI_FILE_CONQINITRC, NULL, 0, 0);
  
  map_common();			/* Map the conquest universe common block */
  cdinit();			/* initialize display environment */
  
  Context.unum = MSG_GOD;	/* stow user number */
  Context.snum = ERR;		/* don't display in cdgetp - JET */
  Context.entship = FALSE;	/* never entered a ship */
  Context.histslot = ERR;	/* useless as an op */
  Context.lasttang = Context.lasttdist = 0;
  Context.lasttarg[0] = EOS;
  Context.display = TRUE;
  Context.maxlin = cdlins();	/* number of lines */
  
  Context.maxcol = cdcols();	/* number of columns */
  Context.recmode = RECMODE_OFF;

  sprintf(msgbuf, "OPER: User %s has entered conqoper.",
          operName);
  utLog(msgbuf);			/* log it too... */
  clbStoreMsg( MSG_COMP, MSG_GOD, msgbuf );

  operate();
  
  cdend();
  
  exit(0);
  
}


/*  bigbang - fire a torp from every ship */
/*  SYNOPSIS */
/*    bigbang */
void bigbang(void)
{
  int i, snum, cnt;
  real dir;
  
  dir = 0.0;
  cnt = 0;
  for ( snum = 1; snum <= MAXSHIPS; snum = snum + 1 )
    if ( Ships[snum].status == SS_LIVE )
      {
	for ( i = 0; i < MAXTORPS; i = i + 1 )
	  if ( ! clbLaunch( snum, dir, 1, LAUNCH_NORMAL ) )
	    break;
	  else
	    {
	      dir = utMod360( dir + 40.0 );
	      cnt = cnt + 1;
	    }
      }
  cprintf(MSG_LIN1,0,ALIGN_CENTER, 
  "#%d#bigbang: Fired #%d#%d #%d#torpedos, hoo hah won't they be surprised!", 
	InfoColor,SpecialColor,cnt,InfoColor );
  
  utLog("OPER: %s fired BigBang - %d tropedos",
       operName, cnt);

  return;
  
}


/*  debugdisplay - verbose and ugly version of display */
/*  SYNOPSIS */
/*    int snum */
/*    debugdisplay( snum ) */
void debugdisplay( int snum )
{
  
  /* The following aren't displayed by this routine... */
  /* int ssrpwar(snum,NUMPLANETS)	# self-ruled planets s/he is at war */
  /* int slastmsg(snum)		# last message seen */
  /* int salastmsg(snum)		# last message allowed to be seen */
  /* int smap(snum)			# strategic map or not */
  /* int spfuse(snum)			# tenths until phasers can be fired */
  /* int sscanned(snum,NUMPLAYERTEAMS)	# fuse for which ships have been */
  /* int stalert(snum)			# torp alert! */
  /* int sctime(snum)			# cpu hundreths at last check */
  /* int setime(snum)			# elapsed hundreths at last check */
  /* int scacc(snum)			# accumulated cpu time */
  /* int seacc(snum)			# accumulated elapsed time */
  
  int i, j, unum, lin, tcol, dcol;
  real x;
  char buf[MSGMAXLINE];
  char *torpstr = "???";
  
#define TOFF "OFF"
#define TLAUNCHING "LAUNCHING"
#define TLIVE "LIVE"
#define TDETONATE "DETONATE"
#define TFIREBALL "EXPLODING"
  
  
  cdclrl( 1, MSG_LIN1 - 1 ); 	/* don't clear the message lines */
  unum = Ships[snum].unum;
  
  lin = 1;
  tcol = 1;
  dcol = tcol + 10;
  cprintf(lin,tcol,ALIGN_NONE,"#%d#%s",LabelColor, "    ship:");
  buf[0] = EOS;
  utAppendShip( snum, buf );
  if ( SROBOT(snum) )
    appstr( " (ROBOT)", buf );
  cprintf( lin, dcol,ALIGN_NONE,"#%d#%s",InfoColor,buf );
  lin++;
  cprintf(lin,tcol,ALIGN_NONE,"#%d#%s",LabelColor, "      sx:");
  cprintf(lin,dcol,ALIGN_NONE,"#%d#%0g",InfoColor, oneplace(Ships[snum].x));
  lin++;
  cprintf(lin,tcol,ALIGN_NONE,"#%d#%s",LabelColor, "      sy:");
  cprintf(lin,dcol,ALIGN_NONE,"#%d#%0g",InfoColor, oneplace(Ships[snum].y));
  lin++;
  cprintf(lin,tcol,ALIGN_NONE,"#%d#%s",LabelColor, "     sdx:");
  cprintf(lin,dcol,ALIGN_NONE,"#%d#%0g",InfoColor, oneplace(Ships[snum].dx));
  lin++;
  cprintf(lin,tcol,ALIGN_NONE,"#%d#%s",LabelColor, "     sdy:");
  cprintf(lin,dcol,ALIGN_NONE,"#%d#%0g",InfoColor, oneplace(Ships[snum].dy));
  lin++;
  cprintf(lin,tcol,ALIGN_NONE,"#%d#%s",LabelColor, "  skills:");
  cprintf(lin,dcol,ALIGN_NONE,"#%d#%0g",InfoColor, 
	(oneplace(Ships[snum].kills + Ships[snum].strkills)));
  lin++;
  cprintf(lin,tcol,ALIGN_NONE,"#%d#%s",LabelColor, "   swarp:");
  x = oneplace(Ships[snum].warp);
  if ( x == ORBIT_CW )
    cprintf(lin,dcol,ALIGN_NONE,"#%d#%s",InfoColor, "ORBIT_CW");
  else if ( x == ORBIT_CCW )
    cprintf(lin,dcol,ALIGN_NONE,"#%d#%s",InfoColor, "ORBIT_CCW");
  else
  	cprintf(lin,dcol,ALIGN_NONE,"#%d#%0g",InfoColor, x);
  lin++;
  cprintf(lin,tcol,ALIGN_NONE,"#%d#%s",LabelColor, "  sdwarp:");
  cprintf(lin,dcol,ALIGN_NONE,"#%d#%0g",InfoColor, oneplace(Ships[snum].dwarp));
  lin++;
  cprintf(lin,tcol,ALIGN_NONE,"#%d#%s",LabelColor, "   shead:");
  cprintf(lin,dcol,ALIGN_NONE,"#%d#%0d",InfoColor, round(Ships[snum].head));
  lin++;
  cprintf(lin,tcol,ALIGN_NONE,"#%d#%s",LabelColor, "  sdhead:");
  cprintf(lin,dcol,ALIGN_NONE,"#%d#%0d",InfoColor, round(Ships[snum].dhead));
  lin++;
  cprintf(lin,tcol,ALIGN_NONE,"#%d#%s",LabelColor, " sarmies:");
  cprintf(lin,dcol,ALIGN_NONE,"#%d#%0d",InfoColor, round(Ships[snum].armies));
  
  lin = 1;
  tcol = 23;
  dcol = tcol + 12;
  cprintf(lin,tcol,ALIGN_NONE,"#%d#%s",LabelColor, "      name:");
  if ( Ships[snum].alias != EOS )
  	cprintf(lin,dcol,ALIGN_NONE,"#%d#%s",InfoColor, Ships[snum].alias);
  lin++;
  cprintf(lin,tcol,ALIGN_NONE,"#%d#%s",LabelColor, "  username:");
  buf[0] = EOS;
  if ( unum >= 0 && unum < MAXUSERS )
    {
      c_strcpy( Users[unum].username, buf );
      if ( buf[0] != EOS )
	appchr( ' ', buf );
    }
  appchr( '(', buf );
  utAppendInt( unum, buf );
  appchr( ')', buf );
  cprintf(lin,dcol,ALIGN_NONE,"#%d#%s",InfoColor, buf);
  lin++;
  cprintf(lin,tcol,ALIGN_NONE,"#%d#%s",LabelColor, "     slock:");
  cprintf(lin+1,tcol,ALIGN_NONE,"#%d#%s",LabelColor, "       dtt:");
  i = Ships[snum].lock;
  if ( -i >= 1 && -i <= NUMPLANETS )
    {
  	  cprintf(lin,dcol,ALIGN_NONE,"#%d#%s",InfoColor, Planets[-i].name);
	  cprintf(lin+1,dcol,ALIGN_NONE,"#%d#%0d",InfoColor,
		  round( dist( Ships[snum].x, Ships[snum].y, Planets[-i].x, Planets[-i].y ) ));
    }
  else if ( i != 0 )
  	cprintf(lin,dcol,ALIGN_NONE,"#%d#%0d",InfoColor, i);
  lin+=2;
  cprintf(lin,tcol,ALIGN_NONE,"#%d#%s",LabelColor, "     sfuel:");
  cprintf(lin,dcol,ALIGN_NONE,"#%d#%0d",InfoColor, round(Ships[snum].fuel));
  lin++;
  cprintf(lin,tcol,ALIGN_NONE,"#%d#%s",LabelColor, "       w/e:");
  sprintf( buf, "%d/%d", Ships[snum].weapalloc, Ships[snum].engalloc );
  if ( Ships[snum].wfuse > 0 || Ships[snum].efuse > 0 )
    {
      appstr( " (", buf );
      utAppendInt( Ships[snum].wfuse, buf );
      appchr( '/', buf );
      utAppendInt( Ships[snum].efuse, buf );
      appchr( ')', buf );
    }
  cprintf(lin,dcol,ALIGN_NONE,"#%d#%s",InfoColor, buf);
  lin++;
  cprintf(lin,tcol,ALIGN_NONE,"#%d#%s",LabelColor, "      temp:");
  sprintf( buf, "%d/%d", round(Ships[snum].wtemp), round(Ships[snum].etemp) );
  cprintf(lin,dcol,ALIGN_NONE,"#%d#%s",InfoColor, buf);
  lin++;
  cprintf(lin,tcol,ALIGN_NONE,"#%d#%s",LabelColor, "   ssdfuse:");
  i = Ships[snum].sdfuse;
  buf[0] = EOS;
  if ( i != 0 )
    {
      sprintf( buf, "%d ", i );
    }
  if ( SCLOAKED(snum) )
    appstr( "(CLOAKED)", buf );
  cprintf(lin,dcol,ALIGN_NONE,"#%d#%s",LabelColor, buf);
  lin++;
  cprintf(lin,tcol,ALIGN_NONE,"#%d#%s",LabelColor, "      spid:");
  i = Ships[snum].pid;
  if ( i != 0 )
    {
/*      sprintf( buf, "%d", i ); */
  	  cprintf(lin,dcol,ALIGN_NONE,"#%d#%d",InfoColor, i);
    }
  lin++;
  cprintf(lin,tcol,ALIGN_NONE,"#%d#%s",LabelColor, "slastblast:");
  cprintf(lin,dcol,ALIGN_NONE,"#%d#%0g",InfoColor, oneplace(Ships[snum].lastblast));
  lin++;
  cprintf(lin,tcol,ALIGN_NONE,"#%d#%s",LabelColor, "slastphase:");
  cprintf(lin,dcol,ALIGN_NONE,"#%d#%0g",InfoColor, oneplace(Ships[snum].lastphase));
  
  lin = 1;
  tcol = 57;
  dcol = tcol + 12;
  cprintf(lin,tcol,ALIGN_NONE,"#%d#%s",LabelColor, "   sstatus:");
  buf[0] = EOS;
  utAppendShipStatus( Ships[snum].status, buf );
  cprintf(lin,dcol,ALIGN_NONE,"#%d#%s",InfoColor, buf);
  lin++;
  cprintf(lin,tcol,ALIGN_NONE,"#%d#%s",LabelColor, " skilledby:");
  i = Ships[snum].killedby;
  if ( i != 0 )
    {
      buf[0] = EOS;
      utAppendKilledBy( Ships[snum].killedby, buf );
	  cprintf(lin,dcol,ALIGN_NONE,"#%d#%s",InfoColor, buf);
    }
  lin++;
  cprintf(lin,tcol,ALIGN_NONE,"#%d#%s",LabelColor, "   shields:");
  cprintf(lin,dcol,ALIGN_NONE,"#%d#%0d",InfoColor, round(Ships[snum].shields));
  if ( ! SSHUP(snum) )
  	cprintf(lin,dcol+5,ALIGN_NONE,"#%d#%c",InfoColor, 'D');
  else
  	cprintf(lin,dcol+5,ALIGN_NONE,"#%d#%c",InfoColor, 'U');
  lin++;
  cprintf(lin,tcol,ALIGN_NONE,"#%d#%s",LabelColor, "   sdamage:");
  cprintf(lin,dcol,ALIGN_NONE,"#%d#%0d",InfoColor, round(Ships[snum].damage));
  if ( SREPAIR(snum) )
  	cprintf(lin,dcol+5,ALIGN_NONE,"#%d#%c",InfoColor, 'R');
  lin++;
  cprintf(lin,tcol,ALIGN_NONE,"#%d#%s",LabelColor, "  stowedby:");
  i = Ships[snum].towedby;
  if ( i != 0 )
    {
      buf[0] = EOS;
      utAppendShip( i, buf );
  	  cprintf(lin,dcol,ALIGN_NONE,"#%d#%s",InfoColor, buf);
    }
  lin++;
  cprintf(lin,tcol,ALIGN_NONE,"#%d#%s",LabelColor, "   stowing:");
  i = Ships[snum].towing;
  if ( i != 0 )
    {
      buf[0] = EOS;
      utAppendShip( i, buf );
  	  cprintf(lin,dcol,ALIGN_NONE,"#%d#%s",InfoColor, buf);
    }
  lin++;
  cprintf(lin,tcol,ALIGN_NONE,"#%d#%s",LabelColor, "      swar:");
  buf[0] = '(';
  for ( i = 0; i < NUMPLAYERTEAMS; i = i + 1 )
    if ( Ships[snum].war[i] )
      buf[i+1] = Teams[i].teamchar;
    else
      buf[i+1] = '-';
  buf[NUMPLAYERTEAMS+1] = ')';
  buf[NUMPLAYERTEAMS+2] = EOS;
  fold( buf );
  cprintf(lin,dcol,ALIGN_NONE,"#%d#%s",InfoColor, buf);
  
  lin++;
  cprintf(lin,tcol,ALIGN_NONE,"#%d#%s",LabelColor, "     srwar:");
  buf[0] = '(';
  for ( i = 0; i < NUMPLAYERTEAMS; i = i + 1 )
    if ( Ships[snum].rwar[i] )
      buf[i+1] = Teams[i].teamchar;
    else
      buf[i+1] = '-';
  buf[NUMPLAYERTEAMS+1] = ')';
  buf[NUMPLAYERTEAMS+2] = EOS;
  cprintf(lin,dcol,ALIGN_NONE,"#%d#%s",InfoColor, buf);
  
  lin ++;

  cprintf(lin,tcol,ALIGN_NONE,"#%d#%s",LabelColor, "     flags:");
  cprintf(lin,dcol,ALIGN_NONE,"#%d#0x%04x",InfoColor, Ships[snum].flags);

  lin++;

  cprintf(lin,tcol,ALIGN_NONE,"#%d#%s",LabelColor, "   saction:");
  i = Ships[snum].action;
  if ( i != 0 )
    {
      robstr( i, buf );
	  cprintf(lin,dcol,ALIGN_NONE,"#%d#%s",InfoColor, buf);
    }
  
  lin = (Context.maxlin - (Context.maxlin - MSG_LIN1)) - (MAXTORPS+1);  /* dwp */
  cprintf(lin,3,ALIGN_NONE,"#%d#%s",LabelColor,
	 "tstatus    tfuse    tmult       tx       ty      tdx      tdy     twar");
  for ( i = 0; i < MAXTORPS; i = i + 1 )
    {
      lin++;
      switch(Ships[snum].torps[i].status)
	{
	case TS_OFF:
	  torpstr = TOFF;
	  break;
	case TS_LAUNCHING:
	  torpstr = TLAUNCHING;
	  break;
	case TS_LIVE:
	  torpstr = TLIVE;
	  break;
	case TS_DETONATE:
	  torpstr = TDETONATE;
	  break;
	case TS_FIREBALL:
	  torpstr = TFIREBALL;
	  break;
	}
      cprintf(lin,3,ALIGN_NONE,"#%d#%s",InfoColor, torpstr);
      if ( Ships[snum].torps[i].status != TS_OFF )
	{
	  cprintf(lin,13,ALIGN_NONE,"#%d#%6d",InfoColor, Ships[snum].torps[i].fuse);
	  cprintf(lin,19,ALIGN_NONE,"#%d#%9g",InfoColor, oneplace(Ships[snum].torps[i].mult));
	  cprintf(lin,28,ALIGN_NONE,"#%d#%9g",InfoColor, oneplace(Ships[snum].torps[i].x));
	  cprintf(lin,37,ALIGN_NONE,"#%d#%9g",InfoColor, oneplace(Ships[snum].torps[i].y));
	  cprintf(lin,46,ALIGN_NONE,"#%d#%9g",InfoColor, oneplace(Ships[snum].torps[i].dx));
	  cprintf(lin,55,ALIGN_NONE,"#%d#%9g",InfoColor, oneplace(Ships[snum].torps[i].dy));
	  buf[0] = '(';
	  for ( j = 0; j < NUMPLAYERTEAMS; j++ )
	    if ( Ships[snum].torps[i].war[j] )
	      buf[j+1] = Teams[j].teamchar;
	    else
	      buf[j+1] = '-';
	  buf[NUMPLAYERTEAMS+1] = ')';
	  buf[NUMPLAYERTEAMS+2] = EOS;
	  cprintf(lin,67,ALIGN_NONE,"#%d#%s",InfoColor, buf);
	}
    }
  
  cdmove( 1, 1 );
  cdrefresh();
  
  return;
  
}


/*  debugplan - debugging planet list */
/*  SYNOPSIS */
/*    debugplan */
void debugplan(void)
{
  
  int i, j, k, cmd, lin, col, olin;
  int outattr;
  static int sv[NUMPLANETS + 1];
  char junk[10], uninhab[20];
  char hd0[MSGMAXLINE*4];
  char *hd1="D E B U G G I N G  P L A N E T   L I S T";
  string hd2="planet        C T arm uih scan        planet        C T arm uih scan";
  char hd3[BUFFER_SIZE];
  int FirstTime = TRUE;
  int PlanetOffset;             /* offset into NUMPLANETS for this page */
  int PlanetIdx = 0;
  int Done;


  if (FirstTime == TRUE)
    {
      FirstTime = FALSE;
      sprintf(hd0,
	      "#%d#%s#%d#%s#%d#%s#%d#%s",
	      LabelColor,
		  hd1,
	      InfoColor,
		  "  ('",
	      SpecialColor,
		  "-", 
	      InfoColor,
		  "' = hidden)");

      for ( i = 1; i <= NUMPLANETS; i = i + 1 )
	sv[i] = i;
      clbSortPlanets( sv );
    }
  
  strcpy( hd3, hd2 );
  for ( i = 0; hd3[i] != EOS; i++ )
    if ( hd3[i] != ' ' )
      hd3[i] = '-';

  PlanetIdx = 0;

  PlanetOffset = 1;
  cdclear();
  Done = FALSE;
  
  cdclear();
  
  Done = FALSE;
  do
    {
      cdclra(0, 0, MSG_LIN1 + 2, Context.maxcol - 1);
      PlanetIdx = 0;
      
      lin = 1;
      
      cprintf(lin,0,ALIGN_CENTER,"%s", hd0 );
      
      lin++;
      cprintf( lin,0,ALIGN_CENTER,"#%d#%s", LabelColor, hd2 );
      lin++;
      cprintf( lin,0,ALIGN_CENTER,"#%d#%s", LabelColor, hd3 );
      lin++;
      olin = lin;
      col = 6;
      
      PlanetIdx = 0;
      
      if (PlanetOffset <= NUMPLANETS)
        {
          while ((PlanetOffset + PlanetIdx) <= NUMPLANETS)
            {
              i = PlanetOffset + PlanetIdx;
              PlanetIdx++;
              k = sv[i];
	      
	      for ( j = 0; j < NUMPLAYERTEAMS; j++ )
		if ( Planets[k].scanned[j] && (j >= 0 && j < NUMPLAYERTEAMS) )
		  junk[j] = Teams[j].teamchar;
		else
		  junk[j] = '-';
	      junk[j] = EOS;
	      j = Planets[k].uninhabtime;
	      if ( j != 0 )
		sprintf( uninhab, "%d", j );
	      else
		uninhab[0] = EOS;
	      
	      switch(Planets[k].type)
		{
		case PLANET_SUN:
		  outattr = RedLevelColor;
		  break;
		case PLANET_CLASSM:
		  outattr = GreenLevelColor;
		  break;
		case PLANET_DEAD:
		  outattr = YellowLevelColor;
		  break;
		case PLANET_CLASSA:
		case PLANET_CLASSO:
		case PLANET_CLASSZ:
		  outattr = CQC_A_BOLD;
		  break;
		case PLANET_GHOST:
		  outattr = NoColor;
		  break;
		default:
		  outattr = SpecialColor;
		  break;
		}
		  
	      cprintf(lin, col, ALIGN_NONE,
		      "#%d#%-13s %c %c %3d %3s %4s",
		      outattr, 
		      Planets[k].name, 
		      ConqInfo->chrplanets[Planets[k].type], 
		      Teams[Planets[k].team].teamchar,
		      Planets[k].armies, 
		      uninhab, 
		      junk );
	      
	      if ( ! Planets[k].real )
		cprintf(lin,col-2,ALIGN_NONE, "#%d#%c", SpecialColor, '-');
	      
	      lin++;
	      if ( lin == MSG_LIN2 )
		{
		  if (col == 44)
		    break;	/* out of while */
		  lin = olin;
		  col = 44;
		}
	      uiPutColor(0);
	    } /* while */
	  
	  if ((PlanetOffset + PlanetIdx) > NUMPLANETS)
	    mcuPutPrompt( MTXT_DONE, MSG_LIN2 ); /* last page? */
	  else
	    mcuPutPrompt( MTXT_MORE, MSG_LIN2 );

          cdrefresh();
	  
          if (iogtimed( &cmd, 1.0 ))
            {                   /* got a char */
              if (cmd != ' ')
                {               /* quit */
                  Done = TRUE;
                }
              else
                {               /* some other key... */
		  /* setup for new page */
                  PlanetOffset += PlanetIdx;
                  if (PlanetOffset > NUMPLANETS)
                    {           /* pointless to continue */
                      Done = TRUE;
                    }
                }
            }
	  
	  /* didn't get a char, update */
        } /* if PlanetOffset <= NUMPLANETS */
      else
	Done = TRUE;            /* else PlanetOffset > NUMPLANETS */
      
    } while(Done != TRUE); /* do */
  
  return;
  
}


/*  gplanmatch - GOD's check if a string matches a planet name */
/*  SYNOPSIS */
/*    int gplanmatch, pnum */
/*    char str() */
/*    int status */
/*    status = opPlanetMatch( str, pnum ) */
int opPlanetMatch( char str[], int *pnum )
{
  int i;
  
  if ( alldig( str ) == TRUE )
    {
      i = 0;
      if ( ! utSafeCToI( pnum, str, i ) )
	return ( FALSE );
      if ( *pnum < 1 || *pnum > NUMPLANETS )
	return ( FALSE );
    }
  else
    return ( clbPlanetMatch( str, pnum, TRUE ) );
  
  return ( TRUE );
  
}


/*  kiss - give the kiss of death */
/*  SYNOPSIS */
/*    kiss */
void kiss(int snum, int prompt_flg)
{
  
  int i, unum;
  char ch, buf[MSGMAXLINE], mbuf[MSGMAXLINE], ssbuf[MSGMAXLINE];
  int didany;
  char *prompt_str = "Kill what (<cr> for driver)? ";
  char *kill_driver_str = "Killing the driver."; 
  char *cant_kill_ship_str = "You can't kill ship %c%d (%s) status (%s).";
  char *kill_ship_str1 = "Killing ship %c%d (%s).";
  char *kill_ship_str2 = "Killing ship %c%d (%s) user (%s).";
  char *nobody_str = "Nobody here but us GODs.";
  char *no_user_str = "No such user.";
  char *no_ship_str = "No such ship.";
  char *not_flying_str = "User %s (%s) isn't flying right now.";

  /* Find out what to kill. */
  if (prompt_flg)
    {
      cdclrl( MSG_LIN1, 2 );
      if (snum == 0)
	buf[0] = EOS;
      else
	sprintf(buf, "%d", snum);

      ch = (char)cdgetx( prompt_str, MSG_LIN1, 1, TERMS, buf, MSGMAXLINE,
			 TRUE);
      if ( ch == TERM_ABORT )
	{
	  cdclrl( MSG_LIN1, 1 );
	  cdmove( 1, 1 );
	  return;
	}
      utDeleteBlanks( buf );
    }
  else 
    {
      if (snum == 0)
	return;
      else
	sprintf(buf,"%d",snum);
    }
  
  /* Kill the driver? */
  if ( buf[0] == EOS )
    {
      cdclrl( MSG_LIN1, 1 ); 
      sprintf(mbuf,"%s", kill_driver_str);
      cdputs( mbuf, MSG_LIN1, 1 );
      if ( mcuConfirm() )
	if ( Driver->drivstat == DRS_RUNNING )
	  Driver->drivstat = DRS_KAMIKAZE;
      cdclrl( MSG_LIN1, 2 );
      cdmove( 1, 1 );
      utLog("OPER: %s killed the driver", operName);
      return;
    }
  
  /* Kill a ship? */
  if ( alldig( buf ) == TRUE )
    {
      i = 0;
      utSafeCToI( &snum, buf, i );		/* ignore status */
      if ( snum < 1 || snum > MAXSHIPS )
	cdputs( no_ship_str, MSG_LIN2, 1 );
      else if ( Ships[snum].status != SS_LIVE ) {
	cdclrl( MSG_LIN1, 1 );
	ssbuf[0] = EOS; 
	utAppendShipStatus( Ships[snum].status, ssbuf);
	sprintf(mbuf, cant_kill_ship_str,
		Teams[Ships[snum].team].teamchar, 
		snum, 
		Ships[snum].alias, 
		ssbuf);
	cdputs( mbuf, MSG_LIN1, 1 );
      }
      else {
	cdclrl( MSG_LIN1, 1 );
	sprintf(mbuf, kill_ship_str1,
		Teams[Ships[snum].team].teamchar, snum, Ships[snum].alias);
	cdputs( mbuf, MSG_LIN1, 1 );
	if ( mcuConfirm() )
	  {
	    clbKillShip( snum, KB_GOD );
	    cdclrl( MSG_LIN2, 1 );
	    utLog("OPER: %s killed ship %d",
		 operName, snum);
	  }
	cdclrl( MSG_LIN1, 1 );
      }
      cdmove( 1, 1 );
      return;
    }
  
  /* Kill EVERYBODY? */
  if ( utStringMatch( buf, "all", FALSE ) )
    {
      didany = FALSE;
      for ( snum = 1; snum <= MAXSHIPS; snum++ )
	if ( Ships[snum].status == SS_LIVE )
	  {
	    didany = TRUE;
	    cdclrl( MSG_LIN1, 1 );
	    sprintf(buf, kill_ship_str1,
		    Teams[Ships[snum].team].teamchar, 
		    snum, 
		    Ships[snum].alias);
	    cdputs( buf, MSG_LIN1, 1 );
	    if ( mcuConfirm() )
	      {
		utLog("OPER: %s killed ship %d",
		     operName, snum);
		clbKillShip( snum, KB_GOD );
	      }
	  }
      if ( didany )
	cdclrl( MSG_LIN1, 2 );
      else
	cdputs( nobody_str, MSG_LIN2, 1 );
      cdmove( 1, 1 );
      return;
    }
  
  /* Kill a user? */
  if ( ! clbGetUserNum( &unum, buf, -1 ) )
    {
      cdputs( no_user_str, MSG_LIN2, 1 );
      cdmove( 0, 0 );
      return;
    }
  
  /* Yes. */
  didany = FALSE;
  for ( snum = 1; snum <= MAXSHIPS; snum++ )
    if ( Ships[snum].status == SS_LIVE )
      if ( Ships[snum].unum == unum )
	{
	  didany = TRUE;
	  cdclrl( MSG_LIN1, 1 );
	  sprintf(mbuf, kill_ship_str2,
		Teams[Ships[snum].team].teamchar, 
		  snum, 
		  Ships[snum].alias, 
		  buf);
	  cdputs( mbuf, MSG_LIN1, 1 );
	  if ( mcuConfirm() )
		  {
	    clbKillShip( snum, KB_GOD );
	    cdclrl( MSG_LIN2, 1 );
	    utLog("OPER: %s killed ship %d",
		 operName, snum);
	  }
	}
  if ( ! didany ) {
	cdclrl( MSG_LIN1, 1 );
	sprintf(mbuf, not_flying_str, Users[unum].username, 
		Users[unum].alias);
	cdputs( mbuf, MSG_LIN1, 1 );
  }
  else
    cdclrl( MSG_LIN1, 2 );
  
  return;
  
}


/*  opback - put up the background for the operator program */
/*  SYNOPSIS */
/*    int lastrev, savelin */
/*    opback( lastrev, savelin ) */
void opback( int lastrev, int *savelin )
{
  int i, lin, col;
  char cbuf[MSGMAXLINE];
  extern char *ConquestVersion;
  extern char *ConquestDate;
  
  int FirstTime = TRUE;
  static char sfmt[MSGMAXLINE * 2];

  if (FirstTime == TRUE)
    {
      FirstTime = FALSE;
      sprintf(sfmt,
	      "#%d#(#%d#%%c#%d#) - %%s",
	      LabelColor,
	      InfoColor,
	      LabelColor);
	}

  cdclear();
  
  lin = 1;
  if ( lastrev == COMMONSTAMP ) 
    {
      uiPutColor(NoColor|CQC_A_BOLD);
      cdputc( "CONQUEST OPERATOR PROGRAM", lin );
      uiPutColor(YellowLevelColor);
      sprintf( cbuf, "%s (%s)",
	       ConquestVersion, ConquestDate);
      cdputc( cbuf, lin+1 );
    }
  else
    {
      uiPutColor(RedLevelColor);
      sprintf( cbuf, "CONQUEST COMMON BLOCK MISMATCH %d != %d",
	       lastrev, COMMONSTAMP );
      cdputc( cbuf, lin );
      uiPutColor(0);
    }
  
  EnableConqoperSignalHandler(); /* enable trapping of interesting signals */

  lin++;
  
  lin+=2;
  *savelin = lin;
  lin+=3;
  
  cprintf(lin,0,ALIGN_CENTER,"#%d#%s",NoColor, "Options:");
  lin+=2;
  i = lin;
  
  col = 5;
  cprintf(lin,col,ALIGN_NONE,sfmt, 'f', "flip the open/closed flag");
  lin++;
  cprintf(lin,col,ALIGN_NONE,sfmt, 'd', "flip the doomsday machine!");
  lin++;
  cprintf(lin,col,ALIGN_NONE,sfmt, 'h', "hold the driver");
  lin++;
  cprintf(lin,col,ALIGN_NONE,sfmt, 'I', "initialize");
  lin++;
  cprintf(lin,col,ALIGN_NONE,sfmt, 'b', "big bang");
  lin++;
  cprintf(lin,col,ALIGN_NONE,sfmt, 'H', "user history");
  lin++;
  cprintf(lin,col,ALIGN_NONE,sfmt, '/', "player list");
  lin++;
  cprintf(lin,col,ALIGN_NONE,sfmt, '\\', "full player list");
  lin++;
  cprintf(lin,col,ALIGN_NONE,sfmt, '?', "planet list");
  lin++;
  cprintf(lin,col,ALIGN_NONE,sfmt, '$', "debugging planet list");
  lin++;
  cprintf(lin,col,ALIGN_NONE,sfmt, 'p', "edit a planet");
  lin++;
  cprintf(lin,col,ALIGN_NONE,sfmt, 'w', "watch a ship");
  lin++;
  cprintf(lin,col,ALIGN_NONE,sfmt, 'i', "info");
  
  lin = i;
  col = 45;
  cprintf(lin,col,ALIGN_NONE,sfmt, 'r', "create a robot ship");
  lin++;
  cprintf(lin,col,ALIGN_NONE,sfmt, 'L', "review messages");
  lin++;
  cprintf(lin,col,ALIGN_NONE,sfmt, 'm', "message from GOD");
  lin++;
  cprintf(lin,col,ALIGN_NONE,sfmt, 'O', "options menu");
  lin++;
  cprintf(lin,col,ALIGN_NONE,sfmt, 'T', "team stats");
  lin++;
  cprintf(lin,col,ALIGN_NONE,sfmt, 'U', "user stats");
  lin++;
  cprintf(lin,col,ALIGN_NONE,sfmt, 'S', "more user stats");
  lin++;
  cprintf(lin,col,ALIGN_NONE,sfmt, 's', "special stats page");
  lin++;
  cprintf(lin,col,ALIGN_NONE,sfmt, 'a', "add a user");
  lin++;
  cprintf(lin,col,ALIGN_NONE,sfmt, 'e', "edit a user");
  lin++;
  cprintf(lin,col,ALIGN_NONE,sfmt, 'R', "resign a user");
  lin++;
  cprintf(lin,col,ALIGN_NONE,sfmt, 'k', "kiss of death");
  lin++;
  cprintf(lin,col,ALIGN_NONE,sfmt, 'q', "exit");
  
  return;
  
}

/*  operate - main part of the conquest operator program */
/*  SYNOPSIS */
/*    operate */
void operate(void)
{
  
  int i, lin, savelin;
  int redraw, now, readone;
  int lastrev, msgrand;
  char buf[MSGMAXLINE], junk[MSGMAXLINE];
  char xbuf[MSGMAXLINE];
  int ch;

  ConqInfo->glastmsg = ConqInfo->lastmsg;  

  lastrev = *CBlockRevision;
  utGrand( &msgrand );

  redraw = TRUE;
  while (TRUE)      /* repeat */
    {
      if ( redraw || lastrev != *CBlockRevision )
	{
	  lastrev = *CBlockRevision;
	  opback( lastrev, &savelin );
	  redraw = FALSE;
	}
      /* Line 1. */

      if (*CBlockRevision == COMMONSTAMP)
	{
	  /* game status */
	  if ( ConqInfo->closed )
	    c_strcpy( "CLOSED", junk );
	  else
	    c_strcpy( "open", junk );
	  
	  /* driver status */
	  
	  switch ( Driver->drivstat )
	    {
	    case DRS_OFF:
	      c_strcpy( "OFF", xbuf );
	      break;
	    case DRS_RESTART:
	      c_strcpy( "RESTART", xbuf );
	      break;
	    case DRS_STARTING:
	      c_strcpy( "STARTING", xbuf );
	      break;
	    case DRS_HOLDING:
	      c_strcpy( "HOLDING", xbuf );
	      break;
	    case DRS_RUNNING:
	      c_strcpy( "on", xbuf );
	      break;
	    case DRS_KAMIKAZE:
	      c_strcpy( "KAMIKAZE", xbuf );
	      break;
	    default:
	      c_strcpy( "???", xbuf );
	    }
	  
	  /* eater status */
	  i = Doomsday->status;
	  if ( i == DS_OFF )
	    c_strcpy( "off", buf );
	  else if ( i == DS_LIVE )
	    {
	      c_strcpy( "ON (", buf );
	      i = Doomsday->lock;
	      if ( -i > 0 && -i <= NUMPLANETS )
		appstr( Planets[-i].name, buf );
	      else
		utAppendShip( i, buf );		/* this will handle funny numbers */
	      appchr( ')', buf );
	    }
	  else
	    appstr( "???", buf );
	  
	  lin = savelin;
	  cdclrl( lin, 1 );
	  cprintf(lin,0,ALIGN_CENTER,"#%d#%s#%d#%s#%d#%s#%d#%s#%d#%s#%d#%s",
		  LabelColor,"game ",InfoColor,junk,LabelColor,", driver ",InfoColor,
		  xbuf,LabelColor,", eater ",InfoColor,buf);
	  
	  /* Line 2. */
	  strcpy(buf, semGetStatusStr());

	  lin++;
	  cdclrl( lin, 1 );
	  uiPutColor(SpecialColor);
	  cdputc( buf, lin );
	  uiPutColor(0);
      

	  /* Display a new message, if any. */
	  readone = FALSE;
	  if ( utDeltaGrand( msgrand, &now ) >= NEWMSG_GRAND )
	    if ( utGetMsg( MSG_GOD, &ConqInfo->glastmsg ) )
	      {
		mcuReadMsg( MSG_GOD, ConqInfo->glastmsg, MSG_MSG );
		
#if defined(OPER_MSG_BEEP)
		if (Msgs[ConqInfo->glastmsg].msgfrom != MSG_GOD)
		  cdbeep();
#endif
		readone = TRUE;
		msgrand = now;
	      }
	  cdmove( 1, 1 );
	  cdrefresh();
	  /* Un-read message, if there's a chance it got garbaged. */
	  if ( readone )
	    if ( iochav() )
	      ConqInfo->glastmsg = utModPlusOne( ConqInfo->glastmsg - 1, MAXMESSAGES );

	} /* *CBlockRevision != COMMONSTAMP */
      else 
	{ /* COMMONBLOCK MISMATCH */

	  cprintf(4, 0, ALIGN_CENTER, "#%d#You must (I)nitialize (e)verything.",
		  RedLevelColor);
	  cdmove( 1, 1 );
	  cdrefresh();

	}


      /* Get a char with timeout. */
      if ( ! iogtimed( &ch, 1.0 ) )
	continue;		/* next */
      switch ( ch )
	{
	case 'a':
	  opuadd();
	  redraw = TRUE;
	  break;
	case 'b':
	  if ( mcuConfirm() )
	    bigbang();
	  break;
	case 'd':
	  if ( Doomsday->status == DS_LIVE )
	    {
	      Doomsday->status = DS_OFF;
	      utLog("OPER: %s deactivated the Doomsday machine",
		   operName);
	    }
	  else
	    {
	      clbDoomsday();
	      utLog("OPER: %s has ACTIVATED the Doomsday machine",
		   operName);
	    }
	  break;
	case 'e':
	  opuedit();
	  redraw = TRUE;
	  break;
	case 'f':
	  if ( ConqInfo->closed )
	    {
	      ConqInfo->closed = FALSE;
	      /* Unlock the lockwords (just in case...) */
	      PVUNLOCK(&ConqInfo->lockword);
	      PVUNLOCK(&ConqInfo->lockmesg);
	      Driver->drivstat = DRS_OFF;
	      Driver->drivpid = 0;
	      Driver->drivowner[0] = EOS;
	      
	      utLog("OPER: %s has enabled the game",
		   operName);
	    }
	  else if ( mcuConfirm() )
	    {
	      ConqInfo->closed = TRUE;
	      utLog("OPER: %s has disabled the game",
                   operName);
	    }
	  break;
	case 'h':
	  if ( Driver->drivstat == DRS_HOLDING )
	    Driver->drivstat = DRS_RUNNING;
	  else
	    Driver->drivstat = DRS_HOLDING;
	  break;
	case 'H':
	  mcuHistList( TRUE );
	  redraw = TRUE;
	  break;
	case 'i':
	  opinfo( MSG_GOD );
	  break;
	case 'I':
	  opinit();
	  redraw = TRUE;
	  break;
	case 'k':
	  kiss(0,TRUE);
	  break;
	case 'L':
	  mcuReviewMsgs( MSG_GOD, ConqInfo->glastmsg );
	  break;
	case 'm':
	  cucSendMsg( MSG_GOD, TRUE, FALSE );
	  break;
	case 'O':
	  SysOptsMenu();
	  redraw = TRUE;
	  break;
	case 'p':
	  oppedit();
	  redraw = TRUE;
	  break;
	case 'q':
	case 'Q':
	  return;
	  break;
	case 'r':
	  oprobot();
	  break;
	case 'R':
	  opresign();
	  redraw = TRUE;
	  break;
	case 's':
	  opstats();
	  redraw = TRUE;
	  break;
	case 'S':
	  mcuUserStats( TRUE , 0 ); /* we're always neutral ;-) - dwp */
	  redraw = TRUE;
	  break;
	case 'T':
	  opTeamList();
	  redraw = TRUE;
	  break;
	case 'U':
	  mcuUserList( TRUE, 0 );
	  redraw = TRUE;
	  break;
	case 'w':
	  watch();
	  operStopTimer();		/* to be sure */
	  redraw = TRUE;
	  break;
	case '/':
	  mcuPlayList( TRUE, FALSE, 0 );
	  redraw = TRUE;
	  break;
	case '\\':
	  mcuPlayList( TRUE, TRUE, 0 );
	  redraw = TRUE;
	  break;
	case '?':
	  opPlanetList();
	  redraw = TRUE;
	  break;
	case '$':
	  debugplan();
	  redraw = TRUE;
	  break;
	case 0x0c:
	  cdredo();
	  redraw = TRUE;
	  break;
	case ' ':
	case TERM_NORMAL:
	case EOS:
	  /* do nothing */
	default:
	  cdbeep();
	}
      /* Disable messages for awhile. */
      utGrand( &msgrand );
    } /* repeat */
  
  /* NOTREACHED */
  
}


/*  opinfo - do an operator info command */
/*  SYNOPSIS */
/*    int snum */
/*    opinfo( snum ) */
void opinfo( int snum )
{
  int i, j, now[NOWSIZE];
  char ch;
  string pmt="Information on: ";
  string huh="I don't understand.";
  
  cdclrl( MSG_LIN1, 2 );
  
  cbuf[0] = EOS;
  ch = (char)cdgetx( pmt, MSG_LIN1, 1, TERMS, cbuf, MSGMAXLINE, TRUE );
  if ( ch == TERM_ABORT )
    {
      cdclrl( MSG_LIN1, 1 );
      return;
    }
  
  utDeleteBlanks( cbuf );
  fold( cbuf );
  if ( cbuf[0] == EOS )
    {
      cdclrl( MSG_LIN1, 1 );
      return;
    }
  
  if ( cbuf[0] == 's' && alldig( &cbuf[1] ) == TRUE )
    {
      i = 0;
      utSafeCToI( &j, &cbuf[1], i );		/* ignore status */
      mcuInfoShip( j, snum );
    }
  else if ( alldig( cbuf ) == TRUE )
    {
      i = 0;
      utSafeCToI( &j, cbuf, i );		/* ignore status */
      mcuInfoShip( j, snum );
    }
  else if ( opPlanetMatch( cbuf, &j ) )
    mcuInfoPlanet( "", j, snum );
  else if ( utStringMatch( cbuf, "time", FALSE ) )
    {
      getnow( now, 0 );
      c_strcpy( "It's ", cbuf );
      utAppendTime( now, cbuf );
      appchr( '.', cbuf );
      mcuPutMsg( cbuf, MSG_LIN1 );
      cdmove( MSG_LIN1, 1 );
    }
  else
    {
      cdmove( MSG_LIN2, 1 );
      mcuPutMsg( huh, MSG_LIN2 );
    }
  
  return;
  
}


/*  opinit - handle the various kinds of initialization */
/*  SYNOPSIS */
/*    opinit */
void opinit(void)
{
  
  int i, lin, col, icol;
  char ch, buf[MSGMAXLINE];
  string pmt="Initialize what: ";
  
  
  cdclear();
  cdredo();
  
  lin = 2;
  icol = 11;
  uiPutColor(LabelColor);
  cdputc( "Conquest Initialization", lin );
  
  lin+=3;
  col = icol - 2;
  c_strcpy( "(r)obots", buf );
  i = strlen( buf );
  uiPutColor(InfoColor);
  cdputs( buf, lin, col+1 );
  uiPutColor(CQC_A_BOLD);
  cdbox( lin-1, col, lin+1, col+i+1 );
  col = col + i + 4;
  uiPutColor(LabelColor);
  cdputs( "<-", lin, col );
  col = col + 4;
  c_strcpy( "(e)verything", buf );
  i = strlen( buf );
  uiPutColor(InfoColor);
  cdputs( buf, lin, col+1 );
  uiPutColor(CQC_A_BOLD);
  cdbox( lin-1, col, lin+1, col+i+1 );
  col = col + i + 4;
  uiPutColor(LabelColor);
  cdputs( ".", lin, col );
  col = col + 4;
  c_strcpy( "(z)ero everything", buf );
  i = strlen( buf );
  uiPutColor(InfoColor);
  cdputs( buf, lin, col+1 );
  uiPutColor(CQC_A_BOLD);
  cdbox( lin-1, col, lin+1, col+i+1 );
  
  col = icol + 20;
  lin+=3;
  uiPutColor(LabelColor);
  cdput( '|', lin, col );
  lin++;
  cdput( 'v', lin, col );
  lin+=3;
  
  col = icol;
  c_strcpy( "(s)hips", buf );
  i = strlen( buf );
  uiPutColor(InfoColor);
  cdputs( buf, lin, col+1 );
  uiPutColor(CQC_A_BOLD);
  cdbox( lin-1, col, lin+1, col+i+1 );
  col = col + i + 4;
  uiPutColor(LabelColor);
  cdputs( "<-", lin, col );
  col = col + 4;
  c_strcpy( "(u)niverse", buf );
  i = strlen( buf );
  uiPutColor(InfoColor);
  cdputs( buf, lin, col+1 );
  uiPutColor(CQC_A_BOLD);
  cdbox( lin-1, col, lin+1, col+i+1 );
  col = col + i + 4;
  uiPutColor(LabelColor);
  cdputs( ".", lin, col );
  col = col + 4;
  c_strcpy( "(g)ame", buf );
  i = strlen( buf );
  uiPutColor(InfoColor);
  cdputs( buf, lin, col+1 );
  uiPutColor(CQC_A_BOLD);
  cdbox( lin-1, col, lin+1, col+i+1 );
  col = col + i + 4;
  uiPutColor(LabelColor);
  cdputs( ".", lin, col );
  col = col + 4;
  c_strcpy( "(p)lanets", buf );
  i = strlen( buf );
  uiPutColor(InfoColor);
  cdputs( buf, lin, col+1 );
  uiPutColor(CQC_A_BOLD);
  cdbox( lin-1, col, lin+1, col+i+1 );
  
  col = icol + 20;
  lin+=3;
  uiPutColor(LabelColor);
  cdput( '|', lin, col );
  lin++;
  cdput( 'v', lin, col );
  lin+=3;
  
  col = icol + 15;
  c_strcpy( "(m)essages", buf );
  i = strlen( buf );
  uiPutColor(InfoColor);
  cdputs( buf, lin, col+1 );
  uiPutColor(CQC_A_BOLD);
  cdbox( lin-1, col, lin+1, col+i+1 );
  col = col + i + 8;
  c_strcpy( "(l)ockwords", buf );
  i = strlen( buf );
  uiPutColor(InfoColor);
  cdputs( buf, lin, col+1 );
  uiPutColor(CQC_A_BOLD);
  cdbox( lin-1, col, lin+1, col+i+1 );
  
  while (TRUE)  /*repeat */
    {
      lin = MSG_LIN1;
      col = 30;
      cdclrl( lin, 1 );
      uiPutColor(InfoColor);
      buf[0] = EOS;
      ch = (char)cdgetx( pmt, lin, col, TERMS, buf, MSGMAXLINE, TRUE );
      cdclrl( lin, 1 );
      cdputs( pmt, lin, col );
  	  uiPutColor(0);
      col = col + strlen( pmt );
      if ( ch == TERM_ABORT || buf[0] == EOS )
	break;
      switch ( buf[0] )
	{
	case 'e':
	  cdputs( "everything", lin, col );
	  if ( mcuConfirm() )
	    {
	      DoInit('e', FALSE);
	    }
	  break;
	case 'z':
	  cdputs( "zero everything", lin, col );
	  if ( mcuConfirm() )
	    DoInit('z', FALSE);
	  break;
	case 'u':
	  cdputs( "universe", lin, col );
	  if ( mcuConfirm() )
	    {
	      DoInit('u', FALSE);
	    }
	  break;
	case 'g':
	  cdputs( "game", lin, col );
	  if ( mcuConfirm() )
	    {
	      DoInit('g', FALSE);
	    }
	  break;
	case 'p':
	  cdputs( "planets", lin, col );
	  if ( mcuConfirm() )
	    {
	      DoInit('p', FALSE);
	    }
	  break;
	case 's':
	  cdputs( "ships", lin, col );
	  if ( mcuConfirm() )
	    {
	      DoInit('s', FALSE);
	    }
	  break;
	case 'm':
	  cdputs( "messages", lin, col );
	  if ( mcuConfirm() )
	    {
	      DoInit('m', FALSE);
	    }
	  break;
	case 'l':
	  cdputs( "lockwords", lin, col );
	  if ( mcuConfirm() )
	    {
	      DoInit('l', FALSE);
	    }
	  break;
	case 'r':
	  cdputs( "robots", lin, col );
	  if ( mcuConfirm() )
	    {
	      DoInit('r', FALSE);
	    }
	  break;
	default:
	  cdbeep();
	}
    }
  
  return;
  
}


/*  oppedit - edit a planet's characteristics */
/*  SYNOPSIS */
/*    oppedit */
void oppedit(void)
{
  
  int i, j, lin, col, datacol;
  static int pnum = PNUM_EARTH;
  real x;
  int ch;
  char buf[MSGMAXLINE];
  int attrib;

  int FirstTime = TRUE;
  static char sfmt[MSGMAXLINE * 2];

  if (FirstTime == TRUE)
    {
      FirstTime = FALSE;
      sprintf(sfmt,
	      "#%d#(#%d#%%s#%d#)   %%s",
	      LabelColor,
	      InfoColor,
	      LabelColor);
	}

  
  col = 4;
  datacol = col + 28;
  
  cdredo();
  cdclear();
  while (TRUE) /*repeat*/
    {
      
      /* Display the planet. */
      i = 20;			/* i = 10 */
      j = 57;


	  /* colorize planet name according to type */
      if ( Planets[pnum].type == PLANET_SUN )
	attrib = RedLevelColor;
      else if ( Planets[pnum].type == PLANET_CLASSM )
	attrib = GreenLevelColor;
      else if ( Planets[pnum].type == PLANET_DEAD )
	attrib = YellowLevelColor;
      else if ( Planets[pnum].type == PLANET_CLASSA ||
		Planets[pnum].type == PLANET_CLASSO ||
		Planets[pnum].type == PLANET_CLASSZ ||
		Planets[pnum].type == PLANET_GHOST )   /* white as a ghost ;-) */
	attrib = CQC_A_BOLD;
      else 
	attrib = SpecialColor;
      
				/* if we're doing a sun, use yellow
				   else use attrib set above */
      if (Planets[pnum].type == PLANET_SUN)
	uiPutColor(YellowLevelColor);
      else
	uiPutColor(attrib);
      mcuPutThing(Planets[pnum].type, i, j );
      uiPutColor(0);

	  /* suns have red cores, others are cyan. */
      if (Planets[pnum].type == PLANET_SUN)
	uiPutColor(RedLevelColor);
      else
	uiPutColor(InfoColor);
      cdput( ConqInfo->chrplanets[Planets[pnum].type], i, j + 1);
      uiPutColor(0);

      sprintf(buf, "%s\n", Planets[pnum].name);
      uiPutColor(attrib);
      cdputs( buf, i + 1, j + 2 ); /* -[] */
      uiPutColor(0);
      
      /* Display info about the planet. */
      lin = 4;
      i = pnum;
      cprintf(lin,col,ALIGN_NONE,sfmt, "p", "  Planet:\n");
      cprintf( lin,datacol,ALIGN_NONE,"#%d#%s (%d)", 
		attrib, Planets[pnum].name, pnum );
      
      lin++;
      i = Planets[pnum].primary;
      if ( i == 0 )
	{
      lin++;
	  
	  x = Planets[pnum].orbvel;
	  if ( x == 0.0 )
	    cprintf(lin,col,ALIGN_NONE,sfmt, "v", "  Stationary\n");
	  else
	    {
	      cprintf(lin,col,ALIGN_NONE,sfmt, "v", "Velocity:\n");
	      cprintf( lin,datacol,ALIGN_NONE,"#%d#Warp %f", 
			InfoColor, oneplace(x) );
	    }
	}
      else
	{
	  cprintf(lin,col,ALIGN_NONE,sfmt, "o", "  Orbiting:\n");
	  cprintf( lin,datacol,ALIGN_NONE,"#%d#%s (%d)", 
		InfoColor, Planets[i].name, i );
	  
      lin++;
	  cprintf(lin,col,ALIGN_NONE,sfmt, "v", "  Orbit velocity:\n");
	  cprintf( lin,datacol,ALIGN_NONE,"#%d#%.1f degrees/minute", 
		InfoColor, Planets[pnum].orbvel );
	}
      
      lin++;
      cprintf(lin,col,ALIGN_NONE,sfmt, "r", "  Radius:\n");
      cprintf( lin,datacol,ALIGN_NONE, "#%d#%.1f", InfoColor, Planets[pnum].orbrad );
      
      lin++;
      cprintf(lin,col,ALIGN_NONE,sfmt, "a", "  Angle:\n");
      cprintf( lin,datacol,ALIGN_NONE, "#%d#%.1f", InfoColor, Planets[pnum].orbang );
      
      lin++;
      i = Planets[pnum].type;
      cprintf(lin,col,ALIGN_NONE,sfmt, "t", "  Type:\n");
      cprintf( lin, datacol, ALIGN_NONE, 
	       "#%d#%s (%d)", InfoColor, ConqInfo->ptname[i], i );
      
      lin++;
      i = Planets[pnum].team;
      if ( pnum <= NUMCONPLANETS )
	  {
		cprintf(lin,col,ALIGN_NONE,"#%d#%s",LabelColor,"        Owner team:\n");
	  }
      else
		cprintf(lin,col,ALIGN_NONE,sfmt, "T", "  Owner team:\n");
      cprintf( lin,datacol,ALIGN_NONE, "#%d#%s (%d)", InfoColor,Teams[i].name, i );
      
      lin++;
      cprintf(lin,col,ALIGN_NONE,sfmt, "x,y", "Position:\n");
      cprintf( lin,datacol,ALIGN_NONE, "#%d#%.1f, %.1f",
		InfoColor, Planets[pnum].x, Planets[pnum].y );
      
      lin++;
      cprintf(lin,col,ALIGN_NONE,sfmt, "A", "  Armies:\n");
      cprintf( lin,datacol,ALIGN_NONE, "#%d#%d", InfoColor, Planets[pnum].armies );
      
      lin++;
      cprintf(lin,col,ALIGN_NONE,sfmt, "s", "  Scanned by:\n");
      buf[0] = '(';
      for ( i = 1; i <= NUMPLAYERTEAMS; i = i + 1 )
		if ( Planets[pnum].scanned[i - 1] )
		  buf[i] = Teams[i - 1].teamchar;
		else
		  buf[i] = '-';
      buf[NUMPLAYERTEAMS+1] = ')';
      buf[NUMPLAYERTEAMS+2] = '\0';
      cprintf( lin, datacol,ALIGN_NONE, "#%d#%s",InfoColor, buf);
      
      lin++;
      cprintf(lin,col,ALIGN_NONE,sfmt, "u", "  Uninhabitable time:\n");
      cprintf( lin,datacol,ALIGN_NONE, "#%d#%d", 
		InfoColor, Planets[pnum].uninhabtime );
      
      lin++;
      if ( Planets[pnum].real )
		  cprintf(lin,col,ALIGN_NONE,sfmt, "-", "  Visible\n");
      else
		  cprintf(lin,col,ALIGN_NONE,sfmt, "+", "  Hidden\n");
      
      lin++;
      cprintf(lin,col,ALIGN_NONE,sfmt, "n", "  Change planet name\n");
      
      lin++;
      cprintf(lin,col,ALIGN_NONE,sfmt, "<>", 
		" decrement/increment planet number\n");
      
      cdclra(MSG_LIN1, 0, MSG_LIN1 + 2, Context.maxcol - 1);
      
      cdmove( 0, 0 );
      cdrefresh();
      
      if ( ! iogtimed( &ch, 1.0 ) )
	continue;		/* next */
      switch ( ch )
	{
	case 'a':
	  /* Angle. */
	  ch = mcuGetCX( "New angle? ", MSG_LIN1, 0,
		     TERMS, buf, MSGMAXLINE );
	  if ( ch == TERM_ABORT || buf[0] == EOS )
	    continue;	/* next */
	  utDeleteBlanks( buf );
	  i = 0;
	  if ( ! utSafeCToI( &j, buf, i ) )
	    continue;	/* next */

	  x = ctor( buf);
	  if ( x < 0.0 || x > 360.0 )
	    continue;	/* next */
	  Planets[pnum].orbang = x;
	  break;
	case 'A':
	  /* Armies. */
	  ch = mcuGetCX( "New number of armies? ",
		     MSG_LIN1, 0, TERMS, buf, MSGMAXLINE );
	  if ( ch == TERM_ABORT || buf[0] == EOS )
	    continue;
	  utDeleteBlanks( buf );
	  i = 0;
	  if ( ! utSafeCToI( &j, buf, i ) )
	    continue;
	  Planets[pnum].armies = j;
	  break;
	case 'n':
	  /* New planet name. */
	  ch = mcuGetCX( "New name for this planet? ",
		     MSG_LIN1, 0, TERMS, buf, MAXPLANETNAME );
	  if ( ch != TERM_ABORT && ( ch == TERM_EXTRA || buf[0] != EOS ) )
	    utStcpn( buf, Planets[pnum].name, MAXPLANETNAME );
	  break;
	case 'o':
	  /* New primary. */
	  ch = mcuGetCX( "New planet to orbit? ",
		     MSG_LIN1, 0, TERMS, buf, MAXPLANETNAME );
	  if ( ch == TERM_ABORT || buf[0] == EOS )
	    continue;	/* next */
	  if ( buf[1] == '0' && buf[2] == EOS )
	    Planets[pnum].primary = 0;
	  else if ( opPlanetMatch( buf, &i ) )
	    Planets[pnum].primary = i;
	  break;
	case 'v':
	  /* Velocity. */
	  ch = mcuGetCX( "New velocity? ",
		     MSG_LIN1, 0, TERMS, buf, MSGMAXLINE );
	  if ( ch == TERM_ABORT || buf[0] == EOS )
	    continue;	/* next */
	  utDeleteBlanks( buf );
	  i = 0;
	  if ( ! utSafeCToI( &j, buf, i ) )
	    continue;	/* next */

	  Planets[pnum].orbvel = ctor( buf );
	  break;
	case 'T':
	  /* Rotate owner team. */
	  if ( pnum > NUMCONPLANETS )
	    {
	      Planets[pnum].team = utModPlusOne( Planets[pnum].team + 1, NUMALLTEAMS );
	    }
	  else
	    cdbeep();
	  break;
	case 't':
	  /* Rotate planet type. */
	  Planets[pnum].type = utModPlusOne( Planets[pnum].type + 1, MAXPLANETTYPES );
	  break;
	case 'x':
	  /* X coordinate. */
	  ch = mcuGetCX( "New X coordinate? ",
		     MSG_LIN1, 0, TERMS, buf, MSGMAXLINE );
	  if ( ch == TERM_ABORT || buf[0] == EOS )
	    continue;	/* next */
	  utDeleteBlanks( buf );
	  i = 0;

	  if ( ! utSafeCToI( &j, buf, i ) )
	    continue;	/* next */

	  Planets[pnum].x = ctor( buf );
	  break;
	case 'y':
	  /* Y coordinate. */
	  ch = mcuGetCX( "New Y coordinate? ",
		     MSG_LIN1, 0, TERMS, buf, MSGMAXLINE );
	  if ( ch == TERM_ABORT || buf[0] == EOS )
	    continue;	/* next */
	  utDeleteBlanks( buf );
	  i = 0;
	  if ( ! utSafeCToI( &j, buf, i ) )
	    continue;	/* next */

	  Planets[pnum].y = ctor( buf );
	  break;
	case 's':
	  /* Scanned. */
	  cdputs( "Toggle which team? ", MSG_LIN1, 1 );
	  cdmove( MSG_LIN1, 20 );
	  cdrefresh();
	  ch = (char)toupper( iogchar() );
	  for ( i = 0; i < NUMPLAYERTEAMS; i = i + 1 )
	    if ( ch == Teams[i].teamchar )
	      {
		Planets[pnum].scanned[i] = ! Planets[pnum].scanned[i];
		break;
	      }
	  break;
	  /* Uninhabitable minutes */
	case 'u':
	  ch = mcuGetCX( "New uninhabitable minutes? ",
		     MSG_LIN1, 0, TERMS, buf, MSGMAXLINE );
	  if ( ch == TERM_ABORT || buf[0] == EOS )
	    continue;
	  utDeleteBlanks( buf );
	  i = 0;
	  if ( ! utSafeCToI( &j, buf, i ) )
	    continue;
	  Planets[pnum].uninhabtime = j;
	  break;
	case 'p':
	  ch = mcuGetCX( "New planet to edit? ",
		     MSG_LIN1, 0, TERMS, buf, MAXPLANETNAME );
	  if ( ch == TERM_ABORT || buf[0] == EOS )
	    continue;	/* next */
	  if ( opPlanetMatch( buf, &i ) )
	    pnum = i;
	  break;
	case 'r':
	  /* Radius. */
	  ch = mcuGetCX( "New radius? ",
		     MSG_LIN1, 0, TERMS, buf, MSGMAXLINE );
	  if ( ch == TERM_ABORT || buf[0] == EOS )
	    continue;	/* next */
	  utDeleteBlanks( buf );
	  i = 0;
	  if ( ! utSafeCToI( &j, buf, i ) )
	    continue;	/* next */

	  Planets[pnum].orbrad = ctor( buf );
	  break;
	case '+':
	  /* Now you see it... */
	  Planets[pnum].real = TRUE;
	  break;
	case '-':
	  /* Now you don't */
	  Planets[pnum].real = FALSE;
	  break;
	case '>': /* forward rotate planet number - dwp */
	case KEY_RIGHT:
	case KEY_UP:
	  pnum = mod( pnum + 1, NUMPLANETS );
	  pnum = (pnum == 0) ? NUMPLANETS : pnum;
	  break;
	case '<':  /* reverse rotate planet number - dwp */
	case KEY_LEFT:
	case KEY_DOWN:
	  pnum = (pnum >= 0) ? -pnum : pnum; 
	  pnum = mod( (NUMPLANETS + 1) - (pnum + 1), NUMPLANETS + 1 );
	  pnum = (pnum == 0) ? NUMPLANETS : pnum;
	  break;
	case ' ':
	  /* do no-thing */
	  break;
	case 0x0c:
	  cdredo();
	  break;
	case TERM_NORMAL:
	case TERM_ABORT:
	case 'q':
	case 'Q':
	  return;
	  break;
	default:
	  cdbeep();
	}
    }/* while (TRUE) */
  
  /* NOTREACHED */
  
}


/*  opplanlist - display the planet list for an operator */
/*  SYNOPSIS */
/*    opplanlist */
void opPlanetList(void)
{
  mcuPlanetList( TEAM_NOTEAM, 0 );		/* we get extra info */
}


/*  opresign - resign a user */
/*  SYNOPSIS */
/*    opresign */
void opresign(void)
{
  
  int unum;
  char ch, buf[MSGMAXLINE];
  
  cdclrl( MSG_LIN1, 2 );
  buf[0] = EOS;
  ch = (char)cdgetx( "Resign user: ", MSG_LIN1, 1, TERMS, buf, MSGMAXLINE,
		     TRUE);
  if ( ch == TERM_ABORT )
    {
      cdclrl( MSG_LIN1, 1 );
      return;
    }

  if ( ! clbGetUserNum( &unum, buf, -1 ) )
    {
      cdputs( "No such user.", MSG_LIN2, 1 );
      cdmove( 1, 1 );
      cdrefresh();
      c_sleep( 1.0 );
    }
  else if ( mcuConfirm() )
    {
      utLog("OPER: %s has resigned %s (%s)",
	   operName,
	   Users[unum].username,
	   Users[unum].alias);

      clbResign( unum, TRUE );
    }
  cdclrl( MSG_LIN1, 2 );
  
  return;
  
}


/*  oprobot - handle gratuitous robot creation */
/*  SYNOPSIS */
/*    oprobot */
void oprobot(void)
{
  
  int i, j, snum, unum, num, anum;
  char ch, buf[MSGMAXLINE];
  int warlike;
  char xbuf[MSGMAXLINE];
  
  cdclrl( MSG_LIN1, 2 );
  buf[0] = EOS;
  ch = (char)cdgetx( "Enter username for new robot (Orion, Federation, etc): ",
	      MSG_LIN1, 1, TERMS, buf, MAXUSERNAME, TRUE );
  if ( ch == TERM_ABORT || buf[0] == EOS )
    {
      cdclrl( MSG_LIN1, 1 );
      return;
    }
  /* catch lowercase, uppercase typos - dwp */
  strcpy(xbuf,buf);
  j = strlen(xbuf);
  buf[0] = (char)toupper(xbuf[0]);
  if (j>1)
  	for (i=1;i<j && xbuf[i] != EOS;i++)
		buf[i] = (char)tolower(xbuf[i]);

  if ( ! clbGetUserNum( &unum, buf, -1 ) )
    {
      char *uptr = buf;
				/* un-upper case first char and
				   try again */
      if (*uptr == '@')
	uptr++;
      uptr[0] = (char)tolower(uptr[0]);
      if ( ! clbGetUserNum( &unum, buf, -1 ) )
	{
	  cdputs( "No such user.", MSG_LIN2, 1 );
	  return;
	}
    }
  
  /* Defaults. */
  num = 1;
  warlike = FALSE;
  
  if ( ch == TERM_EXTRA )
    {
      buf[0] = EOS;
      ch = (char)cdgetx( "Enter number desired ([TAB] for warlike): ",
		  MSG_LIN2, 1, TERMS, buf, MAXUSERNAME, TRUE );
      if ( ch == TERM_ABORT )
	{
	  cdclrl( MSG_LIN1, 2 );
	  return;
	}
      warlike = ( ch == TERM_EXTRA );
      utDeleteBlanks( buf );
      i = 0;
      utSafeCToI( &num, buf, i );
      if ( num <= 0 )
	num = 1;
    }
  
  anum = 0;
  for ( i = 1; i <= num; i = i + 1 )
    {
      if ( ! newrob( &snum, unum ) )
	{
	  mcuPutMsg( "Failed to create robot ship.", MSG_LIN1 );
	  break;
	}
      
      anum = anum + 1;
      
      /* If requested, make the robot war-like. */
      if ( warlike )
	{
	  for ( j = 0; j < NUMPLAYERTEAMS; j = j + 1 )
	    Ships[snum].war[j] = TRUE;
	  Ships[snum].war[Ships[snum].team] = FALSE;
	}
    }
  
  /* Report the good news. */
  utLog("OPER: %s created %d %s%s (%s) robot(s)",
       operName,
       anum, 
       (warlike == TRUE) ? "WARLIKE " : "",
       Users[unum].alias, 
       Users[unum].username);

  sprintf( buf, "Automation %s (%s) is now flying ",
	 Users[unum].alias, Users[unum].username );
  if ( anum == 1 )
    utAppendShip( snum, buf );
  else
    {
      utAppendInt( anum, buf );
      appstr( " new ships.", buf );
    }
  cdclrl( MSG_LIN2, 1 );
  i = MSG_LIN1;
  if ( anum != num )
    i = i + 1;
  mcuPutMsg( buf, i );
  
  return;
  
}


/*  opstats - display operator statistics */
/*  SYNOPSIS */
/*    opstats */
void opstats(void)
{
  
  int i, lin, col;
  unsigned long size;
  char buf[MSGMAXLINE], junk[MSGMAXLINE*2], timbuf[32];
  int ch;
  real x;
  string sfmt="#%d#%32s #%d#%12s\n";
  string tfmt="#%d#%32s #%d#%20s\n";
  string pfmt="#%d#%32s #%d#%11.1f%%\n";
  
  col = 8;
  cdclear();
  do /*repeat*/
    {
      lin = 2;
      utFormatSeconds( ConqInfo->ccpuseconds, timbuf );
      cprintf( lin,col,ALIGN_NONE,sfmt, 
		LabelColor,"Conquest cpu time:", InfoColor,timbuf );
      
      lin++;
      i = ConqInfo->celapsedseconds;
      utFormatSeconds( i, timbuf );
      cprintf( lin,col,ALIGN_NONE,sfmt, 
		LabelColor,"Conquest elapsed time:", InfoColor,timbuf );
      
      lin++;
      if ( i == 0 )
	x = 0.0;
      else
	x = oneplace( 100.0 * rfix(ConqInfo->ccpuseconds) / rfix(i) );
      cprintf( lin,col,ALIGN_NONE,pfmt, 
		LabelColor,"Conquest cpu usage:", InfoColor,x);
      
      lin+=2;
      utFormatSeconds( ConqInfo->dcpuseconds, timbuf );
      cprintf( lin,col,ALIGN_NONE,sfmt, 
		LabelColor,"Conqdriv cpu time:", InfoColor,timbuf );
      
      lin++;
      i = ConqInfo->delapsedseconds;
      utFormatSeconds( i, timbuf );
      cprintf( lin,col,ALIGN_NONE,sfmt, 
		LabelColor,"Conqdriv elapsed time:", InfoColor,timbuf );
      
      lin++;
      if ( i == 0 )
	x = 0.0;
      else
	x = oneplace( 100.0 * rfix(ConqInfo->dcpuseconds) / rfix(i) );
      cprintf( lin,col,ALIGN_NONE,pfmt, 
		LabelColor,"Conqdriv cpu usage:", InfoColor,x);
      
      lin+=2;
      utFormatSeconds( ConqInfo->rcpuseconds, timbuf );
      cprintf( lin,col,ALIGN_NONE,sfmt, 
		LabelColor,"Robot cpu time:", InfoColor,timbuf );
      
	  lin++;
      i = ConqInfo->relapsedseconds;
      utFormatSeconds( i, timbuf );
      cprintf( lin,col,ALIGN_NONE,sfmt, 
		LabelColor,"Robot elapsed time:", InfoColor,timbuf );
      
      lin++;
      if ( i == 0 )
	x = 0.0;
      else
	x = ( 100.0 * rfix(ConqInfo->rcpuseconds) / rfix(i) );
      cprintf( lin, col, ALIGN_NONE, pfmt, 
		LabelColor, "Robot cpu usage:", InfoColor, x);
      
      lin+=2;
      cprintf( lin, col, ALIGN_NONE, tfmt, 
		LabelColor, "Last initialize:", InfoColor, ConqInfo->inittime);
      
      lin++;
      cprintf( lin, col, ALIGN_NONE, tfmt, 
		LabelColor, "Last conquer:", InfoColor, ConqInfo->conqtime);
      
      lin++;
      utFormatSeconds( Driver->playtime, timbuf );
      cprintf( lin, col, ALIGN_NONE, sfmt, 
		LabelColor, "Driver time:", InfoColor, timbuf);
      
      lin++;
      utFormatSeconds( Driver->drivtime, timbuf );
      cprintf( lin, col, ALIGN_NONE, sfmt, 
		LabelColor, "Play time:", InfoColor, timbuf);
      
      lin++;
      cprintf( lin, col, ALIGN_NONE, tfmt, 
		LabelColor, "Last upchuck:", InfoColor, ConqInfo->lastupchuck);
      
      lin++;
      utFormatTime( timbuf, 0 );
      cprintf( lin, col, ALIGN_NONE, tfmt, 
		LabelColor, "Current time:", InfoColor, timbuf);
      
      lin+=2;
      if ( Driver->drivowner[0] != EOS )
	sprintf( junk, "%d #%d#(#%d#%s#%d#)", 
		 Driver->drivpid, LabelColor, SpecialColor, 
		 Driver->drivowner, LabelColor );
      else if ( Driver->drivpid != 0 )
	sprintf( junk, "%d", Driver->drivpid );
      else
	junk[0] = EOS;

      if (junk[0] == EOS)
	cprintf( lin,col,ALIGN_NONE, 
		 "#%d#drivsecs = #%d#%03d#%d#, drivcnt = #%d#%d\n",
		 LabelColor, InfoColor, 
		 Driver->drivsecs,LabelColor,InfoColor,Driver->drivcnt);
      else
	cprintf( lin,col,ALIGN_NONE, 
                 "#%d#%s#%d#, drivsecs = #%d#%03d#%d#, drivcnt = #%d#%d\n",
		 InfoColor,junk,LabelColor,InfoColor, 
                 Driver->drivsecs,LabelColor,InfoColor,Driver->drivcnt);
      
      lin++;
      comsize( &size );
      cprintf( lin,col,ALIGN_NONE, 
	       "#%d#%u #%d#bytes (out of #%d#%d#%d#) in the common block.\n",
	       InfoColor,size,LabelColor,InfoColor, SIZEOF_COMMONBLOCK,LabelColor );
      
      lin++;
      sprintf( buf, "#%d#Common ident is #%d#%d", 
	       LabelColor,InfoColor,*CBlockRevision);
      if ( *CBlockRevision != COMMONSTAMP )
	{
	  sprintf( junk, " #%d#(binary ident is #%d#%d#%d#)\n", 
		   LabelColor,InfoColor,COMMONSTAMP,LabelColor );
	  appstr( junk, buf );
	}
      cprintf( lin,col,ALIGN_NONE, "%s",buf);
      
      cdmove( 1, 1 );
      uiPutColor(0);
      cdrefresh();
    }
  while ( !iogtimed( &ch, 1.0 ) ); /* until */
  
  return;
  
}


/*  opteamlist - display the team list for an operator */
/*  SYNOPSIS */
/*    opteamlist */
void opTeamList(void)
{
  
  int ch;
  
  cdclear();
  do /* repeat*/
    {
      mcuTeamList( -1 );
      mcuPutPrompt( MTXT_DONE, MSG_LIN2 );
      cdrefresh();
    }
  while ( !iogtimed( &ch, 1.0 ) ); /* until */
  
}


/*  opuadd - add a user */
/*  SYNOPSIS */
/*    opuadd */
void opuadd(void)
{
  
  int i, unum, team;
  char ch;
  char buf[MSGMAXLINE], junk[MSGMAXLINE], name[MSGMAXLINE];
  char *nameptr;

  cdclrl( MSG_LIN1, 2 );
  name[0] = EOS;
  ch = (char)cdgetx( "Add user: ", MSG_LIN1, 1, TERMS, name, MAXUSERNAME,
		     TRUE);
  /*  utDeleteBlanks( name );*/

  nameptr = name;
  if (*nameptr == '@')
    nameptr++;			/* in case we're adding a remote user */

  if ( ch == TERM_ABORT || nameptr[0] == EOS )
    {
      cdclrl( MSG_LIN1, 1 );
      return;
    }
  if ( clbGetUserNum( &unum, name, -1 ) ) /* don't want to use ptr here */
    {
      cdputs( "That user is already enrolled.", MSG_LIN2, 1 );
      cdmove( 1, 1 );
      cdrefresh();
      c_sleep( 1.0 );
      cdclrl( MSG_LIN1, 2 );
      return;
    }
  for ( team = -1; team == -1; )
    {
      sprintf(junk, "Select a team (%c%c%c%c): ",
	     Teams[TEAM_FEDERATION].teamchar,
	     Teams[TEAM_ROMULAN].teamchar,
	     Teams[TEAM_KLINGON].teamchar,
	     Teams[TEAM_ORION].teamchar);
      
      cdclrl( MSG_LIN1, 1 );
      buf[0] = EOS;
      ch = (char)cdgetx( junk, MSG_LIN1, 1, TERMS, buf, MSGMAXLINE, TRUE );
      if ( ch == TERM_ABORT )
	{
	  cdclrl( MSG_LIN1, 1 );
	  return;
	}
      else if ( ch == TERM_EXTRA && buf[0] == EOS )
	team = rndint( 0, NUMPLAYERTEAMS - 1);
      else
	{
	  ch = (char)toupper( buf[0] );
	  for ( i = 0; i < NUMPLAYERTEAMS; i = i + 1 )
	    if ( Teams[i].teamchar == ch )
	      {
		team = i;
		break;
	      }
	}
    }
  
  
  buf[0] = EOS;
  utAppendTitle( team, buf );
  appchr( ' ', buf );
  i = strlen( buf );

  appstr( nameptr, buf );
  buf[i] = (char)toupper( buf[i] );
  buf[MAXUSERPNAME] = EOS;
  if ( ! clbRegister( nameptr, buf, team, &unum ) )
    {
      cdputs( "Error adding new user.", MSG_LIN2, 1 );
      cdmove( 0, 0 );
      cdrefresh();
      c_sleep( 1.0 );
    }
  else		
    {
      utLog("OPER: %s added user '%s'.",
	   operName, name);

    }
  cdclrl( MSG_LIN1, 2 );
  

  ChangePassword(unum, TRUE);

  return;

}


/*  opuedit - edit a user */
/*  SYNOPSIS */
/*    opuedit */
void opuedit(void)
{

#define MAXUEDITROWS (MAXOPTIONS+2) 

  int i, unum, row = 1, lin, olin, tcol, dcol, lcol, rcol;
  char buf[MSGMAXLINE];
  int ch, left = TRUE;
  char datestr[DATESIZE];
  static char *prompt2 = "any other key to quit.";
  static char *rprompt = "Use arrow keys to position, [SPACE] to modify, [TAB] to change password";
  char *promptptr;

  cdclrl( MSG_LIN1, 2 );
  uiPutColor(InfoColor);
  ch = mcuGetCX( "Edit which user: ", MSG_LIN1, 0, TERMS, buf, MAXUSERNAME );
  if ( ch == TERM_ABORT )
    {
      cdclrl( MSG_LIN1, 2 );
	  uiPutColor(0);
      return;
    }
  /*  utDeleteBlanks( buf );*/

  if ( ! clbGetUserNum( &unum, buf, -1 ) )
    {
      cdclrl( MSG_LIN1, 2 );
      cdputs( "Unknown user.", MSG_LIN1, 1 );
	  uiPutColor(0);
      cdmove( 1, 1 );
      cdrefresh();
      c_sleep( 1.0 );
      return;
    }
  cdclear();
  cdclrl( MSG_LIN1, 2 );

  while (TRUE) /* repeat */
    {
      /* Do the right side first. */
      cdclrl( 1, MSG_LIN1 -1 );

      lin = 1;
      tcol = 43;
      dcol = 62;
      rcol = dcol - 1;
      
      cprintf(lin,tcol,ALIGN_NONE,"#%d#%s", LabelColor,"         Username:");
      cprintf(lin,dcol,ALIGN_NONE,"#%d#%s", InfoColor, Users[unum].username);
      
      lin++;
      cprintf(lin,tcol,ALIGN_NONE,"#%d#%s", LabelColor,"   Multiple count:");
      cprintf(lin,dcol,ALIGN_NONE,"#%d#%0d", InfoColor, 
	      Users[unum].multiple);
      
      lin++;
      for ( i = 0; i < MAXOOPTIONS; i++ )
	{
	  cprintf(lin+i,tcol,ALIGN_NONE,"#%d#%17d:", LabelColor,i);
	  cprintf(lin+i,dcol,ALIGN_NONE,"#%d#%c", RedLevelColor,'F');
	}

      lin+=(MAXOOPTIONS + 1);
      cprintf(lin,tcol,ALIGN_NONE,"#%d#%s", LabelColor,"          Urating:");
      cprintf(lin,dcol,ALIGN_NONE,"#%d#%0g",InfoColor, 
	      oneplace(Users[unum].rating));
      
      lin++;
      cprintf(lin,tcol,ALIGN_NONE,"#%d#%s", LabelColor,"             Uwar:");
      buf[0] = '(';
      for ( i = 0; i < NUMPLAYERTEAMS; i = i + 1 )
	if ( Users[unum].war[i] )
	  buf[i+1] = Teams[i].teamchar;
	else
	  buf[i+1] = '-';
      buf[NUMPLAYERTEAMS+1] = ')';
      buf[NUMPLAYERTEAMS+2] = EOS;
      cprintf(lin,dcol,ALIGN_NONE,"#%d#%s",InfoColor, buf);
      
      lin++;
      cprintf(lin,tcol,ALIGN_NONE,"#%d#%s", LabelColor,"           Urobot:");
      if ( Users[unum].robot )
      	cprintf(lin,dcol,ALIGN_NONE,"#%d#%c",GreenLevelColor, 'T');
      else
      	cprintf(lin,dcol,ALIGN_NONE,"#%d#%c",RedLevelColor, 'F');
      
      /* Now the left side. */
      lin = 1;
      tcol = 3;
      dcol = 22;
      lcol = dcol - 1;
      
      cprintf(lin,tcol,ALIGN_NONE,"#%d#%s", LabelColor,"             Name:");


      cprintf(lin,dcol,ALIGN_NONE,"#%d#%s",InfoColor, 
	      Users[unum].alias);
      
      lin++;
      cprintf(lin,tcol,ALIGN_NONE,"#%d#%s", LabelColor,"             Team:");
      i = Users[unum].team;
      if ( i < 0 || i >= NUMPLAYERTEAMS )
		  cprintf(lin,dcol,ALIGN_NONE,"#%d#%0d",InfoColor, i);
      else
		  cprintf(lin,dcol,ALIGN_NONE,"#%d#%s",InfoColor, Teams[i].name);
      
      lin++;
      for ( i = 0; i < MAXOOPTIONS; i++ )
	{
	  cprintf(lin+i,tcol,ALIGN_NONE,"#%d#%17d:", LabelColor,i);

	  if ( Users[unum].ooptions[i] )
	    cprintf(lin+i,dcol,ALIGN_NONE,"#%d#%c", GreenLevelColor,'T');
	  else
	    cprintf(lin+i,dcol,ALIGN_NONE,"#%d#%c", RedLevelColor,'F');
	}
      cprintf(lin+OOPT_MULTIPLE,tcol,ALIGN_NONE,"#%d#%s", 
		LabelColor,"         Multiple:");
      cprintf(lin+OOPT_SWITCHTEAMS,tcol,ALIGN_NONE,"#%d#%s", 
		LabelColor,"     Switch teams:");
      cprintf(lin+OOPT_PLAYWHENCLOSED,tcol,ALIGN_NONE,"#%d#%s", 
		LabelColor," Play when closed:");
      cprintf(lin+OOPT_SHITLIST,tcol,ALIGN_NONE,"#%d#%s", 
		LabelColor,"          Disable:");
      cprintf(lin+OOPT_OPER,tcol,ALIGN_NONE,"#%d#%s", 
		LabelColor,"Conquest Operator:");
      cprintf(lin+OOPT_LOSE,tcol,ALIGN_NONE,"#%d#%s", 
		LabelColor,"             Lose:");
      cprintf(lin+OOPT_AUTOPILOT,tcol,ALIGN_NONE,"#%d#%s", 
		LabelColor,"        Autopilot:");
      
      lin+=(MAXOOPTIONS + 1);
      cprintf(lin,tcol,ALIGN_NONE,"#%d#%s", LabelColor,"       Last entry:");

      if (Users[unum].lastentry == 0)
	strcpy(datestr, "never");
      else
	utFormatTime(datestr, Users[unum].lastentry);

      cprintf(lin,dcol,ALIGN_NONE,"#%d#%s",InfoColor, 
	      datestr);
      
      lin++;
      cprintf(lin,tcol,ALIGN_NONE,"#%d#%s", LabelColor,"  Elapsed seconds:");
      utFormatSeconds( Users[unum].stats[TSTAT_SECONDS], buf );
      i = dcol + 11 - strlen( buf );
      cprintf(lin,i,ALIGN_NONE,"#%d#%s",InfoColor, buf);
      
      lin++;
      cprintf(lin,tcol,ALIGN_NONE,"#%d#%s", LabelColor,"      Cpu seconds:");
      utFormatSeconds( Users[unum].stats[TSTAT_CPUSECONDS], buf );
      i = dcol + 11 - strlen ( buf );
      cprintf(lin,i,ALIGN_NONE,"#%d#%s",InfoColor, buf);
      
      lin++;
      
      /* Do column 4 of the bottom stuff. */
      olin = lin;
      tcol = 62;
      dcol = 72;
      cprintf(lin,tcol,ALIGN_NONE,"#%d#%s", LabelColor, "Maxkills:");
      cprintf(lin,dcol,ALIGN_NONE,"#%d#%0d",InfoColor, 
      	Users[unum].stats[USTAT_MAXKILLS]);
      
      lin++;
      cprintf(lin,tcol,ALIGN_NONE,"#%d#%s", LabelColor, "Torpedos:");
      cprintf(lin,dcol,ALIGN_NONE,"#%d#%0d",InfoColor,
      	Users[unum].stats[USTAT_TORPS]);
      
      lin++;
      cprintf(lin,tcol,ALIGN_NONE,"#%d#%s", LabelColor, " Phasers:");
      cprintf(lin,dcol,ALIGN_NONE,"#%d#%0d",InfoColor, 
      	Users[unum].stats[USTAT_PHASERS]);
      
      /* Do column 3 of the bottom stuff. */
      lin = olin;
      tcol = 35;
      dcol = 51;
      cprintf(lin,tcol,ALIGN_NONE,"#%d#%s", LabelColor, " Planets taken:");
      cprintf(lin,dcol,ALIGN_NONE,"#%d#%0d",InfoColor,
      	Users[unum].stats[USTAT_CONQPLANETS]);
      
      lin++;
      cprintf(lin,tcol,ALIGN_NONE,"#%d#%s", LabelColor, " Armies bombed:");
      cprintf(lin,dcol,ALIGN_NONE,"#%d#%0d",InfoColor, 
      	Users[unum].stats[USTAT_ARMBOMB]);
      
      lin++;
      cprintf(lin,tcol,ALIGN_NONE,"#%d#%s", LabelColor, "   Ship armies:");
      cprintf(lin,dcol,ALIGN_NONE,"#%d#%0d",InfoColor,
      	Users[unum].stats[USTAT_ARMSHIP]);
      
      /* Do column 2 of the bottom stuff. */
      lin = olin;
      tcol = 18;
      dcol = 29;
      cprintf(lin,tcol,ALIGN_NONE,"#%d#%s", LabelColor, " Conquers:");
      cprintf(lin,dcol,ALIGN_NONE,"#%d#%0d",InfoColor,
      	 Users[unum].stats[USTAT_CONQUERS]);
      
      lin++;
      cprintf(lin,tcol,ALIGN_NONE,"#%d#%s", LabelColor,"    Coups:");
      cprintf(lin,dcol,ALIGN_NONE,"#%d#%0d",InfoColor,
      	Users[unum].stats[USTAT_COUPS]);
      
      lin++;
      cprintf(lin,tcol,ALIGN_NONE,"#%d#%s", LabelColor, "Genocides:");
      cprintf(lin,dcol,ALIGN_NONE,"#%d#%0d",InfoColor, 
      	Users[unum].stats[USTAT_GENOCIDE]);
      
      /* Do column 1 of the bottom stuff. */
      lin = olin;
      tcol = 1;
      dcol = 10;
      cprintf(lin,tcol,ALIGN_NONE,"#%d#%s", LabelColor, "   Wins:");
      cprintf(lin,dcol,ALIGN_NONE,"#%d#%0d",InfoColor, 
      	Users[unum].stats[USTAT_WINS]);
      
      lin++;
      cprintf(lin,tcol,ALIGN_NONE,"#%d#%s", LabelColor, " Losses:");
      cprintf(lin,dcol,ALIGN_NONE,"#%d#%0d",InfoColor, 
      	Users[unum].stats[USTAT_LOSSES]);
      
      lin++;
      cprintf(lin,tcol,ALIGN_NONE,"#%d#%s", LabelColor, "Entries:");
      cprintf(lin,dcol,ALIGN_NONE,"#%d#%0d",InfoColor, 
      	Users[unum].stats[USTAT_ENTRIES]);
      
      promptptr = rprompt;

      cprintf(MSG_LIN1,0,ALIGN_CENTER,"#%d#%s", InfoColor,
	      promptptr);
      cprintf(MSG_LIN2,0,ALIGN_CENTER,"#%d#%s", InfoColor,
	      prompt2);

      if ( left )
	i = lcol;
      else
	i = rcol;

      cdput( '+', row, i );
      cdmove( row, i );
      cdrefresh();
      
      /* Now, get a char and process it. */
      if ( ! iogtimed( &ch, 1.1 ) )
	continue;		/* next */
      switch ( ch )
	{
	case 'a': 
	case 'A': 
	case 'h': 
	case 'H':
	case KEY_LEFT:
	  /* Left. */
	  left = TRUE;
	  break;
	case 'd': 
	case 'D': 
	case 'l': 
	case 'L':
	case KEY_RIGHT:
	  /* Right. */
	  left = FALSE;
	  break;
	case 'w': 
	case 'W': 
	case 'k':
	case 'K':
	case KEY_UP:
	  /* Up. */
	  row = max( row - 1, 1 );
	  break;
	case 'x':
	case  'X':
	case 'j':
	case  'J':
	case KEY_DOWN:
	  /* Down. */
	  row = min( row + 1, MAXUEDITROWS );
	  break;
	case 'y':
	case 'Y':
	case KEY_A1:
	case KEY_HOME:
	  /* Up and left. */
	  left = TRUE;
	  row = max( row - 1, 1 );
	  break;
	case 'e': 
	case 'E':
	case 'u':
	case 'U':
	case KEY_PPAGE:
	case KEY_A3:
	  /* Up and right. */
	  left = FALSE;
	  row = max( row - 1, 1 );
	  break;
	case 'z':
	case 'Z':
	case 'b':
	case 'B':
	case KEY_END:
	case KEY_C1:
	  /* Down and left. */
	  left = TRUE;
	  row = min( row + 1, MAXUEDITROWS );
	  break;
	case 'c':
	case 'C':
	case 'n':
	case 'N':
	case KEY_NPAGE:
	case KEY_C3:
	  /* Down and right. */
	  left = FALSE;
	  row = min( row + 1, MAXUEDITROWS );
	  break;
	case ' ':
	  /* Modify the current entry. */
	  if ( left && row == 1 )
	    {
	      /* Pseudonym. */
	      cdclrl( MSG_LIN2, 1 );
	      ch = mcuGetCX( "Enter a new pseudonym: ",
			 MSG_LIN2, 0, TERMS, buf, MAXUSERPNAME );
	      if ( ch != TERM_ABORT &&
		  ( buf[0] != EOS || ch == TERM_EXTRA ) )
		utStcpn( buf, Users[unum].alias, MAXUSERPNAME ); /* -[] */
	    }
	  else if ( ! left && row == 1 )
	    {
	      /* Username. */
	      cdclrl( MSG_LIN2, 1 );
	      ch = mcuGetCX( "Enter a new username: ",
			 MSG_LIN2, 0, TERMS, buf, MAXUSERNAME );
	      if ( ch != TERM_ABORT && buf[0] != EOS)
	      {
		utDeleteBlanks( buf );
		if ( ! clbGetUserNum( &i, buf, -1 ) )
		  utStcpn( buf, Users[unum].username, MAXUSERNAME );
		else
		  {
		    cdclrl( MSG_LIN1, 2 );
		    cdputc( "That username is already in use.",
			   MSG_LIN2 );
		    cdmove( 1, 1 );
		    cdrefresh();
		    c_sleep( 1.0 );
		  }
	      }
	    }
	  else if ( left && row == 2 )
	    {
	      /* Team. */
	      Users[unum].team = utModPlusOne( Users[unum].team + 1, NUMPLAYERTEAMS );
	    }
	  else if ( ! left && row == 2 )
	    {
	      /* Multiple count. */
	      cdclrl( MSG_LIN2, 1 );
	      ch = mcuGetCX( "Enter new multiple count: ",
			 MSG_LIN2, 0, TERMS, buf, MSGMAXLINE );
	      if ( ch != TERM_ABORT && buf[0] != EOS )
		{
		  utDeleteBlanks( buf );
		  i = 0;
		  utSafeCToI( &(Users[unum].multiple), buf, i );
		}
	    }
	  else
	    {
	      i = row - 3;
	      if ( left )
		if ( i >= 0 && i < MAXOOPTIONS )
		  Users[unum].ooptions[i] = ! Users[unum].ooptions[i];
		else
		  cdbeep();
	      else
		cdbeep();
	    }
	  break;

	case TERM_EXTRA:	/* change passwd */
	  ChangePassword(unum, TRUE);
	  break;
	  
	case 0x0c:
	  cdredo();
	  break;

	case TERM_NORMAL:
	case TERM_ABORT:

	default:
	  return;
	}
    }
  
  /* NOTREACHED */
  
}


/*  watch - peer over someone's shoulder */
/*  SYNOPSIS */
/*    watch */
void watch(void)
{
  
  int snum, tmp_snum, old_snum;
  int ch, normal;
  int msgrand, readone, now;
  char buf[MSGMAXLINE];
  int live_ships = TRUE;
  int toggle_flg = FALSE;   /* jon no like the toggle line ... :-) */

  normal = TRUE;

  if (!prompt_ship(buf, &snum, &normal))
    return;
  else
    {
	  old_snum = tmp_snum = snum;
	  Context.redraw = TRUE;
	  cdclear();
	  cdredo();
	  utGrand( &msgrand );

	  Context.snum = snum;		/* so display knows what to display */
	  operSetTimer();

	  while (TRUE)	/* repeat */
	    {
	      if (!normal)
		Context.display = FALSE; /* can't use it to display debugging */
	      else
		Context.display = TRUE;

		/* set up toggle line display */
		/* cdclrl( MSG_LIN1, 1 ); */
		if (toggle_flg)
                  toggle_line(snum,old_snum);

	    /* Try to display a new message. */
	    readone = FALSE;
	    if ( utDeltaGrand( msgrand, &now ) >= NEWMSG_GRAND )
		if ( utGetMsg( MSG_GOD, &ConqInfo->glastmsg ) )
		  {
		    mcuReadMsg( MSG_GOD, ConqInfo->glastmsg, MSG_MSG );
#if defined(OPER_MSG_BEEP)
		    if (Msgs[ConqInfo->glastmsg].msgfrom != MSG_GOD)
		      cdbeep();
#endif		     
		    msgrand = now;
		    readone = TRUE;
		  }

	      if ( !normal )
		{
		  debugdisplay( snum );
		}
	      
	      /* Un-read message, if there's a chance it got garbaged. */
	      if ( readone )
		if ( iochav() )
		  ConqInfo->glastmsg = utModPlusOne( ConqInfo->glastmsg - 1, MAXMESSAGES );
	      
	      /* Get a char with timeout. */
	      if ( ! iogtimed( &ch, 1.0 ) )
		continue; /* next */
	      cdclrl( MSG_LIN1, 2 );
	      switch ( ch )
		{
		case 'd':    /* flip the doomsday machine (only from doomsday window) */
		  if (snum == DISPLAY_DOOMSDAY)
		    {
		      if ( Doomsday->status == DS_LIVE )
			Doomsday->status = DS_OFF;
		      else
			clbDoomsday();
		    }
		  else
		    cdbeep();
		  break;
		case 'h':
		  operStopTimer();
		  dowatchhelp();
		  Context.redraw = TRUE;
		  operSetTimer();
		  break;
		case 'i':
		  opinfo( MSG_GOD );
		  break;
		case 'k':
		  kiss(Context.snum, TRUE);
		  break;
                case 'M':		/* strategic/tactical map */
                  if (SMAP(Context.snum))
                    SFCLR(Context.snum, SHIP_F_MAP);
                  else
                    SFSET(Context.snum, SHIP_F_MAP);

                  break;
		case 'm':
		  cucSendMsg( MSG_GOD, TRUE, FALSE );
		  break;
		case 'r':  /* just for fun - dwp */
		  oprobot();
		  break;
		case 'L':
		  mcuReviewMsgs( MSG_GOD, ConqInfo->glastmsg );
		  break;
		case 0x0c:
		  operStopTimer();
		  cdredo();
		  Context.redraw = TRUE;
		  operSetTimer();
		  break;
		case 'q':
		case 'Q':
		  operStopTimer();
		  return;
		  break;
		case 'w': /* look at any ship (live or not) if specifically asked for */
		  tmp_snum = snum;
		  if (prompt_ship(buf, &snum, &normal)) 
		    {
		      if (tmp_snum != snum) 
			{
			  old_snum = tmp_snum;
			  tmp_snum = snum;
			  Context.redraw = TRUE;
			}
		      Context.snum = snum;
		      if (normal)
			{
			  operStopTimer();
			  display( Context.snum );
			  operSetTimer();
			}
		    }
		  break;
		case 'W': /* toggle live_ships flag */
		  if (live_ships)
		    live_ships = FALSE;
		  else
		    live_ships = TRUE;
		  break;
		case '`':                 /* toggle between two ships */
		  if (normal || (!normal && old_snum > 0))
		    {
		      if (old_snum != snum) 
			{
			  tmp_snum = snum;
			  snum = old_snum;
			  old_snum = tmp_snum;
			  
			  Context.snum = snum;
			  Context.redraw = TRUE;
			  if (normal)
			    {
			      operStopTimer();
			      display( Context.snum );
			      operSetTimer();
			    }
			}
		    }
		  else
		    cdbeep();
		  break;
		case '~':                 /* toggle debug display */
		  if (Context.snum > 0) 
		    {
		      if (normal)
			normal = FALSE;
		      else
			normal = TRUE;
		      Context.redraw = TRUE;
		      cdclear();
		    }
		  else
		    cdbeep();
		  break;
		case '/':                /* ship list - dwp */
		  operStopTimer();
		  mcuPlayList( TRUE, FALSE, 0 );
		  Context.redraw = TRUE;
		  operSetTimer();
		  break;
		case '\\':               /* big ship list - dwp */
		  operStopTimer();
		  mcuPlayList( TRUE, TRUE, 0 );
		  Context.redraw = TRUE;
		  operSetTimer();
		  break;
		case '!':
		  if (toggle_flg)
			toggle_flg = FALSE;
		  else
			toggle_flg = TRUE;
		  break;
		case '>':  /* forward rotate ship numbers (including doomsday) - dwp */
		case KEY_RIGHT:
		case KEY_UP:
		  while (TRUE)
		    {
		      int i;

		      if (live_ships)
			{	/* we need to make sure that there is
				   actually something alive or an
				   infinite loop will result... */
			  int foundone = FALSE;

			  for (i=1; i <= MAXSHIPS; i++)
			    {
			      if (clbStillAlive(i))
				{
				  foundone = TRUE;
				}
			    }
			  if (foundone == FALSE)
			    {	/* check the doomsday machine */
			      if (Doomsday->status == DS_LIVE)
				foundone = TRUE;
			    }

			  if (foundone == FALSE)
			    {
			      cdbeep();
			      break; /* didn't find one, beep, leave everything
				      alone*/
			    }
			}

		      if (snum == DISPLAY_DOOMSDAY)
			{	  /* doomsday - wrap around to first ship */
			  i = 1;
			}
		      else	
			i = snum + 1;

		      if (i > MAXSHIPS)
			{	/* if we're going past
				   now loop thu specials (only doomsday for
				   now... ) */
			  if (normal)
			    i = DISPLAY_DOOMSDAY;
			  else
			    i = 1;
			}
		      
		      snum = i;
			
		      Context.redraw = TRUE;
		      
		      if (live_ships)
			if ((snum > 0 && clbStillAlive(snum)) || 
			    (snum == DISPLAY_DOOMSDAY && Doomsday->status == DS_LIVE))
			  {
			    Context.snum = snum;
			    break;
			  }
			else
			  continue;
		      else
			{
			  Context.snum = snum;
			  break;
			}
		    }
		  if (normal)
		    {
		      operStopTimer();
		      display( Context.snum );
		      operSetTimer();
		    }
		  break;
		case '<':  /* reverse rotate ship numbers (including doomsday)  - dwp */
		case KEY_LEFT:
		case KEY_DOWN:
		  while (TRUE)
		    {
		      int i;

		      if (live_ships)
			{	/* we need to make sure that there is
				   actually something alive or an
				   infinite loop will result... */
			  int foundone = FALSE;

			  for (i=1; i <= MAXSHIPS; i++)
			    {
			      if (clbStillAlive(i))
				{
				  foundone = TRUE;
				}
			    }
			  if (foundone == FALSE)
			    {	/* check the doomsday machine */
			      if (Doomsday->status == DS_LIVE)
				foundone = TRUE;
			    }

			  if (foundone == FALSE)
			    {
			      cdbeep();
			      break; /* didn't find one, beep, leave everything
				      alone*/
			    }
			}


		      if (snum == DISPLAY_DOOMSDAY)
			{	  /* doomsday - wrap around to last ship */
			  i = MAXSHIPS;
			}
		      else	
			i = snum - 1;

		      if (i <= 0)
			{	/* if we're going past
				   now loop thu specials (only doomsday for
				   now... )*/
			  if (normal)
			    i = DISPLAY_DOOMSDAY;
			  else
			    i = MAXSHIPS;
			}
		      
		      snum = i;
			
		      Context.redraw = TRUE;
		      
		      if (live_ships)
			if ((snum > 0 && clbStillAlive(snum)) || 
			    (snum == DISPLAY_DOOMSDAY && Doomsday->status == DS_LIVE))
			  {
			    Context.snum = snum;
			    break;
			  }
			else
			  continue;
		      else
			{
			  Context.snum = snum;
			  break;
			}
		    }
		  if (normal)
		    {
		      operStopTimer();
		      display( Context.snum );
		      operSetTimer();
		    }

		  break;
		case TERM_ABORT:
		  return;
		  break;
		default:
		  cdbeep();
		  mcuPutMsg( "Type h for help.", MSG_LIN2 );
		  break;
		}
	      /* Disable messages for awhile. */
	      utGrand( &msgrand );
	    }
	} /* end else */

  /* NOTREACHED */
  
    }

int prompt_ship(char buf[], int *snum, int *normal)
{
  int tch;
  int tmpsnum = 0;
  string pmt="Watch which ship (<cr> for doomsday)? ";
  string nss="No such ship.";

  tmpsnum = *snum;

  cdclrl( MSG_LIN1, 2 );
  buf[0] = EOS;
  tch = cdgetx( pmt, MSG_LIN1, 1, TERMS, buf, MSGMAXLINE, TRUE );
  cdclrl( MSG_LIN1, 1 );

  if ( tch == TERM_ABORT )
    {
      return(FALSE); /* dwp */
    }
  
  /* 
   * DWP - Removed old code to watch doomsday machine.
   * Watch it with conqlb.c display() now.
   */
  
  *normal = ( tch != TERM_EXTRA );		/* line feed means debugging */

  utDeleteBlanks( buf );

  if ( strlen( buf ) == 0 ) 
    {              /* watch doomsday machine */
      tmpsnum = DISPLAY_DOOMSDAY;
      *normal = TRUE;		/* doomsday doesn't have a debugging view */
    }
  else
    {
      if ( alldig( buf ) != TRUE )
	{
	  cdputs( nss, MSG_LIN2, 1 );
	  cdmove( 1, 1 );
	  cdrefresh();
	  c_sleep( 1.0 );
	  return(FALSE); /* dwp */
	}
      utSafeCToI( &tmpsnum, buf, 0 );	/* ignore return status */
    }

  if ( (tmpsnum < 1 || tmpsnum > MAXSHIPS) && tmpsnum != DISPLAY_DOOMSDAY )
    {
      cdputs( nss, MSG_LIN2, 1 );
      cdmove( 1, 1 );
      cdrefresh();
      c_sleep( 1.0 );
      return(FALSE); /* dwp */
    }

  *snum = tmpsnum;
  return(TRUE);

} /* end prompt_ship() */


/*  dowatchhelp - display a list of commands while watching a ship */
/*  SYNOPSIS */
/*    dowatchhelp( void ) */
void dowatchhelp(void)
{
  int lin, col, tlin;
  int ch;
  int FirstTime = TRUE;
  static char sfmt[MSGMAXLINE * 2];

  if (FirstTime == TRUE)
    {
      FirstTime = FALSE;
      sprintf(sfmt,
	      "#%d#%%-9s#%d#%%s",
	      InfoColor,
	      LabelColor);
	}

  cdclear();
  cprintf(1,0,ALIGN_CENTER,"#%d#%s", LabelColor, "WATCH WINDOW COMMANDS");
  
  lin = 4;
  
  /* Display the left side. */
  tlin = lin;
  col = 4;
  tlin++;
  cprintf(tlin,col,ALIGN_NONE,sfmt, 
	"d", "flip the doomsday machine - doomsday window only");
  tlin++;
  cprintf(tlin,col,ALIGN_NONE,sfmt, "m", "message from GOD");
  tlin++;
  cprintf(tlin,col,ALIGN_NONE,sfmt, "L", "review messages");
  tlin++;
  cprintf(tlin,col,ALIGN_NONE,sfmt, "k", "kill a ship");
  tlin++;
  cprintf(tlin,col,ALIGN_NONE,sfmt, "h", "this message");
  tlin++;
  cprintf(tlin,col,ALIGN_NONE,sfmt, "w", "watch a ship");
  tlin++;
  cprintf(tlin,col,ALIGN_NONE,sfmt, 
  	"W", "toggle between (live status) and (any status) ships");
  tlin++;
  cprintf(tlin,col,ALIGN_NONE,sfmt, 
  	"<>", "decrement/increment ship number\n");
  tlin++;
  cprintf(tlin,col,ALIGN_NONE,sfmt, "`", "toggle between two ships");
  tlin++;
  cprintf(tlin,col,ALIGN_NONE,sfmt, 
  	"~", "toggle between window and debug ship screen");
  tlin++;
  cprintf(tlin,col,ALIGN_NONE,sfmt, "!", "display toggle line");
  tlin++;
  cprintf(tlin,col,ALIGN_NONE,sfmt, "/", "player list");

  mcuPutPrompt( MTXT_DONE, MSG_LIN2 );
  cdrefresh();
  while ( ! iogtimed( &ch, 1.0 ) )
    ;
  cdclrl( MSG_LIN2, 1 );
  
  return;
  
}


void toggle_line(int snum, int old_snum)
{

  char *frmt_str = "(') = Toggle %s:%s";
  char snum_str[MSGMAXLINE];
  char old_snum_str[MSGMAXLINE];
  char buf[MSGMAXLINE];
  
  build_toggle_str(snum_str,snum);
  build_toggle_str(old_snum_str,old_snum);
  
  sprintf(buf,frmt_str,snum_str, old_snum_str);
  cdputs( buf, MSG_LIN1, (Context.maxcol-(strlen(buf))));  /* at end of line */
  
  return;

}

char *build_toggle_str(char *snum_str, int snum)
{
  
  char buf[MSGMAXLINE];
  static char *doomsday_str = "DM";
  static char *deathstar_str = "DS";
  static char *unknown_str = "n/a";
  
  buf[0] = EOS;
  if (snum > 0 && snum <= MAXSHIPS)
    {          /* ship */
      sprintf(snum_str,"%c%d", Teams[Ships[snum].team].teamchar, snum);
    }
  else if (snum < 0 && -snum <= NUMPLANETS) 
    {  /* planet */

      sprintf(snum_str, "%c%c%c", 
	      Planets[-snum].name[0], 
	      Planets[-snum].name[1], 
	      Planets[-snum].name[2]);
    }
  else if (snum == DISPLAY_DOOMSDAY)          /* specials */
    strcpy(snum_str,doomsday_str);
  else if (snum == DISPLAY_DEATHSTAR)
    strcpy(snum_str,deathstar_str);
  else                                        /* should not get here */
    strcpy(snum_str,unknown_str);
  
  return(snum_str);

}

/* DoInit(InitChar, cmdline) - Based on InitChar, init something (like in 
 *   the (I)nitialize screen).  if cmdline is TRUE, output status on stdout.
 */

int DoInit(char InitChar, int cmdline)
{

  if (cmdline == TRUE)
    {
      fprintf(stdout, "Initialized ");
      fflush(stdout);
    }

				/*  perform an init on something */
  switch(InitChar)
    {
    case 'e': 
      clbInitEverything();
      *CBlockRevision = COMMONSTAMP;

      if (cmdline == TRUE)
	{
	  fprintf(stdout, "everything.\n");
	  fflush(stdout);
	}

      break;

    case 'z': 
      clbZeroEverything();

      if (cmdline == TRUE)
	{
	  fprintf(stdout, "common block (zeroed).\n");
	  fflush(stdout);
	}

      break;

    case 'u': 
      clbInitUniverse();
      *CBlockRevision = COMMONSTAMP;

      if (cmdline == TRUE)
	{
	  fprintf(stdout, "universe.\n");
	  fflush(stdout);
	}

      break;

    case 'g': 
      clbInitGame();
      *CBlockRevision = COMMONSTAMP;

      if (cmdline == TRUE)
	{
	  fprintf(stdout, "game.\n");
	  fflush(stdout);
	}

      break;

    case 'p': 
      cqiInitPlanets();
      *CBlockRevision = COMMONSTAMP;

      if (cmdline == TRUE)
	{
	  fprintf(stdout, "planets.\n");
	  fflush(stdout);
	}

      break;

    case 's': 
      clbClearShips();
      *CBlockRevision = COMMONSTAMP;

      if (cmdline == TRUE)
	{
	  fprintf(stdout, "ships.\n");
	  fflush(stdout);
	}

      break;

    case 'm': 
      clbInitMsgs();
      *CBlockRevision = COMMONSTAMP;

      if (cmdline == TRUE)
	{
	  fprintf(stdout, "messages.\n");
	  fflush(stdout);
	}

      break;

    case 'l': 
      PVUNLOCK(&ConqInfo->lockword);
      PVUNLOCK(&ConqInfo->lockmesg);
      *CBlockRevision = COMMONSTAMP;

      if (cmdline == TRUE)
	{
	  fprintf(stdout, "lockwords.\n");
	  fflush(stdout);
	}

      break;

    case 'r': 
      clbInitRobots();
      *CBlockRevision = COMMONSTAMP;

      if (cmdline == TRUE)
	{
	  fprintf(stdout, "robots.\n");
	  fflush(stdout);
	}

      break;

    default:
      if (cmdline == TRUE)
	{
	  fprintf(stdout, "nothing. '%c' unrecognized.\n", InitChar);
	  fflush(stdout);
	}
      break;
    }
      
  utLog("OPER: %s initialized '%c'",
       operName, InitChar);

  return TRUE;
}

void EnableConqoperSignalHandler(void)
{
#ifdef DEBUG_SIG
  utLog("EnableConquestSignalHandler() ENABLED");
#endif
  
  signal(SIGHUP, (void (*)(int))DoConqoperSig);
  signal(SIGTSTP, SIG_IGN);
  signal(SIGTERM, (void (*)(int))DoConqoperSig);  
  signal(SIGINT, (void (*)(int))DoConqoperSig);
  signal(SIGQUIT, (void (*)(int))DoConqoperSig);

  return;
}

void DoConqoperSig(int sig)
{
  
#ifdef DEBUG_SIG
  utLog("DoSig() got SIG %d", sig);
#endif
  
  switch(sig)
    {
    case SIGTERM:
    case SIGINT:
    case SIGHUP:
    case SIGQUIT:
      operStopTimer();
      cdrefresh();
      cdend();
      exit(0);			/* WE EXIT HERE */
      break;
    default:
      break;
    }

  EnableConqoperSignalHandler();	/* reset */
  return;
}


/*  astoperservice - ast service routine for conqoper */
/*  SYNOPSIS */
/*    astservice */
/* This routine gets called from a sys$setimr ast. Normally, it outputs */
/* one screen update and then sets up another timer request. */
void astoperservice(int sig)
{
  /* Don't do anything if we're not supposed to. */
  if ( ! Context.display )
    return;
  
  operStopTimer();
  
  /* Perform one ship display update. */
  display( Context.snum );
  
  /* Schedule for next time. */
  operSetTimer();
  
  return;
  
}

/*  operSetTimer - set timer to display() for conqoper...*/
/*  SYNOPSIS */
void operSetTimer(void)
{
  static struct sigaction Sig;
  
#ifdef HAVE_SETITIMER
  struct itimerval itimer;
#endif
  
  Sig.sa_handler = (void (*)(int))astoperservice;
  
  Sig.sa_flags = 0;

  if (sigaction(SIGALRM, &Sig, NULL) == -1)
    {
      utLog("clntSetTimer():sigaction(): %s\n", strerror(errno));
      exit(errno);
    }
  
#ifdef HAVE_SETITIMER

  if (Context.updsec >= 1 && Context.updsec <= 10)
    {
      if (Context.updsec == 1)
	{
	  itimer.it_value.tv_sec = 1;
	  itimer.it_value.tv_usec = 0;
	}
      else
	{
	  itimer.it_value.tv_sec = 0;
	  itimer.it_value.tv_usec = (1000000 / Context.updsec);
	}
    }
  else
    {
      itimer.it_value.tv_sec = 0;
      itimer.it_value.tv_usec = (1000000 / 2); /* 2/sec */
    }

  itimer.it_interval.tv_sec = itimer.it_value.tv_sec;
  itimer.it_interval.tv_usec = itimer.it_value.tv_usec;

  setitimer(ITIMER_REAL, &itimer, NULL);
#else
  alarm(1);			/* set alarm() */
#endif  
  return;
  
}



/*  operStopTimer - cancel timer */
/*  SYNOPSIS */
/*    operStopTimer */
void operStopTimer(void)
{
#ifdef HAVE_SETITIMER
  struct itimerval itimer;
#endif
  
  Context.display = FALSE;
  

  signal(SIGALRM, SIG_IGN);
  
#ifdef HAVE_SETITIMER
  itimer.it_value.tv_sec = itimer.it_interval.tv_sec = 0;
  itimer.it_value.tv_usec = itimer.it_interval.tv_usec = 0;
  
  setitimer(ITIMER_REAL, &itimer, NULL);
#else
  alarm(0);
#endif


  Context.display = TRUE;
  
  return;
  
}

