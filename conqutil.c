#include "c_defs.h"

/************************************************************************
 *
 * $Id$
 *
 * Copyright 1999-2004 Jon Trulson under the ARTISTIC LICENSE. (See LICENSE).
 ***********************************************************************/

/*                               C O N Q U T I L */
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

#include "conqdef.h"
#include "conqcom.h"
#include "global.h"
#include "context.h"
#include "color.h"
#include "conqlb.h"
#include "conqutil.h"

/* if set, utLog uses the system log, else it is created in HOME */
static int systemlog   = TRUE;
static int echo2stderr = FALSE;  /* whether to echo utLog to stderr */
                                 /* this will be ignored if systemlog is
                                    TRUE */

/*  utAccurateDist - figure distance traveled while changing velocities */
/*  SYNOPSIS */
/*    real dis, curvel, newvel, acc */
/*    dis = utAccurateDist( curvel, newvel, acc ) */
/*  DESCRIPTION */
/*    These formulas works for de-acceleration only. */
real utAccurateDist( real curvel, real newvel, real acc )
{
  real t;
  /*    The following is a box approximation that takes into account */
  /*    the way the driver moves ships and so gives the *exact* distance. */
  /*    v = curvel - newvel */
  /*    n = v / ( ITER_SECONDS * acc ) + 1.0 */
  /*    d = ( n * ITER_SECONDS + ( v / 2.0 + newvel ) * MM_PER_SEC_PER_WARP ) */
  /*    A "faster", but less accurate formula (when compared to the */
  /*    way the driver moves ships) is as follows: */
  t = ( curvel - newvel ) / acc;
  return ( ( curvel * t - 0.5 * acc * t * t ) * MM_PER_SEC_PER_WARP );
  
}


/*  angle - compute the angle between two points */
/*  SYNOPSIS */
/*    real ang, angle, fromx, fromy, tox, toy */
/*    ang = utAngle( fromx, fromy, tox, toy ) */
real utAngle( real fromx, real fromy, real tox, real toy )
{
  if ( fromx == tox && fromy == toy )
    return ( 0.0 );
  
  return ( utMod360( rtod( atan2( toy - fromy, tox - fromx ) ) ) );
  
}


/*  utAppendInt - append an int to a string */
/*  SYNOPSIS */
/*    int int */
/*    char str() */
/*    utAppendInt( i, str ) */
void utAppendInt( int i, char *str )
{
  char buf[BUFFER_SIZE];
  
  buf[0] = EOS;
  sprintf(buf, "%d", i);
  appstr( buf, str );
  
  return;
  
}


/*  utAppendNumWord - append a number in English */
/*  SYNOPSIS */
/*    int num */
/*    char buf() */
/*    utAppendNumWord( num, buf ) */
/* Note: This routine only works for the number less than 100. */
void utAppendNumWord( int num, char *buf )
{
  int i, j;
  
  i = num;
  if ( i >= 100 )
    {
      appstr( "big num", buf );
      return;
    }
  if ( i >= 20 )
    {
      j = i/10;
      switch ( j )
	{
	case 2:
	  appstr( "twenty", buf );
	  break;
	case 3:
	  appstr( "thirty", buf );
	  break;
	case 4:
	  appstr( "forty", buf );
	  break;
	case 5:
	  appstr( "fifty", buf );
	  break;
	case 6:
	  appstr( "sixty", buf );
	  break;
	case 7:
	  appstr( "seventy", buf );
	  break;
	case 8:
	  appstr( "eighty", buf );
	  break;
	case 9:
	  appstr( "ninety", buf );
	  break;
	default:
	  appstr( "???", buf );
	  break;
	}
      i = i - j*10;
      if ( i == 0 )
	return;
      appchr( '-', buf );
    }
  
  switch ( i )
    {
    case 0:
      appstr( "zero", buf );
      break;
    case 1:
      appstr( "one", buf );
      break;
    case 2:
      appstr( "two", buf );
      break;
    case 3:
      appstr( "three", buf );
      break;
    case 4:
      appstr( "four", buf );
      break;
    case 5:
      appstr( "five", buf );
      break;
    case 6:
      appstr( "six", buf );
      break;
    case 7:
      appstr( "seven", buf );
      break;
    case 8:
      appstr( "eight", buf );
      break;
    case 9:
      appstr( "nine", buf );
      break;
    case 10:
      appstr( "ten", buf );
      break;
    case 11:
      appstr( "eleven", buf );
      break;
    case 12:
      appstr( "twelve", buf );
      break;
    case 13:
      appstr( "thirteen", buf );
      break;
    case 14:
      appstr( "fourteen", buf );
      break;
    case 15:
      appstr( "fifteen", buf );
      break;
    case 16:
      appstr( "sixteen", buf );
      break;
    case 17:
      appstr( "seventeen", buf );
      break;
    case 18:
      appstr( "eighteen", buf );
      break;
    case 19:
      appstr( "nineteen", buf );
      break;
    }
  
  return;
  
}


