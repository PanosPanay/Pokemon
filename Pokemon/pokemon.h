#pragma once
#include<iostream>
#include<string.h>
#include<string>
#include<windows.h>
#include<time.h>
using namespace std;
//const int SKILL_NUM = 20;//设定一个精灵可以拥有的技能数上限为20
//const int MIN_ATKI = 10;//设定最低攻击间隔，单位为10^-1s

//POWER:力量型，高攻击...TANK:肉盾型，高生命值...DEFENSIVE:防御型，高防御...AGILE:敏捷型，低攻击间隔
enum POKEMONKIND
{
	POWER, TANK, DEFENSIVE, AGILE
};

//五行属性：水 克 火 克 金 克 木 克 土 克 水
enum WUXINGTYPE
{
	SHUI, HUO, JIN, MU, TU
};

//技能种类：攻击型技能，回血型技能，增强自己防御力的技能，降低对手防御力的技能，增强自己的攻击力
enum SKILLKIND
{
	ATTACK, REHP, SELFDEFFENCE, OPPDEFEENCE, SELFATTACK
};

//技能是否已经拥有
enum OWN
{
	OWNED, NOTOWN
};

//技能招式类
class SKILL {
public:
	string SkillName;//技能名称
	int SkillRank=1;//技能等级
	SKILLKIND SkillKind;//技能种类。攻击or防御
	int SkillPower;//技能威力
	int SkillHit;//技能命中
	//int SkillPP;//Power Point招式点数，剩余可使用该招式的次数
	OWN Selected=NOTOWN;
	SKILL();
	SKILL(string sname, int srank, SKILLKIND skind, int spower, int shit);
	SKILL(const SKILL &SK);
};
typedef SKILL * PSKILL;

//宠物基类
class POKEMON {
private:
	POKEMONKIND	Kind;//种类
	string Name;//名字
	int Rank=1;//等级:每个精灵初始等级为1，满级15
	int Exp;//经验值，战斗获得，先是100升一级，每升一级后都要多100才能升级，100，200，300.。。。
	int	Hp;//生命值
	int	AtkInterval;//攻击间隔：单位为10^-1s
	//伤害=（（2*等级+10）/250*攻击方攻击力/防御方防御力*技能威力+2）*加成  加成由属性相克造成
	int Atk;//攻击力：攻击力高的精灵使用物理招式的伤害多
	int Def;//防御力：防御力高的精灵受到物理招式的伤害少
	//命中判定：A=招式的命中*攻击方命中率*(1-防御方回避率)。产生一个1～255之间的随机数，该随机数小于A时视为命中，否则为失误。
	double Accuracy;//命中率：命中率越高招式越容易命中
	double Evasiveness;//闪避率：闪避率越高，受到的招式越不容易命中
	WUXINGTYPE wType;//五行属性
	SKILL AllSkills[20];//所有技能列表
	PSKILL GotSkills[20];//已获得的技能列表，指向所有技能列表中相应的技能
	int AllSkillCnt;
	int GotSkillCnt;//当前已获得的技能数//是不是应该弄成public方便点//修改成指针？？？
	string Nick;//昵称

public:
	POKEMON();//默认构造函数
	POKEMON(POKEMONKIND xkind, string xname, int xrank, int xexp, int xatk, 
		int xdef, int xhp, int xatki,double xaccuracy,double xevasiveness,
		WUXINGTYPE xtype, int xskillcnt, string xnick, int xallSkillcnt);//赋值构造函数
	POKEMON(const POKEMON &PET);//拷贝构造函数
	~POKEMON();
	void Input_Kind(POKEMONKIND xkind);
	POKEMONKIND Get_Kind()const;
	void Input_Name(string xname);
	string Get_Name()const;
	void Input_Rank(int xrank);
	int Get_Rank()const;
	void Input_Exp(int xexp);
	int Get_Exp()const;
	void Input_Atk(int xatk);
	int Get_Atk()const;
	void Input_Def(int xdef);
	int Get_Def()const;
	void Input_Hp(int xhp);
	int Get_Hp()const;
	void Input_AtkI(int xatki);
	int Get_AtkI()const;
	void Input_Accuracy(double xaccuracy);
	double Get_Accuracy()const;
	void Input_Evasiveness(double xevasiveness);
	double Get_Evasiveness()const;
	void Input_Type(WUXINGTYPE xtype);
	WUXINGTYPE Get_Type()const;
	void Input_GotSkillCnt(int xskillcnt);
	int Get_GotSkillCnt()const;
	void Input_ALLSkillCnt(int xskillcnt);
	int Get_ALLSkillCnt()const;
	void Input_Nick(string xnick);
	string Get_Nick()const;
	const SKILL *Access_AllSkill()const;//返回访问所有技能列表的0位指针
	SKILL *Write_AllSkill();//返回修改所有技能列表的0位指针
	PSKILL Access_GotSkill(int pos)const;//访问某个已经get到的技能
	PSKILL *Write_GotSkill(int pos);//返回修改已获得技能列表的0位指针
	void RefershRank();//用当前的精灵经验值更新等级信息
	void PrintPetInfo();//打印宠物信息

