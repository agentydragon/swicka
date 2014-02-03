#include "ohlc_provider.h"

bool OHLCProvider::isEmpty() {
	for (QDateTime i = getMinimum(); i <= getMaximum(); i = i.addSecs(getQuantumSeconds())) {
		OHLC data;
		if (tryGetData(i, data)) {
			return false;
		}
	}
	return true;
}
