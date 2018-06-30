
// Comentario de cabecera

#pragma once

#include <memory>
#include <btBulletDynamicsCommon.h>

class Shape
{

	protected:
			
	std::shared_ptr< btCollisionShape > physics_shape;
		
	public:
	
		virtual ~Shape() = default;
		
	protected:
	
		Shape(std::shared_ptr< btCollisionShape > shape) : physics_shape(shape)
		{
		}

	public:

		btCollisionShape * get ()
		{
			return physics_shape.get ();
		}
		
};