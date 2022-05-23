#ifndef INC_22S_FLIGHT_PLANNER_DSLINKEDLIST_H
#define INC_22S_FLIGHT_PLANNER_DSLINKEDLIST_H

#include "Node.h"
#include <stdexcept>

template <class T>
class DLList{
public:
    struct Iterator{    //standard iterator set up, handles most basic functions of a basic iterator
        explicit Iterator(Node<T>* pssdDataPtr){ ptr = pssdDataPtr;}

        T& operator*() const     { return ptr->get(); }
        Iterator& operator++()   { ptr = ptr->get_next(); return *this; }
        Iterator operator++(int) { Iterator temp = *this; ptr = ptr->get_next(); return temp; }
        Iterator& operator--()   { ptr = ptr->get_prev(); return *this; }
        Iterator operator--(int) { Iterator temp = *this; ptr = ptr->get_prev(); return temp; }
        friend bool operator== (const Iterator& a, const Iterator& b) { return (a.ptr == b.ptr); }
        friend bool operator!= (const Iterator& a, const Iterator& b) { return (a.ptr != b.ptr); }

        Node<T>* ptr;
    };
    Iterator begin() const { return Iterator(dummy->get_next()); }  //dummy->get_next() is the first element in *this, AKA the head of the list
    Iterator last() const  { return Iterator(dummy->get_prev()); }
    Iterator end() const   { return Iterator(dummy); }  //passes dummy as the "end()" of *this because dummy is the last actual node in *this, but it is not defined with a data value, so the user cannot read from it

    DLList();
    DLList(const DLList<T>&);             //O(n) | fills *this with a deep copy of all DSNodes from the passed DLList
    DLList<T>& push_back(const T&);             //O(1) | appends the passed variable to the end *this DSlinkedList
    DLList<T>& push_front(const T&);            //O(1) | appends the passed variable to the front *this DSlinkedList
    T pop_back();                                     //O(1) | removes the back-most variable from *this DSlinkedList
    T pop_front();                                    //O(1) | removes the front-most variable from *this DSlinkedList
    T& peek_back()   { if(eleCount == 0){ throw std::invalid_argument("Invalid call to Node<T>& peek_back() | Size of Linked List is 0"); } return tail->get(); }
    T& peek_front()  { if(eleCount == 0){ throw std::invalid_argument("Invalid call to Node<T>& peek_front() | Size of Linked List is 0"); } return head->get(); }
    int size() const { return eleCount; }             //O(1)
    bool is_empty() const { return (eleCount == 0); } //O(1)
    DLList<T>& clear();           //O(n) | clears all Node instances in *this LinkedList and resets all *this data-members
    DLList<T>& erase_at(int);     //O(n) | removes the Node at the given subscript from *this
    Iterator erase_at(Iterator);  //O(1)
    Node<T>* erase_at(Node<T>*);  //O(1)
    T& operator [](int);                //O(n) | returns the data, by reference, found in the Node at the given subscript
    T read_at(int) const;               //O(n) | returns a copy of the data found in the Node at the given subscript
    DLList<T>& operator =(const DLList<T>&);    //O(n) | clears *this DLList, and fills *this with a deep copy of all DSNodes from the passed DLList
    DLList<T> &insert_after(int, const T&);           //O(n) | inserts the passed data after the Node found at the given subscript
    DLList<T> &insert_before(int, const T&);          //O(n) | inserts the passed data before the Node found at the given subscript
    bool contains(const T&);                                //O(n) | traverses the DSNodes within *this DLList until it reaches a Node with an equal data value
    ~DLList();                    //O(n)

private:
    Node<T>* dummy = nullptr; //using a dummy node to remove the need to constantly check for nullptr related edge cases
    Node<T>* head = nullptr;  //the dummy node is both at the back of the list and at the front
    Node<T>* tail = nullptr;
    int eleCount = 0;           //used to count the number of DSNodes in *this
};