/*  utAppendTime - append English formated time and date */
/*  SYNOPSIS */
/*   utAppendTime( now, buf ) */
void utAppendTime( int now[], char *buf )
{
  int hour;
  int am;
  
  am = TRUE;				/* assume morning */
  hour = now[4];
  if ( hour == 0 )
    hour = 12;			/* midnight */
  else if ( hour == 12 )
    am = FALSE;			/* afternoon */
  else if ( hour > 12 )
    {
      hour = hour - 12;
      am = FALSE;			/* afternoon */
    }
  switch ( wkday() )
    {
    case 1:
      appstr( "Sunday", buf );
      break;
    case 2:
      appstr( "Monday", buf );
      break;
    case 3:
      appstr( "Tuesday", buf );
      break;
    case 4:
      appstr( "Wednesday", buf );
      break;
    case 5:
      appstr( "Thursday", buf );
      break;
    case 6:
      appstr( "Friday", buf );
      break;
    case 7:
      appstr( "Saturday", buf );
      break;
    default:
      appstr( "???", buf );
      break;
    }
  appstr( ", ", buf );
  switch ( now[2] )
    {
    case 1:
      appstr( "January", buf );
      break;
    case 2:
      appstr( "February", buf );
      break;
    case 3:
      appstr( "March", buf );
      break;
    case 4:
      appstr( "April", buf );
      break;
    case 5:
      appstr( "May", buf );
      break;
    case 6:
      appstr( "June", buf );
      break;
    case 7:
      appstr( "July", buf );
      break;
    case 8:
      appstr( "August", buf );
      break;
    case 9:
      appstr( "September", buf );
      break;
    case 10:
      appstr( "October", buf );
      break;
    case 11:
      appstr( "November", buf );
      break;
    case 12:
      appstr( "December", buf );
      break;
    default:
      appstr( "???", buf );
      break;
    }
  appchr( ' ', buf );
  utAppendInt( now[3], buf );		/* day of month */
  appstr( ", at ", buf );
  utAppendNumWord( hour, buf );		/* hour */
  appchr( ' ', buf );
  if ( now[5] == 0 )			/* minute */
    appstr( "o'clock", buf );
  else
    {
      if ( now[5] < 10 )
	appstr( "o ", buf );
      utAppendNumWord( now[5], buf );
    }
  appchr( ' ', buf );
  if ( am )
    appstr( "ante", buf );
  else
    appstr( "post", buf );
  appstr( " meridiem", buf );
  
  return;
  
}

