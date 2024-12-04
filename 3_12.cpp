#include <iostream>
#include <stack>
#include <string>
using namespace std;

// Định nghĩa một nút trong cây
struct Node {
    string value; // Giá trị của nút (toán tử hoặc toán hạng)
    Node* left;   // Con trái
    Node* right;  // Con phải

    // Constructor
    Node(string val) : value(val), left(nullptr), right(nullptr) {}
};

// Định nghĩa cây biểu thức
struct ExpressionTree {
    Node* root; // Gốc của cây

    // Constructor
    ExpressionTree() : root(nullptr) {}

    // Kiểm tra cây rỗng
    bool isEmpty() const {
        return root == nullptr;
    }

    // Hàm thêm node vào cây (xây dựng từ hậu tố)
    void buildFromPostfix(const string& postfix);

    // Duyệt cây theo các kiểu
    void printInfix(Node* node);   // Trung tố
    void printPrefix(Node* node); // Tiền tố
    void printPostfix(Node* node);// Hậu tố

    // Gọi in từ gốc
    void printInfix() { printInfix(root); }
    void printPrefix() { printPrefix(root); }
    void printPostfix() { printPostfix(root); }
};
void ExpressionTree::buildFromPostfix(const string& postfix) {
    stack<Node*> st;

    for (char ch : postfix) {
        if (isspace(ch)) continue; // Bỏ qua khoảng trắng
        string s(1, ch);

        // Nếu là toán hạng
        if (isalnum(ch)) {
            st.push(new Node(s));
        }
        // Nếu là toán tử
        else {
            Node* node = new Node(s);
            node->right = st.top(); st.pop(); // Con phải
            node->left = st.top(); st.pop();  // Con trái
            st.push(node);
        }
    }

    // Gốc của cây chính là phần tử cuối cùng trong stack
    root = st.top();
    st.pop();
}
void ExpressionTree::printInfix(Node* node) {
    if (!node) return;

    if (node->left || node->right) cout << "("; // Thêm ngoặc nếu là toán tử
    printInfix(node->left);
    cout << node->value;
    printInfix(node->right);
    if (node->left || node->right) cout << ")";
}
void ExpressionTree::printPrefix(Node* node) {
    if (!node) return;

    cout << node->value << " ";
    printPrefix(node->left);
    printPrefix(node->right);
}
void ExpressionTree::printPostfix(Node* node) {
    if (!node) return;

    printPostfix(node->left);
    printPostfix(node->right);
    cout << node->value << " ";
}
int main() {
    ExpressionTree tree;
    
    string postfix = "ab5*-cd6/^+hf-e*"; // Biểu thức hậu tố
    tree.buildFromPostfix(postfix);

    cout << "Trung tố (Infix): ";
    tree.printInfix();
    cout << endl;

    cout << "Tiền tố (Prefix): ";
    tree.printPrefix();
    cout << endl;

    cout << "Hậu tố (Postfix): ";
    tree.printPostfix();
    cout << endl;

    return 0;
}

