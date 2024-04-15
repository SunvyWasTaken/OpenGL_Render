#include "MathUtility.h"

namespace Utility
{
	int NextPowerTwo(const int nbr)
	{
		int tmp = 1;

		if (nbr == 1)
			return 2;

		while (tmp < nbr)
			tmp *= 2;

		return tmp;
	}
}
