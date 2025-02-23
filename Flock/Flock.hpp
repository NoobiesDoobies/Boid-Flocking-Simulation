#ifndef FLOCK_HPP
#define FLOCK_HPP

#include <iostream>
#include <cstdlib>
#include <vector>
#include <random>
#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/ConvexShape.hpp>

#include "Boid.hpp"

struct FlockConfig
{
    // Flock Behavior
    int numBoids;
    float maxSpeed;
    float maxForce;
    float separationWeight;
    float alignmentWeight;
    float cohesionWeight;
    float separationRadius;
    float alignmentRadius;
    float cohesionRadius;

    // Environment
    int windowWidth;
    int windowHeight;
    bool wrapAroundEdges;
    int boundaryMargin;

    // User Interaction
    bool mouseAttraction;
    float mouseForce;

    // Visualization
    bool showVelocityVectors;
    bool showPerceptionRadius;
    bool trailEffect;
    float boidRadius;
    bool followOneBoid;

    // generation
    bool randomize;

    // Constructor with default values
    FlockConfig(int numBoids = 100, float maxSpeed = 4.0f, float maxForce = 0.1f,
                float separationWeight = 1.5f, float alignmentWeight = 1.0f, float cohesionWeight = 1.0f, float separationRadius = 1.f, float alignmentRadius = 1.f, float cohesionRadius = 1.f,
                int windowWidth = 800, int windowHeight = 600, bool wrapAroundEdges = true, int boundaryMargin = 10,
                bool mouseAttraction = false, float mouseForce = 0.5f,
                bool showVelocityVectors = false, bool showPerceptionRadius = false, bool trailEffect = false, float boidRadius = 5.f, bool followOneBoid = false,
                bool randomize = true)
        : numBoids(numBoids), maxSpeed(maxSpeed), maxForce(maxForce),
          separationWeight(separationWeight), alignmentWeight(alignmentWeight), cohesionWeight(cohesionWeight), separationRadius(separationRadius), alignmentRadius(alignmentRadius), cohesionRadius(cohesionRadius),
          windowWidth(windowWidth), windowHeight(windowHeight), wrapAroundEdges(wrapAroundEdges), boundaryMargin(boundaryMargin),
          mouseAttraction(mouseAttraction), mouseForce(mouseForce),
          showVelocityVectors(showVelocityVectors), showPerceptionRadius(showPerceptionRadius), trailEffect(trailEffect), boidRadius(boidRadius), followOneBoid(followOneBoid),
          randomize(randomize) {}
};

class Flock
{
private:
    std::vector<Boid> boids;
    FlockConfig config;
    std::shared_ptr<BoidConfig> sharedBoidConfig;
    Boid *followed_boid;

public:
    Flock(FlockConfig &config);
    // Flock(std::vector<Boid> boids);
    void addBoid(Boid b);
    void applyFlockingRules();
    void update();
    void render(sf::RenderWindow &window);
    void setConfig(FlockConfig &config);
};

#endif