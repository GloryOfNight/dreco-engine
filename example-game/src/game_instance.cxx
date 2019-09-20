#include "game_instance.hxx"

#include "core/engine.hxx"
#include "renderer/vertex.hxx"

#include <vector>

game_instance::game_instance(dreco::engine& _e) : game_base(_e)
{
}

void game_instance::Tick(const float& DeltaTime)
{
	std::vector<vertex> vertexes = {};
	vertexes.reserve(3);

	vertexes.push_back(vertex(-0.5f, 0.5f, 0.0f));
	vertexes.push_back(vertex( -0.5f, 0.0f, 0.0f));
	vertexes.push_back(vertex(0.5f, 0.0f, 0.0f));

	vertexes.push_back(vertex(0.5f, 0.5f, 0.0f));
	vertexes.push_back(vertex(-0.5f, 0.5f, 0.0f));
	vertexes.push_back(vertex(0.5f, 0.0f, 0.0f));

	GetEngine()->GetRenderer()->DrawVertexArray(vertexes);
}