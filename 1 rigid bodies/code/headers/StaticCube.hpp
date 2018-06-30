
// Comentario de cabecera

#pragma once

#include "GameObject.hpp"
#include "Dynamic_Rigid_Body.hpp"
#include "Static_Rigid_Body.hpp"
#include "Box_Shape.hpp"


class StaticCube : public GameObject
{


public:

	StaticCube( int mask = 0) : GameObject( mask)
	{
		std::shared_ptr<Shape> shape(new Box_Shape(4.f,1.f,4.f));
		std::shared_ptr<Rigid_Body> body(new Dynamic_Rigid_Body(shape,   1.f,  -28.f,-5.f,0.f));

		//Bloqueo de ejes
		body->get()->setLinearFactor(btVector3(0,0,0));
		body->get()->setAngularFactor(btVector3(0, 0, 0));

		add_piece("Platform", "../../../../assets/floor.obj", body,2,true);
		//pieces["Platform"].rigidbody->get()->setLinearVelocity(btVector3(-1, 0, 0));

		std::shared_ptr<Shape> triggeruShapu(new Box_Shape(2.f, 8.f, 2.f));
		std::shared_ptr<Trigger> trigguru(new Trigger(triggeruShapu, -28.f, -4.f, 0.f));
		add_Trigger("trigerru", trigguru);
	}

	void update() override
	{ 

		for (int i = 0; i < triggers["trigerru"]->get()->getNumOverlappingObjects(); i++)
		{
			btRigidBody *overlappedRigidbody = static_cast<btRigidBody *>(triggers["trigerru"]->get()->getOverlappingObject(i));
			pieces["Platform"].rigidbody->get()->setLinearVelocity(btVector3(-1, 0, 0));
			
			// do whatever you want to do with these pairs of colliding objects
		}

		if (pieces["Platform"].rigidbody->get()->getWorldTransform().getOrigin().x() < -45.0f) 
		{
			pieces["Platform"].rigidbody->get()->setLinearVelocity(btVector3(0, 0, 0));

		}
		GameObject::update();

		
	}

};