#include "Flock.hpp"

Flock::Flock(FlockConfig &config) : config(config)
{
    // generate boids

    for (int i = 0; i < config.numBoids; i++)
    {
        if (config.randomize)
        {
            std::random_device rd;
            std::mt19937 gen(rd());
            // random 0,1 value
            std::uniform_real_distribution<float> unif(0, 1);

            // create random position with max width and max height
            float rand_x = unif(gen) * config.windowWidth;
            float rand_y = unif(gen) * config.windowHeight;
            sf::Vector2f pos(rand_x, rand_y);

            // create zero vel and acc
            sf::Vector2f vel, acc;
            // create new boid
            Boid new_boid(pos, vel, acc, config.maxSpeed, config.maxForce);

            boids.push_back(new_boid);
        }
        else
        {
            // ToDo: generate boids uniformly
        }
    }
}
// Flock::Flock(std::vector<Boid> boids) : boids(boids) {}

void Flock::addBoid(Boid boid)
{
    boids.push_back(boid);
}

void Flock::applyFlockingRules()
{
    for (auto &boid : boids)
    {
        sf::Vector2f sep = boid.separation(&boids, config.separationRadius);
        sf::Vector2f alg = boid.alignment(&boids, config.alignmentRadius);
        sf::Vector2f coh = boid.cohesion(&boids, config.cohesionRadius);

        sf::Vector2f resultantForce = sep * config.separationWeight + alg * config.alignmentWeight + coh * config.cohesionWeight;

        boid.applyForce(resultantForce);
    }
}

void Flock::update()
{
    for (auto &boid : boids)
    {
        boid.update(config.windowWidth, config.windowHeight, config.wrapAroundEdges, config.boundaryMargin);
    }
}

void Flock::render(sf::RenderWindow &window)
{
    for (auto &boid : boids)
    {
        sf::CircleShape shape(config.boidRadius);
        shape.setPosition(boid.getPosition());
        shape.setFillColor(sf::Color::White);
        window.draw(shape);
    }
}
