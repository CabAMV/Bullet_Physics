#include "GameObject.hpp"
#include "Dynamic_Rigid_Body.hpp"
#include "Static_Rigid_Body.hpp"
#include "Box_Shape.hpp"
#include "Scene.hpp"


class Bullet : public GameObject
{
public:

	Bullet(int mask = 0) : GameObject(mask)
	{


		std::shared_ptr<Shape> sphereShape(new Sphere_Shape(0.5f));
		std::shared_ptr<Rigid_Body> sphereBody(new Dynamic_Rigid_Body(sphereShape, 1.f, 2.5f, 14.f, 2.5f));
		add_piece("Bullet", "../../../../assets/bunny-lowpoly.obj", sphereBody, 1,true);

	}

	void apply_force(float x, float y, float z, float magnitude) override
	{
		pieces["Bullet"].rigidbody->get()->applyForce(btVector3(x, y, z) * magnitude ,  btVector3(0,0,0));
	}

};
