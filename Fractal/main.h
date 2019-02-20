#pragma once

#include "stdafx.h"

bool Setup();
bool InitializeVideo();
bool CreateWindow();
bool CreateRenderer();
bool CreateTexture();
void GenerateAndRenderFractal();
void CheckForQuit();
void GenerateFractal();
void ChangePixelColour();
void IterateThroughPixels();
void SDLCleanUp();

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;
SDL_Texture* fractalTexture = nullptr;

int windowWidth = 800;
int windowHeight = 800;
int WidthOfTextureInBytes;

// Minimum and maximum coordinates for the fractal
const double minX = -2, maxX = 1, minY = -1.5, maxY = 1.5;

//this stores the pixels retrieved from the texture
Uint32 * pixels = NULL;

unsigned int pixelPosition = 0;
double my_x0 = 0.0f;
double my_y0 = 0.0f;
double currentX = 0.0f;
double currentY = 0.0f;
double nextX = 0.0f;
int currentIteration = 0;

//Get the pixel format the texture
SDL_PixelFormat * pixelFormat = SDL_AllocFormat(SDL_PIXELFORMAT_RGB888);


//Holds events coming from SDL
SDL_Event event;

//Controls the game loop
bool bWantsToQuit = false;
