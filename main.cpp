#include <iostream>
#include <queue>
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

  
};

int main()
{
  bi_tree<int> items;
  items.add(66);
  items.add(43);
  items.add(22);
  items.add(55);
  items.remove(55);
  items.postorder();
}