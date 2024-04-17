#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
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

void Game::setup()
{

}

void Game::update()
{

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

	SDL_Rect dstRect{10, 10, 32, 32};
	SDL_RenderCopy(sdlRenderer, texture.get(), nullptr, &dstRect);

	SDL_RenderPresent(sdlRenderer);
}