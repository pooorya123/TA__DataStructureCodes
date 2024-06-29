#include <iostream>
#include <string>

using namespace std;

// کلاس Stack برای پیاده‌سازی پشته
class Stack {
    // ساختار Node برای ذخیره داده‌ها و اشاره‌گر به نود بعدی
    struct Node {
        string data;
        Node* next;
    }; Node* topNode; // اشاره‌گر به بالای پشته

public:
    Stack() : topNode(nullptr) {} // سازنده برای مقداردهی اولیه پشته به null

    ~Stack() { // مخرب برای پاک کردن حافظه تخصیص داده‌شده
        while (!isEmpty()) {
            pop();
        }
    }

    // تابع push برای افزودن عنصر به پشته
    void push(const string& value) {
        Node* newNode = new Node{ value, topNode }; // ایجاد نود جدید
        topNode = newNode; // تنظیم بالای پشته به نود جدید
    }

    // تابع top برای دسترسی به عنصر بالای پشته
    string top() const {
        if (!isEmpty()) {
            return topNode->data;
        }
        throw runtime_error("Stack is empty"); // خطا اگر پشته خالی باشد
    }

    // تابع pop برای حذف عنصر بالای پشته
    void pop() {
        if (!isEmpty()) {
            Node* temp = topNode;
            topNode = topNode->next; // تنظیم بالای پشته به نود بعدی
            delete temp; // حذف نود قبلی
        }
        else {
            throw runtime_error("Stack is empty"); // خطا اگر پشته خالی باشد
        }
    }

    // تابع isEmpty برای بررسی خالی بودن پشته
    bool isEmpty() const {
        return topNode == nullptr;
    }
};

// تابع برای تبدیل عبارت postfix به infix
string postfixToInfix(const string& postfix) {
    Stack stack;

    for (char ch : postfix) { // پردازش هر کاراکتر از عبارت
        if (isalnum(ch)) {  // اگر کاراکتر عدد یا حرف است
            stack.push(string(1, ch)); // اضافه کردن به پشته
        }
        else { // اگر کاراکتر عملگر است
            string op1 = stack.top(); stack.pop(); // گرفتن و حذف اولین عملوند
            string op2 = stack.top(); stack.pop(); // گرفتن و حذف دومین عملوند
            string expression = "(" + op2 + ch + op1 + ")"; // ایجاد عبارت infix
            stack.push(expression); // اضافه کردن عبارت به پشته
        }
    }

    return stack.top(); // برگرداندن عبارت infix نهایی
}

int main() {
    string postfix = "ab+cd+*"; // تعریف عبارت postfix
    string infix = postfixToInfix(postfix); // تبدیل به infix
    cout << "Infix: " << infix << endl; // نمایش عبارت infix
    return 0;
}
////////قسمت دوم تغییر عبارات!!!


