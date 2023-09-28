/* Serhiy Leonchyk
*
* P1: Array Based Binary Search Tree
*
* This Program creates a Binary Search Tree by storing Pair Pointers in an
array
* that point to pairs that contain a Key that is used to compare the
values, and
* value itself. The Array of Pointers is arranged so the index of left
child is
* double the index of the parent, and the right child's index is 1 more
than double
* the parents index. The program has an insert function to insert nodes in
the proper
* place, a remove function to remove nodes and a few helper functions to
help deal
* with the newly created orphans. There are also functions to get the size
and number
* of pairs in the tree. As well as a function to return a true/false if a
value is
* in the tree and a function that updates a value if a pair with a certain
value is
* contained in the tree.
*/
#include "BSTInterface.h"
#include <string>
#include <algorithm>
using namespace std;
template <typename KeyComparable, typename Value >
class BinarySearchTree : BSTInterface < KeyComparable, Value >
{
private:
/*
* Private "Node" Class...for this implementation, the Pair is the Node
*/
class Pair {
public:
KeyComparable key;
Value value;
//Initialize class members from constructor arguments
//by using a member initializer list.
//This method uses direct initialization, which is more
//efficient than using assignment operators inside the constructor body.
Pair(KeyComparable& key, Value& value)
: value{ value }, key{ key }
{
// empty constructor...member initializer is doing all the work
}
}; // end of Pair class
// number of values stored in the tree
int count = 0;
// capacity of array holding the tree
int size = 25;
// the array that holds the pairs
Pair** root = new Pair * [size] {};
/*
* Prints the data of the trea in order based on the key to the output
stream
*/
void printTree(int index, std::ostream& out) const {
// If the current node is empty
if (index > size || root[index] == nullptr) {
// We go back to whoever called us
return;
}
// Call print on everything to the left, that are smaller than us
printTree(index * 2, out);
// Output ourselves to the output stream
out << *(root[index]->value) << endl;
// Call Print on everything to the right, that are greater than us
printTree((index * 2) + 1, out);
return;
}
public:
BinarySearchTree() {
count = 0;
size = 25;
Pair** root = new Pair * [size] {};
cout << "Constructor" << endl;
}
~BinarySearchTree() {
makeEmpty();
delete[] root;
}
/*
* Finds the node with the smallest element in the tree
*/
const Value findMin() const {
int iterator = 1;
if (root[iterator] == nullptr) {
return nullptr;
}
else if (root[iterator * 2] == nullptr && root[(iterator * 2) + 1]
== nullptr) {
return (root[iterator]->value);
}
else {
while (root[iterator * 2] != nullptr) {
iterator = (iterator * 2);
}
return (root[iterator]->value);
}
}
/*
* Finds the node with the largest element in the tree
*/
const Value findMax() const {
int iterator = 1;
if (root[iterator] == nullptr) {
return nullptr;
}
else if (root[iterator * 2] == nullptr && root[(iterator * 2) + 1]
== nullptr) {
return (root[iterator]->value);
}
else {
while (root[(iterator * 2) + 1] != nullptr) {
iterator = (iterator * 2) + 1;
}
return (root[iterator]->value);
}
}
/*
* Finds the node with a key that matches the argKey
* updates the founditem refrerence if found
* returns true if it was found
* returns false if it was not
*/
bool find(const KeyComparable& argKey, Value& foundItem) const {
int iterator = 1;
bool found = false;
while (found != true && iterator < size) {
if (root[iterator]->key == argKey) {
foundItem = root[iterator]->value;
found = true;
}
else if (argKey < root[iterator]->key) {
iterator = (iterator * 2);
}
else if (argKey > root[iterator]->key) {
iterator = (iterator * 2) + 1;
}
else {
return false;
}
}
return found;
}
/*
* Returns true if the item is found in the tree
*/
bool contains(const KeyComparable& argKey) const {
int iterator = 1;
while (root[iterator] != nullptr) {
if (argKey == root[iterator]->key) {
return true;
}
else if (argKey < root[iterator]->key) {
iterator = (iterator * 2);
}
else {
iterator = (iterator * 2) + 1;
}
}
return false;
}
/*
* Returns true if tree has no nodes
*/
bool isEmpty() const {
// stub code: needs to be implemented
return root[1] == nullptr;
}
/*
* Prints all the data from the tree in order based on key
*/
void printTree(std::ostream& out = cout) const {
printTree(1, cout);
}
/*
* Removes all nodes from the tree
*/
void makeEmpty() {
for (int i = 0; i < size; i++) {
delete root[i];
root[i] = nullptr;
}
count = 0;
}
/*
* Inserts a node into the tree
* maintains this property of the tree:
* All nodes to the left will be less
* All nodes to the right will be greater
*/
bool insert(Value value, KeyComparable key) {
Pair* temp = new Pair(key, value);
bool insertCheck = false;
// If the tree is empty then it makes the first number the root
if (root[1] == nullptr)
{
root[1] = temp;
insertCheck = true;
count++;
}
// If the tree only has one member
if (root[2] == nullptr && root[3] == nullptr)
{
// If it is less than, then it puts it to the left
if (temp->key < root[1]->key)
{
root[2] = temp;
//cout << "Going Left" << endl;
insertCheck = true;
count++;
}
// If temp is greater than root, then it is put to the right
else if (temp->key > root[1]->key)
{
root[3] = temp;
//cout << "Going Right" << endl;
insertCheck = true;
count++;
}
}
// If the tree has more than one member
else
{
if (count == size) {
size += 25;
Pair** root1 = new Pair * [size];
std::copy(root, root + 1, root1);
}
// Temporary iterator to help move through the tree
int iterator = 1;
// Will iterate until temp is inserted somewhere
while (insertCheck == false /* && temp->key != root[iterator]-
>key*/)

{
if (iterator * 2 > size) {
resize(size);
}
// If temp is less than the iterator and the left one of
the iterator is empty
if (temp->key < root[iterator]->key && root[iterator * 2]
== nullptr)
{
root[iterator * 2] = temp;
//cout << "Going Left" << endl;
insertCheck = true;
count++;
}
// If temp is greater than the iterator and the right one
of the iterator is empty
else if (temp->key > root[iterator]->key && root[(iterator
* 2) + 1] == nullptr)
{
root[(iterator * 2) + 1] = temp;
//cout << "Going Right" << endl;
insertCheck = true;
count++;
}
// If temp is less than the iterator and the left one of
the iterator isn't empty
else if (temp->key < root[iterator]->key) {
iterator = iterator * 2;
if (iterator >= size) {
resize(size);
}
//cout << "Going Left" << endl;
}
// If temp is greater than the iterator and the right one
of the iterator isn't empty
else if (temp->key > root[iterator]->key)
{
iterator = (iterator * 2) + 1;
if (iterator >= size) {
resize(size);
}
//cout << "Going Right" << endl;
}
}
}
return insertCheck;
}
void resize(int argSize) {
while (argSize >= size) {
size = size * 2;
Pair** newRoot = new Pair * [size] {};
memcpy(newRoot, root, size / 2 * sizeof(Pair*));
memset(newRoot + (size / 2), 0, (size - (size / 2)) * sizeof
(Pair*));
delete[] root;
root = newRoot;
}
return;
}
/*
* Removes the nodes if it contains the given item
*/
void remove(const KeyComparable& key) {
removeHelper(key, 1);
}
void removeHelper(const KeyComparable& key, int index) {
// Move throught the Tree based on the key's value
while (index < size && root[index] != nullptr && key != root
[index]->key) {
(root[index]->key < key) ? index = (index * 2) + 1 : index =
(index * 2);
}
// If the Index is Outside the Tree
if (index >= size) {
return;
}
// Find the successor's Index by moving to the right subtree and
finding its minimum value
int successorIndex = findSuccessor((index * 2) + 1);
// Recursively goes through the tree finding each of the nodes
successor's
// or Predecessors and moving them up
if (successorIndex < size && root[successorIndex] != nullptr) {
root[index] = root[successorIndex];
removeHelper(root[successorIndex]->key, successorIndex);
}
else if (successorIndex < size && root[successorIndex] == nullptr)
{
if (index * 2 < size && root[index * 2] != nullptr) {
root[index] = root[index * 3];
removeHelper(root[index * 2]->key, index * 2);
}
else {
root[index] = nullptr;
count--;
}
}
else {
root[index] = nullptr;
count--;
}
}
int findSuccessor(int index) {
if (index * 2 < size && root[index * 2] != nullptr) {
return findSuccessor(index * 2);
}
else {
return index;
}
}
int getSize() {
return size;
}
int getCount() {
return count;
}
}; // end of BinarySearchTree class
