//
//  DLL.cpp
//
//
//  Created by Chaos Zero on 9/24/20.
//

#include <iostream>
using namespace std;

// Construct the Course class

class Course {
  
private:
    int capacity;
    Course* ptr_prev;
    Course* ptr_next;
    
public:
    
    Course() {}                     // default constructor
    
    Course(int c) {                  // parameterized constructor
        capacity = c;
        ptr_prev = NULL;
        ptr_next = NULL;
    }
    
    void setPrev(Course* node)       // link specific Course to a previous Course
    { ptr_prev = node; }
    
    void setNext(Course* node)       // link specific Course to a next Course
    { ptr_next = node; }
    
    Course* getPrev()               // return the previous linked Course
    { return this->ptr_prev; }
    
    Course* getNext()               // return the next linked Course
    { return this->ptr_next; }
    
    void setCapacity(int number)    // set the capacity of the selected Course
    { capacity = number; }
    
    int getCapacity()               // return the capacity of a selected Course
    { return capacity; }
    
    // This method removes a Course (node) from an implicit Doubly Linked List. Since we don't have an explict DLL class defined, the list is made strictly by linking Course nodes to one another, and the aggregate is taken to be the list. I decided to parameterize this list with two Course objects, representing the head and tail Courses, and a key to search for. If the key matches a certain Course's capacity, then the previous and next Courses that are linked to that specific Course, are now linked to each other, effectively deleting the removed Course from the list.
    
    
    void remove(Course* headNode, Course* tailNode, int key) {
        int currentCapacity;            // keep track of the capacity as an int
        Course* temp = new Course;      // make a temp Course to traverse through and keep track of every key and compare with the capacity at each Course node.
        temp = headNode;        // start temp at the head Course.
        while (temp != NULL) {
            currentCapacity = temp->getCapacity();  // assign current Capacity to the temp Capacity
            if (currentCapacity == key) {       // check if the key matches the Capacity of the traversed Course
                removeCourse(headNode, tailNode, temp);     // employ removeCourse method
                temp = NULL;
            }
            else {
                temp = temp->getNext();     // if the key doesn't match the capacity, traverse to the next Course node.
            }
        }
        
    }
    
    // This method checks for 3 cases: 1. The Course we want to remove is the head, 2. The Course we want to remove is the tail, 3. The course we want to remove is in between the head and tail of the list.
    
    void removeCourse(Course* headNode, Course* tailNode, Course* course) {
        Course* prevCourse = course->getPrev();
        Course* nextCourse = course->getNext();
        
        if (prevCourse == NULL) {       // check to see if the course we want to delete is the head
            headNode = headNode->getNext();     // make/move head Course node the next Course node
            headNode->setPrev(NULL);    // set the previous Course node to NULL
        }
        
        else if (nextCourse == NULL) {  // check to see if the course we want to delete is the tail
            tailNode = tailNode->getPrev();    // make/move the tail Course node to the previous Course node
            tailNode->setNext(NULL);    // set the next Course node to NULL
        }
        
        else {      // if the course we want to delete is in the middle
            course->getPrev()->setNext(course->getNext());  // forwardly link the deleted Course node's previous Course node to the next Course node of the course we want to delete
            course->getNext()->setPrev(course->getPrev());  // backwardly link the deleted Course node's next Course node to the previous Course node of the course we want to delete
            course = NULL;  // delete/wipe the memory of the deleted Course node
        }
    }
    
    // The insert funtion will use a headNode Course pointer, tailNode Course pointer, and data int which will represent the capacity of the inserted Course.
    
    void insert(Course* headNode, Course* tailNode, int data) {
        
        Course* temp = new Course;  // make a temp course to keep track of traversals.
        temp = headNode;            // set temp to the head.
        while(temp != NULL) {
            if (data > temp->getNext()->getCapacity()) {    // if data is greater than the capacity of the next Course of the current Course...
                temp = temp->getNext();     // traverse to the next Course
            }
            else {
                insertNode(temp, temp->getNext(), tailNode, data);  // if we find the capacity not exceeding the capacity of the next Course, we insert the Course node in the appropriate location using the insertNode method.
                temp = NULL;
            }
        }
        
    }
    
    // This method makes sure that we insert the correct Course in the right place. I felt that using 3 Course parameters with an int parameter made this the easiest way and made the most sense for me.
    
