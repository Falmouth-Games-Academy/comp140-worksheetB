#pragma once

void CheckForQuit(SDL_Event &event);

void GenerateFractal(SDL_PixelFormat * pixelFormat, const double &maxX, const double &minX, const double &maxY, const double &minY, Uint32 * pixels);
