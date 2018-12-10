#include "user.h"

USER::USER()
{
	//userName=
	//passWord=
	nick = "NULL";//默认等于"NULL"
	petNum = 0;
	//winRate = 0;
	//2个徽章
	/////////////注册成功后再随机发放3只精灵
}

USER::~USER()
{
	for (int i = 0; i < petNum; ++i)
	{
		delete pets[i];
	}
}

int USER::Get_Online() const
{
	return online;
}

void USER::Input_Online(int uonline)
{
	online = uonline;
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
	if (fightTime == 0)
		winRate = 0;
	else
	{
		winRate = (double)winTime / (double)fightTime;
	}
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

void USER::InitialPets(int utotalOrder)//初始送出3只精灵
{
	for (int i = 0; i < 3; ++i)
	{
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
	pets[0]->Input_totalOrder(utotalOrder);
	pets[1]->Input_totalOrder(utotalOrder+1);
	pets[2]->Input_totalOrder(utotalOrder+2);
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
	sql = "INSERT INTO USER (USERNAME,PASSWORD,NICK,PETNUM,FIGHTTIME,WINTIME,ONLINE) "  \
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
	sql += ",";
	sql += to_string(online);
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
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	string sql;
	const char* data = "Callback function called";

	/* Open database */
	rc = sqlite3_open("pokemon.db", &db);
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		exit(0);
	}
	else {
		fprintf(stderr, "Opened database successfully\n");
	}

	/* Create merged SQL statement */
	sql = "UPDATE USER set USERNAME = '";
	sql += userName;
	sql += "', PASSWORD = '";
	sql += passWord;
	cout << "password2=" << passWord << endl;/////////////
	sql == "', NICK = '";
	sql += nick;
	sql += "', PETNUM = ";
	sql += to_string(petNum);
	sql += ", FIGHTTIME = ";
	sql += to_string(fightTime);
	sql += ", WINTIME = ";
	sql += to_string(winTime);
	sql += ", ONLINE = ";
	sql += to_string(online);
	sql += " where USERNAME='";
	sql += userName;
	sql += "';";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql.data(), callback, (void*)data, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Operation update user done successfully\n");
	}
	sqlite3_close(db);
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
			"SKILL0OWN,SKILL1OWN,SKILL2OWN,SKILL3OWN,SKILL4OWN,SKILL5OWN,TOTALORDER)"\
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
		sql += "',";

		const SKILL* theSkillptr = pets[i]->Access_AllSkill();
		sql += to_string(theSkillptr->Selected);
		sql += ",";
		++theSkillptr;
		sql += to_string(theSkillptr->Selected);
		sql += ",";
		++theSkillptr;
		sql += to_string(theSkillptr->Selected);
		sql += ",";
		++theSkillptr;
		sql += to_string(theSkillptr->Selected);
		sql += ",";
		++theSkillptr;
		sql += to_string(theSkillptr->Selected);
		sql += ",";
		++theSkillptr;
		sql += to_string(theSkillptr->Selected);
		sql += ",";

		sql += to_string(pets[i]->Get_totalOrder());
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
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	string sql;
	const char* data = "Callback function called";

	/* Open database */
	rc = sqlite3_open("pokemon.db", &db);
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		exit(0);
	}
	else {
		fprintf(stderr, "Opened database successfully\n");
	}

	/* Create merged SQL statement */
	//不必全部更新，有些数据不会改////////////////////////////
	for (int i = 0; i < petNum; ++i)
	{
		sql = "UPDATE PET set RANK = ";
		sql += to_string(pets[i]->Get_Rank());
		sql += ", EXP = ";
		sql += to_string(pets[i]->Get_Exp());
		sql += ", HP = ";
		sql += to_string(pets[i]->Get_Hp());
		sql += ", ATKI = ";
		sql += to_string(pets[i]->Get_AtkI());
		sql += ", ATK = ";
		sql += to_string(pets[i]->Get_Atk());
		sql += ", DEF = ";
		sql += to_string(pets[i]->Get_Def());
		sql += ", ACCURACY = ";
		sql += to_string(pets[i]->Get_Accuracy());
		sql += ", EVASIVENESS = ";
		sql += to_string(pets[i]->Get_Evasiveness());
		sql += ", WTYPE = ";
		sql += to_string(pets[i]->Get_Type());
		sql += ", ALLSKILLCNT = ";
		sql += to_string(pets[i]->Get_ALLSkillCnt());
		sql += ", GOTSKILLCNT = ";
		sql += to_string(pets[i]->Get_GotSkillCnt());
		sql += ", NICK = '";
		sql += pets[i]->Get_Nick();

		const SKILL* theSkillptr = pets[i]->Access_AllSkill();
		sql += "', SKILL0OWN = ";
		sql += to_string(theSkillptr->Selected);		
		++theSkillptr;
		sql += ", SKILL1OWN = ";
		sql += to_string(theSkillptr->Selected);
		++theSkillptr;
		sql += ", SKILL2OWN = ";
		sql += to_string(theSkillptr->Selected);
		++theSkillptr;
		sql += ", SKILL3OWN = ";
		sql += to_string(theSkillptr->Selected);
		++theSkillptr;
		sql += ", SKILL4OWN = ";
		sql += to_string(theSkillptr->Selected);
		++theSkillptr;
		sql += ", SKILL5OWN = ";
		sql += to_string(theSkillptr->Selected);

		//sql += ", TOTALORDER = ";
		//sql += to_string(pets[i]->Get_totalOrder());

		sql += " where TOTALORDER=";
		sql += to_string(pets[i]->Get_totalOrder());
		sql += ";";

		/* Execute SQL statement */
		rc = sqlite3_exec(db, sql.data(), callback, (void*)data, &zErrMsg);
		if (rc != SQLITE_OK) {
			fprintf(stderr, "SQL error: %s\n", zErrMsg);
			sqlite3_free(zErrMsg);
		}
		else {
			fprintf(stdout, "Operation update pet done successfully\n");
		}
	}
	sqlite3_close(db);
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
	userName = pResult[7];	
	passWord = pResult[8];
	nick = pResult[9];
	petNum = atoi(pResult[10]);
	fightTime = atoi(pResult[11]);
	winTime = atoi(pResult[12]);
	online = atoi(pResult[13]);
	sqlite3_free_table(pResult);
	//测试输出////////////////////
	cout << "从数据库取出用户：";
	cout << userName << " " << passWord << " " << nick << " " << petNum << " " << fightTime << " " << winTime << " " << online << endl;

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
	int j = 23;
	for (int i = 0; i < nRow; ++i)//or i<petNum
	{
		++j;
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
		pets[i]->Input_totalOrder(atoi(pResult[j]));
		++j;

		//测试输出//////////////////////////
		//cout << pets[i]->Get_Name() << " " << pets[i]->Access_GotSkill(0)->SkillName << endl;
	}
	cout << "successful get the user and his pets'info" << endl;
	sqlite3_close(db);
}
