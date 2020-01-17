#include "math/functions/easing/elastic-easing-function.h"
#include "math/interval.h"
#include <assert.h>
# define M_PI           3.14159265358979323846  /* pi */

using namespace math;
using namespace math::functions;

EasingFunction math::functions::easing::elastic(int b, int a) {

	std::function<double(double)> lambda = [a, b](double t) {
		assert(interval(0.0, 1.0).contains(t));
		if (a == 0) {
			return 1 - pow(2, -1 / 0.5 * t) * cos(t * M_PI * b/3);
		}
		else {
			return 1 - pow(2, -1 / a * t) * cos(t * M_PI * b/3);
		}
	};

	return from_lambda(lambda);
}