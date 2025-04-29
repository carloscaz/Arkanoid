#include <iostream>
#include "Engine/Engine.h"

int main()
{
	std::shared_ptr<Engine> engine = Engine::GetInstance();
	engine->InitGame();
}