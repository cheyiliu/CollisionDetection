/*
 * RoleEmemyBig.h
 *
 *  Created on: 2015年2月9日
 *      Author: yong
 */

#ifndef TESTS_CPP_EMPTY_TEST_CLASSES_ROLEEMEMYBIG_H_
#define TESTS_CPP_EMPTY_TEST_CLASSES_ROLEEMEMYBIG_H_

#include "Role.h"

class RoleEmemyBig: public Role, public Sprite {
public:
	RoleEmemyBig();
	virtual ~RoleEmemyBig();
	virtual void hit(Role* target);
	virtual void gotDamage(int damage);
	virtual void down();
	virtual bool init();
	//
	CREATE_FUNC (RoleEmemyBig)
	;
	void doRemoveSelf(Node* sender);

	int mForce = 100;
};

#endif /* TESTS_CPP_EMPTY_TEST_CLASSES_ROLEEMEMYBIG_H_ */
