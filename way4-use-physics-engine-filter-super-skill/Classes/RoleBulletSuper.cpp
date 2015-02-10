/*
 * RoleBulletSuper.cpp
 *
 *  Created on: 2015年2月9日
 *      Author: yong
 */

#include "RoleBulletSuper.h"

RoleBulletSuper::RoleBulletSuper() {
	// TODO Auto-generated constructor stub
}

RoleBulletSuper::~RoleBulletSuper() {
	// TODO Auto-generated destructor stub
}
bool RoleBulletSuper::init() {
	//////////////////////////////
	// 1. super init first
	if (!Sprite::initWithFile("bang.png")) {
		return false;
	}

	setTag(TAG_BULLET_SUPER);

	auto body = PhysicsBody::createBox(getContentSize() * 1000); // 仅仅保证PhysicsBody足够大就好
	body->setMass(0.000001f); // 将这个超级子弹的重量设的很小，这样对话，碰撞的时候不会把飞机撞的到处乱漂，从而看起来飞机还是沿原来的线路在动
	body->setGroup(PHYSICAL_BODY_HERO_GROUP);
	body->setCategoryBitmask(PHYSICAL_BODY_HERO_BITMASK_CATEGORY);
	body->setContactTestBitmask(PHYSICAL_BODY_HERO_BITMASK_CONTACT_TEST);
	body->setCollisionBitmask(PHYSICAL_BODY_HERO_BITMASK_COLLISION);

	setPhysicsBody(body);
	setVisible(false); // hide this bullet
	return true;
}

void RoleBulletSuper::hit(Role* target) {
	log("RoleBulletSuper, hit------------->");
	if (target) {
		target->gotDamage(ROLE_BULLET_SUPER_FORCE);
	}
}

void RoleBulletSuper::gotDamage(int damage) {
	log("RoleBulletSuper, gotDamage------------->");
	down();
}

void RoleBulletSuper::down() {
	log("RoleBulletSuper, down------------->");
	this->scheduleOnce(schedule_selector(RoleBulletSuper::doRemoveSelf), 0.10f); //TODO use runAction代替
}

void RoleBulletSuper::doRemoveSelf(float dt) {
	log("RoleBulletSuper, doRemoveSelf------------->");
	removeFromParent();
}
