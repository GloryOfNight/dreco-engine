#pragma once
#include "resources/texture.hxx"

#include <string>
#include <vector>

namespace dreco
{
struct vertex_properties
{
	vertex_properties();

	std::vector<float> vertexes = {};

	std::vector<uint8_t> vert_elem = {};

	std::vector<float> texture_coords = {};

	static vertex_properties ModelSpritePlane();
};
}	// namespace dreco