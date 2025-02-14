#include <iostream>
#include <SFML/Graphics.hpp>
#include "Boid.hpp"
#include "Flock.hpp"

#define WINDOW_WIDTH  640
#define WINDOW_HEIGHT 480

int main() {
    // Create Config
    FlockConfig config;
    config.numBoids = 50;
    config.windowWidth = WINDOW_WIDTH;
    config.windowHeight = WINDOW_HEIGHT;
    config.maxSpeed = 5.0f;
    config.maxForce = 0.05f;
    config.randomize = true;
    config.separationWeight = 0.5;
    config.alignmentWeight = 0.5;
    config.cohesionWeight = 0.5;
    config.boidRadius = 5;
    config.separationRadius = 50;
    config.alignmentRadius = 80;
    config.cohesionRadius = 100;

    // Initialize Flock
    std::cout << "Creating Flock..." << std::endl;
    Flock flock(config);
    std::cout << "Flock Created!" << std::endl;

    // Initialize SFML Window
    sf::RenderWindow App(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Boid Flocking Simulation");

    if (!App.isOpen()) {
        std::cerr << "SFML Window failed to open!" << std::endl;
        return EXIT_FAILURE;
    }

    // Main Loop
    sf::Clock clock;
    while (App.isOpen()) {
        // Handle Events
        sf::Event event;
        while (App.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                App.close();
        }

        // Update Simulation
        float dt = clock.restart().asSeconds();
        flock.applyFlockingRules();
        flock.update();  // Ensure update function accepts delta time

        // Render
        App.clear();
        flock.render(App);
        App.display();

        sf::sleep(sf::milliseconds(16));  // Maintain ~60 FPS
    }

    return EXIT_SUCCESS;
}
