#pragma once
#include <vector>
#include <string>

namespace dreco
{
struct vertex_properties
{
    vertex_properties() 
    {
    }

    std::vector<float> vertexes = {};
    
    std::vector<float> texture_coords = {};

    std::string texture_path = "";
};
}	// namespace dreco