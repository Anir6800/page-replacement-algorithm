#include <stdio.h>
int findIndex(int pages[], int n, int start) {
    int res = -1, farthest = start;
    for (int i = 0; i < n; i++) {
        int j;
        for (j = start; j >= 0; j--) {
            if (pages[i] == pages[j]) {
                break;
            }
        }
        if (j == -1) {
            return i;
        }
        if (j < farthest) {
            farthest = j;
            res = i;
        }
    }
    return (res == -1) ? 0 : res;
}

void fifo(int pages[], int n, int capacity) {
    int page_faults = 0;
    int queue[capacity];
    int front = 0, rear = 0;

    for (int i = 0; i < n; i++) {
        int flag = 0;
        for (int j = 0; j < capacity; j++) {
            if (queue[j] == pages[i]) {
                flag = 1;
                break;
            }
        }

        if (!flag) {
            if ((rear + 1) % capacity == front) {
                printf("Page %d is replaced.\n", queue[front]);
                front = (front + 1) % capacity;
            }

            queue[rear] = pages[i];
            rear = (rear + 1) % capacity;
            page_faults++;
        }
    }

    printf("Total Page Faults: %d\n", page_faults);
}

void optimal(int pages[], int n, int capacity) {
    int page_faults = 0;
    int queue[capacity];

    for (int i = 0; i < n; i++) {
        int flag = 0;
        for (int j = 0; j < capacity; j++) {
            if (queue[j] == pages[i]) {
                flag = 1;
                break;
            }
        }

        if (!flag) {
            if (i >= capacity) {
                int replaceIndex = findIndex(pages, i, i - capacity);
                printf("Page %d is replaced.\n", queue[replaceIndex]);
                queue[replaceIndex] = pages[i];
            } else {
                queue[i] = pages[i];
            }

            page_faults++;
        }
    }

    printf("Total Page Faults: %d\n", page_faults);
}

void lru(int pages[], int n, int capacity) {
    int page_faults = 0;
    int queue[capacity];

    for (int i = 0; i < n; i++) {
        int flag = 0;
        for (int j = 0; j < capacity; j++) {
            if (queue[j] == pages[i]) {
                flag = 1;
                break;
            }
        }

        if (!flag) {
            if (i >= capacity) {
                int replaceIndex = findIndex(pages, i, i - 1);
                printf("Page %d is replaced.\n", queue[replaceIndex]);
                queue[replaceIndex] = pages[i];
            } else {
                queue[i] = pages[i];
            }

            page_faults++;
        }
    }

    printf("Total Page Faults: %d\n", page_faults);
}

int main() {
    int n, capacity;

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int pages[n];

    printf("Enter the page reference sequence:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the capacity of the memory: ");
    scanf("%d", &capacity);

    printf("\nFIFO Page Replacement Algorithm:\n");
    fifo(pages, n, capacity);

    printf("\nOptimal Page Replacement Algorithm:\n");
    optimal(pages, n, capacity);

    printf("\nLRU Page Replacement Algorithm:\n");
    lru(pages, n, capacity);

    return 0;
}
