#include <iostream>
#include <SDL.h>
#include "Screen.h"

using namespace n_Screen;

int main(int argc, char* argv[]) {

	Screen screen;

	if(screen.init() == false) {
		std::cout << "Error initialising SDL." << std::endl;
	}

	while (true) {
		// Update particles
		// Draw particles
		// Check for messages/events

		if(screen.processEvents() == false) {
			break;
		}
	}

	screen.close();

	return 0;
}
