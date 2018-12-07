#include"pokemon.h"
#include"user.h"
#include"fight.h"
#include"sqlite3.h"
//#include<winsock2.h>
#pragma comment(lib, "ws2_32.lib")

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
		"WINTIME		INT		NOT NULL);";

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

//根据用户名查找用户是否存在		//返回值0：不存在；1：存在且密码输入正确；2：存在但密码输入错误
int sqlite_find_user_exist(string username,string password)
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
		return 0;					//用户不存在
	}		
	else
	{
		if (password == pResult[7])//数据库是一直加，一行6个，第二行第2个，从0开始计，所以是7
		{
			cout << "Correct username and password." << endl;
			return 1;				//用户存在，且密码输入正确
		}
		else
		{
			//cout << pResult[7] << endl;
			cout << "Wrong password!" << endl;
			return 2;				//用户存在，但是密码输入错误
		}
	}
}

int main(int argc, char* argv[])
{
	srand((unsigned)time(NULL));

	//初始运行一次,创建一个表就注释掉(已创建，不需要重复创建）
	//CreatTable();
	//-------------------------------------------------
	//USER auser;
	//auser.InitialPets();
	//auser.InsertUser();
	//auser.InsertPet();
	//USER buser;
	//buser.FillInfo_from_Sqlite();

	USER  *newuser=new USER;//新建一个用户

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
					int searchResult = sqlite_find_user_exist(username, password);
					if (searchResult == 0)//用户不存在
					{
						dataSend = "login:|user_not_exist|";
					}
					else if (searchResult == 1)//用户存在且密码输入正确
					{
						dataSend = "login:|ok|";
					}
					else if (searchResult == 2)//用户存在但是密码输入错误
					{
						dataSend = "login:|pwd_error|";
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
					int searchResult = sqlite_find_user_exist(username, password);
					if (searchResult == 0)//用户不存在
					{
						dataSend = "sign:|ok|";
						//注册一个用户，插入到数据库
						//USER  newuser;
						newuser->Input_UserName(username);
						newuser->Input_PassWord(password);
						newuser->InitialPets();
						newuser->InsertUser();
						newuser->InsertPet();
					}
					else if (searchResult == 1||searchResult==2)//用户已存在
					{
						dataSend = "sign:|user_exist|";
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

		//string dataSend;
		//getline(cin, dataSend);
		cout << "dataSend = " << dataSend;//测试输出
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