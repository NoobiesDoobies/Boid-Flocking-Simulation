#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Gui.hpp"

#include "Boid.hpp"
#include "Flock.hpp"

#define WINDOW_HEIGHT 480
#define WINDOW_WIDTH 720

#define MENU_WIDTH 240
#define MENU_HEIGHT WINDOW_HEIGHT
sf::Color hex2color(const std::string &hexcolor)
{
    sf::Color color = sf::Color::White;
    if (hexcolor.size() == 7) // #ffffff
    {
        color.r = strtoul(hexcolor.substr(1, 2).c_str(), NULL, 16);
        color.g = strtoul(hexcolor.substr(3, 2).c_str(), NULL, 16);
        color.b = strtoul(hexcolor.substr(5, 2).c_str(), NULL, 16);
    }
    else if (hexcolor.size() == 4) // #fff
    {
        color.r = strtoul(hexcolor.substr(1, 1).c_str(), NULL, 16) * 17;
        color.g = strtoul(hexcolor.substr(2, 1).c_str(), NULL, 16) * 17;
        color.b = strtoul(hexcolor.substr(3, 1).c_str(), NULL, 16) * 17;
    }
    return color;
}

void clearScreen(sf::RenderWindow *window, sf::Color sim_bg_color, sf::Color slider_bg_color)
{
    sf::RectangleShape sim({WINDOW_WIDTH, WINDOW_HEIGHT});
    sf::RectangleShape slider({MENU_WIDTH, MENU_HEIGHT});

    sim.setPosition({0, 0});
    sim.setFillColor(sim_bg_color);

    slider.setPosition({WINDOW_WIDTH, 0});
    slider.setFillColor(slider_bg_color);

    window->draw(sim);
    window->draw(slider);
}

int main()
{
    // Create Config
    FlockConfig config;
    config.numBoids = 50;
    config.windowWidth = WINDOW_WIDTH;
    config.windowHeight = WINDOW_HEIGHT;
    config.maxSpeed = 10.0f;
    config.maxForce = 0.1f;
    config.randomize = true;
    config.separationWeight = 10.0;
    config.alignmentWeight = 1.0;
    config.cohesionWeight = 1.0;
    config.boidRadius = 7.5;
    config.separationRadius = WINDOW_WIDTH / 10;
    config.alignmentRadius = WINDOW_WIDTH / 5;
    config.cohesionRadius = WINDOW_WIDTH / 5;

    // Initialize Flock
    std::cout << "Creating Flock..." << std::endl;
    Flock flock(config);
    std::cout << "Flock Created!" << std::endl;

    // Initialize SFML Window
    sf::RenderWindow App(sf::VideoMode(WINDOW_WIDTH + MENU_WIDTH, WINDOW_HEIGHT), "Boid Flocking Simulation");

    if (!App.isOpen())
    {
        std::cerr << "SFML Window failed to open!" << std::endl;
        return EXIT_FAILURE;
    }

    // Create widgets
    gui::Menu menu(App);
    gui::Theme::loadFont("widget_styles/tahoma.ttf");
    gui::Theme::loadTexture("widget_styles/texture-default.png");
    gui::Theme::windowBgColor = hex2color("#d4d0c8");
    gui::HBoxLayout *hbox = menu.addHBoxLayout();
    gui::FormLayout *form = hbox->addFormLayout();

    menu.setPosition(WINDOW_WIDTH, 0);

    // Create slider
    gui::Slider *test_slider = new gui::Slider();
    test_slider->setStep(1);
    test_slider->setCallback([&]()
                             { std::cout << "Value is " << test_slider->getValue() << std::endl; });
    form->addRow("Test Slider", test_slider);

    // Main Loop
    sf::Clock clock;
    while (App.isOpen())
    {
        // Handle Events
        sf::Event event;
        while (App.pollEvent(event))
        {
            menu.onEvent(event);
            if (event.type == sf::Event::Closed)
                App.close();
        }

        // Draw slider

        // Update Simulation
        float dt = clock.restart().asSeconds();
        flock.applyFlockingRules();
        flock.update(); // Ensure update function accepts delta time

        // Render
        // App.clear(hex2color("#d4d0c8"));
        clearScreen(&App, sf::Color::Black, hex2color("#d4d0c8"));
        App.draw(menu);
        flock.render(App);
        App.display();

        sf::sleep(sf::milliseconds(16)); // Maintain ~60 FPS
    }

    return EXIT_SUCCESS;
}
