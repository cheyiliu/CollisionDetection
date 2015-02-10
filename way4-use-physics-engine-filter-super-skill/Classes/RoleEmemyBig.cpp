/*
 * RoleEmemyBig.cpp
 *
 *  Created on: 2015年2月9日
 *      Author: yong
 */

#include "RoleEmemyBig.h"

RoleEmemyBig::RoleEmemyBig() {
	// TODO Auto-generated constructor stub

}

RoleEmemyBig::~RoleEmemyBig() {
	// TODO Auto-generated destructor stub
}

bool RoleEmemyBig::init() {
	//////////////////////////////
	// 1. super init first
	if (!Sprite::initWithSpriteFrameName("hero1.png")) {
		return false;
	}

	setTag(TAG_ENEMY_PLANE);
	auto body = PhysicsBody::createBox(getContentSize());
	body->setGroup(PHYSICAL_BODY_ENEMY_GROUP);
	body->setCategoryBitmask(PHYSICAL_BODY_ENEMY_BITMASK_CATEGORY);
	body->setContactTestBitmask(PHYSICAL_BODY_ENEMY_BITMASK_CONTACT_TEST);
	body->setCollisionBitmask(PHYSICAL_BODY_ENEMY_BITMASK_COLLISION);
	setPhysicsBody(body);
	setRotation(-90);

	Point endPos = Point(0, 100);
	runAction(
			Sequence::create(MoveTo::create(3.0, endPos),
					CallFunc::create(
							CC_CALLBACK_0(RoleEmemyBig::doRemoveSelf, this, this)),
					NULL));
	return true;
}

void RoleEmemyBig::hit(Role* target) {
	log("RoleEmemyBig, hit------------->");
	if (target) {
		target->gotDamage(mForce);
	}
}

void RoleEmemyBig::gotDamage(int damage) {
	log("RoleEmemyBig, gotDamage------------->");
	down();
}

void RoleEmemyBig::down() {
	log("RoleEmemyBig, down------------->");

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
			CC_CALLBACK_0(RoleEmemyBig::doRemoveSelf, this, this));
	auto sequence = Sequence::create(animate, remove, nullptr);
	runAction(sequence);
}

void RoleEmemyBig::doRemoveSelf(Node* sender) {
	log("RoleEmemyBig，spriteDone");
	removeFromParent();
}
