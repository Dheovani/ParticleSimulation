#include "particles.h"
#include <random>
#include <exception>

namespace Simulation
{
	std::vector<Particle> particles = {};
}

using namespace Simulation;

const sf::Color Simulation::GetRandColor() noexcept(false)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(1, 7);

	switch (dis(gen)) {
	case White:
		return sf::Color::White;

	case Red:
		return sf::Color::Red;

	case Green:
		return sf::Color::Green;

	case Blue:
		return sf::Color::Blue;

	case Yellow:
		return sf::Color::Yellow;

	case Magenta:
		return sf::Color::Magenta;

	case Cyan:
		return sf::Color::Cyan;

	default:
	case Black:
		throw std::exception("Unexpected value!");
	}
}

const Particle Simulation::GenParticle() noexcept(false)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<size_t> dist(5, 95);

	float x = (float)dist(gen) * 10, y = (float)dist(gen) * 10;
	y = y > window_height ? (y - window_height) : y;

	Particle particle;
	particle.position = sf::Vector2f(x, y);
	particle.velocity = sf::Vector2f((float)dist(gen), -150);
	particle.acceleration = sf::Vector2f(0, 98);
	particle.color = GetRandColor();

	return particle;
}

void Simulation::DrawParticle(const Particle& particle, const SWindow& window) noexcept(true)
{
	sf::CircleShape ptc(5);
	ptc.setFillColor(particle.color);
	ptc.setPosition(particle.position);
	window->draw(ptc);
}

void Simulation::ApplyPhysics(Particle& particle, float dTime, sf::Vector2u windowSize) noexcept(true)
{
	particle.velocity += particle.acceleration * dTime;
	particle.position += particle.velocity * dTime;

	if (particle.position.x <= 0) {
		particle.position.x = 0;
		particle.velocity.x = -(particle.velocity.x / 2);
	}

	if (particle.position.x + 10 >= windowSize.x) {
		particle.position.x = (float)windowSize.x - 10;
		particle.velocity.x = -(particle.velocity.x / 2);
	}

	if (particle.position.y <= 0) {
		particle.position.y = 0;
		particle.velocity.y = -(particle.velocity.y / 2);
	}

	if (particle.position.y + 10 >= windowSize.y) {
		particle.position.y = (float)windowSize.y - 10;
		particle.velocity.y = -(particle.velocity.y / 2);
	}
}

void Simulation::DealWithCollisions(Particle& particle) noexcept(true)
{
	for (Particle& other : particles) {
		if (particle != other) {
			sf::Vector2f delta = particle.position - other.position;
			float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);

			if (distance < 10) {
				sf::Vector2f normal = delta / distance;
				float relativeVelocity = (particle.velocity - other.velocity).x * normal.x + (particle.velocity - other.velocity).y * normal.y;

				if (relativeVelocity < 0) {
					float coefficientOfRestitution = 0.8f;
					sf::Vector2f impulse = (1 + coefficientOfRestitution) * relativeVelocity / 2 * normal;
					particle.velocity -= impulse;
					other.velocity += impulse;
				}
			}
		}
	}
}

SWindow Simulation::GetWindow() noexcept(true)
{
	auto window = std::make_shared<sf::RenderWindow>(
		sf::VideoMode(window_width, window_height),
		"Particle Simulation",
		sf::Style::Titlebar | sf::Style::Close);

	return window;
}

void Simulation::Run(const SWindow& window) noexcept(false)
{
	if (particles.empty()) {
		for (int i = 0; i < PARTICLE_AMOUNT; ++i)
			particles.push_back(GenParticle());
	}

	sf::Clock clock;
	while (window->isOpen()) {
		sf::Event event;
		sf::Vector2i beginDrag, endDrag;

		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window->close();
			else
				window->close(); // TODO: Move particles according to mouse movemente
		}

		float deltaTime = clock.restart().asSeconds();
		window->clear(sf::Color::Black);

		for (Particle& ptc : particles) {
			ApplyPhysics(ptc, deltaTime, window->getSize());
			DealWithCollisions(ptc);
			DrawParticle(ptc, window);
		}

		window->display();
	}
}
