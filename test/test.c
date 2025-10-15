#include "SDL_fire_priv.h"
#include <ctest.h>
#include <math.h>

int fcmp(float a, float b) {
	return fabsf(a - b) < 0.00001;
}

int main(void) {
	CTEST(!SDL_Init(SDL_INIT_EVERYTHING));

	SDL_FRect base = {0, 0, 16, 16};
	SDL_Color col = {255, 100, 0, 255};
	Uint32 ticks_per_change = 10;
	float speed = 10.0f;
	Uint8 num_particles = 10;
	SDL_Fire *fire = SDL_CreateFire(base, col, ticks_per_change, speed, num_particles);
	CTEST(fire);

	Uint32 cur_time = ticks_per_change;
	SDL_FPoint new_pos = {5.0f, 5.0f};
	SDL_FireEmission emission = SDL_FIRE_EMISSION_LEFT;

	CTEST(!SDL_UpdateFire(fire, new_pos, cur_time, emission));

	CTEST(fire->base.x == new_pos.x);
	CTEST(fire->base.y == new_pos.y);
	CTEST(fire->particles[0].is_active == true);
	for (int i = 1; i < fire->num_particles; i++) {
		CTEST(fire->particles[i].is_active == false);
	}
	CTEST(fire->particles[0].col.r == fire->col.r);
	CTEST(fire->particles[0].col.g == fire->col.g);
	CTEST(fire->particles[0].col.b == fire->col.b);
	CTEST(fire->particles[0].col.a == fire->col.a);
	CTEST(fcmp(fire->particles[0].frect.x, fire->base.x - fire->base.w / 2));
	CTEST(fire->particles[0].frect.y == fire->base.y);
	CTEST(fire->particles[0].frect.w == fire->base.w);
	CTEST(fire->particles[0].frect.h == fire->base.h);
	CTEST(fire->particles[0].speed == fire->default_speed);

	cur_time += ticks_per_change;
	CTEST(!SDL_UpdateFire(fire, new_pos, cur_time, emission));

	CTEST(fire->particles[0].is_active == true);
	CTEST(fire->particles[1].is_active == true);
	for (int i = 2; i < fire->num_particles; i++) {
		CTEST(fire->particles[i].is_active == false);
	}
	CTEST(fcmp(fire->particles[0].col.r, fire->col.r - COL_CHANGE_FACTOR));
	CTEST(fcmp(fire->particles[0].col.g, fire->col.g - COL_CHANGE_FACTOR));
	CTEST(fire->particles[0].col.b == 0);
	CTEST(fcmp(fire->particles[0].col.a, fire->col.a - COL_CHANGE_FACTOR));
	CTEST(fcmp(fire->particles[0].frect.x, fire->base.x - fire->base.w / 2));
	CTEST(fcmp(fire->particles[0].frect.y, fire->base.y - fire->particles[0].speed - SPEED_CHANGE_FACTOR));
	CTEST(fire->particles[0].frect.w == fire->base.w);
	CTEST(fire->particles[0].frect.h == fire->base.h);
	CTEST(fcmp(fire->particles[0].speed, fire->default_speed - SPEED_CHANGE_FACTOR));
	CTEST(fire->particles[1].col.r == fire->col.r);
	CTEST(fire->particles[1].col.g == fire->col.g);
	CTEST(fire->particles[1].col.b == fire->col.b);
	CTEST(fire->particles[1].col.a == fire->col.a);
	CTEST(fcmp(fire->particles[1].frect.x, fire->base.x - fire->base.w / 2));
	CTEST(fire->particles[1].frect.y == fire->base.y);
	CTEST(fire->particles[1].frect.w == fire->base.w);
	CTEST(fire->particles[1].frect.h == fire->base.h);
	CTEST(fire->particles[1].speed == fire->default_speed);

	ctest_print_results();
	return 0;
}
