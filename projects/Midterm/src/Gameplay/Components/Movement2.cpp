#include "Gameplay/Components/Movement2.h"
#include <GLFW/glfw3.h>
#include "Gameplay/GameObject.h"
#include "Gameplay/Scene.h"
#include "Utils/ImGuiHelper.h"

void Movement2::Awake()
{
	_body = GetComponent<Gameplay::Physics::RigidBody>();
	if (_body == nullptr) {
		IsEnabled = false;
	}
}

void Movement2::RenderImGui() {
	LABEL_LEFT(ImGui::DragFloat, "Impulse3", &_impulse3, 1.0f);
}

nlohmann::json Movement2::ToJson() const {
	return {
		{ "impulse3", _impulse3 }
	};
}

Movement2::Movement2() :
	IComponent(),
	_impulse3(0.1f)
{ }

Movement2::~Movement2() = default;

Movement2::Sptr Movement2::FromJson(const nlohmann::json& blob) {
	Movement2::Sptr result = std::make_shared<Movement2>();
	result->_impulse3 = blob["impulse3"];
	return result;
}

void Movement2::Update(float deltaTime) 
{

	if (glfwGetKey(GetGameObject()->GetScene()->Window, GLFW_KEY_A) == GLFW_PRESS)
	{
		_body->ApplyImpulse(glm::vec3(0.2f, 0.0f, 0.0f));
	}
	if (glfwGetKey(GetGameObject()->GetScene()->Window, GLFW_KEY_D) == GLFW_PRESS)
	{
		_body->ApplyImpulse(glm::vec3(-0.2f, 0.0f, 0.0f));
	}
	if (glfwGetKey(GetGameObject()->GetScene()->Window, GLFW_KEY_W) == GLFW_PRESS)
	{
		_body->ApplyImpulse(glm::vec3(0.0f, -0.2f, 0.0f));
	}
	if (glfwGetKey(GetGameObject()->GetScene()->Window, GLFW_KEY_S) == GLFW_PRESS)
	{
		_body->ApplyImpulse(glm::vec3(0.0f, 0.2f, 0.0f));
	}
}

