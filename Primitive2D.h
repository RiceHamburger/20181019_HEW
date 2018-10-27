/*====================================================================================

	基礎オブジェクトタイプ集　2D　 [primitive2D.h]
																Autor	: 西口
																Date	: 2018/06/24
--------------------------------------------------------------------------------------
コメント:
--------------------------------------------------------------------------------------
修正日時:
18/09/18 : Int2を追加。
====================================================================================*/


#ifndef PRIMITIVE2D_H
#define PRIMITIVE2D_H

/*--------------------------------------------------------------------------------------
	インクルードファイル
--------------------------------------------------------------------------------------*/
#include <math.h>
#include <d3dx9.h>

/*--------------------------------------------------------------------------------------
	定数定義
--------------------------------------------------------------------------------------*/
#define OX_EPSILON				(0.000001f)					//誤差

/*
	2成分int
*/
struct Int2{
	//２成分float
	float x, y;

	//コンストラクタ : デフォルト
	Int2() : x(0.0f) , y(0.0f){}

	//コンストラクタ : 2成分floatに初期値を代入して作成
	Int2( float x , float y) : x(x) , y(y){}

	//デスストラクタ
	~Int2(){}

	//演算子のオーバーロード
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
	//end演算子のオーバーロード

	//セット :  Int2 = float*2 
	Int2 Set(float nX, float nY) {
		x = nX;
		y = nY;
		return *this;
	}

};


/*
	2成分float
*/
struct Float2{
	//２成分float
	float x, y;

	//コンストラクタ : デフォルト
	Float2() : x(0.0f) , y(0.0f){}

	//コンストラクタ : 2成分floatに初期値を代入して作成
	Float2( float x , float y) : x(x) , y(y){}

	//デスストラクタ
	~Float2(){}

	//演算子のオーバーロード
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
	//end演算子のオーバーロード

	//演算子のオーバーロード D3DVECTOR2との互換性
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
	//end演算子のオーバーロード D3DVECTOR2との互換性

	//ゲット : D3DXVECTOR2への変換
	D3DXVECTOR2 toD3DXVECTOR2(void) {
		return D3DXVECTOR2(x, y);
	}

	//
	//　ツールメソッド
	//

	//セット :  Float2 = float*2 
	Float2 Set(float nX, float nY) {
		x = nX;
		y = nY;
		return *this;
	}


	//内積
	float dot(const Float2 &r) const {
		return x * r.x + y * r.y;
	}

	//外積
	float cross(const Float2 &r) const {
		return x * r.y - y * r.x;
	}

	//ベクトルとしてみた際の大きさ
	float length() const {
		return sqrtf(lengthSq());
	}

	//べき乗した大きさ
	float lengthSq() const {
		return x * x + y * y;
	}

	//正規化:元の値を更新
	void norm() {
		const float len = length();
		if (len > 0.0f) {
			x /= len;
			y /= len;
		}
	}

	//正規化:元の値は参照のみで正規化された値を取り出す
	Float2 getNorm() const {
		const float len = length();
		if (len > 0.0f) {
			return Float2(x / len, y / len);
		}
		return Float2(0.0f, 0.0f);
	}


};


/*
	点
*/
typedef Float2 Point2D;


/*
	ベクトル
*/
struct Vec2 : public Float2 
{
	//コンストラクタ : デフォルト
	Vec2() {};

	//コンストラクタ : 2成分からベクトルの作成
	Vec2(float x, float y) : Float2(x, y) {};

	//コンストラクタ : Float2型をベクトルに変換
	Vec2(const Float2 &r) : Float2(r) {};

	//デスストラクタ
	~Vec2() {};
	
	//＝演算子　オーバーロード
	Vec2& operator = (const Float2 &r) {
		x = r.x;
		y = r.y;

		return *this;
	}

	//正規化
	void norm() {
		const float len = length();
		if (len > 0.0f) {
			x /= len;
			y /= len;
		}
	}

	//垂直判定
	bool isVertical(const Vec2 &r) const {
		float d = dot(r);
		return (-OX_EPSILON < d && d < OX_EPSILON);		//誤差範囲内なら０として扱う
	}

	//平行判定
	bool isParallel(const Vec2 &r) const {
		float d = cross(r);
		return (-OX_EPSILON < d && d < OX_EPSILON);		//誤差範囲内なら０として扱う
	}