/*  utAppendKilledBy - append killed by string */
/*  SYNOPSIS */
/*    int kb */
/*    char buf() */
/*    utAppendKilledBy( kb, buf ) */
void utAppendKilledBy( int kb, char *buf )
{
  
  switch ( kb )
    {
    case KB_SELF:
      appstr( "self", buf );
      break;
    case KB_NEGENB:
      appstr( "negenb", buf );
      break;
    case KB_CONQUER:
      appstr( "conquer", buf );
      break;
    case KB_NEWGAME:
      appstr( "newgame", buf );
      break;
    case KB_EVICT:
      appstr( "evict", buf );
      break;
    case KB_SHIT:
      appstr( "shit", buf );
      break;
    case KB_DOOMSDAY:
      appstr( "doomsday", buf );
      break;
    case KB_GOTDOOMSDAY:
      appstr( "gotdoomsday", buf );
      break;
    case KB_GOD:
      appstr( "GOD", buf );
      break;
    default:
      if ( kb > 0 && kb <= MAXSHIPS )
	utAppendShip( kb, buf );
      else if ( -kb > 0 && -kb <= NUMPLANETS )
	appstr( Planets[-kb].name, buf );
      else
	utAppendInt( kb, buf );
      break;
    }
  
  return;
  
}

/*  utAppendShip - append a ship number to a string */
/*  SYNOPSIS */
/*    int snum */
/*    char str() */
/*    utAppendShip( snum, str ) */
void utAppendShip( int snum, char *str )
{
  int i;
  char ch;
  
  ch = 'S';
  if ( snum > 0 && snum <= MAXSHIPS )
    {
      i = Ships[snum].team;
      if ( i >= 0 && i < NUMPLAYERTEAMS )
	ch = Teams[i].teamchar;
    }
  
  appchr( ch, str );
  utAppendInt( snum, str );
  
  return;
}


/*  utAppendShipStatus - append ship status string */
/*  SYNOPSIS */
/*    int status */
/*    char buf() */
/*    utAppendShipStatus( status, buf ) */
void utAppendShipStatus( int status, char *buf )
{
  switch ( status )
    {
    case SS_OFF:
      appstr( "off", buf );
      break;
    case SS_ENTERING:
      appstr( "entering", buf );
      break;
    case SS_LIVE:
      appstr( "live", buf );
      break;
    case SS_DYING:
      appstr( "dying", buf );
      break;
    case SS_DEAD:
      appstr( "dead", buf );
      break;
    case SS_RESERVED:
      appstr( "reserved", buf );
      break;
    default:
      utAppendInt( status, buf );
      break;
    }
  return;
  
}


/*  utAppendTitle - append a team oriented title */
/*  SYNOPSIS */
/*    int team */
/*    char buf() */
/*    utAppendTitle( team, buf ) */
void utAppendTitle( int team, char *buf )
{
  switch ( team )
    {
    case TEAM_FEDERATION:
      appstr( "Captain", buf );
      break;
    case TEAM_ROMULAN:
      appstr( "Centurion", buf );
      break;
    case TEAM_ORION:
      appstr( "Commander", buf );
      break;
    case TEAM_KLINGON:
      appstr( "Kommander", buf );
      break;
    }
  
  return;
  
}


/*  utArrowsToDir - interpret arrow keys */
int utArrowsToDir( char *str, real *dir )
{
  int i, n, idx; 
  real thedir, ndir, ndir1, ndir2;
  string arrs="*dewqazxc";	/* the '*' is to fill arrs[0] - JET */
  
  /* Special hack preventing "ea" and "da" from being recognized as arrows. */
  /* "ea" is reserved for Earth and "da" for Dakel. */
  if ( (char)tolower(str[0]) == 'e' && (char)tolower(str[1]) == 'a' )
    return ( FALSE );
  if ( (char)tolower(str[0]) == 'd' && (char)tolower(str[1]) == 'a' )
    return ( FALSE );
  
  thedir = 0.0;
  
  for ( i = 0; str[i] != EOS; i = i + 1 )
    {
      n = i + 1;
      idx = c_index( arrs, (char)tolower(str[i]) );
      if ( idx == ERR || idx == 0)
	return ( FALSE );
      
      ndir1 = ((real)idx - 1.0) * 45.0;
      ndir2 = (real)ndir1 - 360.0;
      
      if ( (real)fabs( thedir - ndir1 ) < (real)fabs( thedir - ndir2 ) )
	ndir = ndir1;
      else
	ndir = ndir2;
      
      thedir = (((thedir*((real)n - 1)) + ndir ) / (real)n);
      
    }
  
  
  *dir = utMod360( thedir );
  
  return ( TRUE );
  
}

