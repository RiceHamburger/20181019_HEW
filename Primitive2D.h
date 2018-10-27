/*====================================================================================

	��b�I�u�W�F�N�g�^�C�v�W�@2D�@ [primitive2D.h]
																Autor	: ����
																Date	: 2018/06/24
--------------------------------------------------------------------------------------
�R�����g:
--------------------------------------------------------------------------------------
�C������:
18/09/18 : Int2��ǉ��B
====================================================================================*/


#ifndef PRIMITIVE2D_H
#define PRIMITIVE2D_H

/*--------------------------------------------------------------------------------------
	�C���N���[�h�t�@�C��
--------------------------------------------------------------------------------------*/
#include <math.h>
#include <d3dx9.h>

/*--------------------------------------------------------------------------------------
	�萔��`
--------------------------------------------------------------------------------------*/
#define OX_EPSILON				(0.000001f)					//�덷

/*
	2����int
*/
struct Int2{
	//�Q����float
	float x, y;

	//�R���X�g���N�^ : �f�t�H���g
	Int2() : x(0.0f) , y(0.0f){}

	//�R���X�g���N�^ : 2����float�ɏ����l�������č쐬
	Int2( float x , float y) : x(x) , y(y){}

	//�f�X�X�g���N�^
	~Int2(){}

	//���Z�q�̃I�[�o�[���[�h
	Int2 operator + (const Int2 &r) const {
		return Int2(x + r.x, y + r.y);
	}

	Int2 operator - (const Int2 &r) const {
		return Int2(x - r.x, y - r.y);
	}

	Int2 operator -() const {
		return Int2(x * -1.0f, y * -1.0f);
	}

	Int2 operator * (const Int2 &r) const {
		return Int2(x * r.x, y * r.y);
	}

	Int2 operator / (const Int2 &r) const {
		return Int2(x / r.x, y / r.y);
	}

	Int2 operator * (float r) const {
		return Int2(x * r, y * r);
	}

	Int2 operator / (float r) const {
		return Int2(x / r, y / r);
	}

	friend Int2 operator * (float l, const Int2 &r) {
		return Int2(r.x * l, r.y * l);
	}

	friend Int2 operator / (float l, const Int2 &r) {
		return Int2(r.x / l, r.y / l);
	}
	//end���Z�q�̃I�[�o�[���[�h

	//�Z�b�g :  Int2 = float*2 
	Int2 Set(float nX, float nY) {
		x = nX;
		y = nY;
		return *this;
	}

};


/*
	2����float
*/
struct Float2{
	//�Q����float
	float x, y;

	//�R���X�g���N�^ : �f�t�H���g
	Float2() : x(0.0f) , y(0.0f){}

	//�R���X�g���N�^ : 2����float�ɏ����l�������č쐬
	Float2( float x , float y) : x(x) , y(y){}

	//�f�X�X�g���N�^
	~Float2(){}

	//���Z�q�̃I�[�o�[���[�h
	Float2 operator + (const Float2 &r) const {
		return Float2(x + r.x, y + r.y);
	}

	Float2 operator - (const Float2 &r) const {
		return Float2(x - r.x, y - r.y);
	}

	Float2 operator -() const {
		return Float2(x * -1.0f, y * -1.0f);
	}

	Float2 operator * (const Float2 &r) const {
		return Float2(x * r.x, y * r.y);
	}

	Float2 operator / (const Float2 &r) const {
		return Float2(x / r.x, y / r.y);
	}

	Float2 operator * (float r) const {
		return Float2(x * r, y * r);
	}

	Float2 operator / (float r) const {
		return Float2(x / r, y / r);
	}

	friend Float2 operator * (float l, const Float2 &r) {
		return Float2(r.x * l, r.y * l);
	}

	friend Float2 operator / (float l, const Float2 &r) {
		return Float2(r.x / l, r.y / l);
	}
	//end���Z�q�̃I�[�o�[���[�h

	//���Z�q�̃I�[�o�[���[�h D3DVECTOR2�Ƃ̌݊���
	Float2 operator + (const D3DXVECTOR2 &r) {
		return Float2(x + r.x, y + r.y);
	}

