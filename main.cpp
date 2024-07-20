#include <cstdlib>
#include <iostream>
#include "particles.h"

int main(void)
{
	SWindow window = Simulation::GetWindow();
	if (!window) {
		std::cout << "Could not generate simulation's window!!" << std::endl;
		return EXIT_FAILURE;
	}

	Simulation::Run(window);
	return EXIT_SUCCESS;
}