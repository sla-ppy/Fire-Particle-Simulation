#include "Swarm.h"

namespace caveofprogramming {

	Swarm::Swarm() {
		m_pParticles = new Particle[NPARTICLES];
	}

	Swarm::~Swarm() {
		delete[] m_pParticles;
	}

}