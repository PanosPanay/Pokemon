#include"pokemon.h"
#include"user.h"
#include"fight.h"
#include"sqlite3.h"
#include<sstream>
//#include<winsock2.h>
#pragma comment(lib, "ws2_32.lib")
using namespace std;
const int USERMAX = 20;//设定最大同时登录的用户数
int petsCnt; //宠物总数
const int VIRTUAL_PETS_NUM = 8;//虚拟精灵数为8
//USER *playUsers[USERMAX];//存储当前在线的用户

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
		"NICK			TEXT	NOT NULL," \
		"PETNUM         INT     NOT NULL," \
		"FIGHTTIME      INT		NOT NULL," \
		"WINTIME		INT		NOT NULL," \
		"ONLINE			INT		NOT NULL);";

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
	//USERNAME是主人用户名，PETORDER是具体精灵类对应的序号
	sql = "CREATE TABLE PET("  \
		"USERNAME	TEXT	NOT NULL," \
		"PETORDER	INT		NOT NULL," \
		"KIND		INT		NOT NULL," \
		"NAME		TEXT    NOT NULL," \
		"RANK       INT		NOT NULL," \
		"EXP        INT     NOT NULL," \
		"HP			REAL	NOT NULL," \
		"ATKI		INT		NOT NULL," \
		"ATK		INT		NOT	NULL," \
		"DEF		INT		NOT NULL," \
		"ACCURACY	REAL		NOT	NULL,"\
		"EVASIVENESS	REAL	NOT NULL,"\
		"WTYPE		INT		NOT	NULL,"\
		"ALLSKILLCNT	INT	NOT	NULL,"\
		"GOTSKILLCNT	INT	NOT	NULL,"\
		"NICK		TEXT	NOT NULL,"\
		"SKILL0OWN	INT		NOT NULL,"\
		"SKILL1OWN	INT		NOT NULL,"\
		"SKILL2OWN	INT		NOT NULL,"\
		"SKILL3OWN	INT		NOT NULL,"\
		"SKILL4OWN	INT		NOT NULL,"\
		"SKILL5OWN	INT		NOT NULL,"\
		"TOTALORDER INT PRIMARY KEY NOT NULL);";

	/* Execute SQL statement */
	rc = sqlite3_exec(db, sql.data(), callback, 0, &zErrMsg);
	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}
	else {
		fprintf(stdout, "Table PET created successfully\n");
	}

	sqlite3_close(db);
}

//根据用户名查找用户是否存在		//返回值0：不存在；1：存在且密码输入正确；2：存在但密码输入错误
int sqlite_find_user_exist(string username,string password)
{
	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;
	string sql;
	int exist;

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
	sql += username;
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
	if (nRow == 0)
	{
		cout << "The userName \'" << username << "\' has not been signed." << endl;
		exist = 0;					//用户不存在
	}		
	else
	{
		if (password == pResult[8])//数据库是一直加，一行7个，第二行第2个，从0开始计，所以是8
		{
			cout << "Correct username and password." << endl;
			exist = 1;				//用户存在，且密码输入正确
		}
		else
		{
			//cout << pResult[8] << endl;
			cout << "Wrong password!" << endl;
			exist = 2;				//用户存在，但是密码输入错误
		}
	}
	sqlite3_close(db);
	return exist;
}

string Get_AllUserInfo()//获取所有注册用户的信息(用户名、在线状态、胜率)存到string中返回
{
	string userdata;
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
	sql = "SELECT * FROM USER;";
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
	cout << "用户数=" << nRow << endl;////////////
	userdata = to_string(nRow);
	userdata += "|";
	for (int i = 0; i < nRow; ++i)
	{
		userdata += pResult[(i + 1) * 7];
		userdata += "|";
		/*int j;
		for (j = 0; j < USERMAX&&(playUsers[j]==nullptr || playUsers[j]->Get_UserName()!= pResult[(i + 1) * 7]); ++j)
		{
		}
		if (j == USERMAX)//没有找到，即未登录
		{
			userdata += "离线|";
		}
		else
		{
			userdata += "在线|";
		}*///以上需要将PlayUsers[]数组设为全局变量,改为以下
		int onlineState = atoi(pResult[(i + 1) * 7 + 6]);
		if(onlineState==0)
			userdata += "离线|";
		else
			userdata += "在线|";

		int fightTime = atoi(pResult[(i + 1) * 7 + 4]);
		int winTime= atoi(pResult[(i + 1) * 7 + 5]);
		double winRate;
		if (fightTime == 0)
			winRate = 0;
		else
			winRate = (double)winTime / (double)fightTime;
		userdata += to_string(winRate);
		userdata += "|";
	}
	sqlite3_close(db);
	return userdata;
}

