
// Comentario de cabecera

#pragma once

#include "Shape.hpp"

class Cylinder_Shape : public Shape
{
public:

	Cylinder_Shape(float x,float y,float z) : Shape(std::shared_ptr<btCylinderShapeZ>(new btCylinderShapeZ(btVector3(x,y,z))))
	{
	}

};
