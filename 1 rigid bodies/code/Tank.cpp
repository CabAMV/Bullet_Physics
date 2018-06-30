#pragma once

#include "headers\Scene.hpp"

Tank::Tank( int _mask )
{
	mask = _mask;
	canShoot = true;
	shootCounter = 0;
	shootDelay = 10;


	std::shared_ptr<Shape> wheelShape1(new Cylinder_Shape(1, 1, 1));
	std::shared_ptr<Rigid_Body> wheelBody1(new Dynamic_Rigid_Body(wheelShape1, 50.f, 0.f, 4.f, 0.f));
	add_piece("wheel1", "../../../../assets/bunny-lowpoly.obj", wheelBody1, 1,true);
	wheelBody1->get()->setFriction(20.f);
	pieces["wheel1"].rigidbody->get()->setActivationState(DISABLE_DEACTIVATION);


	std::shared_ptr<Shape> wheelShape2(new Cylinder_Shape(1, 1, 1));
	std::shared_ptr<Rigid_Body> wheelBody2(new Dynamic_Rigid_Body(wheelShape2, 50.f, 0.f, 4.f, 5.f));
	add_piece("wheel2", "../../../../assets/bunny-lowpoly.obj", wheelBody2, 1, true);
	wheelBody2->get()->setFriction(20.f);
	pieces["wheel2"].rigidbody->get()->setActivationState(DISABLE_DEACTIVATION);



	std::shared_ptr<Shape> wheelShape3(new Cylinder_Shape(1, 1, 1));
	std::shared_ptr<Rigid_Body> wheelBody3(new Dynamic_Rigid_Body(wheelShape3, 50.f, 5.f, 4.f, 0.f));
	add_piece("wheel3", "../../../../assets/bunny-lowpoly.obj", wheelBody3, 1, true);
	wheelBody3->get()->setFriction(20.f);
	pieces["wheel3"].rigidbody->get()->setActivationState(DISABLE_DEACTIVATION);



	std::shared_ptr<Shape> wheelShape4(new Cylinder_Shape(1, 1, 1));
	std::shared_ptr<Rigid_Body> wheelBody4(new Dynamic_Rigid_Body(wheelShape4, 50.f, 5.f, 4.f, 5.f));
	add_piece("wheel4", "../../../../assets/bunny-lowpoly.obj", wheelBody4, 1, true);
	wheelBody4->get()->setFriction(20.f);
	pieces["wheel4"].rigidbody->get()->setActivationState(DISABLE_DEACTIVATION);



	std::shared_ptr<Shape> shape(new Box_Shape(1, 0.4f, 2.6f));
	std::shared_ptr<Rigid_Body> body(new Dynamic_Rigid_Body(shape, 100.f, 2.5f, 12.f, 2.5f));
	add_piece("Tank", "../../../../assets/TankBody.obj", body, 1, true);    //250,100,650,


	std::shared_ptr<Shape> sphereShape(new Sphere_Shape(0.5f));
	std::shared_ptr<Rigid_Body> sphereBody(new Dynamic_Rigid_Body(sphereShape, 50.f, 2.5f, 14.f, 2.5f));
	add_piece("TankSphere", "../../../../assets/bunny-lowpoly.obj", sphereBody, 1, true);
	pieces["TankSphere"].rigidbody->get()->setActivationState(DISABLE_DEACTIVATION);

	std::shared_ptr<Shape> canonShape(new Sphere_Shape(0.5f));
	std::shared_ptr<Rigid_Body> canonBody(new Dynamic_Rigid_Body(canonShape, 0.5f, 4.f, 14.f, 2.5f ));
	add_piece("Canon", "../../../../assets/Wheel.obj", canonBody, 1, true);
	pieces["Canon"].rigidbody->get()->setActivationState(DISABLE_DEACTIVATION);
	pieces["Canon"].rigidbody->get()->setAngularFactor(btVector3(0,1,0));


	//pieces["Tank"].rigidbody->get()->applyForce(btVector3(-5000, 0, 0), btVector3(0, 0, 0));

	add_Hinge_joint("wheelJoint1", body, wheelBody4, btVector3(2.5f, -1, 2.5f), btVector3(0, 0, 0), btVector3(0, 0, 1), btVector3(0, 0, 1));
	add_Hinge_joint("wheelJoint2", body, wheelBody3, btVector3(2.5f, -1, -2.5f), btVector3(0, 0, 0), btVector3(0, 0, 1), btVector3(0, 0, 1));
	add_Hinge_joint("wheelJoint3", body, wheelBody2, btVector3(-2.5f, -1, 2.5f), btVector3(0, 0, 0), btVector3(0, 0, 1), btVector3(0, 0, 1));
	add_Hinge_joint("wheelJoint4", body, wheelBody1, btVector3(-2.5f, -1, -2.5f), btVector3(0, 0, 0), btVector3(0, 0, 1), btVector3(0, 0, 1));

	add_Hinge_joint("TankBodyJoint", body, sphereBody, btVector3(0, 2, 0), btVector3(0, 0, 0), btVector3(0, 1, 0), btVector3(0, 1, 0));
	add_Hinge_joint("CanonJoint", sphereBody, canonBody, btVector3(0, 0, 2), btVector3(0, 0, 0), btVector3(1, 1, 1), btVector3(0, 0, 0));



	for (int i = 0; i < 30; i++) 
	{
		std::shared_ptr<Shape> sphereShape1(new Sphere_Shape(0.5f));
		std::shared_ptr<Rigid_Body> sphereBody1(new Dynamic_Rigid_Body(sphereShape1, 1.f, 2000.5f, 2000.f, 2000.f));
		add_piece("bullet" + std::to_string(i) , "../../../../assets/sphere.obj", sphereBody1, 1, false);
		setPieceActive("bullet" + std::to_string(i), false);
	}
	poolIndex = 0;

}

