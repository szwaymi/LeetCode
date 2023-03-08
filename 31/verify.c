void rQuickSort(int *piValues, unsigned int iSize) {
	unsigned int iLeft;
	unsigned int iRight;
	iLeft = 0;
	iRight = iSize;

	do {
		do {
			iRight--;
		} while (piValues[0] <= piValues[iRight] && iLeft < iRight);
		do {
			iLeft++;
		} while (piValues[0] > piValues[iLeft] && iLeft < iRight);
		if (iLeft < iRight) {
			unsigned int iTemp;
			iTemp = piValues[iLeft];
			piValues[iLeft] = piValues[iRight];
			piValues[iRight] = iTemp;
		}
	} while (iLeft < iRight);

	unsigned int iTemp;
	iTemp = piValues[0];
	piValues[0] = piValues[iRight];
	piValues[iRight] = iTemp;

	if (iRight > 1) {
		rQuickSort(&piValues[0], iRight);
	}
	if (iSize - iRight - 1 > 1) {
		rQuickSort(&piValues[iRight + 1], iSize - iRight - 1);
	}
	return;
}

void rVRF_NextPermutation(int* piSeries, int iLength) {

	unsigned int iConTarget;
	unsigned int iConSearch;
	unsigned int iLocMin = 0xFFFFFFFF;
	unsigned int iLocTarget;
	for (iConTarget = 1; iConTarget < iLength; iConTarget++) {
		iLocTarget = iLength - 1 - iConTarget;
		int iMin = 0x7FFFFFFF;
		for (iConSearch = iLocTarget + 1; iConSearch < iLength; iConSearch++) {
			if (piSeries[iLocTarget] < piSeries[iConSearch]) {
				if (piSeries[iConSearch] < iMin) {
					iLocMin = iConSearch;
				}
			}
		}
		if (iLocMin != 0xFFFFFFFF) {
			break;
		}
	}
	if (iLocMin == 0xFFFFFFFF) {
		for (iConSearch = 0; iConSearch < iLength / 2; iConSearch++) {
			unsigned int iTemp;
			iTemp = piSeries[iConSearch];
			piSeries[iConSearch] = piSeries[iLength - iConSearch - 1];
			piSeries[iLength - iConSearch - 1] = iTemp;

		}
	}
	else {
		int iTemp;
		iTemp = piSeries[iLocTarget];
		piSeries[iLocTarget] = piSeries[iLocMin];
		piSeries[iLocMin] = iTemp;
		unsigned int iSizeSort = iLength - iLocTarget - 1;
		if (iSizeSort > 1) {
			rQuickSort(&piSeries[iLocTarget + 1], iLength - iLocTarget - 1);
		}
	}
}