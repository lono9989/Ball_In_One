#ifndef FIELD_H_
#define FIELD_H_

#include<DxLib.h>
#include"Mylib/Mylib.h"
#include "Collision/Line.h"
#include "Collision/Ray.h"
#include "Collision/BoundingSphere.h"

class Field {
public:
	//�R���X�g���N�^
	Field(int model);
	//�f�X�g���N�^
	~Field();
	//�X�V
	void update(float delta_time);
	//�`��
	void draw() const;
	void draw_shadow()const;
	// �����Ƃ̏Փ˔���
	bool collide(const Line& line, MV1_COLL_RESULT_POLY* result) const;
	// ���C�Ƃ̏Փ˔���
	bool collide(const Ray& ray, float max_distance, MV1_COLL_RESULT_POLY* result) const;
	// ���̂Ƃ̏Փ˔���
	bool collide(const BoundingSphere& sphere, MV1_COLL_RESULT_POLY_DIM* result,GSvector3* intersect) const;
	//�t�B�[���h����
	bool is_inside(const GSvector3& position) const;
	//�t�B�[���h�O��
	bool is_outside(const GSvector3& posiition) const;


	//�R�s�[�֎~
	Field(const Field& other) = default;
	Field& operator=(const Field& other) = default;

private:
	//�w�i�摜
	GSuint bg_{ 0 };
	//�X�N���[���ʒu
	float scroll_{ 0.0f };
	int field_Model{ -1 };
};

#endif;

