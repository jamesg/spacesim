#include "matrix.hpp"

matrix<4,1> multiplyquaternions(matrix<4,1> a, matrix<4,1> b) {
	a = a.unitvector();
	b = b.unitvector();
	matrix<4,1> r = 
	{{ {(a[0][3]*b[0][0] + a[0][0]*b[0][3] + a[0][1]*b[0][2] - a[0][2]*b[0][1]),
	(a[0][3]*b[0][1] + a[0][1]*b[0][3] + a[0][2]*b[0][0] - a[0][0]*b[0][2]),
	(a[0][3]*b[0][2] + a[0][2]*b[0][3] + a[0][0]*b[0][1] - a[0][1]*b[0][0]),
	(a[0][3]*b[0][3] - a[0][0]*b[0][0] - a[0][1]*b[0][1] - a[0][2]*b[0][2])} }};
	matrix<4,1> test = r.unitvector();
	return test;
}

matrix<3,1> rotatevectorbyquaternion(matrix<3,1> v, matrix<4,1> q) {
	float mag = v.magnitude();
	matrix<3,1> vn = v.unitvector();
	
	matrix<4,1> vecQuat, resQuat;
	vecQuat[0][0] = vn[0][0];
	vecQuat[0][1] = vn[0][1];
	vecQuat[0][2] = vn[0][2];
	vecQuat[0][3] = 0.0f;
	
	resQuat = multiplyquaternions(vecQuat, quaternioncougate(q));
	resQuat = multiplyquaternions(q, resQuat);

	return (matrix<3,1>){{ {resQuat[0][0], resQuat[0][1], resQuat[0][2]} }} ;
}

matrix<4,1> quaternioncougate(matrix<4,1> a) {
	return (matrix<4,1>){{	{-a[0][0],-a[0][1],-a[0][2],a[0][3]} }};
}

matrix<4,1> quaternionfromaxis(matrix<3,1> v, float angle) {
	float sinAngle;
	angle *= 0.5f;
	matrix<3,1> vn = v.unitvector();
 
	sinAngle = sin(angle);
 
	matrix<4,1> q;
 
	q[0][0] = (vn[0][0] * sinAngle);
	q[0][1] = (vn[0][1] * sinAngle);
	q[0][2] = (vn[0][2] * sinAngle);
	q[0][3] = cos(angle);
	
	return q.unitvector();
}

matrix<4,4> quaterniontomatrix(matrix<4,1> q) {
	q = q.unitvector();
	
	float x2 = q[0][0] * q[0][0];
	float y2 = q[0][1] * q[0][1];
	float z2 = q[0][2] * q[0][2];
	
	float xy = q[0][0] * q[0][1];
	float xz = q[0][0] * q[0][2];
	float yz = q[0][1] * q[0][2];
	
	float wx = q[0][3] * q[0][0];
	float wy = q[0][3] * q[0][1];
	float wz = q[0][3] * q[0][2];
	
	matrix<4,4> r;
	r[0][0] = 1.0f - 2.0f * (y2 + z2);
	r[0][1] =  2.0f * (xy - wz);
	r[0][2] = 2.0f * (xz + wy);
	r[0][3] = 0.0f;
	r[1][0] = 2.0f * (xy + wz);
	r[1][1] = 1.0f - 2.0f * (x2 + z2);
	r[1][2] = 2.0f * (yz - wx);
	r[1][3] = 0.0f;
	r[2][0] = 2.0f * (xz - wy);
	r[2][1] = 2.0f * (yz + wx);
	r[2][2] = 1.0f - 2.0f * (x2 + y2);
	r[2][3] = 0.0f;
	r[3][0] = 0.0f;
	r[3][1] = 0.0f;
	r[3][2] = 0.0f;
	r[3][3] = 1.0f;
	return r;
}

matrix<4,1> slowquaternionrotation(matrix<4,1> q, float m) {
	if (m != 0) q[0][3] =  q[0][3] / m;
	return q.unitvector();
}
