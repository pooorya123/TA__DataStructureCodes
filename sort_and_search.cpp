/////////Poorya Razavi 4001406916/////


#include <iostream>
#include <vector> // برای استفاده از بردارها
#include <algorithm> // برای استفاده از توابع الگوریتمی مثل swap

using namespace std;

// ساختار برای الگوریتم‌های مرتب‌سازی
struct Sort {
    // مرتب‌سازی حبابی
    void bubbleSort(vector<int>& arr) {
        int n = arr.size();
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - i - 1; ++j) {
                if (arr[j] > arr[j + 1]) {
                    swap(arr[j], arr[j + 1]); // استفاده از swap
                }
            }
        }
    }

    // مرتب‌سازی انتخابی
    void selectionSort(vector<int>& arr) {
        int n = arr.size();
        for (int i = 0; i < n - 1; ++i) {
            int minIndex = i;
            for (int j = i + 1; j < n; ++j) {
                if (arr[j] < arr[minIndex]) {
                    minIndex = j;
                }
            }
            swap(arr[i], arr[minIndex]); // استفاده از swap
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
    cout << "1. Bubble Sort" << endl;
    cout << "2. Selection Sort" << endl;
    cin >> choice;

    switch (choice) {
    case 1:
        sorter.bubbleSort(arr);
        cout << "Array sorted using Bubble Sort." << endl;
        break;
    case 2:
        sorter.selectionSort(arr);
        cout << "Array sorted using Selection Sort." << endl;
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