	Float2 operator - (const D3DXVECTOR2 &r) {
		return Float2(x - r.x, y - r.y);
	}

	Float2 operator * (const D3DXVECTOR2 &r) {
		return Float2(x * r.x, y * r.y);
	}

	Float2 operator / (const D3DXVECTOR2 &r) {
		return Float2(x / r.x, y / r.y);
	}

	Float2 operator = (const D3DXVECTOR2 &r) {
		return Float2(r.x, r.y);
	}
	//end���Z�q�̃I�[�o�[���[�h D3DVECTOR2�Ƃ̌݊���

	//�Q�b�g : D3DXVECTOR2�ւ̕ϊ�
	D3DXVECTOR2 toD3DXVECTOR2(void) {
		return D3DXVECTOR2(x, y);
	}

	//
	//�@�c�[�����\�b�h
	//

	//�Z�b�g :  Float2 = float*2 
	Float2 Set(float nX, float nY) {
		x = nX;
		y = nY;
		return *this;
	}


	//����
	float dot(const Float2 &r) const {
		return x * r.x + y * r.y;
	}

	//�O��
	float cross(const Float2 &r) const {
		return x * r.y - y * r.x;
	}

	//�x�N�g���Ƃ��Ă݂��ۂ̑傫��
	float length() const {
		return sqrtf(lengthSq());
	}

	//�ׂ��悵���傫��
	float lengthSq() const {
		return x * x + y * y;
	}

	//���K��:���̒l���X�V
	void norm() {
		const float len = length();
		if (len > 0.0f) {
			x /= len;
			y /= len;
		}
	}

	//���K��:���̒l�͎Q�Ƃ݂̂Ő��K�����ꂽ�l�����o��
	Float2 getNorm() const {
		const float len = length();
		if (len > 0.0f) {
			return Float2(x / len, y / len);
		}
		return Float2(0.0f, 0.0f);
	}


};


/*
	�_
*/
typedef Float2 Point2D;


/*
	�x�N�g��
*/
struct Vec2 : public Float2 
{
	//�R���X�g���N�^ : �f�t�H���g
	Vec2() {};

	//�R���X�g���N�^ : 2��������x�N�g���̍쐬
	Vec2(float x, float y) : Float2(x, y) {};

	//�R���X�g���N�^ : Float2�^���x�N�g���ɕϊ�
	Vec2(const Float2 &r) : Float2(r) {};

	//�f�X�X�g���N�^
	~Vec2() {};
	
	//�����Z�q�@�I�[�o�[���[�h
	Vec2& operator = (const Float2 &r) {
		x = r.x;
		y = r.y;

		return *this;
	}

	//���K��
	void norm() {
		const float len = length();
		if (len > 0.0f) {
			x /= len;
			y /= len;
		}
	}

	//��������
	bool isVertical(const Vec2 &r) const {
		float d = dot(r);
		return (-OX_EPSILON < d && d < OX_EPSILON);		//�덷�͈͓��Ȃ�O�Ƃ��Ĉ���
	}

	//���s����
	bool isParallel(const Vec2 &r) const {
		float d = cross(r);
		return (-OX_EPSILON < d && d < OX_EPSILON);		//�덷�͈͓��Ȃ�O�Ƃ��Ĉ���
	}

	//�s�p����
	bool isSharpAngle(const Vec2 &r) const {
		return (dot(r) >= 0.0f);
	}

};

/*
	����
*/
struct Line2D {
	Point2D p;		//�n�_
	Vec2 v;			//�����x�N�g��

	//�R���X�g���N�^ : �f�t�H���g
	Line2D() : p(0.0f, 0.0f), v(0.0f, 0.0f) {};

	//�R���X�g���N�^ : �_�ƃx�N�g�����璼���̍쐬
	Line2D(const Point2D &p, const Vec2 &v) : p(p), v(v) {};

	//�_��̍��W���擾����
	//�x�N�g���Ɋ|���Z����W��
	Point2D GetPoint(float t) const {
		return p + (v * t);
	}
};

