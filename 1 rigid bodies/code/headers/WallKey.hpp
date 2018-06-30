
// Comentario de cabecera

#pragma once

#include "GameObject.hpp"
#include "Dynamic_Rigid_Body.hpp"
#include "Static_Rigid_Body.hpp"
#include "Box_Shape.hpp"


class WallKey : public GameObject
{
public:

	WallKey(int mask = 0) : GameObject(mask)
	{


		std::shared_ptr<Shape> shape(new Box_Shape(1.2f, 6.f, 16.f));
		std::shared_ptr<Rigid_Body> body(new Static_Rigid_Body(shape, -75.f, 0.f, 0.f));
		add_piece("DesWall", "../../../../assets/Wall.obj", body, 1, true);

		std::shared_ptr<Shape> shapeKey(new Box_Shape(0.f, 0.f, 0.f));
		std::shared_ptr<Rigid_Body> keyBody(new Static_Rigid_Body(shapeKey,0.f, -4.f, 20.f));
		add_piece("Key", "../../../../assets/llaveTanque.obj", keyBody, 1, true);

		std::shared_ptr<Shape> triggeruShapu(new Box_Shape(2.f, 8.f, 2.f));
		std::shared_ptr<Trigger> trigguru(new Trigger(triggeruShapu, 0.f, -4.f, 20.f));
		add_Trigger("trigerru", trigguru);

	}

	void update() override
	{
		for (int i = 0; i < triggers["trigerru"]->get()->getNumOverlappingObjects(); i++)
		{
			btRigidBody *overlappedRigidbody = static_cast<btRigidBody *>(triggers["trigerru"]->get()->getOverlappingObject(i));
			
			setPieceActive("Key",false);
			setPieceActive("DesWall", false);
			pieces["Key"].rigidbody->get()->getWorldTransform().setOrigin(btVector3(0, -2000, 0));
			pieces["DesWall"].rigidbody->get()->getWorldTransform().setOrigin(btVector3(0,-2000,0));

		}

		GameObject::update();


	}
};
