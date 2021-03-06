
// Comentario de cabecera

#pragma once

#include "Shape.hpp"

class Box_Shape : public Shape
{
	public:
	
		Box_Shape(float width, float height, float depth)
		:
			Shape(std::shared_ptr<btCollisionShape>(new btBoxShape(btVector3(width, height, depth))))
		{
		}
		
};