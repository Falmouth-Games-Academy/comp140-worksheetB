// main.cpp : Defines the entry point for the console application.
// Basic application layout source from the following tutorial
// http://www.willusher.io/pages/sdl2/

#include "stdafx.h"

int Mandelbrot_fractal(double x0, double y0, int maxIterations)
{
	double x = 0, y = 0;
	int iter = 0;

	while ((x*x) + (y*y) <= 4 && iter < maxIterations)
	{
		double nextX = (x*x) - (y*y) + x0;
		y = (2 * x*y) + y0;
		x = nextX;
		iter++;
	}

	return iter;
}

Uint32 GetColor()
{

}

int main(int, char**) 
{
	int windowWidth = 1200;
	int windowHeight = 1200;
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

		// add some extra layers for a cool fx
		int layers = 5;
		for (int layer = 0; layer <= layers; layer++)
		{
			// work out the amount of interrates, the lower the iter the more basic the fractal is
			int iterations = 25 + (25 * layer);

			for (int pixelY = 0; pixelY < windowHeight; pixelY++) {
				//Map the y coordinate into the range minY to maxY
				double y0 = ((double)pixelY / windowHeight) * (maxY - minY) + minY;

				for (int pixelX = 0; pixelX < windowWidth; pixelX++) {

					// Map the x coordinate into the range minX to maxX
					double x0 = ((double)pixelX / windowWidth) * (maxX - minX) + minX;

					unsigned int pixelPosition = pixelY * (pitch / pixelFormat->BytesPerPixel) + pixelX;

					// iterate to find the value of the pixel for the fractal
					int iter = Mandelbrot_fractal(x0, y0, iterations);
					// Write the pixel
					// work out the color for the pixel
					Uint32 colour = SDL_MapRGB(pixelFormat, 255, 255, 255); 
					bool set = true;	//should we set the pixel

					if (iter > ((float)iterations * 0.90f))
						colour = SDL_MapRGB(pixelFormat, 200 + ((55/layers) * layer), 200, 200);
					else if (iter > ((float)iterations * 0.2f))
						colour = SDL_MapRGB(pixelFormat, 100, 100 + ((155 / layers) * layer), 100);
					else if (iter > ((float)iterations * 0.1f))
						colour = SDL_MapRGB(pixelFormat, 50 , 50 , 50 + ((205 / layers) * layer));
					else
						set = false;

					if(set || layer == 0)
						// Now we can set the pixel(s) we want.
						pixels[pixelPosition] = colour;
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