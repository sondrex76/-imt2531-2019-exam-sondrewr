# imt2531-2019-exam-sondrewr

## Deployment process
- Clone the repository then open CMakeLists.txt within the primary folder with cmake
- Run Exam-imt2531-2019.exe through cmake

## Use
- When the program runs you will spawn at a set locaiton
- You can look around by moving your mouse around, and change your camera's location using the buttons on the screen or hitting wasd + space and left shift
	- You are only able to look a specific amount up and down
- You can change camera mode by hitting 't'
- While in free range camera mode you can manouver with wasd, but in third and first person mode you cannot 
- If you want to see more snow you must move further into the map or mvoe upwards

## Functionality
- A randomly generated map is generated based on the perlin noise algorithm
- The terrain is textured based on height
- Elevations are textured by different textures based on height
- A raindeer is rendered, it is below the starting position of the user
- Snow spawns at a set height above the map and despawns when it reaches the height of the ground
- You can change which direction you are looking at by moving your mouse
- You can change your x, y and z coordinates by clicking the buttons to the top left or using wasd + space and shift for up and down respectivly
- You can place a light by clicking the place light button just to the right to the movement keys
- You can move the raindeer by hitting the wasd keys while in first and third person view
- There is a source of light that makes shadows
- There is a skybox and a rendered sun on the horizon, the sky is blue and the void is a dark red
- When the raindeer moves it will follow the slope of the terrain

## WIP
- I wanted to use some form of noise generation such as Fractional Brownian Motion). to generate the random values used for the perlin nose used for terran generation but did not have the time
- Main has too much code in it, if I had more time I would have prioritised splitting it and moving various pieces of code into new and/or relevant files

## Sources of resources
- Perlin noise: https://en.wikipedia.org/wiki/Perlin_noise

## Known bugs
- You move faster diagonally then stright since I am not normalizing the speed based on direction
- Movement over terrain is based on the camera's position, not the model's at the moment