template<class T>
DLList<T>::DLList() {
    dummy = new Node<T>();    //creating a dummy node
    dummy->set_prev(dummy);     //when the list is empty, the dummy node will point to itself for next and prev
    dummy->set_next(dummy);
    head = dummy;               //the 'head' and 'tail' point to 'dummy' to follow the rule that 'head' points 'dummy.next', and 'tail' points to 'dummy.prev'
    tail = dummy;
    eleCount = 0;
}

template<class T>
DLList<T> &DLList<T>::push_back(const T& passed) {
    auto* newNode = new Node<T>(passed);  //creating a new Node on the heap
    dummy->get_prev()->set_next(newNode);   //change the 'next' pointer of the node in front of dummy (the current tail node) to point to the new Node
    newNode->set_prev(dummy->get_prev());   //change the 'prev' pointer of the new Node to point to the Node in front of dummy
    dummy->set_prev(newNode);               //change the 'prev' pointer of dummy to point to the new Node
    newNode->set_next(dummy);               //change the 'next' pointer of the new Node to point to dummy
    head = dummy->get_next();               //updated 'head' and 'tail' to be their proper DSNodes
    tail = dummy->get_prev();
    eleCount++;     //increasing eleCount to account for the increased length due to the inclusion of the new Node
    return *this;
}

template<class T>
DLList<T> &DLList<T>::push_front(const T& passed) {
    auto* newNode = new Node<T>(passed);  //creating a new Node on the heap
    newNode->set_next(dummy->get_next());   //change the 'next' pointer of the new node to point to the node after dummy (the current head node)
    dummy->get_next()->set_prev(newNode);   //change the 'prev' pointer of the node after dummy (the current head node) to point to the new Node
    dummy->set_next(newNode);               //change the 'next' pointer of dummy to point to the new Node
    newNode->set_prev(dummy);               //change the 'prev' pointer of the new Node to point to dummy
    head = dummy->get_next();               //updated 'head' and 'tail' to be their proper DSNodes
    tail = dummy->get_prev();
    eleCount++;     //increasing eleCount to account for the increased length due to the inclusion of the new Node
    return *this;
}

template<class T>
T DLList<T>::pop_back() {
    if(eleCount == 0)       //check is length of *this is 0
        throw std::invalid_argument("Invalid call to Node<T> DLList<T>::pop_back() | Size of Linked List is 0");

    T toReturn = tail->read();              //saving the value saved in the current tail so that we can return a copy of it
    tail->get_prev()->set_next(dummy);      //change the 'next' pointer of the node in front of the current tail to point to dummy | starting the removal process
    dummy->set_prev(tail->get_prev());      //change the 'prev' pointer of dummy to the node in from of the current tail pointer
    delete tail;                            //all ties are cut from the 'tail' node, it can be deleted
    tail = dummy->get_prev();               //update 'tail'
    eleCount--;                             //decrement the length variable
    return toReturn;                        //return the save value of the now popped node
}

template<class T>
T DLList<T>::pop_front() {
    if(eleCount == 0)
        throw std::invalid_argument("Invalid call to Node<T> DLList<T>::pop_front() | Size of Linked List is 0");

    T toReturn = head->read();
    head->get_next()->set_prev(dummy);      //starting the removal process | setting the 'prev' pointer of the node after the head node to dummy
    dummy->set_next(head->get_next());      //setting the 'next' pointer of dummy to the node after the head node
    delete head;                            //all ties to the 'head' node are cut, it can be deleted
    head = dummy->get_next();               //update the 'head' pointer
    eleCount--;                             //decrement the length variable
    return toReturn;
}

template<class T>
DLList<T>::~DLList() {
    if(eleCount > 0){   //if the length of *this is more than 0, then we need to delete all the nodes within *this
        for (Node<T> *ptr = head->get_next(); ptr != dummy; ptr = ptr->get_next())
            delete ptr->get_prev(); //started at the second Node in *this, delete the node before the current node
        delete dummy->get_prev();   //the above loop stops when ptr is dummy, so the node before dummy is never deleted | so we delete it now
    }
    delete dummy;   //finally, we delete the dummy node, which we will always even if *this is empty
}

