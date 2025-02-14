#ifndef BOID_HPP
#define BOID_HPP

#include <iostream>
#include <cmath>
#include <vector>

#include <SFML/System.hpp>

class Boid
{
private:
    sf::Vector2f pos;
    float rot;
    sf::Vector2f vel;
    sf::Vector2f acc;
    float maxSpeed;
    float maxForce;

public:
    Boid(sf::Vector2f pos, float rot, sf::Vector2f vel, sf::Vector2f acc, float maxSpeed, float maxForce);

    void applyForce(sf::Vector2f force);
    void update(int windowWidth, int windowHeight, bool wrapAroundEdges, int boundaryMargin);
    sf::Vector2f separation(std::vector<Boid> *boids, float separationRadius);
    sf::Vector2f alignment(std::vector<Boid> *boids, float alignmentRadius);
    sf::Vector2f cohesion(std::vector<Boid> *boids, float cohesionRadius);

    sf::Vector2f getPosition();
    float getRotation();
    sf::Vector2f getVelocity();
    sf::Vector2f getAcceleration();

    void setRotation(float rotation);

    sf::Vector2f limitVector(sf::Vector2f vel, float maxMagnitude);
    float distance(sf::Vector2f pos_a, sf::Vector2f pos_b);
    sf::Vector2f normalizeVector(sf::Vector2f vector);
};

#endif