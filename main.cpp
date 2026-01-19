#include <iostream>
#include <queue>
#include <cmath>
using namespace std;

template <class type>
class bi_tree 
{
  struct node {
    type item;
    node *right;
    node *left;
  };
  node *root;

  void add(node *&p, type v) {
    if(p == nullptr){
      p = new node{v, nullptr, nullptr};
      return;
    }

    if(v > p->item)
      add(p->right, v);
    else 
      add(p->left, v);
  }

  void preorder(node *p) {
    if(p == nullptr)
      return;
    cout << p->item << endl;
    preorder(p->left);
    preorder(p->right);
  }
  void inorder(node *p) {
    if(p == nullptr)
      return;
    inorder(p->left);
    cout << p->item << endl;
    inorder(p->right);
  }
  void postorder(node *p) {
    if(p == nullptr)
      return;
    postorder(p->left);
    postorder(p->right);
    cout << p->item << endl;
  }
  void levelprint(node *p) {
    if(p == nullptr)
      return;
    queue<node*> s;
    s.push(p);
    while(!s.empty()){
      node *cur = s.front();
      cout << cur->item << endl;
      if(cur->left != nullptr)
        s.push(cur->left);
      if(cur->right != nullptr)
        s.push(cur->right);
      s.pop();
    }
  }

  bool search(type some, node *p) {
    if(p == nullptr)
      return false;
    if(some > p->item)
      return search(some, p->right);
    else if(some < p->item)
      return search(some, p->left);
    else if(some == p->item)
      return true;
    return false;
  }

  node* remove(node *p, type value) {
    if(p == nullptr){
      cout << "The item is not found" << endl;
      return nullptr;
    }
    
    if(value > p->item)
      p->right = remove(p->right, value);
    else if(value < p->item)
      p->left = remove(p->left, value);
    else {
      if(p->left == nullptr && p->right == nullptr){
        delete p;
        return nullptr;
      }
      else if(p->left == nullptr && p->right != nullptr){
        node *cur = p->right;
        delete p;
        return cur;
      }
      else if(p->left != nullptr && p->right == nullptr){
        node *cur = p->left;
        delete p;
        return cur;
      }
      else if(p->left != nullptr && p->right != nullptr){
        node *parent = p;
        node *succ = p->right;
        while(succ->left != nullptr){
          parent = succ;
          succ = succ->left;
        }
        p->item = succ->item;
        if(parent == p) 
          parent->right = remove(parent->right, succ->item);
        else 
          parent->left = remove(parent->left, succ->item);
      }
    }
    return p;
  }

  void clear(node *p) {
    if(p == nullptr) 
      return;
    clear(p->left);
    clear(p->right);
    delete p;
  }

  int height(node *root) {
    if(root == nullptr)
      return -1;
    return max(height(root->left), height(root->right)) + 1;
  }

  int checkbalanced(node *root) {
      int bal;
      if(!root)
        return 0;

      int leftHeight = checkbalanced(root->left);
      if(leftHeight == -1)
        return -1;

      int rightHeight = checkbalanced(root->right);
      if(rightHeight == -1)
        return -1;

      if(abs(leftHeight - rightHeight) > 1)
        return -1;
      return 1 + (max(leftHeight, rightHeight));
  }

  void AVL_insert(node *&root, type value) {
    if(!root) {
      root = new node{value, nullptr, nullptr};
      return;
    }
    
    if(value > root->item){
      AVL_insert(root->right, value);
    }
    else {
      AVL_insert(root->left, value);
    }

    root = rebalance(root);
  }

  node *leftrotation(node *z) {
    node *y = z->right;
    node *holdyleft = y->left;
    y->left = z;
    z->right = holdyleft;
    return y;
  }
  node *rightrotation(node *z) {
    node *y = z->left;
    node *holdyright = y->right;
    y->right = z;
    z->left = holdyright;
    return y;
  }
  node *rebalance(node *root) {
    int bf = (height(root->left) - height(root->right));

    // LL imbalacnce
    if(bf > 1 && height(root->left->left) >= height(root->left->right)){
      return rightrotation(root);
    }
    // RR imbalance
    if(bf < -1 && height(root->right->right) >= height(root->right->left)){
      return leftrotation(root);
    }
    // LR imbalance
    if(bf > 1 && height(root->left->right) > height(root->left->left)){
      root->left = leftrotation(root->left);
      return rightrotation(root);
    }
    // RL imbalance
    if(bf < -1 && height(root->right->left) > height(root->right->right)){
      root->right = rightrotation(root->right);
      return leftrotation(root);
    }

    return root;
  }
public:
  bi_tree() : root(nullptr) {}
  ~bi_tree() {
    clear(root);
  }

  void add(type value) {
    add(root, value);
  }

  void preorder() { preorder(root); }
  void inorder() { inorder(root); }
  void postorder() { postorder(root); }
  void levelprint() {
     levelprint(root);
  }

  bool search(type something) {
    return search(something, root);
  }

  void remove(type t) {
    root = remove(root, t);
  }

  bool isEmpty() {
    return root == nullptr;
  }

  int height() {
    return height(root);
  }

  bool balanced() {
    return checkbalanced(root) != -1;
  }

  void AVL_insert(type value) {
    return AVL_insert(root, value);
  }
};

int main()
{
  
}