void utSetLogConfig(int usesys, int echostderr)
{
  if (usesys)
    {
      systemlog = TRUE;
      echo2stderr = FALSE;
    }
  else
    {
      systemlog = FALSE;
      echo2stderr = echostderr;
    }
 
  return;
}


/*  utError - conquest error message to god */
void utError(char *fmt, ...)
{
  va_list ap;
  char buf[BIG_BUFFER_SIZE];
  
  va_start(ap, fmt);
  (void)vsnprintf(buf, sizeof(buf) - 1, fmt, ap);
  
  va_end(ap);
  
  clbStoreMsg( MSG_OUTSIDE, MSG_GOD, buf );
  
  return;
  
}

void utLog(char *fmt, ...)
{
  va_list ap;
  static int nowarn = FALSE;     /* if set, ignore logging */
  static char buf[BIG_BUFFER_SIZE];
  static char errfile[MID_BUFFER_SIZE];
  static FILE *errfd = NULL;
  char *homevar;
  int tmp;

  va_start(ap, fmt);
  (void)vsnprintf(buf, sizeof(buf) - 1, fmt, ap);
  
  va_end(ap);

  if (errfd == NULL)
    {
      
      if (systemlog)
	{
	  umask(007);
	  sprintf(errfile, "%s/%s", CONQSTATE, C_CONQ_ERRLOG);
	  if (ConquestGID == ERR)
	    {
	      fprintf(stderr, "conqutil: utLog():  ConquestGID == ERR!\n");
	      exit(1);
	    }
	}
      else
	{			/* local logfile */
	  if ((homevar = getenv(CQ_USERHOMEDIR)) != NULL)
            {
              snprintf(errfile, sizeof(errfile) - 1, "%s/%s/%s", 
                       homevar, CQ_USERCONFDIR, C_CONQ_ERRLOG);
            }
	  else
	    snprintf(errfile, sizeof(errfile) - 1, "%s", C_CONQ_ERRLOG);
	}

      if ((errfd = fopen(errfile, "a+")) == NULL)
	{
	  if ((tmp = creat(errfile, 0660)) == -1)
	    {

              if (!nowarn)
                {
                  fprintf(stderr, "utLog(): creat(%s): %s\n",
                          errfile,
                          strerror(errno));
                  nowarn = TRUE;
                }
	      
              if (!systemlog)
                {
                  /* if the logfile could not be created for a user,
                     keep trying (the .conquest/ dir may not exist
                     yet), but only log an error once. */
                  nowarn = TRUE;
                  return;
                }
              else
                exit(1);
	    }
	  else
	    {
	      close(tmp);

#if !defined(MINGW)
	      if (systemlog)
		if (chmod(errfile, 
			  (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP)) == -1)
		  {
		    perror("utLog():chmod()");
		    exit(1);
		  }
#endif
	    }
	}
      else
	{
	  fclose(errfd);
	}
      
#if !defined(MINGW)
      if (systemlog)
	chown(errfile, 0, ConquestGID);
#endif

      if ((errfd = fopen(errfile, "a+")) == NULL)
	{
	  perror("utLog(): can't open logfile");
	}
    }
  
  if (errfd != NULL)
    {
      fprintf(errfd, "%ld:%d:%s\n", time(0), (int)getpid(), buf);
      fflush(errfd);
    }

  if (echo2stderr)
    {
      fprintf(stderr, "%s\n", buf);
      fflush(stderr);
    }

  
  return;
  
}





