#include "Field.h"
#include "Assets.h"

const float FieldSize{ 150.0f };

Field::Field() : scroll_{ 0.0f }{
	MV1SetupCollInfo(Assets::Mesh_Field, -1, 64, 64, 64);
}

Field::~Field()
{
	MV1TerminateCollInfo(Assets::Mesh_Field);
}

void Field::update(float delta_time) {
}

void Field::draw()const {
	//SetUseLighting(FALSE);
	//MV1SetUseOrigShader(TRUE);
	//SetUseVertexShader(Assets::VShader_Normal);
	//SetUsePixelShader(Assets::PShader_Normal);
	MV1SetPosition(Assets::Mesh_Field, VECTOR{ 0.0f,0.0f,0.0f });
	MV1DrawModel(Assets::Mesh_Field);
	//MV1SetUseOrigShader(FALSE);
	//SetUseLighting(TRUE);
}

void Field::draw_shadow() const
{
	MV1DrawModel(Assets::Mesh_Field);
}

bool Field::collide(const Line& line, MV1_COLL_RESULT_POLY* result) const
{
	*result =
		MV1CollCheck_Line(Assets::Mesh_Field, -1, line.start.VECTOR_, line.end.VECTOR_);
	return result->HitFlag;

}

bool Field::collide(const Ray& ray, float max_distance, MV1_COLL_RESULT_POLY* result) const
{
	Line line{
		 ray.position,
		 ray.position + (ray.direction.normalized() * max_distance) };
	return collide(line, result);
}

bool Field::collide(const BoundingSphere& sphere, MV1_COLL_RESULT_POLY_DIM* result, GSvector3* intersect) const
{
	bool isend_{ false };
	*result = MV1CollCheck_Sphere(Assets::Mesh_Field, -1, sphere.center.VECTOR_, sphere.radius);
	if (intersect != nullptr) {

	// 座標を求める
	GSvector3 position = sphere.center;

	Col(result, &position, sphere.radius);
	while (!isend_) {

		MV1_COLL_RESULT_POLY_DIM a;
		a = MV1CollCheck_Sphere(Assets::Mesh_Field, -1, position.VECTOR_, sphere.radius);
		if (a.HitNum > 0)
		{
			Col(&a, &position, sphere.radius);
			
		}
		else isend_ = true;
		MV1CollResultPolyDimTerminate(a);
	}
	*intersect = position;
	}
	// フィールドとの衝突判定
	return result->HitNum > 0;
}

bool Field::is_inside(const GSvector3& position)const {
	if (ABS(position.x) >= FieldSize)return false;
	if (ABS(position.y) >= FieldSize)return false;
	return true;
}

bool Field::is_outside(const GSvector3& position)const {
	return !is_inside(position);
}

void Field::Col(MV1_COLL_RESULT_POLY_DIM* a, GSvector3* position, float radius) const
{
	GSvector3 target;
	for (int i = 0; i < a->HitNum; ++i) {
		MV1_COLL_RESULT_POLY pol = MV1CollCheck_GetResultPoly(*a, i);
		VECTOR v = Get_Triangle_Point_MinPosition(position->VECTOR_, pol.Position[0], pol.Position[1], pol.Position[2]);
		position->VECTOR_ = VAdd(v, VScale(VNorm(VSub(position->VECTOR_, v)), radius * 1.01f));
	}
}

