
// Comentario de cabecera

#pragma once

#include <memory>
#include "Rigid_Body.hpp"


class Static_Rigid_Body : public Rigid_Body
{
		
	public:
		
		Static_Rigid_Body(std::shared_ptr< Shape > shape, float posx = 0, float posy = 0, float posz = 0, float rotx = 0, float roty = 0, float rotz = 0) : Rigid_Body(shape,posx,posy ,posz, rotx, roty, rotz)
		{

			btRigidBody::btRigidBodyConstructionInfo info(0, state.get(), shape.get()->get());

			body.reset(new btRigidBody(info));
			

		}



		
};