    void insertNode(Course* current, Course* next, Course* tail, int data) {
        Course* temp = new Course;      // make a temp Course to keep track
        temp->setCapacity(data);        // set temp with the capacity we want to insert with. (Temp will be the Course we insert).
        
        if (next == NULL) {     // check to see if the current Course is the tail.
            next = tail;        // if so, make the next node the tail.
            tail->setPrev(temp); // then, set the tail's previous Course node as temp
            current->setNext(temp); // and set the next current Course as temp
        }
        
        else {                      // if current is NOT the tail...
            current->setNext(temp);    // set the current's next Course as temp
            next->setPrev(temp);        // set the current's next's previous Course as temp
            temp->setPrev(current); // set temp's previous Course as current
            temp->setNext(next);    // set temp's next Course as next
        }
    }
    
};

// Global variables
Course* head = new Course;
Course* tail = new Course;

// function prototypes
int binarySearch(Course*, int, int, int);

int main() {
    
    int i = 1;
    int count = 0;
    int input, key, capacity;
    
    Course* temp = new Course;
    Course* case1 = new Course;
    
    cin >> input >> key;        // read in the inputs
    
    while(cin >> capacity) {    // keep reading in inputs as capacity
        if (i == 1) {           // for the first capacity, we configure the head Course node.
            head->setCapacity(capacity);    // set the head with initial capacity
            head->setPrev(NULL);            // set head's next to NULL
            head->setNext(NULL);            // set head's previous to NULL
            i+=1;                           // increment i to break out of if statement
            count+=1;                       // increment count (number of Courses)
        }
        else {
            
            Course* c = new Course;     // allocate a new Course object
            if (i == 2) {               // we want to specifically handle the head and it's next case separately.
                c->setPrev(head);       // set c's previous to head
                c->setCapacity(capacity);   // give c the newly read in capacity
                head->setNext(c);       // set head's next to c
                i+=1;                   // break out of this case
                temp = c;               // set temp to c to keep track of list
                count+=1;               // increment count
            }
            else {                      // all future cases will be handled here
                c->setPrev(temp);       // set the new Course object c previous to temp
                c->setCapacity(capacity);   // set capacity to c
                temp->setNext(c);           // temp, which is still read in as the previous c Course, is now setting it's next to this new c Course. Temp is now doubly linked.
                temp = c;   // Set temp to the new Course c.
                count+=1;   // increment count
                tail = temp;    // after the last capacity is read in, the tail will be set to the last temp before the statement breaks out.
            }
        }
        
    }
    
    // We use a switch statement to handle the input cases.
    
    switch(input) {
        case 0:         // if input is 0, do a binary search.
            int x;
            x = binarySearch(head, key, 1, count);
            cout << x;
            break;

        case 1:         // if input is 1, traverse through the linked list and decide whether to insert or remove a Course node.
            int j = 0;
            case1 = head;
            while (j == 0) {
                if (case1->getCapacity() == key) {  // if we find a match between a capacity of a Course in the list and the key, we remove that Course from the list.
                    head->remove(head, tail, key);
                    j+=1;
                }
                else {
                    case1 = case1->getNext();   // if not immediately found, go to the next Course and repeat.
                    if (case1 == tail) {    // if we reach the end of the list, the key does not match the capacity. So, we insert a new Course.
                        head->insert(head, tail, key);
                        j+=1;
                    }
                }
            }
            while (head != NULL) {     // print out all the capacities of the list
                cout << head->getCapacity() << " ";
                head = head->getNext();
            }
    }
    return 0;
}

// This is a non-recursive method to perform a binary search.

int binarySearch(Course* head, int key, int lowIndex, int highIndex) {

    if (lowIndex > highIndex) {       // if the lower index exceeds the higher index, the element is not found.
        return -1;
    }

    while (lowIndex <= highIndex) {     // the lower index is allowed to be less or equal to the higher index
        
        Course* temp = new Course;  // create a temp course to keep track
        temp = head;        // set the temp course to the head

        int midpoint = (lowIndex + highIndex) / 2;     // midpoint is the average of low and high

        for (int i = 0; i < midpoint; i++) { // traverse the Course nodes until we reach the "index" of the midpoint.
                temp = temp->getNext();
        }

        if (key == temp->getCapacity()) {   // if the "index" Course's capacity matches the key, we found the Course. So, we return the midpoint, aka, the number of the Course in the list we found.
            return midpoint;
        }

        else if (key < temp->getCapacity()) {   // if the key is less than the capacity returned at the midpoint index, we truncate the high value to the mid-1 index, cutting it in half.
            highIndex = midpoint - 1;
        }

        else {      // if the key is greater than the capacity returned at the midpoint index, we truncate the lower value to the mid + 1 index, cutting it in half.
            lowIndex = midpoint + 1;
        }
    }
    return -1;
}
