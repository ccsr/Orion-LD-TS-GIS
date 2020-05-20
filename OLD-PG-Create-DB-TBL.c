//
//  OLD-PG-Create-DB-TBL.c
//  Orion-LD-TS-GIS
//
//  Created by CHANDRA CHALLAGONDA on 14.04.20.
//  Copyright © 2020 CHANDRA CHALLAGONDA. All rights reserved.
//

#include </usr/include/postgresql/libpq-fe.h>
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

    char* oldPgDbConnCheckSql = "user=postgres password=orion dbname=postgres";

    puts("here we are - 1.1");

    //strcat (oldPgDbConnCheckSql, "oldTenantName");
    //strcat (oldPgDbConnCheckSql, pgDbName);

    char oldPgDbSql[50] = "CREATE DATABASE ";   //This HARDCODED
    char *oldPgDbSqlSyntax = ";";

    puts("here we are - 1.1");

    strcat (oldPgDbSql, oldTenantName);
    strcat (oldPgDbSql, oldPgDbSqlSyntax);

    printf("Full sentence of tenand database command is %s\n",oldPgDbSql);

    puts("here we are - 2");

    PGconn* oldPgConn = OldPg_OpenConnection(oldPgDbConnCheckSql);

    PGresult* oldPgRes;

    puts("here we are - 3");
    char oldPgDbSqlExec[40] = "user=postgres password=orion dbname=";
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
            puts("here we are - 3.3");
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
    const char* oldPgDbObjsql[5];
    puts("here we are 7");

    oldPgDbObjsql[0] = "CREATE EXTENSION IF NOT EXISTS postgis";
    oldPgDbObjsql[1] = "CREATE TABLE IF NOT EXISTS entity_table (entity_id TEXT NOT NULL,entity_type TEXT,createdAt TIMESTAMP,modifiedAt TIMESTAMP,PRIMARY KEY (entity_id))";
    //Objsql[2] = "CREATE EXTENSION IF NOT EXISTS timescaledb";
    oldPgDbObjsql[2] = "create type attribute_value_type_enum as enum ('value_type_string', 'value_type_number', 'value_type_boolean', 'value_type_relation')";
    //oldPgDbObjsql[4] = "CREATE TABLE IF NOT EXISTS attributes_table (entity_id TEXT NOT NULL REFERENCES entity_table(entity_id),attribute_id TEXT NOT NULL, attribute_name TEXT, attribute_value_type attribute_value_type_enum, attribute_sub_propery BOOL, attribute_unit_code TEXT, attribute_data_set_id TEXT, attribute_instance_id bigint GENERATED BY DEFAULT AS IDENTITY(START WITH 1 INCREMENT BY 1), attribute_value_string TEXT, attribute_value_boolean BOOL, attribute_value_number float8, attribute_value_relation TEXT, geo_property GEOMETRY,created_at TIMESTAMP NOT NULL,modified_at TIMESTAMP NOT NULL, observed_at TIMESTAMP NOT NULL,PRIMARY KEY (attribute_id,observed_at,created_at,modified_at))";
    oldPgDbObjsql[3] = "CREATE TABLE IF NOT EXISTS attributes_table (entity_id TEXT NOT NULL REFERENCES entity_table(entity_id),attribute_id TEXT NOT NULL, attribute_name TEXT, attribute_value_type attribute_value_type_enum, attribute_sub_propery BOOL, attribute_unit_code TEXT, attribute_data_set_id TEXT, attribute_instance_id bigint GENERATED BY DEFAULT AS IDENTITY(START WITH 1 INCREMENT BY 1), attribute_value_string TEXT, attribute_value_boolean BOOL, attribute_value_number float8, attribute_value_relation TEXT, geo_property GEOMETRY,created_at TIMESTAMP NOT NULL,modified_at TIMESTAMP NOT NULL, observed_at TIMESTAMP NOT NULL,PRIMARY KEY (attribute_id,observed_at,created_at,modified_at))";
    //oldPgDbObjsql[5] = "SELECT create_hypertable('attributes_table', 'modified_at')";
    //oldPgDbObjsql[6] = "SELECT create_hypertable('attributes_table', 'created_at')";
    //oldPgDbObjsql[7] = "SELECT create_hypertable('attributes_table', 'observed_at')";
    oldPgDbObjsql[4] = "CREATE TABLE IF NOT EXISTS attribute_sub_properties_table (entity_id TEXT NOT NULL,attribute_id TEXT NOT NULL,attribute_instance_id bigint, sub_attrubute_id TEXT NOT NULL, sub_attribute_value_type attribute_value_type_enum,sub_attribute_value_string TEXT, sub_attribute_value_boolean BOOL, sub_attribute_value_number float8, sub_attribute_value_relation TEXT,sub_attribute_name TEXT,sub_attribute_geo_property GEOMETRY,sub_attribute_unit_code TEXT,PRIMARY KEY (attribute_instance_id))";

    puts("here we are 8");
    printf("Database name with tenant is %s\n",oldPgDbSql);

    char oldPgDbSqlExec[50] = "user=postgres password=orion dbname=";
    strcat (oldPgDbSqlExec, oldPgDbSql);

    printf("The exec statement is %s\n",oldPgDbSqlExec);

    PGconn* oldPgConn = OldPg_OpenConnection(oldPgDbSqlExec);

    puts("here we are 9");

    PGresult* oldPgRes;

    if(oldPgConn != NULL)
    {
        for(int oldPgDbNumObj = 0; oldPgDbNumObj < 5; oldPgDbNumObj++)
        {
            puts("here we are 9.0");
            printf("The SQL statement is - %s\n",oldPgDbObjsql[oldPgDbNumObj]);
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
        puts("here we are 10");
    }
    OldPg_Closeconnection(oldPgConn);
    puts("here we are 11");
}
