#include <iostream>
#include <string>
#include <map>

using namespace std;

class Stack {
private:
    int top;
    int capacity;
    int *storage;

public:
    //ctor
    Stack (int cap) {
        if (cap <= 0) throw string("Stack's capacity must be positive");

        storage = new int[cap];
        this->capacity = cap;
        top = -1; // index denoting the bottom of the stack
    }

    void push(int value) {
        if (top == capacity) throw string("Stack has reached the capacity");

        top++;
        storage[top] = value;
    }

    void pop() {
        if (top == -1) throw string ("Nothing to pop - bottom of the stack");
        top--;
    }

    int peek() {
        if (top == -1) throw string ("Nothing to peek at - bottom of the stack");

        return storage[top];
    }

    bool isEmpty() {
        return (top == -1);
    }
};

//3.2 - 2 stacks solution (because it only has to remember changed # of mins)
class Stack::StackwithMin {
    Stack *minStack;

    Stack::StackwithMin(int capacity) {
        minstack = new Stack(capacity);
    }

    void push(int value) {
        if (value <= minStack->peek) { //min = value
            minStack->push(value);
        }
    }

    void pop(int value) {
        if (value == minStack->peek()) {
            minStack->pop();
        }
    }
};

int main() {
    // Basic stacks feature test
    Stack *test = new Stack(5);

    test->push(11);
    test->push(12);
    test->push(13);
    cout << "Should be 13 at top: " << test->peek() <<endl;
    test->pop();
    cout << "Should now be 12: " << test->peek() << endl;
    test->pop();
    test->pop();
    cout << "Is the stack empty? " << test->isEmpty() << endl;

    return 0;
}