	virtual void Upgrade();//升级函数（虚函数）
	//virtual void SkillAll();//存入该类小精灵的所有技能
};

//-----------------------------------------------------------------------------------------
//四种类型的精灵类：
//力量型宠物小精灵：高攻击
class POWERPET :public POKEMON{
public:
	POWERPET();
	POWERPET(POKEMONKIND xkind, string xname, int xrank, int xexp, int xatk,
		int xdef, int xhp, int xatki, double xaccuracy, double xevasiveness,
		WUXINGTYPE xtype, int xskillcnt, string xnick, int xallSkillcnt);
	POWERPET(const POWERPET& PET);

};
//肉盾型宠物小精灵：高生命
class TANKPET :public POKEMON{
public:
	TANKPET();
	TANKPET(POKEMONKIND xkind, string xname, int xrank, int xexp, int xatk,
		int xdef, int xhp, int xatki, double xaccuracy, double xevasiveness,
		WUXINGTYPE xtype, int xskillcnt, string xnick, int xallSkillcnt);
	TANKPET(const TANKPET& PET);

};
//防御性宠物小精灵：高防御
class DEFENSIVEPET :public POKEMON{
public:
	DEFENSIVEPET();
	DEFENSIVEPET(POKEMONKIND xkind, string xname, int xrank, int xexp, int xatk,
		int xdef, int xhp, int xatki, double xaccuracy, double xevasiveness,
		WUXINGTYPE xtype, int xskillcnt, string xnick, int xallSkillcnt);
	DEFENSIVEPET(const DEFENSIVEPET& PET);

};
//敏捷型宠物小精灵：低攻击间隔
class AGILEPET :public POKEMON{
public:
	AGILEPET();
	AGILEPET(POKEMONKIND xkind, string xname, int xrank, int xexp, int xatk,
		int xdef, int xhp, int xatki, double xaccuracy, double xevasiveness,
		WUXINGTYPE xtype, int xskillcnt, string xnick, int xallSkillcnt);
	AGILEPET(const AGILEPET& PET);

};
//----------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------
//具体的精灵类
//鲤鱼王（1-5）->暴鲤龙（6-10）->超级暴鲤龙（11-15）,高攻击
class GYARADOS :public POWERPET {
public:
	GYARADOS();
	/*GYARADOS(POKEMONKIND xkind, string xname, int xrank, int xexp, int xatk,
		int xdef, int xhp, int xatki, double xaccuracy, double xevasiveness,
		WUXINGTYPE xtype, int xskillcnt, string xnick, int xallSkillcnt);*/
	GYARADOS(const GYARADOS& PET);
	virtual void Upgrade();//升级函数（虚函数）
	void SkillAll();//存入该类小精灵的所有技能
};
//小福蛋Happiny->吉利蛋Chansey->幸福蛋Blissey,肉盾型
class HAPPINY :public TANKPET {
public:
	HAPPINY();
	/*HAPPINY(POKEMONKIND xkind, string xname, int xrank, int xexp, int xatk,
		int xdef, int xhp, int xatki, double xaccuracy, double xevasiveness,
		WUXINGTYPE xtype, int xskillcnt, string xnick, int xallSkillcnt);*/
	HAPPINY(const HAPPINY& PET);
	virtual void Upgrade();//升级函数（虚函数）
	void SkillAll();//存入该类小精灵的所有技能
};
//杰尼龟Squirtle(1-5级）->卡咪龟Wartortle(6-10级）->水箭龟Blastoise(11-15级），高防御
class SQUIRTLE :public DEFENSIVEPET{
//private:
//	SKILL Skills[SKILL_NUM];
public:
	SQUIRTLE();
	/*SQUIRTLE(POKEMONKIND xkind, string xname, int xrank, int xexp, int xatk,
		int xdef, int xhp, int xatki, double xaccuracy, double xevasiveness,
		WUXINGTYPE xtype, int xskillcnt, string xnick, int xallSkillcnt);*/
	SQUIRTLE(const SQUIRTLE& PET);
	virtual void Upgrade();//升级函数（虚函数）
	void SkillAll();//存入该类小精灵的所有技能
};
//超梦xMewtwoX->超梦Mewtwo->超级超梦yMewtwoY，敏捷型
class  MEWTWO :public AGILEPET {
public:
	MEWTWO();
	/*MEWTWO(POKEMONKIND xkind, string xname, int xrank, int xexp, int xatk,
		int xdef, int xhp, int xatki, double xaccuracy, double xevasiveness,
		WUXINGTYPE xtype, int xskillcnt, string xnick, int xallSkillcnt);*/
	MEWTWO(const MEWTWO& PET);
	virtual void Upgrade();//升级函数（虚函数）
	void SkillAll();//存入该类小精灵的所有技能
};
//火斑喵Litten->炎热喵Torracat->炽焰咆啸虎Incineroar，力量型
class INCINEROAR :public POWERPET {
public:
	INCINEROAR();
	/*INCINEROAR(POKEMONKIND xkind, string xname, int xrank, int xexp, int xatk,
		int xdef, int xhp, int xatki, double xaccuracy, double xevasiveness,
		WUXINGTYPE xtype, int xskillcnt, string xnick, int xallSkillcnt);*/
	INCINEROAR(const INCINEROAR& PET);
	virtual void Upgrade();//升级函数（虚函数）
	void SkillAll();//存入该类小精灵的所有技能
};

