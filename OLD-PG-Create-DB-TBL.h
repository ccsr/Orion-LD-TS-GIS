//
//  OLD-PG-Create-DB-TBL.h
//  Orion-LD-TS-GIS
//
//  Created by CHANDRA CHALLAGONDA on 14.04.20.
//  Copyright © 2020 CHANDRA CHALLAGONDA. All rights reserved.
//

#ifndef OLD_PG_Create_DB_TBL_h
#define OLD_PG_Create_DB_TBL_h

#include<string.h>
#include</usr/include/postgresql/libpq-fe.h>

void OldPg_CreateDB(char* oldTenantName,char* pgDbName);
void OldPg_CreateDB_Objects(char* oldPgDbSql);

#endif /* OLD_PG_Create_DB_TBL_h */
