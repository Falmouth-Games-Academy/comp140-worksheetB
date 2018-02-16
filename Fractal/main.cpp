// main.cpp : Defines the entry point for the console application.
// Basic application layout source from the following tutorial
// http://www.willusher.io/pages/sdl2/

#include "stdafx.h"

int main(int, char**) 
{
	double windowWidth = 800;
	double windowHeight = 800;
	//Initialise the Video Part of SDL2
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		//Print out an error message to the screen if this fails
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	//Create a 800x800 window with the title Fractal
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



		for (double pixelY = 0; pixelY < windowHeight; pixelY++) {
			// TODO: Map the y coordinate into the range minY to maxY
			double y0 = (pixelY / windowHeight) * (maxY - minY) + minY;
			for (double pixelX = 0; pixelX < windowWidth; pixelX++){

				// TODO: Map the x coordinate into the range minX to maxX
				double x0 = (pixelX / windowWidth) * (maxX - minX) + minX;

				unsigned int pixelPosition = pixelY * (pitch / pixelFormat->BytesPerPixel) + pixelX;

				Uint32 colour = SDL_MapRGB(pixelFormat, 0, 0, 0);

				// TODO: implement the algorithm to colour a single pixel (x0, y0) of the fractal
				// Calculates x(i) and y(i)
				double currentX = (x0 * x0) - (y0 * y0) + x0;
				double currentY = (2.0 * x0 * y0) + y0;
				// The code below simply fills the screen with random pixels
				for (int i = 0; i < 50; i++)
				{
					// Calculates x(i+1) and y(i+1)
					double nextX = (currentX * currentX) - (currentY * currentY) + x0;
					double nextY = (2 * currentX * currentY) + y0;
					if ((nextX * nextX) + (nextY * nextY) >= 4)
					{
						// Sets outside lines' colour
						colour = SDL_MapRGB(pixelFormat, i * 255 / 50, i * 255 / 50, i * 255 / 50);
						break;
					}
					// Converts currentX and currentY to nextX and nextY so that we can get next value of x(i+1) and y(i+1)
					currentX = nextX;
					currentY = nextY;
				}

				// Write the pixel
				// Now we can set the pixel(s) we want.
				pixels[pixelPosition] = colour;
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