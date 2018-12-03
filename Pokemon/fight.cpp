#include "fight.h"

FIGHT::FIGHT()
{
}

FIGHT::FIGHT(POKEMON *F1, POKEMON *F2)
{
	realA = F1;
	realB = F2;
	A = *realA;
	B = *realB;
}

FIGHT::FIGHT(const FIGHT & theFight)
{
	realA = theFight.realA;
	realB = theFight.realB;
	A = theFight.A;
	B = theFight.B;
}

void FIGHT::A_VS_B()
{
	srand((unsigned)time(NULL));
	//int Attacker;//0表示攻击方是A，1表示攻击方是B
	POKEMON *Attacker = NULL;
	POKEMON *Defender = NULL;
	int currentTime = 0;
	int Aorder = 0;
	int Border = 0;
	int SleepTime = 0;
	if (A.Get_AtkI() <= B.Get_AtkI())
	{
		Attacker = &A;
		currentTime += A.Get_AtkI();
		Defender = &B;
	}
	else
	{
		Attacker = &B;
		currentTime += B.Get_AtkI();
		Defender = &A;
	}
	//输出战斗双方当前属性值
	string defenderName = Defender->Get_Name();
	string attackName = Attacker->Get_Name();
	cout << "战斗开始！" << endl;
	cout << attackName << ": " << "HP=" << Attacker->Get_Hp() << ", Atk=" << Attacker->Get_Atk()
		<< ", Def=" << Attacker->Get_Def() << ", Accuracy=" << Attacker->Get_Accuracy() << ", Evasiveness="
		<< Attacker->Get_Evasiveness() << endl;
	cout << defenderName << ": " << "HP=" << Defender->Get_Hp() << ", Atk=" << Defender->Get_Atk()
		<< ", Def=" << Defender->Get_Def() << ", Accuracy=" << Defender->Get_Accuracy() << ", Evasiveness="
		<< Defender->Get_Evasiveness() << endl << endl;
	while (A.Get_Hp() > 0 && B.Get_Hp() > 0)
	{
		defenderName = Defender->Get_Name();
		attackName = Attacker->Get_Name();
		//需要改变一下atki，注意和速度是相反的概念
		if (Attacker == &A)//A出招
		{
			++Aorder;
		}
		else //B出招
		{
			++Border;
		}
		//确定招式并输出
		int theSkill = rand() % (Attacker->Get_GotSkillCnt());//随机选取一个招式，或者加一个开关，让用户选择招式？？？？？？？？？？？？
		SKILL* theSkillPtr = Attacker->Access_GotSkill(theSkill);
		cout << "招式" << Aorder + Border << ":" << endl;
		cout << attackName << "发动" << theSkillPtr->SkillName << endl;
		//计算命中
		int theHitNum = (theSkillPtr->SkillHit)*(Attacker->Get_Accuracy())*(1 - (Defender->Get_Evasiveness())) * 100;
		int isHit = rand() % 100 + 1;
		double addition = 1;//加成，属性相克
		switch (theSkillPtr->SkillKind)
		{
		case ATTACK:
			//分析命中率和伤害函数
			//double addition = 1;//加成，属性相克
			if (Defender->Get_Type() - Attacker->Get_Type() == 1 || Defender->Get_Type() - Attacker->Get_Type() == 4)
				addition = 1.2;
			else if (Attacker->Get_Type() - Defender->Get_Type() == 1 || Attacker->Get_Type() - Defender->Get_Type() == 4)
				addition = 0.8;
			
			if (isHit <= theHitNum)//命中
			{
				//计算伤害
				int hurt = ((Attacker->Get_Atk()) / (Attacker->Get_Def()))*(theSkillPtr->SkillPower)*(addition);
				int theHp = Defender->Get_Hp();
				if (theHp > hurt)
					theHp = theHp - hurt;
				else
					theHp = 0;
				Defender->Input_Hp(theHp);
				cout << "命中！" << defenderName << "受到" << hurt << "点伤害！" << endl;
			}
			else
			{
				cout << "未命中！" << defenderName << "灵巧地躲避了攻击！" << endl;
			}
			break;
		case REHP:
			if (isHit <= theHitNum)//成功使用招式回血
			{
				int theHp = Attacker->Get_Hp();
				theHp = theHp + theSkillPtr->SkillPower;
				Attacker->Input_Hp(theHp);
				cout << "成功回血！" << attackName << "生命值增加" << theSkillPtr->SkillPower << "点" << endl;
			}
			else
			{
				cout << "回血失败！" << endl;
			}
			break;
		case SELFDEFFENCE:
			if (isHit <= theHitNum)//成功使用招式增加自身防御力
			{
				int theDef = Attacker->Get_Def();
				theDef = theDef + theSkillPtr->SkillPower;
				Attacker->Input_Def(theDef);
				cout << "成功出招！" << attackName << "防御力增加" << theSkillPtr->SkillPower << "点" << endl;
			}
			else
			{
				cout << "防御力提升失败！" << endl;
			}
			break;
		case OPPDEFEENCE:
			if (isHit <= theHitNum)//成功使用招式降低对方防御力
			{
				int theDef = Attacker->Get_Def();
				if (theDef - theSkillPtr->SkillPower > 10)//防御力下限为10
				{
					theDef = theDef - theSkillPtr->SkillPower;
					cout << "成功出招！" << defenderName << "防御力降低" << theSkillPtr->SkillPower << "点" << endl;
				}
				else
				{					
					cout << "成功出招！" << defenderName << "防御力降低到下限（10点）" << endl;
					theDef = 10;
				}				
				Attacker->Input_Def(theDef);
			}
			else
			{
				cout << "未能对敌方防御力造成实质性威胁！" << endl;
			}
			break;
		case SELFATTACK:
			if (isHit <= theHitNum)//成功使用招式增加自身攻击力
			{
				int theAtk = Attacker->Get_Atk();
				theAtk = theAtk + theSkillPtr->SkillPower;
				Attacker->Input_Atk(theAtk);
				cout << "成功出招！" << attackName << "攻击力增加" << theSkillPtr->SkillPower << "点" << endl;
			}
			else
			{
				cout << "攻击力提升失败！" << endl;
			}
			break;
		default:
			break;
		}
		//输出战斗双方当前属性值
		cout << attackName << ": " << "HP=" << Attacker->Get_Hp() << ", Atk=" << Attacker->Get_Atk()
			<< ", Def=" << Attacker->Get_Def() << ", Accuracy=" << Attacker->Get_Accuracy() << ", Evasiveness="
			<< Attacker->Get_Evasiveness() << endl;
		cout << defenderName << ": " << "HP=" << Defender->Get_Hp() << ", Atk=" << Defender->Get_Atk()
			<< ", Def=" << Defender->Get_Def() << ", Accuracy=" << Defender->Get_Accuracy() << ", Evasiveness="
			<< Defender->Get_Evasiveness() << endl << endl;
		//设置几率降低精灵的命中率和闪避率
		//下一个出招的精灵
		if (((Aorder + 1)*A.Get_AtkI()) < ((Border + 1)*B.Get_AtkI()))
		{
			Attacker = &A;
			Defender = &B;
			SleepTime = ((Aorder + 1)*A.Get_AtkI()) - currentTime;
		}
		else
		{
			Attacker = &B;
			Defender = &A;
			SleepTime = ((Aorder + 1)*B.Get_AtkI()) - currentTime;
		}
		//Sleep(SleepTime);///////////////////////////////////////////////
	}
	//战斗后增加宠物小精灵的经验
	if (A.Get_Hp() > 0)//A赢
	{
		int nowExp = A.Get_Exp();
		nowExp = nowExp + winExp;
		A.Input_Exp(nowExp);
		nowExp = B.Get_Exp();
		nowExp = nowExp + loseExp;
		B.Input_Exp(nowExp);
		cout << A.Get_Name() << "WIN!" << "EXP+" << winExp << endl;
		cout << B.Get_Name() << "LOSE!" << "EXP+" << loseExp << endl;
	}
	else if (B.Get_Hp() > 0)//B赢
	{
		int nowExp = B.Get_Exp();
		nowExp = nowExp + winExp;
		B.Input_Exp(nowExp);
		nowExp = A.Get_Exp();
		nowExp = nowExp + loseExp;
		A.Input_Exp(nowExp);
		cout << B.Get_Name() << "WIN!" << "EXP+" << winExp << endl;
		cout << A.Get_Name() << "LOSE!" << "EXP+" << loseExp << endl;
	}
	else//A、B平局（实际不会出现？）
	{
		int nowExp = A.Get_Exp();
		nowExp = nowExp + tieExp;
		A.Input_Exp(nowExp);
		nowExp = B.Get_Exp();
		nowExp = nowExp + tieExp;
		B.Input_Exp(nowExp);
		cout << B.Get_Name() << "TIE!" << "EXP+" << tieExp << endl;
		cout << A.Get_Name() << "TIE!" << "EXP+" << tieExp << endl;
	}
	//更新宠物等级信息
	A.RefershRank();
	B.RefershRank();
	//检查是否有升级
	if (A.Get_Rank() > realA->Get_Rank())//升级
	{
		//最后再把新的等级和经验返回给宠物
		realA->Input_Exp(A.Get_Exp());
		realA->Input_Rank(A.Get_Rank());
		realA->Upgrade();//调用升级函数
	}
	else
	{
		realA->Input_Exp(A.Get_Exp());
		realA->Input_Rank(A.Get_Rank());
	}
	if (B.Get_Rank() > realB->Get_Rank())
	{
		realB->Input_Exp(B.Get_Exp());
		realB->Input_Rank(B.Get_Rank());
		realB->Upgrade();
	}
	else
	{
		realB->Input_Exp(B.Get_Exp());
		realB->Input_Rank(B.Get_Rank());
	}
	
}

