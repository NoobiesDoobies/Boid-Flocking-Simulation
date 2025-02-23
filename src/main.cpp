#include <iostream>
#include <string>
#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Gui.hpp"

#include "Boid.hpp"
#include "Flock.hpp"

#define WINDOW_HEIGHT 480
#define WINDOW_WIDTH 720

#define MENU_WIDTH 320
#define MENU_HEIGHT WINDOW_HEIGHT

#define MENU_PADDING_X 10
#define MENU_PADDING_Y 10

#define PROGRESS_BAR_LENGTH 40

#define SLIDER_LENGTH (MENU_WIDTH - MENU_PADDING_X) / 2 - PROGRESS_BAR_LENGTH

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

struct SliderConfig
{
    std::string name;
    int minValue;
    int maxValue;
    int step;
    float scaler;
    float *variableToBeChanged;
    std::unique_ptr<gui::ProgressBar> pbar;

};

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
    gui::VBoxLayout *vbox = menu.addVBoxLayout();

    menu.setPosition(WINDOW_WIDTH + MENU_PADDING_X, MENU_PADDING_Y);

    //  SliderConfig a {"test", 1, 2, 1, 1, &config.maxSpeed, std::make_unique<gui::ProgressBar*>(gui::ProgressBar(PROGRESS_BAR_LENGTH)) };

    // Create slider
    std::vector<SliderConfig> slider_configs;
    //                         name,                min,    max,    step,   scaler, variableToBeChanged
    // slider_configs.push_back({"Number of Boids", 1, 100, 1, 1, &config.numBoids});
    slider_configs.push_back({"Max Speed        ", 1, 20, 1, 1, &config.maxSpeed, std::make_unique<gui::ProgressBar>(gui::ProgressBar(PROGRESS_BAR_LENGTH))});
    slider_configs.push_back({"Max Force        ", 1, 20, 1, 1, &config.maxForce, std::make_unique<gui::ProgressBar>(gui::ProgressBar(PROGRESS_BAR_LENGTH))});
    slider_configs.push_back({"Separation Weight", 0, 20, 1, 1, &config.separationWeight, std::make_unique<gui::ProgressBar>(gui::ProgressBar(PROGRESS_BAR_LENGTH))});
    slider_configs.push_back({"Alignment Weight ", 0, 20, 1, 1, &config.alignmentWeight, std::make_unique<gui::ProgressBar>(gui::ProgressBar(PROGRESS_BAR_LENGTH))});
    slider_configs.push_back({"Cohesion Weight  ", 0, 20, 1, 1, &config.cohesionWeight, std::make_unique<gui::ProgressBar>(gui::ProgressBar(PROGRESS_BAR_LENGTH))});
    slider_configs.push_back({"Separation Radius", 1, 200, 1, 1, &config.separationRadius, std::make_unique<gui::ProgressBar>(gui::ProgressBar(PROGRESS_BAR_LENGTH))});
    slider_configs.push_back({"Alignment Radius ", 1, 200, 1, 1, &config.alignmentRadius, std::make_unique<gui::ProgressBar>(gui::ProgressBar(PROGRESS_BAR_LENGTH))});
    slider_configs.push_back({"Cohesion Radius  ", 1, 200, 1, 1, &config.cohesionRadius, std::make_unique<gui::ProgressBar>(gui::ProgressBar(PROGRESS_BAR_LENGTH))});
    slider_configs.push_back({"Boid Radius      ", 1, 20, 1, 1, &config.boidRadius, std::make_unique<gui::ProgressBar>(gui::ProgressBar(PROGRESS_BAR_LENGTH))});

    for (auto &slider_config : slider_configs)
    {
        gui::HBoxLayout *hbox1 = vbox->addHBoxLayout();

        // add label
        hbox1->addLabel(slider_config.name);

        // add slider
        gui::Slider *slider = new gui::Slider(SLIDER_LENGTH);
        slider->setStep(slider_config.step);
        slider->setCallback([&slider_config, slider, &config, &flock]()
                            {
                                // Directly update the value
                                *slider_config.variableToBeChanged = slider->getValue() * slider_config.scaler;

                                // Apply updated config
                                flock.setConfig(config);

                                // Debug print
                                std::cout << slider_config.name << " is now " << *slider_config.variableToBeChanged << std::endl;

                                slider_config.pbar.get()->setValue(slider->getValue());
                            });
        hbox1->add(slider);

        // add progress bar
        hbox1->add(slider_config.pbar.get());
    }

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
