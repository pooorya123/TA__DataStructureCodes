////////////poorya razavi 4001406916////////////////


#include <iostream>
#include <algorithm> // برای استفاده از max
using namespace std;

const int MAX_SIZE = 100;

// افزودن دو چندجمله‌ای
void addPolynomials(int poly1[][2], int size1, int poly2[][2], int size2, int result[][2]) {
    int i = 0, j = 0, k = 0;
    for (; i < size1 && j < size2; k++) {
        if (poly1[i][1] == poly2[j][1]) {
            result[k][0] = poly1[i][0] + poly2[j][0];
            result[k][1] = poly1[i][1];
            i++;
            j++;
        }
        else if (poly1[i][1] > poly2[j][1]) {
            result[k][0] = poly1[i][0];
            result[k][1] = poly1[i][1];
            i++;
        }
        else {
            result[k][0] = poly2[j][0];
            result[k][1] = poly2[j][1];
            j++;
        }
    }
    for (; i < size1; i++, k++) {
        result[k][0] = poly1[i][0];
        result[k][1] = poly1[i][1];
    }
    for (; j < size2; j++, k++) {
        result[k][0] = poly2[j][0];
        result[k][1] = poly2[j][1];
    }
}

// تفریق دو چندجمله‌ای
void subtractPolynomials(int poly1[][2], int size1, int poly2[][2], int size2, int result[][2]) {
    int i = 0, j = 0, k = 0;
    for (; i < size1 && j < size2; k++) {
        if (poly1[i][1] == poly2[j][1]) {
            result[k][0] = poly1[i][0] - poly2[j][0];
            result[k][1] = poly1[i][1];
            i++;
            j++;
        }
        else if (poly1[i][1] > poly2[j][1]) {
            result[k][0] = poly1[i][0];
            result[k][1] = poly1[i][1];
            i++;
        }
        else {
            result[k][0] = -poly2[j][0];
            result[k][1] = poly2[j][1];
            j++;
        }
    }
    for (; i < size1; i++, k++) {
        result[k][0] = poly1[i][0];
        result[k][1] = poly1[i][1];
    }
    for (; j < size2; j++, k++) {
        result[k][0] = -poly2[j][0];
        result[k][1] = poly2[j][1];
    }
}

// ضرب دو چندجمله‌ای
void multiplyPolynomials(int poly1[][2], int size1, int poly2[][2], int size2, int result[][2]) {
    int tempResult[MAX_SIZE * MAX_SIZE][2] = { 0 }; // برای ذخیره نتایج موقت
    int k = 0;

    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            tempResult[k][0] = poly1[i][0] * poly2[j][0];
            tempResult[k][1] = poly1[i][1] + poly2[j][1];
            k++;
        }
    }

    // ترکیب جملات مشابه در نتیجه
    for (int i = 0; i < k; i++) {
        for (int j = i + 1; j < k; j++) {
            if (tempResult[i][1] == tempResult[j][1]) {
                tempResult[i][0] += tempResult[j][0];
                tempResult[j][0] = 0; // علامت گذاری به عنوان ترکیب شده
            }
        }
    }

    // حذف جملات ترکیب شده
    int newSize = 0;
    for (int i = 0; i < k; i++) {
        if (tempResult[i][0] != 0) {
            result[newSize][0] = tempResult[i][0];
            result[newSize][1] = tempResult[i][1];
            newSize++;
        }
    }
}

// چاپ چندجمله‌ای
void printPolynomial(int poly[][2], int size) {
    bool isFirstTerm = true;
    for (int i = 0; i < size; i++) {
        if (poly[i][0] != 0) {
            if (!isFirstTerm && poly[i][0] > 0) {
                cout << "+";
            }
            cout << poly[i][0];
            if (poly[i][1] != 0) {
                cout << "x";
                if (poly[i][1] != 1) {
                    cout << "^" << poly[i][1];
                }
            }
            isFirstTerm = false;
        }
    }
    if (isFirstTerm) {
        cout << "0";
    }
    cout << endl;
}

// تابع اصلی
int main() {
    int poly1[MAX_SIZE][2], poly2[MAX_SIZE][2], result1[MAX_SIZE][2], result2[MAX_SIZE][2], result3[MAX_SIZE][2];
    int size1, size2;

    // ورودی چندجمله‌ای اول
    cout << "Enter the size of the first polynomial: ";
    cin >> size1;
    cout << "Enter the coefficients and exponents of the first polynomial: ";
    for (int i = 0; i < size1; i++) {
        cin >> poly1[i][0] >> poly1[i][1];
    }

    // ورودی چندجمله‌ای دوم
    cout << "Enter the size of the second polynomial: ";
    cin >> size2;
    cout << "Enter the coefficients and exponents of the second polynomial: ";
    for (int i = 0; i < size2; i++) {
        cin >> poly2[i][0] >> poly2[i][1];
    }

    // افزودن چندجمله‌ای‌ها
    addPolynomials(poly1, size1, poly2, size2, result1);
    cout << "Sum of the polynomials: ";
    printPolynomial(result1, max(size1, size2));

    // تفریق چندجمله‌ای‌ها
    subtractPolynomials(poly1, size1, poly2, size2, result2);
    cout << "Difference of the polynomials: ";
    printPolynomial(result2, max(size1, size2));

    // ضرب چندجمله‌ای‌ها
    multiplyPolynomials(poly1, size1, poly2, size2, result3);
    cout << "Product of the polynomials: ";
    printPolynomial(result3, size1 * size2); // حداکثر اندازه ممکن نتیجه

    return 0;
}
