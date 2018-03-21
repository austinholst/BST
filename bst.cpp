#include <iostream>
#include <cstring>
#include "Node.h"
#include <stdio.h>

using namespace std;


//Prototypes
void build(Node* &head, Node* previous, Node* current,  Node* newNode);
void printTree(Node* head, int space);
void remove(Node* head, int number);
Node* findMin(Node* current);


//Variables
bool running = true;

//Head declaration
Node* head = NULL;

int main() {
  while(running != false) {
    cout << "Would you like to 'add' a number, 'remove' a number, 'print' the tree or 'quit'?" << endl;
    char answer[10];
    cin >> answer;
    if(strcmp(answer, "add") == 0) {
      cout << "What number would you like to add to the binary tree?" << endl;
      int number;
      cin >> number;
      Node* node = new Node(number);
      build(head, head, head, node);
    }
    else if(strcmp(answer, "remove") == 0) {
      cout << "What number would you like to remove?" << endl;
      int number;
      cin >> number;
      remove(head,  number);
    }
    else if(strcmp(answer, "print") == 0) {
      printTree(head, 0);
    }
    else if(strcmp(answer, "quit") == 0) {
      running = false;
    }
    else {
      cout << "That wasn't one of the options..." << endl;
    }
  }
   
  return 0;
}


//Build the unbalanced tree
void build(Node* &head, Node* previous, Node* current,  Node* newNode) {
  if(head == NULL) {
    head = newNode;
  }
  else {
    //If the new node is larger than the head go right
    if(newNode->getNum() > current->getNum()) {
      //If there is nothing to the right of head place new node there
      if(current->getRight() == NULL) {
	current->setRight(newNode);
	newNode->setParent(current);
      }
      //If there is something to the right of head then run build again with that node as head
      else {
	build(head, previous, current->getRight(), newNode);
      }
    }
    //If the new node is smaller than the head go left
    else {
      if(current->getLeft() == NULL) {
	current->setLeft(newNode);
	newNode->setParent(current);
      }
      else {
	build(head, previous, current->getLeft(), newNode);
      }
    }
  }
}

//Print out the tree
void printTree(Node* head, int space) {
  if(head == NULL) {
    return;
  }
  space += 10;
  printTree(head->getRight(), space);
  
  printf("\n");
  for(int i = 0; i < space; i++) {
    printf(" ");
  }
  printf("%d\n", head->getNum());
  printTree(head->getLeft(), space);
}

//Remove nodes from the tree
//Instead of swapping the data in the node, swap the node itself
void remove(Node* head, int number) {
  //If the current node is the same as the number you want to delete
  if(head->getNum() == number) {
    //If the current node has no children
    if(head->getLeft() == NULL && head->getRight() == NULL) {
      Node* current = head;
      if(current->getParent() == NULL) {
	head = NULL; //THIS DOESN"T WORK
      }
      else if(current->getParent()->getLeft() == current) {
	current->getParent()->setLeft(NULL);
      }
      else if(current->getParent()->getRight() == current) {
	current->getParent()->setRight(NULL);
      }
    }
    //If there is only a right node
    else if(head->getLeft() == NULL) {
      Node* temp = head->getRight();
      head->setNum(temp->getNum());
      head->setRight(temp->getRight());
      head->setLeft(temp->getLeft());
      delete temp;
    }
    //If there is only a left node
    else if(head->getRight() == NULL) {
      Node* temp = head->getLeft();
      head->setNum(temp->getNum());
      head->setRight(temp->getRight());
      head->setLeft(temp->getLeft());
      delete temp;
    }
    //there are two children
    else if(head->getLeft() != NULL && head->getRight() != NULL) {
      Node* current = head->getRight();
      Node* previous = head;
      if(current->getLeft() == NULL) {
	head->setNum(current->getNum());
	head->setRight(current->getRight());
      }
      while(current->getLeft() !=NULL) {
	previous = current;
	current = current->getLeft();
      }
      head->setNum(current->getNum());
      if(current->getRight() != NULL) {
	current->setNum(current->getRight()->getNum());
	current->setRight(NULL);
      }
      else {
	current->getParent()->setLeft(NULL);
      }
    }
  }
  //If the number you want is bigger than current 
  else if(number > head->getNum()) {
    if(head->getRight() == NULL) {
      cout << "That number isn't in the tree" << endl;
    }
    else {
      remove(head->getRight(), number);
    }
  }
  //If the number you want is smaller than current
  else if(number < head->getNum()) {
    if(head->getLeft() == NULL) {
      cout << "That number isn't in the tree" << endl;
    }
    else {
      remove(head->getLeft(), number);
    }
  }
}

//Goes right one and then all the way to the left of the tree
Node* findMin(Node* current) {
  if(current->getLeft() != NULL) {
    findMin(current->getLeft());
  }
  else {
    cout << "Find Min num: "  << current->getNum() << endl;
    return current;
  }
}
