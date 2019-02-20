#pragma once

bool Setup();
bool CreateRenderer();
bool CreateTexture();
bool CreateWindow();
bool InitializeVideo();
void SDLCleanUp();
void GenerateAndRenderFractal();
void CheckForQuit();
void GenerateFractal();


int WidthOfTextureInBytes;

int windowWidth = 800;
int windowHeight = 800;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Texture* fractalTexture = nullptr;

// Minimum and maximum coordinates for the fractal
const double minX = -2, maxX = 1, minY = -1.5, maxY = 1.5;

//this stores the pixels retrieved from the texture
Uint32 * pixels = NULL;

//Get the pixel format the texture
SDL_PixelFormat * pixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGB888);

int maxIterations = 175;

//Holds events coming from SDL
SDL_Event event;

//Controls the game loop
bool bWantsToQuit = false;
