#pragma once
namespace ariel{
  class Node{
    private:
      int _data;
      Node* left;
      Node* right;
    public:
      Node(int data); //constructor
      Node* getLeft(); 
      Node* getRight(); 
      void setLeft(Node* left);
      void setRight(Node* right);
      int getData();
  };

  class Tree{
    private:
      int _size;
      Node* _root;
    public:
    //Constructor & Destructor
      Tree();
      ~Tree();
    //Methods
      Tree& insert(int i);
      void remove(int i);
      int size();
      bool contains(int i);
      int root();
      int parent(int i); //returns the parent of node conatining i.
      int left(int i); //returns the data inside the left child of node containing i.
      int right(int i); //returns the data inside the right child of node containing i.
      void print(); //prints the tree in-order.
      Node* getRoot(); //getter for the root.
    private:
      Node* find(int i); //finds i inside the tree
      void printRecursive(Node* curr);
      void Destroy(Node* curr);
      
  };
}
