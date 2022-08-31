#include "GSeasing.h"

float GSeasing::gsEasingInBack(float t, float s)
{
	return t * t * ((s + 1) * t - s);
}

float GSeasing::gsEasingInBounce(float t)
{
	t = 1.0f - t;
	if (t < 1.0f / 2.75f) {
		return 1.0f - (7.5625f * t * t);
	}
	if (t < 2.0f / 2.75f) {
		t -= 1.5f / 2.75f;
		return 1.0f - (7.5625f * t * t + 0.75f);
	}
	if (t < 2.5f / 2.75f) {
		t -= 2.25f / 2.75f;
		return 1.0f - (7.5625f * t * t + 0.9375f);
	}
	t -= 2.625f / 2.75f;
	return 1.0f - (7.5625f * t * t + 0.984375f);
}

float GSeasing::gsEasingInCirc(float t)
{
	return -(std::sqrt(1.0f - t * t) - 1.0f);
}

float GSeasing::gsEasingInCubic(float t)
{
	return t * t * t;
}

float GSeasing::gsEasingInElastic(float t, float s)
{
	return t <= 0.0f
		? 0.0f
		: t >= 1.0f
		? 1.0f
		: -powf(2.0f, 10.0f * t - 10.0f) * sinf((t * 10.0f - 10.75f) * s);
}

float GSeasing::gsEasingInExpo(float t)
{
	return (t <= 0.0) ? 0.0f : std::pow(2.0f, 10.0f * (t - 1.0f));
}

float GSeasing::gsEasingInQuad(float t)
{
	return t * t;
}

float GSeasing::gsEasingInQuart(float t)
{
	return t * t * t * t;
}

float GSeasing::gsEasingInQuint(float t)
{
	return t * t * t * t * t;
}

float GSeasing::gsEasingInSine(float t)
{
	return -std::cos(t * (3.14159265359f / 2.0f)) + 1.0f;
}

float GSeasing::gsEasingOutBack(float t, float s)
{
	t -= 1.0f;
	return t * t * ((s + 1.0f) * t + s) + 1.0f;
}

float GSeasing::gsEasingOutBounce(float t)
{
	if (t < 1.0f / 2.75f) {
		return 7.5625f * t * t;
	}
	if (t < 2.0f / 2.75f) {
		t -= 1.5f / 2.75f;
		return 7.5625f * t * t + 0.75f;
	}
	if (t < 2.5f / 2.75f) {
		t -= 2.25f / 2.75f;
		return 7.5625f * t * t + 0.9375f;
	}
	t -= 2.625f / 2.75f;
	return 7.5625f * t * t + 0.984375f;
}

float GSeasing::gsEasingOutCirc(float t)
{
	t -= 1.0f;
	return std::sqrt(1.0f - t * t);
}

float GSeasing::gsEasingOutCubic(float t)
{
	t -= 1.0f;
	return t * t * t + 1.0f;
}

float GSeasing::gsEasingOutElastic(float t, float s)
{
	return t <= 0.0f
		? 0.0f
		: t >= 1.0f
		? 1.0f
		: std::pow(2.0f, -10.0f * t) * std::sin((t * 10.0f - 0.75f) * s) + 1.0f;
}

float GSeasing::gsEasingOutExpo(float t)
{
	return (t >= 1.0f) ? 1.0f : (-std::pow(2.0f, -10.0f * t) + 1.0f);
}

float GSeasing::gsEasingOutQuad(float t)
{
	return -t * (t - 2.0f);
}

float GSeasing::gsEasingOutQuart(float t)
{
	t -= 1.0f;
	return 1.0f - t * t * t * t;
}

float GSeasing::gsEasingOutQuint(float t)
{
	t -= 1.0f;
	return t * t * t * t * t + 1.0f;
}

float GSeasing::gsEasingOutSine(float t)
{
	return std::sin(t * (3.14159265359f / 2.0f));
}

float GSeasing::gsEasingInOutBack(float t, float s)
{
	float k = 1.525f;
	t *= 2.0f;
	s *= k;
	if (t < 1.0f) {
		return 0.5f * (t * t * ((s + 1) * t - s));
	}
	t -= 2.0f;
	return 0.5f * (t * t * ((s + 1) * t + s) + 2.0f);
}

float GSeasing::gsEasingInOutBounce(float t)
{
	return (t < 0.5f)
		? (gsEasingInBounce(t * 2.0f) * 0.5f)
		: (gsEasingOutBounce(t * 2.0f - 1.0f) * 0.5f + 0.5f);
}

float GSeasing::gsEasingInOutCirc(float t)
{
	t *= 2.0f;
	if (t < 1.0f) {
		return -0.5f * (std::sqrt(1.0f - t * t) - 1.0f);
	}
	t -= 2.0f;
	return 0.5f * (std::sqrt(1.0f - t * t) + 1.0f);
}

float GSeasing::gsEasingInOutCubic(float t)
{
	t *= 2.0f;
	if (t < 1.0f) {
		return 0.5f * t * t * t;
	}
	t -= 2.0f;
	return 0.5f * (t * t * t + 2.0f);
}

float GSeasing::gsEasingInOutElastic(float t, float s)
{
	return t <= 0.0f
		? 0.0f
		: t >= 1.0f
		? 1.0f
		: t < 0.5f
		? -(std::pow(2.0f, 20.0f * t - 10.0f) * std::sin((20.0f * t - 11.125f) * s)) / 2.0f
		: (std::pow(2.0f, -20.0f * t + 10.0f) * std::sin((20.0f * t - 11.125f) * s)) / 2.0f + 1.0f;
}

float GSeasing::gsEasingInOutExpo(float t)
{
	if (t == 0.0f) {
		return 0.0f;
	}
	if (t == 1.0f) {
		return 1.0f;
	}
	t *= 2.0f;
	if (t < 1.0f) {
		return 0.5f * std::pow(2.0f, 10.0f * (t - 1.0f));
	}
	t -= 1.0f;
	return 0.5f * (-std::pow(2.0f, -10.0f * t) + 2.0f);
}

float GSeasing::gsEasingInOutQuad(float t)
{
	t *= 2.0f;
	if (t < 1.0f) {
		return 0.5f * t * t;
	}
	t -= 1.0f;
	return -0.5f * (t * (t - 2.0f) - 1.0f);
}

float GSeasing::gsEasingInOutQuart(float t)
{
	t *= 2.0f;
	if (t < 1.0f) {
		return 0.5f * t * t * t * t;
	}
	t -= 2.0f;
	return -0.5f * (t * t * t * t - 2.0f);
}

float GSeasing::gsEasingInOutQuint(float t)
{
	t *= 2.0f;
	if (t < 1.0f) {
		return 0.5f * t * t * t * t * t;
	}
	t -= 2.0f;
	return 0.5f * (t * t * t * t * t + 2.0f);
}

float GSeasing::gsEasingInOutSine(float t)
{
	return -0.5f * (std::cos(3.14159265359f * t) - 1.0f);
}