string Get_a_User_Info(string theUser)//获取数据库中第theUser个用户的精灵信息，用string返回
{
	string petsData;
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
	sql += theUser;
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
	int petsCnt = atoi(pResult[10]);//宠物数量
	cout << "精灵数=" << nRow << endl;////////////
	petsData = to_string(petsCnt);
	petsData += "|";

	sql = "SELECT * FROM PET WHERE USERNAME='";
	sql += theUser;
	sql += "';";
	rc = sqlite3_get_table(db, sql.data(), &pResult, &nRow, &nCol, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		sqlite3_close(db);
		cout << zErrMsg << endl;
		sqlite3_free(zErrMsg);
		exit(0);
	}	
	for (int i = 0; i < nRow; ++i)
	{
		petsData += pResult[(i + 1) * 23 + 3];//name
		petsData += "|";
		petsData += pResult[(i + 1) * 23 + 15];//nick
		petsData += "|";
		POKEMONKIND petKind = (POKEMONKIND)atoi(pResult[(i + 1) * 23 + 2]);
		switch (petKind)
		{
		case POWER:
			petsData += "力量型";
			break;
		case TANK:
			petsData += "肉盾型";
			break;
		case DEFENSIVE:
			petsData += "防御型";
			break;
		case AGILE:
			petsData += "敏捷型";
			break;
		}
		petsData += "|";
		WUXINGTYPE petType = (WUXINGTYPE)atoi(pResult[(i + 1) * 23 + 12]);
		switch (petType)
		{
		case SHUI:
			petsData += "水";
			break;
		case HUO:
			petsData += "火";
			break;
		case JIN:
			petsData += "金";
			break;
		case MU:
			petsData += "木";
			break;
		case TU:
			petsData += "土";
			break;
		default:
			break;
		}
		petsData += "|";
		petsData += pResult[(i + 1) * 23 + 4];//rank
		petsData += "|";
		petsData += pResult[(i + 1) * 23 + 1];//petorder
		petsData += "|";
		petsData += pResult[(i + 1) * 23 + 5];//exp
		petsData += "|";
		petsData += pResult[(i + 1) * 23 + 6];//hp
		petsData += "|";
		petsData += pResult[(i + 1) * 23 + 8];//atk
		petsData += "|";
		petsData += pResult[(i + 1) * 23 + 9];//def
		petsData += "|";
		petsData += pResult[(i + 1) * 23 + 7];//atki
		petsData += "|";
		petsData += pResult[(i + 1) * 23 + 10];//accuracy
		petsData += "|";
		petsData += pResult[(i + 1) * 23 + 11];//evasiveness
		petsData += "|";
		petsData += pResult[(i + 1) * 23 + 14];//gotskillcnt
		petsData += "|";
	}
	sqlite3_close(db);
	return petsData;
}

int GetPetsCnt()//得到宠物总数
{
	int nowPetsCnt;
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
	sql = "SELECT TOTALORDER FROM PET ORDER BY TOTALORDER DESC;";
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
	if (nRow == 0)
		nowPetsCnt = 0;
	else
		nowPetsCnt = atoi(pResult[1]);
	sqlite3_close(db);
	cout <<"当前系统送出精灵总数："<< nowPetsCnt+1 << endl;////////////
	//return nRow;
	return nowPetsCnt+1;
}


