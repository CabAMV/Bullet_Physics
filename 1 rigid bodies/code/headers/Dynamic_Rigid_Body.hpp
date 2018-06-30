
// Comentario de cabecera

#pragma once

#include <memory>
#include "Rigid_Body.hpp"

class Dynamic_Rigid_Body : public Rigid_Body
{		
	btScalar mass;
		
	public:
		
		Dynamic_Rigid_Body(std::shared_ptr< Shape > & shape, float mass, float posx = 0, float posy = 0, float posz = 0, float rotx = 0, float roty = 0, float rotz = 0) : Rigid_Body(shape , posx, posy, posz,rotx, roty, rotz), mass(btScalar(mass))
		{
			btVector3 localInertia(0, 0, 0);

			shape->get ()->calculateLocalInertia (mass, localInertia);
			
			btRigidBody::btRigidBodyConstructionInfo info(mass, state.get(), shape.get()->get(), localInertia);
			
			body.reset (new btRigidBody(info));
		}
};