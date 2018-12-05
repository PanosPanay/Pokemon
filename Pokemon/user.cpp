#include "user.h"

USER::USER()
{
	//userName=
	//passWord=
	petNum = 0;
	//winRate
	//2个徽章
	/////////////注册成功后再随机发放3只精灵
}

string USER::Get_UserName() const
{
	return userName;
}

void USER::Input_UserName(string uname)
{
	userName = uname;
}

string USER::Get_PassWord() const
{
	return passWord;
}

void USER::Input_PassWord(string upw)
{
	passWord = upw;
}

int USER::Get_PetNum() const
{
	return petNum;
}

void USER::Input_PetNum(int pnum)
{
	petNum = pnum;
}

const POKEMON * USER::ReadPets(int order) const
{
	const POKEMON* aPet = pets + order;
	return aPet;
}

POKEMON * USER::WritePets(int order)
{
	POKEMON* aPet = pets + order;
	return aPet;
}

void USER::InitialPets()//初始送出3只精灵，未完成
{
	for (int i = 0; i < 3; ++i)
	{
		srand((unsigned)time(NULL));
		int random = rand() % PETMAX;
		/*switch (random) 
		{
		case 0:
			GYARADOS gyarados1;
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
		case 7:
			break;
		}*/
	}
}

void USER::InsertUser()
{
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	string sql;

	/* Open database */
	rc = sqlite3_open("pokemon.db", &db);
	if (rc) {
		fprintf(stderr, "Can't open database pokemon.db: %s\n", sqlite3_errmsg(db));
		exit(0);
	}
	else {
		fprintf(stderr, "Opened database pokemon.db successfully\n");
	}

	//插入用户信息
	/* Create SQL statement */
	sql = "INSERT INTO USER (USERNAME,PASSWORD,PETNUM,WINRATE,NUMBADGE,ADVBADGE) "  \
		"VALUES ('";
	sql += userName;
	sql += "','";
	sql += passWord;
	sql += "',";
	sql += to_string(petNum);
	sql += ",";
	sql += to_string(winRate);
	sql += ",";
	sql += to_string(petNumBadge);
	sql += ",";
	sql += to_string(petAdvancedBadge);
	sql += ");";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql.data(), callback, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "USER Records created successfully\n");
	}
	sqlite3_close(db);
}

void USER::UpdateUser()
{
}

void USER::InsertPet()//需要循环多次调用？？？？？？？？？？？？？？？？？？根据宠物数量循环
{
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	string sql;

	/* Open database */
	rc = sqlite3_open("pokemon.db", &db);
	if (rc) {
		fprintf(stderr, "Can't open database pokemon.db: %s\n", sqlite3_errmsg(db));
		exit(0);
	}
	else {
		fprintf(stderr, "Opened database pokemon.db successfully\n");
	}

	//插入用户的宠物信息
	for (int i = 0; i < petNum; ++i)
	{
		/* Create SQL statement */
		sql = "INSERT INTO PET (USERNAME,KIND,NAME,RANK,EXP,HP,ATKI,ATK,DEF,ACCURACY,"\
			"EVASIVENESS,WTYPE,ALLSKILLCNT,GOTSKILLCNT,NICK,"\
			"SKILL0NAME,SKILL0RANK,SKILL0KIND,SKILL0POWER,SKILL0HIT,SKILL0OWN,"\
			"SKILL1NAME,SKILL1RANK,SKILL1KIND,SKILL1POWER,SKILL1HIT,SKILL1OWN,"\
			"SKILL2NAME,SKILL2RANK,SKILL2KIND,SKILL2POWER,SKILL2HIT,SKILL2OWN,"\
			"SKILL3NAME,SKILL3RANK,SKILL3KIND,SKILL3POWER,SKILL3HIT,SKILL3OWN,"\
			"SKILL4NAME,SKILL4RANK,SKILL4KIND,SKILL4POWER,SKILL4HIT,SKILL4OWN,"\
			"SKILL5NAME,SKILL5RANK,SKILL5KIND,SKILL5POWER,SKILL5HIT,SKILL5OWN) "\
			"VALUES ('";
		sql += userName;
		sql += "',";
		sql += to_string(pets[i].Get_Kind());
		sql += ",'";
		sql += pets[i].Get_Name();
		sql += "',";
		sql += to_string(pets[i].Get_Rank());
		sql += ",";
		/*sql += to_string(petNumBadge);
		sql += ",";
		sql += to_string(petAdvancedBadge);
		sql += ");";*///////////////////////////////处理到这里

		/* Execute SQL statement */
		rc = sqlite3_exec(db, sql.data(), callback, 0, &zErrMsg);
		if (rc != SQLITE_OK) {
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}
		else {
			fprintf(stdout, "USER Records created successfully\n");
		}
	}
	
	sqlite3_close(db);
}

void USER::UpdatePet()
{
}