	//鋭角判定
	bool isSharpAngle(const Vec2 &r) const {
		return (dot(r) >= 0.0f);
	}

};

/*
	直線
*/
struct Line2D {
	Point2D p;		//始点
	Vec2 v;			//方向ベクトル

	//コンストラクタ : デフォルト
	Line2D() : p(0.0f, 0.0f), v(0.0f, 0.0f) {};

	//コンストラクタ : 点とベクトルから直線の作成
	Line2D(const Point2D &p, const Vec2 &v) : p(p), v(v) {};

	//点上の座標を取得する
	//ベクトルに掛け算する係数
	Point2D GetPoint(float t) const {
		return p + (v * t);
	}
};

/*
	線分:方向持ち
*/
struct Segment2D : public Line2D
{
	//コンストラクタ : デフォルト
	Segment2D() {};

	//コンストラクタ : 点とベクトルから線分の作成
	Segment2D(const Point2D &p, const Vec2 &v) : Line2D(p, v) {};

	//コンストラクタ : p1を始点、p2を終点として線分の作成
	Segment2D(const Point2D &p1, const Point2D &p2) : Line2D(p1, p2 - p1) {};

	//終点を取得
	Float2 GetEndPoint() const {
		return p + v;
	}
};

/*
	円２D
*/
struct Circle2D {
	Point2D p;		//中心点
	float r;		//半径

	//コンストラクタ : デフォルト
	Circle2D() : p(0.0f, 0.0f), r(0.5f) {}
	
	//コンストラクタ : 初期化値　代入
	Circle2D(const Point2D &p, float r) : p(p), r(r) {}

	//デスストラクタ
	~Circle2D() {}
};

/*
	カプセル
*/
struct Capsule2D {
	Segment2D s;	//線分
	float r;		//半径

	//コンストラクタ : デフォルト
	Capsule2D() : r(0.5f) {}

	//コンストラクタ : 線分と半径からカプセルの作成
	Capsule2D(const Segment2D &s, float r) : s(s), r(r) {}

	//コンストラクタ : p1を始点 , p2を終点とする線分と半径からカプセルの作成
	Capsule2D(const Point2D &p1, const Point2D &p2, float r) : s(p1, p2), r(r) {}

	//カプセルを四角形としてみた際の各辺の長さ(少し重いかも…)
	float lenX() { return s.v.length() + r * 2.0f; }
	float lenY() { return r * 2.0f; }

	//デスストラクタ
	~Capsule2D() {}
};

/*
	四角形 : 中心座標　+　各辺の1/2の値を持つタイプ(都合の悪い場合別途作成)
*/
struct RectC2D {
	Point2D p;		//中心点
	Float2 hl;		//各辺の長さの1/2

	//コンストラクタ : デフォルト
	RectC2D() {}

	//コンストラクタ : 初期値を指定して作成
	RectC2D(const Point2D &p, const Float2 &hl) : p(p), hl(hl) {}

	//各辺の長さを取得
	float lenX() const { return hl.x * 2.0f; }
	float lenY() const { return hl.y * 2.0f; }
};


/*
	四角形 : 左上頂点　+ 幅　+ 高さ
*/
struct Rect2D {
	Point2D p;		//左上頂点
	Float2 l;		//各辺の長さ

					//コンストラクタ : デフォルト
	Rect2D() {}

	//コンストラクタ : 初期値を指定して作成
	Rect2D(const Point2D &p, const Float2 &hl) : p(p), l(l) {}

	//各辺の長さを取得
	float lenX() const { return l.x; }
	float lenY() const { return l.y; }
};

/*
	三角形
*/
struct Triangle2D {
	Point2D p[3];	//頂点座標

	//コンストラクタ : デフォルト
	Triangle2D() {}

	//デスストラクタ
	~Triangle2D() {}

	//辺の長さを取得
	float len(int i) const {
		//点piの対辺の長さ : 例i=0　辺p1p2の長さ
		return vec( i ).length();
	}

	//辺ベクトルの取得
	Vec2 vec(int i) const {
		//点piの対辺のベクトル : 例i=0　辺p1p2のベクトル
		int v[] = { 1 , 2 , 0 , 1 };
		return p[v[i + 1]] - p[v[i]];
	}
};



#endif //PRIMITIVE2D_H