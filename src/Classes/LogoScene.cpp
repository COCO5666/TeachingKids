#include "LogoScene.h"
#include "LoadingScene.h"

USING_NS_CC;

Scene* LogoScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LogoScene::create();
	scene->addChild(layer);
	return scene;
}

bool LogoScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//��ȡ��Ļ�ֱ���
	auto visibleSize = Director::getInstance()->getVisibleSize();

	//�������Ȳ�����Դ��Ŀ¼
	std::vector<std::string> paths;
	paths.push_back("LogoScene");
	FileUtils::getInstance()->setSearchResolutionsOrder(paths);

	//�װ汳��
	auto bg = Sprite::create("bg.png");//�����װ澫��
	bg->setScale(0.5);
	bg->setAnchorPoint(Vec2(0, 0));
	bg->setPosition(0, 0);
	this->addChild(bg);

	//logo ���ã�Ȼ���ٶ���
	auto logo = Sprite::create("logo.png");
	logo->setAnchorPoint(Vec2(0.5, 0.5));
	logo->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	logo->setScale(0.5f);
	this->addChild(logo);

	//�Ŵ�
	auto sprite1Scale1 = ScaleTo::create(1.0f, 1.3 / 2);
	auto spriteScale2 = ScaleTo::create(1.0f, 0.2 / 2);
	//���ֳ���
	auto fade2 = FadeIn::create(1);
	//��ʧ��
	auto fade1 = FadeOut::create(1);
	//���ж���
	auto sqe1 = Sequence::create(fade2, sprite1Scale1, spriteScale2, fade1, CallFunc::create(CC_CALLBACK_0(LogoScene::EnterLoadingScene, this)), NULL);
	logo->runAction(sqe1);

	return true;
}


void LogoScene::EnterLoadingScene()
{
	auto  *scene1 = LoadingScene::createScene();
	//auto trans1=TransitionFadeTR::create(1,scene1);
	//auto trans1=TransitionPageTurn ::create(1.2f,scene1,false);
	auto trans = TransitionProgressHorizontal::create(1.2f, scene1);
	Director::getInstance()->replaceScene(trans);
}