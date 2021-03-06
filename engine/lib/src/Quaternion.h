#ifndef __Quaternion_h__
#define __Quaternion_h__

#include "Vector3.h"

namespace Galaxy3D
{
	class Quaternion
	{
	public:
		Quaternion(float x=0, float y=0, float z=0, float w=1);

		Quaternion operator *(const Quaternion &q) const;
		Vector3 operator *(const Vector3 &p) const;
		bool operator !=(const Quaternion &v) const;
		bool operator ==(const Quaternion &v) const;
		Vector3 ToEulerAngles() const;
		std::string ToString() const;

		inline static Quaternion Identity() {return m_identity;}
		static Quaternion Inverse(const Quaternion &q);
		static Quaternion AngleAxis(float angle, const Vector3 &axis);
		static Quaternion Euler(float x, float y, float z);
		static Quaternion Euler(const Vector3 &e) {return Euler(e.x, e.y, e.z);}

	public:
		float x;
		float y;
		float z;
		float w;

	private:
		static Quaternion m_identity;
	};
}

#endif