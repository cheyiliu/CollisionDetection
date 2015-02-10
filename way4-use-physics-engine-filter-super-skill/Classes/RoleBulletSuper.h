/*
 * RoleBulletSuper.h
 *
 *  Created on: 2015年2月9日
 *      Author: yong
 */

#ifndef TESTS_CPP_EMPTY_TEST_CLASSES_ROLEBULLETSUPER_H_
#define TESTS_CPP_EMPTY_TEST_CLASSES_ROLEBULLETSUPER_H_

#include "Role.h"

class RoleBulletSuper: public Role, public Sprite {
public:
	RoleBulletSuper();
	virtual ~RoleBulletSuper();
	virtual void hit(Role* target);
	virtual void gotDamage(int damage);
	virtual void down();
	virtual bool init();
	//
	CREATE_FUNC(RoleBulletSuper)
	;
	void doRemoveSelf(float dt);
};

#endif /* TESTS_CPP_EMPTY_TEST_CLASSES_ROLEBULLETSUPER_H_ */
