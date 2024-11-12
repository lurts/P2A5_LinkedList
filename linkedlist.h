#pragma once

class LinkedList{
private:
    struct Node {
        int data;
        Node* next;
        Node(int value) : data(value), next(nullptr) {}
    };

    Node* head;

public:
    // Constructor
    // Initialisiert eine leere Liste (nullptr als head)
    LinkedList() :
        head(nullptr) 
        {};
    // Destructor, gibt Memory wieder frei
    // startet bei "head" und l�scht alle elemente der Liste (l�uft bis das n�chste element nullptr ist)
    ~LinkedList() {
        Node* next;

        while (head != nullptr) {
            next = head->next;
            delete head;
            head = next;
        }
    }

    // Gibt die Anzahl an Elementen in der Liste zur�ck
    unsigned int size() const;

    // Gibt den Pointer zum Head der Liste zur�ck
    // Node* getHead() const;

    // Gibt den Wert an einem bestimmten Index zur�ck
    int at(unsigned int index) const;

    // H�ngt ein neues Element hinten an
    void append(int nvalue);

    // Sortiert ein neues Element in die Liste ein
    void sortAppend(int nvalue);
};

// Gibt die Summe aller Elemente zur�ck
int sum(const LinkedList& list);