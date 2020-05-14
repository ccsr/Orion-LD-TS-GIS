//
//  OLD-PG-Create-DB-TBL.c
//  Orion-LD-TS-GIS
//
//  Created by CHANDRA CHALLAGONDA on 14.04.20.
//  Copyright © 2020 CHANDRA CHALLAGONDA. All rights reserved.
//

#include <libpq-fe.h>
#include "OLD-PG-Create-DB-TBL.h"
#include "OLD-PG-Conn.h"

void OldPg_CreateDB(char *oldTenantName,char *pgDbName)
{
    puts("here we are - 0");
    if (oldTenantName == NULL)
    {
	puts("here we are - 0.1");
        oldTenantName = "orion_ld";
	printf("printing the value of oldTenantName %s",oldTenantName);
    }
    
    if (pgDbName == NULL) {
        pgDbName = "postgres";
    }

    puts("here we are - 1");
    printf("%s\n",oldTenantName);
    
    char* oldPgDbConnCheckSql = "user=postgres dbname=postgres";
   
    puts("here we are - 1.1");
	    
    //strcat (oldPgDbConnCheckSql, "oldTenantName");
    //strcat (oldPgDbConnCheckSql, pgDbName);
    
    char oldPgDbSql[30] = "CREATE DATABASE ";   //This HARDCODED
    char *oldPgDbSqlSyntax = ";";

    puts("here we are - 1.1");

    strcat (oldPgDbSql, oldTenantName);
    strcat (oldPgDbSql, oldPgDbSqlSyntax);

    printf("Full sentence of tenand database command is %s\n",oldPgDbSql);

    puts("here we are - 2");
    
    PGconn* oldPgConn = OldPg_OpenConnection(oldPgDbConnCheckSql);

    PGresult* oldPgRes;
    
    puts("here we are - 3");
    char oldPgDbSqlExec[40] = "user=postgres dbname=";
    strcat (oldPgDbSqlExec, oldTenantName);

    if(oldPgConn != NULL)
    {
        oldPgRes = PQexec(oldPgConn, oldPgDbSql);
	PGconn* oldPgConn = OldPg_OpenConnection(oldPgDbSqlExec);

        if (PQresultStatus(oldPgRes) != PGRES_COMMAND_OK && PQstatus(oldPgConn) != CONNECTION_OK)
        {
	     puts("here we are - 3.1");
            fprintf(stderr, "%s\n", PQerrorMessage(oldPgConn));
        }
        else
        {
	    puts("here we are - 3.2");
            OldPg_CreateDB_Objects(oldTenantName);
        }

        puts("here we are - 4");
        
        PQclear(oldPgRes);
        
        puts("here we are - 5");

        OldPg_Closeconnection(oldPgConn);
        puts("here we are - 6");
    }
}

void OldPg_CreateDB_Objects(char* oldPgDbSql)
{
    const char* oldPgDbObjsql[4];
    puts("here we are 7");

    oldPgDbObjsql[0] = "CREATE EXTENSION IF NOT EXISTS postgis";
    oldPgDbObjsql[1] = "CREATE TABLE IF NOT EXISTS entity_table (entity_id TEXT NOT NULL,entity_type TEXT,createdAt TIMESTAMP,modifiedAt TIMESTAMP,PRIMARY KEY (entity_id))";
    oldPgDbObjsql[2] = "CREATE EXTENSION IF NOT EXISTS timescaledb CASCADE";
    oldPgDbObjsql[3] = "CREATE TABLE IF NOT EXISTS attributes_table (entity_id TEXT NOT NULL REFERENCES entity_table(entity_id),attribute_id TEXT NOT NULL,attribute_type TEXT,attribute_value TEXT, geo_property GEOMETRY,time TIMESTAMP,PRIMARY KEY (entity_id,attribute_id,time))";
   

    puts("here we are 8");
    printf("Database name with tenant is %s\n",oldPgDbSql);

    char oldPgDbSqlExec[40] = "user=postgres dbname=";
    strcat (oldPgDbSqlExec, oldPgDbSql);

    printf("The exec statement is %s\n",oldPgDbSqlExec);

    PGconn* oldPgConn = OldPg_OpenConnection(oldPgDbSqlExec);

    puts("here we are 9");

    PGresult* oldPgRes;

    if(oldPgConn != NULL)
    {
        for(int oldPgDbNumObj = 0; oldPgDbNumObj < 4; oldPgDbNumObj++)
        {
            oldPgRes = PQexec(oldPgConn, oldPgDbObjsql[oldPgDbNumObj]);

            puts("here we are 9.1");
	    if (PQresultStatus(oldPgRes) != PGRES_COMMAND_OK)
            {
                fprintf(stderr, "%s\n", PQerrorMessage(oldPgConn));

                break;
            }
	    puts("here we are 9.2");

            PQclear(oldPgRes);
        }

        OldPg_Closeconnection(oldPgConn);
    }
}
