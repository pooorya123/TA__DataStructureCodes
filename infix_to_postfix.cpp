//poorya razavi 4001406916


#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>
using namespace std;

///////////////////////////////////////////////////////
// ساختار پشته
struct Stack {
    int* array; // آرایه برای نگهداری عناصر پشته
    int top; // شاخص بالاترین عنصر در پشته
    unsigned capacity; // ظرفیت پشته
};

///////////////////////////////////////////////////////
// ایجاد پشته با ظرفیت مشخص
struct Stack* createStack(unsigned capacity) {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    if (!stack) return NULL;

    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (int*)malloc(stack->capacity * sizeof(int));

    if (!stack->array) return NULL;

    return stack;
}

///////////////////////////////////////////////////////
// بررسی اینکه آیا پشته خالی است یا خیر
int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

///////////////////////////////////////////////////////
// گرفتن بالاترین عنصر از پشته بدون حذف آن
char peek(struct Stack* stack) {
    return stack->array[stack->top];
}

///////////////////////////////////////////////////////
// حذف بالاترین عنصر از پشته و بازگرداندن آن
char pop(struct Stack* stack) {
    if (!isEmpty(stack))
        return stack->array[stack->top--];
    return '$'; // علامت $ برای نشان دادن خطا پشته خالی
}

///////////////////////////////////////////////////////
// افزودن یک عنصر به بالای پشته
void push(struct Stack* stack, char op) {
    stack->array[++stack->top] = op;
}

///////////////////////////////////////////////////////
// بررسی اینکه آیا یک کاراکتر عملوند (عدد) است یا خیر
int isOperand(char ch) {
    return (ch >= '0' && ch <= '9');
}

///////////////////////////////////////////////////////
// بازگرداندن تقدم عملگرها
int precedence(char ch) {
    switch (ch) {
    case '+':
    case '-': return 1;
    case '*':
    case '/': return 2;
    case '^': return 3;
    }
    return -1;
}

///////////////////////////////////////////////////////
// تبدیل عبارت اینفیکس به پستفیکس
void infixToPostfix(char* expression, char* postfix) {
    int i, k;
    struct Stack* stack = createStack(strlen(expression));
    if (!stack) return;

    for (i = 0, k = -1; expression[i]; ++i) {
        // اگر کاراکتر عملوند است، به نتیجه اضافه شود
        if (isOperand(expression[i]))
            postfix[++k] = expression[i];
        // اگر کاراکتر '(' است، به پشته اضافه شود
        else if (expression[i] == '(')
            push(stack, expression[i]);
        // اگر کاراکتر ')' است، عناصر پشته تا '(' بیرون کشیده شوند
        else if (expression[i] == ')') {
            while (!isEmpty(stack) && peek(stack) != '(')
                postfix[++k] = pop(stack);
            if (!isEmpty(stack) && peek(stack) != '(')
                return;
            else
                pop(stack);
        }
        else {
            // اگر کاراکتر عملگر است، تا زمانی که تقدم کمتر یا مساوی عملگرهای پشته باشد، آن‌ها را بیرون بکشید
            while (!isEmpty(stack) && precedence(expression[i]) <= precedence(peek(stack)))
                postfix[++k] = pop(stack);
            push(stack, expression[i]);
        }
    }

    // تمام عملگرهای باقی‌مانده در پشته را به نتیجه اضافه کنید
    while (!isEmpty(stack))
        postfix[++k] = pop(stack);

    postfix[++k] = '\0'; // پایان دادن به رشته پستفیکس
}

///////////////////////////////////////////////////////
// ارزیابی عبارت پستفیکس
int evaluatePostfix(char* postfix) {
    struct Stack* stack = createStack(strlen(postfix));
    if (!stack) return -1;

    for (int i = 0; postfix[i]; ++i) {
        // اگر کاراکتر عملوند است، به پشته اضافه شود
        if (isOperand(postfix[i]))
            push(stack, postfix[i] - '0');
        else {
            // اگر کاراکتر عملگر است، دو عملوند از پشته بیرون کشیده و عملیات را انجام دهید
            int val1 = pop(stack);
            int val2 = pop(stack);
            switch (postfix[i]) {
            case '+': push(stack, val2 + val1); break;
            case '-': push(stack, val2 - val1); break;
            case '*': push(stack, val2 * val1); break;
            case '/': push(stack, val2 / val1); break;
            }
        }
    }
    return pop(stack);
}

///////////////////////////////////////////////////////
// ارزیابی عبارت اینفیکس
int evaluateInfix(char* expression) {
    char postfix[100];
    infixToPostfix(expression, postfix); // تبدیل اینفیکس به پستفیکس
    return evaluatePostfix(postfix); // ارزیابی پستفیکس
}

///////////////////////////////////////////////////////
int main() {
    char expression[] = "3+5*(2-1)";
    cout << "Infix Expression: " << expression << endl;

    char postfix[100];
    infixToPostfix(expression, postfix);
    cout << "Postfix Expression: " << postfix << endl;

    int result = evaluateInfix(expression);
    cout << "Evaluation Result: " << result << endl;

    return 0;
}
