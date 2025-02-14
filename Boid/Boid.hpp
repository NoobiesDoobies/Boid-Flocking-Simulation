#ifndef BOID_HPP
#define BOID_HPP

#include <cmath>
#include <vector>

#include <SFML/System.hpp>


class Boid{
private:
    sf::Vector2f pos;
    sf::Vector2f vel;
    sf::Vector2f acc;
    float maxSpeed;
    float maxForce;

public:
    Boid();
    Boid(sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f acc);
    Boid(sf::Vector2f pos, sf::Vector2f vel, sf::Vector2f acc, float maxSpeed, float maxForce); 
    
    void applyForce(sf::Vector2f force);
    void update(int windowWidth, int windowHeight, bool wrapAroundEdges, int boundaryMargin);
    sf::Vector2f limitVector(sf::Vector2f vel, float maxMagnitude);
    sf::Vector2f separation(std::vector<Boid> boids);
    sf::Vector2f alignment(std::vector<Boid> boids);
    sf::Vector2f cohesion(std::vector<Boid> boids);

    sf::Vector2f getPosition();
    sf::Vector2f getVelocity();
    sf::Vector2f getAcceleration();
};

#endif