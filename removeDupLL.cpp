#include <iostream>
#include <string>
#include <map>

using namespace std;

struct node {
    node* next = NULL;
    int data;

    node(int d) {
        this->data = d;
    }

    node();


    void appendToTail(int d) {
        node* end = new node(d);
        node* n = this;

        //looking for the tail
        while (n->next != NULL) {
            n = n->next;
        }
        n->next = end;
    }

    void printNodes () {
        node* n = this;

        while (n->next != NULL) {
            cout << n->data << " ";
            n = n->next;
        }
        cout << n->data << endl;
    }

    //2.1 - map version
    void removeDupLL() {
        node *tmp, *n;
        map<int, node> map;

        if (this == NULL) return;

        n = this;
        map.insert(pair<int,node>(n->data,*n));

        while (n->next != NULL) {
            if (map.find(n->next->data) != map.end()) {
                tmp = n->next;
                n->next = n->next->next;
                delete tmp;
            } else {
                map.insert(pair<int, node> (n->next->data, *n));
                n = n->next;
            }
        }
    }

    //2.1 - runner version
    void removeDupLL2() {
        node *runner, *tmp, *n;
        n = this;

        while (n != NULL) {
            runner = n;
cout <<"n->data is: " << n->data << endl;
            while (runner->next != NULL) {
                cout << "runner->next is: " << runner->next->data << endl;
                if (n->data == runner->next->data) {
                    cout << "Removing: " << runner->next->data << endl;
                    tmp = runner->next;
                    n->next = runner->next->next;
                    delete tmp;

                } else {
                    runner = runner->next;
                }
            }

            cout << "current node looks like: ";
            n->printNodes();
            n = n->next;
        }
    }

    //2.2 - kth from the last
    // use the runner - 1st pointer reaches end, 2nd pointer reaches end - k
    int kfromlast(int k) {
        node *leader, *runner;
        leader = this;
        runner = this;

        while (leader->next != NULL) {
            while (k - 1 > 0) {
                leader = leader->next;
                --k;
            }
            runner = runner->next;
            leader = leader->next;
        }

        return runner->data;
    }

    // 2.4 - partition LL wrt the value x
    node* partitionLL(int x) {
        node *pivot, *n, *tmp, *tmp2, *partitioned;
        pivot = new node(x);
        partitioned = pivot;

        n = this;
        while (n != NULL) {
            if (pivot->data <= n->data) {
                tmp = pivot->next;
                tmp2 = n->next;

                pivot->next = n;
                n->next = tmp;
                n = tmp2;
            } else {
                tmp = n->next;
                tmp2 = partitioned;

                partitioned = n;
                partitioned->next = tmp2;
                n= tmp;
            }
        }

        return partitioned;
    }
};


// 2.3 - delete the middle node, given access to the node ONLY
void deletemidnode(node* midnode) {
    node *temp;

    temp = midnode->next;
    midnode->data = midnode->next->data;
    midnode->next = midnode->next->next;

    delete temp;
}

//2.5 - recursively adding each of the nodes
node* add_nodal_numbers(node* n1, node* n2, int carry) {
    int sum;

    //base-case
    if (n1 == NULL && n2 == NULL && carry == 0) return NULL;

    sum = n1->data + n2->data + carry;

    cout << "sum is: " << sum << endl;
    node* output = new node(sum % 10);

    if (n1 != NULL || n2 != NULL || sum >= 10) {
        node* recursive_output = add_nodal_numbers(n1==NULL? NULL : n1->next, n2== NULL? NULL: n2->next, sum >=10? 1 : 0);
        output->next = recursive_output;
    }

    return output;
}


// extra - reverse a LL
// iterative
node* reverseLL(node* head) {
    node* current, *prev, *nxt;
    prev = NULL;
    current = head;

    while (current != NULL) {
        nxt = current->next;
        current->next = prev;
        prev = current;
        current = nxt;
    }

    return prev;
}



//2.6 - circular loop, returns the node at the beginning of the loop
node* circularLL(node* inputLL) {
    node* pointer = inputLL, * runner;

    while (pointer != NULL) {
        runner = pointer->next;
        while (runner != NULL) {
            if (pointer->data == runner->data) {
                return pointer;
            }
            runner = runner->next;
        }
        pointer = pointer->next;
    }

    return NULL;
}


int main() {
    //2.6
    node* circLL = new node(1);
    circLL->appendToTail(2);
    circLL->appendToTail(3);
    circLL->appendToTail(4);
    circLL->appendToTail(5);
    circLL->appendToTail(3);

    node* retVal = circularLL(circLL);

    cout << "Should return 3: " << retVal->data << endl;

    node* reverse = reverseLL(circLL);
    cout << "Should be 354321: ";
    reverse->printNodes();

    /*
    node* root;
    root = new node(2);
    root->appendToTail(6);
    root->appendToTail(2);
    root->appendToTail(6);
    root->appendToTail(4);
    root->appendToTail(5);
    root->appendToTail(6);

    root->printNodes();
    //2.5 - add two nodal inputs and return nodal output as the sum of the two
    node* n1 = new node(1);
    n1->appendToTail(2);
    n1->appendToTail(3);
    n1->printNodes();

    cout << "PLUS" << endl;

    node* n2 = new node(4);
    n2->appendToTail(5);
    n2->appendToTail(6);
    n2->printNodes();

    cout << "EQUALS" << endl;

    node* retval = add_nodal_numbers(n1, n2, 0);
    retval->printNodes();


    //2.4 - partition wrt x
    node* test_node = root->partitionLL(3);
    test_node->printNodes();

    //2.3 midnode delete
    node *midnode = root->next->next->next; //should be 6
    deletemidnode(midnode);

    root->printNodes();

    //2.2 kth from the end
    cout << "Should be 4: " << root->kfromlast(3) <<endl;

    //2.1 test
    root->removeDupLL();

    cout << "After removing duplicates: ";
    root->printNodes();
*/

    return 0;
}
