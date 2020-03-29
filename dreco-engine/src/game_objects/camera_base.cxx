#include "camera_base.hxx"

#include "utils/math_utils.hxx"

using namespace dreco;

camera_base::camera_base(game_world* _w) : game_object{_w}, view{}, projection{}
{
}

void camera_base::Begin()
{
	game_object::Begin();
	
	view = CalculateViewMatrix();
	projection = CalculateProjectionMatrix();
}

void camera_base::SetTransform(const transform& _t)
{
	game_object::SetTransform(_t);
	view = CalculateViewMatrix();
}

void camera_base::OnScreenSizeUpdate()
{
	projection = CalculateProjectionMatrix();
}

mat2x3 camera_base::GetViewMatrix() const
{
	return view;
}

mat2x3 camera_base::GetProjectionMatrix() const
{
	return projection;
}

mat2x3 camera_base::CalculateViewMatrix() const
{
	return mat2x3::GetModelMatrix(GetTransform());
}

mat2x3 camera_base::CalculateProjectionMatrix() const
{
	int w, h;
	GetGameInstance()->GetViewSize(w, h);

	const float aspect_ratio = static_cast<float>(w) / static_cast<float>(h);

	// scale_factor applied when screen got too wide
	float scale_factor = 1.0f;
	if (aspect_ratio < 0.5625f)
	{
		scale_factor = (aspect_ratio / 0.5625f);
	}

	const float right_left = aspect_ratio / scale_factor;
	const float top_down = 1.0f / scale_factor;

	return math_utils::CreateProjectionMatrix2D(
		right_left, -right_left, top_down, -top_down);
}