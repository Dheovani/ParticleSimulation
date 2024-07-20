#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#ifndef PARTICLE_AMOUNT
#define PARTICLE_AMOUNT 1000
#endif // !PARTICLE_AMOUNT

typedef std::shared_ptr<sf::RenderWindow> SWindow;

namespace Simulation
{
	constexpr uint64_t window_width = 1000;
	constexpr uint64_t window_height = 600;

	// Particle colors
	enum PColor : int
	{
		Black = 0,
		White = 1,
		Red = 2,
		Green = 3,
		Blue = 4,
		Yellow = 5,
		Magenta = 6,
		Cyan = 7
	};

	// Generates a random number corresponding to one of the 
	// PColor enum's values from 1 to 7 (Background is black)
	const sf::Color GetRandColor() noexcept(false);

	typedef struct Particle
	{
		sf::Vector2f position;
		sf::Vector2f velocity;
		sf::Vector2f acceleration;
		sf::Color color;

		// For comparing particles' positions
		bool operator==(const Particle& other) const
		{
			return position == other.position;
		}
	} Particle;
	
	// Generates a particle
	const Particle GenParticle() noexcept(false);

	// Draws the particle in the map
	inline void DrawParticle(const Particle& particle, const SWindow& window) noexcept(true);

	// Apply pshysics to the particles, according to their acceleration and time
	void ApplyPhysics(Particle& particle, float dTime, sf::Vector2u windowSize) noexcept(true);

	// Generates the simulation's window
	SWindow GetWindow() noexcept(true);

	// Runs the simulation main event poll loop
	void Run(const SWindow& window) noexcept(false);
}