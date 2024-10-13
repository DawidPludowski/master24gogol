
#include<stdio.h>

void insertsort(int arr[], int size) {

    double min;
    int min_idx;
    double temp;

    for (int i = 0; i < size; i++) {
        min = arr[i];
        min_idx = i;
        for (int j = i+1; j < size; j++) {
            if (arr[j] < min) {
                min = arr[j];
                min_idx = j;
            }
        }
        if (min_idx != i) {
            temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
        }
    }
}

int main() {

    int list[] = { 6, 3, 9, 2, 1, 0, 10, 4, 8, 7 };
    int size = sizeof(list) / sizeof(list[0]);

    insertsort(list, size);

    for (int i = 0; i < size; i++) {
        printf("%d, ", list[i]);
    }
    printf("\n");

}