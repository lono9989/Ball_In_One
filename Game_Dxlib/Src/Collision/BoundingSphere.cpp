#include "BoundingSphere.h"
#include "Mylib/Mylib.h"

// �R���X�g���N�^
BoundingSphere::BoundingSphere(float radius, const GSvector3& center) :
    radius{ radius }, center{ center } {
}

// ���s�ړ�
BoundingSphere BoundingSphere::translate(const GSmatrix4& position) const {
    return NULL;// BoundingSphere{ radius, center + position };
}

// ���W�ϊ�
BoundingSphere BoundingSphere::transform(const GSmatrix4& matrix) const {
    return BoundingSphere{ radius * matrix.getScale().y, matrix.transform(center) };
}


// �������Ă��邩�H
bool BoundingSphere::intersects(const BoundingSphere& other) const {
    return gsCollisionSphereAndSphere(
        &center, radius, &other.center, other.radius) == GS_TRUE;
}

// �f�o�b�O�\��
void BoundingSphere::draw() const {
    SetUseZBuffer3D(TRUE);
    SetWriteZBuffer3D(TRUE);
    DrawSphere3D(center.VECTOR_, radius, 16, GetColor(0, 0, 0), GetColor(0, 0, 0), FALSE);
}