int main(int argc, char* argv[])
{
	srand((unsigned)time(NULL));

	//初始运行一次,创建一个表就注释掉(已创建，不需要重复创建）
	//CreatTable();
	//-------------------------------------------------
	petsCnt = GetPetsCnt();//获得当前系统分发出去的总数

	USER *playUsers[USERMAX];
	for (int i = 0; i < USERMAX; ++i)
	{
		playUsers[i] = nullptr;			//nullptr代表没有存用户，如果一个用户退出登录，delete再重置为nullptr
	}
	int userCnt = 0;
	USER  *newuser=new USER;//新建一个用户
	int currentUser;//当前正在处理的user

	POKEMON *virtualPets[VIRTUAL_PETS_NUM];//虚拟精灵列表
	for (int i = 0; i < VIRTUAL_PETS_NUM; ++i)
	{
		virtualPets[i] = nullptr;
	}

	//socket通信
	//初始化DLL
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsdata;
	if (WSAStartup(sockVersion, &wsdata) != 0)
	{
		return 1;
	}

	//创建套接字
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == INVALID_SOCKET)
	{
		cout << "Socket error" << endl;
		return 1;
	}


	//绑定套接字
	sockaddr_in sockAddr;
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = htons(9999);//设置端口号
	sockAddr.sin_addr.S_un.S_addr = INADDR_ANY;

	if (bind(serverSocket, (sockaddr*)&sockAddr, sizeof(sockAddr)) == SOCKET_ERROR) {
		cout << "Bind error" << endl;
		return 1;
	}

	//开始监听
	if (listen(serverSocket, 10) == SOCKET_ERROR) {
		cout << "Listen error" << endl;
		return 1;
	}

	SOCKET clientSocket;
	sockaddr_in client_sin;
	char msg[65535];//存储传送的消息
	int flag = 0;//是否已经连接上
	int len = sizeof(client_sin);
	while (true) {
		if (!flag)
			cout << "等待连接..." << endl;
		clientSocket = accept(serverSocket, (sockaddr*)&client_sin, &len);
		if (clientSocket == INVALID_SOCKET) {
			cout << "Accept error" << endl;
			flag = 0;
			return 1;
		}
		if (!flag)
			cout << "接收到一个连接：" << inet_ntoa(client_sin.sin_addr) << endl;
		flag = 1;
		int num = recv(clientSocket, msg, 65535, 0);
		//cout << num;
		if (num > 0)
		{
			msg[num] = '\0';
			cout << "Client say: " << msg << endl;

		}

		string dataSend;//准备恢复发送的消息
		//切割收到的消息
		char *nextToken = NULL;
		const char* split = "|";
		char * dataPart = strtok_s(msg, split, &nextToken);
		string thePart = dataPart;
		string username;
		string password;
		if (thePart == "login:")						//收到请求登录的消息
		{
			dataPart = strtok_s(NULL, split, &nextToken);
			thePart = dataPart;
			if (thePart == "username:")
			{
				dataPart = strtok_s(NULL, split, &nextToken);
				
				//处理用户名，查找数据库看用户是否存在
				username = dataPart;
				dataPart = strtok_s(NULL, split, &nextToken);
				thePart = dataPart;
				if (thePart == "password:")
				{
					dataPart = strtok_s(NULL, split, &nextToken);
					
					//处理密码
					password = dataPart;
					int searchResult = sqlite_find_user_exist(username, password);//0表示登录
					if (searchResult == 0)//用户不存在
					{
						dataSend = "login:|"+username+"|user_not_exist|";
					}
					else if (searchResult == 1)//用户存在且密码输入正确，登录，存到当前用户列表
					{
						dataSend = "login:|"+username+"|ok|";
						//在在线用户列表中找到一个没有存用户的，新建一个用户数据
						int i = 0;
						for (i = 0; i < USERMAX&&playUsers[i] != nullptr; ++i)
						{
						}
						currentUser = i;
						playUsers[currentUser] = new USER;
						//去数据库根据用户名寻找
						playUsers[currentUser]->Input_UserName(username);
						playUsers[currentUser]->FillInfo_from_Sqlite();
						playUsers[currentUser]->Input_Online(1);
						playUsers[currentUser]->UpdateUser();//为了更新登录状态
						++userCnt;//在线的用户数+1
					}
					else if (searchResult == 2)//用户存在但是密码输入错误
					{
						dataSend = "login:|"+username+"|pwd_error|";
					}
				}
			}

		}
		else if (thePart == "sign:")						//收到请求注册的消息
		{
			dataPart= strtok_s(NULL, split, &nextToken);
			thePart = dataPart;
			if (thePart == "username:")
			{
				dataPart = strtok_s(NULL, split, &nextToken);
				
				//处理用户名:查找数据库
				username = dataPart;
				dataPart = strtok_s(NULL, split, &nextToken);
				thePart = dataPart;
				if (thePart == "password:")
				{
					dataPart = strtok_s(NULL, split, &nextToken);
					
					//处理密码
					password = dataPart;
					int searchResult = sqlite_find_user_exist(username, password);//1表示是注册
					if (searchResult == 0)//用户不存在
					{
						dataSend = "sign:|"+username+"|ok|";
						//注册一个用户，插入到数据库
						USER  *newuser=new USER;					
						newuser->Input_UserName(username);
						newuser->Input_PassWord(password);
						cout << "petsCnt=" << petsCnt << endl;
						newuser->InitialPets(petsCnt);
						newuser->InsertUser();
						newuser->InsertPet();
						petsCnt = GetPetsCnt();
					}
					else if (searchResult == 1||searchResult==2)//用户已存在
					{
						dataSend = "sign:|"+username+"|user_exist|";
					}
				}
				else
				{
					cout << "收到信息有误，无法获取密码" << endl;
				}
			}
			else
			{
				cout << "收到信息有误，无法获取用户名" << endl;
			}
		}
		else if (thePart == "user_self_info:")
		{
			dataPart = strtok_s(NULL, split, &nextToken);
			username = dataPart;
			//已经登录的用户信息肯定能找到，不存在找不到的情况
			int i;
			for (i = 0; i < USERMAX && (playUsers[i]==nullptr||playUsers[i]->Get_UserName()!=username); ++i)
			{
			}
			if (i == USERMAX)
				cout << "用户" << username << "未登录！" << endl;
			else
			{
				currentUser = i;
				dataSend = "user_self_info:|";
				dataSend += playUsers[currentUser]->Get_UserName();
				dataSend += "|";
				dataSend += playUsers[currentUser]->Get_Nick();
				dataSend += "|";
				dataSend += to_string(playUsers[currentUser]->Get_FightTime());
				dataSend += "|";
				dataSend += to_string(playUsers[currentUser]->Get_WinTime());
				dataSend += "|";
				dataSend += to_string(playUsers[currentUser]->Get_WinRate());
				dataSend += "|";
				dataSend += to_string(playUsers[currentUser]->Get_PetNum());
				dataSend += "|";
				dataSend += to_string(playUsers[currentUser]->Get_AdvNum());
				dataSend += "|";
				for (int j = 0; j < playUsers[currentUser]->Get_PetNum(); ++j)
				{
					dataSend += playUsers[currentUser]->ReadPets(j)->Get_Name();
					dataSend += "|";
					dataSend += playUsers[currentUser]->ReadPets(j)->Get_Nick();
					dataSend += "|";
					POKEMONKIND theKind = playUsers[currentUser]->ReadPets(j)->Get_Kind();
					switch (theKind)
					{
					case POWER:
						dataSend += "力量型";
						break;
					case TANK:
						dataSend += "肉盾型";
						break;
					case DEFENSIVE:
						dataSend += "防御型";
						break;
					case AGILE:
						dataSend += "敏捷型";
						break;
					}
					dataSend += "|";
					dataSend += to_string(playUsers[currentUser]->ReadPets(j)->Get_Rank());
					dataSend += "|";
				}
			}
		}
		else if (thePart == "pet_info:")
		{
			dataPart = strtok_s(NULL, split, &nextToken);
			username = dataPart;
			int i;
			for (i = 0; i < USERMAX && (playUsers[i] == nullptr || playUsers[i]->Get_UserName() != username); ++i)
			{
			}
			if (i == USERMAX)
				cout << "用户" << username << "未登录！" << endl;
			else
			{
				currentUser = i;
				dataPart = strtok_s(NULL, split, &nextToken);
				int thePet = atoi(dataPart);
				dataSend = "pet_info:|" + username + "|";
				dataSend += playUsers[currentUser]->ReadPets(thePet)->Get_Name();
				dataSend += "|";
				dataSend += playUsers[currentUser]->ReadPets(thePet)->Get_Nick();
				dataSend += "|";
				POKEMONKIND pkind = playUsers[currentUser]->ReadPets(thePet)->Get_Kind();
				switch (pkind)
				{
				case POWER:
					dataSend += "力量型";
					break;
				case TANK:
					dataSend += "肉盾型";
					break;
				case DEFENSIVE:
					dataSend += "防御型";
					break;
				case AGILE:
					dataSend += "敏捷型";
					break;
				}
				dataSend += "|";
				WUXINGTYPE thetype = playUsers[currentUser]->ReadPets(thePet)->Get_Type();
				switch (thetype)
				{
				case JIN:
					dataSend += "金";
					break;
				case MU:
					dataSend += "木";
					break;
				case SHUI:
					dataSend += "水";
					break;
				case HUO:
					dataSend += "火";
					break;
				case TU:
					dataSend += "土";
					break;
				}
				dataSend += "|";
				dataSend += to_string(playUsers[currentUser]->ReadPets(thePet)->Get_Rank());
				dataSend += "|";
				dataSend += to_string(playUsers[currentUser]->ReadPets(thePet)->Get_Order());
				dataSend += "|";
				dataSend += to_string(playUsers[currentUser]->ReadPets(thePet)->Get_Exp());
				dataSend += "|";
				dataSend += to_string(playUsers[currentUser]->ReadPets(thePet)->Get_Hp());
				dataSend += "|";
				dataSend += to_string(playUsers[currentUser]->ReadPets(thePet)->Get_Atk());
				dataSend += "|";
				dataSend += to_string(playUsers[currentUser]->ReadPets(thePet)->Get_Def());
				dataSend += "|";
				dataSend += to_string(playUsers[currentUser]->ReadPets(thePet)->Get_AtkI());
				dataSend += "|";
				dataSend += to_string(playUsers[currentUser]->ReadPets(thePet)->Get_Accuracy());
				dataSend += "|";
				dataSend += to_string(playUsers[currentUser]->ReadPets(thePet)->Get_Evasiveness());
				dataSend += "|";
				dataSend += to_string(playUsers[currentUser]->ReadPets(thePet)->Get_GotSkillCnt());
				dataSend += "|";
				for (int j = 0; j < playUsers[currentUser]->ReadPets(thePet)->Get_GotSkillCnt(); ++j)
				{
					dataSend += playUsers[currentUser]->ReadPets(thePet)->Access_GotSkill(j)->SkillName;
					dataSend += "|";
					SKILLKIND theskillKind= playUsers[currentUser]->ReadPets(thePet)->Access_GotSkill(j)->SkillKind;
					switch (theskillKind)
					{
					case ATTACK:
						dataSend += "攻击技能";
						break;
					case REHP:
						dataSend += "回血技能";
						break;
					case OPPDEFEENCE:
						dataSend += "减弱对方防御力";
						break;
					case SELFATTACK:
						dataSend += "增强自身攻击力";
						break;
					case SELFDEFFENCE:
						dataSend += "增强自身防御力";
						break;
					}
					dataSend += "|";
					dataSend += to_string(playUsers[currentUser]->ReadPets(thePet)->Access_GotSkill(j)->SkillPower);
					dataSend += "|";
					dataSend += to_string(playUsers[currentUser]->ReadPets(thePet)->Access_GotSkill(j)->SkillHit);
					dataSend += "|";
					dataSend += to_string(playUsers[currentUser]->ReadPets(thePet)->Access_GotSkill(j)->SkillRank);
					dataSend += "|";
				}
			}
		}
		else if (thePart == "alluser_info:")
		{
			dataPart = strtok_s(NULL, split, &nextToken);
			username = dataPart;
			dataSend = "alluser_info:|" + username + "|";
			dataSend += Get_AllUserInfo();
		}
		else if (thePart == "access_auser_pet_info:")
		{
			dataPart = strtok_s(NULL, split, &nextToken);
			username = dataPart;
			dataSend = "access_auser_pet_info:|" + username + "|";
			dataPart = strtok_s(NULL, split, &nextToken);
			string theUser = dataPart;
			dataSend += Get_a_User_Info(theUser);
		}
		else if (thePart == "quit_info:")
		{
			dataPart = strtok_s(NULL, split, &nextToken);
			username = dataPart;
			int i;
			for (i = 0; i < USERMAX && (playUsers[i] == nullptr || playUsers[i]->Get_UserName() != username); ++i)
			{
			}
			if (i == USERMAX)
				cout << "用户" << username << "未登录！" << endl;
			else
			{
				currentUser = i;
				dataSend += "quit_info:|" + username + "|ok|";
				cout << "password1=" << playUsers[currentUser]->Get_PassWord() << endl;////
				playUsers[currentUser]->Input_Online(0);
				playUsers[currentUser]->UpdateUser();
				playUsers[currentUser]->UpdatePet();
				delete playUsers[currentUser];
				playUsers[currentUser] = nullptr;
				--userCnt;//登录的用户数-1
			}
		}
		else if (thePart == "mypets_info:")
		{
			dataPart = strtok_s(NULL, split, &nextToken);
			username = dataPart;
			int i;
			for (i = 0; i < USERMAX && (playUsers[i] == nullptr || playUsers[i]->Get_UserName() != username); ++i)
			{
			}
			if (i == USERMAX)
				cout << "用户" << username << "未登录！" << endl;
			else
			{
				currentUser = i;
				dataSend += "mypets_info:|" + username + "|";
				dataSend += to_string(playUsers[currentUser]->Get_PetNum());
				dataSend += "|";
				for (int j = 0; j < playUsers[currentUser]->Get_PetNum(); ++j)///////////////////
				{
					dataSend += playUsers[currentUser]->ReadPets(j)->Get_Name();
					dataSend += "|";
					dataSend += playUsers[currentUser]->ReadPets(j)->Get_Nick();
					dataSend += "|";
					POKEMONKIND pkind = playUsers[currentUser]->ReadPets(j)->Get_Kind();
					switch (pkind)
					{
					case POWER:
						dataSend += "力量型";
						break;
					case TANK:
						dataSend += "肉盾型";
						break;
					case DEFENSIVE:
						dataSend += "防御型";
						break;
					case AGILE:
						dataSend += "敏捷型";
						break;
					}
					dataSend += "|";
					WUXINGTYPE thetype = playUsers[currentUser]->ReadPets(j)->Get_Type();
					switch (thetype)
					{
					case JIN:
						dataSend += "金";
						break;
					case MU:
						dataSend += "木";
						break;
					case SHUI:
						dataSend += "水";
						break;
					case HUO:
						dataSend += "火";
						break;
					case TU:
						dataSend += "土";
						break;
					}
					dataSend += "|";
					dataSend += to_string(playUsers[currentUser]->ReadPets(j)->Get_Rank());
					dataSend += "|";
					dataSend += to_string(playUsers[currentUser]->ReadPets(j)->Get_Order());
					dataSend += "|";
					dataSend += to_string(playUsers[currentUser]->ReadPets(j)->Get_Exp());
					dataSend += "|";
					dataSend += to_string(playUsers[currentUser]->ReadPets(j)->Get_Hp());
					dataSend += "|";
					dataSend += to_string(playUsers[currentUser]->ReadPets(j)->Get_Atk());
					dataSend += "|";
					dataSend += to_string(playUsers[currentUser]->ReadPets(j)->Get_Def());
					dataSend += "|";
					dataSend += to_string(playUsers[currentUser]->ReadPets(j)->Get_AtkI());
					dataSend += "|";
					dataSend += to_string(playUsers[currentUser]->ReadPets(j)->Get_Accuracy());
					dataSend += "|";
					dataSend += to_string(playUsers[currentUser]->ReadPets(j)->Get_Evasiveness());
					dataSend += "|";
					dataSend += to_string(playUsers[currentUser]->ReadPets(j)->Get_GotSkillCnt());
					dataSend += "|";
				}
			}
		}
		else if (thePart == "virtualpets_info:")////
		{
			dataPart = strtok_s(NULL, split, &nextToken);
			username = dataPart;
			//随机虚拟精灵表
			cout << "初始化虚拟精灵表" << endl;
			for (int i = 0; i < VIRTUAL_PETS_NUM; ++i)
			{
				if (virtualPets[i] != nullptr)
				{
					delete virtualPets[i];
					virtualPets[i] = nullptr;
				}					
				int randomName = rand() % 8;
				switch (randomName)
				{
				case 0:
					virtualPets[i] = new GYARADOS;
					break;
				case 1:
					virtualPets[i] = new HAPPINY;
					break;
				case 2:
					virtualPets[i] = new SQUIRTLE;
					break;
				case 3:
					virtualPets[i] = new MEWTWO;
					break;
				case 4:
					virtualPets[i] = new INCINEROAR;
					break;
				case 5:
					virtualPets[i] = new WOBBUFFET;
					break;
				case 6:
					virtualPets[i] = new STEELIX;
					break;
				case 7:
					virtualPets[i] = new ALAKAZAM;
				default:
					break;
				}
				int randomExp = rand() % 2600;
				virtualPets[i]->Input_Exp(randomExp);
				virtualPets[i]->RefershRank();
				int currentRank = virtualPets[i]->Get_Rank();
				double currentHP = virtualPets[i]->Get_Hp();
				int currentAtk = virtualPets[i]->Get_Atk();
				int currentDef = virtualPets[i]->Get_Def();
				int currentAtkI = virtualPets[i]->Get_AtkI();
				for (int j = 1; j < currentRank; ++j)
				{
					currentHP += rand() % 5 + 1;
					currentAtk += rand() % 5 + 1;
					currentDef += rand() % 5 + 1;
					currentAtkI -= rand() % 3 + 1;
					if (currentAtkI <= 10)
					{
						currentAtkI = 10;
					}
					//有几率获得技能
					int randomSkill = rand() % 10;//跳过第一个技能
					if (randomSkill >= 5 && virtualPets[i]->Get_GotSkillCnt() < virtualPets[i]->Get_ALLSkillCnt())
					{
						randomSkill = rand() % (virtualPets[i]->Get_ALLSkillCnt() - 1) + 1;//跳过第一个技能
						PSKILL nextSkill = virtualPets[i]->Write_AllSkill() + randomSkill;
						while (nextSkill->Selected == OWNED)
						{
							randomSkill = rand() % (virtualPets[i]->Get_ALLSkillCnt() - 1) + 1;//跳过第一个技能
							nextSkill = virtualPets[i]->Write_AllSkill() + randomSkill;
						}
						int currentSkillCnt = virtualPets[i]->Get_GotSkillCnt();
						PSKILL* newSkill = virtualPets[i]->Write_GotSkill(currentSkillCnt);
						*newSkill = nextSkill;
						(*newSkill)->Selected = OWNED;
						++currentSkillCnt;
						virtualPets[i]->Input_GotSkillCnt(currentSkillCnt);
					}
				}
				virtualPets[i]->Input_Hp(currentHP);
				virtualPets[i]->Input_Atk(currentAtk);
				virtualPets[i]->Input_AtkI(currentAtkI);
				virtualPets[i]->Input_Def(currentDef);
			}

			dataSend += "virtualpets_info:|" + username + "|";
			dataSend += to_string(VIRTUAL_PETS_NUM);
			dataSend += "|";
			for (int j = 0; j < VIRTUAL_PETS_NUM; ++j)
			{
				dataSend += virtualPets[j]->Get_Name();
				dataSend += "|";
				dataSend += virtualPets[j]->Get_Nick();
				dataSend += "|";
				POKEMONKIND pkind = virtualPets[j]->Get_Kind();
				switch (pkind)
				{
				case POWER:
					dataSend += "力量型";
					break;
				case TANK:
					dataSend += "肉盾型";
					break;
				case DEFENSIVE:
					dataSend += "防御型";
					break;
				case AGILE:
					dataSend += "敏捷型";
					break;
				}
				dataSend += "|";
				WUXINGTYPE thetype = virtualPets[j]->Get_Type();
				switch (thetype)
				{
				case JIN:
					dataSend += "金";
					break;
				case MU:
					dataSend += "木";
					break;
				case SHUI:
					dataSend += "水";
					break;
				case HUO:
					dataSend += "火";
					break;
				case TU:
					dataSend += "土";
					break;
				}
				dataSend += "|";
				dataSend += to_string(virtualPets[j]->Get_Rank());
				dataSend += "|";
				dataSend += to_string(virtualPets[j]->Get_Order());
				dataSend += "|";
				dataSend += to_string(virtualPets[j]->Get_Exp());
				dataSend += "|";
				dataSend += to_string(virtualPets[j]->Get_Hp());
				dataSend += "|";
				dataSend += to_string(virtualPets[j]->Get_Atk());
				dataSend += "|";
				dataSend += to_string(virtualPets[j]->Get_Def());
				dataSend += "|";
				dataSend += to_string(virtualPets[j]->Get_AtkI());
				dataSend += "|";
				dataSend += to_string(virtualPets[j]->Get_Accuracy());
				dataSend += "|";
				dataSend += to_string(virtualPets[j]->Get_Evasiveness());
				dataSend += "|";
				dataSend += to_string(virtualPets[j]->Get_GotSkillCnt());
				dataSend += "|";
			}
		}
		else if (thePart == "FighterA_info:")
		{
			dataPart = strtok_s(NULL, split, &nextToken);
			username = dataPart;
			dataPart = strtok_s(NULL, split, &nextToken);
			int thePetOrder = atoi(dataPart);
			int i;
			for (i = 0; i < USERMAX && (playUsers[i] == nullptr || playUsers[i]->Get_UserName() != username); ++i)
			{
			}
			if (i == USERMAX)
				cout << "用户" << username << "未登录！" << endl;
			else
			{
				currentUser = i;
				dataSend += "FighterA_info:|" + username + "|";
				dataSend += playUsers[currentUser]->ReadPets(thePetOrder)->Get_Name();
				dataSend += "|";
				dataSend += to_string(playUsers[currentUser]->ReadPets(thePetOrder)->Get_Hp());
				dataSend += "|";
				dataSend += to_string(playUsers[currentUser]->ReadPets(thePetOrder)->Get_Atk());
				dataSend += "|";
				dataSend += to_string(playUsers[currentUser]->ReadPets(thePetOrder)->Get_Def());
				dataSend += "|";
				dataSend += to_string(playUsers[currentUser]->ReadPets(thePetOrder)->Get_AtkI());
				dataSend += "|";
				dataSend += to_string(playUsers[currentUser]->ReadPets(thePetOrder)->Get_Accuracy());
				dataSend += "|";
				dataSend += to_string(playUsers[currentUser]->ReadPets(thePetOrder)->Get_Evasiveness());
				dataSend += "|";
				dataSend += to_string(playUsers[currentUser]->ReadPets(thePetOrder)->Get_Rank());
				dataSend += "|";
				POKEMONKIND pkind = playUsers[currentUser]->ReadPets(thePetOrder)->Get_Kind();
				switch (pkind)
				{
				case POWER:
					dataSend += "力量型";
					break;
				case TANK:
					dataSend += "肉盾型";
					break;
				case DEFENSIVE:
					dataSend += "防御型";
					break;
				case AGILE:
					dataSend += "敏捷型";
					break;
				}
				dataSend += "|";
				WUXINGTYPE thetype = playUsers[currentUser]->ReadPets(thePetOrder)->Get_Type();
				switch (thetype)
				{
				case JIN:
					dataSend += "金";
					break;
				case MU:
					dataSend += "木";
					break;
				case SHUI:
					dataSend += "水";
					break;
				case HUO:
					dataSend += "火";
					break;
				case TU:
					dataSend += "土";
					break;
				}
				dataSend += "|";
				dataSend += playUsers[currentUser]->ReadPets(thePetOrder)->Get_Nick();
				dataSend += "|";
				dataSend += to_string(playUsers[currentUser]->ReadPets(thePetOrder)->Get_Order());
				dataSend += "|";
				dataSend += to_string(playUsers[currentUser]->ReadPets(thePetOrder)->Get_Exp());
				dataSend += "|";				
				dataSend += to_string(playUsers[currentUser]->ReadPets(thePetOrder)->Get_GotSkillCnt());
				dataSend += "|";
				for (int i = 0; i < playUsers[currentUser]->ReadPets(thePetOrder)->Get_GotSkillCnt(); ++i)
				{
					dataSend += playUsers[currentUser]->ReadPets(thePetOrder)->Access_GotSkill(i)->SkillName;
					dataSend += "|";
					dataSend += to_string(playUsers[currentUser]->ReadPets(thePetOrder)->Access_GotSkill(i)->SkillKind);
					dataSend += "|";
					dataSend += to_string(playUsers[currentUser]->ReadPets(thePetOrder)->Access_GotSkill(i)->SkillPower);
					dataSend += "|";
					dataSend += to_string(playUsers[currentUser]->ReadPets(thePetOrder)->Access_GotSkill(i)->SkillHit);
					dataSend += "|";
					dataSend += to_string(playUsers[currentUser]->ReadPets(thePetOrder)->Access_GotSkill(i)->SkillRank);
					dataSend += "|";
				}
			}
		}
		else if (thePart == "FighterB_info:")
		{
			dataPart = strtok_s(NULL, split, &nextToken);
			username = dataPart;
			dataPart = strtok_s(NULL, split, &nextToken);
			int thePetOrder = atoi(dataPart);
			dataSend += "FighterB_info:|" + username + "|";
			dataSend += virtualPets[thePetOrder]->Get_Name();
			dataSend += "|";
			dataSend += to_string(virtualPets[thePetOrder]->Get_Hp());
			dataSend += "|";
			dataSend += to_string(virtualPets[thePetOrder]->Get_Atk());
			dataSend += "|";
			dataSend += to_string(virtualPets[thePetOrder]->Get_Def());
			dataSend += "|";
			dataSend += to_string(virtualPets[thePetOrder]->Get_AtkI());
			dataSend += "|";
			dataSend += to_string(virtualPets[thePetOrder]->Get_Accuracy());
			dataSend += "|";
			dataSend += to_string(virtualPets[thePetOrder]->Get_Evasiveness());
			dataSend += "|";
			dataSend += to_string(virtualPets[thePetOrder]->Get_Rank());
			dataSend += "|";
			POKEMONKIND pkind = virtualPets[thePetOrder]->Get_Kind();
			switch (pkind)
			{
			case POWER:
				dataSend += "力量型";
				break;
			case TANK:
				dataSend += "肉盾型";
				break;
			case DEFENSIVE:
				dataSend += "防御型";
				break;
			case AGILE:
				dataSend += "敏捷型";
				break;
			}
			dataSend += "|";
			WUXINGTYPE thetype = virtualPets[thePetOrder]->Get_Type();
			switch (thetype)
			{
			case JIN:
				dataSend += "金";
				break;
			case MU:
				dataSend += "木";
				break;
			case SHUI:
				dataSend += "水";
				break;
			case HUO:
				dataSend += "火";
				break;
			case TU:
				dataSend += "土";
				break;
			}
			dataSend += "|";
			dataSend += virtualPets[thePetOrder]->Get_Nick();
			dataSend += "|";
			dataSend += to_string(virtualPets[thePetOrder]->Get_Order());
			dataSend += "|";
			dataSend += to_string(virtualPets[thePetOrder]->Get_Exp());
			dataSend += "|";
			dataSend += to_string(virtualPets[thePetOrder]->Get_GotSkillCnt());
			dataSend += "|";
			for (int i = 0; i < virtualPets[thePetOrder]->Get_GotSkillCnt(); ++i)
			{
				dataSend += virtualPets[thePetOrder]->Access_GotSkill(i)->SkillName;
				dataSend += "|";
				dataSend += to_string(virtualPets[thePetOrder]->Access_GotSkill(i)->SkillKind);
				dataSend += "|";
				dataSend += to_string(virtualPets[thePetOrder]->Access_GotSkill(i)->SkillPower);
				dataSend += "|";
				dataSend += to_string(virtualPets[thePetOrder]->Access_GotSkill(i)->SkillHit);
				dataSend += "|";
				dataSend += to_string(virtualPets[thePetOrder]->Access_GotSkill(i)->SkillRank);
				dataSend += "|";
			}
		}
		else if (thePart == "UPFight_info:")
		{
			dataPart = strtok_s(NULL, split, &nextToken);
			username = dataPart;
			dataPart = strtok_s(NULL, split, &nextToken);
			int fightMode = atoi(dataPart);//战斗模式，0为升级赛，1为决斗赛
			dataPart = strtok_s(NULL, split, &nextToken);
			int thePetOrder = atoi(dataPart);//出战精灵在当前用户表中的序号
			dataPart = strtok_s(NULL, split, &nextToken);
			int virtualPetOrder = atoi(dataPart);//应战精灵在虚拟精灵表中的序号
			dataPart = strtok_s(NULL, split, &nextToken);
			int theEXP = atoi(dataPart);
			dataPart = strtok_s(NULL, split, &nextToken);
			int win;
			thePart = dataPart;
			if (thePart == "win")
				win = 1;
			else if (thePart == "lose")
				win = 0;
			cout << thePart << endl;//////////////////
			int i;
			for (i = 0; i < USERMAX && (playUsers[i] == nullptr || playUsers[i]->Get_UserName() != username); ++i)
			{
			}
			if (i == USERMAX)
				cout << "用户" << username << "未登录！" << endl;
			else
			{
				currentUser = i;
				int oldRank= playUsers[currentUser]->ReadPets(thePetOrder)->Get_Rank();
				playUsers[currentUser]->WritePets(thePetOrder)->Input_Exp(theEXP);
				playUsers[currentUser]->WritePets(thePetOrder)->RefershRank();
				int nowWintime = playUsers[currentUser]->Get_WinTime();
				nowWintime += win;
				playUsers[currentUser]->Input_WinTime(nowWintime);
				int nowFightTime = playUsers[currentUser]->Get_FightTime();
				++nowFightTime;
				playUsers[currentUser]->Input_FightTime(nowFightTime);
				dataSend += "UPFight_info:|" + username + "|";
				dataSend += to_string(playUsers[currentUser]->ReadPets(thePetOrder)->Get_Rank());
				dataSend += "|";
				string upgrade_info;
				if (oldRank < playUsers[currentUser]->ReadPets(thePetOrder)->Get_Rank())//升级
				{
					upgrade_info = playUsers[currentUser]->WritePets(thePetOrder)->Upgrade();
				}
				else
					upgrade_info = "加油，离升级只有一步之遥了！|";
				dataSend += to_string(playUsers[currentUser]->ReadPets(thePetOrder)->Get_Hp());
				dataSend += "|";
				dataSend += to_string(playUsers[currentUser]->ReadPets(thePetOrder)->Get_Atk());
				dataSend += "|";
				dataSend += to_string(playUsers[currentUser]->ReadPets(thePetOrder)->Get_Def());
				dataSend += "|";
				dataSend += to_string(playUsers[currentUser]->ReadPets(thePetOrder)->Get_AtkI());
				dataSend += "|";
				dataSend += to_string(playUsers[currentUser]->ReadPets(thePetOrder)->Get_GotSkillCnt());
				dataSend += "|";
				dataSend += playUsers[currentUser]->ReadPets(thePetOrder)->Get_Name();
				dataSend += "|";
				dataSend += upgrade_info;

				if (fightMode == 1)//决斗赛
				{
					if (win == 0)//失败，送出精灵
					{
						int givePetsNum = 3;
						if (playUsers[currentUser]->Get_PetNum() < givePetsNum)
						{
							givePetsNum = playUsers[currentUser]->Get_PetNum();
						}
						int petChoose[3];//三只让用户挑选的精灵在用户精灵表中的序号
						for (int j = 0; j < givePetsNum; ++j)
						{
							petChoose[j] = rand() % (playUsers[currentUser]->Get_PetNum());
							int k;
							int flag = 0;
							while (flag == 0)
							{
								for (k = 0; k < j && petChoose[k] != petChoose[j]; ++k)
								{

								}
								if (k < j)//重复，重新随机一只
								{
									petChoose[j] = rand() % (playUsers[currentUser]->Get_PetNum());
								}
								else
									flag = 1;//退出循环
							}							
						}
						dataSend += to_string(givePetsNum);//待选择被送出精灵数
						dataSend += "|";
						for (int j = 0; j < givePetsNum; ++j)
						{
							dataSend += to_string(petChoose[j]);//该待选择被送出精灵在用户精灵表中的序号
							dataSend += "|";
							dataSend += to_string(playUsers[currentUser]->ReadPets(petChoose[j])->Get_Order());//用于获得是哪种具体的精灵，用于确定图片
							dataSend += "|";
							dataSend += playUsers[currentUser]->ReadPets(petChoose[j])->Get_Name();
							dataSend += "|";
							dataSend += to_string(playUsers[currentUser]->ReadPets(petChoose[j])->Get_Rank());
							dataSend += "|";
						}
					}
					else//赢得该战胜的精灵（虚拟列表中）
					{
						int currentPetsCnt = playUsers[currentUser]->Get_PetNum();
						POKEMON *thePetPtr=playUsers[currentUser]->WritePets(currentPetsCnt);
						(*thePetPtr) = *virtualPets[virtualPetOrder];
						++currentPetsCnt;
						playUsers[currentUser]->Input_PetNum(currentPetsCnt);
						thePetPtr->Input_totalOrder(petsCnt);
						++petsCnt;
						//直接在客户端输出获得精灵即可
					}
				}
			}
		}
		else if (thePart == "deletepet_info:")
		{
			dataPart = strtok_s(NULL, split, &nextToken);
			username = dataPart;
			dataPart = strtok_s(NULL, split, &nextToken);
			int thePetOrder = atoi(dataPart);
			int i;
			for (i = 0; i < USERMAX && (playUsers[i] == nullptr || playUsers[i]->Get_UserName() != username); ++i)
			{
			}
			if (i == USERMAX)
				cout << "用户" << username << "未登录！" << endl;
			else
			{
				currentUser = i;
				delete playUsers[currentUser]->WritePets(thePetOrder);
				int currentPetNum = playUsers[currentUser]->Get_PetNum();
				for (int i = thePetOrder; i < currentPetNum-1; ++i)//抛弃的宠物之后的精灵前移
				{
					POKEMON *thePetPtr = playUsers[currentUser]->WritePets(i);
					POKEMON *nextPtr = playUsers[currentUser]->WritePets(i + 1);
					thePetPtr = nextPtr;
				}
				--currentPetNum;
				playUsers[currentUser]->Input_PetNum(currentPetNum);
				if (currentPetNum == 0)//用户没有精灵了，随机发放一只初始精灵
				{
					POKEMON *thePetPtr = playUsers[currentUser]->WritePets(currentPetNum);
					int random = rand() % 8;
					switch (random)
					{
					case 0:
						thePetPtr = new GYARADOS;
						break;
					case 1:
						thePetPtr = new HAPPINY;
						break;
					case 2:
						thePetPtr = new SQUIRTLE;
						break;
					case 3:
						thePetPtr = new MEWTWO;
						break;
					case 4:
						thePetPtr = new INCINEROAR;
						break;
					case 5:
						thePetPtr = new WOBBUFFET;
						break;
					case 6:
						thePetPtr = new STEELIX;
						break;
					case 7:
						thePetPtr = new ALAKAZAM;
					default:
						break;
					}
					thePetPtr->Input_totalOrder(petsCnt);
					++petsCnt;
					playUsers[currentUser]->Input_PetNum(1);
				}
				dataSend += "deletepet_info:|" + username + "|" + "ok|";
			}
		}

		//string dataSend;
		//getline(cin, dataSend);
		cout << "dataSend = " << dataSend << endl;//测试输出
		const char * sendData;
		sendData = dataSend.c_str();
		send(clientSocket, sendData, strlen(sendData), 0);//发送，在最后加上空格，$等终止符，防止读到后面的乱码
		closesocket(clientSocket);
	}

	closesocket(serverSocket);
	WSACleanup();

	system("pause");
	return 0;
}