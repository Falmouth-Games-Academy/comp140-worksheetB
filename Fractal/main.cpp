// main.cpp : Defines the entry point for the console application.
// Basic application layout source from the following tutorial
// http://www.willusher.io/pages/sdl2/

#include "stdafx.h"
#include "main.h"

int WidthOfTextureInBytes;

int windowWidth = 800;
int windowHeight = 800;

//Controls the game loop
bool bWantsToQuit = false;

int main(int, char**) 
{
	//Initialise the Video Part of SDL2
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		//Print out an error message to the screen if this fails
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;

		return 1;
	}

	//Create a 800x800 window with the title Fractal
	// Name, Position (X, Y of top left corner), size and width, is visible(?)
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

	//Create a texture, STREAMING means that we will update the texture 
	SDL_Texture * fractalTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_STREAMING, windowWidth, windowHeight);

	//Get the pixel format the texture
	SDL_PixelFormat * pixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGB888);

	// Minimum and maximum coordinates for the fractal
	const double minX = -2, maxX = 1, minY = -1.5, maxY = 1.5;

	//Holds events coming from SDL
	SDL_Event event;

	while (!bWantsToQuit)
	{
		while (SDL_PollEvent(&event)) 
		{
			CheckForQuit(event);
		}
		//Clear the renderer
		SDL_RenderClear(renderer);

		//do drawing here
		SDL_LockTexture(fractalTexture, NULL, (void**)&pixels, &WidthOfTextureInBytes);

		for (int pixelY = 0; pixelY < windowHeight; pixelY++)
		{
			for (int pixelX = 0; pixelX < windowWidth; pixelX++)
			{
				unsigned int pixelPosition = pixelY * (WidthOfTextureInBytes / pixelFormat->BytesPerPixel) + pixelX;

				double x0 = ((double)pixelX / windowWidth) * (maxX - minX) + minX;
				double y0 = ((double)pixelY / windowHeight) * (maxY - minY) + minY;

				double currentX = 0;
				double currentY = 0;

				int currentIteration = 0;
				int maxIterations = 175;

				double XSquared = 0;
				double YSquared = 0;

				while (((XSquared + YSquared) <= 4) && (currentIteration < maxIterations))
				{
					XSquared = currentX * currentX;
					YSquared = currentY * currentY;

					double nextX = (XSquared - YSquared) + x0;

					currentY = (2 * currentX * currentY) + y0;

					currentX = nextX;

					currentIteration++;
				}

				/// Background colour, coloured a pure red
				Uint32 colour = SDL_MapRGB(pixelFormat, 200, 0, 0);

				if (currentIteration > ((float)maxIterations * 0.99f))
				{
					/// Inside of the fractal, coloured a busy black
					colour = SDL_MapRGB(pixelFormat, rand() % 30, rand() % 30, rand() % 30);
				}
				else if (currentIteration > ((float)maxIterations * 0.2f))
				{
					/// Inner border, coloured a bright yellow
					colour = SDL_MapRGB(pixelFormat, 255, 255, 0);
				}
				else if (currentIteration > ((float)maxIterations * 0.1f))
				{
					/// Outer border, coloured a strong orange
					colour = SDL_MapRGB(pixelFormat, 255, 140, 0);
				}
				pixels[pixelPosition] = colour;
			}
		}
		SDL_UnlockTexture(fractalTexture);
		
		SDL_RenderCopy(renderer, fractalTexture, NULL, NULL);

		//Display the work the renderer has been doing, this makes something appear on the screen
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

void CheckForQuit(SDL_Event &event)
{
	switch (event.type)
	{
	case SDL_QUIT:
	{
		bWantsToQuit = true;
		break;
	}
	case SDL_KEYDOWN:
	{
		if (event.key.keysym.sym == SDLK_ESCAPE)
		{
			bWantsToQuit = true;
		}
		break;
	}
	}
}
