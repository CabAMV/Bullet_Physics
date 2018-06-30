
// Comentario de cabecera

#pragma once

#include "GameObject.hpp"
#include "Dynamic_Rigid_Body.hpp"
#include "Static_Rigid_Body.hpp"
#include "Box_Shape.hpp"


class StaticElements : public GameObject
{
public:

	StaticElements( int mask = 0) : GameObject( mask)
	{
		std::shared_ptr<Shape> shape(new Box_Shape(25.f, 1.f, 50.f));      //500cm en max=2.f    250=1.f
		std::shared_ptr<Rigid_Body> body(new Static_Rigid_Body(shape, 0.f, -5.f, 0.f));       
		add_piece("Floor1", "../../../../assets/BigFloor.obj", body, 1,true);

		std::shared_ptr<Shape> shape2(new Box_Shape(25.f, 1.f, 50.f));
		std::shared_ptr<Rigid_Body> body2(new Static_Rigid_Body(shape2, -75.f, -5.f, 0.f));
		add_piece("Floor2", "../../../../assets/BigFloor.obj", body2, 1, true);

		std::shared_ptr<Shape> shape3(new Box_Shape(25.f, 1.f, 50.f));
		std::shared_ptr<Rigid_Body> body3(new Static_Rigid_Body(shape3, -150.f, -5.f, 0.f));
		add_piece("Floor3", "../../../../assets/BigFloor.obj", body3, 1, true);

		std::shared_ptr<Shape> shape4(new Box_Shape(1.2f, 6.f, 16.f));
		std::shared_ptr<Rigid_Body> body4(new Static_Rigid_Body(shape4, -75.f, 0.f, 30.f));
		add_piece("Wall1", "../../../../assets/Wall.obj", body4, 1, true);

		std::shared_ptr<Shape> shape5(new Box_Shape(1.2f, 6.f, 16.f));
		std::shared_ptr<Rigid_Body> body5(new Static_Rigid_Body(shape5, -75.f, 0.f, -30.f));
		add_piece("Wall2", "../../../../assets/Wall.obj", body5, 1, true);
		
		
		//Cubes
		std::shared_ptr<Shape> bunnyShape1(new Box_Shape(3.f,3.f,3.f));
		std::shared_ptr<Rigid_Body> bunny1(new Dynamic_Rigid_Body(bunnyShape1,10 ,-150.f, 10.f, 0.f));
		add_piece("Bunny1", "../../../../assets/bunny-lowpoly.obj", bunny1, 3, true);

		std::shared_ptr<Shape> bunnyShape2(new Box_Shape(3.f, 3.f, 3.f));
		std::shared_ptr<Rigid_Body> bunny2(new Dynamic_Rigid_Body(bunnyShape2, 10, -150.f, 10.f, 5.f));
		add_piece("Bunny2", "../../../../assets/bunny-lowpoly.obj", bunny2, 3, true);

		std::shared_ptr<Shape> bunnyShape3(new Box_Shape(3.f, 3.f, 3.f));
		std::shared_ptr<Rigid_Body> bunny3(new Dynamic_Rigid_Body(bunnyShape3, 10, -150.f, 10.f, -5.f));
		add_piece("Bunny3", "../../../../assets/bunny-lowpoly.obj", bunny3, 3, true);



	}

	void update() override
	{

		//pieces["Cube"].rigidbody->get()->setLinearVelocity(btVector3(0,0,0));
		GameObject::update();


	}
};
