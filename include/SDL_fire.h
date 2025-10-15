/*
MIT License

Copyright (c) 2025 broskobandi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/** \file include/SDL_fire.h
 * \brief Public header file for the SDL_fire library.
 * \details This file contains the declarations of the public functions 
 * and the SDL_Fire type.*/

#ifndef SDL_FIRE_H
#define SDL_FIRE_H

#include <SDL2/SDL.h>

/** Declaration of the opaque SDL_Fire struct. */
typedef struct SDL_Fire SDL_Fire;

#ifdef __cplusplus
extern "C" {
#endif

/** Creates a new instance of SDL_Fire.
 * \param base The rect wher the fire originates.
 * \param col The color of the base.
 * \param ticks_per_change The number of ticks to pass between updates.
 * \param frequency The frequency with which new particles are emitted
 * (the actual frequency is a random number influenced by this data).
 * \param speed The original speed of new particles. 
 * \param num_particles The maximum number of particles that can be emitted.
 * \return A pointer to the SDL_Fire object. */
SDL_Fire *SDL_CreateFire(
	SDL_FRect base,
	SDL_Color col,
	Uint32 ticks_per_change,
	int frequency,
	float speed,
	Uint8 num_particles
);

/** Updates an SDL_Fire object.
 * \param fire A pointer to the SDL_Fire object.
 * \param new_pos The new position of the base rect.
 * \return 0 on success or 1 on failure. */
int SDL_UpdateFire(SDL_Fire *fire, SDL_FPoint new_pos);

/** Draws an SDL_Fire object.
 * \param fire A pointer to the SDL_Fire object.
 * \param ren The SDL_Renderer to be used for drawing.
 * \return 0 on success or 1 on failure. */
int SDL_DrawFire(SDL_Fire *fire, SDL_Renderer *ren);

/** Destroys an SDL_Fire object.
 * \param fire A pointer to the fire object. */
void SDL_DestroyFire(SDL_Fire *fire);

/** Returns a string containing the latest error information
 * or NULL.  */
const char *SDL_FireGetError();

#ifdef __cplusplus
}
#endif

#endif
