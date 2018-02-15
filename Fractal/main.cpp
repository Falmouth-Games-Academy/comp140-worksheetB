// main.cpp : Defines the entry point for the console application.
// Basic application layout source from the following tutorial
// http://www.willusher.io/pages/sdl2/

#include "stdafx.h"

int main(int, char**) 
{
	int windowWidth = 800;
	int windowHeight = 800;
	double doubleWindowWidth = 800;
	double doubleWindowHeight = 800;
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
			// Map the y coordinate into the range minY to maxY
			double y0 = (pixelY / doubleWindowWidth) * (maxY - minY) + minY;

			for (int pixelX = 0; pixelX < windowWidth; pixelX++){

				// Map the x coordinate into the range minX to maxX
				double x0 = (pixelX / doubleWindowWidth) * (maxX - minX) + minX;

				unsigned int pixelPosition = pixelY * (pitch / pixelFormat->BytesPerPixel) + pixelX;

				// algorithm to colour a single pixel (x0, y0) of the fractal
				double lastX = x0; // used to store the X value for recursion
				double lastY = y0; // used to store the Y value for recursion
				int i = 0; // counter
				int iterations = 40; // max number of iterations

				while  (i < iterations) {
					double currentX = ((lastX * lastX) - (lastY * lastY)) + x0;
					double currentY = (2 * lastX * lastY) + y0;
					double smallestValue = (currentX * currentX) + (currentY * currentY);
					i++;
					lastX = currentX; // set the current X value to the variable to be used in the next iteration
					lastY = currentY; // set the current Y value to the variable to be used in the next iteration
					if (smallestValue >= 4) {
						// Set Pixel colour
						int tempColour = 255 - (i * 5); //  uses the current value of i to help pick a colour for the green value
						Uint32 colour = SDL_MapRGB(pixelFormat, 0, tempColour, 140);
						// Now we can set the pixel(s) we want.
						pixels[pixelPosition] = colour;
						break;
					}
					else if (i == iterations) {
						// Set Pixel colour
						Uint32 colour = SDL_MapRGB(pixelFormat, 0, 0, 0);
						// Now we can set the pixel(s) we want.
						pixels[pixelPosition] = colour;
					}
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