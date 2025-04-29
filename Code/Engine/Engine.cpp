#include "Engine.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "../ECS/Entities/EntityManager.h"
#include "../ComponentManager.h"
#include "../ECS/Systems/PhysicsSystem.h"
#include "../ECS/Systems/RenderSystem.h"
#include "../ECS/Systems/CollisionSystem.h"
#include "../ECS/Systems/PlayerSystem.h"
#include "../ECS/Systems/BrickSystem.h"
#include "../ECS/Systems/PowerUpSystem.h"
#include "../ECS/Systems/BallSystem.h"
#include "../ECS/Systems/UISystem.h"
#include "../ECS/Systems/LevelSystem.h"

#include "../ECS/Systems/EventManager.h"
#include "../OpenGL/Text/Text.h" 

std::shared_ptr<Engine> Engine::m_instance = nullptr;

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//If the window size changes, update the dimensions of windowData
	Engine::GetInstance()->GetWindowData()->SetWindowWidth(width);
	Engine::GetInstance()->GetWindowData()->SetWindowHeight(height);
	glViewport(0, 0, width, height);
}

Engine::Engine()
{
	std::cout << "Engine Created" << std::endl;
}

Engine::~Engine()
{}

std::shared_ptr<Engine> Engine::GetInstance()
{
	//If doesn't exist an instance of the engine creates a new instance and return it
	if (m_instance == nullptr)
	{
		m_instance = std::make_shared<Engine>();
	}

	return m_instance;
}

std::shared_ptr<Window> Engine::GetWindowData()
{
	return m_windowData;
}

double Engine::GetDeltaTime()
{
	return m_deltaTime;
}

std::shared_ptr<Scene> Engine::GetActiveScene()
{
	return m_activeScene;
}

std::shared_ptr<Shader> Engine::GetGameShader()
{
	return m_gameShader;
}

void Engine::SetDeltaTime(double _deltaTime)
{
	if (_deltaTime > 0.016f)
	{
		m_deltaTime = 0.016f;
	}
	m_deltaTime = _deltaTime;
}

void Engine::SetActiveScene(std::shared_ptr<Scene> _scene)
{
	if (_scene != nullptr)
	{
		m_activeScene = _scene;
	}
}

void Engine::SetShader(const std::shared_ptr<Shader>& _shader)
{
	m_gameShader = _shader;
}



void Engine::InitGame()
{
	//Create a window with GLFW with default data
	m_windowData = std::make_shared<Window>(800, 600);
	glfwSetFramebufferSizeCallback(m_windowData->GetWindow(), framebuffer_size_callback);

	//Al the entities are goig to use the same shader so we use the same shader instance for all
	SetShader(std::make_shared<Shader>("Data/VertexShader.glsl", "Data/FragmentShader.glsl"));
	GetGameShader()->UseShader();

	//Create a global Event Manager
	EventManager& eventManager = EventManager::GetInstance();

	//Create all the systems of the game
	std::shared_ptr<PlayerSystem> playerSystem = PlayerSystem::GetInstance();
	std::shared_ptr<CollisionSystem>collisionSystem = CollisionSystem::GetInstance();
	std::shared_ptr<PhysicsSystem> physicsSystem = PhysicsSystem::GetInstance();
	std::shared_ptr<RenderSystem> renderSystem = RenderSystem::GetInstance();
	std::shared_ptr<BrickSystem> brickSystem = BrickSystem::GetInstance();
	std::shared_ptr<PowerUpSystem> powerUpSystem = PowerUpSystem::GetInstance();
	std::shared_ptr<BallSystem> ballSystem = BallSystem::GetInstance();
	std::shared_ptr<UISystem> uiSystem = UISystem::GetInstance();
	std::shared_ptr<LevelSystem> levelSystem = LevelSystem::GetInstance();

	//Register all the systems in the Event Manager
	eventManager.AddSystem(playerSystem);
	eventManager.AddSystem(collisionSystem);
	eventManager.AddSystem(physicsSystem);
	eventManager.AddSystem(renderSystem);
	eventManager.AddSystem(brickSystem);
	eventManager.AddSystem(powerUpSystem);
	eventManager.AddSystem(ballSystem);
	eventManager.AddSystem(uiSystem);
	eventManager.AddSystem(levelSystem);



	//Create a MainMenuLevel
	eventManager.SendMessage(CreateMainMenuEvent());

	//Init the loop of the game with a deltaTime
	double lastTime = glfwGetTime();
	while (!glfwWindowShouldClose(m_windowData->GetWindow()))
	{
		double deltaTime = glfwGetTime() - lastTime;
		SetDeltaTime(deltaTime);
		lastTime = glfwGetTime();

		//Draw a background color
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		levelSystem->Tick(deltaTime);

		playerSystem->Tick(deltaTime);
		physicsSystem->Tick(deltaTime);
		collisionSystem->Tick(deltaTime);
		brickSystem->Tick(deltaTime);
		powerUpSystem->Tick(deltaTime);
		ballSystem->Tick(deltaTime);

		//Configure ImGui to draw
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		renderSystem->Tick(deltaTime);

		//ImGui::ShowDemoWindow(); // Show demo window! :)


		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


		//Swap buffers
		glfwSwapBuffers(m_windowData->GetWindow());
		glfwPollEvents();

	}
	//Terminate the game
	glfwTerminate();
}

Window::Window(int _width, int _height) :
	m_width(_width),
	m_height(_height)
{
	//Init GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	//Create a GLFW Window with a width and height dimensions
	m_window = glfwCreateWindow(m_width, m_height, "Arkanoid - Carlos Caz Pretus", nullptr, nullptr);
	if (m_window == nullptr)
	{
		std::cout << "Error creating a GLFW Window" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(m_window);

	//Init Glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	//Set the viewport dimensions
	glViewport(0, 0, m_width, m_height);

	//Activate Blending in OpenGL
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiWindowFlags_NoCollapse;
	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	ImGuiStyle& style = ImGui::GetStyle();
	ImGui_ImplGlfw_InitForOpenGL(m_window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
	io.Fonts->AddFontDefault();
}

Window::~Window()
{}

GLFWwindow* Window::GetWindow()
{
	return m_window;
}

int Window::GetWindowWidth()
{
	return m_width;
}

int Window::GetWindowHeight()
{
	return m_height;
}

void Window::SetWindowWidth(int _width)
{
	m_width = _width;
}

void Window::SetWindowHeight(int _heigth)
{
	m_height = _heigth;
}
