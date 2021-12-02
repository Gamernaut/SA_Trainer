//#include <iostream>
//#include <SDL.h>
//#include <SDL_image.h>
#include <plog/Log.h>
#include "SA_Trainer.h"
#include "plog/Initializers/RollingFileInitializer.h"

using namespace cpv;

int main(int argc, char* argv[]) {
	SA_Trainer trainer;

	// uses plog -> https://github.com/SergiusTheBest/plog
	plog::init(plog::verbose, log_path, 1000000, 5);
	
	PLOG_DEBUG << "Hello log!";

	// programatically set the logging level
	plog::get()->setMaxSeverity(plog::warning);

	trainer.Initialise();
	trainer.Run();
	trainer.CloseDown();

	return 0;
}