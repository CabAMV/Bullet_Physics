
// Comentario de cabecera

#pragma once

#include <memory>
#include <vector>
#include "Rigid_Body.hpp"
#include <btBulletDynamicsCommon.h>
#include "Trigger.hpp"

class Physics_World
{
	std::unique_ptr<btDiscreteDynamicsWorld> world;
	std::vector< std::shared_ptr< Rigid_Body >> bodies;
	std::vector< std::shared_ptr< btTypedConstraint >> joints;
	std::vector< std::shared_ptr< Trigger >> triggers;



	btDefaultCollisionConfiguration 	collisionConfiguration;
	btCollisionDispatcher 				collisionDispatcher;
	btDbvtBroadphase 					overlappingPairCache;
	btSequentialImpulseConstraintSolver constraintSolver;
	
	public: 
		Physics_World()  : collisionDispatcher(&collisionConfiguration)
		{

			world.reset 
			(
				new btDiscreteDynamicsWorld 
				(
					&collisionDispatcher,
					&overlappingPairCache,
					&constraintSolver,
					&collisionConfiguration
				)
			);

			world->setGravity(btVector3(0, -10, 0));
		}
		
	public:
	
		void step(float deltaTime)
		{
			world->stepSimulation(deltaTime);
		}
		
		void addWithMask(std::shared_ptr< Rigid_Body > & body,int group,int mask)
		{
			bodies.push_back (body);
			
			world->addRigidBody (body->get (),group,mask);
		}

		void addConstraint(std::shared_ptr< btTypedConstraint > joint)
		{
			joints.push_back(joint);
			btTypedConstraint  * pointer =  joint.get();

			world->addConstraint(pointer);
		}

		void addCollision(std::shared_ptr< Trigger > &  _trigger)
		{
			triggers.push_back(_trigger);
			btGhostObject  * pointer = _trigger->get();

			world->addCollisionObject(pointer);
			world->getBroadphase()->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());
		}

		void add(std::shared_ptr< Rigid_Body > & body)
		{
			bodies.push_back(body);

			world->addRigidBody(body->get());
		}

		void reset() 
		{
			world.reset();
		}
}; 