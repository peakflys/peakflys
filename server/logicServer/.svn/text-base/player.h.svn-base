#include <iostream>
#include <iomanip>//用于设置域宽
#include <stdlib.h>
#include <time.h>//用于产生随机因子
#include "container.h"
enum property{sw,ar,mg};//设置三种职业属性，枚举类型
class Player//人物类
{
	friend void showinfo(Player &p1,Player &p2);//显示两个玩家的信息
	friend class Swordsman;
	friend class Archer;
	friend class Mage;
protected:
	int HP,HPmax,MP,MPmax,AP,DP,speed,EXP,LV;//一般属性
	char name[10];//人物名称
	property role;//人物职业（角色）
	container bag;//物品栏
public:
	virtual bool attack(Player &p)=0;//普通攻击，纯虚函数
	virtual bool specialatt(Player &p)=0;//特殊攻击，纯虚函数
	virtual void isLevelUp()=0;//升级设定，纯虚函数
	void ReFill();//每版结束后人类玩家生命值魔法值恢复
	bool Death();//告知是否人物已经死亡
	void isDead();//判断人物是否死亡
	bool useHeal();//使用回复剂，与职业无关
	bool useMW();//使用魔法水，与职业无关
	void transfer(Player &p);//敌人杀死后，人类玩家获得对方物品
	char showRole();//显示人物的职业
protected:
	bool death;//是否死亡
};
void Player::ReFill()
{
	HP=HPmax;
	MP=MPmax;
}
bool Player::Death()
{
	return death;
}
void Player::isDead()
{
	if (HP<=0)
	{
		cout <<name <<"已阵亡。" <<endl;
		system("pause");
		death=1;
	}
}
bool Player::useHeal()
{
	if (bag.nOfHeal()>0)
	{
		HP=HP+100;
		if (HP>HPmax)
			HP=HPmax;
		cout <<name <<"使用了回复剂，生命值增加了100。" <<endl;
		bag.useHeal();
		system("pause");
		return 1;//使用回复剂操作成功
	}
	cout <<"对不起，您没有回复剂可以使用了。" <<endl;
	system("pause");
	return 0;//使用回复剂操作失败
}
bool Player::useMW()
{
	if (bag.nOfMW()>0)
	{
		MP=MP+80;
		if (MP>MPmax)
			MP=MPmax;
		cout <<name <<"使用了魔法水，魔法值增加了80。" <<endl;
		bag.useMW();
		system("pause");
		return 1;
	}
	cout <<"对不起，您没有魔法水可以使用了。" <<endl;
	system("pause");
	return 0;
}
void Player::transfer(Player &p)
{
	cout <<name <<"获得了" <<p.bag.nOfHeal() <<"个回复剂和" <<p.bag.nOfMW() <<"个魔法水。" <<endl;
	system("pause");
	bag.set(bag.nOfHeal()+p.bag.nOfHeal(),bag.nOfMW()+p.bag.nOfMW());
}
char Player::showRole()
{
	switch(role)
	{
	case sw:
		cout <<setw(6) <<"剑士";
		break;
	case ar:
		cout <<setw(6) <<"弓箭手";
		break;
	case mg:
		cout <<setw(6) <<"法师";
		break;
	default:
		break;
	}
	return ' ';
}
void showinfo(Player &p1,Player &p2)//纯粹的输出问题
{
	cout <<"###################################################" <<endl;
	cout <<"# 玩家 " <<setw(11) <<p1.name <<" LV." <<setw(3) <<p1.LV <<"# 敌人 " <<setw(11) <<p2.name <<" LV." <<setw(3) <<p2.LV <<'#' <<endl;
	cout <<"# HP " <<setw(3) <<(p1.HP<=999?p1.HP:999) <<'/' <<setw(3) <<(p1.HPmax<=999?p1.HPmax:999) <<" MP " <<setw(3) <<(p1.MP<=999?p1.MP:999) <<'/' <<setw(3) <<(p1.MPmax<=999?p1.MPmax:999) <<"  # HP "<<setw(3) <<(p2.HP<=999?p2.HP:999) <<'/' <<setw(3) <<(p2.HPmax<=999?p2.HPmax:999) <<" MP " <<setw(3) <<(p2.MP<=999?p2.MP:999) <<'/' <<setw(3) <<(p2.MPmax<=999?p2.MPmax:999) <<"  #"<<endl;
	cout <<"# AP " <<setw(3) <<(p1.AP<=999?p1.AP:999) <<" DP " <<setw(3) <<(p1.DP<=999?p1.DP:999) <<" Speed " <<setw(3) <<(p1.speed<=999?p1.speed:999) <<"# AP " <<setw(3) <<(p2.AP<=999?p2.AP:999) <<" DP " <<setw(3) <<(p2.DP<=999?p2.DP:999) <<" Speed " <<setw(3) <<(p2.speed<=999?p2.speed:999) <<'#' <<endl;
	cout <<"# EXP" <<setw(7) <<p1.EXP <<" 职业 ";
	cout <<p1.showRole();
	cout <<"# EXP" <<setw(7) <<p2.EXP <<" 职业 ";
	cout <<p2.showRole() <<'#' <<endl;
	cout <<"###################################################" <<endl;
	p1.bag.display();
}




		



