#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "SA_Trainer.h"


int main(int argc, char* argv[]) {
	SA_Trainer trainer;


	trainer.initialise();
	trainer.run();
	trainer.closeDown();

	return 0;
}