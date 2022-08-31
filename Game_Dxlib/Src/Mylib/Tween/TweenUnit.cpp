#include "TweenUnit.h"
#include <algorithm>

TweenUnit::TweenUnit(float duration) : duration_{ duration } { }

void TweenUnit::update(float delta_time) {
    // delayが設定されていたら、それが無くなるまで何もせず待機
    if (delay_ > 0) {
        delay_ -= delta_time;
        // 待機しすぎた分は経過時間として計上
        if (delay_ < 0) {
            elapsed_ = -delay_;
        }
        return;
    }

    // 経過時間を進める
    elapsed_ += delta_time;
    // 進捗率（0～1）を計算
    float progress = elapsed_ / duration_;
    // 進捗率が1を超えないようにする
    progress = std::min(progress, 1.0f);
    // 進捗率にイージングを適用する
    float eased = apply_ease(progress, ease_type_, overshoot_);
    // イージングを適用した進捗率を使い、派生クラスごとの更新処理を行う
    on_update(eased);
    // 終了したかを判定する
    is_finished_ = progress >= 1.0f;

    // 終了していて、かつ、完了時コールバックが設定されている場合は、それを実行する
    if (is_finished_ && complete_func_) {
        complete_func_();
    }
}

bool TweenUnit::is_finished() const {
    return is_finished_;
}

TweenUnit& TweenUnit::ease(EaseType ease_type) {
    ease_type_ = ease_type;
    return *this;
}

TweenUnit& TweenUnit::overshoot(float overshoot) {
    overshoot_ = overshoot;
    return *this;
}

TweenUnit& TweenUnit::delay(float delay) {
    delay_ = delay;
    return *this;
}

TweenUnit& TweenUnit::on_complete(std::function<void()> complete_func) {
    complete_func_ = complete_func;
    return *this;
}

const std::string& TweenUnit::name() const {
    return name_;
}

TweenUnit& TweenUnit::name(const std::string& name) {
    name_ = name;
    return *this;
}

float TweenUnit::apply_ease(float value, EaseType ease_type, float overshoot) {
    switch (ease_type) {
    case EaseType::Linear:         return value;
    case EaseType::EaseInBack:     return GSeasing::gsEasingInBack(value, overshoot);
    case EaseType::EaseInCirc:     return GSeasing::gsEasingInCirc(value);
    case EaseType::EaseInCubic:    return GSeasing::gsEasingInCubic(value);
    case EaseType::EaseInExpo:     return GSeasing::gsEasingInExpo(value);
    case EaseType::EaseInQuad:     return GSeasing::gsEasingInQuad(value);
    case EaseType::EaseInQuart:    return GSeasing::gsEasingInQuart(value);
    case EaseType::EaseInQuint:    return GSeasing::gsEasingInQuint(value);
    case EaseType::EaseInSine:     return GSeasing::gsEasingInSine(value);
    case EaseType::EaseOutBack:    return GSeasing::gsEasingOutBack(value, overshoot);
    case EaseType::EaseOutBounce:  return GSeasing::gsEasingOutBounce(value);
    case EaseType::EaseOutCirc:    return GSeasing::gsEasingOutCirc(value);
    case EaseType::EaseOutCubic:   return GSeasing::gsEasingOutCubic(value);
    case EaseType::EaseOutElastic: {
        if (value == 1.0f) return 1.0f;
        return 1.0f - cosf(value * 10.0f * overshoot) * powf(1.0f - value, 3.0f);
    }
    case EaseType::EaseOutExpo:    return GSeasing::gsEasingOutExpo(value);
    case EaseType::EaseOutQuad:    return GSeasing::gsEasingOutQuad(value);
    case EaseType::EaseOutQuart:   return GSeasing::gsEasingOutQuart(value);
    case EaseType::EaseOutQuint:   return GSeasing::gsEasingOutQuint(value);
    case EaseType::EaseOutSine:    return GSeasing::gsEasingOutSine(value);
    case EaseType::EaseInOutBack:  return GSeasing::gsEasingInOutBack(value, overshoot);
    case EaseType::EaseInOutCirc:  return GSeasing::gsEasingInOutCirc(value);
    case EaseType::EaseInOutCubic: return GSeasing::gsEasingInOutCubic(value);
    case EaseType::EaseInOutExpo:  return GSeasing::gsEasingInOutExpo(value);;
    case EaseType::EaseInOutQuad:  return GSeasing::gsEasingInOutQuad(value);
    case EaseType::EaseInOutQuart: return GSeasing::gsEasingInOutQuart(value);
    case EaseType::EaseInOutQuint: return GSeasing::gsEasingInOutQuint(value);
    case EaseType::EaseInOutSine:  return GSeasing::gsEasingInOutSine(value);
    case EaseType::Punch: {
        if (value == 0 || value == 1) return 0;
        float peek = 0.25f / overshoot;
        float a = (value - 1.0f) / (peek - 1.0f);
        a = CLAMP(a, 0.0f, 1.0f);
        float b = a * a * (3 - 2 * a);
        return sin(value * 6.28318530f * overshoot) * b;
    }
    default: return value;
    }
}