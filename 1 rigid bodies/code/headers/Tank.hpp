
// Comentario de cabecera

#pragma once

#include "GameObject.hpp"
#include "Dynamic_Rigid_Body.hpp"
#include "Static_Rigid_Body.hpp"
#include "Bullet.hpp"
#include "Scene.hpp"
#include <vector>



class Tank : public GameObject 
{
	public:



		Tank(int mask = 0);

		void update() override;
		 
		void Shoot(const std::string & from, float force);

private:
	int poolIndex;
	bool canShoot;
	int shootCounter;
	int shootDelay;

	float angularSpeed = 2;



};