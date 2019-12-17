#include "vertex_properties.hxx"

using namespace dreco;

vertex_properties::vertex_properties()
{
}

vertex_properties vertex_properties::ModelPlane()
{
	vertex_properties model = vertex_properties();

	// clang-format off
	model.vertexes = 
    {
		-0.5f, 0.5f, 0.0f, 
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f
	};
	model.vert_elem = 
	{
		0, 1, 2,
		0, 2, 3
	};
	model.texture_coords = 
    {   
        0.0, 1.0,
	    0.0, 0.0,
        1.0, 0.0,

		1.0, 1.0,
		0.0, 1.0,
		1.0, 0.0,
    };
	// clang-format on

	return model;
}