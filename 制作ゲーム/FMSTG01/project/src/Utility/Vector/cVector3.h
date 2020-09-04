#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	cVector3.h													*/
/*  @brief		:	�Q�����x�N�g���N���X										*/
/*	@written	:	s.kosugi													*/
/*	@create		:	2019/03/04													*/
/*																				*/
/*==============================================================================*/

#include <DxLib.h>
//================================================================================================
// �x�N�g���N���X
class cVector3
{
public:
	float	x;
	float	y;
	float	z;

	
	cVector3(void);
	cVector3(float x, float y);
	cVector3(float x, float y,float z);
	cVector3(const cVector3& v );
	~cVector3();

	//------------------------------------------------------------------------------------
	// �I�y���[�^�[�I�[�o�[���[�h

	// ���
	inline  cVector3&   operator=(const cVector3& v)
	{
		x = v.x; y = v.y; z = v.z;
		return *this;
	};
	// ���Z
	inline  cVector3&   operator+=(const cVector3& v)
	{
		x += v.x; y += v.y; z += v.z;
		return *this;
	};
	// ���Z
	inline  cVector3&   operator-=(const cVector3& v)
	{
		x -= v.x; y -= v.y; z -= v.z;
		return *this;
	};
	// ��Z(�X�J���[�{)
	inline  cVector3&	operator*=(float scalar)
	{
		x *= scalar; y *= scalar; z *= scalar;
		return *this;
	};
	// ����
	inline	bool		operator==(cVector3 v) const { return ( x == v.x && y == v.y && z == v.z); };
	// �s��
	inline	bool		operator!=(cVector3 v) const { return (x != v.x && y != v.y && z != v.z); };
	// ���Z
	inline	cVector3	operator+(const cVector3& v) { 
		cVector3 ret;
		ret.x = x + v.x; ret.y = y + v.y; ret.z = z + v.z;
		return ret;
	};
	// ���Z
	inline	cVector3	operator-(const cVector3& v) {
		cVector3 ret;
		ret.x = x - v.x; ret.y = y - v.y; ret.z = z - v.z;
		return ret;
	};
	// ��Z
	inline	cVector3	operator*(const cVector3& v) {
		cVector3 ret;
		ret.x = x * v.x; ret.y = y * v.y; ret.z = z * v.z;
		return ret;
	};
	// ��Z(�X�J���[�{)
	inline	cVector3	operator*(float scalar) {
		cVector3 ret;
		ret.x = x * scalar; ret.y = y * scalar; ret.z = z * scalar;
		return ret;
	};
	// ���Z
	inline	cVector3	operator/(const cVector3& v) {
		cVector3 ret;
		ret.x = x / v.x; ret.y = y / v.y; ret.z = z / v.z;
		return ret;
	};
	// ���Z(�X�J���[)
	inline	cVector3	operator/(float scalar) {
		cVector3 ret;
		ret.x = x / scalar; ret.y = y / scalar; ret.z = z / scalar;
		return ret;
	};
	// ������
	inline	cVector3	operator-( void ) {
		return cVector3(-x,-y,-z);
	};

	// �L���X�g���Z�q
	// DXLib�p�̃x�N�g���\���̂ɃL���X�g����
	operator VECTOR() const { return VECTOR{ x,y,z }; };
	
	//------------------------------------------------------------------------------------
};