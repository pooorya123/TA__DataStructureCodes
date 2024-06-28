//poortya razavi 4001406916


#include <iostream>
#include <memory>
#include <vector>

using namespace std;

// ساختار گره درخت دودویی
struct Node {
    int data;
    unique_ptr<Node> left;
    unique_ptr<Node> right;
};

// کلاس صف (Queue)
class Queue {
private:
    vector<Node*> data;
public:
    void push(Node* node) {
        data.push_back(node);
    }
    void pop() {
        if (!data.empty()) {
            data.erase(data.begin());
        }
    }
    Node* front() const {
        return data.empty() ? nullptr : data.front();
    }
    bool empty() const {
        return data.empty();
    }
    int size() const {
        return data.size();
    }
};

// کلاس پشته (Stack)
class Stack {
private:
    vector<Node*> data;
public:
    void push(Node* node) {
        data.push_back(node);
    }
    void pop() {
        if (!data.empty()) {
            data.pop_back();
        }
    }
    Node* top() const {
        return data.empty() ? nullptr : data.back();
    }
    bool empty() const {
        return data.empty();
    }
};

class BinaryTree {
private:
    unique_ptr<Node> root;

    // تابع کمکی پیمایش Inorder
    void inorderHelper(Node* node) const {
        if (node == nullptr) return;
        inorderHelper(node->left.get());
        cout << node->data << " ";
        inorderHelper(node->right.get());
    }

    // تابع کمکی پیمایش Preorder
    void preorderHelper(Node* node) const {
        if (node == nullptr) return;
        cout << node->data << " ";
        preorderHelper(node->left.get());
        preorderHelper(node->right.get());
    }

    // تابع کمکی پیمایش Postorder
    void postorderHelper(Node* node) const {
        if (node == nullptr) return;
        postorderHelper(node->left.get());
        postorderHelper(node->right.get());
        cout << node->data << " ";
    }

    // تابع کمکی برای محاسبه ارتفاع درخت
    int heightHelper(Node* node) const {
        if (node == nullptr) return 0;
        int leftHeight = heightHelper(node->left.get());
        int rightHeight = heightHelper(node->right.get());
        return max(leftHeight, rightHeight) + 1;
    }

    // تابع کمکی برای پیدا کردن گره هدف و والد آن
    Node* findNode(int data, Node*& parent) const {
        Queue q;
        q.push(root.get());
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            if (current->data == data) return current;
            if (current->left) {
                parent = current;
                q.push(current->left.get());
            }
            if (current->right) {
                parent = current;
                q.push(current->right.get());
            }
        }
        return nullptr;
    }

public:
    BinaryTree() : root(nullptr) {}

    // تابع برای درج گره جدید در درخت
    void insert(int data) {
        auto newNode = make_unique<Node>();
        newNode->data = data;
        if (root == nullptr) {
            root = move(newNode);
            return;
        }

        Queue q;
        q.push(root.get());

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            if (current->left == nullptr) {
                current->left = move(newNode);
                break;
            }
            else {
                q.push(current->left.get());
            }

            if (current->right == nullptr) {
                current->right = move(newNode);
                break;
            }
            else {
                q.push(current->right.get());
            }
        }
    }

    // تابع برای پیمایش سطح به سطح (BFS)
    void BFS() const {
        if (root == nullptr) return;

        Queue q;
        q.push(root.get());

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            cout << current->data << " ";

            if (current->left) q.push(current->left.get());
            if (current->right) q.push(current->right.get());
        }
        cout << endl;
    }

    // تابع برای پیمایش عمق به عمق (DFS)
    void DFS() const {
        if (root == nullptr) return;

        Stack s;
        s.push(root.get());

        while (!s.empty()) {
            Node* current = s.top();
            s.pop();
            cout << current->data << " ";

            if (current->right) s.push(current->right.get());
            if (current->left) s.push(current->left.get());
        }
        cout << endl;
    }

    // تابع برای پیمایش Inorder
    void inorder() const {
        inorderHelper(root.get());
        cout << endl;
    }

    // تابع برای پیمایش Preorder
    void preorder() const {
        preorderHelper(root.get());
        cout << endl;
    }

    // تابع برای پیمایش Postorder
    void postorder() const {
        postorderHelper(root.get());
        cout << endl;
    }

    // تابع برای پیمایش سطح به سطح
    void levelOrder() const {
        if (root == nullptr) return;

        Queue q;
        q.push(root.get());

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            cout << current->data << " ";

            if (current->left) q.push(current->left.get());
            if (current->right) q.push(current->right.get());
        }
        cout << endl;
    }

    // تابع برای محاسبه ارتفاع درخت
    int getHeight() const {
        return heightHelper(root.get());
    }

    // تابع برای جستجوی یک داده در درخت
    bool search(int data) const {
        Queue q;
        q.push(root.get());

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            if (current->data == data) return true;

            if (current->left) q.push(current->left.get());
            if (current->right) q.push(current->right.get());
        }
        return false;
    }

    // تابع برای پیدا کردن ارتفاع یک گره خاص در درخت
    int findHeightOfNode(int data) const {
        Queue q;
        q.push(root.get());

        int level = 0;
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                Node* current = q.front();
                q.pop();
                if (current->data == data) return level;
                if (current->left) q.push(current->left.get());
                if (current->right) q.push(current->right.get());
            }
            ++level;
        }
        return -1; // گره پیدا نشد
    }

    // تابع برای حذف یک گره از درخت
    void deleteNode(int data) {
        if (!root) {
            cout << "Node with data " << data << " not found in the tree." << endl;
            return;
        }

        Queue q;
        q.push(root.get());
        Node* target = nullptr;
        Node* lastNode = nullptr;
        Node* lastNodeParent = nullptr;
        Node* targetParent = nullptr;

        while (!q.empty()) {
            lastNode = q.front();
            q.pop();

            if (lastNode->data == data) {
                target = lastNode;
                targetParent = lastNodeParent;
            }

            if (lastNode->left) {
                q.push(lastNode->left.get());
                lastNodeParent = lastNode;
            }

            if (lastNode->right) {
                q.push(lastNode->right.get());
                lastNodeParent = lastNode;
            }
        }

        if (target) {
            target->data = lastNode->data;

            if (lastNodeParent->left.get() == lastNode) {
                lastNodeParent->left.reset();
            }
            else {
                lastNodeParent->right.reset();
            }
        }
        else {
            cout << "Node with data " << data << " not found in the tree." << endl;
        }
    }
};

int main() {
    BinaryTree tree;
    tree.insert(10);
    tree.insert(2);
    tree.insert(38);
    tree.insert(4);
    tree.insert(5);
    tree.insert(6);

    cout << "Breadth-First Search => ";
    tree.BFS();

    cout << "Depth-First Search => ";
    tree.DFS();

    cout << "Inorder => ";
    tree.inorder();

    cout << "Preorder => ";
    tree.preorder();

    cout << "Postorder => ";
    tree.postorder();

    cout << "Level Order => ";
    tree.levelOrder();

    cout << "Height of the tree => " << tree.getHeight() << endl;

    int searchData = 3;
    cout << searchData << " is in the tree => " << (tree.search(searchData) ? "Yes" : "No") << endl;

    int heightOfNodeData = 4;
    cout << "Height of node with data " << heightOfNodeData << " => " << tree.findHeightOfNode(heightOfNodeData) << endl;

    int deleteData = 2;
    tree.deleteNode(deleteData);

    cout << "Inorder traversal after deleting node with data " << deleteData << " => ";
    tree.inorder();

    return 0;
}
