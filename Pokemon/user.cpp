#include "user.h"

USER::USER()
{
	//userName=
	//passWord=
	nick = userName;//默认等于用户名
	petNum = 0;
	//winRate = 0;
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

string USER::Get_Nick() const
{
	return nick;
}

void USER::Input_Nick(string unick)
{
	nick = unick;
}

int USER::Get_PetNum() const
{
	return petNum;
}

void USER::Input_PetNum(int pnum)
{
	petNum = pnum;
}

int USER::Get_AdvNum() const
{
	int advNum = 0;
	for (int i = 0; i < petNum; ++i)
	{
		if (pets[i]->Get_Rank() >= 15)
			++advNum;
	}
	return advNum;
}

int USER::Get_FightTime() const
{
	return fightTime;
}

void USER::Input_FightTime(int uftime)
{
	fightTime = uftime;
}

int USER::Get_WinTime() const
{
	return winTime;
}

void USER::Input_WinTime(int uwintime)
{
	winTime = uwintime;
}

double USER::Get_WinRate() const
{
	double winRate;
	winRate = (double)winTime / (double)fightTime;
	return winRate;
}

BADGE USER::Get_PetNumBadge() const
{
	BADGE numBadge;
	if (petNum < 3)
		numBadge = NONE;
	else if (petNum >= 3 && petNum < 5)
		numBadge = CUPREOUS;
	else if (petNum >= 5 && petNum < 8)
		numBadge = SLIVERN;
	else
		numBadge = GOLDEN;
	return numBadge;
}

BADGE USER::Get_AdvBadge() const
{
	int AdvNum = Get_AdvNum();
	BADGE advBadge;
	if (AdvNum < 1)
		advBadge = NONE;
	else if (AdvNum >= 1 && AdvNum < 3)
		advBadge = CUPREOUS;
	else if (AdvNum >= 3 && AdvNum < 5)
		advBadge = SLIVERN;
	else
		advBadge = GOLDEN;
	return advBadge;
}


const POKEMON * USER::ReadPets(int order) const
{
	return pets[order];
}

POKEMON * USER::WritePets(int order)
{
	return pets[order];
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
		switch (random)
		{
		case 0:
			pets[i] = new GYARADOS;
			break;
		case 1:
			pets[i] = new HAPPINY;
			break;
		case 2:
			pets[i] = new SQUIRTLE;
			break;
		case 3:
			pets[i] = new MEWTWO;
			break;
		case 4:
			pets[i] = new INCINEROAR;
			break;
		case 5:
			pets[i] = new WOBBUFFET;
			break;
		case 6:
			pets[i] = new STEELIX;
			break;
		case 7:
			pets[i] = new ALAKAZAM;
		default:
			break;
		}
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
	sql = "INSERT INTO USER (USERNAME,PASSWORD,NICK,PETNUM,FIGHTTIME,WINTIME) "  \
		"VALUES ('";
	sql += userName;
	sql += "','";
	sql += passWord;
	sql += "','";
	sql += nick;
	sql += "',";
	sql += to_string(petNum);
	sql += ",";
	sql += to_string(fightTime);
	sql += ",";
	sql += to_string(winTime);
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
		sql = "INSERT INTO PET (USERNAME,PETORDER,KIND,NAME,RANK,EXP,HP,ATKI,ATK,DEF,ACCURACY,"\
			"EVASIVENESS,WTYPE,ALLSKILLCNT,GOTSKILLCNT,NICK,"\
			"SKILL0OWN,SKILL1OWN,SKILL2OWN,SKILL3OWN,SKILL4OWN,SKILL5OWN)"\
			"VALUES ('";
		sql += userName;
		sql += "',";
		sql += to_string(pets[i]->Get_Order());
		sql += ",";
		sql += to_string(pets[i]->Get_Kind());
		sql += ",'";
		sql += pets[i]->Get_Name();
		sql += "',";
		sql += to_string(pets[i]->Get_Rank());
		sql += ",";
		sql += to_string(pets[i]->Get_Exp());
		sql += ",";
		sql += to_string(pets[i]->Get_Hp());
		sql += ",";
		sql += to_string(pets[i]->Get_AtkI());
		sql += ",";
		sql += to_string(pets[i]->Get_Atk());
		sql += ",";
		sql += to_string(pets[i]->Get_Def());
		sql += ",";
		sql += to_string(pets[i]->Get_Accuracy());
		sql += ",";
		sql += to_string(pets[i]->Get_Evasiveness());
		sql += ",";
		sql += to_string(pets[i]->Get_Type());
		sql += ",";
		sql += to_string(pets[i]->Get_ALLSkillCnt());
		sql += ",";
		sql += to_string(pets[i]->Get_GotSkillCnt());
		sql += ",'";
		sql += pets[i]->Get_Nick();
		sql += "','";

		const SKILL* theSkillptr = pets[i]->Access_AllSkill();
		sql += to_string(theSkillptr->Selected);
		sql += ",'";
		++theSkillptr;
		sql += to_string(theSkillptr->Selected);
		sql += ",'";
		++theSkillptr;
		sql += to_string(theSkillptr->Selected);
		sql += ",'";
		++theSkillptr;
		sql += to_string(theSkillptr->Selected);
		sql += ",'";
		++theSkillptr;
		sql += to_string(theSkillptr->Selected);
		sql += ",'";
		++theSkillptr;
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
	nick = pResult[2];
	petNum = atoi(pResult[3]);
	fightTime = atoi(pResult[4]);
	winTime = atoi(pResult[5]);
	sqlite3_free_table(pResult);
	//测试输出////////////////////
	cout << userName << endl << passWord << endl << nick << petNum << endl << fightTime << endl << winTime << endl;

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

		int j = 1;
		int order = atoi(pResult[j]);
		switch (order)
		{
		case 0:
			pets[i] = new GYARADOS;
			break;
		case 1:
			pets[i] = new HAPPINY;
			break;
		case 2:
			pets[i] = new SQUIRTLE;
			break;
		case 3:
			pets[i] = new MEWTWO;
			break;
		case 4:
			pets[i] = new INCINEROAR;
			break;
		case 5:
			pets[i] = new WOBBUFFET;
			break;
		case 6:
			pets[i] = new STEELIX;
			break;
		case 7:
			pets[i] = new ALAKAZAM;
		default:
			break;
		}
		pets[i]->Input_Order(order);
		++j;
		pets[i]->Input_Kind((POKEMONKIND)atoi(pResult[j]));
		++j;
		pets[i]->Input_Name(pResult[j]);
		++j;
		pets[i]->Input_Rank(atoi(pResult[j]));
		++j;
		pets[i]->Input_Exp(atoi(pResult[j]));
		++j;
		pets[i]->Input_Hp(strtod(pResult[j],NULL));
		++j;
		pets[i]->Input_AtkI(atoi(pResult[j]));
		++j;
		pets[i]->Input_Atk(atoi(pResult[j]));
		++j;
		pets[i]->Input_Def(atoi(pResult[j]));
		++j;
		pets[i]->Input_Accuracy(strtod(pResult[j], NULL));
		++j;
		pets[i]->Input_Evasiveness(strtod(pResult[j], NULL));
		++j;
		pets[i]->Input_Type((WUXINGTYPE)atoi(pResult[j]));
		++j;
		pets[i]->Input_ALLSkillCnt(atoi(pResult[j]));
		++j;
		pets[i]->Input_GotSkillCnt(atoi(pResult[j]));
		++j;
		pets[i]->Input_Nick(pResult[j]);
		++j;
		PSKILL *theSkill = pets[i]->Write_GotSkill(0);
		for (int k = 0; k <= 5; ++k)
		{
			if ((OWN)atoi(pResult[j]) == OWNED)
			{
				*theSkill = pets[i]->Write_AllSkill() + k;
				++theSkill;
			}
			++j;
		}
	}

	sqlite3_close(db);
}
