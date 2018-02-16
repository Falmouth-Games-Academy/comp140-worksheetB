// main.cpp : Defines the entry point for the console application.
// Basic application layout source from the following tutorial
// http://www.willusher.io/pages/sdl2/

#include "stdafx.h"
#include <cmath>

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


		// Nested For Loop to go through every pixel in the window 
		for (int pixelY = 0; pixelY < windowHeight; pixelY++) 
		{
			// Map the y coordinate into the range minY to maxY
			double y0 = (pixelY / (double)windowHeight) * (maxY - minY) + minY;

			for (int pixelX = 0; pixelX < windowWidth; pixelX++)
			{
				/* The colour to set all pixels initially */
				Uint32 colourPixel = SDL_MapRGB(pixelFormat, 0, 0, 0);

				// Map the x coordinate into the range minX to maxX
				double x0 = (pixelX / (double)windowWidth) * (maxX - minX) + minX;

				unsigned int pixelPosition = pixelY * (pitch / pixelFormat->BytesPerPixel) + pixelX;

				// TODO: implement the algorithm to colour a single pixel (x0, y0) of the fractal

				int i = 0;
				/* Number of iterations to go through, the higher the number the more 
				crisp the fractal image becomes */
				int numIterations = 100;

				// Set the initial x and y to 0 for the first iteration
				double lastX = 0;
				double lastY = 0;

				// While loop to go through
				while (i < numIterations)
				{
					/* Uses x and y values calculated in previous iteration (or 0 if just started)
					to calculate values needed for this iteration */
					//double thisX = ((lastX * lastX) - (lastY * lastY)) + x0;
					//double thisY = (2 * lastX * lastY) + y0;

					// Julia set computation
					double thisX = pow((lastX * lastX) + (lastY * lastY), (i / 2)) * cos(i * atan2(lastY, lastX)) + x0;
					double thisY = pow((lastX * lastX) + (lastY * lastY), (i / 2)) * sin(i * atan2(lastY, lastX)) + y0;
					
					// Inrease iteration number
					i++;

					// Fractal computation to determine shape (where next pixel colour is changed)
					if ((thisX * thisX) + (thisY * thisY) >= 4)
					{
						/* Write the pixel. Smoothens the colour on the outside of the fractal, 
						gradually getting lighter through each iteration as i increases assuming 
						it passed the if statement*/
						colourPixel = SDL_MapRGB(pixelFormat, i*255/10, 0, 0);
						break;
					}

					// Previous values of x and y to be used in the next iteration
					lastX = thisX;
					lastY = thisY;
				
				}
				// Now we can set the pixel(s) we want.
				pixels[pixelPosition] = colourPixel;
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