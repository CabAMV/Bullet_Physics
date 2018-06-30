
// Comentario de cabecera

#pragma once

#include <memory>
#include <map>
#include <string>
#include "Graphic_Scene.hpp"
#include "Physics_World.hpp"
#include "GameObject.hpp"
#include "Tank.hpp"
#include "Box_Shape.hpp"
#include "Dynamic_Rigid_Body.hpp"
#include "StaticCube.hpp"

class Tank;

class Scene
{
protected:
	//Graphic_Scene graphics_scene;

	std::map <std::string, std::shared_ptr <GameObject>> game_objects;	

	glt::Render_Node graphics_scene;
	Physics_World    physics_world;

	public:

	Scene() 
	{
		create_scene();

	}

public:

	void add_game_object(const std::string & name, std::shared_ptr<GameObject> & game_object);

	
	void add_game_object(const std::string & name, std::shared_ptr<GameObject> & game_object, int group, int mask);


	Physics_World & getPhysicsWorld()
	{
		return physics_world;
	}

	glt::Render_Node & getGraphicScene() 
	{
		return graphics_scene;
	}

	void create_scene();

	void reset_viewport(const sf::Window & window, glt::Render_Node & scene);
	
	GameObject *get_game_object(const std::string & name);
	
	void update()
	{
		physics_world.step(1.f / 60.f);
		
		for (auto & obj : game_objects)
		{
			obj.second->update();
		}
		//Actualizacion de todas las entidades
	}
	
	void render()
	{
		graphics_scene.render();
		//Llama al render de graphics_scene
	}
};