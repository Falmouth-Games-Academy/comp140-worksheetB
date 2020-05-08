// main.cpp : Defines the entry point for the console application.
// Basic application layout source from the following tutorial
// http://www.willusher.io/pages/sdl2/

#include "stdafx.h"

// Map the input within a given range on the screen (width or height accepted as input)
double mapTo(int input, int imageSize, double minValue, double maxValue)
{
	double range = maxValue - minValue;
	return input * (range / imageSize) + minValue;
}

// Formula given appears the formula for the Mandelbrot set: https://en.wikipedia.org/wiki/Mandelbrot_set
// Return number of iterations it took tod etermine whether the number is contained by the Mandelbrot Set.	Higher max_iterations will yield other results
int formula(double cr, double ci, int max_iterations)
{
	// This formula makes use of complex numbers i.e. zr is the real component and zi is the imaginary component
	int  i = 0;
	double zr = 0.0, zi = 0.0;
	while (i < max_iterations && zr * zr + zi * zi < 4.0)
	{
		// Apply given formula to generate imaginary and real components
		double aux = zr * zr - zi * zi + cr;
		zi = 2.0 * zr * zi + ci; 
		zr = aux;
		i++;
	}

	return i;
}

/* 
Sierpinski Carpet works by determining whether a pixel at coordinates x and y is contained within a square at that respective level 
(each square is 1/3 the size of the squares on the previous level, and are equidistant on the plane)
Source: https://en.wikipedia.org/wiki/Sierpinski_carpet -> original code snippet was found there;

For a simple 3x3 square:
> Only the middle pixel would be coloured because x = 1 and y = 1 and therefore x % 3 = 1 and y % 3 = 1:

XXX
X X
XXX

In the case of the 9x9 square: 
> The central area will have its center be 0 on the first iteration (x = 4 and y = 4)
> The rest of the pixels in the central area will have their x and y divided by 3 (x = 3, 4, 5 and y = 3, 4, 5)
> The resulted positions will be pairs of (1, 1), therefore will have a value of 0
> This process is then extrapolated to larger and larger squares to create the Serpinski carpet

XXXXXXXXX
X XX XX X
XXXXXXXXX
XXX   XXX
X X   X X
XXX   XXX
XXXXXXXXX
X XX XX X
XXXXXXXXX
*/
int findSierpinskiCarpet(int x, int y)
{
	while (x > 0 || y > 0)
	{
		//checks if the pixel is in the center for the current square level
		if (x % 3 == 1 && y % 3 == 1) 
			return 0;

		//x and y are decremented to check the next larger square level
		x /= 3; 
		y /= 3;
	}
	// if all possible square levels are checked and the pixel is not determined to be open it must be filled
	return 1; 
}

// Alternate version of the Serpinski carpet, I was experimenting with the normal Serpinski carpet and I ended up with this. Looked interesting enough that I would put as a separate algorithm.
int findSierpinskiCarpetAlt(int x, int y)
{
	int temp = x * y;
	while (temp > 0)
	{
		if (temp % 9 == 1)
			return 0;
		temp /= 9;
	}
	// if all possible square levels are checked and the pixel is not determined to be open it must be filled
	return 1;
}
/*
USAGE:

> Run program
> Input 1, 2, or 3 for a fractal algorithm and input settings if necessary
> Input 4 to quit the program

*/

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

		std::cout << "Which fractal would you like to display?\n";
		std::cout << "1. Mandelbrot set\n";
		std::cout << "2. Sierpinski carpet\n";
		std::cout << "3. Sierpinski carpet - alternative\n";
		std::cout << "4. Quit\n";

		// Use this variable to determine the user's choice in the "menu"
		int choice;
		std::cin >> choice;

		// Determine what algorithm to use or quit the program
		switch (choice)
		{
		case 1: 
		{
			// Fractal parameters
			int maxN = 0;

			// Custom number of iterations!
			std::cout << "Please input custom number of iterations:\n";
			std::cin >> maxN;

			// Use this to determine what colour scheme to use when displaying fractal
			int colourScheme = 0;

			// Get desired colour scheme input from user
			std::cout << "Please input desired colour scheme:\n";
			std::cout << "1. Default - Grayscale\n";
			std::cout << "2. Dev's Special\n";
			std::cin >> colourScheme;

			// Define ranges for real values and imaginary values
			double minR = -1.5, maxR = 0.7, minI = -1.0, maxI = 1.0;

			// Iterate through window pixels
			for (int y = 0; y < windowHeight; y++)
			{
				for (int x = 0; x < windowWidth; x++)
				{
					// Real component
					double cr = mapTo(x, windowWidth, minR, maxR);
					// Imaginary component
					double ci = mapTo(y, windowHeight, minI, maxI);

					// Get number of iterations
					int n = formula(cr, ci, maxN);

					// Colour parameters
					int r = (n % 256);
					int g = (n % 256);
					int b = (n % 256);

					// Switch based on user's deisred colour scheme
					// Create RGB components of colours
					switch (colourScheme)
					{
					case 1: 
					{
						r = (n % 256);
						g = (n % 256);
						b = (n % 256);
						break;
					}
					case 2:
					{
						r = (((x / 2 + y / 2) / 2) / (n % 256)) % 256;
						g = (n % 256) % 2 * 255;
						b = (n % 256) % 2 * 255;
						break;
					}
					default:
					{
						r = (n % 256);
						g = (n % 256);
						b = (n % 256);
						std::cout << "Invalid colour scheme detected, switching to Default\n";
						break;
					}
					}

					// Pixel position via 1D array
					unsigned int pixelPosition = y * (pitch / pixelFormat->BytesPerPixel) + x;

					// Set pixel colour
					Uint32 colour = SDL_MapRGB(pixelFormat, r, g, b);
					pixels[pixelPosition] = colour;
				}
			}
			break;
		}
		case 2:
		{
			// Iterate through all the window pixels
			for (int y = 0; y < windowHeight; y++)
			{
				for (int x = 0; x < windowWidth; x++)
				{
					// Pixel position in a 1D array
					unsigned int pixelPosition = y * (pitch / pixelFormat->BytesPerPixel) + x;

					// Get a colour value (Black/White) based on whether a pixel is contained by the Serpinski carpet
					int n = findSierpinskiCarpet(x, y);
					n = n == 1 ? 255 : 0;

					// Colour the pixel
					Uint32 colour = SDL_MapRGB(pixelFormat, n, n, n);
					pixels[pixelPosition] = colour;
				}
			}
			break;
		}
		case 3:
		{
			std::cout << "NOTE: This variation was obtained by altering the normal Serpinski carpet algorithm.\n";
			for (int y = 0; y < windowHeight; y++)
			{
				for (int x = 0; x < windowWidth; x++)
				{
					// Pixel position in a 1D array
					unsigned int pixelPosition = y * (pitch / pixelFormat->BytesPerPixel) + x;

					// Get a colour value (Black/White) based on whether a pixel is contained by the alternate Serpinski carpet
					int n = findSierpinskiCarpetAlt(x, y);
					n = n == 1 ? 255 : 0;

					// Colour the pixel
					Uint32 colour = SDL_MapRGB(pixelFormat, n, n, n);
					pixels[pixelPosition] = colour;
				}
			}
			break;
		}
		case 4:
		{
			quit = true;
			break;
		}
		default:
		{
			break;
		}
		}

		// Notify the user the display is complete
		std::cout << "Finished displaying...\n";

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