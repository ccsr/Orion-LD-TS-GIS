//
//  OLD-PG-Conn.c
//  Orion-LD-TS-GIS
//
//  Created by CHANDRA CHALLAGONDA on 14.04.20.
//  Copyright © 2020 CHANDRA CHALLAGONDA. All rights reserved.
//

#include </usr/include/postgresql/libpq-fe.h>
#include "OLD-PG-Conn.h"

void OldPg_Closeconnection(PGconn* conn)
{
    PQfinish(conn);
}


PGconn* OldPg_OpenConnection(char* oldPgConnString)
{
    PGconn *oldPgConn = PQconnectdb(oldPgConnString);

    if (PQstatus(oldPgConn) == CONNECTION_BAD)
    {
        fprintf(stderr, "CONNECTION_BAD %s\n", PQerrorMessage(oldPgConn));

        OldPg_Closeconnection(oldPgConn);

        return NULL;
    }
    else if (PQstatus(oldPgConn) == CONNECTION_OK)
    {
        puts("CONNECTION_OK");

        return oldPgConn;
    }
}
