/*
    LinkedList Header File : Made by Kanwar Adnan
    List of Methods :
        1)  isEmpty()
        2)  isIndex()
        3)  isValid()
        4)  insertAtBeginning(int value)
        5)  insertAtLast(int value)
        6)  removeFirst()
        7)  removeLast()
        8)  insertAtId(int id, int value)
        9)  removeAtId(int id)
        10) getLength()
        11) getFirst()
        12) getLast()
        13) getElementById(int id)
        14) getElementByValue(int value)
        15) getMiddle()
        16) getNodeIdByValue(int value)
        17) deleteByValue(int value)
        18) doesExist(int value)
        19) doesExistRet(int value , int * index)
        20) reverse()
        21) print()
        22) print(int x)
        22) printWithIndex()
        23) printRev(Node * current)
        24) getFirstElement()
        25) getLastElement()
        26) getNodeById(int id)
        27) swapElements(int x , int y)
        28) swap(int id1 , int id2)
        29) sort()
        30) sortNodes()
        31) removeDuplicates()
        32) merge(LinkedList list)
        33) mergeSort(LinkedList list)
        34) copy(LinkedList list)
        35) deleteList()
        36) insertAtBeginning(int * arr , int size)
        37) insertAtLast(int * arr , int size)
        38) removeAtId(int * arr , int size) Beta Version works for ascendingly sorted array
        39) deleteByValue(int * arr , int size)
        40) toArray()
*/
#include <iostream>
using namespace std;
#include <time.h>
class Node{
public:
    int data;
    Node * next;
    Node() : data(0), next(NULL) {}

    Node(int data, Node * next = NULL){
        setData(data);
        setNext(next);
    }
    Node * getNext()            { return next; }
    int getData()               { return data; }
    void setNext(Node * next)   { this->next = next; }
    void setData(int data)      { this->data = data; }
};

class LinkedList{
private:
    Node * head;
    Node * last;
    int length;
public:
    LinkedList() : length(0) , head(NULL) {}
    bool isEmpty()              { return (head == NULL); }
    bool isIndex(int index)     { return ( (index <= length) && (index > 0) ); }
    bool isValid(int index)     { return ( (!isEmpty()) && (isIndex(index)) ); }
    Node * getFirst()           { return head; }
    Node * getLast()            { return last; }
    int getFirstElement()       { return getFirst()->getData(); }
    int getLastElement()        { return getLast()->getData(); }
    int getLength()             { return length; }

    // Insertion Methods ------------------------------

    void insertAtBeginning(int value){
        Node * temp = new Node(value);
        if (isEmpty())
            last = temp;
        temp->setNext(head);
        head = temp;
        length++;
    }

    void insertAtLast(int value){
        Node * temp = new Node(value);
        if (isEmpty())
            head = temp;
        else {
            last->setNext(temp);
        }
        last = temp;
        length++;
    }
    
    void insertAtBeginning(int * arr , int size){
        if (size > 0){
            for ( int i = size - 1 ; i >= 0 ; i--){
                insertAtBeginning(arr[i]);
            }
        }
    }

    void insertAtLast(int * arr , int size){
        if (size > 0){
            for ( int i = 0 ; i < size ; i++){
                insertAtLast(arr[i]);
            }
        }
    }

    void insertAtId(int id,int value){
        if (!isEmpty() && isIndex(id) ){
            if (id == 1)
                insertAtBeginning(value);
            else {
                Node * temp = new Node(value);
                Node * prevId = getNodeById(id-1);
                Node * currentId = prevId->getNext();
                prevId->setNext(temp);
                temp->setNext(currentId);
                length++;
            }
        }
        // Comment it if does not need this
        else if (!isEmpty() && (id > length) ){
            insertAtLast(value);
        }
     }

    // Displaying Methods ------------------------------

    void print(){
        Node * temp = head;
        while ( temp != NULL){
            cout << temp->getData() << "->";
            temp = temp->getNext();
        }
        cout << "NULL\n";
    }

