#include <iostream>
#include <SDL.h>
#include "Game.h"
#include <memory>
#include <functional>


Game::Game()
{
	std::cout << "we out here!" << "\n";
}

Game::~Game()
{
	SDL_Quit();
}

void Game::initialize()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
	{
		std::cerr << "Error initializing SDL" << std::endl;
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
		std::cerr << "Error creating SDL Window" << std::endl;
		return;
	}

	renderer = std::unique_ptr<SDL_Renderer, std::function<void(SDL_Renderer*)>>(
		SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC),
		SDL_DestroyRenderer
	);

	if (renderer == nullptr) 
	{
		std::cerr << "Error creating SDL Window" << std::endl;
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
void Game::update()
{

}
void Game::render()
{
	SDL_Renderer* sdlRenderer = renderer.get();

	SDL_SetRenderDrawColor(sdlRenderer, 255, 0, 0, 255);
	SDL_RenderClear(sdlRenderer);

	SDL_RenderPresent(sdlRenderer);
}