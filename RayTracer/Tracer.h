#pragma once

#include "Types.h"
#include "ColorBuffer.h"

class Tracer
{
public:
	void Trace(const ColorBuffer& colorBuffer, class Scene* scene, class Camera* camera);

public:
	int samples = 10;
	int depth = 30;
};