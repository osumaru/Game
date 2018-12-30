#include "engineStdafx.h"
#include "Matrix.h"



const CMatrix CMatrix::Identity(
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.0f, 0.0f, 1.0f
);

void CMatrix::Lerp(float t, const CMatrix & m0, const CMatrix & m1)
{
	CMatrix mat0 = m0;
	CMatrix mat1 = m1;
	CVector3 scale0;
	scale0.x = ((CVector3*)mat0.m[0])->Length();
	scale0.y = ((CVector3*)mat0.m[1])->Length();
	scale0.z = ((CVector3*)mat0.m[2])->Length();
	mat0.m[0][0] /= scale0.x;
	mat0.m[0][1] /= scale0.x;
	mat0.m[0][2] /= scale0.x;
	mat0.m[1][0] /= scale0.y;
	mat0.m[1][1] /= scale0.y;
	mat0.m[1][2] /= scale0.y;
	mat0.m[2][0] /= scale0.z;
	mat0.m[2][1] /= scale0.z;
	mat0.m[2][2] /= scale0.z;
	CVector3 scale1;
	scale1.x = ((CVector3*)mat1.m[0])->Length();
	scale1.y = ((CVector3*)mat1.m[1])->Length();
	scale1.z = ((CVector3*)mat1.m[2])->Length();
	mat1.m[0][0] /= scale1.x;
	mat1.m[0][1] /= scale1.x;
	mat1.m[0][2] /= scale1.x;
	mat1.m[1][0] /= scale1.y;
	mat1.m[1][1] /= scale1.y;
	mat1.m[1][2] /= scale1.y;
	mat1.m[2][0] /= scale1.z;
	mat1.m[2][1] /= scale1.z;
	mat1.m[2][2] /= scale1.z;
	CQuaternion rot0;
	rot0.SetRotation(mat0);
	CQuaternion rot1;
	rot1.SetRotation(mat1);
	rot0.Slerp(t, rot0, rot1);
	CVector3 pos0;
	pos0.x = mat0.m[3][0];
	pos0.y = mat0.m[3][1];
	pos0.z = mat0.m[3][2];
	CVector3 pos1;
	pos1.x = mat1.m[3][0];
	pos1.y = mat1.m[3][1];
	pos1.z = mat1.m[3][2];
	scale0.Lerp(t, scale0, scale1);
	pos0.Lerp(t, pos0, pos1);
	CMatrix transMat;
	transMat.MakeTranslation(pos0);
	CMatrix rotMat;
	rotMat.MakeRotationFromQuaternion(rot0);
	CMatrix scaleMat;
	scaleMat.MakeScaling(scale1);
	*this = CMatrix::Identity;
	this->Mul(scaleMat, rotMat);
	this->Mul(*this, transMat);
}
