#pragma once
#include "pokemon.h"

//所有宠物集和
class ALLPETS {
private:
	int petsCnt;
	GYARADOS gyarados1;
	HAPPINY happiny1;
	SQUIRTLE squirtle1;
	MEWTWO mewtwo1;
	INCINEROAR incineroar1;
	WOBBUFFET wobbufffet1;
	STEELIX steelix1;
	ALAKAZAM alakazam1;
public:
	ALLPETS();
	//RandomInit();//随机每个1级精灵的初始属性
	POKEMON* GetAPet(int order);//返回第order只精灵的指针
};