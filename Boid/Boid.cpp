#include "Boid.hpp"

Boid::Boid(BoidConfig config, BoidState state)
{
    this->config = config;
    this->state = state;
}

void Boid::applyForce(sf::Vector2f force)
{
    force = limitVector(force, config.maxForce);    // limit the force
    state.acc += force;
};

void Boid::update(int windowWidth, int windowHeight, bool wrapAroundEdges, int boundaryMargin)
{
    state.vel = state.vel + state.acc;
    state.vel = limitVector(state.vel, config.maxSpeed);
    std::cout << "config.maxSpeed: " << config.maxSpeed << std::endl;

    state.pos += state.vel;
    state.rot = std::atan2(state.vel.x, -state.vel.y) * 180.0f / 3.1415;

    // reset state.acc to zero
    state.acc = sf::Vector2f();

    if (state.pos.x > windowWidth)
        state.pos.x = 0;
    if (state.pos.x < 0)
        state.pos.x = windowWidth;
    if (state.pos.y > windowHeight)
        state.pos.y = 0;
    if (state.pos.y < 0)
        state.pos.y = windowHeight;
}

sf::Vector2f Boid::separation(std::vector<Boid> *boids, float separationRadius)
{
    sf::Vector2f steer(0, 0);
    int count = 0;
    for (auto &other : *boids)
    {
        float dist = distance(state.pos, other.getState().pos);
        // don't compare self and make sure is within sep rad
        if (this != &other && dist < separationRadius)
        {
            sf::Vector2f delta_pos = state.pos - other.getState().pos;
            steer += delta_pos / (dist * dist);
            count++;
        }
    }

    if (count > 0)
    {
        steer = steer / (float)count; // averaged out the force

        steer = limitVector(steer, config.maxForce);
    }

    return steer;
}

sf::Vector2f Boid::alignment(std::vector<Boid> *boids, float alignmentRadius)
{
    sf::Vector2f avg_vel(0, 0);
    int count = 0;
    for (auto &other : *boids)
    {
        float dist = distance(state.pos, other.getState().pos);
        if (this != &other && dist < alignmentRadius)
        {
            avg_vel += other.getState().vel;
            count++;
        }
    }

    if (count > 0)
    {
        avg_vel /= (float)count;
        return limitVector(avg_vel - state.vel, config.maxForce);
    }
    return sf::Vector2f();
}

sf::Vector2f Boid::cohesion(std::vector<Boid> *boids, float cohesionRadius)
{
    sf::Vector2f center(0, 0);
    int count = 0;

    for (auto &other : *boids)
    {
        float dist = distance(state.pos, other.getState().pos);
        if (this != &other && dist < cohesionRadius)
        {
            center += other.getState().pos;
            count++;
        }
    }

    if (count > 0)
    {
        center /= (float)count;
        return limitVector(center - state.pos, config.maxForce);
    }
    return sf::Vector2f();
}

BoidState Boid::getState()
{
    return state;
}

BoidConfig Boid::getConfig()
{
    return config;
}

void Boid::setState(BoidState state)
{
    this->state = state;
}

void Boid::setConfig(BoidConfig config)
{
    this->config = config;
}

sf::Vector2f Boid::limitVector(sf::Vector2f vel, float maxMagnitude)
{
    // calculate the magnitude of state.vel
    float speed = sqrt(vel.x * vel.x + vel.y * vel.y);
    if (speed > maxMagnitude)
    {
        // normalized state.vel
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