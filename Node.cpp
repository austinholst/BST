#include "Node.h"

using namespace std;

Node::Node(int newNum) {
  num = newNum;
}

//Setters
void Node::setLeft(Node* node) {
  left = node;
}

void Node::setRight(Node* node) {
  right = node;
}

void Node::setParent(Node* node) {
  parent = node;
}

void Node::setNum(int newNum) {
  num = newNum;
}

//Getters
Node* Node::getLeft() {
  return left;
}

Node* Node::getRight() {
  return right;
}

Node* Node::getParent() {
  return parent;
}

int Node::getNum() {
  return num;
}
