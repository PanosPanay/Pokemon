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
	rc = sqlite3_open("test.db", &db);
	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
		exit(0);
	}
	else {
		fprintf(stderr, "Opened database successfully\n");
	}

	//插入
	/* Create SQL statement */
	/*sql = "INSERT INTO USER (USERNAME,PASSWORD,PETNUM,WINRATE,NUMBADGE,ADVBADGE) "  \
		"VALUES (1, 'Paul', 32, 'California', 20000.00 ); " \
		"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY) "  \
		"VALUES (2, 'Allen', 25, 'Texas', 15000.00 ); "     \
		"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
		"VALUES (3, 'Teddy', 23, 'Norway', 20000.00 );" \
		"INSERT INTO COMPANY (ID,NAME,AGE,ADDRESS,SALARY)" \
		"VALUES (4, 'Mark', 25, 'Rich-Mond ', 65000.00 );";*////////写到这里
		
	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql.data(), callback, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Records created successfully\n");
	}
	sqlite3_close(db);

}

void USER::UpdateUser()
{
}

void USER::InsertPet()
{
}

void USER::UpdatePet()
{
}
