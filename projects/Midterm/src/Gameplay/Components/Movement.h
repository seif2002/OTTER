#pragma once
#include "IComponent.h"
#include "Gameplay/Physics/RigidBody.h"

/// <summary>
/// A simple behaviour that applies an impulse along the Z axis to the 
/// rigidbody of the parent when the space key is pressed
/// </summary>
class Movement : public Gameplay::IComponent {
public:
	typedef std::shared_ptr<Movement> Sptr;

	Movement();
	virtual ~Movement();

	virtual void Awake() override;
	virtual void Update(float deltaTime) override;

public:
	virtual void RenderImGui() override;
	MAKE_TYPENAME(Movement);
	virtual nlohmann::json ToJson() const override;
	static Movement::Sptr FromJson(const nlohmann::json& blob);

protected:
	float _impulse2;

	Gameplay::Physics::RigidBody::Sptr _body;
};