    void print(int x){
        Node * temp = head;
        int count = 1;
        if (x<length){
            for(int i = 1 ; i != x ; i++){
                cout << temp->getData() << "->";
                temp = temp->getNext();
            }
        }
        else {
            print();
        }
    }


    void printWithIndex(){
        Node * temp = head;
        int index = 1;
        while (temp != NULL){
            cout << index << " : " << temp->getData() << '\n';
            index++;
            temp = temp->getNext();
        }
        cout << '\n';
    }

    void printRev(Node * current){
        if (current == NULL)
            return;
        printRev(current->getNext());
        cout << "<-" << current->getData();
    }
    
    void printRev(){
        cout << "NULL";
        printRev(getFirst());
        cout << endl;
    }


    // deletion Methods ------------------------------

    void removeFirst(){
        if (isEmpty())
            return;
        else if (head->getNext() == NULL) {
            delete head;
            head = NULL;
            last = NULL;
        }
        else {
            Node * temp = head->getNext();
            delete head;
            head = temp;
        }
        length--;
    }

    void removeLast(){
        if (isEmpty())
            return;
        else if(head->getNext() == NULL){
            delete head;
            head = NULL;
            last = NULL;
        }
        else {
            Node * temp = getNodeById( length - 1 );
            Node * temp2 = temp->getNext();
            delete temp2;
            temp->setNext(NULL);
            last = temp;
        }
        length--;
    }
    
    // It's also same as deleteElementById
    void removeAtId(int id){
        if (!isEmpty() && isIndex(id)){
            if (id == 1){
                removeFirst();
            }
            else if (id == length){
                removeLast();
            }
            else {
                Node * prevId = getNodeById(id-1);
                Node * currentId = prevId->getNext();
                Node * nextId = currentId->getNext();
                prevId->setNext(nextId);
                delete currentId;
                length--;
            }
        }
    }
    // Beta Version
    void removeAtId(int * arr , int size){
        if (size > 0){
            int constant = 0;
            for (int i = 0 ; i < size ; i++){
                removeAtId(arr[i]-constant);
                constant++;
            }
        }
    }

    void deleteByValue(int value){
        if (!isEmpty()){
            if ( (head->getData() == value) )
                removeFirst();
            else {
                Node * temp = head;
                Node * temp2 = head->getNext();
                while (temp2->getNext() != NULL){
                    if (temp2->getData() == value){
                        Node * next = temp2->getNext();
                        temp->setNext(next);
                        delete temp2;
                        length--;
                        return;
                    }
                    temp2 = temp2->getNext();
                    temp = temp->getNext();
                }
                // If the last member is to delete
                if (temp2->getData() == value){
                    removeLast();
                }
            }
        }
    }
    
    void deleteByValue(int * arr , int size){
        if (size > 0){
            for (int i = 0 ; i < size ; i++){
                deleteByValue(arr[i]);
            }
        }
    }

    // Getters ------------------------------

    int getMiddle(){
        int mid = 0;
        if (length % 2 == 0)
            mid = (length / 2);
        else
            mid = (length / 2) + 1;
        return getNodeById(mid)->getData();
    }

    int getElementById(int id){
        Node * temp = getNodeById(id);
        if (temp != NULL)
            return temp->getData();
        return -9999;
    }

    Node * getNodeById(int id){
        if ((!isEmpty()) && (isIndex(id))){
            Node * temp = head;
            int count = 1;
            while (count != id){
                temp = temp->getNext();
                count++;
            }
            return temp;
        }
        return NULL;
    }


    Node * getNodeByValue(int value){
        if (!isEmpty()){
            Node * temp = head;
            while (temp != NULL){
                if (value == temp->getData())
                    return temp;
                temp = temp->getNext();
            }
        }
        return NULL;
    }

