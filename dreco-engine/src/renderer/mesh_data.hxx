#pragma once
#include <stdint.h>

namespace dreco
{
struct mesh_data
{
	mesh_data(float* _vertexes, const size_t& _vertexes_size, uint* _elements,
		const size_t& _elements_size, float* _texture_coordinates,
		const size_t& _texture_coordinates_size)
		: vertexes{_vertexes}
		, vertexes_size{_vertexes_size}
		, elements{_elements}
		, elements_size{_elements_size}
		, texture_coordinates{_texture_coordinates}
		, texture_coordinates_size{_texture_coordinates_size}
	{
	}
	~mesh_data()
	{
		if (vertexes)
			delete[] vertexes;

		if (elements)
			delete[] elements;

		if (texture_coordinates)
			delete[] texture_coordinates;
	}

	mesh_data(const mesh_data& _o) = delete;

	static inline mesh_data* CreateSpritePlane()
	{
		// clang-format off
		const size_t vertexes_size = 12;
		float* vertexes = new float[vertexes_size]
		{
			-0.5f, 0.5f, 0.0f, 
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.5f, 0.5f, 0.0f
		};

		const size_t elements_size = 6;
		uint* elements = new uint[elements_size] 
		{
			0, 1, 2,
			0, 2, 3
		};

		const size_t texture_coordinates_size = 12;
		float* texture_coordinates = new float[texture_coordinates_size] 
		{
			0.0, 1.0,
			0.0, 0.0,
			1.0, 0.0,

			1.0, 1.0,
			0.0, 1.0,
			1.0, 0.0,
		};
		// clang-format on
		return new mesh_data(vertexes, vertexes_size, elements, elements_size,
			texture_coordinates, texture_coordinates_size);
	}

	float* vertexes;
	const size_t vertexes_size;

	uint* elements;
	const size_t elements_size;

	float* texture_coordinates;
	const size_t texture_coordinates_size;
};
}	 // namespace dreco