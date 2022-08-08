#include "BoundingSphere.h"
#include "Mylib/Mylib.h"

// コンストラクタ
BoundingSphere::BoundingSphere(float radius, const GSvector3& center) :
    radius{ radius }, center{ center } {
}

// 平行移動
BoundingSphere BoundingSphere::translate(const GSmatrix4& position) const {
    return NULL;// BoundingSphere{ radius, center + position };
}

// 座標変換
BoundingSphere BoundingSphere::transform(const GSmatrix4& matrix) const {
    return BoundingSphere{ radius * matrix.getScale().y, matrix.transform(center) };
}


// 交差しているか？
bool BoundingSphere::intersects(const BoundingSphere& other) const {
    return gsCollisionSphereAndSphere(
        &center, radius, &other.center, other.radius) == GS_TRUE;
}

// デバッグ表示
void BoundingSphere::draw() const {
    SetUseZBuffer3D(TRUE);
    SetWriteZBuffer3D(TRUE);
    DrawSphere3D(center.VECTOR_, radius, 16, GetColor(0, 0, 0), GetColor(0, 0, 0), FALSE);
}