/* ---------------------------------------------------------------------------
** Project for the course EDA031 at Lunds University, spring 2016.
**
** clientMain.h
**
** Runs a text based client that connects to the database and can
** perform tasks such as: list newsgroups/articles, create and delete
** newsgroups/articles as well as read articles.
**
** Authors: Andres Saemundsson, Anton Friberg, Oscar Gunneson
** -------------------------------------------------------------------------*/
#ifndef CLIENTMAIN_H
#define CLIENTMAIN_H

/*-------------------------------------
    I N C L U D E
-------------------------------------*/
#include <iostream>

#include "inputhandler.h"
#include "clientcommandhandler.h"
#include "../connection/connection.h"
#include "../connection/messagehandler.h"
#include "../connection/exceptions/ngexistsexception.h"
#include "../connection/exceptions/ngdoesnotexistexception.h"
#include "../connection/exceptions/noarticleexception.h"
#include "../connection/exceptions/invalidpathexception.h"


#endif // CLIENTMAIN_H