//小果然Wynaut->果然翁Wobbuffet，肉盾型
class WOBBUFFET :public TANKPET {
public:
	WOBBUFFET();
	/*WOBBUFFET(POKEMONKIND xkind, string xname, int xrank, int xexp, int xatk,
		int xdef, int xhp, int xatki, double xaccuracy, double xevasiveness,
		WUXINGTYPE xtype, int xskillcnt, string xnick, int xallSkillcnt);*/
	WOBBUFFET(const WOBBUFFET& PET);
	virtual void Upgrade();//升级函数（虚函数）
	void SkillAll();//存入该类小精灵的所有技能
};
//大岩蛇Onix->大钢蛇Steelix->超级大钢蛇，防御型
class STEELIX :public DEFENSIVEPET {
public:
	STEELIX();
	/*STEELIX(POKEMONKIND xkind, string xname, int xrank, int xexp, int xatk,
		int xdef, int xhp, int xatki, double xaccuracy, double xevasiveness,
		WUXINGTYPE xtype, int xskillcnt, string xnick, int xallSkillcnt);*/
	STEELIX(const STEELIX& PET);
	virtual void Upgrade();//升级函数（虚函数）
	void SkillAll();//存入该类小精灵的所有技能
};
//凯西Abra->勇基拉Kadabra->胡地Alakazam，敏捷型
class ALAKAZAM :public AGILEPET {
public:
	ALAKAZAM();
	/*ALAKAZAM(POKEMONKIND xkind, string xname, int xrank, int xexp, int xatk,
		int xdef, int xhp, int xatki, double xaccuracy, double xevasiveness,
		WUXINGTYPE xtype, int xskillcnt, string xnick, int xallSkillcnt);*/
	ALAKAZAM(const ALAKAZAM& PET);
	virtual void Upgrade();//升级函数（虚函数）
	void SkillAll();//存入该类小精灵的所有技能
};
