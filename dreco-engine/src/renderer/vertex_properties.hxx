#pragma once
#include "renderer/texture.hxx"

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

	texture* texture_ptr = nullptr;

	static vertex_properties ModelSpritePlane();
};
}	// namespace dreco