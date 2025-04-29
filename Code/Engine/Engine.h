#pragma once

#include <ImGui/imgui.h>
#include <ImGui/imgui_impl_glfw.h>
#include <ImGui/imgui_impl_opengl3.h>

#include <memory>
#include "../Scene/Scene.h"

class GLFWwindow;

//Window data
class Window
{
	GLFWwindow* m_window;
	int m_width, m_height;

public:
	Window(int _width, int _height);
	~Window();
	GLFWwindow* GetWindow();

	int GetWindowWidth();
	int GetWindowHeight();

	void SetWindowWidth(int _width);
	void SetWindowHeight(int _heigth);

};

//Engine of the game
//The engine of the game follows the singleton design pattern
class Engine
{
private:
	//Singleton instance of the engine
	static std::shared_ptr<Engine> m_instance;
	double m_deltaTime;

	std::shared_ptr<Window> m_windowData;
	std::shared_ptr<Scene> m_activeScene;

	std::shared_ptr<Shader> m_gameShader;
public:
	Engine();
	~Engine();

	static std::shared_ptr<Engine> GetInstance();
	std::shared_ptr<Window> GetWindowData();
	double GetDeltaTime();
	std::shared_ptr<Scene> GetActiveScene();
	std::shared_ptr<Shader> GetGameShader();

	void SetDeltaTime(double _deltaTime);
	void SetActiveScene(std::shared_ptr<Scene> _scene);
	void SetShader(const std::shared_ptr<Shader>& _shader);

	void InitGame();
};
