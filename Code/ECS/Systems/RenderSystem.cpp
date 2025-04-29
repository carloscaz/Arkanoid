#include "RenderSystem.h"
#include "../ComponentManager.h"
#include "../Engine/Engine.h"

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>

std::shared_ptr<RenderSystem> RenderSystem::m_instance = nullptr;
RenderSystem::RenderSystem()
{
}
RenderSystem::RenderSystem(std::shared_ptr<ComponentManager> _manager) :
	System(_manager)
{}

std::shared_ptr<RenderSystem> RenderSystem::GetInstance()
{
	if (m_instance == nullptr)
	{
		m_instance = std::shared_ptr<RenderSystem>(new RenderSystem());
	}

	return m_instance;
}

void RenderSystem::Tick(double _deltaTime)
{
	//Activate shader
	Engine::GetInstance()->GetGameShader()->UseShader();
	//Iterate through all the render components of the component manager
	for (std::pair<const EntityID, RenderComponent>& pair : m_componentManager->GetRenderComponents())
	{
		//Get the ID from the first element of the unordered map pair
		EntityID id = pair.first;

		//Create a modelMatrix (using vec3 instead vec2 because glm::translate only accepts glm::vec3 as parameter)
		TransformComponent& transformCop = m_componentManager->GetComponent<TransformComponent>(id);
		RenderComponent& renderComp = m_componentManager->GetComponent<RenderComponent>(id);
		renderComp.GetShader().UseShader();

		if (renderComp.GetActive() == true)
		{
			glm::mat4 modelMatrix = glm::translate(glm::mat4(1.0), glm::vec3(transformCop.GetPosition().x, transformCop.GetPosition().y, 0));
			modelMatrix = glm::rotate(modelMatrix, transformCop.GetRotation().x, glm::vec3(1, 0, 0));
			modelMatrix = glm::rotate(modelMatrix, transformCop.GetRotation().y, glm::vec3(0, 1, 0));
			modelMatrix = glm::rotate(modelMatrix, 0.0f, glm::vec3(0, 0, 1));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(transformCop.GetScale().x * renderComp.GetTexture().GetWidth(), transformCop.GetScale().y * renderComp.GetTexture().GetHeight(), 0.0f));

			//Create a projection matrix (using vec3 instead vec2 because glm::translate only accepts glm::vec3 as parameter)
			glm::mat4 projectionMatrix = glm::ortho(0.0f, (float)Engine::GetInstance()->GetWindowData()->GetWindowWidth(), 0.0f, (float)Engine::GetInstance()->GetWindowData()->GetWindowHeight(), 0.1f, 100.0f);
			Engine::GetInstance()->GetGameShader()->SetMat4("Proj", projectionMatrix);

			//Create a view matrix ((using vec3 instead vec2 because glm::translate only accepts glm::vec3 as parameter)
			glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0, 0, 5), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
			Engine::GetInstance()->GetGameShader()->SetMat4("View", viewMatrix);

			//Bind the texture of the render component to OpenGL
			renderComp.GetTexture().BindTexture();

			//Send the matrix data to the shader
			renderComp.GetShader().SetMat4("Model", modelMatrix);

			//Render the buffer of the render component
			renderComp.GetBuffer().Draw();
		}
	}

	if (Engine::GetInstance()->GetActiveScene()->GetSceneType() == SceneType::MainLevel)
	{
		ImGui::SetNextWindowBgAlpha(0.0f); // Fondo completamente transparente

		ImGuiWindowFlags window_flags =
			ImGuiWindowFlags_NoTitleBar |
			ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_NoScrollbar |
			ImGuiWindowFlags_NoSavedSettings |
			ImGuiWindowFlags_NoInputs |
			ImGuiWindowFlags_NoBackground;
		//ImGuiWindowFlags_NoCollapse;

		ImGui::SetNextWindowPos(ImVec2(Engine::GetInstance()->GetWindowData()->GetWindowWidth() - 150, 20));
		ImGui::SetNextWindowSize(ImVec2(150, 50));
		if (ImGui::Begin(" ", nullptr, window_flags))
		{
			std::string score = std::to_string(m_componentManager->GetComponent<PlayerComponent>(m_componentManager->GetPlayerComponents().begin()->first).GetPlayerScore());
			ImGui::Text(("Player Score: " + score).c_str());
		}
		ImGui::End();
	}

	
}
