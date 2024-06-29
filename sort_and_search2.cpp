//poorya razavi  4001406916
#include <iostream>
#include <vector> // برای استفاده از بردارها

using namespace std;

// ساختار برای الگوریتم‌های مرتب‌سازی
struct Sort {
    // مرتب‌سازی درجی
    void insertionSort(vector<int>& arr) {
        int n = arr.size();
        for (int i = 1; i < n; ++i) {
            int key = arr[i];
            int j = i - 1;
            while (j >= 0 && arr[j] > key) {
                arr[j + 1] = arr[j];
                --j;
            }
            arr[j + 1] = key;
        }
    }

    // مرتب‌سازی ادغامی
    void merge(vector<int>& arr, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;
        vector<int> L(n1), R(n2);

        for (int i = 0; i < n1; ++i)
            L[i] = arr[left + i];
        for (int j = 0; j < n2; ++j)
            R[j] = arr[mid + 1 + j];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr[k] = L[i];
                ++i;
            }
            else {
                arr[k] = R[j];
                ++j;
            }
            ++k;
        }

        while (i < n1) {
            arr[k] = L[i];
            ++i;
            ++k;
        }

        while (j < n2) {
            arr[k] = R[j];
            ++j;
            ++k;
        }
    }

    void mergeSort(vector<int>& arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }
};

// ساختار برای الگوریتم‌های جستجو
struct Search {
    // جستجو خطی
    int linearSearch(const vector<int>& arr, int target) {
        for (size_t i = 0; i < arr.size(); ++i) {
            if (arr[i] == target) {
                return i;
            }
        }
        return -1; // اگر عنصر مورد نظر پیدا نشد
    }

    // جستجو دودویی (فقط برای آرایه‌های مرتب)
    int binarySearch(const vector<int>& arr, int target) {
        int left = 0;
        int right = arr.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (arr[mid] == target) {
                return mid;
            }
            else if (arr[mid] < target) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        return -1; // اگر عنصر مورد نظر پیدا نشد
    }
};

int main() {
    vector<int> arr = { 34, 7, 23, 32, 5, 62 }; // تعریف یک بردار از اعداد صحیح
    int choice;

    // ایجاد نمونه‌های از ساختارهای Sort و Search
    Sort sorter;
    Search searcher;

    // انتخاب نوع مرتب‌سازی
    cout << "Choose sorting method:" << endl;
    cout << "1. Insertion Sort" << endl;
    cout << "2. Merge Sort" << endl;
    cin >> choice;

    switch (choice) {
    case 1:
        sorter.insertionSort(arr);
        cout << "Array sorted using Insertion Sort." << endl;
        break;
    case 2:
        sorter.mergeSort(arr, 0, arr.size() - 1);
        cout << "Array sorted using Merge Sort." << endl;
        break;
    default:
        cout << "Invalid choice." << endl;
        return 1;
    }

    cout << "Sorted array: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    // گرفتن عدد برای جستجو
    cout << "Enter number to search: ";
    int target;
    cin >> target;

    // انتخاب نوع جستجو
    cout << "Choose search method:" << endl;
    cout << "1. Linear Search" << endl;
    cout << "2. Binary Search" << endl;
    cin >> choice;

    int index = -1;
    switch (choice) {
    case 1:
        index = searcher.linearSearch(arr, target);
        break;
    case 2:
        index = searcher.binarySearch(arr, target);
        break;
    default:
        cout << "Invalid choice." << endl;
        return 1;
    }

    // نمایش نتیجه جستجو
    if (index != -1) {
        cout << "Element found at index " << index << endl;
    }
    else {
        cout << "Element not found." << endl;
    }

    return 0;
}
