#pragma once
#include "pokemon.h"
#include "fight.h"
#include "allPets.h"
const int PETMAX = 8;//用户可以拥有的宠物上限

//用户类
class USER {
private:
	string userName;//用户名
	string passWord;//密码
	int petNum=0;//宠物数量
	POKEMON pets[PETMAX];//宠物列表

public:
	USER();
	string Get_UserName() const;
	void Input_UserName(string uname);
	string Get_PassWord() const;
	void Input_PassWord(string upw);
	int Get_PetNum() const;
	void Input_PetNum(int pnum);
	const POKEMON *ReadPets(int order) const;//返回读取第order只宠物的指针
	POKEMON *WritePets(int order);//返回修改第order只宠物的指针
	void InitialPets();//初始随机发放3只宠物
};