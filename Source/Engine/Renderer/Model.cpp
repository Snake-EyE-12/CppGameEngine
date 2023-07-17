#include "Model.h"
#include <sstream>

namespace cg
{
	bool Model::Load(const std::string& filename)
	{
		std::string buffer;
		cg::readFile(filename, buffer);

		std::istringstream stream(buffer);

		std::string line;
		std::getline(stream, line);

		int numPoints = std::stoi(line);
		for (int i = 0; i < numPoints; i++) {
			Vector2 point;
			stream >> point;
			m_points.push_back(point);
		}

		return true;
	}
	void Model::Draw(Renderer& renderer, const vec2& position, float rotation, float scale) {

		if (m_points.empty()) return;

		for (int i = 0; i < m_points.size() - 1; i++) {
			vec2 p1 = (m_points[i] * scale).Rotate(rotation) + position;
			vec2 p2 = (m_points[i + 1] * scale).Rotate(rotation) + position;
			renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}
	void Model::Draw(Renderer& renderer, const Transform& transform)
	{
		Draw(renderer, transform.position, transform.rotation, transform.scale);
	}
}