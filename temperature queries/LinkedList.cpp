#include <iostream>
#include <string>
#include "LinkedList.h"
#include "Node.h"
using namespace std;

LinkedList::LinkedList() 
	: head(nullptr), tail(nullptr)
{
	// Implement this function
}

LinkedList::~LinkedList() {
	// Implement this function
	this->clear();
}

LinkedList::LinkedList(const LinkedList& source) 
	: head(nullptr), tail(nullptr) //**
{
	// Implement this function
	if (source.head == nullptr) {
		head = nullptr;
		tail = nullptr;
	}
	else {
		head = new Node(source.head->data.id, source.head->data.year, source.head->data.month, source.head->data.temperature);
		Node* current = head;
		Node* currSource = source.head;
		while (currSource != source.tail) {
			current->next = new Node(currSource->next->data.id, currSource->next->data.year, currSource->next->data.month, currSource->next->data.temperature);
			currSource = currSource->next;
			current = current->next;
		}
		tail = current;
	}
}

LinkedList& LinkedList::operator=(const LinkedList& source) {
	// Implement this function
	if (head) {
		delete head;
	}
	*this = LinkedList(source);
	return *this;
}

void LinkedList::insert(string location, int year, int month, double temperature) { 
	// Implement this function
	Node* insertedNode = new Node(location, year, month, temperature);
	Node* pCurrent = head;
	Node* pPrevious = nullptr;
	// if empty linked list
	if (head == nullptr) {
		head = insertedNode;
		tail = insertedNode;
		return;
	}
	while(pPrevious != tail) {
		if ((*insertedNode) < (*pCurrent)) {
			if (pPrevious != nullptr) {
				pPrevious->next = insertedNode;
				insertedNode->next = pCurrent;

			}
			// if insertedNode needs to be at beginning
			else if (pPrevious == nullptr) {
				insertedNode->next = pCurrent;
				head = insertedNode;
			}
			return;
		}
		pPrevious = pCurrent;
		pCurrent = pCurrent->next;
	}
	tail->next = insertedNode;
	tail = insertedNode;
	return;
}

void LinkedList::clear() {
	// Implement this function
	Node* pCurrent = head;
	Node* pTemp = nullptr;
    while (pCurrent != nullptr) {
        pTemp = pCurrent->next; // Temp grab next node's address
        delete pCurrent;
        pCurrent = pTemp;
    }
	head = nullptr;
	tail = nullptr;
}

Node* LinkedList::getHead() const {
	// Implement this function it will be used to help grade other functions
	return head;
}

string LinkedList::print() const {
	string outputString;
	// Implement this function
	Node* pCurrent = head;
    while (pCurrent != nullptr)
    {
		outputString.append(pCurrent->data.id);
		outputString.append(" ");
		outputString += to_string(pCurrent->data.year);
		outputString.append(" ");
		outputString += to_string(pCurrent->data.month);
		outputString.append(" ");
		string strTemp = to_string(pCurrent->data.temperature);
		while (strTemp[strTemp.size() - 1] == '0' || strTemp[strTemp.size() - 1] == '.') {
			strTemp.erase(prev(strTemp.end()));
		}
		outputString.append(strTemp);
		outputString.append("\n");
		pCurrent = pCurrent->next;
    }
	return outputString;
}

ostream& operator<<(ostream& os, const LinkedList& ll) {
	/* Do not modify this function */
	os << ll.print();
	return os;
}
