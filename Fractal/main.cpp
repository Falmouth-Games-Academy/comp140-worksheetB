// main.cpp : Defines the entry point for the console application.
// Basic application layout source from the following tutorial
// http://www.willusher.io/pages/sdl2/

#include "stdafx.h"

enum class FractalType {
	Mandelbrot = 0,
	Julia = 1,
};

int main(int, char**) 
{
	FractalType fractalType = FractalType::Mandelbrot;
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

			// change fractal type with spacebar
			if (event.type == SDL_KEYDOWN) {
				if (event.key.keysym.sym == SDLK_SPACE) {
					fractalType = (fractalType == FractalType::Mandelbrot ? FractalType::Julia : FractalType::Mandelbrot);
				}
			}
		}

		//Clear the renderer
		SDL_RenderClear(renderer);

		
		//do drawing here
		SDL_LockTexture(fractalTexture, NULL, (void**)&pixels, &pitch);

		/*const double minX = -2.5, maxX = 1.0;
		const double minY = -1.0, maxY = 1.0;*/
		const double minX = -2.0, maxX = 1.0;
		const double minY = -1.5, maxY = 1.5;
		const double juliaCX = 0.25, juliaCY = 0.5;

		for (int pixelY = 0; pixelY < windowHeight; pixelY++) {
			// Map the y coordinate between minY and maxY
			double physicalY = minY + ((double)pixelY / (double)windowHeight * (maxY - minY));

			for (int pixelX = 0; pixelX < windowWidth; pixelX++){
				// Map the x coordinate between minX and maxX
				double physicalX = minX + ((double)pixelX / (double)windowWidth * (maxX - minX));

				unsigned int pixelPosition = pixelY * (pitch / pixelFormat->BytesPerPixel) + pixelX;
				Uint32 pixelColour = SDL_MapRGB(pixelFormat, 0, 0, 0);

				if (fractalType == FractalType::Mandelbrot) {
					int iteration;
					double lastXVal = physicalX;
					double lastYVal = physicalY;
					const int maxIterations = 200;

					for (iteration = 0; iteration < maxIterations; ++iteration) {
						double nextXVal = lastXVal * lastXVal - lastYVal * lastYVal + physicalX;
						double nextYVal = 2.0 * lastXVal * lastYVal + physicalY;

						if (nextXVal * nextXVal + nextYVal * nextYVal >= 4.0) {
							pixelColour = SDL_MapRGB(pixelFormat, iteration * 255 / maxIterations, iteration * 255 / maxIterations, iteration * 255 / maxIterations);
							break;
						}

						lastXVal = nextXVal;
						lastYVal = nextYVal;
					}
				} else /* FractalType::Julia */ {
					int iteration;
					double lastXVal = physicalX, lastYVal = physicalY;
					const int maxIterations = 20;

					for (iteration = 0; iteration < maxIterations; ++iteration) {
						double nextXVal = lastXVal * lastXVal - lastYVal * lastYVal + juliaCX;
						double nextYVal = 2.0 * lastXVal * lastYVal + juliaCY;

						if (nextXVal * nextXVal + nextYVal * nextYVal >= 4.0) {
							pixelColour = SDL_MapRGB(pixelFormat, iteration * 255 / maxIterations, iteration * 255 / maxIterations, iteration * 255 / maxIterations);
							break;
						}

						lastXVal = nextXVal;
						lastYVal = nextYVal;
					}
				}

				// Write the pixel
				// Now we can set the pixel(s) we want.
				pixels[pixelPosition] = pixelColour;
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