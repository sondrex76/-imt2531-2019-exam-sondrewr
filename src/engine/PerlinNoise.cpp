#include "PerlinNoise.h"

float lerp(float value1, float value2, float distance) {
	return (1.0f - distance) * value1 + distance * value2;
}

// Computes the dot product of the distance and gradient vectors.
float dotGridGradient(int ix, int iy, float x, float y) {

	// Precomputed (or otherwise) gradient vectors at each grid node
	extern float globalGradient[SIZE_ZONES][SIZE_ZONES][2];

	// Compute the distance vector
	float dx = x - (float)ix;
	float dy = y - (float)iy;

	// Compute the dot-product
	return (dx * globalGradient[iy][ix][0] + dy * globalGradient[iy][ix][1]);
}

// Compute Perlin noise at coordinates x, y, must send x and y coordinates divided on 10
float perlin(float x, float y) {

	// Determine grid cell coordinates
	int lowerLeft = (int)x;
	int lowerRight = lowerLeft + 1;
	int upperLeft = (int)y;
	int upperRight = upperLeft + 1;

	// Determine interpolation weights
	// Could also use higher order polynomial/s-curve here
	float sx = x - (float)lowerLeft;
	float sy = y - (float)upperLeft;

	// Interpolate between grid point gradients
	float n0, n1, ix0, ix1, value;

	n0 = dotGridGradient(lowerLeft, upperLeft, x, y);
	n1 = dotGridGradient(lowerRight, upperLeft, x, y);
	ix0 = lerp(n0, n1, sx);

	n0 = dotGridGradient(lowerLeft, upperRight, x, y);
	n1 = dotGridGradient(lowerRight, upperRight, x, y);
	ix1 = lerp(n0, n1, sx);

	value = lerp(ix0, ix1, sy);

	return value;
}