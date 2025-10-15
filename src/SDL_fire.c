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

/** \file src/SDL_fire.c 
 * \brief Implementation for the SDL_fire library.
 * \details This file contains the implementation of public functions and 
 * the SDL_Fire type. */

#include "SDL_fire_priv.h"

_Thread_local static const char *g_err;

/** Creates a new instance of SDL_Fire.
 * \param base The rect where the fire originates.
 * \param col The color of the base.
 * \param ticks_per_change The number of ticks to pass between updates.
 * \param speed The original speed of new particles. 
 * \param num_particles The maximum number of particles that can be emitted.
 * \return A pointer to the SDL_Fire object. */
SDL_Fire *SDL_CreateFire(
	SDL_FRect base,
	SDL_Color col,
	Uint32 ticks_per_change,
	float speed,
	Uint8 num_particles)
{
	SDL_Fire *fire = malloc(sizeof(SDL_Fire));
	if (!fire) {
		g_err = "Failed to create SDL_Fire.";
		return NULL;
	}
	fire->base = base;
	fire->col = col;
	fire->ticks_per_change = ticks_per_change;
	fire->num_particles = num_particles;
	fire->default_speed = speed;
	for (int i = 0; i < fire->num_particles; i++) {
		Particle *p = &fire->particles[i];
		p->col = col;
		p->frect = base;
		p->speed = fire->default_speed;
		p->is_active = false;
	}
	return fire;
}

/** Updates an SDL_Fire object.
 * \param fire A pointer to the SDL_Fire object.
 * \param new_pos The new position of the base rect.
 * \return 0 on success or 1 on failure. */
int SDL_UpdateFire(
	SDL_Fire *fire, SDL_FPoint new_pos, Uint32 cur_time, SDL_FireEmission emission) 
{
	if (!fire) {
		g_err = "Invalid argument.";
		return 1;
	}

	static Uint32 time_of_last_change = 0;

	if (cur_time - time_of_last_change < fire->ticks_per_change)
		return 0;

	fire->base.x = (float)new_pos.x;
	fire->base.y = (float)new_pos.y;

	time_of_last_change = cur_time;

	for (int i = 0; i < fire->num_particles; i++) {
		Particle *p = &fire->particles[i];
		if (p->is_active) {
			p->frect.y -= p->speed;
			if (p->speed >= SPEED_CHANGE_FACTOR)
				p->speed -= SPEED_CHANGE_FACTOR;
			if (p->col.r >= COL_CHANGE_FACTOR)
				p->col.r -= COL_CHANGE_FACTOR;
			if (p->col.g >= COL_CHANGE_FACTOR)
				p->col.g -= COL_CHANGE_FACTOR;
			if (p->col.b >= COL_CHANGE_FACTOR)
				p->col.b -= COL_CHANGE_FACTOR;
			if (p->col.a >= COL_CHANGE_FACTOR)
				p->col.a -= COL_CHANGE_FACTOR;
			if (
				p->col.a < COL_CHANGE_FACTOR ||
				p->speed < SPEED_CHANGE_FACTOR)
			{
				p->is_active = false;
			}
		}
		if (!p->is_active && emission != SDL_FIRE_EMISSION_NONE) {
			p->is_active = true;
			p->speed = fire->default_speed;
			p->col = fire->col;
			p->frect = fire->base;
			switch (emission) {
				case SDL_FIRE_EMISSION_LEFT:
					p->frect.x -= p->frect.w / 2;
					break;
				case SDL_FIRE_EMISSION_RIGHT:
					p->frect.x += p->frect.w / 2;
					break;
				case SDL_FIRE_EMISSION_MIDDLE:
					break;
				case SDL_FIRE_EMISSION_NONE:
					break;
			}
			break;
		}
	}

	return 0;
}

/** Draws an SDL_Fire object.
 * \param fire A pointer to the SDL_Fire object.
 * \param ren The SDL_Renderer to be used for drawing.
 * \return 0 on success or 1 on failure. */
int SDL_DrawFire(SDL_Fire *fire, SDL_Renderer *ren) {
	if (!fire || !ren) {
		g_err = "Invalid argument.";
		return 1;
	}

	for (int i = 0; i < fire->num_particles; i++) {
		Particle *p = &fire->particles[i];
		if (!p->is_active) continue;
		if (SDL_SetRenderDrawColor(
			ren, p->col.r, p->col.g, p->col.b, p->col.a)) {
			g_err = "Failed to draw SDL_Fire.";
			return 1;
		}
		if (SDL_RenderFillRectF(ren, &p->frect)) {
			g_err = "Failed to draw SDL_Fire.";
			return 1;
		}
	}
	if (SDL_SetRenderDrawColor(
		ren, fire->col.r, fire->col.g, fire->col.b, fire->col.a)) {
		g_err = "Failed to draw SDL_Fire";
		return 1;
	}

	return 0;
}

/** Destroys an SDL_Fire object.
 * \param fire A pointer to the fire object. */
void SDL_DestroyFire(SDL_Fire *fire) {
	if (fire) free(fire);
}

/** Returns a string containing the latest error information
 * or NULL.  */
const char *SDL_FireGetError() {
	return g_err;
}
