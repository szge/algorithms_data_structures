#pragma once

namespace alg {
	template <typename T>

	/* Perform bubble sort on array <arr> starting from <start> until <end>
	@param arr the array to be sorted
	@param start the starting index of the subarray to be sorted
	@param end the ending index of the subarray to be sorted

	Notes: mutates arr;
	start and end are passed because there is no elegant way
	to obtain the number of elements in the array
	*/
	static void BubbleSort(T arr[], int start, int end) {
		bool swapped = true; // something has been swapped so keep sorting
		T temp;

		while (swapped) {
			swapped = false;
			for (int i = start; i < end; i++) {
				if (arr[i] > arr[i + 1]) {
					//swap elements
					temp = arr[i];
					arr[i] = arr[i + 1];
					arr[i + 1] = temp;
					swapped = true;
				}
			}

			// we know that the last element is sorted so we can skip it
			end--;
		}
	}
}