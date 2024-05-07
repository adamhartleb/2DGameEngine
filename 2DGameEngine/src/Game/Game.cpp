#include <SDL.h>
#include <SDL_image.h>
#include <glm/glm.hpp>
#include <memory>

#include "Game.h"
#include "../Logger/Logger.h"

Game::Game()
{
	Logger::Log("Game constructor was called!");
}

Game::~Game()
{
	Logger::Log("Game destructor was called!");
	SDL_Quit();
}

void Game::initialize()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
	{
		Logger::Err("Error initializing SDL");
		return;
	}

	SDL_DisplayMode displayMode{};
	SDL_GetCurrentDisplayMode(0, &displayMode);

	windowWidth = displayMode.w;
	windowHeight = displayMode.h;

	window = std::unique_ptr<SDL_Window, std::function<void(SDL_Window*)>>(
		SDL_CreateWindow(
			nullptr, 
			SDL_WINDOWPOS_CENTERED, 
			SDL_WINDOWPOS_CENTERED,
			windowWidth,
			windowHeight,
			SDL_WINDOW_BORDERLESS
		),
		SDL_DestroyWindow
	);

	if (window == nullptr) 
	{
		Logger::Err("Error creating SDL Window");
		return;
	}

	renderer = std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer*)>>(
		SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC),
		SDL_DestroyRenderer
	);

	if (renderer == nullptr) 
	{
		Logger::Err("Error creating SDL Window");
		return;
	}

	SDL_SetWindowFullscreen(window.get(), SDL_WINDOW_FULLSCREEN);

	isRunning = true;
}
void Game::run()
{
	while (isRunning)
	{
		processInput();
		update();
		render();
	}
}
void Game::processInput()
{
	SDL_Event sdlEvent{};
	while (SDL_PollEvent(&sdlEvent))
	{
		switch (sdlEvent.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
			{
				isRunning = false;
				break;
			}
		}
	}
}

glm::vec2 playerPosition{10.0, 20.0};
glm::vec2 playerVelocity{20.0, 0.0};

//void Game::setup()
//{
//	playerPosition = glm::vec2( 10.0, 20.0 );
//	playerVelocity = glm::vec2( 1.0, 0.0 );
//}

void Game::update()
{
	int timeToWait = TARGET_FRAME_TIME - (SDL_GetTicks() - previousFrameTimeMS);
	if (timeToWait > 0 && timeToWait <= TARGET_FRAME_TIME) 
	{
		SDL_Delay(timeToWait);
	}

	// Get how much time has passed from the previous frame in milliseconds.
	// We can then multiple the player velocity by the deltaTime to go from pixels per frame to pixels per second so our
	// physics isn't tied to the framerate. 
	double deltaTime = (SDL_GetTicks() - previousFrameTimeMS) / 1000.0;

	previousFrameTimeMS = SDL_GetTicks();

	playerPosition.x += playerVelocity.x * deltaTime;
	playerPosition.y += playerVelocity.y * deltaTime;
}
void Game::render()
{
	SDL_Renderer* sdlRenderer = renderer.get();

	SDL_SetRenderDrawColor(sdlRenderer, 21, 21, 21, 255);
	SDL_RenderClear(sdlRenderer);

	auto surface{ std::unique_ptr<SDL_Surface, std::function<void(SDL_Surface*)>>(
		IMG_Load("./assets/images/tank-tiger-right.png"),
		SDL_FreeSurface
	)};
	auto texture{ std::unique_ptr<SDL_Texture, std::function<void(SDL_Texture*)>>(
		SDL_CreateTextureFromSurface(sdlRenderer, surface.get()),
		SDL_DestroyTexture
	)};

	SDL_Rect dstRect{
		static_cast<int>(playerPosition.x), 
		static_cast<int>(playerPosition.y), 
		32, 
		32
	};
	SDL_RenderCopy(sdlRenderer, texture.get(), nullptr, &dstRect);

	SDL_RenderPresent(sdlRenderer);
}