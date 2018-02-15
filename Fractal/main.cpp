// main.cpp : Defines the entry point for the console application.
// Basic application layout source from the following tutorial
// http://www.willusher.io/pages/sdl2/

#include "stdafx.h"
#include <complex>

int main(int, char**)
{
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
	while (!quit)
	{
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
		
		for (int pixelY = 0; pixelY < windowHeight; pixelY++) {
			double y0 = (pixelY / (double)windowHeight) * (maxY - minY) + minY;

			for (int pixelX = 0; pixelX < windowWidth; pixelX++) {
				double x0 = (pixelX / (double)windowWidth) * (maxX - minX) + minX;

				unsigned int pixelPosition = pixelY * (pitch / pixelFormat->BytesPerPixel) + pixelX;

				//the current iteration cycle
				int iteration = 0;

				//the max amount of iterations
				int maxIterations = 50;

				double lastX = 0;
				double lastY = 0;

				while (iteration < maxIterations)
				{
					double tempY = (2 * lastX * lastY) + y0;
					double tempX = ((lastX * lastX) - (lastY * lastY)) + x0;

					iteration++;

					if ((tempX * tempX) + (tempY * tempY) >= 4)
					{
						Uint32 colour = SDL_MapRGB(pixelFormat, iteration * 255 / maxIterations, 0, 0);
						pixels[pixelPosition] = colour;
						break;
					}

					lastX = tempX;
					lastY = tempY;
				}
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