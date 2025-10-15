#include "SDL_fire_priv.h"
#include <ctest.h>

int main(void) {
	CTEST(!SDL_Init(SDL_INIT_EVERYTHING));

	SDL_FRect base = {0, 0, 16, 16};
	SDL_Color col = {255, 100, 0, 255};
	Uint32 ticks_per_change = 10;
	float speed = 10.0f;
	Uint8 num_particles = 10;
	SDL_Fire *fire = SDL_CreateFire(base, col, ticks_per_change, speed, num_particles);
	CTEST(fire);

	

	SDL_Quit();

	ctest_print_results();
	return 0;
}