    int getNodeIdByValue(int value){
        if (!isEmpty()){
            Node * temp = head;
            int count = 1;
            while (temp != NULL){
                if (value == temp->getData())
                    return count;
                count++;
                temp = temp->getNext();
            }
        }
        return -9999;
    }

    // Some More Methods ------------------------------

    bool doesExist(int value){
        Node * temp = head;
        while (temp != NULL){
            if (value == temp->getData())
                return true;
            temp = temp->getNext();
        }
        return false;
    }

    // This method returns the index of the element if it exists
    Node * doesExistRet(int value, int* index){
        Node * temp = head;
        int count = 1;
        while (temp != NULL){
            if (value == temp->getData()){
                *index = count;
                return temp;
            }
            temp = temp->getNext();
            count++;
        }
        *index = -1; // -1 incase element not found
        return NULL;
    }

    void swapElements(int x, int y){
        // Nothing to do if x and y are same
        if (x == y)
            return;
     
        // Search for x (keep track of prevX and CurrX
        Node *prevX = NULL, *currX = head;
        while (currX && currX->data != x) {
            prevX = currX;
            currX = currX->next;
        }
     
        // Search for y (keep track of prevY and CurrY
        Node *prevY = NULL, *currY = head;
        while (currY && currY->data != y) {
            prevY = currY;
            currY = currY->next;
        }
     
        // If either x or y is not present, nothing to do
        if (currX == NULL || currY == NULL)
            return;
     
        // If x is not head of linked list
        if (prevX != NULL)
            prevX->next = currY;
        else // Else make y as new head
            head = currY;
     
        // If y is not head of linked list
        if (prevY != NULL)
            prevY->next = currX;
        else // Else make x as new head
            head = currX;
     
        // Swap next pointers
        Node* temp = currY->next;
        currY->next = currX->next;
        currX->next = temp;     
    }
    
    void sort(){
        if (!isEmpty() && length > 1){
            Node * temp = head;
            Node * temp2 = head;
    
            for (int i = 0; i < length; i++) {
                for (int j = 0; j < length - 1; j++) {
                    if (temp->getData() < temp2->getData()) {
                        int tempVal = temp->getData();
                        temp->setData(temp2->getData());
                        temp2->setData(tempVal);
                    }
                    temp2 = temp2->getNext();
                }
                temp2 = head;
                temp = head->getNext();
                for (int k = 0; k < i; k++) {
                    temp = temp->getNext();
                }
            }
        }
    }

    // Mine but inspired from above code
    void swap(int id1, int id2){
        if (isIndex(id1) && isIndex(id2)){
            if (id1 == id2)
                return;
            else {
                Node * prevId1 = NULL , * currId1 = head;
                Node * prevId2 = NULL , * currId2 = head;
                
                int count = 1;
                while (count != id1){
                    prevId1 = currId1;
                    currId1 = currId1->getNext();
                    count++;
                }
                
                count = 1;
                while (count != id2){
                    prevId2 = currId2;
                    currId2 = currId2->getNext();
                    count++;
                }
                
                if (currId1 == NULL || currId2 == NULL){
                    return;
                }
                
                if (prevId1 != NULL){
                    prevId1->setNext(currId2);
                }
                else {
                    head = currId2;
                }

                if (prevId2 != NULL){
                    prevId2->setNext(currId1);
                }
                else {
                    head = currId1;
                }
                Node * nextId2 = currId2->getNext();
                currId2->setNext(currId1->getNext());
                currId1->setNext(nextId2);
            }
        }
    }

    // inserting at last takes 1 step
    void removeDuplicates(){
        LinkedList l1;
        Node * toDelete = head;
        while (head != NULL){
            if (!l1.doesExist(head->getData()))
                l1.insertAtLast(head->getData());
            toDelete = head;
            head = head->getNext();
            delete toDelete;
        }
        head = l1.getFirst();
        length = l1.getLength();
        last = l1.getLast();
    }
    
    // this will join two LinkedLists [changes will reflect]
    
