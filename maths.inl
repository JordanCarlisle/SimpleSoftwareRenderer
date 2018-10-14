#pragma once

namespace maths
{
	inline bool pointInTriangle(const v2& p, const v2& a, const v2& b, const v2& c)
	{
		v3 uvec = cross(
			v3(
				c.x - a.x,
				b.x - a.x,
				a.x - p.x
			),
			v3(
				c.y - a.y,
				b.y - a.y,
				a.y - p.y
			)
		);

		if (uvec.z < 1.0f)
			return false;

		v3 uvw(
			1.0f - (uvec.x + uvec.y) / uvec.z,
			uvec.y / uvec.z,
			uvec.x / uvec.z
		);

		if (uvw.x < 0.0f || uvw.y < 0.0f || uvw.z < 0.0f)
			return false;

		return true;
	}

	inline v3 barycentricCoords(const v2& p, const v2& a, const v2& b, const v2& c)
	{
		v3 uvec = cross(
			v3(
				c.x - a.x,
				b.x - a.x,
				a.x - p.x
			),
			v3(
				c.y - a.y,
				b.y - a.y,
				a.y - p.y
			)
		);

		if (uvec.z < 1.0f)
			return v3(1.0f, 1.0f, -1.0f);

		return v3(
			1.0f - (uvec.x + uvec.y) / uvec.z,
			uvec.y / uvec.z,
			uvec.x / uvec.z
		);
	}

	inline v3 barycentricCoords(const v3& p, const v3& a, const v3& b, const v3& c)
	{
		v3 uvec = cross(
			v3(
				c.x - a.x,
				b.x - a.x,
				a.x - p.x
			),
			v3(
				c.y - a.y,
				b.y - a.y,
				a.y - p.y
			)
		);

		if (std::fabs(uvec.z) < 1.0f)
			return v3(-1.0f, 1.0f, 1.0f);

		return v3(
			1.0f - (uvec.x + uvec.y) / uvec.z,
			uvec.y / uvec.z,
			uvec.x / uvec.z
		);
	}

	inline float degToRad(float degrees)
	{
		return degrees * PI / 180.0f;
	}
	
	inline float radToDeg(float radians)
	{
		return radians * 180.0f / PI;
	}
}