#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#include"OLD-PG-Create-DB-TBL.h"
#include"OLD-PG-Conn.h"


int main(int argc, char* argv[])
{
    puts("-------------------------_______________________________--");
    puts("| After 18 years of Break this Old Fart is coding        |");
    puts("| PostgreSQL with libpq to adding TS & GIS capabilities  |");
    puts("| C is the most elegant programming laguage              |");
    puts("------------------------_____________________________---\n");

    OldPg_CreateDB(NULL,NULL);

    puts("some how function is executed\n");

    return EXIT_SUCCESS;
}
