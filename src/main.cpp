#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "Boid.hpp"
#include "Flock.hpp"

#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 480

int main()
{
    FlockConfig config;
    config.numBoids = 5;
    config.windowWidth = WINDOW_WIDTH;
    config.windowHeight = WINDOW_HEIGHT;
    config.maxSpeed = 1;
    config.maxForce = 1;
    config.randomize = true;
    config.separationWeight = 0.5;
    config.alignmentWeight = 0.5;
    config.cohesionWeight = 0.5;
    config.boidRadius = 5;

    Flock flock(config);


    sf::RenderWindow App(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Boid Flocking Simulation");

    while(App.isOpen())
    {
        // std::cout<<"Looping"<<std::endl;
        flock.applyFlockingRules();
        flock.update();
        flock.render(App);

        App.display();
        App.clear();

    }

    return EXIT_SUCCESS;
}   