using namespace std;

// A utility function to swap two elements 
void swap(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

void heapSort(int arr[], int n)
{
	// Build heap (rearrange array)
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	// One by one extract an element from heap
	for (int i = n - 1; i >= 0; i--)
	{
		// Move current root to end
		swap(&arr[0], &arr[i]); // TODO: check if this works

		// call max heapify on the reduced heap
		heapify(arr, i, 0);
	}
}

void heapify(int arr[], int n, int i)
{
	int largest = i; // Initialize largest as root
	int l = 2 * i + 1; // left = 2*i + 1
	int r = 2 * i + 2; // right = 2*i + 2

	if (l < n && arr[l] > arr[largest])
		largest = l;
	if (r < n && arr[r] > arr[largest])
		largest = r;
	if (largest != i)
	{
		swap(&arr[i], &arr[largest]); // TODO: check if this works

		// Recursively heapify the affected sub-tree
		heapify(arr, n, largest);
	}
}