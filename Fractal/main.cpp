// main.cpp : Defines the entry point for the console application.
// Basic application layout source from the following tutorial
// http://www.willusher.io/pages/sdl2/

#include "stdafx.h"

const unsigned int NumberOfIterations = 255;


Uint32 mandelbrot(double x, double y)
{
	double yComponent = y;
	double xComponent = x;

	for (int i = 0; i < NumberOfIterations; i++)
	{
		if (xComponent*xComponent + yComponent*yComponent >= 4)
		{
			i = (log(i) / log(255)) * 255;
			return SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGB888), i, 0, i);
		}
		double tempYComponent = yComponent;
		yComponent = (2 * xComponent * yComponent) + y;
		xComponent = (xComponent*xComponent) - (tempYComponent*tempYComponent) + x;
	}
	return SDL_MapRGB(SDL_AllocFormat(SDL_PIXELFORMAT_RGB888), 50, 0,50);
}

int main(int, char**) 
{
	bool fractal1 = true;
	int windowWidth = 800;
	int windowHeight = 800;
	//Initialise the Video Part of SDL2
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		//Print out an error message to the screen if this fails
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	//Creare a 800x800 window with the title Fractal
	SDL_Window *window = SDL_CreateWindow("Fractal", 100, 100, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		//Print out error if this fails
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	//Create a renderer
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == nullptr) {
		//Print error and cleanup
		SDL_DestroyWindow(window);
		std::cout << "SDL_CreateRenderer Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}
	//this stores the pixels retrieved from the texture
	Uint32 * pixels = NULL;
	//the pitch is the width of the texture in bytes
	int pitch;
	//Create a texture, STREAMING means that we will update the texture 
	SDL_Texture * fractalTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, windowWidth, windowHeight);
	//Get the pixel format the texture
	SDL_PixelFormat * pixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGB888);


	// Minimum and maximum coordinates for the fractal
	const double minX = -2, maxX = 1, minY = -1.5, maxY = 1.5;

	//Controls the game loop
	bool quit = false;
	//Holds events coming from SDL
	SDL_Event event;
	//Game Loop, while quit is false

	Uint64 NOW = SDL_GetPerformanceCounter();
	Uint64 LAST = 0;
	while (!quit)
	{
		
		NOW = SDL_GetPerformanceCounter();
		LAST = NOW;
		double deltaTime = (double)((NOW - LAST) * 1000 / SDL_GetPerformanceFrequency()); //gets Deltatime

		//Check for Messages from SDL
		while (SDL_PollEvent(&event)) {
			//quit is generated when red cross is clicked
			if (event.type == SDL_QUIT) {
				quit = true;
			}
		}

		//Clear the renderer
		SDL_RenderClear(renderer);

		
		//do drawing here
		SDL_LockTexture(fractalTexture, NULL, (void**)&pixels, &pitch);


		if (fractal1) // Mandlebrot Set
		{
			for (double pixelY = 0; pixelY < windowHeight; pixelY++)
			{
				double yLocation = (pixelY / windowHeight)*(maxY - minY) + minY;
				for (double pixelX = 0; pixelX < windowWidth; pixelX++)
				{
					double xLocation = (pixelX / windowWidth)*(maxX - minX) + minX;
					unsigned int pixelPosition = pixelY * (pitch / pixelFormat->BytesPerPixel) + pixelX;


					
					// Now we can set the pixel(s) we want.
					pixels[pixelPosition] = mandelbrot(xLocation, yLocation);
				}
			}
		}
		else //Dragon curve
		{
			for (int i = 0; i < NumberOfIterations; i++)
			{
				//unsigned int pixelPosition = pixelY * (pitch / pixelFormat->BytesPerPixel) + pixelX;
				//pixels[pixelPosition] =
			}
		}

		SDL_UnlockTexture(fractalTexture);
		
		SDL_RenderCopy(renderer, fractalTexture, NULL, NULL);
		//Display the work the renderer has been doing, this make something appear on the screen


		SDL_RenderPresent(renderer);
	}

	//cleanup!
	SDL_FreeFormat(pixelFormat);
	SDL_DestroyTexture(fractalTexture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
