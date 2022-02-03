#include "Gameplay/Components/ResetPosition.h"
#include "Gameplay/Components/ComponentManager.h"
#include "Gameplay/GameObject.h"

ResetPosition::ResetPosition():
	IComponent(),
	_renderer(nullptr),
	EnterMaterial(nullptr),
	ExitMaterial(nullptr)
{ }
ResetPosition::~ResetPosition() = default;

void ResetPosition::OnEnteredTrigger(const Gameplay::Physics::TriggerVolume::Sptr& trigger) {
	if (_renderer && EnterMaterial) {
		_renderer->SetMaterial(EnterMaterial);
	}
	LOG_INFO("Entered trigger: {}", trigger->GetGameObject()->Name);
}

void ResetPosition::OnLeavingTrigger(const Gameplay::Physics::TriggerVolume::Sptr& trigger) {
	if (_renderer && ExitMaterial) {
		_renderer->SetMaterial(EnterMaterial);
	}
	LOG_INFO("Left trigger: {}", trigger->GetGameObject()->Name);
}

void ResetPosition::Awake() {
	_renderer = GetComponent<RenderComponent>();
}

void ResetPosition::RenderImGui() { }

nlohmann::json ResetPosition::ToJson() const {
	return {
		{ "enter_material", EnterMaterial != nullptr ? EnterMaterial->GetGUID().str() : "null" },
		{ "exit_material", ExitMaterial != nullptr ? ExitMaterial->GetGUID().str() : "null" }
	};
}

ResetPosition::Sptr ResetPosition::FromJson(const nlohmann::json& blob) {
	ResetPosition::Sptr result = std::make_shared<ResetPosition>();
	result->EnterMaterial = ResourceManager::Get<Gameplay::Material>(Guid(blob["enter_material"]));
	result->ExitMaterial  = ResourceManager::Get<Gameplay::Material>(Guid(blob["exit_material"]));
	return result;
}
