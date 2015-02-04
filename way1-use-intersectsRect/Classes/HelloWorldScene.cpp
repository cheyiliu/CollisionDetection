#include "HelloWorldScene.h"
#include "AppMacros.h"
#define TAG_PLANE 1
#define TAG_BULLET 2
USING_NS_CC;

Scene* HelloWorld::scene() {
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	HelloWorld *layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init() {
	//////////////////////////////
	// 1. super init first
	if (!Layer::init()) {
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create("CloseNormal.png",
			"CloseSelected.png",
			CC_CALLBACK_1(HelloWorld::menuCloseCallback,this));

	closeItem->setPosition(
			origin + Vec2(visibleSize) - Vec2(closeItem->getContentSize() / 2));

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, nullptr);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	/////////////////////////////
	// 3. add your codes below...

	// add a label shows "Hello World"
	// create and initialize a label

	auto label = LabelTTF::create("Hello World", "Arial", TITLE_FONT_SIZE);

	// position the label on the center of the screen
	label->setPosition(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - label->getContentSize().height);

	// add the label as a child to this layer
	this->addChild(label, 1);

//    // add "HelloWorld" splash screen"
//    auto sprite = Sprite::create("HelloWorld.png");
//
//    // position the sprite on the center of the screen
//    sprite->setPosition(Vec2(visibleSize / 2) + origin);
//
//    // add the sprite as a child to this layer
//    this->addChild(sprite);

	{
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile(
				"shoot_background.plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shoot.plist");

		auto sprite = Sprite::createWithSpriteFrameName("background.png");
		sprite->setPosition(Vec2(visibleSize / 2) + origin);
		sprite->setRotation(90);
		this->addChild(sprite);

		scheduleUpdate();
		schedule(schedule_selector(HelloWorld::updateCustom), 5.0f,
				kRepeatForever, 0);
	}
	return true;
}

void HelloWorld::menuCloseCallback(Ref* sender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void HelloWorld::update(float dt) {
//    log("update, %d", mPlanes.size());
//    log("update, %d", mBullets.size());
	//碰撞检测
	Vector<Sprite*> bulletsToBeRemoved;
	Vector<Sprite*> planeToBeRemoved;
	for (auto bullet : mBullets) {
		for (auto plane : mPlanes) {
			if (bullet->boundingBox().intersectsRect(plane->getBoundingBox())) {
				log("碰撞了。。。。。。。。");
				bulletsToBeRemoved.pushBack(bullet);
				planeToBeRemoved.pushBack(plane);
			}
		}
	}

	// do remove
	for (auto bullet : bulletsToBeRemoved) {
		mBullets.eraseObject(bullet);
		log("removeChild(bullet)");
		this->removeChild(bullet);
	}
	bulletsToBeRemoved.clear();

	for (auto plane : planeToBeRemoved) {
		mPlanes.eraseObject(plane);
//     this->removeChild(plane);
//     plane->stopAllActions();
		planeBlowup(plane);
	}
	planeToBeRemoved.clear();
}
void HelloWorld::planeBlowup(Sprite* plane) {
	log("planeBlowup");
	auto animation = Animation::create();
	animation->setDelayPerUnit(0.2f);
	animation->addSpriteFrame(
			SpriteFrameCache::getInstance()->getSpriteFrameByName(
					"hero_blowup_n1.png"));
	animation->addSpriteFrame(
			SpriteFrameCache::getInstance()->getSpriteFrameByName(
					"hero_blowup_n2.png"));
	animation->addSpriteFrame(
			SpriteFrameCache::getInstance()->getSpriteFrameByName(
					"hero_blowup_n3.png"));
	animation->addSpriteFrame(
			SpriteFrameCache::getInstance()->getSpriteFrameByName(
					"hero_blowup_n4.png"));

	auto animate = Animate::create(animation);
	auto remove = CallFunc::create(
			CC_CALLBACK_0(HelloWorld::removePlane, this, plane));
	auto sequence = Sequence::create(animate, remove, nullptr);
	plane->runAction(sequence);
}

void HelloWorld::removePlane(Node* pTarget) {
	auto plane = (Sprite*) pTarget;
	if (plane != nullptr) {
		log("removePlane");
		this->removeChild(plane, true);
	}
}
void HelloWorld::updateCustom(float dt) {
	log("updateCustom");
	// add the bullet and the enemy
	auto winSize = Director::getInstance()->getWinSize();
	int actualY = 100;
	int startX = winSize.width - (-50);
	int endX = (-50);
	buildPlane(startX, endX, actualY); //同一高度(actualY)上的飞机和子弹，要相撞
	buildBullet(endX, startX, actualY);

	actualY = 200;
	buildPlane(startX, endX, actualY); //不是同一高度(actualY)上的飞机和子弹，不会相撞
	buildBullet(endX, startX, actualY + 50);
}

void HelloWorld::spriteDone(Node* sender) {
	log("spriteDone");
	Sprite *sprite = (Sprite*) sender;
	this->removeChild(sprite, true);
	int tag = sprite->getTag();
	if (tag == TAG_PLANE)
		mPlanes.eraseObject(sprite);
	else
		mBullets.eraseObject(sprite);
}

void HelloWorld::buildBullet(int startX, int endX, int actualY) {
	log("buildBullet");

	std::string name = "bullet1.png";
	auto sp = Sprite::createWithSpriteFrameName(name);

	Point startPos = Point(startX, actualY);
	Point endPos = Point(endX, actualY);

	sp->setPosition(startPos);
	sp->runAction(
			Sequence::create(MoveTo::create(3.0, endPos),
					CallFuncN::create(this,
							callfuncN_selector(HelloWorld::spriteDone)), NULL));
	sp->setRotation(-90);
	sp->setTag(TAG_BULLET);
	mBullets.pushBack(sp);
	this->addChild(sp);

}

void HelloWorld::buildPlane(int startX, int endX, int actualY) {
	log("buildPlane");

	std::string name = "hero1.png";
	auto sp = Sprite::createWithSpriteFrameName(name);

	Point startPos = Point(startX, actualY);
	Point endPos = Point(endX, actualY);

	sp->setPosition(startPos);
	sp->runAction(
			Sequence::create(MoveTo::create(3.0, endPos),
					CallFuncN::create(this,
							callfuncN_selector(HelloWorld::spriteDone)), NULL));
	sp->setRotation(-90);
	sp->setTag(TAG_PLANE);
	mPlanes.pushBack(sp);

	this->addChild(sp);
}