/*  utDeleteBlanks - remove all blanks from a string */
/*  SYNOPSIS */
/*    char str() */
/*    utDeleteBlanks( str ) */
void utDeleteBlanks( char *str )
{
  int i, j;
  
  for ( i = 0; str[i] != EOS; )
    if ( str[i] == ' ' )
      for ( j = i; str[j] != EOS; j = j + 1 )
	str[j] = str[j+1];
    else
      i = i + 1;
  
  return;
  
}


/*  utDeltaGrand - delta time for thousands */
/*  SYNOPSIS */
/*    int i, utDeltaGrand, s, n */
/*    i = utDeltaGrand( s, n ) */
int utDeltaGrand( int s, int *n )
{
  int tn, ts;
  
  /* Save s in case it and n are the same variable. */
  ts = s;
  
  /* Get thousands since midnight. */
  utGrand( &tn );
  *n = tn;
  
  /* Calculate the difference. */
  if ( tn < ts )
    tn = tn + 24 * 60 * 60 * 1000;		/* crossed midnight */
  
  return ( tn - ts );
  
}


/*  utDeltaSecs - delta time for seconds */
/*  SYNOPSIS */
/*    int i, utDeltaSecs, s, n */
/*    i = utDeltaSecs( s, n ) */

int utDeltaSecs( int s, int *n )
{
  int tn, ts;
  
  /* Save s in case it and n are the same variable. */
  ts = s;
  
  /* Get seconds since midnight. */
  utGetSecs( &tn );
  *n = tn;
  
  /* Calculate the difference. */
  if ( tn < ts )
    tn = tn + ((24 * 60) * 60);		/* crossed midnight */
  
  return ( tn - ts );
  
}


/*  explosion - hits based on distance */
/*  SYNOPSIS */
/*    real newhits, utExplosionHits, basehits, dis */
/*    newhits = utExplosionHits( basehits, dis ) */
real utExplosionHits( real basehits, real dis )
{
  if ( dis > PHASER_DIST )
    return ( 0.0 );
  return ( basehits / ( ( EXPLOSION_FALLOFF - 1.0 ) *
			max( dis - EXPLOSION_RADIUS, 
			     0.0 ) / PHASER_DIST + 1.0 ) -
	   basehits / EXPLOSION_FALLOFF * dis / PHASER_DIST );
  
}


/*  utFormatMinutes - format a minutes string */
/*  SYNOPSIS */
/*   utFormatMinutes( itime, buf ) */
void utFormatMinutes( int itime, char *buf )
{
  int i, days, hours, minutes;
  char junk[32];
  int minus;
  
  if ( itime < 0 )
    {
      minus = TRUE;
      i = -itime;
    }
  else
    {
      minus = FALSE;
      i = itime;
    }
  
  minutes = mod( i, 60 );		/* minutes */
  i = i / 60;
  hours = mod( i, 24 );		/* hours */
  days = i / 24;			/* days */
  
  if ( minus )
    {
      if ( days > 0 )
	days = -days;
      else if ( hours > 0 )
	hours = -hours;
      else
	minutes = -minutes;
    }
  
  /* Format time. */
  sprintf( junk, "%d %2d:%02d", days, hours, minutes );
  
  /* Skip the junk and find the beginning. */
  for ( i = 0; junk[i] == ' ' || junk[i] == ':' || junk[i] == '0'; i = i + 1 )
    ;
  
  /* Store in return buffer. */
  /*    scopy( junk, i, buf, 1 );*/
  strcpy(buf, &junk[i]);
  
  return;
  
}


