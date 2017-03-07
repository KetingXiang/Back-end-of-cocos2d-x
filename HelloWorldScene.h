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
	int count_x[10];		//�����л�������
	int count_y;			//�����л�������

public:
	Listener();
	void RegisterListener();
	virtual void onKeyPressed(EventKeyboard::KeyCode keycode, Event *event);
};
//���˵�
class HelloWorld: public Listener {
private:
	Sprite* Background, * sprite1, * sprite2, * sprite3, * sprite4,
		* sprite5, * sprite6, * sprite7, * sprite8, * sprite9;
	int x = 600;			//��һ��ѡ��ĺ�����
	int y = 550;			//............������
	int step = 80;			//������
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	virtual void update(float dt);
    CREATE_FUNC(HelloWorld);
};
//��������
class ParameterAdjust : public Listener {
private:
	Sprite* Background1, *Background2, *sprite1, *sprite2, *sprite3, *sprite4, *sprite5, *sprite6, *sprite7, *sprite8, *sprite9, *sprite10, 
			*sprite11, *sprite12, *sprite13, *sprite14, *sprite15, *sprite16, *sprite17, *sprite18, *sprite19, *sprite20, *sprite21,
			*sprite22;
	int x = 200;			//��һ��ѡ��ĺ�����
	int y = 600;			//............������
	int step = 38;			//������
	std::vector<std::string> red;			//��ɫ����
	std::vector<std::string> green;			//��ɫ����
	std::vector<std::string> difficulty;	//�Ѷȵ���
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void update(float dt);
	CREATE_FUNC(ParameterAdjust);
};
//�������
class DecodeAdjust : public Listener {
private:
	Sprite* Background1, *Background2, *sprite1, *sprite2, *sprite3, *sprite4, *sprite5, *sprite6, *sprite7, *sprite8, *sprite9, *sprite10,
		*sprite11, *sprite12, *sprite13, *sprite14, *sprite15, *sprite16, *sprite17, *sprite18, *sprite19, *sprite20, *sprite21,
		*sprite22;
	int step = 63;			//������
	bool flag1;				//�Ƿ񵯳�������������
	bool c[12];		//�����12λ�����Ӧ�Ӹ�λ����λ���ж��Ƿ�����
	int count[12];	//��¼12λ
	int UpOrDown;	//����ѡ��
	int LeftOrRight;	//����ѡ��
	std::vector<std::string> red;//��ɫ����
	std::vector<std::string> green;//��ɫ����
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void update(float dt);
	CREATE_FUNC(DecodeAdjust);
};
//����
class CheckAccount : public Listener {
private:
	Sprite* Background1, *Background2, *sprite1, *sprite2, *sprite3, *sprite4, *sprite5, *sprite6, *sprite7, *sprite8, *sprite9, *sprite10,
		*sprite11, *sprite12, *sprite13, *sprite14, *sprite15, *sprite16, *sprite17, *sprite18, *sprite19, *sprite20, *sprite21,
		*sprite22;
	Layer* layer1;
	Layer* layer2;
	bool flag;				//�ֻ�����ʱ�ı�־λ����Ϊ����������enter��
	int count;
	std::vector<std::string> red;//��ɫ����
	std::vector<std::string> green;//��ɫ����
	std::vector<std::string> blue;
	std::vector<std::string> white;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void update(float dt);
	CREATE_FUNC(CheckAccount);
};
//����
class ReportAccount : public Listener {
private:
	Sprite* Background1, *Background2, *Background3, *sprite1, *sprite2, *sprite3, *sprite4, *sprite5, *sprite6, *sprite7, *sprite8, *sprite9, *sprite10,
		*sprite11, *sprite12, *sprite13, *sprite14, *sprite15, *sprite16, *sprite17, *sprite18, *sprite19, *sprite20, *sprite21,
		*sprite22, *sprite23, *sprite24;
	Layer* layer1;	//ѡ���˺�ĵ�һ������
	Layer* layer2;
	bool flag1, flag2, flag3;	//��Ӧ��¼��ǰ���ĸ����棬true��ʾ�򿪡�
	bool c[8];		//�����8λ�����Ӧ�Ӹ�λ����λ���ж��Ƿ�����
	int count[8];	//��¼8λ
	int UpOrDown;	//����ѡ��
	int LeftOrRight;	//����ѡ��
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
//ϵͳ����
class SystemSetting : public Listener {
private:
	Sprite* Background1, *Background2, *sprite1, *sprite2, *sprite3, *sprite4, *sprite5, *sprite6, *sprite7, *sprite8, *sprite9, *sprite10,
		*sprite11, *sprite12, *sprite13, *sprite14, *sprite15, *sprite16, *sprite17, *sprite18, *sprite19, *sprite20, *sprite21,
		*sprite22, *sprite23, *sprite24;
	bool c[8];		//�����8λ�����Ӧ�Ӹ�λ����λ���ж��Ƿ�����
	int count[8];	//��¼8λ
	int UpOrDown;	//����ѡ��
	int LeftOrRight;	//����ѡ��
	std::vector<std::string> red;
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void update(float dt);
	CREATE_FUNC(SystemSetting);
};
//ͨ�Ų���
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
