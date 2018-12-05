#include "user.h"

USER::USER()
{
	//userName=
	//passWord=
	petNum = 0;
	winRate = 0;
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

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	for (i = 0; i < argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

void USER::InitialPets()//初始送出3只精灵
{
	for (int i = 0; i < 3; ++i)
	{
		srand((unsigned)time(NULL));
		int random = rand() % PETMAX;
		ALLPETS allPetsList;
		pets[i] = *(allPetsList.GetAPet(random));
		++petNum;
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

void USER::InsertPet()
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
		sql += to_string(pets[i].Get_Exp());
		sql += ",";
		sql += to_string(pets[i].Get_Hp());
		sql += ",";
		sql += to_string(pets[i].Get_AtkI());
		sql += ",";
		sql += to_string(pets[i].Get_Atk());
		sql += ",";
		sql += to_string(pets[i].Get_Def());
		sql += ",";
		sql += to_string(pets[i].Get_Accuracy());
		sql += ",";
		sql += to_string(pets[i].Get_Evasiveness());
		sql += ",";
		sql += to_string(pets[i].Get_Type());
		sql += ",";
		sql += to_string(pets[i].Get_ALLSkillCnt());
		sql += ",";
		sql += to_string(pets[i].Get_GotSkillCnt());
		sql += ",'";
		sql += pets[i].Get_Nick();
		sql += "','";
		const SKILL* theSkillptr = pets[i].Access_AllSkill();
		sql += theSkillptr->SkillName;	//开始插入技能0
		sql += "',";
		sql += to_string(theSkillptr->SkillRank);
		sql += ",";
		sql += to_string(theSkillptr->SkillKind);
		sql += ",";
		sql += to_string(theSkillptr->SkillPower);
		sql += ",";
		sql += to_string(theSkillptr->SkillHit);
		sql += ",";
		sql += to_string(theSkillptr->Selected);
		sql += ",'";
		++theSkillptr;
		sql += theSkillptr->SkillName;	//开始插入技能1
		sql += "',";
		sql += to_string(theSkillptr->SkillRank);
		sql += ",";
		sql += to_string(theSkillptr->SkillKind);
		sql += ",";
		sql += to_string(theSkillptr->SkillPower);
		sql += ",";
		sql += to_string(theSkillptr->SkillHit);
		sql += ",";
		sql += to_string(theSkillptr->Selected);
		sql += ",'";
		++theSkillptr;
		sql += theSkillptr->SkillName;	//开始插入技能2
		sql += "',";
		sql += to_string(theSkillptr->SkillRank);
		sql += ",";
		sql += to_string(theSkillptr->SkillKind);
		sql += ",";
		sql += to_string(theSkillptr->SkillPower);
		sql += ",";
		sql += to_string(theSkillptr->SkillHit);
		sql += ",";
		sql += to_string(theSkillptr->Selected);
		sql += ",'";
		++theSkillptr;
		sql += theSkillptr->SkillName;	//开始插入技能3
		sql += "',";
		sql += to_string(theSkillptr->SkillRank);
		sql += ",";
		sql += to_string(theSkillptr->SkillKind);
		sql += ",";
		sql += to_string(theSkillptr->SkillPower);
		sql += ",";
		sql += to_string(theSkillptr->SkillHit);
		sql += ",";
		sql += to_string(theSkillptr->Selected);
		sql += ",'";
		++theSkillptr;
		sql += theSkillptr->SkillName;	//开始插入技能4
		sql += "',";
		sql += to_string(theSkillptr->SkillRank);
		sql += ",";
		sql += to_string(theSkillptr->SkillKind);
		sql += ",";
		sql += to_string(theSkillptr->SkillPower);
		sql += ",";
		sql += to_string(theSkillptr->SkillHit);
		sql += ",";
		sql += to_string(theSkillptr->Selected);
		sql += ",'";
		++theSkillptr;
		sql += theSkillptr->SkillName;	//开始插入技能5
		sql += "',";
		sql += to_string(theSkillptr->SkillRank);
		sql += ",";
		sql += to_string(theSkillptr->SkillKind);
		sql += ",";
		sql += to_string(theSkillptr->SkillPower);
		sql += ",";
		sql += to_string(theSkillptr->SkillHit);
		sql += ",";
		sql += to_string(theSkillptr->Selected);
		sql += ");";

		/* Execute SQL statement */
		rc = sqlite3_exec(db, sql.data(), callback, 0, &zErrMsg);
		if (rc != SQLITE_OK) {
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}
		else {
			fprintf(stdout, "PET Records created successfully\n");
		}
	}
	
	sqlite3_close(db);
}

void USER::UpdatePet()
{
}

void USER::FillInfo_from_Sqlite()
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

	//取出用户信息
	sql = "SELECT * FROM USER WHERE USERNAME='";
	sql += userName;
	sql += "';";
	char** pResult;
	int nRow;
	int nCol;
	rc = sqlite3_get_table(db, sql.data(), &pResult, &nRow, &nCol, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		sqlite3_close(db);
		cout << zErrMsg << endl;
		sqlite3_free(zErrMsg);
		exit(0);
	}
	userName = pResult[0];
	passWord = pResult[1];
	petNum = atoi(pResult[2]);
	winRate = strtod(pResult[3], NULL);
	petNumBadge = (BADGE)atoi(pResult[4]);
	petAdvancedBadge = (BADGE)atoi(pResult[5]);
	sqlite3_free_table(pResult);
	//测试输出////////////////////
	cout << userName << endl << passWord << endl << petNum << endl << winRate << endl << petNumBadge << endl << petAdvancedBadge << endl;

	//取出宠物信息
	sql = "SELECT * FROM PET WHERE USERNAME='";
	sql += userName;
	sql += "';";
	rc = sqlite3_get_table(db, sql.data(), &pResult, &nRow, &nCol, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		sqlite3_close(db);
		cout << zErrMsg << endl;
		sqlite3_free(zErrMsg);
		exit(0);
	}
	for (int i = 0; i < nRow; ++i)//or i<petNum
	{
		int j = 0;
		pets[i].Input_Kind((POKEMONKIND)atoi(pResult[j]));
		++j;
		pets[i].Input_Name(pResult[j]);
		++j;

	}

	sqlite3_close(db);
}