/*  utFormatSeconds - format a seconds string */
/*  SYNOPSIS */
/*   utFormatSeconds( itime, buf ) */
void utFormatSeconds( int itime, char *buf )
{
  int i, days, hours, minutes, seconds;
  char junk[BUFFER_SIZE];
  int minus;
  
  if ( itime < 0 )
    {
      minus = TRUE;
      i = -itime;
    }
  else
    {
      minus = FALSE;
      i = itime;
    }
  
  seconds = mod( i, 60 );		/* seconds */
  i = i / 60;
  minutes = mod( i, 60 );		/* minutes */
  i = i / 60;
  hours = mod( i, 24 );		/* hours */
  days = i / 24;			/* days */
  
  if ( minus )
    {
      if ( days > 0 )
	days = -days;
      else if ( hours > 0 )
	hours = -hours;
      else if ( minutes > 0 )
	minutes = -minutes;
      else
	seconds = -seconds;
    }
  
  /* Format time. */
  sprintf( junk, "%d %2d:%02d:%02d", days, hours, minutes, seconds );
  
  strcpy(buf, junk);
  
  return;
  
}


/*  utGetMsg - find the next readable message */
/*  SYNOPSIS */
/*    int gotone, utGetMsg */
/*    int snum, msg */
/*    gotone = utGetMsg( snum, msg ) */
int utGetMsg( int snum, int *msg )
{
  while ( *msg != ConqInfo->lastmsg )
    {
      *msg = utModPlusOne( *msg + 1, MAXMESSAGES );
      if ( clbCanRead( snum, *msg ) )
        return(TRUE);

    }
  return ( FALSE );
  
}


/*  utFormatTime - get the date and time into a string */
/*  SYNOPSIS */
/*    char buf() */
/*    utFormatTime( buf ) */
void utFormatTime( char *buf, time_t thetime )
{
  int now[NOWSIZE];
  char junk[5];
  
  getnow( now, thetime );
  switch ( now[2] )
    {
    case 1:
      c_strcpy( "Jan", junk );
      break;
    case 2:
      c_strcpy( "Feb", junk );
      break;
    case 3:
      c_strcpy( "Mar", junk );
      break;
    case 4:
      c_strcpy( "Apr", junk );
      break;
    case 5:
      c_strcpy( "May", junk );
      break;
    case 6:
      c_strcpy( "Jun", junk );
      break;
    case 7:
      c_strcpy( "Jul", junk );
      break;
    case 8:
      c_strcpy( "Aug", junk );
      break;
    case 9:
      c_strcpy( "Sep", junk );
      break;
    case 10:
      c_strcpy( "Oct", junk );
      break;
    case 11:
      c_strcpy( "Nov", junk );
      break;
    case 12:
      c_strcpy( "Dec", junk );
      break;
    default:
      c_strcpy( "???", junk );
      break;
    }
  sprintf( buf, "%2d:%02d:%02d %02d%s%02d",
	 now[4], now[5], now[6], now[3], junk, mod( now[1], 100 ) );
  
  return;
  
}


/*  grand - thousands since midnight */
/*  SYNOPSIS */
/*    int h */
/*    utGrand( h ) */
void utGrand( int *h )
{
  int now[NOWSIZE];
  
  getnow( now, 0 );
  *h = ( ( ( now[4] * 60 ) + now[5] ) * 60 + now[6] ) * 1000 + now[7];
  
  return;
  
}


/*  utGetSecs - seconds since midnight */
/*  SYNOPSIS */
/*    int s */
/*    utGetSecs( s ) */
void utGetSecs( int *s )
{
  int now[NOWSIZE];
  
  getnow( now, 0 );
  *s = ( ( now[4] * 60 ) + now[5] ) * 60 + now[6];
  
  return;
  
}


/*  utMod360 - modularize a real number to 0.0 <= r < 360.0 */
/*  SYNOPSIS */
/*    real mr, utMod360, r */
/*    mr = utMod360( r ) */
real utMod360( real r )
{
  real mr;
  
  mr = r;
  
  while ( mr < 0.0 )
    mr += 360.0;
  
  return((real) fmod(mr, 360.0));
  
}


