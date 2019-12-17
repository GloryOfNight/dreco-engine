#pragma once
#include "renderer/texture.hxx"

#include <memory>
#include <string>
#include <vector>

namespace dreco
{
struct vertex_properties
{
	vertex_properties();

	std::vector<float> vertexes = {};

	std::vector<uint32_t> vert_elem = {};

	std::vector<float> texture_coords = {};

	std::shared_ptr<texture> texture_ptr = nullptr;

	static vertex_properties ModelPlane();
};
}	// namespace dreco