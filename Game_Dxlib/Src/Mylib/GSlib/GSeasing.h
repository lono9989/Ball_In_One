/*
* Robert Penner's easing functions.
*
* See the following to learn more about these famous functions:
* http://www.robertpenner.com/easing/
*
* License:
* http://www.robertpenner.com/easing_terms_of_use.html
*/
#ifndef GS_EASING_H_
#define GS_EASING_H_

#include <cmath>

class GSeasing {
public:
	static float gsEasingInBack(float t, float s = 1.70158f);
	static float gsEasingInBounce(float t);
	static float gsEasingInCirc(float t);
	static float gsEasingInCubic(float t);
	static float gsEasingInElastic(float t, float s = 2.094395102f);
	static float gsEasingInExpo(float t);
	static float gsEasingInQuad(float t);
	static float gsEasingInQuart(float t);
	static float gsEasingInQuint(float t);
	static float gsEasingInSine(float t);
	static float gsEasingOutBack(float t, float s = 1.70158f);
	static float gsEasingOutBounce(float t);
	static float gsEasingOutCirc(float t);
	static float gsEasingOutCubic(float t);
	static float gsEasingOutElastic(float t, float s = 2.094395102f);
	static float gsEasingOutExpo(float t);
	static float gsEasingOutQuad(float t);
	static float gsEasingOutQuart(float t);
	static float gsEasingOutQuint(float t);
	static float gsEasingOutSine(float t);
	static float gsEasingInOutBack(float t, float s = 1.70158f);
	static float gsEasingInOutBounce(float t);
	static float gsEasingInOutCirc(float t);
	static float gsEasingInOutCubic(float t);
	static float gsEasingInOutElastic(float t, float s = 1.396263402f);
	static float gsEasingInOutExpo(float t);
	static float gsEasingInOutQuad(float t);
	static float gsEasingInOutQuart(float t);
	static float gsEasingInOutQuint(float t);
	static float gsEasingInOutSine(float t);
};
#endif