#include <GLFW/glfw3.h>
#include "Gameplay/GameObject.h"
#include "Gameplay/Scene.h"
#include "Utils/ImGuiHelper.h"
#include "Gameplay/Physics/ICollider.h"
#include "Gameplay/Physics/RigidBody.h"
#include "Gameplay/Components/PuckBounce.h"
#include "Gameplay/Components/ComponentManager.h"


void PuckBounce::Awake()
{
	_body = GetComponent<Gameplay::Physics::RigidBody>();
	if (_body == nullptr) {
		IsEnabled = false;
	}
	_renderer = GetComponent<RenderComponent>();
	
}

void PuckBounce::RenderImGui() {
	LABEL_LEFT(ImGui::DragFloat, "Impulse4", &_impulse4, 1.0f);
}

PuckBounce::PuckBounce() :
	IComponent(),
	_renderer(nullptr),
	EnterMaterial(nullptr),
	ExitMaterial(nullptr),
	_impulse4(0.4f)
{}
PuckBounce::~PuckBounce() = default;

void PuckBounce::OnEnteredTrigger(const Gameplay::Physics::TriggerVolume::Sptr& trigger)
{

	if (trigger->GetGameObject()->Name == "RedNet")
	{
		LOG_INFO("Player 2 Score");
		ResetPuckRed();
	}
	if (trigger->GetGameObject()->Name == "BlueNet")
	{
		LOG_INFO("Player 1 Score");
		ResetPuckBlue();
	}
	LOG_INFO("TEST {}",trigger->GetGameObject()->Name);

}

void PuckBounce::ResetPuckRed()
{
	GetGameObject()->SetPosition(glm::vec3(0.0f, 3.0f, 0.0f));
}

void PuckBounce::ResetPuckBlue()
{
	GetGameObject()->SetPosition(glm::vec3(0.0f, -3.0f, 0.0f));
}

nlohmann::json PuckBounce::ToJson() const {
	return {
		{ "enter_material", EnterMaterial != nullptr ? EnterMaterial->GetGUID().str() : "null" },
		{ "exit_material", ExitMaterial != nullptr ? ExitMaterial->GetGUID().str() : "null" }
	};
}

PuckBounce::Sptr PuckBounce::FromJson(const nlohmann::json& blob) {
	PuckBounce::Sptr result = std::make_shared<PuckBounce>();
	result->EnterMaterial = ResourceManager::Get<Gameplay::Material>(Guid(blob["enter_material"]));
	result->ExitMaterial = ResourceManager::Get<Gameplay::Material>(Guid(blob["exit_material"]));
	return result;
}

void PuckBounce::Update(float deltaTime)
{

}

