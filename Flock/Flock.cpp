#include "Flock.hpp"

Flock::Flock(FlockConfig &config) : config(config)
{
    // generate boids

    sharedBoidConfig = std::make_shared<BoidConfig>(
        BoidConfig{
            config.maxSpeed,
            config.maxForce,
            config.separationWeight,
            config.alignmentWeight,
            config.cohesionWeight,
            config.separationRadius,
            config.alignmentRadius,
            config.cohesionRadius});
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
            float rot = 0;
            sf::Vector2f vel, acc;
            // create new boid
            BoidState state = {pos, rot, vel, acc};

            Boid new_boid(sharedBoidConfig, state);

            boids.push_back(new_boid);
        }
        else
        {
            // ToDo: generate boids uniformly
        }
    }

    followed_boid = &boids[0];
}

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
        sf::ConvexShape convex;
        convex.setPointCount(3);
        convex.setPoint(0, {-config.boidRadius / 2, +config.boidRadius / 2});
        convex.setPoint(1, {+config.boidRadius / 2, +config.boidRadius / 2});
        convex.setPoint(2, {0, -config.boidRadius});
        convex.setPosition(boid.getState().pos);
        convex.setRotation(boid.getState().rot);

        if (&boid == followed_boid)
        {
            convex.setFillColor(sf::Color::Yellow);

            std::cout << "alignment radius: " << config.alignmentRadius << std::endl;
            // create alignment circle
            sf::CircleShape alignment_circle(config.alignmentRadius);
            alignment_circle.setPosition(sf::Vector2f(boid.getState().pos.x - config.alignmentRadius, boid.getState().pos.y - config.alignmentRadius));
            alignment_circle.setOutlineColor(sf::Color::Red);
            alignment_circle.setOutlineThickness(3.f);
            alignment_circle.setFillColor(sf::Color::Transparent);
            window.draw(alignment_circle);

            // create cohesion circle
            sf::CircleShape cohesion_circle(config.cohesionRadius);
            cohesion_circle.setPosition(sf::Vector2f(boid.getState().pos.x - config.cohesionRadius, boid.getState().pos.y - config.cohesionRadius));
            cohesion_circle.setOutlineColor(sf::Color::Green);
            cohesion_circle.setOutlineThickness(3.f);
            cohesion_circle.setFillColor(sf::Color::Transparent);
            window.draw(cohesion_circle);

            // create separation circle
            sf::CircleShape separation_circle(config.separationRadius);
            separation_circle.setPosition(sf::Vector2f(boid.getState().pos.x - config.separationRadius, boid.getState().pos.y - config.separationRadius));
            separation_circle.setOutlineColor(sf::Color::Blue);
            separation_circle.setOutlineThickness(3.f);
            separation_circle.setFillColor(sf::Color::Transparent);
            window.draw(separation_circle);
        }
        else
        {
            convex.setFillColor(sf::Color::White);
        }
        window.draw(convex);
    }
}

void Flock::setConfig(FlockConfig &config)
{
    this->config = config;

    sharedBoidConfig = std::make_shared<BoidConfig>(
        BoidConfig{
            config.maxSpeed,
            config.maxForce,
            config.separationWeight,
            config.alignmentWeight,
            config.cohesionWeight,
            config.separationRadius,
            config.alignmentRadius,
            config.cohesionRadius});
    for (auto &boid : boids)
    {
        boid.setConfig(sharedBoidConfig);
    }
}