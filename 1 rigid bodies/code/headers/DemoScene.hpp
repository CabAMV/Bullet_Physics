#pragma once

#include "Scene.hpp"
#include "StaticElements.hpp"
#include "WallKey.hpp"

class DemoScene:public Scene
{


public:

	DemoScene():Scene()
	{
		std::shared_ptr<GameObject> tank(new Tank());
		add_game_object(std::string("Tank"), tank );

		std::shared_ptr<GameObject> Cube(new StaticCube());
		add_game_object(std::string("Cube"), Cube);

		std::shared_ptr<GameObject> Floor(new StaticElements());
		add_game_object(std::string("Floor"), Floor);

		std::shared_ptr<GameObject> Wall(new WallKey());
		add_game_object(std::string("Wall"), Wall);
	}


};