/*  utModPlusOne - modulus plus one */
/*  SYNOPSIS */
/*    int mi, utModPlusOne, i, modulus */
/*    mi = utModPlusOne( i, modulus ) */
int utModPlusOne( int i, int modulus )
{
  int m, n;
  
  m = i;
  
  while ( m < 0 )
    m += modulus;
  
  n = mod(--m, modulus) + 1;
  return((n >= modulus) ? 0 : n);
  
  /*    return((n == 0) ? 1 : n);*/
  
  /*    while ( m < 1 )
	m = m + modulus;
	
	return ( mod( m-1, modulus ) + 1 );
	*/
}


/*  utSafeCToI - char to int conversion with overflow protection */
/*  SYNOPSIS */
/*    int flag, utSafeCToI */
/*    int num, ptr */
/*    char buf() */
/*    flag = utSafeCToI( num, buf ptr ) */
int utSafeCToI( int *num, char *buf, int offset )
{
  int retval;

  retval = FALSE;
  if (buf[offset] == EOS)
    {		
      *num = 0;
      retval = FALSE;
    }

  *num = atoi( &buf[offset]);
  retval = TRUE;

  /* If the number is the same size as the biggest integer, */
  /*  assume that it is too big. */
  
  if ( *num >= INT_MAX )
    {
      *num = INT_MAX;
      retval = FALSE;
    }
  
  return ( retval );
  
}


/*  special - check if a string is a valid "special" specifier */
/*  SYNOPSIS */
/*    char str() */
/*    int what, token, count */
/*    int flag, special */
/*    flag = utIsSpecial( str, what, token, count ) */
int utIsSpecial( char *str, int *what, int *token, int *count )
{
  int i; 
  char buf[20];
  
  *what = NEAR_ERROR;
  *token = SPECIAL_NOTSPECIAL;
  *count = 0;
  
  /* Reject obvious losers. */
  if ( str[0] != 'n' && str[0] != 'w' && str[0] != 'h' )
    return ( FALSE );
  
  utStcpn( str, buf, 20 );			/* need a private copy */
  
  /* Find threshold count; cleverly, the default will be zero when using ctoi. */
  for ( i = 0; buf[i] != EOS && c_type( buf[i] ) != DIGIT; i = i + 1 )
    ;
  buf[i] = EOS;				/* ditch numeric part */
  utSafeCToI( count, str, i );		/* ignore status */
  
  if ( utStringMatch( buf, "nes", FALSE ) )	/* this one must be first */
    {
      *what = NEAR_SHIP;
      *token = SPECIAL_ENEMYSHIP;
    }
  else if ( utStringMatch( buf, "nfp", FALSE ) )
    {
      *what = NEAR_PLANET;
      *token = SPECIAL_FUELPLANET;
    }
  else if ( utStringMatch( buf, "nep", FALSE ) )
    {
      *what = NEAR_PLANET;
      *token = SPECIAL_ENEMYPLANET;
    }
  else if ( utStringMatch( buf, "ns", FALSE ) )
    {
      *what = NEAR_SHIP;
      *token = SPECIAL_SHIP;
    }
  else if ( utStringMatch( buf, "np", FALSE ) )
    {
      *what = NEAR_PLANET;
      *token = SPECIAL_PLANET;
    }
  else if ( utStringMatch( buf, "nts", FALSE ) )
    {
      *what = NEAR_SHIP;
      *token = SPECIAL_TEAMSHIP;
    }
  else if ( utStringMatch( buf, "nap", FALSE ) )
    {
      *what = NEAR_PLANET;
      *token = SPECIAL_ARMYPLANET;
      if ( *count <= 0 )
	*count = 1;
    }
  else if ( utStringMatch( buf, "wp", FALSE ) )
    {
      *what = NEAR_PLANET;
      *token = SPECIAL_WEAKPLANET;
    }
  else if ( utStringMatch( buf, "ntp", FALSE ) )
    {
      *what = NEAR_PLANET;
      *token = SPECIAL_TEAMPLANET;
    }
  else if ( utStringMatch( buf, "nrp", FALSE ) )
    {
      *what = NEAR_PLANET;
      *token = SPECIAL_REPAIRPLANET;
    }
  else if ( utStringMatch( buf, "hp", FALSE ) )
    {
      *what = NEAR_PLANET;
      *token = SPECIAL_HOMEPLANET;
    }
  else
    return ( FALSE );		/* string simply isn't special */
  
  return ( TRUE );
  
}


