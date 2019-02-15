# comp140-worksheetB

## Part A - Arduino Game Controller Project

### Overview

For my game controller project I intend to create a game in the visual style of the original Elite games, or as close as possible, in 3D space.
As for the game controller itself, I have been thinking about ways to implement a 2-part controller:
* One part that would control the Player Ships's rotation on the 3 axis (and perhaps even movement speed) and
* Another part that would control the rest of the ships components, such as weapons.

### The game controller

The layout will consist of 2 parts: the right side will contain the movement controls, while the left side will control the ships' components.

For the Rotation and/or movement part, I intend to use either a Gyroscope (for rotations) attached to a tensiometer (for acceleration) or 4 tensiomeneters controlling the 3 rotational axis and the movement speed.

For the ship components controls' I intend to use, for starters, a single button layout for firing the weapons.

However, it should be noted that while the first part of the controller contains much of the most important controls, it may be cumbersome to use them all at once. Therefore, I was thinking about switching the movement controls to the second part of the controller to balance it out.

As for the exterior design of the controller, I was thinking about having either a button panel (for controlling the weapons) and some sort of outer casing (or fighter-style handle) for the gyro and acceleration tensiometer. Of course, that would mean that it would be able to rotate along all 3 axis as well as move forwards or backwards to determine the acceleration speed. As this may be cumbersome, I have also prepared an alternative layout.

The second layout I had in mind differs in only one aspect: the movement controls are next to the button panel, possibly as a handle that needs to be pushed forward or backwards to accelerate and deccelerate, respectively.

Finally, I intend to attach several LED's to the second part to display warnings such as fuel remaining, proximity warnings, damage wearnings etc. (Mostly for immersion)

### The game itself

For the game itself I intend to create a simple 3D space exploration game, with some basic interactivity (such as landing on certain stellar objects or crashing into planets) and some basic combat. As for the type of game I will be aiming for, I would most likely go for sanbox, as it presents little restrictions to the player, and much creative freedom for me to add and remove ideas as I continue the development process. 

As for the biggest setbacks I plan on encountering, I could name:
* My lack of knowledge in SDL will likely slow the initial development
* Since I will be using OpenGL I will need to research it intensely
* AI for enemies will certainly prove difficult, but I am confident that I can work it out
* Given the overall complexity, I will need to work with the overall performance in mind

### External references

[HOTAS controllers](https://www.windowscentral.com/best-hotas-controllers-vr)

[Original Elite ships](https://www.c64-wiki.com/images/thumb/0/0b/EliteShipIdentificationChart.jpg/800px-EliteShipIdentificationChart.jpg)
