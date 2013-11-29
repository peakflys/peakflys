#include <iostream>
using namespace std;

class container//人物的物品栏
{
protected:
	int numOfHeal;//回复剂数
	int numOfMagicWater;//魔法水数
public:
	container();//构造函数
	void set(int i,int j);//重设物品数
	int nOfHeal();//判断是否还有回复剂
	int nOfMW();//判断是否还有魔法水
	void display();//显示物品情况
	bool useHeal();//使用回复剂
	bool useMW();//使用魔法水
};
container::container()
{
	set(0,0);
}
void container::set(int i,int j)
{
	numOfHeal=i;
	numOfMagicWater=j;
}
int container::nOfHeal()
{
	return numOfHeal;
}
int container::nOfMW()
{
	return numOfMagicWater;
}
void container::display()
{
	cout <<"回复剂（生命值+100）还有" <<numOfHeal <<"个" <<endl;
	cout <<"魔法水（魔法值+ 80）还有" <<numOfMagicWater <<"个" <<endl;
}
bool container::useHeal()
{
	numOfHeal--;
	return 1;
}
bool container::useMW()
{
	numOfMagicWater--;
	return 1;
}