/*  utStcpn - copy a string with a size limit */
/*  SYNOPSIS */
/*    char from(), to() */
/*    int tosize */
/*    utStcpn( from, to, tosize ) */
void utStcpn( char *from, char *to, int tosize )
{
  strncpy(to, from, tosize);
  to[tosize - 1] = '\0';
  
}


/*  utStringMatch - check whether two strings match or not */
/*  SYNOPSIS */
/*    int matched, utStringMatch, casesensitive */
/*    char str1(), str2() */
/*    matched = utStringMatch( str1, str2, casesensitive ) */
int utStringMatch( char *str1, char *str2, int casesensitive )
{
  int i;
  
  if ( casesensitive )
    for ( i = 0; str1[i] == str2[i] && str1[i] != EOS; i = i + 1 )
      ;
  else
    for ( i = 0;
	 (char)tolower(str1[i]) == (char)tolower(str2[i]) && str1[i] != EOS;
	 i = i + 1 )
      ;
  
  if ( i == 0 )
    {
      if ( str1[0] == EOS && str2[0] == EOS )
	return ( TRUE );
      else
	return ( FALSE );
    }
  else if ( str1[i] == EOS || str2[i] == EOS )
    return ( TRUE );
  
  return ( FALSE );
  
}


/*  utSubAngle - find smallest difference between angles. */
/*  SYNOPSIS */
/*    real h, utSubAngle, a1, a2 */
/*    h = utSubAngle( a1, a2 ) */
real utSubAngle( real a1, real a2 )
{
  real x;
  
  x = a1 - a2;
  while ( x > 180.0 )
    x = x - 360.0;
  while ( x < -180.0 )
    x = x + 360.0;
  
  return ( x );
  
}

/* Under windows, we play a few more games to figure out where
 * system-related stuff can be found, like souncd/img/etc... For non
 * windows (!MINGW) systems we simply return the path arg that was
 * passed in.
 * 
 * For windows, we will look for an env var: CONQUEST_ROOT, which if
 * present will be used to locate the other dirs.  If this env var is
 * not set, we will use Windows $COMMONPROGRAMFILES/Conquest/.  If
 * that fails, we will use just '/Conquest'.
 *
 * At present, we only care about CONQETC and CONQSHARE.
 */

char *utGetPath(const char *thepath)
{
#if !defined(MINGW)
  /* the non-windows case just returns thepath. */
  return thepath;
#else

  char *theroot = NULL;
  static char retpath[PATH_MAX];
  char *defaultConq = "";

  if (!(theroot = getenv("CONQUEST_ROOT")))
    {
      /* next check COMMONPROGRAMFILES */
      if (!(theroot = getenv("COMMONPROGRAMFILES")))
        {
          theroot = "/Conquest";
        }
      else
        {                       /* Add /Conquest to COMMONPROGRAMFILES */
          defaultConq = "/Conquest";
        }
    }

  /* now determine the path requested and do our magic. */

  if (!strcmp(thepath, CONQETC))
    {                           /* etc */
      snprintf(retpath, PATH_MAX - 1, "%s%s/etc", theroot, defaultConq);
    }
  else if (!strcmp(thepath, CONQSHARE))
    {                           /* share */
      snprintf(retpath, PATH_MAX - 1, "%s%s", theroot, defaultConq);
    }
  else
    {                           /* default, just return original path */
      snprintf(retpath, PATH_MAX - 1, "%s", thepath);
    }

  return retpath;

#endif  /* MINGW */
}
