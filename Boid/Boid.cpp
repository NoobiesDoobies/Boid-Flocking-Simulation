#include "Boid.hpp"

Boid::Boid()
{
    pos = {0.f, 0.f};
    vel = {0.f, 0.f};
    acc = {0.f, 0.f};
    maxSpeed = 0.f;
    maxForce = 0.f;
}
Boid::Boid(
    sf::Vector2f pos,
    sf::Vector2f vel,
    sf::Vector2f acc) : pos(pos),
                        vel(vel),
                        acc(acc)
{

    maxSpeed = 0.f;
    maxForce = 0.f;
}

Boid::Boid(
    sf::Vector2f pos,
    sf::Vector2f vel,
    sf::Vector2f acc,
    float maxSpeed,
    float maxForce) : pos(pos),
                      vel(vel),
                      acc(acc),
                      maxSpeed(maxSpeed),
                      maxForce(maxForce) {}

void Boid::applyForce(sf::Vector2f force)
{
    force = limitVector(force, maxForce);
    acc += force;
}

void Boid::update(int windowWidth, int windowHeight, bool wrapAroundEdges, int boundaryMargin)
{
    vel += acc;
    vel = limitVector(vel, maxSpeed);
    pos += vel;

    // reset acc to zero
    acc = sf::Vector2f();

    if (pos.x > windowWidth)
        pos.x = 0;
    if (pos.x < 0)
        pos.x = windowWidth;
    if (pos.y > windowHeight)
        pos.y = 0;
    if (pos.y < 0)
        pos.y = windowHeight;
}

sf::Vector2f Boid::limitVector(sf::Vector2f vel, float maxMagnitude)
{
    // calculate the magnitude of vel
    float speed = sqrt(vel.x * vel.x + vel.y * vel.y);
    if (speed > maxMagnitude)
    {
        // normalized vel
        sf::Vector2f normalizedVel = vel / speed;

        // limit to max
        return maxMagnitude * normalizedVel;
    }

    return vel;
}

sf::Vector2f Boid::separation(std::vector<Boid> boids)
{
    return sf::Vector2f();
}

sf::Vector2f Boid::alignment(std::vector<Boid> boids)
{
    return sf::Vector2f();
}

sf::Vector2f Boid::cohesion(std::vector<Boid> boids)
{
    return sf::Vector2f();
}

sf::Vector2f Boid::getPosition()
{
    return pos;
}

sf::Vector2f Boid::getVelocity()
{
    return vel;
}

sf::Vector2f Boid::getAcceleration()
{
    return acc;
}