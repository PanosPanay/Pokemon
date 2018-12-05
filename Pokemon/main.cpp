#include"pokemon.h"
#include"fight.h"
#include"sqlite3.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

//链接数据库并创建用户和宠物2个表
void CreatTable()
{
	sqlite3 *db;
	char *zErrMsg = 0;
	int  rc;
	string sql;

	/* Open database */
	rc = sqlite3_open("pokemon.db", &db);
	if (rc) {
		fprintf(stderr, "Can't open database pokemon.db: %s\n", sqlite3_errmsg(db));
		exit(0);
	}
	else {
		fprintf(stdout, "Opened database pokemon.db successfully\n");
	}

	//创建用户表
	/* Create SQL statement */
	sql = "CREATE TABLE USER("  \
		"USERNAME TEXT PRIMARY KEY     NOT NULL," \
		"PASSWORD       TEXT    NOT NULL," \
		"PETNUM         INT     NOT NULL," \
		"WINRATE        REAL	NOT NULL," \
		"NUMBADGE		INT		NOT NULL,"\
		"ADVBADGE		INT		NOT	NULL);";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql.data(), callback, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Table USER created successfully\n");
	}

	//创建精灵表
	/* Create SQL statement */
	sql = "CREATE TABLE PET("  \
		"USERNAME	TEXT	NOT NULL,"\
		"KIND		INT		NOT NULL,"\
		"NAME		TEXT    NOT NULL," \
		"RANK       INT		NOT NULL," \
		"EXP        INT     NOT NULL," \
		"HP			REAL	NOT NULL," \
		"AKTI		INT		NOT NULL,"\
		"ATK		INT		NOT	NULL,"\
		"DEF		INT		NOT NULL,"\
		"ACCURACY	REAL		NOT	NULL,"\
		"EVASIVENESS	REAL	NOT NULL,"\
		"WTYPE		INT		NOT	NULL,"\
		"ALLSKILLCNT	INT	NOT	NULL,"\
		"GOTSKILLCNT	INT	NOT	NULL,"\
		"NICK		TEXT	NOT NULL,"\
		"SKILL0NAME	TEXT	NOT NULL,"\
		"SKILL0RANK	INT		NOT	NULL,"\
		"SKILL0KIND	INT		NOT	NULL,"\
		"SKILL0POWER	INT	NOT NULL,"\
		"SKILL0HIT	INT		NOT NULL,"\
		"SKILL0OWN	INT		NOT NULL,"\
		"SKILL1NAME	TEXT	NOT NULL,"\
		"SKILL1RANK	INT		NOT	NULL,"\
		"SKILL1KIND	INT		NOT	NULL,"\
		"SKILL1POWER	INT	NOT NULL,"\
		"SKILL1HIT	INT		NOT NULL,"\
		"SKILL1OWN	INT		NOT NULL,"\
		"SKILL2NAME	TEXT	NOT NULL,"\
		"SKILL2RANK	INT		NOT	NULL,"\
		"SKILL2KIND	INT		NOT	NULL,"\
		"SKILL2POWER	INT	NOT NULL,"\
		"SKILL2HIT	INT		NOT NULL,"\
		"SKILL2OWN	INT		NOT NULL,"\
		"SKILL3NAME	TEXT	NOT NULL,"\
		"SKILL3RANK	INT		NOT	NULL,"\
		"SKILL3KIND	INT		NOT	NULL,"\
		"SKILL3POWER	INT	NOT NULL,"\
		"SKILL3HIT	INT		NOT NULL,"\
		"SKILL3OWN	INT		NOT NULL,"\
		"SKILL4NAME	TEXT	NOT NULL,"\
		"SKILL4RANK	INT		NOT	NULL,"\
		"SKILL4KIND	INT		NOT	NULL,"\
		"SKILL4POWER	INT	NOT NULL,"\
		"SKILL4HIT	INT		NOT NULL,"\
		"SKILL4OWN	INT		NOT NULL,"\
		"SKILL5NAME	TEXT	NOT NULL,"\
		"SKILL5RANK	INT		NOT	NULL,"\
		"SKILL5KIND	INT		NOT	NULL,"\
		"SKILL5POWER	INT	NOT NULL,"\
		"SKILL5HIT	INT		NOT NULL,"\
		"SKILL5OWN	INT		NOT NULL);";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql.data(), callback, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Table USER created successfully\n");
	}

	sqlite3_close(db);
}

int main()
{
	//初始运行一次,创建一个表就注释掉(已创建，不需要重复创建）
	//CreatTable();

	system("pause");
	return 0;
}