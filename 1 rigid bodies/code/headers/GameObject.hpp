
// Comentario de cabecera

#pragma once

#include <Model_Obj.hpp>
#include "Rigid_Body.hpp"
#include <memory>
#include <string>
#include <map>
#include "Sphere_Shape.hpp"
#include "Cylinder_Shape.hpp"
#include "Scene.hpp"
#include "Trigger.hpp"

class Scene;
class DemoScene;

using glt::Model_Obj;
using std::shared_ptr;

class GameObject
{
protected:


	struct Piece
	{
		std::shared_ptr<Model_Obj >  graphics_model;
		std::shared_ptr<Rigid_Body>  rigidbody;
		float graphicsScale;
		bool active;
	};

	struct Joint
	{
		std::shared_ptr<btTypedConstraint > joint;
		std::shared_ptr<Rigid_Body> bodyA;
		std::shared_ptr<Rigid_Body> bodyB;
	};

	typedef std::map< std::string, Piece > PieceList;
	typedef std::map< std::string, std::shared_ptr<btHingeConstraint > > HingeList;
	typedef std::map< std::string, std::shared_ptr<btPoint2PointConstraint > > PtoPList;
	typedef std::map< std::string, std::shared_ptr<Trigger > > TriggerList;



	PieceList pieces;
	HingeList hingejoints;
	PtoPList ptoPJoints;
	TriggerList triggers;
	int       mask;

public:

	// , Shape & shape
	GameObject(int mask = 0) :mask(mask)
	{
		//scene->getGraphicScene();
	}

	void add_piece(const std::string & name, const std::string & model_obj_path, const shared_ptr< Rigid_Body > & rigid_body, float scale, bool active)
	{
		//pieces[name];
		Piece & piece = pieces[name];

		piece.graphics_model.reset(new Model_Obj(model_obj_path));
		piece.rigidbody = rigid_body;
		piece.graphicsScale = scale;
		piece.active = active;

		if (piece.active == true)
		{
			piece.rigidbody->get()->setActivationState(ACTIVE_TAG);
		}
		else
		{
			piece.rigidbody->get()->setActivationState(ISLAND_SLEEPING);
		}


		// Hay que añadir a scene el Model_Obj y a physics_world
	}

	void add_PtP_joint(const std::string & name, const shared_ptr< Rigid_Body > & bodyA, const shared_ptr< Rigid_Body > & bodyB, const btVector3 & pivotInA, const btVector3 & pivotInB)
	{
		std::shared_ptr<btPoint2PointConstraint > & joint = ptoPJoints[name];
		joint.reset(new btPoint2PointConstraint(*bodyA->get(), *bodyB->get(), pivotInA, pivotInB));
		//joint.bodyA = bodyA;
		//joint.bodyB = bodyB;

	}

	void add_Hinge_joint(const std::string & name, const shared_ptr< Rigid_Body > & bodyA, const shared_ptr< Rigid_Body > & bodyB, const btVector3 &pivotInA, const btVector3 &pivotInB, const btVector3 &axisInA, const btVector3 &axisInB, bool useReferenceFrameA = false)
	{
		std::shared_ptr<btHingeConstraint > & joint = hingejoints[name];
		joint.reset(new btHingeConstraint(*bodyA->get(), *bodyB->get(), pivotInA, pivotInB, axisInA, axisInB));
		//joint.bodyA = bodyA;
		//joint.bodyB = bodyB;

	}
	void add_Trigger(const std::string & name, const shared_ptr< Trigger > & _trigger)
	{
		std::shared_ptr<Trigger >  & trigger=triggers[name] ;
		trigger = _trigger;
	}

	void link_pieces_to_scene(glt::Render_Node & graphics_scene, Physics_World & physics_world)
	{
		for (auto & piece : pieces)
		{
			graphics_scene.add(piece.first, piece.second.graphics_model);
			physics_world.add(piece.second.rigidbody);
			// añadir al mundo físico (con o sin máscara -> mask != 0)
		}
	}

	void link_joints_to_scene(Physics_World & physics_world)
	{
		for (auto & joint : hingejoints)
		{
			physics_world.addConstraint(joint.second);
			// añadir al mundo físico (con o sin máscara -> mask != 0)
		}
		for (auto & joint : ptoPJoints)
		{
			physics_world.addConstraint(joint.second);
			// añadir al mundo físico (con o sin máscara -> mask != 0)
		}
	}

	void link_triggers_to_scene(Physics_World & physics_world) 
	{
		for (auto & trigger : triggers)
		{
			physics_world.addCollision(trigger.second);
			// añadir al mundo físico (con o sin máscara -> mask != 0)
		}
	}

	virtual void update()
	{
		btTransform physicsTransform;
		for (auto & piece : pieces)
		{
			piece.second.rigidbody->get()->getMotionState()->getWorldTransform(physicsTransform);
			glm::mat4 graphicsTransform;
			physicsTransform.getOpenGLMatrix(glm::value_ptr(graphicsTransform));
			piece.second.graphics_model->set_transformation(graphicsTransform);
			piece.second.graphics_model->scale(piece.second.graphicsScale);

		}

	}

	void setPieceActive(const std::string & name, bool active)
	{
		pieces[name].active = active;
		if (pieces[name].active == true)
		{
			pieces[name].rigidbody->get()->setActivationState(ACTIVE_TAG);

		}
		else
		{
			pieces[name].rigidbody->get()->setActivationState(ISLAND_SLEEPING);
		}
		pieces[name].graphics_model->set_visible(active);

	}

	btVector3 getForwardVector(const std::string & name)
	{
		btTransform WheelTransform = pieces[name].rigidbody->get()->getWorldTransform();
		btScalar WheelMatrix[16];
		WheelTransform.getOpenGLMatrix(WheelMatrix);
		return btVector3(WheelMatrix[8], WheelMatrix[9], WheelMatrix[10]);
	}



	virtual void  apply_force(float x, float y, float z, float magnitude)
	{
	}



};
