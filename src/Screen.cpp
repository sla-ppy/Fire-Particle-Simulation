#include <iostream>

#include "Screen.h"

namespace caveofprogramming {

	// Screen member initialization 
	Screen::Screen() :
		m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer1(NULL), m_buffer2(NULL) { }

	bool Screen::init() {
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			return false;
		}

		// Create window
		m_window = SDL_CreateWindow("Particle Fire Explosion",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
			SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		// If failed, return
		if (m_window == NULL) {
			SDL_Quit();
			return false;
		}

		// Create renderer and texture
		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
		m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

		// If renderer fail, return
		if (m_renderer == NULL) {
			SDL_DestroyWindow(m_window);
			SDL_Quit();
			return false;
		}

		// If texture fail, return
		if (m_texture == NULL) {
			SDL_DestroyRenderer(m_renderer);
			SDL_DestroyWindow(m_window);
			SDL_Quit();
			return false;
		}

		// Buffer declaration
		m_buffer1 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
		m_buffer2 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];

		// Memset, clearing buffers
		memset(m_buffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
		memset(m_buffer2, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));

		return true;
	}

	void Screen::boxBlur() {
		// Swapping buffers, so pixel is in buffer 2 and we are drawing to m_buffer 1
		// Temporary variable for swapping values!!!
		Uint32* temp = m_buffer1;

		m_buffer1 = m_buffer2;
		m_buffer2 = temp;

		for (int y = 0; y < SCREEN_HEIGHT; y++) {
			for (int x = 0; x < SCREEN_WIDTH; x++) {
			
				/* 
				* Looking at middle pixel, around it bunch of other pixels.
				* Add up colour values of RGB in each of the pixels, total of 9
				* Then divide them by 9 and plot that back into "1" so the colour
				* Value of center pixel (which is of location X/Y) will become
				* Average of the colour values of all other pixel colour values
				* Including itself, which creates the box blur effect.
				* 
				* 0 0 0
				* 0 1 0
				* 0 0 0
				*/

				int redTotal = 0;
				int greenTotal = 0;
				int blueTotal = 0;

				for (int row = -1; row <= 1; row++) {
					for (int col = -1; col <= 1; col++) {
						int currentX = x + col;
						int currentY = y + row;

						/*
						* For every pixel that we look at will end up
						* Will end up iterating through all of the pixels in the grid of 9 
						*/
						
						// Ignoring pixels out of the Screen bounds
						if (currentX >= 0 && currentX < SCREEN_WIDTH && currentY >= 0 && currentY < SCREEN_HEIGHT) {
							// This is how we get from X/Y coordinates to an index within this array
							Uint32 color = m_buffer2[currentY * SCREEN_WIDTH + currentX];

							// Shifting back the values
							Uint8 red = color >> 24;
							Uint8 green = color >> 16;
							Uint8 blue = color >> 8;

							// Assigning total values
							redTotal += red;
							greenTotal += green;
							blueTotal += blue;
						}
					}
				}

				// Getting individuals color values
				Uint8 red = redTotal / 9;
				Uint8 green = greenTotal / 9;
				Uint8 blue = blueTotal / 9;

				setPixel(x, y, red, green, blue);
			}
		}
	}

	/*
	// Restores memset to initial value, effectively "clearing" the screen so particles
	// wont leave a trail behind
	void Screen::clear() {
		memset(m_buffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
		memset(m_buffer2, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
	}
	*/

	void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue) {

		if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
			return;
		}

		Uint32 color = 0;

		color += red;
		color <<= 8;
		color += green;
		color <<= 8;
		color += blue;
		color <<= 8;
		color += 0xFF;

		// RGBA

		m_buffer1[(y * SCREEN_WIDTH) + x] = color;
	}

	// Screen update
	void Screen::update() {
		SDL_UpdateTexture(m_texture, NULL, m_buffer1, SCREEN_WIDTH * sizeof(Uint32));
		SDL_RenderClear(m_renderer);
		SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
		SDL_RenderPresent(m_renderer);

	}

	// Event process? Im not sure yet
	bool Screen::processEvents() {
		SDL_Event event;

		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				return false;
			}
		}
		return true;
	}

	// Screen close
	void Screen::close() {
		delete[] m_buffer1;
		delete[] m_buffer2;
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyTexture(m_texture);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}

} /* namespace caveofprogramming */
