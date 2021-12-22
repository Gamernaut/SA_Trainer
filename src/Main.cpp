///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Author:	Carmelo Volpe
//
//	Date:	September 2021
//
//	Purpose:    Main entry point for program
// 
// Coding Style:    Google C++ -> https://google.github.io/styleguide/cppguide.html
//
///////////////////////////////////////////////////////////////////////////////////////////////////////


//#include <plog/Log.h>
#include "SA_Trainer.h"
#include "plog/Initializers/RollingFileInitializer.h"

using namespace cpv;

int main(int argc, char* argv[]) {
	
	// Create a logger and set logging level using plog -> https://github.com/SergiusTheBest/plog
	// Can also programmatically set the logging level -> plog::get()->setMaxSeverity(plog::warning);
	plog::init(plog::verbose, log_path, 1000000, 5);
	PLOG_VERBOSE << "Logger started";
	
	// Start application
	SA_Trainer trainer;
	trainer.Initialise();
	trainer.Run();
	trainer.CloseDown();

	return 0;
}