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
		"AKTI		INT		NOT NULL," \
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

int main(int argc, char* argv[])
{
	//��ʼ����һ��,����һ�����ע�͵�(�Ѵ���������Ҫ�ظ�������
	//CreatTable();
	//-------------------------------------------------
	//USER auser;
	//auser.InitialPets();
	//auser.InsertUser();
	//USER buser;
	//buser.FillInfo_from_Sqlite();

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
	char msg[100];//�洢���͵���Ϣ
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
		if (num > 0)
		{
			msg[num] = '\0';
			cout << "Client say: " << msg << endl;

		}

		string data;
		getline(cin, data);
		const char * sendData;
		sendData = data.c_str();
		send(clientSocket, sendData, strlen(sendData), 0);//���ͣ��������Ͽո�$����ֹ������ֹ�������������
		closesocket(clientSocket);
	}

	closesocket(serverSocket);
	WSACleanup();

	system("pause");
	return 0;
}