#include "HelloWorldScene.h"
#include <windows.h>
#include <iostream>

using namespace std;

USING_NS_CC;
/////////////////////////////////////////----------监听器----------////////////////////////////////////////////
Listener::Listener() {
	KeyUp = false;
	KeyDown = false;
	KeyLeft = false;
	KeyRight = false;
	KeyEnter = false;
	memset(count_x, 0, sizeof(count_x));
	count_y = 0;
}
void Listener::RegisterListener() {
	auto ListenerKey = EventListenerKeyboard::create();
	ListenerKey->onKeyPressed= CC_CALLBACK_2(Listener::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(ListenerKey, this);
}
void Listener::onKeyPressed(EventKeyboard::KeyCode keycode, Event *event) {
	if (keycode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
		KeyUp = true;
		count_y--;
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
		KeyDown = true;
		count_y++;
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
		KeyLeft = true;
		count_x[count_y]--;
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
		KeyRight = true;
		count_x[count_y]++;
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_KP_ENTER) {
		KeyEnter = true;
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_BACKSPACE) {
		auto director = Director::getInstance();
		director->end();
	}
}
/////////////////////////////////////////----------主菜单----------////////////////////////////////////////////
Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}
bool HelloWorld::init()
{
    if ( !Layer::init() ) {
        return false;
    }
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//背景图片
	Background = Sprite::create("Setting/SettingParameter/3.png");
	Background->setAnchorPoint(Point(0, 1));
	Background->setPosition(Vec2(origin.x + 0, origin.y + visibleSize.height));
	float width1 = Background->getContentSize().width;
	float height1 = Background->getContentSize().height;
	Background->setScaleX(visibleSize.width / width1);
	Background->setScaleY(visibleSize.height / height1);
	this->addChild(Background, 0);

	//参数调整
	sprite1 = Sprite::create("Setting/SettingParameter/4.png");
	sprite1->setAnchorPoint(Point(0, 0));
	sprite1->setPosition(Vec2(x, y));
	this->addChild(sprite1, 1);
	
	//解码调整
	sprite2 = Sprite::create("Setting/SettingParameter/5.png");
	sprite2->setAnchorPoint(Point(0, 0));
	sprite2->setPosition(Vec2(x, y - step * 1));
	this->addChild(sprite2, 1);

	//查账
	sprite3 = Sprite::create("Setting/SettingParameter/6.png");
	sprite3->setAnchorPoint(Point(0, 0));
	sprite3->setPosition(Vec2(x, y - step * 2));
	this->addChild(sprite3, 1);

	//报账
	sprite4 = Sprite::create("Setting/SettingParameter/7.png");
	sprite4->setAnchorPoint(Point(0, 0));
	sprite4->setPosition(Vec2(x, y - step * 3));
	this->addChild(sprite4, 1);

	//系统设置
	sprite5 = Sprite::create("Setting/SettingParameter/8.png");
	sprite5->setAnchorPoint(Point(0, 0));
	sprite5->setPosition(Vec2(x, y - step * 4));
	this->addChild(sprite5, 1);

	//通信测试
	sprite6 = Sprite::create("Setting/SettingParameter/9.png");
	sprite6->setAnchorPoint(Point(0, 0));
	sprite6->setPosition(Vec2(x, y - step * 5));
	this->addChild(sprite6, 1);

	//退出
	sprite7 = Sprite::create("Setting/SettingParameter/10.png");
	sprite7->setAnchorPoint(Point(0, 0));
	sprite7->setPosition(Vec2(x, y - step * 6));
	this->addChild(sprite7, 1);
    
	//指示当前选项图标
	sprite8 = Sprite::create("Setting/SettingParameter/car.png");
	sprite8->setAnchorPoint(Point(0, 0));
	sprite8->setPosition(Vec2(x - step, y));
	this->addChild(sprite8, 1);

	//指示当前选线图标后的白色阴影
	sprite9 = Sprite::create("Setting/SettingParameter/1.png");
	sprite9->setAnchorPoint(Point(0, 0));
	sprite9->setPosition(Vec2(x, y));
	this->addChild(sprite9, 0);

	this->RegisterListener();
		
	scheduleUpdate();
    
    return true;
}
void HelloWorld::update(float dt) {
	if (KeyUp || KeyDown) {
		count_y = (count_y < 0) ? (count_y + 7) : (count_y % 7);
		auto moveTo1 = MoveTo::create(0.1, Vec2(x - step, y - step * count_y));
		auto moveTo2 = MoveTo::create(0.1, Vec2(x, y - step * count_y));
		sprite8->runAction(moveTo1);
		sprite9->runAction(moveTo2);
		KeyUp = KeyDown = false;
	}
	else if (KeyEnter) {
		auto director = Director::getInstance();
		if (count_y == 0) {
			auto scene = ParameterAdjust::createScene();
			director->pushScene(scene);
		}
		else if (count_y == 1) {
			auto scene = DecodeAdjust::createScene();
			director->pushScene(scene);
		}
		else if (count_y == 2) {
			auto scene = CheckAccount::createScene();
			director->pushScene(scene);
		}
		else if (count_y == 3) {
			auto scene = ReportAccount::createScene();
			director->pushScene(scene);
		}
		else if (count_y == 4) {
			auto scene = SystemSetting::createScene();
			director->pushScene(scene);
		}
		else if (count_y == 5) {
			auto scene = CommunicationTest::createScene();
			director->pushScene(scene);
		}
		else
			director->end();
		KeyEnter = false;
	}

}
////////////////////////////////////////----------参数调整----------///////////////////////////////////////////
Scene* ParameterAdjust::createScene()
{
	auto scene = Scene::create();
	auto layer = ParameterAdjust::create();
	scene->addChild(layer);
	return scene;
}
bool ParameterAdjust::init()
{
	if (!Layer::init()) {
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//建立常用图片地址索引
	green.push_back("ParameterAdjust/Number1/0_1.png");
	green.push_back("ParameterAdjust/Number1/0_2.png");
	green.push_back("ParameterAdjust/Number1/0_3.png");
	green.push_back("ParameterAdjust/Number1/0_4.png");
	green.push_back("ParameterAdjust/Number1/0_5.png");
	green.push_back("ParameterAdjust/Number1/0_6.png");
	green.push_back("ParameterAdjust/Number1/0_7.png");
	green.push_back("ParameterAdjust/Number1/0_8.png");
	green.push_back("ParameterAdjust/Number1/0_9.png");
	green.push_back("ParameterAdjust/Number1/0_10.png");

	red.push_back("ParameterAdjust/Number/0_1.png");
	red.push_back("ParameterAdjust/Number/0_2.png");
	red.push_back("ParameterAdjust/Number/0_3.png");
	red.push_back("ParameterAdjust/Number/0_4.png");
	red.push_back("ParameterAdjust/Number/0_5.png");
	red.push_back("ParameterAdjust/Number/0_6.png");
	red.push_back("ParameterAdjust/Number/0_7.png");
	red.push_back("ParameterAdjust/Number/0_8.png");
	red.push_back("ParameterAdjust/Number/0_9.png");
	red.push_back("ParameterAdjust/Number/0_10.png");

	difficulty.push_back("ParameterAdjust/1_1.png");
	difficulty.push_back("ParameterAdjust/1_2.png");
	difficulty.push_back("ParameterAdjust/1_3.png");
	difficulty.push_back("ParameterAdjust/1_4.png");
	difficulty.push_back("ParameterAdjust/1_5.png");

	//背景图片
	Background1 = Sprite::create("ParameterAdjust/background.png");
	Background1->setAnchorPoint(Point(0, 1));
	Background1->setPosition(Vec2(0, visibleSize.height));
	float width1 = Background1->getContentSize().width;
	float height1 = Background1->getContentSize().height;
	Background1->setScaleX(visibleSize.width / width1);
	Background1->setScaleY(visibleSize.height / height1);
	this->addChild(Background1, 0);

	//所有选项
	Background2 = Sprite::create("ParameterAdjust/parameter1.png");
	Background2->setAnchorPoint(Point(0, 1));
	Background2->setPosition(Vec2(250, 600));
	this->addChild(Background2, 1);

	//指示当前选项图标--car
	sprite1 = Sprite::create("Setting/SettingParameter/car.png");
	sprite1->setAnchorPoint(Point(0, 0));
	sprite1->setPosition(Vec2(170, 565));
	this->addChild(sprite1, 1);

	//指示当前选线图标后的白色阴影
	sprite2 = Sprite::create("ParameterAdjust/2.png");
	sprite2->setAnchorPoint(Point(0, 0));
	sprite2->setPosition(Vec2(250, 565));
	this->addChild(sprite2, 1);

	//调整难度
	sprite3 = Sprite::create("ParameterAdjust/1_1.png");
	sprite3->setAnchorPoint(Point(1, 0));
	sprite3->setPosition(Vec2(955, 565));
	this->addChild(sprite3, 1);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//押注时间个位
	sprite4 = Sprite::create(green[0]);
	sprite4->setAnchorPoint(Point(1, 0));
	sprite4->setPosition(Vec2(928, 530));
	this->addChild(sprite4, 1);
	//押注时间十位
	sprite5 = Sprite::create(green[0]);
	sprite5->setAnchorPoint(Point(1, 0));
	sprite5->setPosition(Vec2(910, 530));
	sprite5->setVisible(false);
	this->addChild(sprite5, 1);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//闲庄最大压分个位
	sprite6 = Sprite::create(red[0]);
	sprite6->setAnchorPoint(Point(1, 0));
	sprite6->setPosition(Vec2(928, 530 - step));
	this->addChild(sprite6, 1);
	//闲庄最大压分十位
	sprite7 = Sprite::create(red[0]);
	sprite7->setAnchorPoint(Point(1, 0));
	sprite7->setPosition(Vec2(910, 530 - step));
	sprite7->setVisible(false);
	this->addChild(sprite7, 1);
	//闲庄最大压分百位
	sprite8 = Sprite::create(red[0]);
	sprite8->setAnchorPoint(Point(1, 0));
	sprite8->setPosition(Vec2(892, 530 - step));
	sprite8->setVisible(false);
	this->addChild(sprite8, 1);
	//闲庄最大压分千位
	sprite9 = Sprite::create(red[0]);
	sprite9->setAnchorPoint(Point(1, 0));
	sprite9->setPosition(Vec2(874, 530 - step));
	sprite9->setVisible(false);
	this->addChild(sprite9, 1);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//和最大压分个位
	sprite10 = Sprite::create(green[0]);
	sprite10->setAnchorPoint(Point(1, 0));
	sprite10->setPosition(Vec2(928, 530 - step * 2));
	sprite10->setVisible(true);
	this->addChild(sprite10, 1);
	//和最大压分十位
	sprite11 = Sprite::create(green[0]);
	sprite11->setAnchorPoint(Point(1, 0));
	sprite11->setPosition(Vec2(910, 530 - step * 2));
	sprite11->setVisible(false);
	this->addChild(sprite11, 1);
	//和最大压分百位
	sprite12 = Sprite::create(green[0]);
	sprite12->setAnchorPoint(Point(1, 0));
	sprite12->setPosition(Vec2(892, 530 - step * 2));
	sprite12->setVisible(false);
	this->addChild(sprite12, 1);
	//和最大压分千位
	sprite13 = Sprite::create(green[0]);
	sprite13->setAnchorPoint(Point(1, 0));
	sprite13->setPosition(Vec2(874, 530 - step * 2));
	sprite13->setVisible(false);
	this->addChild(sprite13, 1);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//其它最大压分个位
	sprite14 = Sprite::create(red[0]);
	sprite14->setAnchorPoint(Point(1, 0));
	sprite14->setPosition(Vec2(928, 530 - step * 3));
	this->addChild(sprite14, 1);
	//其它最大压分十位
	sprite15 = Sprite::create(red[0]);
	sprite15->setAnchorPoint(Point(1, 0));
	sprite15->setPosition(Vec2(910, 530 - step * 3));
	sprite15->setVisible(false);
	this->addChild(sprite15, 1);
	//其它最大压分百位
	sprite16 = Sprite::create(red[0]);
	sprite16->setAnchorPoint(Point(1, 0));
	sprite16->setPosition(Vec2(892, 530 - step * 3));
	sprite16->setVisible(false);
	this->addChild(sprite16, 1);
	//其它最大压分千位
	sprite17 = Sprite::create(red[0]);
	sprite17->setAnchorPoint(Point(1, 0));
	sprite17->setPosition(Vec2(874, 530 - step * 3));
	sprite17->setVisible(false);
	this->addChild(sprite17, 1);
	///////////////////////////////////////////////////////////////////////////////////////////////////////////
	//最小压分切换个位
	sprite18 = Sprite::create(green[0]);
	sprite18->setAnchorPoint(Point(1, 0));
	sprite18->setPosition(Vec2(928, 530 - step * 4));
	sprite18->setVisible(true);
	this->addChild(sprite18, 1);
	//最小压分切换十位
	sprite19 = Sprite::create(green[0]);
	sprite19->setAnchorPoint(Point(1, 0));
	sprite19->setPosition(Vec2(910, 530 - step * 4));
	sprite19->setVisible(false);
	this->addChild(sprite19, 1);
	//最小压分切换百位
	sprite20 = Sprite::create(green[0]);
	sprite20->setAnchorPoint(Point(1, 0));
	sprite20->setPosition(Vec2(892, 530 - step * 4));
	sprite20->setVisible(false);
	this->addChild(sprite20, 1);
	//最小压分切换千位
	sprite21 = Sprite::create(green[0]);
	sprite21->setAnchorPoint(Point(1, 0));
	sprite21->setPosition(Vec2(874, 530 - step * 4));
	sprite21->setVisible(false);
	this->addChild(sprite21, 1);
	///////////////////////////////////////////////////////////////////////////////////////////////////
	//机器摆放
	sprite22 = Sprite::create("ParameterAdjust/5.png");
	sprite22->setAnchorPoint(Point(1, 0));
	sprite22->setPosition(Vec2(955, 530 - step * 7));
	this->addChild(sprite22, 1);

	this->RegisterListener();

	scheduleUpdate();

	return true;
}
void ParameterAdjust::update(float dt) {
	if (KeyUp || KeyDown) {
		count_y = (count_y < 0) ? (count_y + 12) : (count_y % 12);
		if (count_y <= 8) {
			auto moveTo1 = MoveTo::create(0.1, Vec2(170, 565 - step * count_y));
			auto moveTo2 = MoveTo::create(0.1, Vec2(250, 565 - step * count_y));
			sprite1->runAction(moveTo1);
			sprite2->runAction(moveTo2);
		}
		else {
			auto moveTo1 = MoveTo::create(0.1, Vec2(170, 565 + 15 - step * (count_y + 1)));
			auto moveTo2 = MoveTo::create(0.1, Vec2(250, 565 + 15 - step * (count_y + 1)));
			sprite1->runAction(moveTo1);
			sprite2->runAction(moveTo2);
		}
		KeyUp = KeyDown = false;
	}
	else if (KeyLeft || KeyRight) {
		if (count_y == 0) {				//难度设置
			count_x[count_y] = (count_x[count_y] < 0) ? (count_x[count_y] + 5) : count_x[count_y] % 5;
			sprite3->setTexture(difficulty[count_x[count_y]]);
		}
		else if (count_y == 1) {		//押注时间, 取出个位十位分别判断，下面也是同理
			count_x[count_y] = (count_x[count_y] < 0) ? (count_x[count_y] + 100) : count_x[count_y] % 100;
			int TempFirst = count_x[count_y] % 10;
			int TempSecond = count_x[count_y] / 10;
			sprite4->setTexture(green[TempFirst]);
			if (TempSecond == 0)
				sprite5->setVisible(false);
			else {
				sprite5->setVisible(true);
				sprite5->setTexture(green[TempSecond]);
			}
		}
		else if (count_y == 2) {		//庄闲最大压分
			count_x[count_y] = (count_x[count_y] < 0) ? (count_x[count_y] + 100) : count_x[count_y] % 100;
			int TempFirst = count_x[count_y] % 10;
			int TempSecond = count_x[count_y] / 10;
			if (TempFirst == 0 && TempSecond == 0) {
				sprite7->setVisible(false);
				sprite8->setVisible(false);
				sprite9->setVisible(false);
			}
			else {
				sprite7->setVisible(true);
				sprite8->setVisible(true);
				sprite8->setTexture(red[TempFirst]);
				if (TempSecond == 0)
					sprite9->setVisible(false);
				else {
					sprite9->setVisible(true);
					sprite9->setTexture(red[TempSecond]);
				}
			}
		}
		else if (count_y == 3) {		//和最大押分
			count_x[count_y] = (count_x[count_y] < 0) ? (count_x[count_y] + 51) : count_x[count_y] % 51;
			int TempFirst = count_x[count_y] % 10;
			int TempSecond = count_x[count_y] / 10;
			if (TempFirst == 0 && TempSecond == 0) {
				sprite11->setVisible(false);
				sprite12->setVisible(false);
				sprite13->setVisible(false);
			}
			else {
				sprite11->setVisible(true);
				sprite12->setVisible(true);
				sprite12->setTexture(green[TempFirst]);
				if (TempSecond == 0)
					sprite13->setVisible(false);
				else {
					sprite13->setVisible(true);
					sprite13->setTexture(green[TempSecond]);
				}				
			}
		}
		else if (count_y == 4) {		//其他最大押分
			count_x[count_y] = (count_x[count_y] < 0) ? (count_x[count_y] + 51) : count_x[count_y] % 51;
			int TempFirst = count_x[count_y] % 10;
			int TempSecond = count_x[count_y] / 10;
			if (TempFirst == 0 && TempSecond == 0) {
				sprite15->setVisible(false);
				sprite16->setVisible(false);
				sprite17->setVisible(false);
			}
			else {
				sprite15->setVisible(true);
				sprite16->setVisible(true);
				sprite16->setTexture(red[TempFirst]);
				if (TempSecond == 0)
					sprite17->setVisible(false);
				else {
					sprite17->setVisible(true);
					sprite17->setTexture(red[TempSecond]);
				}
			}
		}
		else if (count_y == 5) {		//最小押分切换
			count_x[count_y] = (count_x[count_y] < 0) ? (count_x[count_y] + 6) : count_x[count_y] % 6;
			if (count_x[count_y] == 0) {
				sprite18->setTexture(green[0]);
				sprite19->setVisible(false);
				sprite20->setVisible(false);
				sprite21->setVisible(false);
			}
			else if (count_x[count_y] == 1) {
				sprite18->setTexture(green[1]);
				sprite19->setVisible(false);
				sprite20->setVisible(false);
				sprite21->setVisible(false);
			}
			else if (count_x[count_y] == 2) {
				sprite18->setTexture(green[0]);
				sprite19->setTexture(green[1]);
				sprite19->setVisible(true);
				sprite20->setVisible(false);
				sprite21->setVisible(false);
			}
			else if (count_x[count_y] == 3) {
				sprite18->setTexture(green[0]);
				sprite19->setTexture(green[0]);
				sprite20->setTexture(green[1]);
				sprite19->setVisible(true);
				sprite20->setVisible(true);
				sprite21->setVisible(false);
			}
			else if (count_x[count_y] == 4) {
				sprite18->setTexture(green[0]);
				sprite19->setTexture(green[0]);
				sprite20->setTexture(green[5]);
				sprite19->setVisible(true);
				sprite20->setVisible(true);
				sprite21->setVisible(false);
			}
			else if (count_x[count_y] == 5) {
				sprite18->setTexture(green[0]);
				sprite19->setTexture(green[0]);
				sprite20->setTexture(green[0]);
				sprite21->setTexture(green[1]);
				sprite19->setVisible(true);
				sprite20->setVisible(true);
				sprite21->setVisible(true);
			}
		}
		else if (count_y == 6) {			//倍数选择

		}
		else if (count_y == 7) {			//彩票比例

		}
		else if (count_y == 8) {			//机器摆放
			count_x[count_y] = (count_x[count_y] < 0) ? (count_x[count_y] + 2) : count_x[count_y] % 2;
			if (count_x[count_y] == 0)
				sprite22->setTexture("ParameterAdjust/5.png");
			else
				sprite22->setTexture("ParameterAdjust/13.png");
		}
		KeyLeft = KeyRight = false;
	}
	else if (KeyEnter) {		
		auto director = Director::getInstance();
		if (count_y == 9) {										//恢复为默认设置
			auto scene = ParameterAdjust::createScene();
			director->replaceScene(scene);
		}
		else if (count_y == 10) {								//保存并退出
			director->popScene();
		}
		else if (count_y == 11) {								//不保存退出
			director->popScene();
		}
		KeyEnter = false;
	}

}
////////////////////////////////////////----------解码调整----------///////////////////////////////////////////
Scene* DecodeAdjust::createScene() {
	auto scene = Scene::create();
	auto layer = DecodeAdjust::create();
	scene->addChild(layer);
	return scene;
}
bool DecodeAdjust::init() {
	if (!Layer::init()) {
		return false;
	}
	flag1 = false;
	memset(c, false, sizeof(c));
	memset(count, 0, sizeof(count));
	UpOrDown = 0;
	LeftOrRight = 0;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//建立常用图片地址索引
	green.push_back("ParameterAdjust/Number1/0_1.png");
	green.push_back("ParameterAdjust/Number1/0_2.png");
	green.push_back("ParameterAdjust/Number1/0_3.png");
	green.push_back("ParameterAdjust/Number1/0_4.png");
	green.push_back("ParameterAdjust/Number1/0_5.png");
	green.push_back("ParameterAdjust/Number1/0_6.png");
	green.push_back("ParameterAdjust/Number1/0_7.png");
	green.push_back("ParameterAdjust/Number1/0_8.png");
	green.push_back("ParameterAdjust/Number1/0_9.png");
	green.push_back("ParameterAdjust/Number1/0_10.png");
	red.push_back("ParameterAdjust/Number/0_1.png");
	red.push_back("ParameterAdjust/Number/0_2.png");
	red.push_back("ParameterAdjust/Number/0_3.png");
	red.push_back("ParameterAdjust/Number/0_4.png");
	red.push_back("ParameterAdjust/Number/0_5.png");
	red.push_back("ParameterAdjust/Number/0_6.png");
	red.push_back("ParameterAdjust/Number/0_7.png");
	red.push_back("ParameterAdjust/Number/0_8.png");
	red.push_back("ParameterAdjust/Number/0_9.png");
	red.push_back("ParameterAdjust/Number/0_10.png");

	Background1 = Sprite::create("DecodeAdjust/background.png");
	Background1->setAnchorPoint(Point(0, 1));
	Background1->setPosition(Vec2(0, visibleSize.height));
	float width1 = Background1->getContentSize().width;
	float height1 = Background1->getContentSize().height;
	Background1->setScaleX(visibleSize.width / width1);
	Background1->setScaleY(visibleSize.height / height1);
	this->addChild(Background1, 1);

	Background2 = Sprite::create("DecodeAdjust/parameter.png");
	Background2->setAnchorPoint(Point(0, 1));
	Background2->setPosition(Vec2(300, 600));
	this->addChild(Background2, 1);

	//指示当前选项图标--car
	sprite1 = Sprite::create("DecodeAdjust/car.png");
	sprite1->setAnchorPoint(Point(0, 0));
	sprite1->setPosition(Vec2(480, 170));
	this->addChild(sprite1, 1);

	//指示当前选线图标后的白色阴影
	sprite2 = Sprite::create("DecodeAdjust/di.png");
	sprite2->setAnchorPoint(Point(0, 0));
	sprite2->setPosition(Vec2(550, 170));
	this->addChild(sprite2, 1);

	//投币比例
	sprite3 = Sprite::create(red[0]);
	sprite3->setAnchorPoint(Point(1, 0));
	sprite3->setPosition(Vec2(950, 575));
	this->addChild(sprite3, 1);

	//场地类型
	sprite4 = Sprite::create("DecodeAdjust/04.png");
	sprite4->setAnchorPoint(Point(1, 0));
	sprite4->setPosition(Vec2(980, 565 - step));
	this->addChild(sprite4, 1);

	//打码天数
	sprite5 = Sprite::create(green[0]);
	sprite5->setAnchorPoint(Point(1, 0));
	sprite5->setPosition(Vec2(945, 575 - step * 2));
	this->addChild(sprite5, 1);

	//打码成功信息
	sprite6 = Sprite::create("DecodeAdjust/03.png");
	sprite6->setAnchorPoint(Point(1, 0));
	sprite6->setPosition(Vec2(980, 565 - step * 4));
	this->addChild(sprite6, 1);

	sprite7 = Sprite::create("DecodeAdjust/07.png");	//弹出输入解码条码框
	sprite7->setPosition(Vec2(640, 360));
	sprite8 = Sprite::create("DecodeAdjust/06.png");				//下划线
	sprite8->setPosition(Vec2(40, 110));
	sprite7->addChild(sprite8, 1);
	sprite9 = Sprite::create(red[0]);				//1
	sprite9->setPosition(Vec2(40, 130));
	sprite9->setScaleX(1.5);
	sprite9->setScaleY(1.5);
	sprite9->setVisible(false);
	sprite7->addChild(sprite9, 1);
	sprite10 = Sprite::create(red[0]);				//2
	sprite10->setPosition(Vec2(80, 130));
	sprite10->setScaleX(1.5);
	sprite10->setScaleY(1.5);
	sprite10->setVisible(false);
	sprite7->addChild(sprite10, 1);
	sprite11 = Sprite::create(red[0]);				//3
	sprite11->setPosition(Vec2(120, 130));
	sprite11->setScaleX(1.5);
	sprite11->setScaleY(1.5);
	sprite11->setVisible(false);
	sprite7->addChild(sprite11, 1);
	sprite12 = Sprite::create(red[0]);				//4
	sprite12->setPosition(Vec2(160, 130));
	sprite12->setScaleX(1.5);
	sprite12->setScaleY(1.5);
	sprite12->setVisible(false);
	sprite7->addChild(sprite12, 1);
	sprite13 = Sprite::create(red[0]);				//5
	sprite13->setPosition(Vec2(200, 130));
	sprite13->setScaleX(1.5);
	sprite13->setScaleY(1.5);
	sprite13->setVisible(false);
	sprite7->addChild(sprite13, 1);
	sprite14 = Sprite::create(red[0]);				//6
	sprite14->setPosition(Vec2(240, 130));
	sprite14->setScaleX(1.5);
	sprite14->setScaleY(1.5);
	sprite14->setVisible(false);
	sprite7->addChild(sprite14, 1);
	sprite15 = Sprite::create(red[0]);				//7
	sprite15->setPosition(Vec2(280, 130));
	sprite15->setScaleX(1.5);
	sprite15->setScaleY(1.5);
	sprite15->setVisible(false);
	sprite7->addChild(sprite15, 1);
	sprite16 = Sprite::create(red[0]);				//8
	sprite16->setPosition(Vec2(320, 130));
	sprite16->setScaleX(1.5);
	sprite16->setScaleY(1.5);
	sprite16->setVisible(false);
	sprite7->addChild(sprite16, 1);
	sprite17 = Sprite::create(red[0]);				//9
	sprite17->setPosition(Vec2(360, 130));
	sprite17->setScaleX(1.5);
	sprite17->setScaleY(1.5);
	sprite17->setVisible(false);
	sprite7->addChild(sprite17, 1);
	sprite18 = Sprite::create(red[0]);				//10
	sprite18->setPosition(Vec2(400, 130));
	sprite18->setScaleX(1.5);
	sprite18->setScaleY(1.5);
	sprite18->setVisible(false);
	sprite7->addChild(sprite18, 1);
	sprite19 = Sprite::create(red[0]);				//11
	sprite19->setPosition(Vec2(440, 130));
	sprite19->setScaleX(1.5);
	sprite19->setScaleY(1.5);
	sprite19->setVisible(false);
	sprite7->addChild(sprite19, 1);
	sprite20 = Sprite::create(red[0]);				//12
	sprite20->setPosition(Vec2(480, 130));
	sprite20->setScaleX(1.5);
	sprite20->setScaleY(1.5);
	sprite20->setVisible(false);
	sprite7->addChild(sprite20, 1);

	sprite7->setVisible(false);
	this->addChild(sprite7, 2);

	this->RegisterListener();
	scheduleUpdate();

	return true;
}
void DecodeAdjust::update(float dt) {
	if ((KeyUp || KeyDown) && !flag1) {
		count_y = (count_y < 0) ? (count_y + 2) : (count_y % 2);
		auto moveTo1 = MoveTo::create(0.1, Vec2(480, 170 - 75 * count_y));
		auto moveTo2 = MoveTo::create(0.1, Vec2(550, 170 - 75 * count_y));
		sprite1->runAction(moveTo1);
		sprite2->runAction(moveTo2);	
		KeyUp = KeyDown = false;
	}
	else if (KeyEnter && !flag1) {
		if (count_y == 0) {
			flag1 = true;				//弹出输入解码条码框
		}
		else if (count_y == 1) {
			auto director = Director::getInstance();
			director->popScene();
		}
		KeyEnter = false;
	}
	if (flag1) {
		sprite7->setVisible(true);
		if (LeftOrRight == 0) {			//第一位
			if (!c[0]) 					//判断第一位是否填写
				sprite9->setVisible(true);
			if (KeyUp) {
				c[0] = true;
				count[LeftOrRight] ++;
				if (count[LeftOrRight] > 9)
					count[LeftOrRight] %= 10;
				sprite9->setTexture(red[count[LeftOrRight]]);
				KeyUp = false;
			}
			else if (KeyDown) {
				c[0] = true;
				count[LeftOrRight] --;
				if (count[LeftOrRight] < 0)
					count[LeftOrRight] += 10;
				sprite9->setTexture(red[count[LeftOrRight]]);
				KeyDown = false;
			}
			else if (KeyRight) {
				if (c[0]) {
					LeftOrRight++;
					auto moveTo = MoveTo::create(0.01, Vec2(40 + 40 * LeftOrRight, 110));
					sprite8->runAction(moveTo);
				}
				KeyRight = false;
			}
		}
		else if (LeftOrRight == 1) {			//第二位
			if (!c[1])					//判断第二位是否填写
				sprite10->setVisible(true);
			if (KeyUp) {
				c[1] = true;
				count[LeftOrRight] ++;
				if (count[LeftOrRight] > 9)
					count[LeftOrRight] %= 10;
				sprite10->setTexture(red[count[LeftOrRight]]);
				KeyUp = false;
			}
			else if (KeyDown) {
				c[1] = true;
				count[LeftOrRight] --;
				if (count[LeftOrRight] < 0)
					count[LeftOrRight] += 10;
				sprite10->setTexture(red[count[LeftOrRight]]);
				KeyDown = false;
			}
			else if (KeyLeft) {
				LeftOrRight--;
				auto moveTo = MoveTo::create(0.01, Vec2(40 + 40 * LeftOrRight, 110));
				sprite8->runAction(moveTo);
				KeyLeft = false;
			}
			else if (KeyRight) {
				if (c[0] && c[1]) {
					LeftOrRight++;
					auto moveTo = MoveTo::create(0.01, Vec2(40 + 40 * LeftOrRight, 110));
					sprite8->runAction(moveTo);
				}
				KeyRight = false;
			}
		}
		else if (LeftOrRight == 2) {			//第3位
			if (!c[2])					//判断第3位是否填写
				sprite11->setVisible(true);
			if (KeyUp) {
				c[2] = true;
				count[LeftOrRight] ++;
				if (count[LeftOrRight] > 9)
					count[LeftOrRight] %= 10;
				sprite11->setTexture(red[count[LeftOrRight]]);
				KeyUp = false;
			}
			else if (KeyDown) {
				c[2] = true;
				count[LeftOrRight] --;
				if (count[LeftOrRight] < 0)
					count[LeftOrRight] += 10;
				sprite11->setTexture(red[count[LeftOrRight]]);
				KeyDown = false;
			}
			else if (KeyLeft) {
				LeftOrRight--;
				auto moveTo = MoveTo::create(0.01, Vec2(40 + 40 * LeftOrRight, 110));
				sprite8->runAction(moveTo);
				KeyLeft = false;
			}
			else if (KeyRight) {
				if (c[0] && c[1] && c[2]) {
					LeftOrRight++;
					auto moveTo = MoveTo::create(0.01, Vec2(40 + 40 * LeftOrRight, 110));
					sprite8->runAction(moveTo);
				}
				KeyRight = false;
			}
		}
		else if (LeftOrRight == 3) {			//第4位
			if (!c[3])					//判断第4位是否填写
				sprite12->setVisible(true);
			if (KeyUp) {
				c[3] = true;
				count[LeftOrRight] ++;
				if (count[LeftOrRight] > 9)
					count[LeftOrRight] %= 10;
				sprite12->setTexture(red[count[LeftOrRight]]);
				KeyUp = false;
			}
			else if (KeyDown) {
				c[3] = true;
				count[LeftOrRight] --;
				if (count[LeftOrRight] < 0)
					count[LeftOrRight] += 10;
				sprite12->setTexture(red[count[LeftOrRight]]);
				KeyDown = false;
			}
			else if (KeyLeft) {
				LeftOrRight--;
				auto moveTo = MoveTo::create(0.01, Vec2(40 + 40 * LeftOrRight, 110));
				sprite8->runAction(moveTo);
				KeyLeft = false;
			}
			else if (KeyRight) {
				if (c[0] && c[1] && c[2] && c[3]) {
					LeftOrRight++;
					auto moveTo = MoveTo::create(0.01, Vec2(40 + 40 * LeftOrRight, 110));
					sprite8->runAction(moveTo);
				}
				KeyRight = false;
			}
		}
		else if (LeftOrRight == 4) {			//第5位
			if (!c[4])					//判断第5位是否填写
				sprite13->setVisible(true);
			if (KeyUp) {
				c[4] = true;
				count[LeftOrRight] ++;
				if (count[LeftOrRight] > 9)
					count[LeftOrRight] %= 10;
				sprite13->setTexture(red[count[LeftOrRight]]);
				KeyUp = false;
			}
			else if (KeyDown) {
				c[4] = true;
				count[LeftOrRight] --;
				if (count[LeftOrRight] < 0)
					count[LeftOrRight] += 10;
				sprite13->setTexture(red[count[LeftOrRight]]);
				KeyDown = false;
			}
			else if (KeyLeft) {
				LeftOrRight--;
				auto moveTo = MoveTo::create(0.01, Vec2(40 + 40 * LeftOrRight, 110));
				sprite8->runAction(moveTo);
				KeyLeft = false;
			}
			else if (KeyRight) {
				if (c[0] && c[1] && c[2] && c[3] && c[4]) {
					LeftOrRight++;
					auto moveTo = MoveTo::create(0.01, Vec2(40 + 40 * LeftOrRight, 110));
					sprite8->runAction(moveTo);
				}
				KeyRight = false;
			}
		}
		else if (LeftOrRight == 5) {			//第6位
			if (!c[5])					//判断第6位是否填写
				sprite14->setVisible(true);
			if (KeyUp) {
				c[5] = true;
				count[LeftOrRight] ++;
				if (count[LeftOrRight] > 9)
					count[LeftOrRight] %= 10;
				sprite14->setTexture(red[count[LeftOrRight]]);
				KeyUp = false;
			}
			else if (KeyDown) {
				c[5] = true;
				count[LeftOrRight] --;
				if (count[LeftOrRight] < 0)
					count[LeftOrRight] += 10;
				sprite14->setTexture(red[count[LeftOrRight]]);
				KeyDown = false;
			}
			else if (KeyLeft) {
				LeftOrRight--;
				auto moveTo = MoveTo::create(0.01, Vec2(40 + 40 * LeftOrRight, 110));
				sprite8->runAction(moveTo);
				KeyLeft = false;
			}
			else if (KeyRight) {
				if (c[0] && c[1] && c[2] && c[3] && c[4] && c[5]) {
					LeftOrRight++;
					auto moveTo = MoveTo::create(0.01, Vec2(40 + 40 * LeftOrRight, 110));
					sprite8->runAction(moveTo);
				}
				KeyRight = false;
			}
		}
		else if (LeftOrRight == 6) {			//第7位
			if (!c[6])					//判断第7位是否填写
				sprite15->setVisible(true);
			if (KeyUp) {
				c[6] = true;
				count[LeftOrRight] ++;
				if (count[LeftOrRight] > 9)
					count[LeftOrRight] %= 10;
				sprite15->setTexture(red[count[LeftOrRight]]);
				KeyUp = false;
			}
			else if (KeyDown) {
				c[6] = true;
				count[LeftOrRight] --;
				if (count[LeftOrRight] < 0)
					count[LeftOrRight] += 10;
				sprite15->setTexture(red[count[LeftOrRight]]);
				KeyDown = false;
			}
			else if (KeyLeft) {
				LeftOrRight--;
				auto moveTo = MoveTo::create(0.01, Vec2(40 + 40 * LeftOrRight, 110));
				sprite8->runAction(moveTo);
				KeyLeft = false;
			}
			else if (KeyRight) {
				if (c[0] && c[1] && c[2] && c[3] && c[4] && c[5] && c[6]) {
					LeftOrRight++;
					auto moveTo = MoveTo::create(0.01, Vec2(40 + 40 * LeftOrRight, 110));
					sprite8->runAction(moveTo);
				}
				KeyRight = false;
			}
		}
		else if (LeftOrRight == 7) {			//第8位
			if (!c[7])					//判断第8位是否填写
				sprite16->setVisible(true);
			if (KeyUp) {
				c[7] = true;
				count[LeftOrRight] ++;
				if (count[LeftOrRight] > 9)
					count[LeftOrRight] %= 10;
				sprite16->setTexture(red[count[LeftOrRight]]);
				KeyUp = false;
			}
			else if (KeyDown) {
				c[7] = true;
				count[LeftOrRight] --;
				if (count[LeftOrRight] < 0)
					count[LeftOrRight] += 10;
				sprite16->setTexture(red[count[LeftOrRight]]);
				KeyDown = false;
			}
			else if (KeyLeft) {
				LeftOrRight--;
				auto moveTo = MoveTo::create(0.01, Vec2(40 + 40 * LeftOrRight, 110));
				sprite8->runAction(moveTo);
				KeyLeft = false;
			}
			else if (KeyRight) {
				if (c[0] && c[1] && c[2] && c[3] && c[4] && c[5] && c[6] && c[7]) {
					LeftOrRight++;
					auto moveTo = MoveTo::create(0.01, Vec2(40 + 40 * LeftOrRight, 110));
					sprite8->runAction(moveTo);
				}
				KeyRight = false;
			}
		}
		else if (LeftOrRight == 8) {			//第9位
			if (!c[8])					//判断第9位是否填写
				sprite17->setVisible(true);
			if (KeyUp) {
				c[8] = true;
				count[LeftOrRight] ++;
				if (count[LeftOrRight] > 9)
					count[LeftOrRight] %= 10;
				sprite17->setTexture(red[count[LeftOrRight]]);
				KeyUp = false;
			}
			else if (KeyDown) {
				c[8] = true;
				count[LeftOrRight] --;
				if (count[LeftOrRight] < 0)
					count[LeftOrRight] += 10;
				sprite17->setTexture(red[count[LeftOrRight]]);
				KeyDown = false;
			}
			else if (KeyLeft) {
				LeftOrRight--;
				auto moveTo = MoveTo::create(0.01, Vec2(40 + 40 * LeftOrRight, 110));
				sprite8->runAction(moveTo);
				KeyLeft = false;
			}
			else if (KeyRight) {
				if (c[0] && c[1] && c[2] && c[3] && c[4] && c[5] && c[6] && c[7] && c[8]) {
					LeftOrRight++;
					auto moveTo = MoveTo::create(0.01, Vec2(40 + 40 * LeftOrRight, 110));
					sprite8->runAction(moveTo);
				}
				KeyRight = false;
			}
		}
		else if (LeftOrRight == 9) {			//第10位
			if (!c[9])					//判断第10位是否填写
				sprite18->setVisible(true);
			if (KeyUp) {
				c[9] = true;
				count[LeftOrRight] ++;
				if (count[LeftOrRight] > 9)
					count[LeftOrRight] %= 10;
				sprite18->setTexture(red[count[LeftOrRight]]);
				KeyUp = false;
			}
			else if (KeyDown) {
				c[9] = true;
				count[LeftOrRight] --;
				if (count[LeftOrRight] < 0)
					count[LeftOrRight] += 10;
				sprite18->setTexture(red[count[LeftOrRight]]);
				KeyDown = false;
			}
			else if (KeyLeft) {
				LeftOrRight--;
				auto moveTo = MoveTo::create(0.01, Vec2(40 + 40 * LeftOrRight, 110));
				sprite8->runAction(moveTo);
				KeyLeft = false;
			}
			else if (KeyRight) {
				if (c[0] && c[1] && c[2] && c[3] && c[4] && c[5] && c[6] && c[7] && c[8] && c[9]) {
					LeftOrRight++;
					auto moveTo = MoveTo::create(0.01, Vec2(40 + 40 * LeftOrRight, 110));
					sprite8->runAction(moveTo);
				}
				KeyRight = false;
			}
		}
		else if (LeftOrRight == 10) {			//第11位
			if (!c[10])					//判断第11位是否填写
				sprite19->setVisible(true);
			if (KeyUp) {
				c[10] = true;
				count[LeftOrRight] ++;
				if (count[LeftOrRight] > 9)
					count[LeftOrRight] %= 10;
				sprite19->setTexture(red[count[LeftOrRight]]);
				KeyUp = false;
			}
			else if (KeyDown) {
				c[10] = true;
				count[LeftOrRight] --;
				if (count[LeftOrRight] < 0)
					count[LeftOrRight] += 10;
				sprite19->setTexture(red[count[LeftOrRight]]);
				KeyDown = false;
			}
			else if (KeyLeft) {
				LeftOrRight--;
				auto moveTo = MoveTo::create(0.01, Vec2(40 + 40 * LeftOrRight, 110));
				sprite8->runAction(moveTo);
				KeyLeft = false;
			}
			else if (KeyRight) {
				if (c[0] && c[1] && c[2] && c[3] && c[4] && c[5] && c[6] && c[7] && c[8] && c[9] && c[10]) {
					LeftOrRight++;
					auto moveTo = MoveTo::create(0.01, Vec2(40 + 40 * LeftOrRight, 110));
					sprite8->runAction(moveTo);
				}
				KeyRight = false;
			}
		}
		else if (LeftOrRight == 11) {			//第12位
			if (!c[11])					//判断第12位是否填写
				sprite20->setVisible(true);
			if (KeyUp) {
				c[11] = true;
				count[LeftOrRight] ++;
				if (count[LeftOrRight] > 9)
					count[LeftOrRight] %= 10;
				sprite20->setTexture(red[count[LeftOrRight]]);
				KeyUp = false;
			}
			else if (KeyDown) {
				c[11] = true;
				count[LeftOrRight] --;
				if (count[LeftOrRight] < 0)
					count[LeftOrRight] += 10;
				sprite20->setTexture(red[count[LeftOrRight]]);
				KeyDown = false;
			}
			else if (KeyLeft) {
				LeftOrRight--;
				auto moveTo = MoveTo::create(0.01, Vec2(40 + 40 * LeftOrRight, 110));
				sprite8->runAction(moveTo);
				KeyLeft = false;
			}
		}
		if (c[0] && c[1] && c[2] && c[3] && c[4] && c[5] && c[6] && c[7] && c[8] && c[9] && c[10] && c[11]) {
			if (KeyEnter) {				//输入完毕后确认

				KeyEnter = false;
			}
		}
	}
}
//////////////////////////////////////////----------查账----------/////////////////////////////////////////////
Scene* CheckAccount::createScene() {
	auto scene = Scene::create();
	auto layer = CheckAccount::create();
	scene->addChild(layer);
	return scene;
}
bool CheckAccount::init() {
	if (!Layer::init()) {
		return false;
	}
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	flag = false;	//初始化flag
	count = 0;
	//建立常用图片地址索引
	green.push_back("ParameterAdjust/Number1/0_1.png");
	green.push_back("ParameterAdjust/Number1/0_2.png");
	green.push_back("ParameterAdjust/Number1/0_3.png");
	green.push_back("ParameterAdjust/Number1/0_4.png");
	green.push_back("ParameterAdjust/Number1/0_5.png");
	green.push_back("ParameterAdjust/Number1/0_6.png");
	green.push_back("ParameterAdjust/Number1/0_7.png");
	green.push_back("ParameterAdjust/Number1/0_8.png");
	green.push_back("ParameterAdjust/Number1/0_9.png");
	green.push_back("ParameterAdjust/Number1/0_10.png");

	red.push_back("ParameterAdjust/Number/0_1.png");
	red.push_back("ParameterAdjust/Number/0_2.png");
	red.push_back("ParameterAdjust/Number/0_3.png");
	red.push_back("ParameterAdjust/Number/0_4.png");
	red.push_back("ParameterAdjust/Number/0_5.png");
	red.push_back("ParameterAdjust/Number/0_6.png");
	red.push_back("ParameterAdjust/Number/0_7.png");
	red.push_back("ParameterAdjust/Number/0_8.png");
	red.push_back("ParameterAdjust/Number/0_9.png");
	red.push_back("ParameterAdjust/Number/0_10.png");

	blue.push_back("CheckAccount/blue/0_1.png");
	blue.push_back("CheckAccount/blue/0_2.png");
	blue.push_back("CheckAccount/blue/0_3.png");
	blue.push_back("CheckAccount/blue/0_4.png");
	blue.push_back("CheckAccount/blue/0_5.png");
	blue.push_back("CheckAccount/blue/0_6.png");
	blue.push_back("CheckAccount/blue/0_7.png");
	blue.push_back("CheckAccount/blue/0_8.png");
	blue.push_back("CheckAccount/blue/0_9.png");
	blue.push_back("CheckAccount/blue/0_10.png");

	white.push_back("CheckAccount/white/0_1.png");
	white.push_back("CheckAccount/white/0_2.png");
	white.push_back("CheckAccount/white/0_3.png");
	white.push_back("CheckAccount/white/0_4.png");
	white.push_back("CheckAccount/white/0_5.png");
	white.push_back("CheckAccount/white/0_6.png");
	white.push_back("CheckAccount/white/0_7.png");
	white.push_back("CheckAccount/white/0_8.png");
	white.push_back("CheckAccount/white/0_9.png");
	white.push_back("CheckAccount/white/0_10.png");

	Background1 = Sprite::create("DecodeAdjust/background.png");
	Background1->setAnchorPoint(Point(0, 1));
	Background1->setPosition(Vec2(0, visibleSize.height));
	this->addChild(Background1, 1);

	Background2 = Sprite::create("CheckAccount/parameter.png");
	Background2->setAnchorPoint(Point(0.5, 0.5));
	Background2->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5));
	this->addChild(Background2, 1);

	//指示当前选项图标--car
	sprite1 = Sprite::create("DecodeAdjust/car.png");
	sprite1->setAnchorPoint(Point(0, 0));
	sprite1->setPosition(Vec2(1000, 100));
	this->addChild(sprite1, 1);

	//指示当前选线图标后的白色阴影
	sprite2 = Sprite::create("DecodeAdjust/di.png");
	sprite2->setAnchorPoint(Point(0, 0));
	sprite2->setPosition(Vec2(1100, 100));
	this->addChild(sprite2, 1);
	//分机账
	sprite3 = Sprite::create("CheckAccount/03.png");
	sprite3->setAnchorPoint(Point(0, 0));
	sprite3->setPosition(Vec2(1100, 100));
	this->addChild(sprite3, 1);
	//退出
	sprite4 = Sprite::create("CheckAccount/04.png");
	sprite4->setAnchorPoint(Point(0, 0));
	sprite4->setPosition(Vec2(1100, 50));
	this->addChild(sprite4, 1);
	/////////////////////////////////////////////////////////////    layer1
	//1-8号机
	layer1 = Layer::create();
	auto sprite1_0 = Sprite::create("CheckAccount/5.png");
	sprite1_0->setAnchorPoint(Point(0, 1));
	sprite1_0->setPosition(Vec2(0, 720));
	float width1 = sprite1_0->getContentSize().width;
	float height1 = sprite1_0->getContentSize().height;
	sprite1_0->setScaleX(visibleSize.width / width1);
	sprite1_0->setScaleY(visibleSize.height / height1);
	layer1->addChild(sprite1_0, 1);
	//第一页
	auto sprite1_1 = Sprite::create(white[1]);
	sprite1_1->setPosition(Vec2(1210, 690));
	layer1->addChild(sprite1_1, 1);
	//1-8的序号
	auto sprite1_2 = Sprite::create(white[1]);
	sprite1_2->setPosition(Vec2(150, 630));
	layer1->addChild(sprite1_2, 1);

	auto sprite1_3 = Sprite::create(white[2]);
	sprite1_3->setPosition(Vec2(460, 630));
	layer1->addChild(sprite1_3, 1);

	auto sprite1_4 = Sprite::create(white[3]);
	sprite1_4->setPosition(Vec2(770, 630));
	layer1->addChild(sprite1_4, 1);

	auto sprite1_5 = Sprite::create(white[4]);
	sprite1_5->setPosition(Vec2(1080, 630));
	layer1->addChild(sprite1_5, 1);

	auto sprite1_6 = Sprite::create(white[5]);
	sprite1_6->setPosition(Vec2(150, 325));
	layer1->addChild(sprite1_6, 1);

	auto sprite1_7 = Sprite::create(white[6]);
	sprite1_7->setPosition(Vec2(460, 325));
	layer1->addChild(sprite1_7, 1);

	auto sprite1_8 = Sprite::create(white[7]);
	sprite1_8->setPosition(Vec2(770, 325));
	layer1->addChild(sprite1_8, 1);

	auto sprite1_9 = Sprite::create(white[8]);
	sprite1_9->setPosition(Vec2(1080, 325));
	layer1->addChild(sprite1_9, 1);

	layer1->setVisible(false);
	this->addChild(layer1, 3);

	////////////////////////////////////////////////////////////    layer2
	//9-16号机
	layer2 = Layer::create();
	auto sprite2_0 = Sprite::create("CheckAccount/5.png");
	sprite2_0->setAnchorPoint(Point(0, 1));
	sprite2_0->setPosition(Vec2(0, 720));
	float width2 = sprite2_0->getContentSize().width;
	float height2 = sprite2_0->getContentSize().height;
	sprite2_0->setScaleX(visibleSize.width / width2);
	sprite2_0->setScaleY(visibleSize.height / height2);
	layer2->addChild(sprite2_0, 1);
	//第2页
	auto sprite2_1 = Sprite::create(white[2]);
	sprite2_1->setPosition(Vec2(1210, 690));
	layer2->addChild(sprite2_1, 1);
	//9-18的序号
	auto sprite2_2 = Sprite::create(white[9]);
	sprite2_2->setPosition(Vec2(150, 630));
	layer2->addChild(sprite2_2, 1);

	auto sprite2_3 = Sprite::create(white[0]);
	sprite2_3->setPosition(Vec2(460, 630));
	layer2->addChild(sprite2_3, 1);
	auto sprite2_3_1 = Sprite::create(white[1]);
	sprite2_3_1->setPosition(Vec2(445, 630));
	layer2->addChild(sprite2_3_1, 1);

	auto sprite2_4 = Sprite::create(white[1]);
	sprite2_4->setPosition(Vec2(770, 630));
	layer2->addChild(sprite2_4, 1);
	auto sprite2_4_1 = Sprite::create(white[1]);
	sprite2_4_1->setPosition(Vec2(755, 630));
	layer2->addChild(sprite2_4_1, 1);

	auto sprite2_5 = Sprite::create(white[2]);
	sprite2_5->setPosition(Vec2(1080, 630));
	layer2->addChild(sprite2_5, 1);
	auto sprite2_5_1 = Sprite::create(white[1]);
	sprite2_5_1->setPosition(Vec2(1065, 630));
	layer2->addChild(sprite2_5_1, 1);

	auto sprite2_6 = Sprite::create(white[3]);
	sprite2_6->setPosition(Vec2(150, 325));
	layer2->addChild(sprite2_6, 1);
	auto sprite2_6_1 = Sprite::create(white[1]);
	sprite2_6_1->setPosition(Vec2(135, 325));
	layer2->addChild(sprite2_6_1, 1);

	auto sprite2_7 = Sprite::create(white[4]);
	sprite2_7->setPosition(Vec2(460, 325));
	layer2->addChild(sprite2_7, 1);
	auto sprite2_7_1 = Sprite::create(white[1]);
	sprite2_7_1->setPosition(Vec2(445, 325));
	layer2->addChild(sprite2_7_1, 1);

	auto sprite2_8 = Sprite::create(white[5]);
	sprite2_8->setPosition(Vec2(770, 325));
	layer2->addChild(sprite2_8, 1);
	auto sprite2_8_1 = Sprite::create(white[1]);
	sprite2_8_1->setPosition(Vec2(755, 325));
	layer2->addChild(sprite2_8_1, 1);

	auto sprite2_9 = Sprite::create(white[6]);
	sprite2_9->setPosition(Vec2(1080, 325));
	layer2->addChild(sprite2_9, 1);
	auto sprite2_9_1 = Sprite::create(white[1]);
	sprite2_9_1->setPosition(Vec2(1065, 325));
	layer2->addChild(sprite2_9_1, 1);

	layer2->setVisible(false);
	this->addChild(layer2, 3);

	this->RegisterListener();
	scheduleUpdate();

	return true;
}
void CheckAccount::update(float dt) {
	if ((KeyUp || KeyDown) && !flag) {
		count_y = (count_y < 0) ? (count_y + 2) : (count_y % 2);
		auto moveTo1 = MoveTo::create(0.1, Vec2(1000, 100 - 50 * count_y));
		auto moveTo2 = MoveTo::create(0.1, Vec2(1100, 100 - 50 * count_y));
		sprite1->runAction(moveTo1);
		sprite2->runAction(moveTo2);
		KeyUp = KeyDown = false;
	}
	else if (KeyEnter && !flag) {
		if (count_y == 0) {
			layer1->setVisible(true);
			flag = true;
		}
		else if (count_y == 1) {
			auto director = Director::getInstance();
			director->popScene();
		}
		KeyEnter = false;
	}
	if (flag) {
		if (KeyUp) {
			count--;
			count = (count < 0) ? (count + 2) : count;
		}
		else if (KeyDown) {
			count++;
			count = (count > 1) ? (count % 2) : count;
		}
		if (count == 0) {
			layer1->setVisible(true);
			layer2->setVisible(false);
		}
		else {
			layer1->setVisible(false);
			layer2->setVisible(true);
		}
		if (KeyEnter) {
			layer1->setVisible(false);
			layer2->setVisible(false);
			flag = false;
		}
		KeyUp = KeyDown = KeyEnter = false;
	}
}
//////////////////////////////////////////----------报账----------/////////////////////////////////////////////
Scene* ReportAccount::createScene() {
	auto scene = Scene::create();
	auto layer = ReportAccount::create();
	scene->addChild(layer);
	return scene;
}
bool ReportAccount::init() {
	if (!Layer::init()) {
		return false;
	}
	flag1 = true;
	flag2 = flag3 = false;		//初始化三个页面是否打开的标志位。
	memset(c, false, sizeof(c));
	memset(count, 0, sizeof(count));
	UpOrDown = 0;
	LeftOrRight = 0;
	red.push_back("ReportAccount/reportcode/red/0_1.png");
	red.push_back("ReportAccount/reportcode/red/0_2.png");
	red.push_back("ReportAccount/reportcode/red/0_3.png");
	red.push_back("ReportAccount/reportcode/red/0_4.png");
	red.push_back("ReportAccount/reportcode/red/0_5.png");
	red.push_back("ReportAccount/reportcode/red/0_6.png");
	red.push_back("ReportAccount/reportcode/red/0_7.png");
	red.push_back("ReportAccount/reportcode/red/0_8.png");
	red.push_back("ReportAccount/reportcode/red/0_9.png");
	red.push_back("ReportAccount/reportcode/red/0_10.png");
	blue.push_back("ReportAccount/reportcode/blue/0_1.png");
	blue.push_back("ReportAccount/reportcode/blue/0_2.png");
	blue.push_back("ReportAccount/reportcode/blue/0_3.png");
	blue.push_back("ReportAccount/reportcode/blue/0_4.png");
	blue.push_back("ReportAccount/reportcode/blue/0_5.png");
	blue.push_back("ReportAccount/reportcode/blue/0_6.png");
	blue.push_back("ReportAccount/reportcode/blue/0_7.png");
	blue.push_back("ReportAccount/reportcode/blue/0_8.png");
	blue.push_back("ReportAccount/reportcode/blue/0_9.png");
	blue.push_back("ReportAccount/reportcode/blue/0_10.png");
	green.push_back("ReportAccount/reportcode/green/0_1.png");
	green.push_back("ReportAccount/reportcode/green/0_2.png");
	green.push_back("ReportAccount/reportcode/green/0_3.png");
	green.push_back("ReportAccount/reportcode/green/0_4.png");
	green.push_back("ReportAccount/reportcode/green/0_5.png");
	green.push_back("ReportAccount/reportcode/green/0_6.png");
	green.push_back("ReportAccount/reportcode/green/0_7.png");
	green.push_back("ReportAccount/reportcode/green/0_8.png");
	green.push_back("ReportAccount/reportcode/green/0_9.png");
	green.push_back("ReportAccount/reportcode/green/0_10.png");
	orange.push_back("ReportAccount/reportcode/orange/0_1.png");
	orange.push_back("ReportAccount/reportcode/orange/0_2.png");
	orange.push_back("ReportAccount/reportcode/orange/0_3.png");
	orange.push_back("ReportAccount/reportcode/orange/0_4.png");
	orange.push_back("ReportAccount/reportcode/orange/0_5.png");
	orange.push_back("ReportAccount/reportcode/orange/0_6.png");
	orange.push_back("ReportAccount/reportcode/orange/0_7.png");
	orange.push_back("ReportAccount/reportcode/orange/0_8.png");
	orange.push_back("ReportAccount/reportcode/orange/0_9.png");
	orange.push_back("ReportAccount/reportcode/orange/0_10.png");
	purple.push_back("ReportAccount/reportcode/purple/0_1.png");
	purple.push_back("ReportAccount/reportcode/purple/0_2.png");
	purple.push_back("ReportAccount/reportcode/purple/0_3.png");
	purple.push_back("ReportAccount/reportcode/purple/0_4.png");
	purple.push_back("ReportAccount/reportcode/purple/0_5.png");
	purple.push_back("ReportAccount/reportcode/purple/0_6.png");
	purple.push_back("ReportAccount/reportcode/purple/0_7.png");
	purple.push_back("ReportAccount/reportcode/purple/0_8.png");
	purple.push_back("ReportAccount/reportcode/purple/0_9.png");
	purple.push_back("ReportAccount/reportcode/purple/0_10.png");

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//背景图片
	Background1 = Sprite::create("Setting/SettingParameter/3.png");
	Background1->setAnchorPoint(Point(0, 1));
	Background1->setPosition(Vec2(origin.x + 0, origin.y + visibleSize.height));
	float width1 = Background1->getContentSize().width;
	float height1 = Background1->getContentSize().height;
	Background1->setScaleX(visibleSize.width / width1);
	Background1->setScaleY(visibleSize.height / height1);
	this->addChild(Background1, 0);
	//对话框
	sprite1 = Sprite::create("ReportAccount/isreport/02.png");
	sprite1->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5));
	this->addChild(sprite1, 1);
	//是
	sprite2 = Sprite::create("ReportAccount/isreport/yes.png");
	sprite2->setAnchorPoint(Point(0, 0));
	sprite2->setPosition(Vec2(visibleSize.width * 0.5 - 150, visibleSize.height * 0.5));
	this->addChild(sprite2, 2);
	//否
	sprite3 = Sprite::create("ReportAccount/isreport/no.png");
	sprite3->setAnchorPoint(Point(0, 0));
	sprite3->setPosition(Vec2(visibleSize.width * 0.5 + 100, visibleSize.height * 0.5));
	this->addChild(sprite3, 2);
	//car
	sprite4 = Sprite::create("ReportAccount/isreport/car.png");
	sprite4->setAnchorPoint(Point(0, 0));
	sprite4->setPosition(Vec2(visibleSize.width * 0.5 - 220, visibleSize.height * 0.5));
	this->addChild(sprite4, 1);
	//阴影
	sprite5 = Sprite::create("Setting/SettingParameter/1.png");
	sprite5->setAnchorPoint(Point(0, 0));
	sprite5->setPosition(Vec2(visibleSize.width * 0.5 - 150, visibleSize.height * 0.5));
	this->addChild(sprite5, 1);

	//确认报账后的第一个界面
	layer1 = Layer::create();
	//背景图片
	Background2 = Sprite::create("Setting/SettingParameter/3.png");
	Background2->setAnchorPoint(Point(0, 1));
	Background2->setPosition(Vec2(origin.x + 0, origin.y + visibleSize.height));
	float width2 = Background2->getContentSize().width;
	float height2 = Background2->getContentSize().height;
	Background2->setScaleX(visibleSize.width / width2);
	Background2->setScaleY(visibleSize.height / height2);
	layer1->addChild(Background2, 0);
	sprite6 = Sprite::create("ReportAccount/reportselect/2.png");		//直接延时
	sprite6->setAnchorPoint(Point(0, 0));
	sprite6->setPosition(Vec2(600, 550));
	layer1->addChild(sprite6, 1);
	sprite7 = Sprite::create("ReportAccount/reportselect/3.png");		//打码报账
	sprite7->setAnchorPoint(Point(0, 0));
	sprite7->setPosition(Vec2(600, 450));
	layer1->addChild(sprite7, 1);
	//car
	sprite8 = Sprite::create("ReportAccount/isreport/car.png");
	sprite8->setAnchorPoint(Point(0, 0));
	sprite8->setPosition(Vec2(530, 550));
	layer1->addChild(sprite8, 1);
	//阴影
	sprite9 = Sprite::create("Setting/SettingParameter/1.png");
	sprite9->setAnchorPoint(Point(0, 0));
	sprite9->setPosition(Vec2(600, 550));
	layer1->addChild(sprite9, 0);
	layer1->setVisible(false);				//初始隐藏该界面
	this->addChild(layer1, 3);

	//打码报账界面
	layer2 = Layer::create();
	//背景图片
	Background3 = Sprite::create("Setting/SettingParameter/3.png");
	Background3->setAnchorPoint(Point(0, 1));
	Background3->setPosition(Vec2(origin.x + 0, origin.y + visibleSize.height));
	float width3 = Background3->getContentSize().width;
	float height3 = Background3->getContentSize().height;
	Background3->setScaleX(visibleSize.width / width3);
	Background3->setScaleY(visibleSize.height / height3);
	layer2->addChild(Background3, 0);

	sprite10 = Sprite::create("ReportAccount/reportcode/02.png");		// 1
	sprite10->setAnchorPoint(Point(0, 0));
	sprite10->setPosition(Vec2(450, 610));
	layer2->addChild(sprite10, 1);
	sprite11 = Sprite::create("ReportAccount/reportcode/03.png");		// 2
	sprite11->setAnchorPoint(Point(0, 0));
	sprite11->setPosition(Vec2(450, 570));
	layer2->addChild(sprite11, 1);
	sprite12 = Sprite::create("ReportAccount/reportcode/04.png");		// 3
	sprite12->setAnchorPoint(Point(0, 0));
	sprite12->setPosition(Vec2(450, 530));
	layer2->addChild(sprite12, 1);
	sprite13 = Sprite::create("ReportAccount/reportcode/05.png");		// 4
	sprite13->setAnchorPoint(Point(0, 0));
	sprite13->setPosition(Vec2(450, 490));
	layer2->addChild(sprite13, 1);
	sprite14 = Sprite::create("ReportAccount/reportcode/06.png");		// 5
	sprite14->setAnchorPoint(Point(0, 0));
	sprite14->setPosition(Vec2(450, 450));
	layer2->addChild(sprite14, 1);
	sprite15 = Sprite::create("ReportAccount/reportcode/01.png");		// 输入条码框
	sprite15->setAnchorPoint(Point(0, 1));
	sprite15->setPosition(Vec2(395, 440));
	sprite15->setScaleY(0.85);
	layer2->addChild(sprite15, 1);

	sprite16 = Sprite::create("ReportAccount/reportcode/1.png");		//下划线
	sprite16->setAnchorPoint(Point(0, 1));
	sprite16->setPosition(Vec2(20, 200));
	sprite15->addChild(sprite16, 2);
	sprite17 = Sprite::create(red[0]);				//第一位
	sprite17->setPosition(Vec2(35, 225));
	sprite17->setScaleX(2);
	sprite17->setScaleY(2);
	sprite17->setVisible(false);
	sprite15->addChild(sprite17, 2);
	sprite18 = Sprite::create(red[0]);				//第二位
	sprite18->setPosition(Vec2(105, 225));
	sprite18->setScaleX(2);
	sprite18->setScaleY(2);
	sprite18->setVisible(false);
	sprite15->addChild(sprite18, 2);
	sprite19 = Sprite::create(red[0]);				//第三位
	sprite19->setPosition(Vec2(175, 225));
	sprite19->setScaleX(2);
	sprite19->setScaleY(2);
	sprite19->setVisible(false);
	sprite15->addChild(sprite19, 2);
	sprite20 = Sprite::create(red[0]);				//第四位
	sprite20->setPosition(Vec2(245, 225));
	sprite20->setScaleX(2);
	sprite20->setScaleY(2);
	sprite20->setVisible(false);
	sprite15->addChild(sprite20, 2);
	sprite21 = Sprite::create(red[0]);				//第五位
	sprite21->setPosition(Vec2(315, 225));
	sprite21->setScaleX(2);
	sprite21->setScaleY(2);
	sprite21->setVisible(false);
	sprite15->addChild(sprite21, 2);
	sprite22 = Sprite::create(red[0]);				//第六位
	sprite22->setPosition(Vec2(385, 225));
	sprite22->setScaleX(2);
	sprite22->setScaleY(2);
	sprite22->setVisible(false);
	sprite15->addChild(sprite22, 2);
	sprite23 = Sprite::create(red[0]);				//第七位
	sprite23->setPosition(Vec2(455, 225));
	sprite23->setScaleX(2);
	sprite23->setScaleY(2);
	sprite23->setVisible(false);
	sprite15->addChild(sprite23, 2);
	sprite24 = Sprite::create(red[0]);				//第8位
	sprite24->setPosition(Vec2(525, 225));
	sprite24->setScaleX(2);
	sprite24->setScaleY(2);
	sprite24->setVisible(false);
	sprite15->addChild(sprite24, 2);


	layer2->setVisible(false);
	this->addChild(layer2, 3);

	this->RegisterListener();
	scheduleUpdate();

	return true;
}
void ReportAccount::update(float dt) {
	if (flag1) {
		if (KeyLeft || KeyRight) {
			count_x[count_y] = (count_x[count_y] < 0) ? (count_x[count_y] + 2) : (count_x[count_y] % 2);
			auto moveTo1 = MoveTo::create(0.1, Vec2(420 + 250 * count_x[count_y], 360));
			auto moveTo2 = MoveTo::create(0.1, Vec2(490 + 250 * count_x[count_y], 360));
			sprite4->runAction(moveTo1);
			sprite5->runAction(moveTo2);
			KeyLeft = KeyRight = false;
		}
		else if (KeyEnter) {
			if (count_x[count_y] == 1) {				//不报账
				auto director = Director::getInstance();
				director->popScene();
			}
			else if (count_x[count_y] == 0) {			//报账
				flag2 = true;
				layer1->setVisible(true);				//显示
			}
			count_x[count_y] = 0;
			flag1 = false;
			KeyEnter = false;
		}
	}
	else if (flag2) {
		if (KeyUp || KeyDown) {
			count_y = (count_y < 0) ? (count_y + 2) : (count_y % 2);
			auto moveTo1 = MoveTo::create(0.1, Vec2(530, 550 - count_y * 100));
			auto moveTo2 = MoveTo::create(0.1, Vec2(600, 550 - count_y * 100));
			sprite8->runAction(moveTo1);
			sprite9->runAction(moveTo2);
			KeyUp = KeyDown = false;
		}
		else if (KeyEnter) {
			if (count_y == 0) {

			}
			else if (count_y == 1) {

				layer2->setVisible(true);
				flag3 = true;
			}
			count_y = 0;
			layer1->setVisible(false);
			flag2 = false;
			KeyEnter = false;
		}
	}
	else if (flag3) {
		if (LeftOrRight == 0) {			//第一位
			if (!c[0]) 					//判断第一位是否填写
				sprite17->setVisible(true);
			if (KeyUp) {
				c[0] = true;
				count[LeftOrRight] ++;
				if (count[LeftOrRight] > 9)
					count[LeftOrRight] %= 10;
				sprite17->setTexture(red[count[LeftOrRight]]);
				KeyUp = false;
			}
			else if (KeyDown) {
				c[0] = true;
				count[LeftOrRight] --;
				if (count[LeftOrRight] < 0)
					count[LeftOrRight] += 10;
				sprite17->setTexture(red[count[LeftOrRight]]);
				KeyDown = false;
			}
			else if (KeyRight) {
				if (c[0]) {
					LeftOrRight++;
					auto moveTo = MoveTo::create(0.01, Vec2(20 + 70 * LeftOrRight, 200));
					sprite16->runAction(moveTo);
				}
				KeyRight = false;
			}
		}
		else if (LeftOrRight == 1) {			//第二位
			if (!c[1])					//判断第二位是否填写
				sprite18->setVisible(true);
			if (KeyUp) {
				c[1] = true;
				count[LeftOrRight] ++;
				if (count[LeftOrRight] > 9)
					count[LeftOrRight] %= 10;
				sprite18->setTexture(red[count[LeftOrRight]]);
				KeyUp = false;
			}
			else if (KeyDown) {
				c[1] = true;
				count[LeftOrRight] --;
				if (count[LeftOrRight] < 0)
					count[LeftOrRight] += 10;
				sprite18->setTexture(red[count[LeftOrRight]]);
				KeyDown = false;
			}
			else if (KeyLeft) {
				LeftOrRight--;
				auto moveTo = MoveTo::create(0.01, Vec2(20 + 70 * LeftOrRight, 200));
				sprite16->runAction(moveTo);
				KeyLeft = false;
			}
			else if (KeyRight) {
				if (c[0] && c[1]) {
					LeftOrRight++;
					auto moveTo = MoveTo::create(0.01, Vec2(20 + 70 * LeftOrRight, 200));
					sprite16->runAction(moveTo);
				}
				KeyRight = false;
			}
		}
		else if (LeftOrRight == 2) {			//第3位
			if (!c[2])					//判断第3位是否填写
				sprite19->setVisible(true);
			if (KeyUp) {
				c[2] = true;
				count[LeftOrRight] ++;
				if (count[LeftOrRight] > 9)
					count[LeftOrRight] %= 10;
				sprite19->setTexture(red[count[LeftOrRight]]);
				KeyUp = false;
			}
			else if (KeyDown) {
				c[2] = true;
				count[LeftOrRight] --;
				if (count[LeftOrRight] < 0)
					count[LeftOrRight] += 10;
				sprite19->setTexture(red[count[LeftOrRight]]);
				KeyDown = false;
			}
			else if (KeyLeft) {
				LeftOrRight--;
				auto moveTo = MoveTo::create(0.01, Vec2(20 + 70 * LeftOrRight, 200));
				sprite16->runAction(moveTo);
				KeyLeft = false;
			}
			else if (KeyRight) {
				if (c[0] && c[1] && c[2]) {
					LeftOrRight++;
					auto moveTo = MoveTo::create(0.01, Vec2(20 + 70 * LeftOrRight, 200));
					sprite16->runAction(moveTo);
				}
				KeyRight = false;
			}
		}
		else if (LeftOrRight == 3) {			//第4位
			if (!c[3])					//判断第4位是否填写
				sprite20->setVisible(true);
			if (KeyUp) {
				c[3] = true;
				count[LeftOrRight] ++;
				if (count[LeftOrRight] > 9)
					count[LeftOrRight] %= 10;
				sprite20->setTexture(red[count[LeftOrRight]]);
				KeyUp = false;
			}
			else if (KeyDown) {
				c[3] = true;
				count[LeftOrRight] --;
				if (count[LeftOrRight] < 0)
					count[LeftOrRight] += 10;
				sprite20->setTexture(red[count[LeftOrRight]]);
				KeyDown = false;
			}
			else if (KeyLeft) {
				LeftOrRight--;
				auto moveTo = MoveTo::create(0.01, Vec2(20 + 70 * LeftOrRight, 200));
				sprite16->runAction(moveTo);
				KeyLeft = false;
			}
			else if (KeyRight) {
				if (c[0] && c[1] && c[2] && c[3]) {
					LeftOrRight++;
					auto moveTo = MoveTo::create(0.01, Vec2(20 + 70 * LeftOrRight, 200));
					sprite16->runAction(moveTo);
				}
				KeyRight = false;
			}
		}
		else if (LeftOrRight == 4) {			//第5位
			if (!c[4])					//判断第5位是否填写
				sprite21->setVisible(true);
			if (KeyUp) {
				c[4] = true;
				count[LeftOrRight] ++;
				if (count[LeftOrRight] > 9)
					count[LeftOrRight] %= 10;
				sprite21->setTexture(red[count[LeftOrRight]]);
				KeyUp = false;
			}
			else if (KeyDown) {
				c[4] = true;
				count[LeftOrRight] --;
				if (count[LeftOrRight] < 0)
					count[LeftOrRight] += 10;
				sprite21->setTexture(red[count[LeftOrRight]]);
				KeyDown = false;
			}
			else if (KeyLeft) {
				LeftOrRight--;
				auto moveTo = MoveTo::create(0.01, Vec2(20 + 70 * LeftOrRight, 200));
				sprite16->runAction(moveTo);
				KeyLeft = false;
			}
			else if (KeyRight) {
				if (c[0] && c[1] && c[2] && c[3] && c[4]) {
					LeftOrRight++;
					auto moveTo = MoveTo::create(0.01, Vec2(20 + 70 * LeftOrRight, 200));
					sprite16->runAction(moveTo);
				}
				KeyRight = false;
			}
		}
		else if (LeftOrRight == 5) {			//第6位
			if (!c[5])					//判断第6位是否填写
				sprite22->setVisible(true);
			if (KeyUp) {
				c[5] = true;
				count[LeftOrRight] ++;
				if (count[LeftOrRight] > 9)
					count[LeftOrRight] %= 10;
				sprite22->setTexture(red[count[LeftOrRight]]);
				KeyUp = false;
			}
			else if (KeyDown) {
				c[5] = true;
				count[LeftOrRight] --;
				if (count[LeftOrRight] < 0)
					count[LeftOrRight] += 10;
				sprite22->setTexture(red[count[LeftOrRight]]);
				KeyDown = false;
			}
			else if (KeyLeft) {
				LeftOrRight--;
				auto moveTo = MoveTo::create(0.01, Vec2(20 + 70 * LeftOrRight, 200));
				sprite16->runAction(moveTo);
				KeyLeft = false;
			}
			else if (KeyRight) {
				if (c[0] && c[1] && c[2] && c[3] && c[4] && c[5]) {
					LeftOrRight++;
					auto moveTo = MoveTo::create(0.01, Vec2(20 + 70 * LeftOrRight, 200));
					sprite16->runAction(moveTo);
				}
				KeyRight = false;
			}
		}
		else if (LeftOrRight == 6) {			//第7位
			if (!c[6])					//判断第7位是否填写
				sprite23->setVisible(true);
			if (KeyUp) {
				c[6] = true;
				count[LeftOrRight] ++;
				if (count[LeftOrRight] > 9)
					count[LeftOrRight] %= 10;
				sprite23->setTexture(red[count[LeftOrRight]]);
				KeyUp = false;
			}
			else if (KeyDown) {
				c[6] = true;
				count[LeftOrRight] --;
				if (count[LeftOrRight] < 0)
					count[LeftOrRight] += 10;
				sprite23->setTexture(red[count[LeftOrRight]]);
				KeyDown = false;
			}
			else if (KeyLeft) {
				LeftOrRight--;
				auto moveTo = MoveTo::create(0.01, Vec2(20 + 70 * LeftOrRight, 200));
				sprite16->runAction(moveTo);
				KeyLeft = false;
			}
			else if (KeyRight) {
				if (c[0] && c[1] && c[2] && c[3] && c[4] && c[5] && c[6]) {
					LeftOrRight++;
					auto moveTo = MoveTo::create(0.01, Vec2(20 + 70 * LeftOrRight, 200));
					sprite16->runAction(moveTo);
				}
				KeyRight = false;
			}
		}
		else if (LeftOrRight == 7) {			//第8位
			if (!c[7])					//判断第7位是否填写
				sprite24->setVisible(true);
			if (KeyUp) {
				c[7] = true;
				count[LeftOrRight] ++;
				if (count[LeftOrRight] > 9)
					count[LeftOrRight] %= 10;
				sprite24->setTexture(red[count[LeftOrRight]]);
				KeyUp = false;
			}
			else if (KeyDown) {
				c[7] = true;
				count[LeftOrRight] --;
				if (count[LeftOrRight] < 0)
					count[LeftOrRight] += 10;
				sprite24->setTexture(red[count[LeftOrRight]]);
				KeyDown = false;
			}
			else if (KeyLeft) {
				LeftOrRight--;
				auto moveTo = MoveTo::create(0.01, Vec2(20 + 70 * LeftOrRight, 200));
				sprite16->runAction(moveTo);
				KeyLeft = false;
			}
			else if (KeyEnter) {		//全部输入，确认键
				if (c[0] && c[1] && c[2] && c[3] && c[4] && c[5] && c[6] && c[7]) {
					sprite15->setVisible(false);			//隐藏输入条码框
					auto sprite15_0 = Sprite::create("ReportAccount/reportcode/inputcode.png");
					sprite15_0->setAnchorPoint(Point(0, 1));
					sprite15_0->setPosition(Vec2(445, 440));
					layer2->addChild(sprite15_0, 2);
					//显示条码1到8位
					auto sprite15_1 = Sprite::create(red[count[0]]);
					sprite15_1->setPosition(Vec2(620, 420));
					sprite15_1->setScaleX(2);
					sprite15_1->setScaleY(2);
					layer2->addChild(sprite15_1, 2);
					auto sprite15_2 = Sprite::create(red[count[1]]);
					sprite15_2->setPosition(Vec2(655, 420));
					sprite15_2->setScaleX(2);
					sprite15_2->setScaleY(2);
					layer2->addChild(sprite15_2, 2);
					auto sprite15_3 = Sprite::create(red[count[2]]);
					sprite15_3->setPosition(Vec2(690, 420));
					sprite15_3->setScaleX(2);
					sprite15_3->setScaleY(2);
					layer2->addChild(sprite15_3, 2);
					auto sprite15_4 = Sprite::create(red[count[3]]);
					sprite15_4->setPosition(Vec2(725, 420));
					sprite15_4->setScaleX(2);
					sprite15_4->setScaleY(2);
					layer2->addChild(sprite15_4, 2);
					auto sprite15_5 = Sprite::create(red[count[4]]);
					sprite15_5->setPosition(Vec2(760, 420));
					sprite15_5->setScaleX(2);
					sprite15_5->setScaleY(2);
					layer2->addChild(sprite15_5, 2);
					auto sprite15_6 = Sprite::create(red[count[5]]);
					sprite15_6->setPosition(Vec2(795, 420));
					sprite15_6->setScaleX(2);
					sprite15_6->setScaleY(2);
					layer2->addChild(sprite15_6, 2);
					auto sprite15_7 = Sprite::create(red[count[6]]);
					sprite15_7->setPosition(Vec2(830, 420));
					sprite15_7->setScaleX(2);
					sprite15_7->setScaleY(2);
					layer2->addChild(sprite15_7, 2);
					auto sprite15_8 = Sprite::create(red[count[7]]);
					sprite15_8->setPosition(Vec2(865, 420));
					sprite15_8->setScaleX(2);
					sprite15_8->setScaleY(2);
					layer2->addChild(sprite15_8, 2);
					//正在处理中，请稍后
					auto sprite15_9 = Sprite::create("ReportAccount/reportcode/08.png");
					sprite15_9->setAnchorPoint(Point(0, 1));
					sprite15_9->setPosition(Vec2(550, 350));
					layer2->addChild(sprite15_9, 2);
				}
				KeyEnter = false;
			}
		}
	}
	
}
////////////////////////////////////////----------系统设置----------///////////////////////////////////////////
Scene* SystemSetting::createScene() {
	auto scene = Scene::create();
	auto layer = SystemSetting::create();
	scene->addChild(layer);
	return scene;
}
bool SystemSetting::init() {
	if (!Layer::init()) {
		return false;
	}
	memset(c, false, sizeof(c));
	memset(count, 0, sizeof(count));
	UpOrDown = 0;
	LeftOrRight = 0;
	red.push_back("ReportAccount/reportcode/red/0_1.png");
	red.push_back("ReportAccount/reportcode/red/0_2.png");
	red.push_back("ReportAccount/reportcode/red/0_3.png");
	red.push_back("ReportAccount/reportcode/red/0_4.png");
	red.push_back("ReportAccount/reportcode/red/0_5.png");
	red.push_back("ReportAccount/reportcode/red/0_6.png");
	red.push_back("ReportAccount/reportcode/red/0_7.png");
	red.push_back("ReportAccount/reportcode/red/0_8.png");
	red.push_back("ReportAccount/reportcode/red/0_9.png");
	red.push_back("ReportAccount/reportcode/red/0_10.png");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//背景图片
	Background1 = Sprite::create("Setting/SettingParameter/3.png");
	Background1->setAnchorPoint(Point(0, 1));
	Background1->setPosition(Vec2(origin.x + 0, origin.y + visibleSize.height));
	float width1 = Background1->getContentSize().width;
	float height1 = Background1->getContentSize().height;
	Background1->setScaleX(visibleSize.width / width1);
	Background1->setScaleY(visibleSize.height / height1);
	this->addChild(Background1, 0);
	sprite15 = Sprite::create("SystemSetting/passwordkuang_ss.png");		// 输入条码框
	sprite15->setPosition(Vec2(640, 360));
	sprite16 = Sprite::create("ReportAccount/reportcode/1.png");		//下划线
	sprite16->setAnchorPoint(Point(0, 1));
	sprite16->setPosition(Vec2(20, 200));
	sprite15->addChild(sprite16, 2);
	sprite17 = Sprite::create(red[0]);				//第一位
	sprite17->setPosition(Vec2(35, 225));
	sprite17->setScaleX(2);
	sprite17->setScaleY(2);
	sprite17->setVisible(false);
	sprite15->addChild(sprite17, 2);
	sprite18 = Sprite::create(red[0]);				//第二位
	sprite18->setPosition(Vec2(105, 225));
	sprite18->setScaleX(2);
	sprite18->setScaleY(2);
	sprite18->setVisible(false);
	sprite15->addChild(sprite18, 2);
	sprite19 = Sprite::create(red[0]);				//第三位
	sprite19->setPosition(Vec2(175, 225));
	sprite19->setScaleX(2);
	sprite19->setScaleY(2);
	sprite19->setVisible(false);
	sprite15->addChild(sprite19, 2);
	sprite20 = Sprite::create(red[0]);				//第四位
	sprite20->setPosition(Vec2(245, 225));
	sprite20->setScaleX(2);
	sprite20->setScaleY(2);
	sprite20->setVisible(false);
	sprite15->addChild(sprite20, 2);
	sprite21 = Sprite::create(red[0]);				//第五位
	sprite21->setPosition(Vec2(315, 225));
	sprite21->setScaleX(2);
	sprite21->setScaleY(2);
	sprite21->setVisible(false);
	sprite15->addChild(sprite21, 2);
	sprite22 = Sprite::create(red[0]);				//第六位
	sprite22->setPosition(Vec2(385, 225));
	sprite22->setScaleX(2);
	sprite22->setScaleY(2);
	sprite22->setVisible(false);
	sprite15->addChild(sprite22, 2);
	sprite23 = Sprite::create(red[0]);				//第七位
	sprite23->setPosition(Vec2(455, 225));
	sprite23->setScaleX(2);
	sprite23->setScaleY(2);
	sprite23->setVisible(false);
	sprite15->addChild(sprite23, 2);
	sprite24 = Sprite::create(red[0]);				//第8位
	sprite24->setPosition(Vec2(525, 225));
	sprite24->setScaleX(2);
	sprite24->setScaleY(2);
	sprite24->setVisible(false);
	sprite15->addChild(sprite24, 2);
	this->addChild(sprite15, 1);

	this->RegisterListener();
	scheduleUpdate();

	return true;
}
void SystemSetting::update(float dt) {
	if (LeftOrRight == 0) {			//第一位
		if (!c[0]) 					//判断第一位是否填写
			sprite17->setVisible(true);
		if (KeyUp) {
			c[0] = true;
			count[LeftOrRight] ++;
			if (count[LeftOrRight] > 9)
				count[LeftOrRight] %= 10;
			sprite17->setTexture(red[count[LeftOrRight]]);
			KeyUp = false;
		}
		else if (KeyDown) {
			c[0] = true;
			count[LeftOrRight] --;
			if (count[LeftOrRight] < 0)
				count[LeftOrRight] += 10;
			sprite17->setTexture(red[count[LeftOrRight]]);
			KeyDown = false;
		}
		else if (KeyRight) {
			if (c[0]) {
				LeftOrRight = 1;
				auto moveTo = MoveTo::create(0.01, Vec2(20 + 70 * LeftOrRight, 200));
				sprite16->runAction(moveTo);
			}
			KeyRight = false;
		}
	}
	else if (LeftOrRight == 1) {			//第二位
		if (!c[1])					//判断第二位是否填写
			sprite18->setVisible(true);
		if (KeyUp) {
			c[1] = true;
			count[LeftOrRight] ++;
			if (count[LeftOrRight] > 9)
				count[LeftOrRight] %= 10;
			sprite18->setTexture(red[count[LeftOrRight]]);
			KeyUp = false;
		}
		else if (KeyDown) {
			c[1] = true;
			count[LeftOrRight] --;
			if (count[LeftOrRight] < 0)
				count[LeftOrRight] += 10;
			sprite18->setTexture(red[count[LeftOrRight]]);
			KeyDown = false;
		}
		else if (KeyLeft) {
			LeftOrRight--;
			auto moveTo = MoveTo::create(0.01, Vec2(20 + 70 * LeftOrRight, 200));
			sprite16->runAction(moveTo);
			KeyLeft = false;
		}
		else if (KeyRight) {
			if (c[0] && c[1]) {
				LeftOrRight++;
				auto moveTo = MoveTo::create(0.01, Vec2(20 + 70 * LeftOrRight, 200));
				sprite16->runAction(moveTo);
			}
			KeyRight = false;
		}
	}
	else if (LeftOrRight == 2) {			//第3位
		if (!c[2])					//判断第3位是否填写
			sprite19->setVisible(true);
		if (KeyUp) {
			c[2] = true;
			count[LeftOrRight] ++;
			if (count[LeftOrRight] > 9)
				count[LeftOrRight] %= 10;
			sprite19->setTexture(red[count[LeftOrRight]]);
			KeyUp = false;
		}
		else if (KeyDown) {
			c[2] = true;
			count[LeftOrRight] --;
			if (count[LeftOrRight] < 0)
				count[LeftOrRight] += 10;
			sprite19->setTexture(red[count[LeftOrRight]]);
			KeyDown = false;
		}
		else if (KeyLeft) {
			LeftOrRight--;
			auto moveTo = MoveTo::create(0.01, Vec2(20 + 70 * LeftOrRight, 200));
			sprite16->runAction(moveTo);
			KeyLeft = false;
		}
		else if (KeyRight) {
			if (c[0] && c[1] && c[2]) {
				LeftOrRight++;
				auto moveTo = MoveTo::create(0.01, Vec2(20 + 70 * LeftOrRight, 200));
				sprite16->runAction(moveTo);
			}
			KeyRight = false;
		}
	}
	else if (LeftOrRight == 3) {			//第4位
		if (!c[3])					//判断第4位是否填写
			sprite20->setVisible(true);
		if (KeyUp) {
			c[3] = true;
			count[LeftOrRight] ++;
			if (count[LeftOrRight] > 9)
				count[LeftOrRight] %= 10;
			sprite20->setTexture(red[count[LeftOrRight]]);
			KeyUp = false;
		}
		else if (KeyDown) {
			c[3] = true;
			count[LeftOrRight] --;
			if (count[LeftOrRight] < 0)
				count[LeftOrRight] += 10;
			sprite20->setTexture(red[count[LeftOrRight]]);
			KeyDown = false;
		}
		else if (KeyLeft) {
			LeftOrRight--;
			auto moveTo = MoveTo::create(0.01, Vec2(20 + 70 * LeftOrRight, 200));
			sprite16->runAction(moveTo);
			KeyLeft = false;
		}
		else if (KeyRight) {
			if (c[0] && c[1] && c[2] && c[3]) {
				LeftOrRight++;
				auto moveTo = MoveTo::create(0.01, Vec2(20 + 70 * LeftOrRight, 200));
				sprite16->runAction(moveTo);
			}
			KeyRight = false;
		}
	}
	else if (LeftOrRight == 4) {			//第5位
		if (!c[4])					//判断第5位是否填写
			sprite21->setVisible(true);
		if (KeyUp) {
			c[4] = true;
			count[LeftOrRight] ++;
			if (count[LeftOrRight] > 9)
				count[LeftOrRight] %= 10;
			sprite21->setTexture(red[count[LeftOrRight]]);
			KeyUp = false;
		}
		else if (KeyDown) {
			c[4] = true;
			count[LeftOrRight] --;
			if (count[LeftOrRight] < 0)
				count[LeftOrRight] += 10;
			sprite21->setTexture(red[count[LeftOrRight]]);
			KeyDown = false;
		}
		else if (KeyLeft) {
			LeftOrRight--;
			auto moveTo = MoveTo::create(0.01, Vec2(20 + 70 * LeftOrRight, 200));
			sprite16->runAction(moveTo);
			KeyLeft = false;
		}
		else if (KeyRight) {
			if (c[0] && c[1] && c[2] && c[3] && c[4]) {
				LeftOrRight++;
				auto moveTo = MoveTo::create(0.01, Vec2(20 + 70 * LeftOrRight, 200));
				sprite16->runAction(moveTo);
			}
			KeyRight = false;
		}
	}
	else if (LeftOrRight == 5) {			//第6位
		if (!c[5])					//判断第6位是否填写
			sprite22->setVisible(true);
		if (KeyUp) {
			c[5] = true;
			count[LeftOrRight] ++;
			if (count[LeftOrRight] > 9)
				count[LeftOrRight] %= 10;
			sprite22->setTexture(red[count[LeftOrRight]]);
			KeyUp = false;
		}
		else if (KeyDown) {
			c[5] = true;
			count[LeftOrRight] --;
			if (count[LeftOrRight] < 0)
				count[LeftOrRight] += 10;
			sprite22->setTexture(red[count[LeftOrRight]]);
			KeyDown = false;
		}
		else if (KeyLeft) {
			LeftOrRight--;
			auto moveTo = MoveTo::create(0.01, Vec2(20 + 70 * LeftOrRight, 200));
			sprite16->runAction(moveTo);
			KeyLeft = false;
		}
		else if (KeyRight) {
			if (c[0] && c[1] && c[2] && c[3] && c[4] && c[5]) {
				LeftOrRight++;
				auto moveTo = MoveTo::create(0.01, Vec2(20 + 70 * LeftOrRight, 200));
				sprite16->runAction(moveTo);
			}
			KeyRight = false;
		}
	}
	else if (LeftOrRight == 6) {			//第7位
		if (!c[6])					//判断第7位是否填写
			sprite23->setVisible(true);
		if (KeyUp) {
			c[6] = true;
			count[LeftOrRight] ++;
			if (count[LeftOrRight] > 9)
				count[LeftOrRight] %= 10;
			sprite23->setTexture(red[count[LeftOrRight]]);
			KeyUp = false;
		}
		else if (KeyDown) {
			c[6] = true;
			count[LeftOrRight] --;
			if (count[LeftOrRight] < 0)
				count[LeftOrRight] += 10;
			sprite23->setTexture(red[count[LeftOrRight]]);
			KeyDown = false;
		}
		else if (KeyLeft) {
			LeftOrRight--;
			auto moveTo = MoveTo::create(0.01, Vec2(20 + 70 * LeftOrRight, 200));
			sprite16->runAction(moveTo);
			KeyLeft = false;
		}
		else if (KeyRight) {
			if (c[0] && c[1] && c[2] && c[3] && c[4] && c[5] && c[6]) {
				LeftOrRight++;
				auto moveTo = MoveTo::create(0.01, Vec2(20 + 70 * LeftOrRight, 200));
				sprite16->runAction(moveTo);
			}
			KeyRight = false;
		}
	}
	else if (LeftOrRight == 7) {			//第8位
		if (!c[7])					//判断第8位是否填写
			sprite24->setVisible(true);
		if (KeyUp) {
			c[7] = true;
			count[LeftOrRight] ++;
			if (count[LeftOrRight] > 9)
				count[LeftOrRight] %= 10;
			sprite24->setTexture(red[count[LeftOrRight]]);
			KeyUp = false;
		}
		else if (KeyDown) {
			c[7] = true;
			count[LeftOrRight] --;
			if (count[LeftOrRight] < 0)
				count[LeftOrRight] += 10;
			sprite24->setTexture(red[count[LeftOrRight]]);
			KeyDown = false;
		}
		else if (KeyLeft) {
			LeftOrRight--;
			auto moveTo = MoveTo::create(0.01, Vec2(20 + 70 * LeftOrRight, 200));
			sprite16->runAction(moveTo);
			KeyLeft = false;
		}
		else if (KeyEnter) {		//全部输入，确认键
			if (c[0] && c[1] && c[2] && c[3] && c[4] && c[5] && c[6] && c[7]) {
				sprite15->setVisible(false);			//隐藏输入条码框
				
			}
			KeyEnter = false;
		}
	}
}
////////////////////////////////////////----------通信测试----------///////////////////////////////////////////
Scene* CommunicationTest::createScene() {
	auto scene = Scene::create();
	auto layer = CommunicationTest::create();
	scene->addChild(layer);
	return scene;
}
bool CommunicationTest::init() {
	if (!Layer::init()) {
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//背景图片
	Background = Sprite::create("Setting/SettingParameter/3.png");
	Background->setAnchorPoint(Point(0, 1));
	Background->setPosition(Vec2(origin.x + 0, origin.y + visibleSize.height));
	float width1 = Background->getContentSize().width;
	float height1 = Background->getContentSize().height;
	Background->setScaleX(visibleSize.width / width1);
	Background->setScaleY(visibleSize.height / height1);
	this->addChild(Background, 0);
	//图标
	sprite1 = Sprite::create("communicationtest/04.png");
	sprite1->setPosition(Vec2(480, 400));
	this->addChild(sprite1, 1);	
	sprite2 = Sprite::create("communicationtest/01.png");
	sprite2->setPosition(Vec2(650, 400));
	this->addChild(sprite2, 1);
	sprite3 = Sprite::create("communicationtest/02.png");
	sprite3->setPosition(Vec2(640, 300));
	this->addChild(sprite3, 1);

	this->RegisterListener();
	scheduleUpdate();

	return true;
}
void CommunicationTest::update(float dt) {
	if (KeyEnter) {
		auto director = Director::getInstance();
		director->popScene();
	}
}
///////////////////////////////////////////----------END----------/////////////////////////////////////////////