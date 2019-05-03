#pragma once

#include "../renderer/Mesh.h"

const Renderer::Vertex vertices[] = {
	//Side 1
	Renderer::Vertex{ /*pos*/{-0.5f, -0.5f, -0.5f}, /*norm*/{1, 1, 1}, /*uv*/{0.5, 0.5}},
	Renderer::Vertex{ /*pos*/{0.5f, -0.5f, -0.5f}, /*norm*/{1, 1, 1}, /*uv*/{0.5, 0.5}},
	Renderer::Vertex{ /*pos*/{0.5f,  0.5f, -0.5f}, /*norm*/{1, 1, 1}, /*uv*/{0.5, 0.5}},
	Renderer::Vertex{ /*pos*/{0.5f,  0.5f, -0.5f}, /*norm*/{1, 1, 1}, /*uv*/{0.5, 0.5}},
	Renderer::Vertex{ /*pos*/{-0.5f,  0.5f, -0.5f}, /*norm*/{1, 1, 1}, /*uv*/{0.5, 0.5}},
	Renderer::Vertex{ /*pos*/{-0.5f, -0.5f, -0.5f}, /*norm*/{1, 1, 1}, /*uv*/{0.5, 0.5}},

	//Side 2
	Renderer::Vertex{ /*pos*/{-0.5f, -0.5f,  0.5f}, /*norm*/{1, 1, 1}, /*uv*/{0.5, 0.5}},
	Renderer::Vertex{ /*pos*/{0.5f, -0.5f,  0.5f}, /*norm*/{1, 1, 1}, /*uv*/{0.5, 0.5}},
	Renderer::Vertex{ /*pos*/{0.5f,  0.5f,  0.5f}, /*norm*/{1, 1, 1}, /*uv*/{0.5, 0.5}},
	Renderer::Vertex{ /*pos*/{0.5f,  0.5f,  0.5f}, /*norm*/{1, 1, 1}, /*uv*/{0.5, 0.5}},
	Renderer::Vertex{ /*pos*/{-0.5f,  0.5f,  0.5f}, /*norm*/{1, 1, 1}, /*uv*/{0.5, 0.5}},
	Renderer::Vertex{ /*pos*/{-0.5f, -0.5f,  0.5f}, /*norm*/{1, 1, 1}, /*uv*/{0.5, 0.5}},

	//Side 3
	Renderer::Vertex{ /*pos*/{-0.5f,  0.5f,  0.5f}, /*norm*/{1, 1, 1}, /*uv*/{0.5, 0.5}},
	Renderer::Vertex{ /*pos*/{-0.5f,  0.5f, -0.5f}, /*norm*/{1, 1, 1}, /*uv*/{0.5, 0.5}},
	Renderer::Vertex{ /*pos*/{-0.5f, -0.5f, -0.5f}, /*norm*/{1, 1, 1}, /*uv*/{0.5, 0.5}},
	Renderer::Vertex{ /*pos*/{-0.5f, -0.5f, -0.5f}, /*norm*/{1, 1, 1}, /*uv*/{0.5, 0.5}},
	Renderer::Vertex{ /*pos*/{-0.5f, -0.5f,  0.5f}, /*norm*/{1, 1, 1}, /*uv*/{0.5, 0.5}},
	Renderer::Vertex{ /*pos*/{-0.5f,  0.5f,  0.5f}, /*norm*/{1, 1, 1}, /*uv*/{0.5, 0.5}},

	//Side 4
	Renderer::Vertex{ /*pos*/{0.5f,  0.5f,  0.5f}, /*norm*/{1, 1, 1}, /*uv*/{0.5, 0.5}},
	Renderer::Vertex{ /*pos*/{0.5f,  0.5f, -0.5f}, /*norm*/{1, 1, 1}, /*uv*/{0.5, 0.5}},
	Renderer::Vertex{ /*pos*/{0.5f, -0.5f, -0.5f}, /*norm*/{1, 1, 1}, /*uv*/{0.5, 0.5}},
	Renderer::Vertex{ /*pos*/{0.5f, -0.5f, -0.5f}, /*norm*/{1, 1, 1}, /*uv*/{0.5, 0.5}},
	Renderer::Vertex{ /*pos*/{0.5f, -0.5f,  0.5f}, /*norm*/{1, 1, 1}, /*uv*/{0.5, 0.5}},
	Renderer::Vertex{ /*pos*/{0.5f,  0.5f,  0.5f}, /*norm*/{1, 1, 1}, /*uv*/{0.5, 0.5}},

	//Side 5
	Renderer::Vertex{ /*pos*/{-0.5f, -0.5f, -0.5f}, /*norm*/{1, 1, 1}, /*uv*/{0.5, 0.5}},
	Renderer::Vertex{ /*pos*/{0.5f, -0.5f, -0.5f}, /*norm*/{1, 1, 1}, /*uv*/{0.5, 0.5}},
	Renderer::Vertex{ /*pos*/{0.5f, -0.5f,  0.5f}, /*norm*/{1, 1, 1}, /*uv*/{0.5, 0.5}},
	Renderer::Vertex{ /*pos*/{0.5f, -0.5f,  0.5f}, /*norm*/{1, 1, 1}, /*uv*/{0.5, 0.5}},
	Renderer::Vertex{ /*pos*/{-0.5f, -0.5f,  0.5f}, /*norm*/{1, 1, 1}, /*uv*/{0.5, 0.5}},
	Renderer::Vertex{ /*pos*/{-0.5f, -0.5f, -0.5f}, /*norm*/{1, 1, 1}, /*uv*/{0.5, 0.5}},

	//Side 6
	Renderer::Vertex{ /*pos*/{-0.5f,  0.5f, -0.5f}, /*norm*/{1, 1, 1}, /*uv*/{0.5, 0.5}},
	Renderer::Vertex{ /*pos*/{0.5f,  0.5f, -0.5f}, /*norm*/{1, 1, 1}, /*uv*/{0.5, 0.5}},
	Renderer::Vertex{ /*pos*/{0.5f,  0.5f,  0.5f}, /*norm*/{1, 1, 1}, /*uv*/{0.5, 0.5}},
	Renderer::Vertex{ /*pos*/{0.5f,  0.5f,  0.5f}, /*norm*/{1, 1, 1}, /*uv*/{0.5, 0.5}},
	Renderer::Vertex{ /*pos*/{-0.5f,  0.5f,  0.5f}, /*norm*/{1, 1, 1}, /*uv*/{0.5, 0.5}},
	Renderer::Vertex{ /*pos*/{-0.5f,  0.5f, -0.5f}, /*norm*/{1, 1, 1}, /*uv*/{0.5, 0.5}},
}
;