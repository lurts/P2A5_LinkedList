#include "linkedlist.h"
#include <stdexcept> // f�r std::out_of_range

unsigned int LinkedList::size() const {
	unsigned int count = 0;
	Node* current = head;

	// Listenelemente durchlaufen und mitz�hlen bis am Ende (nullptr) angekommen
	while (current != nullptr) {
		count++;
		current = current->next;
	}

	return count;
}

//LinkedList::Node* LinkedList::getHead() const {
//	return head;
//}

int LinkedList::at(unsigned int index) const {
	// Wird kein korrekter index (index < 0 oder index > list.size()) �bergeben wird ne exception geworfen. 
	// programm h�lt an und es kommen keine unerwarteten werte zur�ck (besser als "return INT_MIN"?)
	if (index >= size()) {
		//throw std::out_of_range("Index is out of range!");
        return -1;
	}

	Node* current = head;
	int currentIndex = 0;

	// liste durchlaufen bis entweder das ende oder der gefragte index erreicht ist
	while (current != nullptr && currentIndex < index) {
		current = current->next;
		currentIndex++;
	}

	return current->data;
}

// H�ngt ein neues element stumpf hinten an die liste an
void LinkedList::append(int nvalue) {
	//neue Node mit �bergebenen Wert anlegen
	Node* newNode = new Node(nvalue);

	// Pr�fen ob die liste leer ist
	// bei leerer liste wird die neue Node einfach zum head
	if (head == nullptr) {
		head = newNode;
		return;
	}

	// ist die liste nicht leer muss das letzte element gefunden werden
	Node* current = head;
	while (current->next != nullptr) {
		current = current->next;
	}
	// das letzte element ist jetzt das "current" element

	// element anh�ngen
	current->next = newNode;
	return;
}

void LinkedList::sortAppend(int nvalue) {
	// neue Node mit �bergebenen Wert anlegen
	Node* newNode = new Node(nvalue);

	// Pr�fen ob die liste leer ist
	// bei leerer liste wird die neue Node einfach zum head
	if (head == nullptr) {
		head = newNode;
		return;
	}

	// ist das erste element schon gr��er oder gleich dem neuen wird das neue element als head eingef�gt
	if (nvalue <= head->data) {
		newNode->next = head;
		head = newNode;
		return;
	}

	// liste durchlaufen bis ein gr��eres element oder das listenende gefunden wurde
	Node* current = head;
	while (current->next != nullptr && nvalue > current->next->data) {
		current = current->next;
	}

	// neue node einf�gen und pointer aktualisieren
	newNode->next = current->next;
	current->next = newNode;
	return;
}

int sum(const LinkedList& list) {
	int sum = 0;
	unsigned int listSize = list.size();	// die anzahl der elemente in der liste holen

	// die liste komplett durchlaufen und alle werte aufaddieren
	for (unsigned int i = 0; i < listSize; ++i) {
		sum += list.at(i);
	}

	return sum;
}