
// Comentario de cabecera

#pragma once

#include <memory>
#include "Shape.hpp"

class Rigid_Body
{
	protected:

	std::unique_ptr< btRigidBody 		  > body;
	std::unique_ptr< btDefaultMotionState > state;
	std::shared_ptr< Shape   			  > shape;
	
	public:

		Rigid_Body() 
		{
		}
	
		Rigid_Body(std::shared_ptr< Shape > & shape,float posx=0,float posy=0,float posz=0, float rotx = 0, float roty = 0, float rotz = 0) : shape(shape)
		{
			btTransform transform/*(quat,position)*/;
			transform.setIdentity ();
			transform.setOrigin(btVector3(posx, posy, posz));
			transform.setRotation(btQuaternion(rotx,roty,rotz));
		
			state.reset (new btDefaultMotionState(transform));
		}
	
		virtual ~Rigid_Body() = default;

		
		btRigidBody * get ()
		{
			return body.get();
		}
};