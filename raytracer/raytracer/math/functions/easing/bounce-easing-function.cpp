#include "math/functions/easing/bounce-easing-function.h"
#include "math/interval.h"
#include <assert.h>
# define M_PI           3.14159265358979323846  /* pi */

using namespace math;
using namespace math::functions;

EasingFunction math::functions::easing::bounce(int b, int a) {
	
	std::function<double(double)> lambda = [a,b](double t) {
		assert(interval(0.0, 1.0).contains(t));

		//deze is ook nice maar nie echt een bounce
		//mss nice voor elastic	
		//return 1 - pow(2, -1 / a*3 * t) * abs(cos(t * 2*M_PI * b));
		return -exp(-(a) * t) * abs(cos(b * M_PI * t)) + 1;
		
		
	};

	return from_lambda(lambda);
}