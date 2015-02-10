/*
 * Role.h
 *
 *  Created on: 2015年2月9日
 *      Author: yong
 */

#ifndef TESTS_CPP_EMPTY_TEST_CLASSES_ROLE_H_
#define TESTS_CPP_EMPTY_TEST_CLASSES_ROLE_H_

#include "cocos2d.h"
#include "Config.h"

USING_NS_CC;

class Role {
public:
	// 虚析构
	virtual ~Role() {
	}
	// 主动撞击目标，一般会造成目标损坏
	virtual void hit(Role* target) = 0;
	// 被撞击等，遭到损坏
	virtual void gotDamage(int damage)= 0;
	// HP为0了，倒下
	virtual void down()= 0;
};

#endif /* TESTS_CPP_EMPTY_TEST_CLASSES_ROLE_H_ */
