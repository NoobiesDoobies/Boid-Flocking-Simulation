#include <iostream>
#include <string>
#include <memory>
#include <bits/stdc++.h>

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

void drawSimulationWindow(sf::RenderWindow *window, sf::Color bg_color)
{
    sf::RectangleShape sim({WINDOW_WIDTH, WINDOW_HEIGHT});

    sim.setPosition({0, 0});
    sim.setFillColor(bg_color);

    window->draw(sim);
}

void drawSettingsWindow(sf::RenderWindow *window, sf::Color bg_color)
{
    sf::RectangleShape set({MENU_WIDTH, MENU_HEIGHT});

    set.setPosition({WINDOW_WIDTH, 0});
    set.setFillColor(bg_color);

    window->draw(set);
}

struct SliderConfig
{
    std::string name;
    int step;
    float default_value;
    float scaler;
    float *variableToBeChanged;
    std::unique_ptr<gui::ProgressBar> pbar;
    std::unique_ptr<gui::Label> value_label;
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
    config.alignmentRadius = WINDOW_WIDTH / 15;
    config.cohesionRadius = WINDOW_WIDTH / 5;
    config.followOneBoid = true;

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
    //                         name,               step,   default_value, scaler, variableToBeChanged
    slider_configs.push_back({"Max Speed        ", 1, config.maxSpeed, (config.maxSpeed * 3) / 100, &config.maxSpeed, std::make_unique<gui::ProgressBar>(gui::ProgressBar(PROGRESS_BAR_LENGTH)), std::make_unique<gui::Label>(gui::Label(std::to_string(config.maxSpeed)))});
    slider_configs.push_back({"Max Force        ", 1, config.maxForce, (config.maxForce * 3) / 100, &config.maxForce, std::make_unique<gui::ProgressBar>(gui::ProgressBar(PROGRESS_BAR_LENGTH)), std::make_unique<gui::Label>(gui::Label(std::to_string(config.maxForce)))});
    slider_configs.push_back({"Separation Weight", 1, config.separationWeight, (config.separationWeight * 3) / 100, &config.separationWeight, std::make_unique<gui::ProgressBar>(gui::ProgressBar(PROGRESS_BAR_LENGTH)), std::make_unique<gui::Label>(gui::Label(std::to_string(config.separationWeight)))});
    slider_configs.push_back({"Alignment Weight ", 1, config.alignmentWeight, (config.alignmentWeight * 3) / 100, &config.alignmentWeight, std::make_unique<gui::ProgressBar>(gui::ProgressBar(PROGRESS_BAR_LENGTH)), std::make_unique<gui::Label>(gui::Label(std::to_string(config.alignmentWeight)))});
    slider_configs.push_back({"Cohesion Weight  ", 1, config.cohesionWeight, (config.cohesionWeight * 3) / 100, &config.cohesionWeight, std::make_unique<gui::ProgressBar>(gui::ProgressBar(PROGRESS_BAR_LENGTH)), std::make_unique<gui::Label>(gui::Label(std::to_string(config.cohesionWeight)))});
    slider_configs.push_back({"Separation Radius", 1, config.separationRadius, (config.separationRadius * 3) / 100, &config.separationRadius, std::make_unique<gui::ProgressBar>(gui::ProgressBar(PROGRESS_BAR_LENGTH)), std::make_unique<gui::Label>(gui::Label(std::to_string(config.separationRadius)))});
    slider_configs.push_back({"Alignment Radius ", 1, config.alignmentRadius, (config.alignmentRadius * 3) / 100, &config.alignmentRadius, std::make_unique<gui::ProgressBar>(gui::ProgressBar(PROGRESS_BAR_LENGTH)), std::make_unique<gui::Label>(gui::Label(std::to_string(config.alignmentRadius)))});
    slider_configs.push_back({"Cohesion Radius  ", 1, config.cohesionRadius, (config.cohesionRadius * 3) / 100, &config.cohesionRadius, std::make_unique<gui::ProgressBar>(gui::ProgressBar(PROGRESS_BAR_LENGTH)), std::make_unique<gui::Label>(gui::Label(std::to_string(config.cohesionRadius)))});
    slider_configs.push_back({"Boid Radius      ", 1, config.boidRadius, (config.boidRadius * 3) / 100, &config.boidRadius, std::make_unique<gui::ProgressBar>(gui::ProgressBar(PROGRESS_BAR_LENGTH)), std::make_unique<gui::Label>(gui::Label(std::to_string(config.boidRadius)))});

    for (auto &slider_config : slider_configs)
    {
        gui::HBoxLayout *hbox1 = vbox->addHBoxLayout();

        // add label
        hbox1->addLabel(slider_config.name);

        // add slider
        gui::Slider *slider = new gui::Slider(SLIDER_LENGTH);
        slider->setStep(slider_config.step);
        slider->setValue(slider_config.default_value / slider_config.scaler);

        // set default value:
        slider_config.pbar.get()->setValue(slider->getValue());

        slider->setCallback([&slider_config, slider, &config, &flock]()
                            {
                                // Directly update the value
                                *slider_config.variableToBeChanged = slider->getValue() * slider_config.scaler;

                                // Apply updated config
                                flock.setConfig(config);

                                slider_config.pbar.get()->setValue(slider->getValue());
                                
                                slider_config.value_label.get()->setText(std::to_string(*slider_config.variableToBeChanged)); });
        hbox1->add(slider);

        // add progress bar
        // hbox1->add(slider_config.pbar.get());
        hbox1->add(slider_config.value_label.get());
    }

    gui::HBoxLayout *hbox2 = vbox->addHBoxLayout();

    gui::CheckBox *followOneBoidCheckBox = new gui::CheckBox(true);
    followOneBoidCheckBox->setCallback([&config, &flock, followOneBoidCheckBox]()
                                       {
                                           config.followOneBoid = followOneBoidCheckBox->isChecked();
                                           flock.setConfig(config);
                                       });
    hbox2->addLabel("Follow One Boid ");
    hbox2->add(followOneBoidCheckBox);

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
        drawSimulationWindow(&App, sf::Color::Black);
        flock.render(App);

        drawSettingsWindow(&App, hex2color("#d4d0c8"));
        App.draw(menu);

        App.display();

        sf::sleep(sf::milliseconds(16)); // Maintain ~60 FPS
    }

    return EXIT_SUCCESS;
}
