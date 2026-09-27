#include <stdio.h>

#define MAX 100

// Function to insert a value into the Max Heap
void insertMaxHeap(int heap[], int *size, int value) { 
    int i = (*size)++;
    heap[i] = value;
    
    while (i != 0 && heap[(i - 1) / 2] < heap[i]) { 
        int temp = heap[i];
        heap[i] = heap[(i - 1) / 2];
        heap[(i - 1) / 2] = temp;
        i = (i - 1) / 2;
    }
}

// Function to maintain the Max Heap property (Heapify downward)
void maxHeapify(int heap[], int size, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < size && heap[left] > heap[largest])
        largest = left;
        
    if (right < size && heap[right] > heap[largest])
        largest = right;
        
    if (largest != i) {
        int temp = heap[i];
        heap[i] = heap[largest];
        heap[largest] = temp;
        maxHeapify(heap, size, largest);
    }
}

// Function to delete the maximum element (root) from the heap
int deleteMax(int heap[], int *size) {
    int root;
    if (*size <= 0) { 
        printf("Heap is empty\n");
        return -1;
    }
    
    root = heap[0]; 
    heap[0] = heap[--(*size)];
    maxHeapify(heap, *size, 0);
    return root;
}

// Function to print the heap elements
void displayHeap(int heap[], int size) {
    for (int i = 0; i < size; i++)
        printf("%d ", heap[i]);
    printf("\n");
}

int main() {
    int heap[MAX];
    int size = 0;
    int choice, value;
    
    printf("Max Heap using Array\n");
    
    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert\n");
        printf("2. Delete Max (Root)\n");
        printf("3. Display Heap\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                insertMaxHeap(heap, &size, value);
                break;
                
            case 2:
                value = deleteMax(heap, &size);
                if (value != -1)
                    printf("Deleted max (root): %d\n", value);
                break;
                
            case 3:
                printf("Heap elements: ");
                displayHeap(heap, size);
                break;
                
            case 4:
                return 0;
                
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}