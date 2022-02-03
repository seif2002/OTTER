#pragma once
#include "IComponent.h"
#include "Gameplay/Physics/RigidBody.h"

/// <summary>
/// A simple behaviour that applies an impulse along the Z axis to the 
/// rigidbody of the parent when the space key is pressed
/// </summary>
class Movement2 : public Gameplay::IComponent {
public:
	typedef std::shared_ptr<Movement2> Sptr;

	Movement2();
	virtual ~Movement2();

	virtual void Awake() override;
	virtual void Update(float deltaTime) override;

public:
	virtual void RenderImGui() override;
	MAKE_TYPENAME(Movement2);
	virtual nlohmann::json ToJson() const override;
	static Movement2::Sptr FromJson(const nlohmann::json& blob);

protected:
	float _impulse3;

	Gameplay::Physics::RigidBody::Sptr _body;
};