/////////Poorya Razavi 4001406916/////



#include <iostream>
#include <cstdlib>

using namespace std;
/////////////////////////////////////////////
// ساختار گره (node) برای لیست پیوندی
struct node {
    int data;
    struct node* next;
} *head; // اشاره‌گر به سر لیست
////////////////////////////////////////
// تابع برای ایجاد یک گره جدید
node* create_node(int v) {
    struct node* nd = new struct node;
    nd->data = v;
    nd->next = NULL;
    return nd;
}
//////////////////////////////////////////////
// افزودن یک عنصر به ابتدای لیست
void addFirst() {
    struct node* n;
    int v;

    cout << "Enter your data: ";
    cin >> v;

    n = create_node(v);
    if (head == NULL) {
        head = n;
    }
    else {
        n->next = head;
        head = n;
    }
}
///////////////////////////////////////////////
// افزودن یک عنصر به انتهای لیست
void addLast() {
    struct node* t, * n;
    int v;

    cout << "Enter your data: ";
    cin >> v;
    n = create_node(v);

    if (head == NULL) {
        head = n;
    }
    else {
        t = head;
        while (t->next != NULL) {
            t = t->next;
        }
        t->next = n;
    }
}
////////////////////////////////////////////////////////
// نمایش عناصر لیست
void show() {
    struct node* temp;

    if (head == NULL) {
        cout << "The list is empty." << endl;
        return;
    }

    temp = head;
    cout << "Members: ";
    while (temp != NULL) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}
//////////////////////////////////////////////////////
// افزودن یک عنصر به یک موقعیت خاص در لیست
void AddPos() {
    struct node* prvn, * tmpn, * n, * nxtn;
    int v, pos, c = 0;

    cout << "Enter your data: ";
    cin >> v;

    n = create_node(v);

    cout << "Position: ";
    cin >> pos;

    tmpn = head;
    while (tmpn != NULL) {
        tmpn = tmpn->next;
        c++;
    }

    if (pos == 1) {
        if (head == NULL) {
            head = n;
        }
        else {
            n->next = head;
            head = n;
        }
    }
    else if (pos > 1 && pos <= c) {
        nxtn = head;
        for (int i = 1; i < pos; i++) {
            prvn = nxtn;
            nxtn = nxtn->next;
        }
        prvn->next = n;
        n->next = nxtn;
    }
    else {
        cout << "Invalid position!" << endl;
    }
}
/////////////////////////////////////////////////
// حذف یک عنصر از یک موقعیت خاص در لیست
void deleteAtPos() {
    if (head == NULL) {
        cout << "List is empty, nothing to delete." << endl;
        return;
    }

    int pos;
    cout << "Enter the position to delete: ";
    cin >> pos;

    struct node* current = head;
    struct node* previous = NULL;

    int count = 0;
    while (current != NULL) {
        count++;
        if (count == pos) {
            if (previous == NULL) {
                // حذف گره اول
                head = current->next;
            }
            else {
                previous->next = current->next;
            }
            delete current;
            cout << "Element at position " << pos << " deleted." << endl;
            return;
        }
        previous = current;
        current = current->next;
    }

    cout << "Invalid position to delete." << endl;
}
///////////////////////////////////////////
// شمارش تعداد گره‌ها در لیست
int countNodes() {
    struct node* temp = head;
    int count = 0;

    while (temp != NULL) {
        count++;
        temp = temp->next;
    }

    return count;
}
/////////////////////////////////////////
// حذف یک عنصر بر اساس داده
void deleteByData() {
    if (head == NULL) {
        cout << "List is empty, nothing to delete." << endl;
        return;
    }

    int data;
    cout << "Enter the data to delete: ";
    cin >> data;

    struct node* current = head;
    struct node* previous = NULL;

    while (current != NULL) {
        if (current->data == data) {
            if (previous == NULL) {
                // حذف گره اول
                head = current->next;
            }
            else {
                previous->next = current->next;
            }
            delete current;
            cout << "Element with data " << data << " deleted." << endl;
            return;
        }
        previous = current;
        current = current->next;
    }

    cout << "Element with data " << data << " not found." << endl;
}
/////////////////////////////////////////////////
// تابع اصلی
int main() {
    int x;
    head = NULL;

    while (true) {
        cout << "1. Insert at end" << endl;
        cout << "2. Insert at position (including pos=1)" << endl;
        cout << "3. Show list" << endl;
        cout << "4. Delete at position" << endl;
        cout << "5. Count nodes" << endl;
        cout << "6. Delete by data" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter a number: ";

        cin >> x;

        switch (x) {
        case 1:
            addLast();
            break;
        case 2:
            AddPos();
            break;
        case 3:
            show();
            break;
        case 4:
            deleteAtPos();
            break;
        case 5:
            cout << "Number of nodes: " << countNodes() << endl;
            break;
        case 6:
            deleteByData();
            break;
        case 7:
            exit(0);
        default:
            cout << "Invalid option" << endl;
        }
    }

    return 0;
}