template<class T>
DLList<T> &DLList<T>::clear() {
    if(eleCount > 0){   //deleted all contents of *this | like the destructor
        for (Node<T> *ptr = head->get_next(); ptr != dummy; ptr = ptr->get_next())
            delete ptr->get_prev();
        delete dummy->get_prev();
    }
    delete dummy;

    dummy = new Node<T>();    //resetting all contents of *this | like the constructor
    dummy->set_prev(dummy);
    dummy->set_next(dummy);
    head = dummy;
    tail = dummy;
    eleCount = 0;
    return *this;
}

template<class T>
DLList<T> &DLList<T>::erase_at(int subscript) {
    if(subscript < 0 || subscript >= eleCount)
        throw std::invalid_argument("Error in DLList<T> DLList<T>::erase_at(int subscript) | invalid subscript value");

    int count = 0;
    Node<T> *ptr = nullptr;
    for (ptr = head; ptr != dummy; ptr = ptr->get_next()){  //finding the Node to erase by incrementing ptr one node at a time for 'subscript' times
        if(subscript == count)
            break;
        count++;
    }

    //the removal process and cutting ties
    //'ptr' is now the node that the user wants to delete
    ptr->get_next()->set_prev(ptr->get_prev()); //changing the 'prev' pointer of the node after 'ptr' to point to the node before 'ptr'
    ptr->get_prev()->set_next(ptr->get_next()); //changing the 'next' pointer of the node before 'ptr' to point to the node after 'ptr'
    head = dummy->get_next();                   //updated 'head' and 'tail' pointer
    tail = dummy->get_prev();
    eleCount--;                                 //decrementing length variable
    delete ptr;
}

template<class T>
bool DLList<T>::contains(const T& toFind) {
    if(eleCount == 0)   //the list contains nothing when it's length is nothing, so it automatically returns false if the list has a length of 0
        return false;

    for (Node<T> *ptr = head; ptr != dummy; ptr = ptr->get_next()){   //increments ptr one node at a time, starting from the 'head' node
        if(toFind == ptr->read())   //if the data 'toFind' is equal to the data found in the 'ptr' node, return true
            return true;
    }
    return false;   //if the algorithm traversed through the whole list and the value was not found, return false
}

template<class T>
T &DLList<T>::operator[](int subscript) {
    if(subscript < 0 || subscript >= eleCount)  //if the passed subscript value is not within the defined bounds of the list, then I throw an error
        throw std::invalid_argument("Error in T& DLList<T>::operator[](int) | invalid subscript value");

    int count = 0;
    for (Node<T> *ptr = head; ptr != dummy; ptr = ptr->get_next()){   //traverse the list a 'subscript' amount of times, one node at a time
        if(subscript == count)
            return ptr->get();  //returns by reference
        count++;                //increment counter variable
    }
}

template<class T>
T DLList<T>::read_at(int subscript) const {
    if(subscript < 0 || subscript >= eleCount)      //bounds checking
        throw std::invalid_argument("Error in T DLList<T>::read_at(int) | invalid subscript value");

    int count = 0;
    for (Node<T> *ptr = head; ptr != dummy; ptr = ptr->get_next()){   //traverse the list a 'subscript' amount of times, one node at a time
        if(subscript == count)
            return ptr->read(); //returns a copy of the data in the current node
        count++;                //increment counter variable
    }
}

template<class T>
DLList<T> &DLList<T>::insert_after(int subscript, const T& passed) {
    if(subscript < 0 || subscript >= eleCount)      //bounds checking
        throw std::invalid_argument("Error in DLList<T> &DLList<T>::insert_after(int) | invalid subscript value");

    int count = 0;
    Node<T> *ptr = nullptr;
    for (ptr = head; ptr != dummy; ptr = ptr->get_next()){  //move ptr through the list a 'subscript' number of times
        if(subscript == count)  //when the count variable and 'subscript' are equal break
            break;
        count++;
    }

    //'ptr' is now the node that the user wants to insert 'passed' after
    auto* toInsert = new Node<T>(passed); //create a new node with the passed value
    toInsert->set_next(ptr->get_next());    //change the 'next' pointer of the new node to the node after 'ptr'
    toInsert->set_prev(ptr);                //change the 'prev' pointer of the new node to 'ptr'
    ptr->get_next()->set_prev(toInsert);    //change the 'prev' pointer of the node after 'ptr' to be the new node
    ptr->set_next(toInsert);                //change the 'next' pointer of 'ptr' to be the new node
    head = dummy->get_next();               //update 'head' and 'tail' pointers of *this
    tail = dummy->get_prev();
    eleCount++;                             //increment length variable of *this
    return *this;
}

