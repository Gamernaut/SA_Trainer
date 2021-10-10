//#include <iostream>
//#include <SDL.h>
//#include <SDL_image.h>
#include "SA_Trainer.h"

using namespace cpv;

int main(int argc, char* argv[]) {
	SA_Trainer trainer;

	trainer.Initialise();
	trainer.Run();
	trainer.CloseDown();

	return 0;
}