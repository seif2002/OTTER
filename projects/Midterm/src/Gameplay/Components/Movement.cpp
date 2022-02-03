#include "Gameplay/Components/Movement.h"
#include <GLFW/glfw3.h>
#include "Gameplay/GameObject.h"
#include "Gameplay/Scene.h"
#include "Utils/ImGuiHelper.h"

void Movement::Awake()
{
	_body = GetComponent<Gameplay::Physics::RigidBody>();
	if (_body == nullptr) {
		IsEnabled = false;
	}
}

void Movement::RenderImGui() {
	LABEL_LEFT(ImGui::DragFloat, "Impulse2", &_impulse2, 1.0f);
}

nlohmann::json Movement::ToJson() const {
	return {
		{ "impulse2", _impulse2 }
	};
}

Movement::Movement() :
	IComponent(),
	_impulse2(0.1f)
{ }

Movement::~Movement() = default;

Movement::Sptr Movement::FromJson(const nlohmann::json& blob) {
	Movement::Sptr result = std::make_shared<Movement>();
	result->_impulse2 = blob["impulse2"];
	return result;
}

void Movement::Update(float deltaTime) 
{

	if (glfwGetKey(GetGameObject()->GetScene()->Window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		_body->ApplyImpulse(glm::vec3(0.2f, 0.0f, 0.0f));
	}
	if (glfwGetKey(GetGameObject()->GetScene()->Window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		_body->ApplyImpulse(glm::vec3(-0.2f, 0.0f, 0.0f));
	}
	if (glfwGetKey(GetGameObject()->GetScene()->Window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		_body->ApplyImpulse(glm::vec3(0.0f, -0.2f, 0.0f));
	}
	if (glfwGetKey(GetGameObject()->GetScene()->Window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		_body->ApplyImpulse(glm::vec3(0.0f, 0.2f, 0.0f));
	}
}