/*
	����:��������
*/
struct Segment2D : public Line2D
{
	//�R���X�g���N�^ : �f�t�H���g
	Segment2D() {};

	//�R���X�g���N�^ : �_�ƃx�N�g����������̍쐬
	Segment2D(const Point2D &p, const Vec2 &v) : Line2D(p, v) {};

	//�R���X�g���N�^ : p1���n�_�Ap2���I�_�Ƃ��Đ����̍쐬
	Segment2D(const Point2D &p1, const Point2D &p2) : Line2D(p1, p2 - p1) {};

	//�I�_���擾
	Float2 GetEndPoint() const {
		return p + v;
	}
};

/*
	�~�QD
*/
struct Circle2D {
	Point2D p;		//���S�_
	float r;		//���a

	//�R���X�g���N�^ : �f�t�H���g
	Circle2D() : p(0.0f, 0.0f), r(0.5f) {}
	
	//�R���X�g���N�^ : �������l�@���
	Circle2D(const Point2D &p, float r) : p(p), r(r) {}

	//�f�X�X�g���N�^
	~Circle2D() {}
};

/*
	�J�v�Z��
*/
struct Capsule2D {
	Segment2D s;	//����
	float r;		//���a

	//�R���X�g���N�^ : �f�t�H���g
	Capsule2D() : r(0.5f) {}

	//�R���X�g���N�^ : �����Ɣ��a����J�v�Z���̍쐬
	Capsule2D(const Segment2D &s, float r) : s(s), r(r) {}

	//�R���X�g���N�^ : p1���n�_ , p2���I�_�Ƃ�������Ɣ��a����J�v�Z���̍쐬
	Capsule2D(const Point2D &p1, const Point2D &p2, float r) : s(p1, p2), r(r) {}

	//�J�v�Z�����l�p�`�Ƃ��Ă݂��ۂ̊e�ӂ̒���(�����d�������c)
	float lenX() { return s.v.length() + r * 2.0f; }
	float lenY() { return r * 2.0f; }

	//�f�X�X�g���N�^
	~Capsule2D() {}
};

/*
	�l�p�` : ���S���W�@+�@�e�ӂ�1/2�̒l�����^�C�v(�s���̈����ꍇ�ʓr�쐬)
*/
struct RectC2D {
	Point2D p;		//���S�_
	Float2 hl;		//�e�ӂ̒�����1/2

	//�R���X�g���N�^ : �f�t�H���g
	RectC2D() {}

	//�R���X�g���N�^ : �����l���w�肵�č쐬
	RectC2D(const Point2D &p, const Float2 &hl) : p(p), hl(hl) {}

	//�e�ӂ̒������擾
	float lenX() const { return hl.x * 2.0f; }
	float lenY() const { return hl.y * 2.0f; }
};


/*
	�l�p�` : ���㒸�_�@+ ���@+ ����
*/
struct Rect2D {
	Point2D p;		//���㒸�_
	Float2 l;		//�e�ӂ̒���

					//�R���X�g���N�^ : �f�t�H���g
	Rect2D() {}

	//�R���X�g���N�^ : �����l���w�肵�č쐬
	Rect2D(const Point2D &p, const Float2 &hl) : p(p), l(l) {}

	//�e�ӂ̒������擾
	float lenX() const { return l.x; }
	float lenY() const { return l.y; }
};

/*
	�O�p�`
*/
struct Triangle2D {
	Point2D p[3];	//���_���W

	//�R���X�g���N�^ : �f�t�H���g
	Triangle2D() {}

	//�f�X�X�g���N�^
	~Triangle2D() {}

	//�ӂ̒������擾
	float len(int i) const {
		//�_pi�̑Εӂ̒��� : ��i=0�@��p1p2�̒���
		return vec( i ).length();
	}

	//�Ӄx�N�g���̎擾
	Vec2 vec(int i) const {
		//�_pi�̑Εӂ̃x�N�g�� : ��i=0�@��p1p2�̃x�N�g��
		int v[] = { 1 , 2 , 0 , 1 };
		return p[v[i + 1]] - p[v[i]];
	}
};



#endif //PRIMITIVE2D_H