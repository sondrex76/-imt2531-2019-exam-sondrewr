#pragma once

#include "../renderer/RenderContext.h"
#include "..//renderer/Model.h"
#include "consts.h"

class Enviorment {
private:
	Renderer::Model terrain;
public:
	Enviorment(Renderer::RenderContext&);
};