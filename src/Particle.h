#ifndef PARTICLE_H_
#define PARTICLE_H_

namespace caveofprogramming {

	struct Particle
	{
	public:
		double m_x;
		double m_y;

	public:
		Particle();
		virtual ~Particle();
	};

}

#endif