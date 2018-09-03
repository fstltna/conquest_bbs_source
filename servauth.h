/* 
 * server auth
 *
 * $Id$
 *
 * Copyright 2003 Jon Trulson under the ARTISTIC LICENSE. (See LICENSE).
 */

#ifndef SERVAUTH_H_INCLUDED
#define SERVAUTH_H_INCLUDED

#include "conqdef.h"
#include "datatypes.h"
#include "protocol.h"

int Authenticate(char *name, char *password);


#endif /* SERVAUTH_H_INCLUDED */
