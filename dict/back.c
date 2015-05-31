/*************************************************************************
  > File Name: back.c
  > Author: qiu
  > Mail: py_qiu@163.com 
  > Created Time: Sun 31 May 2015 02:36:58 PM CST
 ************************************************************************/

#include<stdio.h>
#include<sqlite3.h>
#define MAXLEN_SQL 50

sqlite3 *db;
int database_open()
{
	int result;
	result = sqlite3_open("database.db", &db);

	if (result != SQLITE_OK)
	{
		if (NULL != db)
		{
			printf ("open database failed \n");
			if (sqlite3_close(db) != SQLITE_OK)
			{
				printf ("server > close database error\n");
			}
			return -1; 
		}
		else
		{
			printf ("server > failed to allocate memory for database\n");
			if (sqlite3_close(db) != SQLITE_OK)
			{
				printf ("server > close database error\n");
			}
			return -1; 
		}
	}

	return 0;
}

int main()
{
database_open();
	char sql[MAXLEN_SQL];

	if (snprintf (sql, MAXLEN_SQL, "update users set state='N' where username='jack'") < 0)
	{
		printf ("snprintf sql error\n");
		return -1;
	}

	if (SQLITE_OK != sqlite3_exec(db, sql, NULL, NULL, NULL))
	{
		printf("failed\n");
		return -1;
	}
	printf ("success\n");

	return 0;
}


