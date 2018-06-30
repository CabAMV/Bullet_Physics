
// Comentario de cabecera

#pragma once

#include "Shape.hpp"

class Sphere_Shape : public Shape
{
	public:
	
		Sphere_Shape(float radius) : Shape(std::shared_ptr<btCollisionShape>(new btSphereShape(btScalar(radius))))
		{
		}
		
};