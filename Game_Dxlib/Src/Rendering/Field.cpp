#include "Field.h"
#include "Assets.h"

const float FieldSize{ 150.0f };

Field::Field(int model) :field_Model{ model }, scroll_{ 0.0f }{
	
	
	MV1SetupCollInfo(model, -1, 64, 64, 64);
}

Field::~Field()
{
	MV1TerminateCollInfo(field_Model);
}

void Field::update(float delta_time) {
}

void Field::draw()const {
	//SetUseLighting(FALSE);
	//MV1SetUseOrigShader(TRUE);
	//SetUseVertexShader(Assets::VShader_Normal);
	//SetUsePixelShader(Assets::PShader_Normal);
	MV1SetPosition(field_Model, VECTOR{ 0.0f,0.0f,0.0f });
	MV1DrawModel(field_Model);
	//MV1SetUseOrigShader(FALSE);
	//SetUseLighting(TRUE);
}

void Field::draw_shadow() const
{
	MV1DrawModel(field_Model);
}

bool Field::collide(const Line& line, MV1_COLL_RESULT_POLY* result) const
{
	*result =
		MV1CollCheck_Line(field_Model, -1, line.start.VECTOR_, line.end.VECTOR_);
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
	*result =
		MV1CollCheck_Sphere(field_Model, -1, sphere.center.VECTOR_, sphere.radius);

	// 座標を求める
	GSvector3 position = sphere.center;
	GSvector3 target;

	GSvector3 v = GSvector3{ 0.0f,0.0f,0.0f };
	for (int i = 0; i < result->HitNum; ++i) {
		MV1_COLL_RESULT_POLY pol = MV1CollCheck_GetResultPoly(*result, i);

		target.VECTOR_ = pol.HitPosition;
		// 相手との距離
		float distance = GSvector3::distance(position, target);

		// 衝突判定球の重なっている長さを求める
		float overlap = sphere.radius - distance;

		// 重なっている部分の距離だけ離れる移動量を求める
		v += (position - target).getNormalized() * overlap*0.7f;
	}
	position += v;
	*intersect = position;
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

