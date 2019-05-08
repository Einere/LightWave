#include "stdafx.h"
#include "CoordConverter.h"

namespace CoordConverter {
	const static projPJ projTM = pj_init_plus("+proj=tmerc +lat_0=38 +lon_0=127.0028902777778 +k=1 +x_0=200000 +y_0=500000 +ellps=bessel +units=m +no_defs +towgs84=-115.80,474.99,674.11,1.16,-2.31,-1.63,6.43");
	const static projPJ projWGS84 = pj_init_plus("+proj=longlat +ellps=WGS84 +datum=WGS84 +no_defs");

	void TMtoWGS84(double* x, double* y) {
		pj_transform(projTM, projWGS84, 1, 1, x, y, NULL);
		*x /= DEG_TO_RAD;
		*y /= DEG_TO_RAD;
	}
}
