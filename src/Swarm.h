#ifndef SWARM_H_
#define SWARM_H_

#include "Particle.h"

namespace caveofprogramming {

	class Swarm
	{
	public:
		const static int NPARTICLES = 5000;

	private:
		// member_pointerParticles
		Particle *m_pParticles;
		int lastTime;

	public:
		Swarm();
		virtual ~Swarm();
		void update(int elapsed);

		const Particle* const getParticles() { return m_pParticles; };
	};

}

#endif