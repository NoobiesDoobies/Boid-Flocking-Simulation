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
    vel = vel + acc;
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

sf::Vector2f Boid::separation(std::vector<Boid> *boids, float separationRadius)
{
    sf::Vector2f steer(0, 0);
    int count = 0;
    for (auto &other : *boids)
    {
        float dist = distance(pos, other.getPosition());
        // don't compare self and make sure is within sep rad
        if (this != &other && dist < separationRadius)
        {
            sf::Vector2f delta_pos = pos - other.getPosition();
            steer += delta_pos / (dist * dist);
            count++;
        }
    }

    if (count > 0)
    {
        steer = steer / (float)count; // averaged out the force

        steer = limitVector(steer, maxForce);
    }

    return steer;
    // return sf::Vector2f();
}

sf::Vector2f Boid::alignment(std::vector<Boid> *boids, float alignmentRadius)
{
    sf::Vector2f avgVelocity(0, 0);
    int count = 0;
    for (auto &other : *boids)
    {
        float dist = distance(pos, other.getPosition());
        if (this != &other && dist < alignmentRadius)
        {
            avgVelocity += other.getVelocity();
            count++;
        }
    }

    if (count > 0)
    {
        avgVelocity /= (float)count;
        return limitVector(avgVelocity - vel, maxForce);
    }
    return sf::Vector2f();
}

sf::Vector2f Boid::cohesion(std::vector<Boid> *boids, float cohesionRadius)
{
    sf::Vector2f center(0, 0);
    int count = 0;

    for (auto &other : *boids)
    {
        float dist = distance(pos, other.getPosition());
        if (this != &other && dist < cohesionRadius)
        {
            center += other.getPosition();
            count++;
        }
    }

    if (count > 0)
    {
        center /= (float)count;
        return limitVector(center - pos, maxForce);
    }
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

float Boid::distance(sf::Vector2f pos_a, sf::Vector2f pos_b)
{
    float delta_x = pos_a.x - pos_b.x;
    float delta_y = pos_a.y - pos_b.y;
    return sqrt(delta_x * delta_x + delta_y * delta_y);
}

sf::Vector2f Boid::normalizeVector(sf::Vector2f vector)
{
    float magnitude = sqrt(vector.x * vector.x + vector.y * vector.y);
    return vector / magnitude;
}