#pragma once
#include <SDL.h>
#include <memory>
#include <functional>

constexpr auto FPS {60};
constexpr auto TARGET_FRAME_TIME{ 1000 / FPS };

class Game
{
private:
	bool isRunning{false};
	std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>> window{};
	std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer*)>> renderer{};

public:
	Game();
	~Game();

	void initialize();
	void run();
	void processInput();
	void setup();
	void update();
	void render();

	int windowWidth{};
	int windowHeight{};
};