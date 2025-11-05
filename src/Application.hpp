#pragma once

#include "Util.hpp"
#include "Game.hpp"
#include "Window.hpp"

class Application {
private:
	static Application* instance;
	Window* window;
	Application();
	Application(WindowConfig* windowConfig);
	Application(int width, int height, const std::string& title);
public:

	static Application* getInstance();
	static Application* getInstance(WindowConfig* windowConfig);
	static Application* getInstance(int width, int height, const std::string& title);
	Window* getWindow() {
		return this->window;
	}
	~Application();

	void run();

};
