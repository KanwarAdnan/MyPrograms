/*
    Doubly LinkedList Header File : Made by Kanwar Adnan
    List of Methods :
        1)  isEmpty()
        2)  isIndex()
        3)  insertAtBeginning(int value)
        4)  insertAtLast(int value)
        5)  removeFirst()
        6)  removeLast()
        7)  insertAtId(int id, int value)
        8)  removeAtId(int id)
        9) getLength()
        10) getFirst()
        11) getLast()
        12) getElementById(int id)
        13) getElementByValue(int value)
        14) print()
        15) printRev()
        16) getFirstElement()
        17) getLastElement()
        18) getNodeById(int id)
*/
#include <iostream>
using namespace std;

class Node{
private:
    int data;
    Node * next;
    Node * prev;
public:
    Node() : data(0), next(NULL), prev(NULL) {}
    Node(int data, Node * next = NULL , Node * prev = NULL){
        setData(data);
        setNext(next);
        setPrev(prev);
    }
    int  getData()               { return this->data; }
    void setData(int data)      { this->data = data; }
    Node * getNext()            { return next; }
    void setNext(Node * next)   { this->next = next; }
    Node * getPrev()            { return prev; }
    void setPrev(Node * prev)   { this->prev = prev; }
};

class Doubly{
private:
    Node * head;
    Node * last;
    int length;
public:
    Doubly() : length(0) , head(NULL) {}
    bool isEmpty()               { return (head == NULL); }
    bool isIndex(int index)      { return ( (index <= length) && (index > 0) ); }
    Node * getFirstNode()        { return head; }
    Node * getLastNode()         { return last; }
    int getLength()              { return length; }
    int getFirstElement()        { return getFirstNode()->getData(); }
    int getLastElement()         { return getLastNode()->getData(); }

    int getElementById(int index){
        Node * temp = getNodeById(index);
        if (temp != NULL)
            return temp->getData();
        return -9999;
    }

    void insertAtBeginning(int value){
        Node * temp = new Node(value);
        temp->setNext(head); // prev will be null already
        head = temp;
        length++;
        if (isEmpty()){
            last = temp;
        }
    }

    void insertAtLast(int value){
        if (isEmpty()){
            insertAtBeginning(value);
            return;
        }
        Node * temp = new Node(value); // new last
        Node * temp2 = getNodeById(length); // last
        temp2->setNext(temp);
        temp->setPrev(temp2);
        length++;
        last = temp; // updating the last
    }

    void insertAt(int index, int value){
        if (isIndex(index)){
            if (index == 1){
                insertAtBeginning(value);
                return;
            }
            Node * temp = new Node(value);
            Node * current = getNodeById(index);
            current->getPrev()->setNext(temp);
            temp->setNext(current);
            temp->setPrev(current->getPrev());
            current->setPrev(temp);
            length++;
        }
    }

    // Incomplete
    void deleteElement(int value){
        if (!isEmpty()){
            Node * temp = head;
            while (temp != NULL){
                if (temp->getData() != value){
                    temp->getPrev()->setNext(temp->getNext());
                    temp->getNext()->setPrev(temp->getPrev());
                    delete temp;
                    length--;
                    return;
                }
                temp = temp->getNext();
            }
        }
    }

    void removeAt(int index){
        if (isIndex(index)){
            if (index == 1){
                removeFirst();
                return;
            }
            if (index == length){
                removeLast();
                return;
            }
            Node * current = getNodeById(index);
            current->getPrev()->setNext(current->getNext());
            current->getNext()->setPrev(current->getPrev());
            delete current;
            length--;
        }
    }

    void removeFirst(){
        if (isEmpty()){
            return;
        }
        if (length == 1){
            delete head;
            head = NULL;
            delete last;
            last = NULL;
        }
        else {
            Node * temp = head;
            head = head->getNext();
            delete temp;
        }
        length--;
    }

    void removeLast(){
        if (isEmpty()){
            return;
        }
        if (length == 1){
            removeFirst();
            return;
        }
        Node * temp = last->getPrev();
        temp->setNext(NULL);
        delete last;
        length--;
        last = temp;
    }

    Node * getNodeById(int index){
        if ((!isEmpty()) && (isIndex(index))){
            Node * current = head;
            int count = 1;
            while (count != index){
                current = current->getNext();
                count++;
            }
            return current;
        }
        return NULL;
    }

    void print(){
        Node * temp = head;
        cout << "NULL<->";
        while (temp != NULL){
            cout << temp->getData() << "<->";
            temp = temp->getNext();
        }
        cout << "NULL\n";
    }

    void printRev(){
        Node * temp = last;
        cout << "NULL";
        while (temp != NULL){
            cout << "<->" << temp->getData();
            temp = temp->getPrev();
        }
        cout << "<->NULL\n";
    }
};

int main(){
    Doubly d;
    int count = 1;
    while (count <= 5){
        d.insertAtLast(count);
        count++;
    }
    cout << "Printing Doubly Linked List\n\t" ;
    d.print();
    cout << "Printing Doubly Linked List in reverse order\n\t" ;
    d.printRev();
    cout << endl;
    cout << "Length : " << d.getLength() << endl;
    cout << "First Element : " << d.getFirstElement() << endl;
    cout << "Last Element : " << d.getLastElement() << endl;

    cout << "\nRemoving first , last, 3rd element and Adding 50 at 2nd index.\n\t";
    d.removeFirst();
    d.removeLast();
    d.removeAt(3);
    d.insertAt(2,50);
    d.print();

    cout << endl;
    cout << "Length : " << d.getLength() << endl;
    cout << "First Element : " << d.getFirstElement() << endl;
    cout << "Last Element : " << d.getLastElement() << endl;
}
