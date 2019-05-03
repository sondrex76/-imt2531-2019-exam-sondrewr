#include "Enviorment.h"


// Constructor for enviorment
Enviorment::Enviorment(Renderer::RenderContext &renderContext) {
	std::vector<uint32_t> indices;						// indices
	std::vector<Renderer::Vertex> vertices;				// vector with vertexes

	for (int i = 0; i < NUM_TRIANGLES_TERRAIN; i++) {
		indices.push_back(i);
	}

	// Define all vertexis to generate terrain

	Renderer::Material terrainMaterial(Renderer::Material(glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.8, 0.8, 0.8), 32.0f, glm::vec3(1.0f, 1.0f, 1.0f)));
	terrain = Renderer::Model::fromGeometry(&vertices[0], 36, &indices[0], indices.size(), std::move(terrainMaterial), renderContext);
}