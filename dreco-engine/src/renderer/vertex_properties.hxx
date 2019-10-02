#pragma once
#include "renderer/texture.hxx"

#include <string>
#include <vector>
#include <memory>

namespace dreco
{
struct vertex_properties
{
	vertex_properties()
	{
	}

	std::vector<float> vertexes = {};

	std::vector<float> texture_coords = {};

    std::shared_ptr<texture> texture_ptr = nullptr;
};
}	// namespace dreco