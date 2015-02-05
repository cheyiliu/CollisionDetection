#include "HelloWorldScene.h"
#include "AppMacros.h"
#define TAG_PLANE 1
#define TAG_BULLET 2
USING_NS_CC;

Scene* HelloWorld::scene() {
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	//定义世界的边界
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto body = PhysicsBody::createEdgeBox(visibleSize,
			PHYSICSBODY_MATERIAL_DEFAULT, 5.0f);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	edgeNode->setPhysicsBody(body);
	scene->addChild(edgeNode);

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


	{
		{
			// 注册物理碰撞事件监听
			auto listener = EventListenerPhysicsContact::create();
			    listener->onContactBegin = [this](PhysicsContact& contact)
			    {
			    	log("onContactBegin");
			        auto spriteA = (Sprite*)contact.getShapeA()->getBody()->getNode();
			        auto spriteB = (Sprite*)contact.getShapeB()->getBody()->getNode();

			        return true;
			    };

			    listener->onContactPreSolve = [] (PhysicsContact& contact,
			            PhysicsContactPreSolve& solve) {

//			        log("onContactPreSolve");
			        return true;
			    };

			    listener->onContactPostSolve = [] (PhysicsContact& contact,
			            const PhysicsContactPostSolve& solve) {

//			        log("onContactPostSolve");
			    };

			    listener->onContactSeperate = [](PhysicsContact& contact) {
			        log("onContactSeperate");
			    };

			    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(
			            listener, 1);
		}
		{
			// touch event监听
			auto touchListener = EventListenerTouchOneByOne::create();

			touchListener->setSwallowTouches(true);
			touchListener->onTouchBegan =
					CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
			touchListener->onTouchMoved =
					CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
			touchListener->onTouchEnded =
					CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
			Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener,
					this);
		}
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



bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event) {
	log("onTouchBegan");
	return true;
}

void HelloWorld::onTouchMoved(Touch *touch, Event *unused_event) {
//	log("onTouchMoved");
}

void HelloWorld::onTouchEnded(Touch *touch, Event *unused_event) {
	log("onTouchEnded");
    Vec2 location = touch->getLocation();
    addNewSpriteAtPosition(location);
}


static int i=0;
void HelloWorld::addNewSpriteAtPosition(Vec2 p) {
	log("---------addNewSpriteAtPosition");

	i++;

	if (i % 2 == 0) {
		log("---------addNewSpriteAtPosition,,,,bang");
		auto sp = Sprite::create("bang.png");
		sp->setTag(1);
		auto body = PhysicsBody::createBox(sp->getContentSize());
		{
//			body->setGroup(-1);//优先级最高
//			body->setCategoryBitmask(0x01);//设置类别
//			body->setContactTestBitmask(0xFFFFFFFF);//和另外的PhysicsBody的类别作与操作
//			body->setCollisionBitmask(0x02);//和另外的PhysicsBody的类别作与操作
		}
		sp->setPhysicsBody(body);
		sp->setPosition(p);
		this->addChild(sp);
	} else {
		log("---------addNewSpriteAtPosition,,,,CloseSelected");
		auto sp = Sprite::create("CloseSelected.png");
		sp->setTag(2);
		auto body = PhysicsBody::createBox(sp->getContentSize());
		{
//			body->setGroup(-1);//优先级最高
//			body->setCategoryBitmask(0x01);//设置类别
//			body->setContactTestBitmask(0xFFFFFFFF);//和另外的PhysicsBody的类别作与操作
//			body->setCollisionBitmask(0x02);//和另外的PhysicsBody的类别作与操作
		}
		sp->setPhysicsBody(body);
		sp->setPosition(p);
		this->addChild(sp);
	}

}