template<class T>
DLList<T> &DLList<T>::insert_before(int subscript, const T& passed) {
    if(subscript < 0 || subscript >= eleCount)      //bounds checking
        throw std::invalid_argument("Error in DLList<T> &DLList<T>::insert_before(int) | invalid subscript value");

    int count = 0;
    Node<T> *ptr = nullptr;
    for (ptr = head; ptr != dummy; ptr = ptr->get_next()){
        if(subscript == count)
            break;
        count++;
    }

    auto* toInsert = new Node<T>(passed);     //the difference between insert_before() and insert_after() is the slight differences of changing the 'next' and 'prev' pointer
    toInsert->set_next(ptr);                    //set the 'next' pointer of the new node to 'ptr'
    toInsert->set_prev(ptr->get_prev());        //set the 'prev' pointer of the new node to the node before 'ptr'
    ptr->get_prev()->set_next(toInsert);        //set the 'next' pointer of the node before 'ptr' to point to the new node
    ptr->set_prev(toInsert);                    //set the 'prev' pointer of 'ptr' to point to the new node
    head = dummy->get_next();                   //update 'head' and 'tail'
    tail = dummy->get_prev();
    eleCount++;                                 //increment length variable of *this
    return *this;
}

template<class T>
DLList<T>::DLList(const DLList<T>& passed) {
    dummy = new Node<T>();    //creating a dummy node
    dummy->set_prev(dummy);     //when the list is empty, the dummy node will point to itself for next and prev
    dummy->set_next(dummy);
    head = dummy;               //the 'head' and 'tail' point to 'dummy' to follow the rule that 'head' points 'dummy.next', and 'tail' points to 'dummy.prev'
    tail = dummy;
    eleCount = 0;
    for (auto& it : passed)     //push back every data value in each node in passed into *this
        push_back(it);
}

template<class T>
DLList<T>& DLList<T>::operator=(const DLList<T>& passed) {
    if(&passed == this) //handles self assignment
        return *this;
    clear();            //clears *this and resets all of *this' data
    for (const auto& it : passed) { //push back every data value in each node in passed into *this
        push_back(it);
    }
    return *this;
}

template<class T>
typename DLList<T>::Iterator DLList<T>::erase_at(DLList<T>::Iterator iterator) {
    Node<T> *ptr = iterator.ptr;

    Iterator toReturn(ptr->get_next());

    //the removal process and cutting ties
    //'ptr' is now the node that the user wants to delete
    ptr->get_next()->set_prev(ptr->get_prev()); //changing the 'prev' pointer of the node after 'ptr' to point to the node before 'ptr'
    ptr->get_prev()->set_next(ptr->get_next()); //changing the 'next' pointer of the node before 'ptr' to point to the node after 'ptr'
    head = dummy->get_next();                   //updated 'head' and 'tail' pointer
    tail = dummy->get_prev();
    eleCount--;                                 //decrementing length variable
    delete ptr;

    return toReturn;
}

template<class T>
Node<T> * DLList<T>::erase_at(Node<T> *node) {
    Node<T>* toReturn = node->get_next();

    //the removal process and cutting ties
    //'node' is now the node that the user wants to delete
    node->get_next()->set_prev(node->get_prev()); //changing the 'prev' pointer of the node after 'node' to point to the node before 'node'
    node->get_prev()->set_next(node->get_next()); //changing the 'next' pointer of the node before 'node' to point to the node after 'node'
    head = dummy->get_next();                   //updated 'head' and 'tail' pointer
    tail = dummy->get_prev();
    eleCount--;                                 //decrementing length variable
    delete node;

    return toReturn;
}

#endif //INC_22S_FLIGHT_PLANNER_DSLINKEDLIST_H
