#ifndef BOID_HPP
#define BOID_HPP

#include <iostream>
#include <cmath>
#include <vector>

#include <SFML/System.hpp>

struct BoidConfig
{
    float maxSpeed;
    float maxForce;
    float separationWeight;
    float alignmentWeight;
    float cohesionWeight;
    float separationRadius;
    float alignmentRadius;
    float cohesionRadius;
};

struct BoidState
{
    sf::Vector2f pos;
    float rot;
    sf::Vector2f vel;
    sf::Vector2f acc;
};

class Boid
{
private:
    BoidConfig config;
    BoidState state;

    // Utility
    static sf::Vector2f limitVector(sf::Vector2f vel, float maxMagnitude);
    static float distance(sf::Vector2f pos_a, sf::Vector2f pos_b);
    static sf::Vector2f normalizeVector(sf::Vector2f vector);

public:
    // Constructor
    Boid(BoidConfig config, BoidState state = {sf::Vector2f(0, 0), 0, sf::Vector2f(0, 0), sf::Vector2f(0, 0)});

    // Methods
    void applyForce(sf::Vector2f force);
    void update(int windowWidth, int windowHeight, bool wrapAroundEdges, int boundaryMargin);
    sf::Vector2f separation(std::vector<Boid> *boids, float separationRadius);
    sf::Vector2f alignment(std::vector<Boid> *boids, float alignmentRadius);
    sf::Vector2f cohesion(std::vector<Boid> *boids, float cohesionRadius);

    // Getter
    BoidState getState();
    BoidConfig getConfig();

    // Setter
    void setState(BoidState state);
    void setConfig(BoidConfig config);

};

#endif