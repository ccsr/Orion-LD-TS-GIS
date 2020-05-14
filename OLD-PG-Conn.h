//
//  OLD-PG-Conn.h
//  Orion-LD-TS-GIS
//
//  Created by CHANDRA CHALLAGONDA on 14.04.20.
//  Copyright © 2020 CHANDRA CHALLAGONDA. All rights reserved.
//

#ifndef Header_h
#define Header_h

#include<string.h>
#include</usr/include/postgresql/libpq-fe.h>


PGconn* OldPg_OpenConnection(char* oldPgConnString);
void OldPg_Closeconnection(PGconn*);


#endif /* Header_h */
