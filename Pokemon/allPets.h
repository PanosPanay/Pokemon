#pragma once
#include "pokemon.h"

//���г��Ｏ��
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
	//RandomInit();//���ÿ��1������ĳ�ʼ����
	POKEMON* GetAPet(int order);//���ص�orderֻ�����ָ��
};