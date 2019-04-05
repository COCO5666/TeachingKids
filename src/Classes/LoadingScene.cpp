#include "LoadingScene.h"
#include "MainScene.h"

Scene*  LoadingScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LoadingScene::create();
	scene->addChild(layer);
	return scene;
}

bool  LoadingScene::init()
{
	//�ȳ�ʼ������
	if (!Layer::init())
	{
		return false;
	}

	//��ȡ��Ļ�ֱ���
	visibleSize = Director::getInstance()->getVisibleSize();

	//�������Ȳ�����Դ��Ŀ¼
	std::vector<std::string> paths;
	paths.push_back("LoadingScene");
	FileUtils::getInstance()->setSearchResolutionsOrder(paths);

	//��ӱ���
	auto bg = Sprite::create("bg.png");
	bg->setAnchorPoint(Vec2(0, 0));
	bg->setScale(0.5);
	this->addChild(bg, 0);

	//��ӽ�������������grassDownSprite����ɫ�ģ�
	auto bg_bar = Sprite::create("red_bar.png");
	barSize = bg_bar->getContentSize();
	bg_bar->setAnchorPoint(Vec2(0, 0));
	bg_bar->setPosition((visibleSize.width - barSize.width / 2) / 2, 78);
	//������ǩ
	bg_bar->setTag(0);
	bg_bar->setScale(0.5);
	this->addChild(bg_bar);

	//��ӽ���������ɫ�ģ�
	bar = LoadingBar::create("orange_bar.png");
	bar->setScale(0.5);
	bar->setAnchorPoint(Vec2(0, 0));
	bar->setPosition(Vec2((visibleSize.width - barSize.width / 2) / 2, 78));
	bar->setDirection(LoadingBar::Direction::LEFT);
	this->addChild(bar, 2);

	//������飬λ�ڵĽ������Ϸ������ýڵ���Ϊ2
	ball = Sprite::create("ball.png");
	ball->setScale(0.5);
	ball->setPosition((visibleSize.width - barSize.width / 2) / 2 - ball->getContentSize().width / 8, 105);
	ball->setAnchorPoint(Vec2(0.5, 0.5));
	auto repeatforeve = RepeatForever::create(RotateBy::create(0.2, 120));
	ball->runAction(repeatforeve);
	this->addChild(ball, 2);

	//��ʱ������ɽ����������к�������˶�
	d = barSize.width / 2 / 100 / 4;
	schedule(schedule_selector(LoadingScene::update), 1.0 / 90);

	return true;
}
void LoadingScene::update(float f)
{
	static float count = 0;
	ball->setPositionX(ball->getPositionX() + d);

	count += 0.25;
	bar->setPercent(count);
	if (count >= 100)
	{
		unschedule(schedule_selector(LoadingScene::update));
		Director *dic = Director::getInstance();
		auto ani = TransitionProgressHorizontal::create(1.2f, MainScene::createScene());
		//auto ani = TransitionRotoZoom::create(1.0f, MainScene::createScene());
		dic->replaceScene(ani);
	}
}