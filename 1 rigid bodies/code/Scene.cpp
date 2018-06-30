#pragma once

#include "headers\Scene.hpp"

void Scene::add_game_object(const std::string & name, std::shared_ptr<GameObject> & game_object)
{
	game_objects[name] = game_object;
	//Linkear piezas
	game_objects[name]->link_pieces_to_scene(graphics_scene, physics_world);
	//Linkear joints
	game_objects[name]->link_joints_to_scene(physics_world);
	//Linkear triggers
	game_objects[name]->link_triggers_to_scene(physics_world);

	//graphics_scene.add(name, game_object->GetModel());
	//physics_world.add(game_object->GetBody());
}

void Scene::add_game_object(const std::string & name, std::shared_ptr<GameObject> & game_object, int group, int mask)
{
	game_objects[name] = game_object;
	game_objects[name]->link_pieces_to_scene(graphics_scene, physics_world);
	game_objects[name]->link_joints_to_scene(physics_world);
	game_objects[name]->link_triggers_to_scene(physics_world);


	//graphics_scene.add(name, game_object->GetModel());
	//physics_world.addWithMask( game_object->GetBody(),(short)group,(short)mask);
}

void Scene::create_scene() 
{
	// Se crean los elementos (nodos) y la escena a la que se añadirán:

	std::shared_ptr< glt::Camera      > camera(new glt::Camera(20.f, 1.f, 400, 1.f));
	std::shared_ptr< glt::Light       > light(new glt::Light);

	// Se añaden los nodos a la escena:

	graphics_scene.add("camera", camera);
	graphics_scene.add("light", light);

	graphics_scene["light"]->translate(glt::Vector3(10.f, 10.f, 10.f));
	graphics_scene["camera"]->translate(glt::Vector3(60.f, 30.f, 0));
	graphics_scene["camera"]->rotate_around_y(1.6f);
	graphics_scene["camera"]->rotate_around_x(-0.2f);
}

void Scene::reset_viewport(const sf::Window & window, glt::Render_Node & scene)
{
	GLsizei width = GLsizei(window.getSize().x);
	GLsizei height = GLsizei(window.getSize().y);

	scene.get_active_camera()->set_aspect_ratio(float(width) / height);

	glViewport(0, 0, width, height);
}

GameObject *  Scene::get_game_object(const std::string & name)
{
	//Si lo encuentra retorna un puntero o sino retorna null
	if (game_objects.count(name))
	{
		return game_objects[name].get();
	}
	else
	{
		return nullptr;
	}
}