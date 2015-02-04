#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
//#include "base/CCVector.h"

USING_NS_CC;
class HelloWorld: public cocos2d::Layer {
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* scene();

	// a selector callback
	void menuCloseCallback(Ref* sender);

	// implement the "static node()" method manually
	CREATE_FUNC(HelloWorld)
	;

	void update(float dt)
override	;
	void updateCustom(float dt);
	void spriteDone(Node* sender);
	void buildBullet(int startx, int endx, int y);
	void buildPlane(int startx, int endx, int y);
	void removePlane(Node* pSender);
	void planeBlowup(Sprite* plane);
	Vector<Sprite*> mBullets;
	Vector<Sprite*> mPlanes;
};

#endif // __HELLOWORLD_SCENE_H__
