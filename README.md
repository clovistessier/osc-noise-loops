# osc-noise-loops
This openFrameworks application uses Perlin noise to generate seamless loops of smooth random values, and transmits them over OSC.

## Description

### What is Perlin Noise?
Perlin noise is an algorithm developed by Ken Perlin for procedurally generating smooth, natural looking textures  for things like water and clouds in video games. You can evaluate the noise function in up 4 dimensions using ofNoise in openFrameworks, and it's characterized by having all points in the noise field be relatively similar to its neighbors in all directions. Compared to pure randomness or something like white noise, this means that there are smooth transitions from any point to any other point in the noise field.

In this application, we are generating a noise field in 3 dimensions and drawing a 2 dimensional slice of it on the left side of the window, mapping the noise value to a greyscale brightness value. If we treat the 3rd dimension as a Z axis, the slice above and below the one being drawn would be visually very similar to the one we can see, but we'll get more into that later.

### Noise Loops
The concept for this application is heavily inspired by this video from Dan Shiffman, and it serves as a good explainer as to what's going on here. Many thanks to him for providing so many great tutorials on creative coding concepts.

[![Coding Train: Polar Perlin Noise Loops](https://img.youtube.com/vi/ZI1dmHv3MeM/0.jpg)](https://www.youtube.com/watch?v=ZI1dmHv3MeM)

Moving in a circular path in the 2-dimensional noise field, while evaulating the brightness of each pixel along the way, will produce a seamlessly repeating sequence of smoothly varying pseudo random numbers. This application provides 6 of these loops in different sizes. All the loops share the same loop period and cursor angle. The brightness seen by each cursor is traced out on the right side of the window. The bigger loops are bumpier because the cursor moves faster and sees more of the noise field than the smaller loops. 

At the end of every cycle, the z value is incremented by a small amount. This moves the noise field being drawn to a slice directly above the current slice. This changes the loops slightly every cycle, causing them to slowly drift and evolve over time. The past 10 cycles are visualized in the traces, with decreasing brightness, allowing you to see how things have been changing at a glance. Setting the dz slider to 0.0 disables this behavior.

## Dependencies and Installation

All of the ofx addons used in this application are included in the base install of openFrameworks.

1. Install [openFrameworks](https://openframeworks.cc/) (tested on 11.0 and 11.2)
2. Clone this repository into the myApps folder of your oF install
3. Import with the projectGenerator to update it for your system
4. Build and run using your IDE

## Usage

Beyond the six loops, there are a couple of extra useful features:
- BPM Sync: Control the loop period from a clock
- Crossfader: smoothly interpolate between the six different loops
- Mixer: Add and subtract the 6 loops to make a composite loop

The GUI exposes the following controls:
- scaling of the noise field
- loop period (seconds)
- z offset to be applied at the end of each loop
- BPM sync
- Crossfader
- Mixer levels
- Center point and size of each loop 

pressing g on the keyboard hides/unhides the GUI

### OSC

[Open Sound Control](https://opensoundcontrol.stanford.edu/) is a protocol for sending real time communication messages between synthesizers, computers, and other multimedia devices. 

By default, this application sends the OSC messages to port 8000 on localhost. If you want to change this, the relevant #defines are at the top of ofApp.h

The arguments sent to address /noiseloop are as follows:
- 0-5: Current value of the 6 loops
- 6: Current value of the crossfader loop
- 7: Current value of the mixer

The clock is sent to address /clock

I use this with the OSC routing application [OSCulator](https://osculator.net/), which is highly recommended if you're using MacOS. [OSCRouter](https://github.com/ETCLabs/OSCRouter) from ETCLabs is another option.