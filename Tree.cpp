
#include "Tree.hpp"
#include <stdexcept>
#include <iostream>

using namespace std;
using namespace ariel;


Node::Node(int data){ //constructor for Node.
  this->_data = data;
  this->left = NULL;
  this->right = NULL;
}

int Node::getData(){ //getter for data.
  return this->_data;
}

Node* Node::getLeft(){ //getter for left child.
  return this->left;
}

Node* Node::getRight(){ //getter for right child.
  return this->right;
}

void Node::setLeft(Node* left){
  this->left = left;
}

void Node::setRight(Node* right){
  this->right = right;
}


Tree::Tree(){ //constructor for Tree.
  _root = NULL;
  _size = 0;
}

Tree::~Tree(){ //recursively destroys the Tree. 
  Destroy(_root);
}

void Tree::Destroy(Node* curr){ //implementation of recursive destroyer.
  if(curr == NULL){
    return;
  }
  Destroy(curr->getLeft());
  Destroy(curr->getRight());
  delete curr;
}

Node* Tree::getRoot(){
  return this->_root;
}

Tree& Tree::insert(int n){
  if(contains(n)){
    throw runtime_error("already inside tree");
  }
  if(_size==0){
    _root = new Node(n);
    _size++;
  } else{
   Node* newNode = new Node(n); //new node created.
   Node* curr = _root; //current node we traverse tree with.
   bool flagInserted = false; //indicates if the node inserted.
   while(!flagInserted){
      if(n < curr->getData()) {
        if(curr-> getLeft() == NULL){
          curr->setLeft(newNode);
          _size++;
          flagInserted = true;
        }else{ //there exists a left child.
          curr = curr->getLeft();
        }
     }else{ //it means n is larger then curr.
       if(curr->getRight() == NULL){
         curr->setRight(newNode);
         _size++;
         break;
       }else{
         curr = curr->getRight();
       }
     }
   }
 }
  return *this;
}


void Tree::remove(int i){
  if(!contains(i)){
    throw runtime_error("You tried to remove non-existent node from the tree.");
  }
  if(_size==1){
    _size--;
    delete _root;
    return;
  } 
    Node* toRemove = find(i);
    if(i != root()){
      Node* parentOf = find(parent(i));
      bool toRemoveIsRightChild = toRemove->getData() > parentOf->getData();
      if(toRemove->getLeft() == NULL && toRemove->getRight() == NULL){
        //no childs. just deletes the node.
        if(toRemoveIsRightChild){
          parentOf->setRight(NULL);
        }
        else{
          parentOf->setLeft(NULL);
        }
        delete toRemove;
        _size--;
      }
      else if(toRemove->getRight() != NULL && toRemove ->getLeft()==NULL){
        //toRemove has only right child. 
        if(toRemoveIsRightChild){
          parentOf->setRight(toRemove->getRight());
        }
        else{ //toRemove is actually a left child.
          parentOf->setLeft(toRemove->getRight());
        }
        delete toRemove;
        _size--;
        return;
      
      } else if(toRemove ->getRight() == NULL && toRemove->getLeft()!=NULL){
        //toRemove has only left child.
        if(toRemoveIsRightChild){
          parentOf->setRight(toRemove->getLeft());
        }
        else{ //toRemove is actually a left child.
          parentOf->setLeft(toRemove->getLeft());
        }
        delete toRemove;
        _size--;
        return;
      } else{
        /*toRemove has 2 childs.
        if toRemove is a right child,
        will take the whole "left tree" of toRemove (left child)and add it to 
        the left-most child of the "right tree"(right child) of toRemove.
        */
        if(toRemoveIsRightChild){
          Node* concat = toRemove->getRight(); //guaranteed to have right child.
          while(concat->getLeft() != NULL){ 
            concat = concat->getLeft();
          }
          concat->setLeft(toRemove->getLeft());
          parentOf->setRight(toRemove->getRight());
          delete toRemove;
          _size--;
          return;
        } else{
          //to remove is left child. same logic, different side trees.
          Node* concat = toRemove->getLeft(); //guaranteed to have left child.
          while(concat->getRight() != NULL){
            concat = concat -> getRight();
          }
          concat->setRight(toRemove->getRight()); 
          parentOf->setLeft(toRemove->getLeft());
          delete toRemove;
          _size--;
          return;
        }
      }
    }
    else{//i is the root. removing root. no childs for root has already been handled (size=1).
      if(toRemove->getLeft() != NULL && toRemove->getRight() == NULL){
        //only left child.
        _root = toRemove->getLeft();
        delete toRemove;
        _size--;
      }
      else if(toRemove->getLeft() == NULL && toRemove->getRight() != NULL){
        //only right child.
        _root = toRemove->getRight();
        delete toRemove;
        _size--;
      }
      else{ //has 2 childs.
        Node* concat = toRemove->getRight();
        while(concat->getLeft() != NULL){
          concat = concat->getLeft();
        }
        concat->setLeft(toRemove->getLeft());
        _root = toRemove->getRight();
        delete toRemove;
        _size--;
      }
    }
}
int Tree::size(){
  return _size;
}

bool Tree::contains(int i){
  try{ //tries to find i inside binary tree.
    Node* isIn = find(i);
  }
  catch(exception& e){ //exception indicates failure to find i.
    return false;
  }
  return true;
}
int Tree::root(){
  if(_size>0){
    return getRoot()->getData();
  }else{
    throw invalid_argument("there is no root");
  }
}

int Tree::parent(int i){ //returns the parent of node containing i.
   if(size()==0 || !contains(i) || root() == i){
    throw invalid_argument("has no parent or does not contain specified node.");
   } else{
    Node* par = this->getRoot(); //pointer to the parent node. starts at root.
    bool foundflag = false;
    while(!foundflag){ //guaranteed to find i.
       if((par->getLeft() !=NULL && par->getLeft()->getData() == i) || (par->getRight() != NULL && par->getRight()->getData() == i)){
         foundflag = true;
       }
       else if(i < par->getData()){
         par = par->getLeft();
       }else{
         par = par->getRight();
       }
     }
     return par->getData();
   }
}

int Tree::left(int i){
  Node* locate = find(i); //finds i inside tree. exception otherwise.
  if(locate->getLeft() != NULL){
    return locate->getLeft()->getData();
  } else {
    throw invalid_argument("There is no left child for requested node.");
  }
}

int Tree::right(int i){
  Node* locate = find(i); //finds i inside tree. exception otherwise.
  if(locate->getRight() != NULL){
    return locate->getRight()->getData();
  } else {
    throw invalid_argument("There is no right child for requested node.");
  }
}

void Tree::print(){ //prints the binary tree IN-ORDER.
  printRecursive(_root);
}

void Tree::printRecursive(Node* curr){ //IN-ORDER recursive printing.
  if(curr==NULL){
    return;
  }
  printRecursive(curr->getLeft());
  cout << curr->getData() << " ";
  printRecursive(curr->getRight());
}


Node* Tree::find(int i){ //finds i inside the tree, returns the pointer to a node containing i.
// throws exception otherwise. 
  if(size() == 0 ){
    throw invalid_argument("Cannot find in an empty tree");
  }
  Node* curr = getRoot();
  while(curr!=NULL){
    if(curr->getData() == i){
      return curr;
    }
    else if(curr->getData()>i){
      curr = curr->getLeft();
    }
    else{
      curr = curr->getRight();
    }
  }
  throw runtime_error("Cannot find requested node."); //traverse through tree, did not find i.
}

