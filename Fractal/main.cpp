// main.cpp : Defines the entry point for the console application.
// Basic application layout source from the following tutorial
// http://www.willusher.io/pages/sdl2/

#include "stdafx.h"
#include <complex>

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
		/*
		SDL_Window *window;
		SDL_Renderer *renderer;
		SDL_CreateWindowAndRenderer(windowWidth, windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS, &window, &renderer);
		SDL_SetWindowPosition(window, 65, 126);


		enum { PaletteSize = 32 };
		int palette[PaletteSize + 1][3];
		for (int i = 0; i <= PaletteSize; ++i)
		{
			palette[i][0] = i < 2 * PaletteSize / 3 ? i * 255 * 3 / (2 * PaletteSize) : 255;
			palette[i][1] = i < PaletteSize / 3 ? 0 : (i - PaletteSize / 3) * 255 * 3 / (2 * PaletteSize);
			palette[i][2] = 0;
		}

		for (int y = 0; y < windowHeight; ++y)
			for (int x = 0; x < windowWidth; ++x)
			{
				std::complex<double> c(0.5 * (x - (windowWidth - windowHeight) / 2) / windowHeight * 4.0 - 2.0, 0.5 * y / windowHeight * 4.0 - 2.0);
				std::complex<double> z(0.0, 0.0);
				int cnt = 0;
				while (cnt < PaletteSize)
				{
					z = z * z + c;
					if (abs(z) > 2.0)
						break;
					++cnt;
				}
				SDL_SetRenderDrawColor(renderer, palette[cnt][0], palette[cnt][1], palette[cnt][2], 0xff);
				SDL_RenderDrawPoint(renderer, x, y);
			} */
		
		for (int pixelY = 0; pixelY < windowHeight; pixelY++) {
			// TODO: Map the y coordinate into the range minY to maxY
			double y0 = (pixelY / windowHeight) * (maxY - minY) + minY;

			for (int pixelX = 0; pixelX < windowWidth; pixelX++) {
				// TODO: Map the x coordinate into the range minX to maxX
				double x0 = (pixelX / windowWidth) * (maxX - minX) + minX;

				unsigned int pixelPosition = pixelY * (pitch / pixelFormat->BytesPerPixel) + pixelX;

				// TODO: implement the algorithm to colour a single pixel (x0, y0) of the fractal
				// The code below simply fills the screen with random pixels

				int i = 1;
				int maxIterations = 50;

				double lastX = x0;
				double lastY = y0;

				bool isTrue = false;

				while (i < maxIterations)
				{

					double tempY = (2 * lastX * lastY) + y0;
					double tempX = ((lastX * lastX) - (lastY * lastY)) + x0;

					i++;
					if ((tempX * tempX) + (tempY * tempY) >= 4)
					{
						isTrue = true;
						break;
					}
				}

				if (isTrue == true)
				{
					Uint32 colour = SDL_MapRGB(pixelFormat, rand() % 255, 0, 0);
					pixels[pixelPosition] = colour;
				}
				else
				{
					Uint32 colour = SDL_MapRGB(pixelFormat, 0, 0, rand() % 255);
					pixels[pixelPosition] = colour;
				}

				// Write the pixel
				// TODO: change this for desired pixel colour value
				// Now we can set the pixel(s) we want.
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