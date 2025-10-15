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

/** \file src/SDL_fire_priv.c 
 * \brief Private header file for the SDL_fire library.
 * \details This file contains data structure definitions. */

#ifndef SDL_FIRE_PRIV_H
#define SDL_FIRE_PRIV_H

#include "SDL_fire.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
#include <stdbool.h>
#include <stdlib.h>

/** The maximum number of particles */
#define MAX_PARTICLES 256

/** Each particle's speed is reduced by this per update. */
#define SPEED_CHANGE_FACTOR 0.1f

/** Each particle's color values are reduced by this per update. */
#define COL_CHANGE_FACTOR 5

/** A struct containing particle information. */
typedef struct {

	/** The particle's rect. */
	SDL_FRect frect;

	/** The particle's original color. */
	SDL_Color col;

	/** Boolean indicating whether the particle is active. */
	bool is_active;

	/** The current speed of the particle.  */
	float speed;

} Particle;

/** Definition of the opaque SDL_Fire struct. */
struct SDL_Fire {

	/** Buffer for the particles. */
	Particle particles[MAX_PARTICLES];

	/** The user defined maximum number of
	 * particles in the instance. */
	Uint8 num_particles;

	/** The rect from which all particles originate. */
	SDL_FRect base;

	/** The color of the base. */
	SDL_Color col;

	/** The number of the ticks to pass between updates. */
	Uint32 ticks_per_change;

	/** The initial speed of each particle. */
	float default_speed;
};

#endif
