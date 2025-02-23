# Boid Flocking Simulation

A **Boid Flocking Simulation** implemented in **C++** using **SFML** and **[SFML Widgets](https://github.com/abodelot/sfml-widgets)** , demonstrating emergent flocking behavior inspired by [Craig Reynold's Boids algorithm](https://en.wikipedia.org/wiki/Boids).

Boid Flocking Simulation Preview

![Boid Flocking Simulation](https://github.com/NoobiesDoobies/Boid-Flocking-Simulation/blob/main/demo/no_settings.gif)


## How to Build Project
### 1. Clone Repo
```
cd && mkdir cpp-projects
cd cpp-projects
git clone git@github.com:NoobiesDoobies/Boid-Flocking-Simulation.git
```

### 2. Install SFML
```
sudo apt update
sudo apt install libsfml-dev cmake g++
```

### 3. Clone SFML Widgets library
```
git clone git@github.com:abodelot/sfml-widgets.git
```

### 4. Build SFML Widgets Library
```
cd sfml-widgets 
make
cd ..
```

### 5. Build Project
```
cd Boid-Flocking-Simulation
mkdir build && cd build
cmake .. -DUSE_CUSTOM_SFML_WIDGETS=ON \
    -DSFML_WIDGETS_LIBRARY_PATH="/path/to/sfml-widgets/lib" \
    -DSFML_WIDGETS_HEADER_PATH="/path/to/sfml-widgets/src/Gui"
make
```

## Simulation with Sliders:
![Boid Flocking Simulation with Sliders](https://github.com/NoobiesDoobies/Boid-Flocking-Simulation/blob/main/demo/with_settings.gif)
