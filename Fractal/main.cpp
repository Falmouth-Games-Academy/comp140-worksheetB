// main.cpp : Defines the entry point for the console application.
// Basic application layout source from the following tutorial
// http://www.willusher.io/pages/sdl2/

#include "stdafx.h"
#include <cmath>
#include <string>
#include <iostream>

using namespace std;

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
	SDL_Window *window = SDL_CreateWindow("Fractal", 1000, 200, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
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

	// Show instructions on the console window
	cout << "Press 1 or 2 to choose a fractal, 1 for Mandlebrot, 2 for Julia:\n>";

	//Controls the game loop
	bool quit = false;

	//Set up for key press
	bool fractal1 = false;
	bool fractal2 = false;

	//Holds events coming from SDL
	SDL_Event event;
	//Game Loop, while quit is false
	while (!quit)
	{
		//Check for Messages from SDL
		while (SDL_PollEvent(&event))
		{
			//quit is generated when red cross is clicked
			if (event.type == SDL_QUIT)
			{
				quit = true;
			}
			// Key press to change fractals
			if (event.type == SDL_KEYDOWN)
			{
				if (event.key.keysym.sym == SDLK_1)
				{
					fractal2 = false;
					fractal1 = true;
				}
				if (event.key.keysym.sym == SDLK_2)
				{
					fractal1 = false;
					fractal2 = true;
				}
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

				int iteration = 0;
				/* Number of iterations to go through, the higher the number the more
				crisp the fractal image becomes */
				int numIterations = 100;

				// Set the initial x and y to 0 for the first iteration
				double lastX = 0;
				double lastY = 0;
				double thisX = 0.0;
				double thisY = 0.0;

				// While loop to go through
				while (iteration < numIterations)
				{
					// Funcions for the Mandelbrot x and y if "1" key is pressed
					if (fractal1 == true)
					{
						thisX = CalculateMandelbrotX(lastX, lastY, x0);
						thisY = CalculateMandelbrotY(lastX, lastY, y0);
					}

					// Funcions for the Julia Set x and y if "2" key is pressed
					if (fractal2 == true)
					{
						thisX = CalculateJuliaX(lastX, lastY, x0, iteration);
						thisY = CalculateJuliaY(lastX, lastY, y0, iteration);
					}
					
					// Inrease iteration number
					iteration++;

					// Fractal computation to determine shape (where next pixel colour is changed)
					if ((thisX * thisX) + (thisY * thisY) >= 4)
					{
						/* Write the pixel. Experimenting with various different colour combinations*/
						colourPixel = SDL_MapRGB(pixelFormat, iteration*255/ 300, iteration*iteration, thisY * thisX / iteration);
						//colourPixel = SDL_MapRGB(pixelFormat, iteration%255, iteration % 255, iteration % 255);
						//colourPixel = SDL_MapRGB(pixelFormat, (iteration+(int)thisX*10)%255, iteration%255, (iteration + (int)thisX * (int)thisY) %255);
						//colourPixel = SDL_MapRGB(pixelFormat, iteration*thisX, 255%(iteration*iteration), thisY);
						//colourPixel = SDL_MapRGB(pixelFormat, iteration, iteration*iteration, lastY);
			
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

/* Uses x and y values calculated in previous iteration (or 0 if just started)
to calculate values needed for this iteration */

/* Fuctions to calculate Mandelbrot fractal for x and y*/
double CalculateMandelbrotX(double lastX, double lastY, double xCoordinate)
{
	double thisX = ((lastX * lastX) - (lastY * lastY)) + xCoordinate;
	return thisX;
}
double CalculateMandelbrotY(double lastX, double lastY, double yCoordinate)
{
	double thisY = (2 * lastX * lastY) + yCoordinate;
	return thisY;
}

/* Fuctions to calculate a Julia fractal for x and y*/
double CalculateJuliaX(double lastX, double lastY, double xCoordinate, int iteration)
{
	double thisX = pow((lastX * lastX) + (lastY * lastY), (iteration / 2)) * cos(iteration * atan2(lastY, lastX)) + xCoordinate;
	return thisX;
}
double CalculateJuliaY(double lastX, double lastY, double yCoordinate, int iteration)
{
	double thisY = pow((lastX * lastX) + (lastY * lastY), (iteration / 2)) * sin(iteration * atan2(lastY, lastX)) + yCoordinate;
	return thisY;
}