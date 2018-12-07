#pragma once
#include "pokemon.h"
#include "fight.h"
#include "string"
const int PETMAX = 8;//用户可以拥有的宠物上限
enum BADGE {							//高级宠物徽章
	GOLDEN,SLIVERN,CUPREOUS,NONE
};
//用户类
class USER {
private:
	string userName;					//用户名
	string passWord;					//密码
	string nick;						//用户昵称
	int petNum=0;						//宠物数量
	//int advNum = 0;						//高级宠物数量
	POKEMON *pets[PETMAX];				//宠物列表
	int fightTime = 0;					//打斗次数
	int winTime = 0;					//战胜次数
	//double winRate = 0;						//胜率
	//BADGE petNumBadge = NONE;			//宠物个数徽章
	//BADGE petAdvancedBadge = NONE;		//高级宠物徽章

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
	int Get_AdvNum() const;				//返回高级宠物数量
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
	const POKEMON *ReadPets(int order) const;		//返回读取第order只宠物的指针
	POKEMON *WritePets(int order);					//返回修改第order只宠物的指针
	void InitialPets();								//初始随机发放3只宠物//未完成
	void InsertUser();								//在用户数据库中插入用户
	void UpdateUser();								//更新数据库中的用户信息
	void InsertPet();								//在宠物数据库中插入用户宠物
	void UpdatePet();								//更新数据库中的宠物信息
	void FillInfo_from_Sqlite();					//从数据库中填入用户数据到类
};