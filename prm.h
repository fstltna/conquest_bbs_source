/* 
 * prompt utils
 *
 * $Id$
 *
 * Copyright 1999-2004 Jon Trulson under the ARTISTIC LICENSE. (See LICENSE).
 */

#ifndef _PRM_H
#define _PRM_H

/* return values from prmProcInput() */
/* retval > 0 is the terminator char entered */

#define PRM_OK            0     /* everything ok */
#define PRM_MAXLEN        -1    /* maxlen exceeded */


typedef struct _prompt {
  int  preinit;                /* pre-initing the prompt resp? */
  char *buf;                    /* response */
  int   buflen;
  char *pbuf;                   /* the prompt */
  char *terms;                  /* terminators */
  int   index;                  /* only used in CP for now */
} prm_t;

int prmProcInput(prm_t *prm, int ch);


#endif /* _PRM_H */
