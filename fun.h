#include "TryOneConsts.h"
int Abou(double x) {
	int y = x;
	if (x >= 0)
		if (x - y < 0.5)
			return y;
		else
			return (y + 1);
	else
		if (x - y < -0.5)
			return (y - 1);
		else
			return y;
}
