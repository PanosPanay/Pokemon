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

//�������ݿⲢ�����û��ͳ���2����
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

	//�����û���
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

	//���������
	/* Create SQL statement */
	//USERNAME�������û�����PETORDER�Ǿ��徫�����Ӧ�����
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

//�����û��������û��Ƿ����		//����ֵ0�������ڣ�1������������������ȷ��2�����ڵ������������
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

	//ȡ���û���Ϣ
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
		return 0;					//�û�������
	}		
	else
	{
		if (password == pResult[7])//���ݿ���һֱ�ӣ�һ��6�����ڶ��е�2������0��ʼ�ƣ�������7
		{
			cout << "Correct username and password." << endl;
			return 1;				//�û����ڣ�������������ȷ
		}
		else
		{
			//cout << pResult[7] << endl;
			cout << "Wrong password!" << endl;
			return 2;				//�û����ڣ����������������
		}
	}
}

int main(int argc, char* argv[])
{
	srand((unsigned)time(NULL));

	//��ʼ����һ��,����һ�����ע�͵�(�Ѵ���������Ҫ�ظ�������
	//CreatTable();
	//-------------------------------------------------
	//USER auser;
	//auser.InitialPets();
	//auser.InsertUser();
	//auser.InsertPet();
	//USER buser;
	//buser.FillInfo_from_Sqlite();

	USER  *newuser=new USER;//�½�һ���û�

	//socketͨ��
	//��ʼ��DLL
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsdata;
	if (WSAStartup(sockVersion, &wsdata) != 0)
	{
		return 1;
	}

	//�����׽���
	SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (serverSocket == INVALID_SOCKET)
	{
		cout << "Socket error" << endl;
		return 1;
	}


	//���׽���
	sockaddr_in sockAddr;
	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = htons(9999);//���ö˿ں�
	sockAddr.sin_addr.S_un.S_addr = INADDR_ANY;

	if (bind(serverSocket, (sockaddr*)&sockAddr, sizeof(sockAddr)) == SOCKET_ERROR) {
		cout << "Bind error" << endl;
		return 1;
	}

	//��ʼ����
	if (listen(serverSocket, 10) == SOCKET_ERROR) {
		cout << "Listen error" << endl;
		return 1;
	}

	SOCKET clientSocket;
	sockaddr_in client_sin;
	char msg[65535];//�洢���͵���Ϣ
	int flag = 0;//�Ƿ��Ѿ�������
	int len = sizeof(client_sin);
	while (true) {
		if (!flag)
			cout << "�ȴ�����..." << endl;
		clientSocket = accept(serverSocket, (sockaddr*)&client_sin, &len);
		if (clientSocket == INVALID_SOCKET) {
			cout << "Accept error" << endl;
			flag = 0;
			return 1;
		}
		if (!flag)
			cout << "���յ�һ�����ӣ�" << inet_ntoa(client_sin.sin_addr) << endl;
		flag = 1;
		int num = recv(clientSocket, msg, 65535, 0);
		//cout << num;
		if (num > 0)
		{
			msg[num] = '\0';
			cout << "Client say: " << msg << endl;

		}

		string dataSend;//׼���ָ����͵���Ϣ
		//�и��յ�����Ϣ
		char *nextToken = NULL;
		const char* split = "|";
		char * dataPart = strtok_s(msg, split, &nextToken);
		string thePart = dataPart;
		string username;
		string password;
		if (thePart == "login:")						//�յ������¼����Ϣ
		{
			dataPart = strtok_s(NULL, split, &nextToken);
			thePart = dataPart;
			if (thePart == "username:")
			{
				dataPart = strtok_s(NULL, split, &nextToken);
				
				//�����û������������ݿ⿴�û��Ƿ����
				username = dataPart;
				dataPart = strtok_s(NULL, split, &nextToken);
				thePart = dataPart;
				if (thePart == "password:")
				{
					dataPart = strtok_s(NULL, split, &nextToken);
					
					//��������
					password = dataPart;
					int searchResult = sqlite_find_user_exist(username, password);
					if (searchResult == 0)//�û�������
					{
						dataSend = "login:|user_not_exist|";
					}
					else if (searchResult == 1)//�û�����������������ȷ
					{
						dataSend = "login:|ok|";
					}
					else if (searchResult == 2)//�û����ڵ��������������
					{
						dataSend = "login:|pwd_error|";
					}
				}
			}

		}
		else if (thePart == "sign:")						//�յ�����ע�����Ϣ
		{
			dataPart= strtok_s(NULL, split, &nextToken);
			thePart = dataPart;
			if (thePart == "username:")
			{
				dataPart = strtok_s(NULL, split, &nextToken);
				
				//�����û���:�������ݿ�
				username = dataPart;
				dataPart = strtok_s(NULL, split, &nextToken);
				thePart = dataPart;
				if (thePart == "password:")
				{
					dataPart = strtok_s(NULL, split, &nextToken);
					
					//��������
					password = dataPart;
					int searchResult = sqlite_find_user_exist(username, password);
					if (searchResult == 0)//�û�������
					{
						dataSend = "sign:|ok|";
						//ע��һ���û������뵽���ݿ�
						//USER  newuser;
						newuser->Input_UserName(username);
						newuser->Input_PassWord(password);
						newuser->InitialPets();
						newuser->InsertUser();
						newuser->InsertPet();
					}
					else if (searchResult == 1||searchResult==2)//�û��Ѵ���
					{
						dataSend = "sign:|user_exist|";
					}
				}
				else
				{
					cout << "�յ���Ϣ�����޷���ȡ����" << endl;
				}
			}
			else
			{
				cout << "�յ���Ϣ�����޷���ȡ�û���" << endl;
			}
		}

		//string dataSend;
		//getline(cin, dataSend);
		cout << "dataSend = " << dataSend;//�������
		const char * sendData;
		sendData = dataSend.c_str();
		send(clientSocket, sendData, strlen(sendData), 0);//���ͣ��������Ͽո�$����ֹ������ֹ�������������
		closesocket(clientSocket);
	}

	closesocket(serverSocket);
	WSACleanup();

	system("pause");
	return 0;
}