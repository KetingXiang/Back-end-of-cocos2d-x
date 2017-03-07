#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <CCEventListenerKeyboard.h>
#include <CCEventKeyboard.h>
#include <CCSpriteFrameCache.h>
using namespace cocos2d;

class Listener : public cocos2d::Layer {
protected:
	bool KeyUp;
	bool KeyDown;
	bool KeyLeft;
	bool KeyRight;
	bool KeyEnter;
	int count_x[10];		//左右切换计数器
	int count_y;			//上下切换计数器

public:
	Listener();
	void RegisterListener();
	virtual void onKeyPressed(EventKeyboard::KeyCode keycode, Event *event);
};
//主菜单
class HelloWorld: public Listener {
private:
	Sprite* Background, * sprite1, * sprite2, * sprite3, * sprite4,
		* sprite5, * sprite6, * sprite7, * sprite8, * sprite9;
	int x = 600;			//第一个选项的横坐标
	int y = 550;			//............纵坐标
	int step = 80;			//纵向间隔
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	virtual void update(float dt);
    CREATE_FUNC(HelloWorld);
};
//参数调整
class ParameterAdjust : public Listener {
private:
	Sprite* Background1, *Background2, *sprite1, *sprite2, *sprite3, *sprite4, *sprite5, *sprite6, *sprite7, *sprite8, *sprite9, *sprite10, 
			*sprite11, *sprite12, *sprite13, *sprite14, *sprite15, *sprite16, *sprite17, *sprite18, *sprite19, *sprite20, *sprite21,
			*sprite22;
	int x = 200;			//第一个选项的横坐标
	int y = 600;			//............纵坐标
	int step = 38;			//纵向间隔
	std::vector<std::string> red;			//红色数字
	std::vector<std::string> green;			//绿色数字
	std::vector<std::string> difficulty;	//难度调整
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void update(float dt);
	CREATE_FUNC(ParameterAdjust);
};
//解码调整
class DecodeAdjust : public Listener {
private:
	Sprite* Background1, *Background2, *sprite1, *sprite2, *sprite3, *sprite4, *sprite5, *sprite6, *sprite7, *sprite8, *sprite9, *sprite10,
		*sprite11, *sprite12, *sprite13, *sprite14, *sprite15, *sprite16, *sprite17, *sprite18, *sprite19, *sprite20, *sprite21,
		*sprite22;
	int step = 63;			//纵向间隔
	bool flag1;				//是否弹出输入解码条码框
	bool c[12];		//输入的12位条码对应从高位到低位，判断是否输入
	int count[12];	//记录12位
	int UpOrDown;	//上下选择
	int LeftOrRight;	//左右选择
	std::vector<std::string> red;//红色数字
	std::vector<std::string> green;//绿色数字
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void update(float dt);
	CREATE_FUNC(DecodeAdjust);
};
//查账
class CheckAccount : public Listener {
private:
	Sprite* Background1, *Background2, *sprite1, *sprite2, *sprite3, *sprite4, *sprite5, *sprite6, *sprite7, *sprite8, *sprite9, *sprite10,
		*sprite11, *sprite12, *sprite13, *sprite14, *sprite15, *sprite16, *sprite17, *sprite18, *sprite19, *sprite20, *sprite21,
		*sprite22;
	Layer* layer1;
	Layer* layer2;
	bool flag;				//分机查账时的标志位，因为是输入两次enter。
	int count;
	std::vector<std::string> red;//红色数字
	std::vector<std::string> green;//绿色数字
	std::vector<std::string> blue;
	std::vector<std::string> white;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void update(float dt);
	CREATE_FUNC(CheckAccount);
};
//报账
class ReportAccount : public Listener {
private:
	Sprite* Background1, *Background2, *Background3, *sprite1, *sprite2, *sprite3, *sprite4, *sprite5, *sprite6, *sprite7, *sprite8, *sprite9, *sprite10,
		*sprite11, *sprite12, *sprite13, *sprite14, *sprite15, *sprite16, *sprite17, *sprite18, *sprite19, *sprite20, *sprite21,
		*sprite22, *sprite23, *sprite24;
	Layer* layer1;	//选择报账后的第一个界面
	Layer* layer2;
	bool flag1, flag2, flag3;	//对应记录当前是哪个界面，true表示打开。
	bool c[8];		//输入的8位条码对应从高位到低位，判断是否输入
	int count[8];	//记录8位
	int UpOrDown;	//上下选择
	int LeftOrRight;	//左右选择
	std::vector<std::string> red;
	std::vector<std::string> blue;
	std::vector<std::string> green;
	std::vector<std::string> orange;
	std::vector<std::string> purple;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void update(float dt);
	CREATE_FUNC(ReportAccount);
};
//系统设置
class SystemSetting : public Listener {
private:
	Sprite* Background1, *Background2, *sprite1, *sprite2, *sprite3, *sprite4, *sprite5, *sprite6, *sprite7, *sprite8, *sprite9, *sprite10,
		*sprite11, *sprite12, *sprite13, *sprite14, *sprite15, *sprite16, *sprite17, *sprite18, *sprite19, *sprite20, *sprite21,
		*sprite22, *sprite23, *sprite24;
	bool c[8];		//输入的8位条码对应从高位到低位，判断是否输入
	int count[8];	//记录8位
	int UpOrDown;	//上下选择
	int LeftOrRight;	//左右选择
	std::vector<std::string> red;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void update(float dt);
	CREATE_FUNC(SystemSetting);
};
//通信测试
class CommunicationTest : public Listener {
private:
	Sprite* Background, *Background2, *sprite1, *sprite2, *sprite3, *sprite4, *sprite5, *sprite6, *sprite7, *sprite8, *sprite9, *sprite10,
		*sprite11, *sprite12, *sprite13, *sprite14, *sprite15, *sprite16, *sprite17, *sprite18, *sprite19, *sprite20, *sprite21,
		*sprite22;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void update(float dt);
	CREATE_FUNC(CommunicationTest);
};

#endif // __HELLOWORLD_SCENE_H__
