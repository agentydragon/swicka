#include "ohlc_provider.h"

bool OHLCProvider::isEmpty() {
	for (QDateTime i = getMinimum(); i <= getMaximum(); i = getInterval()->firstAfter(i)) {
		OHLC data;
		if (tryGetData(i, data)) {
			return false;
		}
	}
	return true;
}