void Tank::update() 
{
	btVector3 forwardVector = getForwardVector("Tank");

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{

		pieces["wheel1"].rigidbody->get()->applyTorqueImpulse(forwardVector * 20);
		pieces["wheel2"].rigidbody->get()->applyTorqueImpulse(forwardVector * 20);
		pieces["wheel3"].rigidbody->get()->applyTorqueImpulse(forwardVector * 20);
		pieces["wheel4"].rigidbody->get()->applyTorqueImpulse(forwardVector * 20);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		pieces["wheel1"].rigidbody->get()->applyTorqueImpulse(forwardVector * -20);
		pieces["wheel2"].rigidbody->get()->applyTorqueImpulse(forwardVector * -20);
		pieces["wheel3"].rigidbody->get()->applyTorqueImpulse(forwardVector * -20);
		pieces["wheel4"].rigidbody->get()->applyTorqueImpulse(forwardVector * -20);

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		pieces["wheel1"].rigidbody->get()->applyTorqueImpulse(forwardVector * -30);
		pieces["wheel2"].rigidbody->get()->applyTorqueImpulse(forwardVector * 30);
		pieces["wheel3"].rigidbody->get()->applyTorqueImpulse(forwardVector * -30);
		pieces["wheel4"].rigidbody->get()->applyTorqueImpulse(forwardVector * 30);

	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		pieces["wheel1"].rigidbody->get()->applyTorqueImpulse(forwardVector * 30);
		pieces["wheel2"].rigidbody->get()->applyTorqueImpulse(forwardVector * -30);
		pieces["wheel3"].rigidbody->get()->applyTorqueImpulse(forwardVector * 30);
		pieces["wheel4"].rigidbody->get()->applyTorqueImpulse(forwardVector * -30);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	{
		pieces["TankSphere"].rigidbody->get()->setAngularVelocity(btVector3(0,-angularSpeed,0));
		//pieces["TankSphere"].rigidbody->get()->applyTorqueImpulse(btVector3(0, -1, 0));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	{
		pieces["TankSphere"].rigidbody->get()->setAngularVelocity(btVector3(0, angularSpeed, 0));

		//pieces["TankSphere"].rigidbody->get()->applyTorqueImpulse(btVector3(0, 1, 0));
	}	

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) 
	{
		pieces["TankSphere"].rigidbody->get()->setAngularVelocity(btVector3(0, 0, 0));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
	{
		if (canShoot) 
		{
			Shoot("TankSphere", 5000);
		}
	}

	if (!canShoot)
	{
		shootCounter++;
		if (shootCounter >= shootDelay)
		{
			canShoot = true;
			shootCounter = 0;
		}
	}
	GameObject::update();


}

void Tank::Shoot(const std::string & from, float force)
{
	canShoot = false;
	setPieceActive("bullet" + std::to_string(poolIndex), true);
	btVector3  originpoint=  pieces[from].rigidbody->get()->getWorldTransform().getOrigin();
	pieces["bullet" + std::to_string(poolIndex)].rigidbody->get()->getWorldTransform().setOrigin(originpoint + getForwardVector(from)*3);
	pieces["bullet" + std::to_string(poolIndex)].rigidbody->get()->setLinearVelocity(btVector3(0,0,0));


	btVector3 forceVector = getForwardVector(from) * force;
	pieces["bullet" + std::to_string(poolIndex)].rigidbody->get()->applyForce(forceVector, btVector3(0,0,0));

	poolIndex++;
	if (poolIndex >= 30) 
	{
		poolIndex = 0;
	}

}