    void merge(LinkedList list){
        if (isEmpty()){
            if (!list.isEmpty()){
                head = list.getFirst();
                length += list.getLength();
            }
        }
        else {
            if (list.isEmpty())
                return;
            else {
                Node * temp = getNodeById(length); // last node
                temp->setNext(list.getFirst());
                length += list.getLength();
            }
        }
    }
    
    void copy(LinkedList list){
        if (isEmpty()){
            if (!list.isEmpty()){
                // again flexing for loop :D
                for (Node * temp2 = list.getFirst() ; temp2 != NULL ; temp2 = temp2->getNext()){
                    insertAtLast(temp2->getData());
                }
            }
        }
        else {
            if (list.isEmpty())
                return;
            else {
                Node * temp = getNodeById(length); // last node
                for (Node * temp2 = list.getFirst() ; temp2 != NULL ; temp2 = temp2->getNext()){
                    insertAtLast(temp2->getData());
                }
            }
        }
    }

    void mergeSort(LinkedList list){
        merge(list);
        sort();
    }
    
    // i know it's not good but it works
    // i wanted to do it so i did
    void sortNodes(){
        Node * temp = head;
        Node * temp2 = head->getNext();
        int tempId = 1;
        int temp2Id = 1;
        LinkedList l1 , l2;
        while ( temp != NULL ){
            while ( temp2 != NULL ){
                if ( (temp->getData()) < (temp2->getData()) ){
                    l1.insertAtLast(tempId);
                    l2.insertAtLast(temp2Id);
                    //swap(tempId,temp2Id);
                }
                temp2 = temp2->getNext();
                temp2Id++;
            }
            tempId++;
            temp = temp->getNext();
            temp2 = head;
            temp2Id = 1;
        }
        Node * temp3 = l1.getFirst();
        Node * temp4 = l2.getFirst();
        
        while (temp3 != NULL){
            swap(temp3->getData(),temp4->getData());
            temp3 = temp3->getNext();
            temp4 = temp4->getNext();
        }
        l1.deleteList();
        l2.deleteList();
    }
    
    void deleteList(){
        if (!isEmpty()){
            Node * prev = NULL;
            Node * temp = head;
            while (temp != NULL){
                prev = temp;
                temp = temp->getNext();
                delete prev;
            }
            head = NULL;
        }
    }

    void reverse(){
        if (!isEmpty()){
            if (length == 1){
                return;
            }
            last = head; // reserving the last
            Node * previous = NULL;
            Node * current = head;
            Node * next = NULL;
            while(current != NULL){
                next = current->getNext();
                current->setNext(previous);
                previous = current;
                current = next;
            }
            head = previous;
        }
    }
    
    int * toArray(){
        if (!isEmpty()){
            int * arr = new int[length];
            int count = 0;
            Node * temp = head;
            while(temp != NULL){
                arr[count] = temp->getData();
                temp = temp->getNext();
                count++;
            }
            return arr;
        }
        return NULL;
    }
    
    void printArray(int * arr , int size){
        for (int i = 0 ; i < size ; i++){
            cout << arr[i] << " ";
        }
        cout << "\n";
    }
    
};

int main(){
    LinkedList l1;
    int arr[5] = {1,2,3,4,5};
    l1.insertAtLast(1);
    l1.insertAtLast(2);
    l1.insertAtBeginning(arr,5);
    l1.print();
}

/*
int main(){
    LinkedList * l1 = new LinkedList;
    clock_t tStart = clock();
    for (int i = 1 ; i != 100000000 ; i = i + 1)
        l1->insertAtLast(i);
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    clock_t tStart2 = clock();
    l1->reverse();
    printf("Time taken: %.2fs\n", (double)(clock() - tStart2)/CLOCKS_PER_SEC);
    l1->print(5);
}
/*
    Time taken: 4.59s
    Time taken: 0.61s
    99999999->99999998->99999997->99999996->
*/
