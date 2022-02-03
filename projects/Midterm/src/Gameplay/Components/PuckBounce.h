#pragma once
#include "IComponent.h"
#include "Gameplay/Physics/RigidBody.h"
#include "Gameplay/Physics/TriggerVolume.h"
#include "Gameplay/Components/RenderComponent.h"

/// <summary>
/// A simple behaviour that applies an impulse along the Z axis to the 
/// rigidbody of the parent when the space key is pressed
/// </summary>
class PuckBounce : public Gameplay::IComponent {
public:
	typedef std::shared_ptr<PuckBounce> Sptr;

	PuckBounce();
	virtual ~PuckBounce();

	Gameplay::Material::Sptr EnterMaterial;
	Gameplay::Material::Sptr ExitMaterial;

	virtual void Awake() override;
	virtual void Update(float deltaTime) override;
	virtual void ResetPuckRed();
	virtual void ResetPuckBlue();
	virtual void OnEnteredTrigger(const std::shared_ptr<Gameplay::Physics::TriggerVolume>& trigger) override;
	virtual void RenderImGui() override;
	MAKE_TYPENAME(PuckBounce);
	virtual nlohmann::json ToJson() const override;
	static PuckBounce::Sptr FromJson(const nlohmann::json& blob);

protected:
	float _impulse4;
	
	RenderComponent::Sptr _renderer;
	Gameplay::Physics::RigidBody::Sptr _inertia;
	Gameplay::Physics::RigidBody::Sptr _motionState;
	Gameplay::Physics::RigidBody::Sptr _body;
};