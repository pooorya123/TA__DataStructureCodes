/////////Poorya Razavi 4001406916/////


#include <iostream>
#include <climits>
using namespace std;

// تعریف کلاس برای نمایش یک Min Heap
class MinHeap {
    int* heapArray; // آرایه برای نگهداری عناصر هیپ
    int capacity;   // حداکثر ظرفیت هیپ
    int heapSize;   // اندازه فعلی هیپ

public:
    // سازنده با ظرفیت مشخص
    MinHeap(int cap);

    // تابعهای کمکی
    void heapify(int);
    int parent(int i) { return (i - 1) / 2; } // پدر یک عنصر
    int left(int i) { return (2 * i + 1); } // چپین یک عنصر
    int right(int i) { return (2 * i + 2); } // راستین یک عنصر
    int getMin() { return heapArray[0]; } // بدست آوردن عنصر کمینه (ریشه هیپ)
    void deleteMin(); // حذف عنصر کمینه از هیپ
    void insert(int k); // اضافه کردن یک عنصر به هیپ
    void preorderTraversal(int index); // نمایش Preorder
    void inorderTraversal(int index); // نمایش Inorder
};

// سازنده با ظرفیت داده شده
MinHeap::MinHeap(int cap) {
    heapSize = 0;
    capacity = cap;
    heapArray = new int[cap];
}

// حذف عنصر کمینه از هیپ
void MinHeap::deleteMin() {
    if (heapSize <= 0)
        return;
    if (heapSize == 1) {
        heapSize--;
        return;
    }

    // انتقال آخرین عنصر به جای ریشه
    heapArray[0] = heapArray[heapSize - 1];
    heapSize--;
    heapify(0); // فراخوانی تابع heapify برای تثبیت هیپ
}

// تابع heapify برای تثبیت هیپ
void MinHeap::heapify(int i) {
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heapSize && heapArray[l] < heapArray[i])
        smallest = l;
    if (r < heapSize && heapArray[r] < heapArray[smallest])
        smallest = r;
    if (smallest != i) {
        swap(heapArray[i], heapArray[smallest]);
        heapify(smallest);
    }
}

// اضافه کردن عنصر به هیپ
void MinHeap::insert(int k) {
    if (heapSize == capacity) {
        cout << "\nOverflow: Could not insert key\n";
        return;
    }

    // اضافه کردن عنصر در انتهای هیپ
    heapSize++;
    int i = heapSize - 1;
    heapArray[i] = k;

    // تثبیت هیپ از آخر به اول
    while (i != 0 && heapArray[parent(i)] > heapArray[i]) {
        swap(heapArray[i], heapArray[parent(i)]);
        i = parent(i);
    }
}

// نمایش Preorder
void MinHeap::preorderTraversal(int index) {
    if (index >= heapSize)
        return;
    cout << heapArray[index] << " ";
    preorderTraversal(left(index));
    preorderTraversal(right(index));
}

// نمایش Inorder
void MinHeap::inorderTraversal(int index) {
    if (index >= heapSize)
        return;
    inorderTraversal(left(index));
    cout << heapArray[index] << " ";
    inorderTraversal(right(index));
}

// تابع main برای تست کد
int main() {
    MinHeap heap(15);
    heap.insert(10);
    heap.insert(20);
    heap.insert(15);
    heap.insert(30);
    heap.insert(40);
    heap.insert(50);
    heap.insert(100);
    heap.insert(25);
    heap.insert(45);
    heap.insert(5);

    cout << "Preorder traversal of min heap:\n";
    heap.preorderTraversal(0);
    cout << "\n\nInorder traversal of min heap:\n";
    heap.inorderTraversal(0);

    cout << "\n\nDeleting the minimum element (root)...\n";
    heap.deleteMin();

    cout << "\n\nPreorder traversal after deletion:\n";
    heap.preorderTraversal(0);
    cout << "\n\nInorder traversal after deletion:\n";
    heap.inorderTraversal(0);

    return 0;
}
