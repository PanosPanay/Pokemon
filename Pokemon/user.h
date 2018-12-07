#pragma once
#include "pokemon.h"
#include "fight.h"
#include "string"
const int PETMAX = 8;//�û�����ӵ�еĳ�������
enum BADGE {							//�߼��������
	GOLDEN,SLIVERN,CUPREOUS,NONE
};
//�û���
class USER {
private:
	string userName;					//�û���
	string passWord;					//����
	string nick;						//�û��ǳ�
	int petNum=0;						//��������
	//int advNum = 0;						//�߼���������
	POKEMON *pets[PETMAX];				//�����б�
	int fightTime = 0;					//�򶷴���
	int winTime = 0;					//սʤ����
	//double winRate = 0;						//ʤ��
	//BADGE petNumBadge = NONE;			//�����������
	//BADGE petAdvancedBadge = NONE;		//�߼��������

public:
	USER();
	~USER();
	string Get_UserName() const;
	void Input_UserName(string uname);
	string Get_PassWord() const;
	void Input_PassWord(string upw);
	string Get_Nick() const;
	void Input_Nick(string unick);
	int Get_PetNum() const;
	void Input_PetNum(int pnum);
	int Get_AdvNum() const;				//���ظ߼���������
	//void Input_AdvNum(int aNum);
	int Get_FightTime() const;
	void Input_FightTime(int uftime);
	int Get_WinTime() const;
	void Input_WinTime(int uwintime);
	double Get_WinRate() const;
	//void Input_WinRate(int uwinrate);
	BADGE Get_PetNumBadge() const;
	//void Input_PetNumBadge(BADGE pbadge);
	BADGE Get_AdvBadge() const;
	//void Input_AdvBadge(BADGE abadge);
	const POKEMON *ReadPets(int order) const;		//���ض�ȡ��orderֻ�����ָ��
	POKEMON *WritePets(int order);					//�����޸ĵ�orderֻ�����ָ��
	void InitialPets();								//��ʼ�������3ֻ����//δ���
	void InsertUser();								//���û����ݿ��в����û�
	void UpdateUser();								//�������ݿ��е��û���Ϣ
	void InsertPet();								//�ڳ������ݿ��в����û�����
	void UpdatePet();								//�������ݿ��еĳ�����Ϣ
	void FillInfo_from_Sqlite();					//�����ݿ��������û����ݵ���
};