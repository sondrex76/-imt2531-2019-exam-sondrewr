# imt2531-2019-exam-sondrewr

## Deployment process
- Clone the repository then open CMakeLists.txt within the primary folder with cmake
- Run Exam-imt2531-2019.exe through cmake

## Use
- When the program runs you will spawn at a set locaiton
- You can look around by moving your mouse around, and change your camera's location using the buttons on the screen
	- You are only able to look a specific amount up and down
	- Currently the mouse detection is weird in that for the y axis it will not allow you to move back again until your mouse is at the same relative location to where it was when you started in the y direction
- The wasd keys move the raindeer according to the direciton it is facing
	- If you want to see the raindeer you must move downwards and look around
- If you want to see more snow you must move further into the map

## Functionality
- A randomly generated map is generated each time you run the program, the terrain uses perlin noise for its terrain generation
- Elevations are textured by different textures based on height
- A raindeer is rendered, move down to see it
- Snow spawns at a set height above the map and despawns when it reaches the height of the ground
- You can change which direction you are looking at by moving your mouse
- You can change your x, y and z coordinates by clicking the buttons to the top left
- You can place a light by clicking the place light button just to the right to the movement keys
- You can move the raindeer by hitting the wasd keys
- There is a source of light that makes shadows

## Sources of resources
Perlin noise: https://en.wikipedia.org/wiki/Perlin_noise
SNowflake model: https://free3d.com/3d-model/fernlike-stellar-dendrites-snowflake-v1--169045.html