#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>

int getrand(int min, int max)
{
	return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

double wtime()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

void swap(int *a, int *b) {
        int temp = *a;
        *a = *b;
        *b = temp;
}

void countingSort(int mass[], int n)
{
   	int k;
	for (int i = 0; i < n; i++)
	{
		k = 0;
        	for (int j = 0; j < n; j++)
        	{
            		if (mass[i] > mass[j])
                	k++;
        	}
		swap(&mass[k], &mass[i]);
	}
}
void bubbleSort(int mass[], int n)
{
	int tmp;
	int noSwap;
	for (int i = n - 1; i >= 0; i--)
	{
    		noSwap = 1;
    		for (int j = 0; j < i; j++)
    		{
        		if (mass[j] > mass[j + 1])
			{
				tmp = mass[j];
        			mass[j] = mass[j + 1];
   	        		mass[j + 1] = tmp;
        			noSwap = 0;
        		}
    		}
    		if (noSwap == 1)
        		break;
	}
}

void heapify(int arr[], int n, int i) {
	// Find largest among root, left child and right child
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < n && arr[left] > arr[largest])
		largest = left;

	if (right < n && arr[right] > arr[largest])
		largest = right;

	// Swap and continue heapifying if root is not largest
	if (largest != i) {
		swap(&arr[i], &arr[largest]);
		heapify(arr, n, largest);
	}
}

// Main function to do heap sort
void heapSort(int arr[], int n) {
	// Build max heap
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	// Heap sort
	for (int i = n - 1; i >= 0; i--) {
		swap(&arr[0], &arr[i]);

		// Heapify root element to get highest element at root again
		heapify(arr, i, 0);
	}
}

// Print an array
void printArray(int arr[], int n) {
	for (int i = 0; i < n; ++i)
		printf("%d ", arr[i]);
	printf("\n");
}
void arrReload(int *arr, int *arr_1, int n)
{
	for(int i = 0; i < n; i++)
        {
                arr_1[i] = arr[i];
        }
}
// Driver code
int main() {
	double t;
	for(int n = 100000; n <= 1000000; n += 50000)
	{
		printf("n = %d\n", n);
		int arr[n];
		for(int i = 0; i < n; i++)
		{
			arr[i] = getrand(0, 100000);
		}
		int arr_1[n];
		arrReload(arr, arr_1, n);
		t = wtime();
	 	heapSort(arr_1, n);
	        printf("heap sort - %lf\n", (wtime() - t));
	        arrReload(arr, arr_1, n);
	        t = wtime();
	        bubbleSort(arr_1, n);
		printf("bubble sort - %lf\n", (wtime() - t));
	        arrReload(arr, arr_1, n);
	        t = wtime();
	        countingSort(arr_1, n);
	        printf("counting sort - %lf\n", (wtime() - t));
	}
}
