#pragma once
#include "pokemon.h"
#include "fight.h"
#include "allPets.h"
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
	int petNum=0;						//��������
	POKEMON pets[PETMAX];				//�����б�
	double winRate;						//ʤ��
	BADGE petNumBadge = NONE;			//�����������
	BADGE petAdvancedBadge = NONE;		//�߼��������

public:
	USER();
	string Get_UserName() const;
	void Input_UserName(string uname);
	string Get_PassWord() const;
	void Input_PassWord(string upw);
	int Get_PetNum() const;
	void Input_PetNum(int pnum);
	const POKEMON *ReadPets(int order) const;		//���ض�ȡ��orderֻ�����ָ��
	POKEMON *WritePets(int order);					//�����޸ĵ�orderֻ�����ָ��
	void InitialPets();								//��ʼ�������3ֻ����//δ���
	void InsertUser();								//���û����ݿ��в����û�
	void UpdateUser();								//�������ݿ��е��û���Ϣ
	void InsertPet();								//�ڳ������ݿ��в����û�����
	void UpdatePet();								//�������ݿ��еĳ�����Ϣ
	void FillInfo_from_Sqlite();					//�����ݿ��������û����ݵ���
};