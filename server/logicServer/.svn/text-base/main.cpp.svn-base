#include <iostream>
#include "swordsman.h"
#include "archer.h"
#include "mage.h"
int main()
{
	char temp[10];
	bool success=0;//操作是否成功
	cout <<"请输入玩家名字：";
	cin >>temp;
	Player *human;//定义一个人物类指针
	int instemp;//存放指令数
	do
	{
		cout <<"请选择职业：1 剑士 2 弓箭手 3 法师" <<endl;
		cin >>instemp;
		system("cls");
		switch (instemp)//选择职业
		{
		case 1://选择了剑士
			human=new Swordsman(1,temp);
			success=1;//操作成功
			break;
		case 2:
			human=new Archer(1,temp);
			success=1;
			break;
		case 3:
			human=new Mage(1,temp);
			success=1;
			break;
		default:
			break;
		}
	}while (success!=1);//循环选择直到操作成功
	int j=0;//第几版
	for (int i=1;j<5;i=i+2)
	{
		j++;
		system("cls");
		cout <<"STAGE " <<j <<endl;
		cout <<"敌方介绍：一个" <<i <<"级的剑士。"<<endl;
		system("pause");
		Swordsman enemy(i,"敌方士兵");//创建一个i级的剑士作为敌人
		human->ReFill();//人类玩家每过一版生命魔法值恢复
		while (!human->Death() && !enemy.Death())//两个人都没死则继续战斗
		{
			success=0;
			while (success!=1)//直到操作成功
			{
				system("cls");
				showinfo(*human,enemy);//显示两个玩家信息
				cout <<"请下达指令：" <<endl;
				cout <<"1 攻击 2 特殊攻击 3 使用回复剂 4 使用魔法水 0 退出游戏 " <<endl;
				cin >>instemp;
				switch (instemp)
				{
				case 0:
					cout <<"是否要退出游戏？Y/N" <<endl;
					char temp;
					cin >>temp;
					if (temp=='Y' || temp=='y')
					{
						return 0;
					}
					else
						break;
				case 1:
					success=human->attack(enemy);//如果把isLevelUp和isDead放到attack里面，会导致电脑也能够升级
					human->isLevelUp();
					enemy.isDead();
					break;
				case 2:
					success=human->specialatt(enemy);
					human->isLevelUp();
					enemy.isDead();
					break;
				case 3:
					success=human->useHeal();
					break;
				case 4:
					success=human->useMW();
					break;
				default:
					break;
				}
			}
			if (!enemy.Death())//如果电脑玩家没有死亡
			{
				enemy.AI(*human);//与人类对战
			}
			else
			{
				human->transfer(enemy);//把物品给人类玩家
			}
			if (human->Death())//如果人类玩家死亡
			{
				system("cls");
				cout <<endl <<endl <<endl <<endl <<endl <<setw(50) <<"胜败乃兵家常事，好男儿请重新再来。" <<endl;
				delete human;//释放内存
				system("pause");
				return 0;
			}
		}
	}
	system("cls");
	cout <<endl <<endl <<endl <<endl <<endl <<setw(60) <<"所有的敌人都已经被您消灭了！世界又恢复了往日的和平。" <<endl <<endl <<endl <<setw(35) <<"终" <<endl <<endl <<endl <<endl <<endl;
	delete human;//释放内存
	system("pause");
	return 0;
}
