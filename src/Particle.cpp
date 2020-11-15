// Needed for M_PI
#define _USE_MATH_DEFINES
#include <math.h>

#include <stdlib.h>

#include "Particle.h"

namespace caveofprogramming {

	// Particle member initialization list for m_x and m_y
	// Putting the particles in the middles of the screen
	Particle::Particle(): m_x(0), m_y(0) {

		m_direction = (2 * M_PI * rand()) / RAND_MAX;
		m_speed = (0.0001 * rand()) / RAND_MAX;

		/*
		// Particle movement speed
		m_xspeed = 0.001 * (((2.0 * rand()) / RAND_MAX) - 1);
		m_yspeed = 0.001 * (((2.0 * rand()) / RAND_MAX) - 1);
		*/
	}

	Particle::~Particle() {

	}

	void Particle::update(int interval) {

		double xspeed = m_speed * cos(m_direction);
		double yspeed = m_speed * sin(m_direction);

		m_x += xspeed * interval;
		m_y += yspeed * interval;

		/*
		// Particle movement
		m_x += m_xspeed;
		m_y += m_yspeed;

		// Particle collision x
		if (m_x <= -1.0 || m_x >= 1.0 ) {
			m_xspeed = -m_xspeed;
		}

		// Particle collision y
		if (m_y <= -1.0 || m_y >= 1.0) {
			m_yspeed = -m_yspeed;
		}
		*/
	}
}