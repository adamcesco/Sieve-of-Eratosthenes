//
// Created by escob on 3/25/2022.
//

#ifndef INC_22S_FLIGHT_PLANNER_DSNODE_H
#define INC_22S_FLIGHT_PLANNER_DSNODE_H

template <class T>
class Node{
public:
    Node(){ data = nullptr; next = nullptr; prev = nullptr; }
    explicit Node(const T&);
    Node(const Node<T>&);
    Node<T>* get_next() const;    //returns a pointer so that the user of the class has both the proper memory address of *this Node and the interface of the Node
    Node<T>* get_prev() const;
    Node<T>& set_next(Node<T>*);
    Node<T>& set_prev(Node<T>*);
    Node<T>& operator =(const Node<T>& toAssign);
    Node<T>& place(const T& passed) { if(data == nullptr){ data = new T(); } *data = passed; }    //places a value into *this' data
    T read() const   { return *data; }  //returns a copy of *this' data
    T& get()         { return *data; }  //returns *this' data by reference
    ~Node() { delete data; }
private:
    T* data;            //the data of a Node is set as a pointer so that the dummy node does always have an instance of T...
    Node<T>* next;    //...this can save a lot of space depending on the data-type because T's default constructor is not automatically called
    Node<T>* prev;
};

template<class T>
Node<T>::Node(const T& passed) {
    data = new T(); //defining 'data' pointer
    *data = passed; //placing the passed value into the memory address 'data' points to
    next = nullptr; //upon construction, 'next' and 'prev' have nothing to point to automatically, so they are both set to nullptr
    prev = nullptr;
}

template<class T>
Node<T>* Node<T>::get_next() const {
    return next;
}

template<class T>
Node<T>* Node<T>::get_prev() const {
    return prev;
}

template<class T>
Node<T>& Node<T>::set_next(Node<T>* toNext) {
    next = toNext;
    return *this;
}

template<class T>
Node<T>& Node<T>::set_prev(Node<T>* toPrev) {
    prev = toPrev;
    return *this;
}

template<class T>
Node<T>::Node(const Node<T>& passed) {
    if(data == nullptr)
        data = new T();
    *data = *passed.data;   //deep copying the data
    next = passed.next;     //shallow copying the prev and next so that both 'toAssign' and *this point to the same previous and next DSNodes
    prev = passed.prev;
}

template<class T>
Node<T> &Node<T>::operator=(const Node<T> &toAssign) {
    if (this == &toAssign)  //handling self-assignment
        return *this;
    *data = *toAssign.data; //deep copying the data
    prev = toAssign.prev;   //shallow copying the prev and next so that both 'toAssign' and *this point to the same previous and next DSNodes
    next = toAssign.next;
    return *this;
}

#endif //INC_22S_FLIGHT_PLANNER_DSNODE_H
