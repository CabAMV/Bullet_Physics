
// Comentario de cabecera

#pragma once

#include <memory>
#include "Shape.hpp"
#include "BulletCollision/CollisionDispatch/btGhostObject.h"

class Trigger
{
protected:

	std::unique_ptr< btGhostObject 		  > body;
	std::shared_ptr< Shape   			  > shape;


public:

	Trigger()
	{
	}

	Trigger(std::shared_ptr< Shape > & shape, float posx = 0, float posy = 0, float posz = 0, float rotx = 0, float roty = 0, float rotz = 0) : shape(shape)
	{
		btTransform transform/*(quat,position)*/;
		transform.setIdentity();
		transform.setOrigin(btVector3(posx, posy, posz));
		transform.setRotation(btQuaternion(rotx, roty, rotz));

		body.reset(new btGhostObject());
		//peta al añadir un trigger
		body->setCollisionShape(shape.get()->get());
		body->setWorldTransform(transform);
		body->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);

	}

	virtual ~Trigger() = default;


	btGhostObject * get()
	{
		return body.get();
	}
	virtual void OnCollisionEnter() {}
};

