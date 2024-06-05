#include <bits/stdc++.h>

using std::vector;
using std::string;
#define vii std::vector <std::vector <int>> 
#define vi std::vector <int>
#define vpii std::vector <std::pair <int, int>>
/*
[ ALL THE DATA IS ILLUSTRATED BY INTEGER ]
*/

// [LINKED LIST]


class Node {
    public:
        int data;
        Node* nextNode;
    
        Node (int _data): data (_data), nextNode (NULL) {}
};
// [opreration in list's node]
// creating the new node ~~ the constructor of the Node class
Node* makeNode (int _data){
    Node* newNode = new Node (_data);
    return newNode;
}

/*
[
    operations:
        void printList () --> traversal
        int size ()
        void push_back (int Value)
        void push_front (int Value)
        void push (int Value)
        void insert (int Value, int Position)
        void pop_front ()
        void pop_back ()
        void erase_key (int keyValue)
        void erase (int Position)
        void erase (int begin, int finish) | begin <= postion < finish
        void erase ()
        void reverse ()
        int get_key (int Index)
        int find (int KeyValue) return the index else return -1
        Node* get (int position)
        void sort ()
]
*/

class LinkedList {
    private:
        Node* root;
        Node* tail; // the optional to access the tail node in O(1)

    public:
        LinkedList (): root (NULL), tail (NULL) {}
        
        // operation on the Linnked list
        void printList () {
            Node* standNode = root;
            int index = 0;
            while (standNode != NULL) {
                std::cout << "[" << index++ << "]";
                std::cout << "[Val: " << standNode -> data ; 
                std::cout << " | seft: " << standNode;
                std::cout << " | next: " << standNode -> nextNode << "]" << '\n' ;

                standNode = standNode -> nextNode;
            }
        }

        // get the size of list
        int size () {
            int countSize = 0;
            Node* standNode = root;
            while (standNode != NULL) {
                ++countSize;
                standNode = standNode -> nextNode;
            }
            return countSize;
        }

        //insert new value into the front of list
        void push_front (int _data) {
            Node* newNode = new Node (_data);
            newNode -> nextNode = root;
            this -> root = newNode;
        }

        // insert a new value into the back of list
        void push_back (int _data) {
            Node* newNode = new Node (_data);
            if (root == NULL) {
                root = newNode;
                return;
            }
            Node* standNode = root;
            while (standNode -> nextNode != NULL) {
                standNode = standNode -> nextNode;
            }
            standNode -> nextNode = newNode;
        }

        // insert in O(1)
        void push (int _data) {
            Node* newNode = new Node (_data);
            // if the list is empty
            if (root == NULL) {
                root = newNode;
                return;
            }
            // if the list contains 1 element
            if (root -> nextNode == NULL) {
                tail = newNode;
                root -> nextNode = tail;
                return;
            }

            tail -> nextNode = newNode;
            tail = newNode;
        }

        void insert (int _data, int positon = 0) {
            Node* newNode = new Node (_data);
            if (positon == 0){
                push_front (_data);
                return;
            }
            Node* standNode = root;
            while (--positon) {
                standNode = standNode -> nextNode;
            }
            newNode -> nextNode = standNode -> nextNode;
            standNode -> nextNode = newNode;
        }

        // delete the first key in the list
        void pop_front () {
            if (root == NULL) return;
            Node* standNode = root;
            standNode = root -> nextNode;
            delete root;
            root = NULL;
            root = standNode;
        }

        // delete the last key in the list
        void pop_back () {
            if (root == NULL) return;
            Node* standNode = root;
            while (standNode -> nextNode -> nextNode) {
                standNode = standNode -> nextNode;
            }
            Node* temp = standNode;
            standNode = standNode -> nextNode;
            delete standNode;
            standNode = NULL;
            temp -> nextNode = NULL;
        }

        // delete the given key
        void erase_key (int key) {
            if (key == root -> data){
                pop_front ();
                return;
            }
            Node* standNode = root -> nextNode;
            Node* previousNode = root;
            Node* afterNode = standNode -> nextNode;
            while (standNode -> nextNode != NULL) {
                if (key == standNode -> data) {
                    previousNode -> nextNode = afterNode;
                    delete standNode;
                    standNode = NULL;
                    return;
                }
                previousNode = standNode;
                standNode = standNode -> nextNode;
                afterNode = standNode -> nextNode;
            }
        }

        // delete the given position;
        void erase  (int position) {
            if (position == 0) {
                pop_front ();
                return;
            }
            Node* standNode = root -> nextNode;
            Node* previousNode = root;
            Node* afterNode = standNode -> nextNode;
            while (--position) {
                previousNode = standNode;
                standNode = standNode -> nextNode;
                afterNode = standNode -> nextNode;
            }
            previousNode -> nextNode = afterNode;
            delete standNode;
            standNode = NULL;
        }
        
        // delete from first to last
        void erase (int first, int last) {
            int repeat = last - first + 1;
            Node* fPart = root;
            while (--first) {
                fPart = fPart -> nextNode;
            } 
            Node* temporary = fPart -> nextNode;
            while (--repeat) {
                Node* temporary_second = temporary -> nextNode;
                delete temporary ;
                temporary = temporary_second;
            }
            fPart -> nextNode = temporary;
        }

        void erase () {
            while (root){
                Node* standNode = root;
                root = root -> nextNode;
                delete standNode;
                standNode = NULL;                
            }
        }

        // // using recursion
        // Node* changeTheNode (Node* &list) {
        //     if (list == NULL || list -> nextNode == NULL) return list;
        //     // reverse the rest part (node list after the root) and change the root as a tail
        //     Node* rest = changeTheNode (list -> nextNode);
        //     list -> nextNode -> nextNode = list;
        //     list -> nextNode = NULL;
        //     return rest;
        // }

        // void reverse () {
        //     root = changeTheNode (root);
        // }

        // reverse by changing the link between two node
        void reverse () {
            Node* standNode = root;
            Node* previousNode = NULL;
            Node* storedNode = NULL;
            while (standNode) {
                storedNode = standNode -> nextNode;
                standNode -> nextNode = previousNode;
                previousNode = standNode;
                standNode = storedNode;
            }
            root = previousNode;
        }

        int get_key (int index) {
            if  (index < 0 || root == NULL || index >= size ()) return -1;
            if (index == 0) return root -> data;
            
            Node* standNode = root;
            while (index--) standNode = standNode -> nextNode;
            return standNode -> data;
        }

        int find (int key) {
            if (root == NULL) return -1;
            Node* standNode = root -> nextNode;
            if (key == root -> data) return 0;
            int index = 1;
            while (standNode) {
                if (key == standNode -> data) return index;
                standNode = standNode -> nextNode;
                ++index;
            }
            return -1;
        }
        //bool isAppear (int key, Node* list) {
        //     if (list == NULL) return false;
        //     if (key == list -> data) return true;
        //     return isAppear (key, list -> nextNode);
        // }

        Node* get (int position) {
            if (root == NULL) return NULL;
            Node* standNode = root;
            if (position == 0) {
                return standNode;
            }
            while (position--) {
                standNode = standNode -> nextNode;
            }
            return standNode;

        }

        void sort () {
            for (Node* i = root; i != NULL; i = i -> nextNode) {
                Node* minNode = i;
                for (Node* j = i -> nextNode; j != NULL; j = j -> nextNode) {
                    if (minNode -> data > j -> data) {
                        minNode = j;
                    }
                }
                int tmp = minNode -> data;
                minNode -> data = i -> data;
                i -> data = tmp;
            }
        }

};

/*
[DOUBLY LINKED LIST]
*/

class DLLNode { 
    public:
        int data;
        DLLNode* prevNode;
        DLLNode* nextNode;

        DLLNode (int _data): data (_data), prevNode (NULL), nextNode (NULL) {}
};

/*
[
    operations:
        void printList () --> traversal
        int size ()
        void push_back (int Value)
        void push_front (int Value)
        void push (int Value)
        void insert (int Value, int Position)
        void pop_front ()
        void pop_back ()
        void erase_key (int keyValue)
        void erase (int Position)
        void erase (int begin, int finish) | begin <= postion < finish
        void erase ()
        void reverse ()
        int get_key (int Index)
        int find (int KeyValue) return the index else return -1
        DLLNode* get (int position)
        void sort ()
]
*/

class DoublyLinkedList {
    private:
        DLLNode* root;
        DLLNode* tail; // optional
    
    public:
        DoublyLinkedList (): root (NULL), tail (NULL) {}

        void printList () {
            DLLNode* standNode = root;
            int index = 0;
            while (standNode) {
                std::cout << "[" << index++ << "]";
                std::cout << "Val: " << standNode -> data << " | ";
                std::cout << "prev: " << standNode -> prevNode << " | ";
                std::cout << "seft: " << standNode << " | ";
                std::cout << "next: " << standNode -> nextNode << '\n';

                standNode = standNode -> nextNode;
            }
        }

        int size () {
            int countNode = 0;
            DLLNode* standNode = root;
            while (standNode){
                ++countNode;
                standNode = standNode -> nextNode;
            }
            return countNode;
        }

        void push_front (int data) {
            DLLNode* newNode = new DLLNode (data);
            if (root == NULL) {
                root = newNode;
                return;
            }
            root -> prevNode = newNode;
            newNode -> nextNode = root;
            root = newNode;
        }

        void push_back (int data){
            DLLNode* newNode = new DLLNode (data);
            if (root == NULL){
                root = newNode;
                return;
            }
            DLLNode* standNode = root;
            while (standNode -> nextNode != NULL) {
                standNode = standNode -> nextNode;
            }
            newNode -> prevNode = standNode;
            standNode -> nextNode = newNode;
            standNode = newNode;
        }

        void push (int data) {
            DLLNode* newNode = new DLLNode (data);
            if (root == NULL) {
                root = newNode;
                return;
            }
            tail -> nextNode = newNode;
            newNode -> prevNode = tail;
            tail = newNode;
        }

        void insert (int data, int position) {
            DLLNode* newNode = new DLLNode (data);
            if (position == 0 || root == NULL) {
                root = newNode;
                return;
            }
            DLLNode* standNode = root;
            while (--position) {
                standNode = standNode -> nextNode;
            }
            newNode -> nextNode = standNode -> nextNode;
            standNode -> nextNode = newNode;
            newNode -> prevNode = standNode;
        }

        void pop_front () {
            if (root == NULL) return;
            DLLNode* standNode = root -> nextNode;
            delete root;
            root = NULL;
            root = standNode;
        }

        void pop_back () {
            DLLNode* standNode = root;
            while (standNode -> nextNode -> nextNode) {
                standNode = standNode -> nextNode;
            }
            DLLNode* tmp = standNode -> nextNode;
            delete tmp;
            tmp = NULL;
            standNode -> nextNode = NULL;
        }

        void erase_key (int key) {
            if (root -> data == key){
                pop_front ();
                return;
            }
            DLLNode* standNode = root;
            DLLNode* prevNode = NULL;
            DLLNode* nextNode = standNode -> nextNode;
            while (standNode -> nextNode) {
                if (standNode -> data == key) {
                    prevNode -> nextNode = nextNode;
                    nextNode -> prevNode = prevNode;
                    delete standNode;
                    standNode = NULL;
                    return;
                }
                prevNode = standNode;
                standNode = standNode -> nextNode;
                nextNode = standNode -> nextNode;
            } 
            return;

        }

        void erase () {
            while (root) {
                DLLNode* tmp = root;
                root = root -> nextNode;
                delete tmp;
                tmp = NULL;
            }
        }

        void erase (int position) {
            if (position < 0 || root == NULL) return;

            if (position == 0) {
                pop_front ();
                return;
            }
            DLLNode* standNode = root;
            while (position--){
                standNode = standNode -> nextNode;
            }
            if (standNode -> nextNode == NULL){
                pop_back ();
                return;
            }
            standNode -> prevNode -> nextNode = standNode -> nextNode;
            standNode -> nextNode -> prevNode = standNode -> prevNode;
            delete standNode;
            standNode = NULL;

        }

        DLLNode* get (int position) {
            if (root == NULL) return NULL;
            DLLNode* standNode = root;
            if (position == 0) {
                return standNode;
            }
            while (position--) {
                standNode = standNode -> nextNode;
            }
            return standNode;

        }

        void erase (int first, int last) {
            DLLNode* firstNode = get (first) -> prevNode;
            DLLNode* FNode = get (first);
            DLLNode* lastNode = get (last);
            for (DLLNode* node = FNode; node != lastNode -> prevNode; node = node -> nextNode){
                DLLNode* tmp = node;
                delete tmp;
                tmp == NULL;
            }
            firstNode -> nextNode = lastNode;
            lastNode -> prevNode = firstNode;
        }

        // void reverse () {
        //     if (!root || root -> nextNode == NULL) return;
        //     DLLNode* lastNode = get (size()-1);
        //     DLLNode* newList = NULL;
        //     DLLNode* tmp = newList;
        //     while (lastNode != root -> prevNode) {
        //         tmp -> data = lastNode -> data;
        //         tmp -> nextNode = lastNode -> prevNode;
        //         tmp -> prevNode = lastNode -> nextNode;
        //         //tmp = tmp -> nextNode;
        //         lastNode = lastNode -> prevNode;
        //     }
        //     root = newList;
        // }

        int get_key (int positon) {
            if (positon < 0 || root == NULL || positon >= size()) return -1;
            DLLNode* standNode = root;
            if (positon == 0) return root -> data;
            while (positon--) {
                standNode = standNode -> nextNode;
            }
            return standNode -> data;
        }

        int find (int key) {
            if (root == NULL) return -1;
            DLLNode* standNode = root -> nextNode;
            if (key == root -> data) return 0;
            int index = 1;
            while (standNode) {
                if (key == standNode -> data) return index;
                standNode = standNode -> nextNode;
                ++index;
            }
            return -1;
        }

        void sort () {
            for (DLLNode* i = root; i != NULL; i = i -> nextNode) {
                DLLNode* minNode = i;
                for (DLLNode* j = i -> nextNode; j != NULL; j = j -> nextNode) {
                    if (minNode -> data > j -> data) {
                        minNode = j;
                    }
                }
                int tmp = minNode -> data;
                minNode -> data = i -> data;
                i -> data = tmp;
            }
        }
        
};

/*
[STACH WITH LINKED LIST]
*/

/*
[
    operations on stack
        void push (int data)
        void pop ()
        int size ()
        int top ()
        bool empty ()
        bool full ()

]
*/
class Stack {
    private:
        LinkedList* list;
        int capacity;
    public:
        Stack (): list (new LinkedList), capacity (-1) {}
        Stack (int Capacity): list (new LinkedList), capacity (Capacity) {}

        void push (int data) {
            if (full ()) return;
            list -> push_front (data);
        }

        void pop () {
            list -> pop_front ();
        }

        int size () {
            return list -> size();
        }

        int top () {
            return list -> get_key (0);
        }

        bool empty () {
            if (list == NULL || list -> size () == 0) return true;
            return false;
        }

        bool full () {
            return list -> size () == capacity ? true : false;
        }

        ~Stack () {
            list -> erase ();
            list = NULL;
            capacity = 0;
        }
};

/*
[QUEUE WITH LINKED LIST]
*/

/*
[
    operations on queue
        void push (int data)
        void pop ()
        int front ()
        int back ()
        int rear ()
        bool empty ()
]
*/

class Queue {
    private:
        LinkedList* list;
    public:
        Queue (): list (new LinkedList ()) {}

        void push (int data) {
            list -> push_back (data);
        }

        void pop () {
            list -> pop_front ();
        }

        int front () {
            return list -> get_key (0);
        }

        int rear () {
            return list -> get_key (1);
        }

        int back () {
            return list -> get_key (list -> size () -1);
        }

        bool empty () {
            return (list == NULL || list -> size () == 0)? true : false;
        }

        ~Queue () {
            list -> erase ();
            list = nullptr;
        }
        
};


/*
[BINARY TREE]
*/
/*
[
    operations:
        *traversals:
            void preOrder ()
            void inOrder ()
            void postOrder ()
            // all of DFS traversal are expressed in recursion, more references and its
            // implementations in the private methods in class BinaryTree

            // BFS traversals
            void level_Order ()
            void spiral_Order ()
            // the implementations in the private methods

        int height ()
        BinaryTreeNode* search (int key)
        void insert (int data)
        void erase (int key)
        // the implementations in the private methods
]
*/

class BinaryTreeNode {
    public:
        int data;
        BinaryTreeNode* leftNode;
        BinaryTreeNode* rightNode;

        BinaryTreeNode (int _data): data (_data), leftNode (NULL), rightNode (NULL) {}

};

class BinaryTree {
    private:

        /*[DFS traversal]*/
         /* NLR */
        // with recursion
        void preOrderRecursive (BinaryTreeNode* root) {
            if (root != NULL) {
                std::cout << root -> data ; 
                std::cout << " | s: " << root ;
                std::cout << " | l: " << root -> leftNode << " | r: " << root -> rightNode << '\n' ; // other operations with data here
                preOrderRecursive (root -> leftNode);
                preOrderRecursive (root -> rightNode);
            }
        }

        // with using stack, using the built-in library instead
        void preOrderWithStack (BinaryTreeNode* root) {
            if (root == NULL) return;
            std::stack <BinaryTreeNode*> nodeBucket;
            nodeBucket.push (root);

            while (!nodeBucket.empty()) {
                BinaryTreeNode* current = nodeBucket.top ();
                std::cout << current -> data << " ";
                std::cout << " | s: " << current ;
                std::cout << " | l: " << current -> leftNode << " | r: " << current -> rightNode << '\n' ; // other operations with data here
                nodeBucket.pop ();
                
                if (current -> rightNode != NULL)
                    nodeBucket.push (current -> rightNode);
                if (current -> leftNode != NULL)
                    nodeBucket.push (current -> leftNode);
            }
        }

        // morris approach
        /*  [
                Using Morris Traversal, we can traverse the tree without using stack and recursion.
                 The algorithm for Preorder is almost similar to Morris traversal for Inorder.

                    1…If left child is null, print the current node data. Move to right child. 
                    ….Else, Make the right child of the inorder predecessor point to the current node. Two cases arise: 
                    ………a) The right child of the inorder predecessor already points to the current node. Set right child to NULL. Move to right child of current node. 
                    ………b) The right child is NULL. Set it to the current node. Print the current node’s data and move to left child of current node. 
                    2…Iterate until the current node is not NULL.
            ]
        */
        void preOrderMorris(BinaryTreeNode* node) {
            BinaryTreeNode* curr = node;

            while (curr) {
                if (!curr->leftNode) {
                    std::cout << curr->data << " ";
                    curr = curr->rightNode;
                } else {
                    BinaryTreeNode* prev = curr->leftNode;
                    while (prev->rightNode && prev->rightNode != curr) {
                        prev = prev->rightNode;
                   }

                    if (!prev->rightNode) {
                        std::cout << curr->data << " ";
                        prev->rightNode = curr;
                        curr = curr->leftNode;
                    } else {
                        prev->rightNode = nullptr;
                        curr = curr->rightNode;
                    }
                }
            }
        }

        /* LNR */
        // with recursion
        void inOrderRecursive (BinaryTreeNode* root) {
            if (root != NULL) {
                inOrderRecursive (root -> leftNode);
                std::cout << root -> data << " ";
                std::cout << " | s: " << root ;
                std::cout << " | l: " << root -> leftNode << " | r: " << root -> rightNode << '\n' ; // other operations with data here
                inOrderRecursive (root -> rightNode);
            }
        }

        // with using stack, using the built-in library instead
        void inOrderWithStack (BinaryTreeNode* root) {
            std::stack <BinaryTreeNode*> nodeBucket;
            BinaryTreeNode* current = root;
            while (current || !nodeBucket.empty ()) {
                while (current != NULL) {
                    nodeBucket.push (current);
                    current = current -> leftNode;
                }
                current = nodeBucket.top ();
                nodeBucket.pop ();
                std::cout << current -> data << " ";
                std::cout << " | s: " << current ;
                std::cout << " | l: " << current -> leftNode << " | r: " << current -> rightNode << '\n' ;// other operations with data here
                current = current -> rightNode;
            }
            
        }

        // morris approach
        void inOrderMorris(BinaryTreeNode* node) {
           BinaryTreeNode* curr = node;

            while (curr) {
                if (!curr->leftNode) {
                    std::cout << curr->data << " ";
                    curr = curr->rightNode;
                } else {
                    BinaryTreeNode* prev = curr->leftNode;
                    while (prev->rightNode && prev->rightNode != curr) {
                        prev = prev->rightNode;
                    }

                    if (!prev->rightNode) {
                        prev->rightNode = curr;
                        curr = curr->leftNode;
                    } else {
                        prev->rightNode = nullptr;
                        std::cout << curr->data << " ";
                        curr = curr->rightNode;
                    }
                }
            }
        }

        /* LRN */
        // with recursion
        void postOrderRecursive (BinaryTreeNode* root) {
            if (root != NULL) {
                postOrderRecursive (root -> leftNode);
                postOrderRecursive (root -> rightNode);
                std::cout << root -> data << " ";
                std::cout << " | s: " << root ;
                std::cout << " | l: " << root -> leftNode << " | r: " << root -> rightNode << '\n' ; // other operations with data here
            }
        }

        // with using stack, using the built-in library instead
        void postOrderWithStack (BinaryTreeNode* root) {
            if (root == NULL) return;
            std::stack <BinaryTreeNode*> nodeBucket, dataBucket;
            nodeBucket.push (root);
            BinaryTreeNode* current;
            // make the order to traverse
            while (!nodeBucket.empty()) {
                current = nodeBucket.top ();
                nodeBucket.pop ();
                dataBucket.push (current);

                if (current ->  rightNode != NULL) {
                    nodeBucket.push (current -> rightNode);
                }
                if (current -> leftNode != NULL) {
                    nodeBucket.push (current -> leftNode);
                }
            }

            // print all the element in the data bucket
            while (!dataBucket.empty ()) {
                BinaryTreeNode* current = dataBucket.top ();
                std::cout << current -> data << " ";
                std::cout << " | s: " << current ;
                std::cout << " | l: " << current -> leftNode << " | r: " <<  current -> rightNode << '\n' ; // other operations with data here
                dataBucket.pop ();
            }
        }

        // Morris Postorder Traversal
        void postOrderMorris(BinaryTreeNode* node) {
            BinaryTreeNode* dummyRoot = new BinaryTreeNode(0);
            dummyRoot->leftNode = node;
            BinaryTreeNode* curr = dummyRoot;
            BinaryTreeNode* prev = nullptr;

            while (curr) {
                if (!curr->leftNode) {
                    curr = curr->rightNode;
                } else {
                    prev = curr->leftNode;
                    while (prev->rightNode && prev->rightNode != curr) {
                        prev = prev->rightNode;
                    }

                    if (!prev->rightNode) {
                        prev->rightNode = curr;
                        curr = curr->leftNode;
                    } else {
                        printReverse(curr->leftNode, prev);
                        prev->rightNode = nullptr;
                        curr = curr->rightNode;
                    }
                }
            }
            delete dummyRoot;
        }

        void printReverse(BinaryTreeNode* from, BinaryTreeNode* to) {
            reverse(from, to);
            BinaryTreeNode* curr = to;

            while (true) {
                std::cout << curr->data << " ";
                if (curr == from) break;
                curr = curr->rightNode;
            }
            reverse(to, from);
        }

        void reverse(BinaryTreeNode* from, BinaryTreeNode* to) {
            if (from == to) return;
            BinaryTreeNode* x = from;
            BinaryTreeNode* y = from->rightNode;
            BinaryTreeNode* z;

            while (x != to) {
                z = y->rightNode;
                y->rightNode = x;
                x = y;
                y = z;
            }
        }

        /* [BFS traversal] *
        /* [level order traversal]*/
        void leverOrder (BinaryTreeNode* root) {
            if (root == NULL) return;   
            std::queue <BinaryTreeNode*> nodeQueue;
            nodeQueue.push (root);
            while (!nodeQueue.empty ()) {
                BinaryTreeNode* current = nodeQueue.front ();
                nodeQueue.pop ();
                std::cout << current -> data << " ";
                std::cout << " | s: " << current ;
                std::cout << " | l: " << current -> leftNode << " | r: " << current -> rightNode<< '\n' ; // other operations with data here
                if (current -> leftNode != NULL) {
                    nodeQueue.push (current -> leftNode);
                }
                if (current -> rightNode != NULL) {
                    nodeQueue.push (current -> rightNode);
                }
            }
        }

        /* [spiral order traversal]*/
        void spiralOrder (BinaryTreeNode* root) {
            if (root == NULL) return;
            std::stack <BinaryTreeNode*> bucketRL, bucketLR;
            bucketLR.push (root);
            while (!bucketLR.empty () || !bucketRL.empty ()) {
                while (!bucketLR.empty()) {
                    BinaryTreeNode* current = bucketLR.top ();
                    bucketLR.pop ();
                    std::cout << current -> data << " ";
                    std::cout << " | s: " << current ;
                    std::cout << " | l: " << current -> leftNode << " | r: " <<  current -> rightNode << '\n' ; // other operations with data here
                    if (current -> leftNode != NULL)
                        bucketRL.push (current -> leftNode);
                    if (current -> rightNode != NULL)
                        bucketRL.push (current -> rightNode);
                }
                
                while (!bucketRL.empty ()) {
                    BinaryTreeNode* current = bucketRL.top ();
                    bucketRL.pop ();
                    std::cout << current -> data << " ";
                    std::cout << " | s: " << current ;
                    std::cout << " | l: " << current -> leftNode << " | r: " <<  current -> rightNode << '\n' ; // other operations with data here
                    if (current -> leftNode != NULL)
                        bucketLR.push (current -> leftNode);
                    if (current -> rightNode != NULL)
                        bucketLR.push (current -> rightNode);
                }
            }
        }

        BinaryTreeNode* find (BinaryTreeNode* root, int key) {
            if (root == NULL || root -> data == key) return root;
            std::queue <BinaryTreeNode*> bucket;
            BinaryTreeNode* current;
            bucket.push (root) ;
            while (!bucket.empty ()){
                current = bucket.front ();
                bucket.pop ();
                if (current -> data == key) {
                    return current;
                }
                if (current -> leftNode != NULL) {
                    bucket.push (current -> leftNode);
                }
                if (current -> rightNode != NULL) {
                    bucket.push (current -> rightNode);
                }
            }
            return NULL;
        }

        BinaryTreeNode* theDeepest (BinaryTreeNode* root) {
            if (root == NULL) return NULL;
            std::queue <BinaryTreeNode*> bucket;
            bucket.push (root);
            BinaryTreeNode* deepest;
            // level traversal
            while (!bucket.empty()) {
                deepest = bucket.front ();
                bucket.pop ();
                if (deepest -> rightNode != NULL){
                    bucket.push (deepest -> rightNode);
                }
                if (deepest -> leftNode != NULL) {
                    bucket.push (deepest -> leftNode);
                }
            }
            return deepest;
        }

        int Height (BinaryTreeNode* root) {
            if (root == NULL) return -1;
            int leftHeight = Height (root -> leftNode);
            int rightHeight = Height (root -> rightNode);
            return 1 + std::max (leftHeight, rightHeight);
        }

        /*[insert the binary tree]*/
        // make the complete or perfect binary tree
        void add (BinaryTreeNode* &root, int data) {
            BinaryTreeNode* insertNode = new BinaryTreeNode (data);
            if (root == NULL) {
                root = insertNode;
                return;
            }
            std::queue <BinaryTreeNode*> bucket;
            bucket.push (root);
            BinaryTreeNode* current;
            while (!bucket.empty()){
                current = bucket.front();
                bucket.pop ();
                if (current -> leftNode == NULL) {
                    current -> leftNode = insertNode;
                    return;
                }else{
                    bucket.push (current -> leftNode);
                }
                if (current -> rightNode == NULL) {
                    current -> rightNode = insertNode;
                    return;
                }else{
                    bucket.push (current -> rightNode);
                }
            }
        }

        void removeTheDeepest (BinaryTreeNode* &root) {
            BinaryTreeNode* deepest = theDeepest (root);
            BinaryTreeNode* current;
            std::queue <BinaryTreeNode*> bucket;
            bucket.push (root);
            while (!bucket.empty ()) {
                current = bucket.front ();
                bucket.pop ();
                if (current == deepest) {
                    current = NULL;
                    delete deepest;
                    return;
                }
                if (current -> rightNode != NULL) {
                    if (current -> rightNode == deepest) {
                        current -> rightNode = NULL;
                        delete deepest;
                        return;
                    }
                    else bucket.push (current -> rightNode);
                }
                if (current -> leftNode != NULL) {
                    if (current -> leftNode == deepest) {
                        current -> leftNode = NULL;
                        delete deepest;
                        return;
                    }
                    else bucket.push (current -> leftNode);
                }
            }
        }

        /*[delete the binary tree, with the give key]*/
        // remove to make the complete tree or the perfect tree, to do this, we exchange the given node with the
        // deepest node and delete the deepest node
        void removing (BinaryTreeNode* &root, int key) {
            if (root == NULL) return;
            if (root -> leftNode == NULL && root -> rightNode == NULL) {
                if (root -> data == key) {
                    delete root;
                    root = NULL;
                }
                return;
            }
            // find the key's node and the deepest node to exchange the data then delete it
            BinaryTreeNode* key_node = NULL;
            BinaryTreeNode* current;
            std::queue <BinaryTreeNode*> bucket;
            bucket.push (root);
            while (!bucket.empty ()) {
                current = bucket.front ();
                bucket.pop ();
                if (current -> data == key) {
                    key_node = current;
                    break;
                }
                if (current -> rightNode != NULL) bucket.push (current -> rightNode);
                if (current -> leftNode != NULL) bucket.push (current -> leftNode); 
            }
            if (key_node == NULL) return;
            key_node -> data = theDeepest (root) -> data;
            removeTheDeepest (root);
        }

    public:
        BinaryTreeNode* root;
        BinaryTree (): root (NULL) {}

        // traversal on the binary tree, using print operation to illustrate
        /*[DFS traversal]*/
        /* NLR */
        // with recursion
        void preOrder () {
            preOrderRecursive (root);
        }

        void inOrder () {
            inOrderRecursive (root);
        }

        void postOrder () {
            postOrderRecursive (root);
        }

        void level_Order () {
            leverOrder (root);
        }

        void spiral_Order () {
            spiralOrder (root);
        }

        int height () {
            return Height (root);
        }

        virtual BinaryTreeNode* search (int key) {
            return find (root, key);
            
        }

        virtual void insert (int data) {
            add (root, data);
        }

        virtual void erase (int key) {
            removing (root, key);
        }
};

/*[BINARY SEARCH TREE]*/

/*
[
    operations:
        traversal - inheritate fromt binary tree
        bool isBST ()
        void insert (int data)
        void erase (int key)
        BinaryTreeNode search (int key)
]
*/

class BinarySearchTree : public BinaryTree {
    private:
        BinaryTreeNode* find (BinaryTreeNode* root,int key) {
            if (root == NULL) return NULL;
            if (root -> data == key) return root;
            else if (root -> data > key) find (root -> leftNode, key);
            else find (root -> rightNode, key);
        }

        void adding (BinaryTreeNode* &root, int data) {
            BinaryTreeNode* newNode = new BinaryTreeNode (data);
            if (root == NULL) {
                root = newNode;
                return;
            }
            if (root -> data > data) adding (root -> leftNode, data);
            else if (root -> data < data) adding (root -> rightNode, data);
        }

        BinaryTreeNode* minNode (BinaryTreeNode* root) {
            BinaryTreeNode* current = root;
            while (current != NULL && current -> leftNode != NULL)
                current = current -> leftNode;
            return current;
        }

        void remove (BinaryTreeNode* &root, int key) {
            if (root == NULL) return;
            if (root -> data < key){
                remove (root -> rightNode, key);
            }else if (root -> data > key){
                remove (root -> leftNode, key);
            }else {
                // case1 if no child both left and right
                if (root -> leftNode == NULL && root -> rightNode == NULL) {
                    delete root;
                    root = NULL;
                }
                // case2 if having either left or right
                else if (root -> leftNode == NULL) {
                    BinaryTreeNode* temp = root;
                    root = root -> rightNode;
                    delete temp;
                    //temp = NULL;
                }else if (root -> rightNode == NULL) {
                    BinaryTreeNode* temp = root;
                    root = root -> leftNode;
                    delete temp;
                   // temp = NULL;
                }
                // case3: having both left child and right child
                else if (root -> leftNode != NULL && root -> rightNode != NULL) {
                    BinaryTreeNode* minnode = minNode (root -> rightNode);
                    root -> data = minnode -> data;
                    remove (root -> rightNode, minnode -> data);
                }
            }
        }

        bool check (BinaryTreeNode* root, int min, int max) {
            if (root == NULL) return true;
            if (root -> data > max || root -> data < min) return false;
            return (check (root -> leftNode, min, root -> data - 1) && 
                    check (root -> rightNode, root -> data + 1, max));
        }

    public:
        bool isBST () {
            return check (root, INT32_MIN, INT32_MAX);
        }
        void insert (int data) {
            adding (root, data);
        }

        void erase (int key) {
            remove (root, key);
        }

        BinaryTreeNode* search (int key) {
            return find (root, key);
        }
};

/* [B-TREE]*/
// a self-balancing tree, like AVL, RB tree
/*
[
    properties:
        - All leaves are at the same level.
        - B-Tree is defined by the term minimum degree ‘t‘. The value of ‘t‘ depends upon disk block size.
        - Every node except the root must contain at least t-1 keys. The root may contain a minimum of 1 key.
        - All nodes (including root) may contain at most (2*t – 1) keys.
        - Number of children of a node is equal to the number of keys in it plus 1.
        - All keys of a node are sorted in increasing order. The child between two keys k1 and k2 contains all keys in the range from k1 and k2.
        - B-Tree grows and shrinks from the root which is unlike Binary Search Tree. Binary Search Trees grow downward and also shrink from downward.
        - Like other balanced Binary Search Trees, the time complexity to search, insert, and delete is O(log n).
        - Insertion of a Node in B-Tree happens only at Leaf Node.
]
*/

/*
[
    other definition for the B-tree
        - giving the k >= 0 -> maximun degree of the B-tree m = 2k + 1;
        - all the leaves are at the same level
        - All nodes (except root and leaves) contain at least k + 1 children nodes and at most m children nodes
            k + 1 <= number of child node <= m
        - All node must contains from k to m - 1 key, the root can be from 1 to m - 1 key
        - One node is not the leaf have n key, so the children node is n + 1 
]
*/
// relationship between m and t: t = [m/2]
/*
[
    pattern of a node

    with n children, V is the key in the datalist, C is the chil node

            C [V] C [V] C [V] C
    so with the data list contain n key, there will be n + 1 child node
]
*/

/*
[
    operations:
        BtreeNode* search (int key)
        void insert (int data)
        void erase (int key)
]
*/

// in this part, we implement the B-tree with the maximum degree (the method for this minimun is similar with this code)
class BTreeNode {
    public:
        // properties list
        std::vector <int> dataList; // store the data of the node
        std::vector <BTreeNode*> children; // store the all the child's node of its seft
        int degree; // the maximum degree, defines the range for the number of keys
        bool leaf; // if this node is the leaf

        BTreeNode (int _degree, bool _leaf): degree (_degree), leaf (_leaf) {}

        // traversal in the node
        void nodeTraversal () {
            int current;
            // trverse for 1'th child to n'th child
            for (current = 0; current < dataList.size (); current++) {
                if (!leaf) children[current] ->nodeTraversal ();
                std::cout << dataList[current] << " " ;
            }
            // traverse the last child in the node
            if (!leaf) children[current] -> nodeTraversal ();
        }

        // no recursive search
        friend std::pair <int, std::vector <BTreeNode*>> searchNode (BTreeNode* root, int key) {
            std::vector <BTreeNode*> path;
            BTreeNode* current = root;
            while (current != NULL) {
                path.push_back (current); // push the step to the target
                // using lower_bound to find the nearest with the key
                std::vector <int>::iterator it = std::lower_bound (current -> dataList.begin(), current -> dataList.end (), key);
                // if find the key in current node
                if  (it != current -> dataList.end () && *it == key) return {it - current -> dataList.begin(), path};
                else {
                    // if the node is leaf and not find in the current node
                    if (current -> leaf == true) return {-1, path};
                    current = current -> children[it - current -> dataList.begin()];
                }
            }
        }

        // devide when the number of key in the current node reaches m - 1
        // index is the index of curent in the children
        void divideChildNode (int index, BTreeNode* &current) {
            BTreeNode* newNode = new BTreeNode (current -> degree, current -> leaf);
            int t = ceil ((float)degree/2); // get minimum degree to split the current node into
                                            // two part that have the same number of key and node
            
            newNode -> dataList.resize (t-1);
            // copy the last t -1 data to the newNode
            for (int i = 0; i < t-1; ++i) {
                newNode -> dataList[i] = current -> dataList[i + t];
            }

            if (!current -> leaf) {
                newNode -> children.resize (t);
                for (int i = 0; i < t; ++i) {
                    newNode -> children[i] = current -> children[i + t];
                }
            }

            children.insert (children.begin () + index + 1, newNode );
            dataList.insert (dataList.begin () + index, current -> dataList[t-1]);
            current -> dataList.resize (t - 1);

        }

        // A utility function to insert a new key in the subtree rooted with
        // this node. The assumption is, the node must be non-full when this
        // function is called
        void insertNonFull (int data) {
            int i = dataList.size () - 1;

            // if the current child is the leaf
            if (leaf) {
                dataList.push_back (0);

                // find the approxiate position for the data
                while (i >= 0 && dataList[i] > data) {
                    dataList[i + 1] = dataList[i];
                    i--;
                }
                // insert the data to the datalist
                dataList[i + 1] = data;
            }
            // if the current node is not the leaf -> can be splitted
            else {
                // find the position
                while ( i >= 0 && dataList[i] > data) {
                    i--;
                }
                // if the child node of the current is full
                if (children[i+1] -> dataList.size () == degree - 1) {
                    // split it
                    divideChildNode (i+1, children[i+1]);

                    if (dataList[i+1] < data) {
                        i++;
                    }
                }
                children[i+1] -> insertNonFull (data);
            }

        }


        // A function that returns the index of the first key that is greater
        // or equal to k
        BTreeNode* find (int key) {
            int current = 0;
            // lower_bound with the key
            while (current < dataList.size () && dataList[current] <= key)
                ++current;
            
            // if find in the current node
            if (current < dataList.size () && dataList[current] == key)
                return this; // the address of curent node
            
            // if the node is leaf and not find in the current node
            if (leaf) return NULL;

            // if not find in the current node
            return children[current] -> find (key);
        }

        // A function to merge idx-th child of the node with (idx+1)th child of
        // the node
        void merge(int index){
            BTreeNode* child = children[index];
            BTreeNode* nextChild = children[index + 1];

            // copy next to current
            child -> dataList.push_back (dataList[index + 1]);
            for  (int i = 0; i < nextChild -> dataList.size (); ++i) {
                child -> dataList.push_back (nextChild -> dataList[i]);
            }

            if (!child -> leaf) {
                for (int i = 0; i <= nextChild -> dataList.size (); ++i) {
                    child -> children.push_back (nextChild -> children[i]);
                }
            }
            dataList.erase (dataList.begin () + index);
            dataList.erase  (dataList.begin () + index + 1);
            delete nextChild;
        }

         // A function to borrow a key from the C[idx+1]-th node and place it
        // in C[idx]th node
        void borrowFromNext(int i) {
            BTreeNode* node = children[i];
            BTreeNode* nextNode = children[i+1];

            node -> dataList.push_back (dataList[i]);
            if (!node -> leaf) {
                node -> children.push_back (nextNode -> children[0]);
            }
            dataList[i] = nextNode -> dataList[0];
            nextNode -> dataList.erase (nextNode -> dataList.begin ());
            if (!nextNode -> leaf) {
                nextNode -> children.erase  (nextNode -> children.begin ());
            }
        }

         // A function to borrow a key from the C[idx-1]-th node and place
        // it in C[idx]th node
        void borrowFromPrev(int id){
            BTreeNode* node = children[id];
            BTreeNode* prevNode = children[id-1];

            for (int i = node -> dataList.size () - 1; i >= 0; --i) { // notice to the --i :)))
                node -> dataList[i+1] = node -> dataList[i];
            }
            node -> dataList[0] = dataList[id-1];
            if (!node -> leaf) {
                for (int i = node -> children.size () - 1; i >= 0; --i) {
                    node -> children[i+1] = node -> children[i];
                }
                node -> children[0] = prevNode -> children[prevNode -> children.size () - 1];
            }

            dataList[id-1] = prevNode -> dataList[prevNode -> dataList.size () - 1];
            prevNode -> dataList.pop_back ();
            node -> dataList.insert (node -> dataList.begin(), prevNode -> dataList[prevNode -> dataList.size () -1]);
            prevNode -> dataList.pop_back ();
        }

        // A function to fill up the child node present in the idx-th
        // position in the C[] array if that child has less than t-1 keys
        void fill(int id) {
            if (id != 0 && children[id-1] -> dataList.size () >= ceil ((float)degree/2)){
                borrowFromPrev (id);
            }else if (id != dataList.size() && children[id + 1] -> dataList.size () >= ceil ((float)degree/2)) {
                borrowFromNext (id);
            }else {
                if (id != dataList.size ()) {
                    merge (id);
                }else {
                    merge (id -1);
                }
            }
        }

         // A function to get the successor of the key- where the key
        // is present in the idx-th position in the node
        int getSucc(int id) {
            BTreeNode* current = children[id + 1];
            while (!current -> leaf) {
                current = current -> children[0];
            }
            return current -> dataList[0];
        }
        

        // A function to get the predecessor of the key- where the key
        // is present in the idx-th position in the node
        int getPred(int id) {
            BTreeNode* current = children[id];
            while (!current -> leaf) {
                current = current -> children[current -> children.size () - 1];
            }
            return current -> dataList[current -> dataList.size () - 1];
        }

         // A function to remove the key present in idx-th position in
        // this node which is a leaf
        void removeFromLeaf(int id) {
            dataList.erase (dataList.begin () + id);
        }

        // A function to remove the key present in idx-th position in
        // this node which is a non-leaf node
        void removeFromNonLeaf(int id) {
            int data = dataList[id];

            if (children[id] -> dataList.size () > ceil ((float)degree/2)) {
                int predecessor = getPred (id);
                dataList[id] = predecessor;
                children[id] -> remove (predecessor);
            } else if (children[id + 1] -> dataList.size () > ceil ((float)degree/2)) {
                int successor = getSucc (id);
                dataList[id] = successor;
                children[id+1] -> remove (successor);
            } else {
                merge (id);
                children[id] -> remove (data);
            }
        }

        // A wrapper function to remove the key k in subtree rooted with
        // this node.
        void remove(int data) {
            int i = 0;

            while (i < dataList.size () && dataList[i] < data) {
                ++i;
            }

            if (i < dataList.size () && dataList[i] == data) {
                if (leaf) {
                    removeFromLeaf (i);
                }else {
                    removeFromNonLeaf (i);
                }
            }else {
                if (leaf) {
                    return;
                }

                bool flag = (i == dataList.size ());
                if (children[i] -> dataList.size () < ceil((float)degree/2)) {
                    fill (i);
                }

                if (flag && i > dataList.size ()) {
                    children[i+1] -> remove (data);
                }else {
                    children[i] -> remove (data);
                }
            }
        }

        friend class Btree;

};

class BTree {
    private:
        int degree;
        BTreeNode* root;

    public:
        BTree (int _degree): degree (_degree), root (NULL) {}

        // traverse the B-tree
        void traverse () {
            if (root != NULL)
                root -> nodeTraversal ();
        }

        // search for a key in B-Tree
        BTreeNode* search (int key) {
            if  (root == NULL)
                return NULL;
            else root -> find (key);
        }

        void insert (int data) {
            if (root == NULL) {
                BTreeNode* newNode = new BTreeNode (degree, true);
                newNode -> dataList.push_back (data);
                root = newNode;
            }else {
                if (root -> dataList.size () == degree -1) {
                    BTreeNode* newNode = new BTreeNode (degree, false);
                    newNode -> children.push_back (root);
                    newNode -> divideChildNode (0, root);
                    int i = 0;
                    if (newNode -> dataList[0] < data) {
                        i++;
                    }
                    newNode -> children[i] -> insertNonFull (data);
                    root = newNode;
                }else {
                    root -> insertNonFull (data);
                }
            }
        }

        void erase (int data) {
            if (root == NULL) return;
            root -> remove (data);

            if (root -> dataList.size () == 0) {
                BTreeNode* node = root;
                if (root -> leaf) {
                    root = NULL;
                }else {
                    root -> children[0];
                }
                delete node;
            }
        }
};

/*HASHING - HASH TABLE - HASH MAP*/

/*Something important*/
/*
[
    *definition:
        Hashing is a fundamental data structure that efficiently stores and retrieves data in a way that allows for quick access.
        It involves mapping data to a specific index in a hash table using a hash function that enables fast retrieval of information
        based on its key. This method is commonly used in databases, caching systems, and various programming applications to optimize 
        search and retrieval operations.
    
    *hash function
        The hash function is a function that takes a key and returns an index into the hash table. The goal of a hash function is to distribute 
        keys evenly across the hash table, minimizing collisions (when two keys map to the same index).

        Common hash functions include:

            Division Method: Key % Hash Table Size
            Multiplication Method: (Key * Constant) % Hash Table Size
            Universal Hashing: A family of hash functions designed to minimize collisions
        
    
    *Components of hashing:
        Key: A Key can be anything string or integer which is fed as input in the hash function the technique that determines 
             an index or location for storage of an item in a data structure.
        Hash Function: The hash function receives the input key and returns the index of an element in an array called a hash table.
             The index is known as the hash index .
        Hash Table: Hash table is a data structure that maps keys to values using a special function called a hash function.
             Hash stores the data in an associative manner in an array where each data value has its own unique index

    *hash collision
        A hash collision occurs when two different keys map to the same index in a hash table. This can happen even with a good hash function, 
        especially if the hash table is full or the keys are similar.
    
    *Collision Resolution Techniques
        Open Addressing (closed hashing):
            Linear Probing: Search for an empty slot sequentially
            Quadratic Probing: Search for an empty slot using a quadratic function
        Closed Addressing (Open chaining):
            Chaining: Store colliding keys in a linked list or binary search tree at each index
            Cuckoo Hashing: Use multiple hash functions to distribute keys
            
    for the Open Addressing
    -> linear probing step by step
        Calculate the hash key. i.e. key = data % size
        Check, if hashTable[key] is empty, store the value directly by hashTable[key] = data
        If the hash index already has some value then, check for next index using key = (key+1) % size
        Check, if the next index is available hashTable[key] then store the value. Otherwise try for next index.
        Do the above process till we find the space.
    
    -> Quadraticn Probing
        If the slot hash(x) % n is full, then we try (hash(x) + 1 2 ) % n.
        If (hash(x) + 1 2 ) % n is also full, then we try (hash(x) + 2 2 ) % n.
        If (hash(x) + 2 2 ) % n is also full, then we try (hash(x) + 3 2 ) % n.
        This process will be repeated for all the values of i until an empty slot is found
    
    -> doube hashing
        h(k, i) = (h1(k) + i * h2(k)) % n 
]
*/

/* INDEX MAPPING (TRIVIAL HASHING)*/
/*
{
    Assign all the values of the hash matrix as 0.
    Traverse the given array:

    If the element ele is non negative assign 
            hash[ele][0] as 1.
    Else take the absolute value of ele and 
            assign hash[ele][1] as 1.
}
*/

bool search (int key, vii hashMap) {
    if (key >= 0 && hashMap[key][0] == 1) return true;
    else return false;

    if (key < 0 && hashMap[-key][1] == 1) return true;
    else return false;
}

void insert (int key, vii& hashMap) {
    if  (key >= 0) {
        hashMap[key][0] = 1;
        return;
    }
    hashMap[-key][1] = 1;

}
/*DIVIDE HASH FUNCTION*/
// hash (x) = x mod N
// x is the given key
// N is the size of the hash map (hash table)

/*MULTIPLATION HASH FUNCTION*/
// hash (x) = [N * (x*A mod 1)]
// N ís the size of hash map
// x is the given key
// A = (sqrt(5) - 1) / 2

/*SEPERATE CHAINING COLLISION HANDLING*/
// giving a hash table size N, hash function: index = hash(x) = x mod n; (using divide hash function)
// if there are two or more data have the same index, then stores them in chain
// chain can be: linked list, Tree, Dynamic sized Array, Seft-balance tree


/*OPEN ADDRESSING COLLISION HANDLING*/

/*  
    giving a hash table size N
    
    LINEAR PROBING
    formula: hash (x) = x mod N
            rehash (x)  = (x + 1) mod N (if hash(x) is full) -> rehash = (x + 2) nod N if hash (x+1) if full
        
        => hash (x) = (hash'(x) + i) mod N = (mainHashfunction(x) + i) mod N
        hash'(x) is the main hash function of the hash table
        i = {0, 1, 2, 3, 4, .., N-1}, is the number iterate to find the positon for the data

    QUADRATIC PROBING
    formulaL: hash (x) = (hash'(x) + c1*i + c2* (i*i)) mod N

        c1 and c2 or more is constant number, we normaly choose c1 = 0 and c2 = 1 to simply the calculating process
        hash'(x) is the main hash function of the hash table
        i = {0, 1, 2, 3, 4, .., N-1}, is the number iterate to find the positon for the data

    DOUBLE HASHING
    formula: hash (x) = (hash1(x) + i * hash2(x)) mod N
        hash1 and hash2 is random or builtin hash function and unchanged
        popular:
        hash1 can be hash (x) = x mod N
        hash2 can be Prime - (x mod Prime), Prime is the prime number which is the nearest number which N
*/

class LinearHashing {
    private:
        int Table_size;
        // using vector to store the data
        vi hashTable;

        int mainHash (int key) {
            return key % Table_size;
        }
    public:
        const int DELETED = INT32_MIN;
        const int EMPTY = -1;

        LinearHashing (int hash_size): Table_size (hash_size){
            hashTable.resize (Table_size);
            std::fill (hashTable.begin (), hashTable.end (), -1);
        }

        void insert (int key) {
            int id = 0;
            for (int i = 0; i < Table_size - 1; ++i) {
                id = mainHash (key + i) % Table_size;
                if (hashTable[id] == -1 || hashTable[id] == DELETED){
                    hashTable[id] = key;
                    break;
                }
            }
            return;
        }

        void remove (int key) {
            int id = 0;
            for (int i = 0; i < Table_size; ++i) {
                id = mainHash (key + i) % Table_size;
                if (hashTable[id] == key) {
                    hashTable[id] = DELETED;
                    return;
                }
            }
            return;
        }

        bool search (int key) {
            int id = 0;
            for (int i = 0; i < Table_size; ++i) {
                id = mainHash (key + i) % Table_size;
                if (hashTable[id] == key) {
                    return true;
                }
            }
            return false;
        }
    ~LinearHashing () {
        Table_size = 0;
        hashTable.resize (0);
    }

};

class QuadraticHashing {
    private:
        int Table_size;
        int c1;
        int c2;
        vi hashTable;
        
        int mainHash (int key) {
            return key % Table_size;
        }

    public:
        const int DELETED = INT32_MIN;
        const int EMPTY = -1;

        QuadraticHashing (int size, int C1, int C2): Table_size (size), c1 (C1), c2 (C2) {
            hashTable.resize (Table_size);
            std::fill (hashTable.begin(), hashTable.end (), EMPTY);
        }   

        void insert (int key) {
            int id = 0;
            for (int i = 0; i < Table_size - 1; ++i) {
                id = (mainHash (key) + c1*i + c2 * (i*i))% Table_size;
                if (hashTable[id] == -1 || hashTable[id] == DELETED){
                    hashTable[id] = key;
                    break;
                }
            }
            return;
        }

        void remove (int key) {
            int id = 0;
            for (int i = 0; i < Table_size; ++i) {
                id = (mainHash (key) + c1*i + c2 * (i*i))% Table_size;
                if (hashTable[id] == key) {
                    hashTable[id] = DELETED;
                    return;
                }
            }
            return;
        }

        bool search (int key) {
            int id = 0;
            for (int i = 0; i < Table_size; ++i) {
                id = (mainHash (key) + c1*i + c2 * (i*i))% Table_size;
                if (hashTable[id] == key) {
                    return true;
                }
            }
            return false;
        }
    ~QuadraticHashing () {
        Table_size = 0;
        c1 = 0;
        c2 = 0;
        hashTable.resize (0);
    }
};

#define MAX_SIZE 10000001ll 

class doubleHash { 

	int TABLE_SIZE, keysPresent, PRIME; 
	vector<int> hashTable; 
	std::bitset<MAX_SIZE> isPrime; 

	/* Function to set sieve of Eratosthenes. */
	void __setSieve(){ 
		isPrime[0] = isPrime[1] = 1; 
		for(long long i = 2; i*i <= MAX_SIZE; i++) 
			if(isPrime[i] == 0) 
				for(long long j = i*i; j <= MAX_SIZE; j += i) 
					isPrime[j] = 1; 

	} 

	int inline hash1(int value){ 
		return value%TABLE_SIZE; 
	} 
	
	int inline hash2(int value){	 
		return PRIME - (value%PRIME); 
	} 

	bool inline isFull(){ 
		return (TABLE_SIZE == keysPresent); 
	} 

	public: 

	doubleHash(int n){ 
		__setSieve(); 
		TABLE_SIZE = n; 

		/* Find the largest prime number smaller than hash table's size. */
		PRIME = TABLE_SIZE - 1; 
		while(isPrime[PRIME] == 1) 
			PRIME--; 

		keysPresent = 0; 

		/* Fill the hash table with -1 (empty entries). */
		for(int i = 0; i < TABLE_SIZE; i++) 
			hashTable.push_back(-1); 
	} 

	void __printPrime(long long n){ 
		for(long long i = 0; i <= n; i++) 
			if(isPrime[i] == 0) 
				std::cout<<i<<", "; 
		std::cout<<'\n'; 
	} 

	/* Function to insert value in hash table */
	void insert(int value){ 

		if(value == -1 || value == -2){ 
			std::cout<<("ERROR : -1 and -2 can't be inserted in the table\n"); 
		} 

		if(isFull()){ 
			std::cout<<("ERROR : Hash Table Full\n"); 
			return; 
		} 
		
		int probe = hash1(value), offset = hash2(value); // in linear probing offset = 1; 
		
		while(hashTable[probe] != -1){ 
			if(-2 == hashTable[probe])				 
				break;								 // insert at deleted element's location 
			probe = (probe+offset) % TABLE_SIZE; 
		} 

		hashTable[probe] = value; 
		keysPresent += 1; 
	} 

	void erase(int value){ 
		/* Return if element is not present */
		if(!search(value)) 
			return;	 
		
		int probe = hash1(value), offset = hash2(value); 

		while(hashTable[probe] != -1) 
			if(hashTable[probe] == value){ 
				hashTable[probe] = -2;		 // mark element as deleted (rather than unvisited(-1)). 
				keysPresent--; 
				return; 
			} 
			else
				probe = (probe + offset) % TABLE_SIZE; 

	} 

	bool search(int value){ 
		int probe = hash1(value), offset = hash2(value), initialPos = probe; 
		bool firstItr = true; 

		while(1){ 
			if(hashTable[probe] == -1)				 // Stop search if -1 is encountered. 
				break; 
			else if(hashTable[probe] == value)		 // Stop search after finding the element. 
				return true; 
			else if(probe == initialPos && !firstItr) // Stop search if one complete traversal of hash table is completed. 
				return false; 
			else
				probe = ((probe + offset) % TABLE_SIZE); // if none of the above cases occur then update the index and check at it. 

			firstItr = false; 
		} 
		return false; 
	} 

	/* Function to display the hash table. */
	void print(){ 
		for(int i = 0; i < TABLE_SIZE; i++) 
			std::cout<<hashTable[i]<<", "; 
		std::cout<<"\n"; 
	} 

}; 

/*
[GRAPH]
*/
// in this session, if i don't mention the type of graph, default both type of graph: undirected and directed

// REPRESENTATION OF GRAPH
/*
[
    the Adjacency Matrix:
        std::vector <std::vector <int>> adjMatrix
            properties: the graph is stored in the form of the 2D matrix where rows and columns denote vertices.
                         Each entry in the matrix represents the weight of the edge between those vertices
                         if u and v are adjacency vertices, expressing with 1 or the weight of the edge between them
                        example
                       1 2 3 4 5
                    1  0 1 0 0 0
                    2  1 0 1 0 1
                    3  0 1 0 0 0
                    4  0 0 0 0 0 
                    5  0 1 0 0 0 

    the edge list: list contain 3 column (if is weighted graph) and 2 column (if is un-weighted graph)
            struct edge{
                int first_vertex,
                int last_vertex;
                int weight;
            };

            std::vector <edge> edgeList; // illustrate both weighted and no-weighted graph
            std::vector <pair <int, int>> edgeList // no-weighted graph

            example: first last weight (optional)
                     1      2    0
                     2      3    0
                     2      5    0

    Adjacency List: store vertex u (adjList[u]) contain a vector stores all the adjacency vertices of it
        std::vector <std::vector <int>> adjList;
        example
                    1 -> {2}
                    2 -> {1, 3, 5}
                    3 -> {2}
                    4 -> {}
                    5 -> {2}

]
*/

// representation
// edge list -> adjacency matrix
std::vector <std::vector <int>> makeAdjMatrix (std::vector <std::vector <int>> edgeList) {
    std::vector <std::vector <int>> adjMatrix;
    int maxElement = 0;
    for (auto edgelist : edgeList) {
        maxElement = std::max (maxElement, *max_element (edgelist.begin (), edgelist.end ()));
    }
    adjMatrix.resize (maxElement +  1);
    for (auto& row : adjMatrix) {
        row.resize (maxElement);
        for (int& i : row) i = 0;
    }
    for (std::vector <int> edge : edgeList) {
        adjMatrix[edge[0]][edge[1]] = 1; // or weight
        adjMatrix[edge[1]][edge[0]] = 1;
    }
    return adjMatrix;
}

std::vector <std::vector <int>> makeAdjMatrix_directed (std::vector <std::vector <int>> edgeList) {
    std::vector <std::vector <int>> adjMatrix;
    int maxElement = 0;
    for (auto edgelist : edgeList) {
        maxElement = std::max (maxElement, *max_element (edgelist.begin (), edgelist.end ()));
    }
    adjMatrix.resize (maxElement +  1);
    for (auto& row : adjMatrix) {
        row.resize (maxElement);
        for (int& i : row) i = 0;
    }
    for (std::vector <int> edge : edgeList) {
        adjMatrix[edge[0]][edge[1]] = 1; // or weight
    }
    return adjMatrix;
}


// edge list -> adjacency list
std::vector <std::vector <int>> makeAdjList (std::vector <std::vector<int>> edgeList) {
    int maxElement = 0;
    for (auto edgelist : edgeList) {
        maxElement = std::max (maxElement, *max_element (edgelist.begin (), edgelist.end ()));
    }
    std::vector <std::vector <int>> adjList (maxElement + 1);
    for (std::vector <int> edge : edgeList) {
        int u = edge[0];
        int v = edge[1];
        adjList[u].push_back (v);
        adjList[v].push_back (u);
    }

    return adjList;
}

std::vector <std::vector <int>> makeAdjList_directed (std::vector <std::vector<int>> edgeList) {
    int maxElement = 0;
    for (auto edgelist : edgeList) {
        maxElement = std::max (maxElement, *max_element (edgelist.begin (), edgelist.end ()));
    }
    std::vector <std::vector <int>> adjList (maxElement + 1);
    for (std::vector <int> edge : edgeList) {
        int u = edge[0];
        int v = edge[1];
        adjList[u].push_back (v);
    }

    return adjList;
}

/*[DEPTH FIRST SEARCH IN THE GRAPH - DFS]*/
/*
[
    complexity
        O (V + E): the adjacency list
        O (V * V) the adjacency matrix
        O (V * E) the edge list
]
*/

/*
[
    1. Detecting cycle in a graph: A graph has a cycle if and only if we see a back edge during DFS. So we can run DFS for the graph and check for back edges.

    2. Path Finding: We can specialize the DFS algorithm to find a path between two given vertices u and z. 

        Call DFS(G, u) with u as the start vertex. 
        Use a stack S to keep track of the path between the start vertex and the current vertex. 
        As soon as destination vertex z is encountered, return the path as the contents of the stack

    3. Topological Sorting: Topological Sorting is mainly used for scheduling jobs from the given dependencies among jobs. In computer science, 
    applications of this type arise in instruction scheduling, ordering of formula cell evaluation when recomputing formula values in spreadsheets, logic synthesis, 
    determining the order of compilation tasks to perform in makefiles, data serialization, and resolving symbol dependencies in linkers.

    4. To test if a graph is bipartite: We can augment either BFS or DFS when we first discover a new vertex, color it opposite its parents, and for each other edge, 
    check it doesn’t link two vertices of the same color. The first vertex in any connected component can be red or black.

    5. Finding Strongly Connected Components of a graph: A directed graph is called strongly connected if there is a path from each vertex in the graph to every other vertex.
    (See this for DFS-based algo for finding Strongly Connected Components)

    6. Solving puzzles with only one solution: such as mazes. (DFS can be adapted to find all solutions to a maze by only including nodes on the current path in the visited set.).

    7. Web crawlers: Depth-first search can be used in the implementation of web crawlers to explore the links on a website.

    8. Maze generation: Depth-first search can be used to generate random mazes.

    9. Model checking: Depth-first search can be used in model checking, which is the process of checking that a model of a system meets a certain set of properties.

    10. Backtracking: Depth-first search can be used in backtracking algorithms.
]
*/
// DFS 
// [in the adjacency list]
// recursion
void DFS (int vertex,vii adjList, std::vector <bool>& visited) {
    std::cout << vertex << " ";
    visited[vertex] = true;
    for (int otherVertex : adjList[vertex]) {
        if (!visited[otherVertex])
            DFS (otherVertex, adjList, visited);
    }
}

// non-recursion
void DFS_NR (int vertex, vii adjlist) {
    int maxVertex = adjlist.size ();
    std::vector <bool> visited (maxVertex, false);
    std::stack <int> verticesBucket;
    verticesBucket.push (vertex);
    while (!verticesBucket.empty ()) {
        int currentVertex = verticesBucket.top ();
        verticesBucket.pop ();
        
        if (!visited[currentVertex]) {
            std::cout << currentVertex << " ";
            visited[currentVertex] = true;
        }
        
        for (int i : adjlist[currentVertex]) {
            if (!visited[i])
                verticesBucket.push (i);
        }
    }
}

// [in the adjacency matrix]
// reucursion
void DFS_M (int vertex, vii& adjMatrix, std::vector <bool>& visited) {
    std::cout << vertex << " ";
    visited[vertex] = true;

    for (int i = 0; i < adjMatrix[vertex].size (); ++i) {
        if (adjMatrix[vertex][i] == 1 && !visited[i]){
            DFS_M (i, adjMatrix, visited);
        }
    }
}

// non - recursive
void DFS_M_NR (int vertex, vii adjMatrix) {
    int numVertices = adjMatrix.size ();
    std::vector <bool> visited  (numVertices, false);
    std::stack <int> verticesBucket;
    verticesBucket.push (vertex);
    while (!verticesBucket.empty ()) {
        int currentVertex = verticesBucket.top ();
        verticesBucket.pop ();
        
        if (!visited[currentVertex]){
            std::cout << currentVertex << " ";
            visited[currentVertex] = true;
        }
        
        for (int i = 0; i < numVertices; ++i ) {
            if (adjMatrix[currentVertex][i] == 1 && !visited[i]) {
                verticesBucket.push (i);
            }
        }
    }
}

// [in the edge list]
// using vector <pair <int, int>>
// recursion
void DFS_EL (int vertex, vpii edgeList, std::vector <bool>& visited) {
    std::cout << vertex << " ";
    visited[vertex] = true;
    for (auto it : edgeList) {
        if (it.first == vertex) {
            if (!visited[it.second]) {
                DFS_EL (it.second, edgeList, visited);
            }
        }
        if (it.second == vertex) {
            if (!visited[it.first]){
                DFS_EL (it.first, edgeList, visited);
            }
        }
    }
}

/*[BREATH FIRST SEARCH IN THE GRAPH - BFS]*/
/*
[
    complexity
        O (V + E): the adjacency list
        O (V * V) the adjacency matrix
        O (V * E) the edge list
]
*/

/*
[
    1. Shortest Path and Minimum Spanning Tree for unweighted graph: In an unweighted graph, the shortest path is the path with the least number of edges. 
    With Breadth First, we always reach a vertex from a given source using the minimum number of edges. Also, in the case of unweighted graphs, any spanning 
    tree is Minimum Spanning Tree and we can use either Depth or Breadth first traversal for finding a spanning tree. 

    2. Minimum Spanning Tree for weighted graphs: We can also find Minimum Spanning Tree for weighted graphs using BFT, but the condition is that the weight 
    should be non-negative and the same for each pair of vertices.

    3. Peer-to-Peer Networks: In Peer-to-Peer Networks like BitTorrent, Breadth First Search is used to find all neighbor nodes. 

    4. Crawlers in Search Engines: Crawlers build an index using Breadth First. The idea is to start from the source page and follow all links from the source 
    and keep doing the same. Depth First Traversal can also be used for crawlers, but the advantage of Breadth First Traversal is, the depth or levels of the built tree 
    can be limited.

    5. Social Networking Websites: In social networks, we can find people within a given distance ‘k’ from a person using Breadth First Search till ‘k’ levels.

    6. GPS Navigation systems: Breadth First Search is used to find all neighboring locations.

    7. Broadcasting in Network: In networks, a broadcasted packet follows Breadth First Search to reach all nodes.

    8. In Garbage Collection: Breadth First Search is used in copying garbage collection using Cheney’s algorithm. Breadth First Search is preferred over Depth First Search 
    because of a better locality of reference.

    9. Cycle detection in undirected graph: In undirected graphs, either Breadth First Search or Depth First Search can be used to detect a cycle. We can use BFS to detect 
    cycle in a directed graph also.

    10. Ford–Fulkerson algorithm In Ford – Fulkerson algorithm, we can either use Breadth First or Depth First Traversal to find the maximum flow. Breadth First Traversal 
    is preferred as it reduces the worst-case time complexity to O(VE2).

    11. To test if a graph is Bipartite: We can either use Breadth First or Depth First Traversal.

    12. Path Finding: We can either use Breadth First or Depth First Traversal to find if there is a path between two vertices. 

    13. Finding all nodes within one connected component: We can either use Breadth First or Depth First Traversal to find all nodes reachable from a given node. 

    14. AI: In AI, BFS is used in traversing a game tree to find the best move.

    15. Network Security: In the field of network security, BFS is used in traversing a network to find all the devices connected to it.

    16. Connected Component: We can find all connected components in an undirected graph.

    17. Topological sorting: BFS can be used to find a topological ordering of the nodes in a directed acyclic graph (DAG).

    18. Image processing: BFS can be used to flood-fill an image with a particular color or to find connected components of pixels.

    19. Recommender systems: BFS can be used to find similar items in a large dataset by traversing the items’ connections in a similarity graph.

    20. Other usages: Many algorithms like Prim’s Minimum Spanning Tree and Dijkstra’s Single Source Shortest Path use structures similar to Breadth First Search. 
]
*/

// BFS in the adjacency list
void BFS (int vertex, vii adjList) {
    std::vector <bool> visited (adjList.size (), false);
    std::queue <int> verticesBucket;

    verticesBucket.push (vertex);
    visited[vertex] = true;

    while (!verticesBucket.empty ()) {
        int currentVertex = verticesBucket.front ();
        verticesBucket.pop ();
        std::cout << currentVertex << " ";
        
        for (auto i : adjList[currentVertex]) {
            if (!visited[i]){
                verticesBucket.push (i);
                visited[i] = true;
            }
        }
    }   
}

// BFS in the adjacency matrix
void BFS_M (int vertex, vii adjMatrix) {
    int numVertices = adjMatrix.size ();
    std::queue <int> verticesBucket;
    std::vector <bool> visited (numVertices, false);
    verticesBucket.push (vertex);
    visited[vertex] = true;

    while (!verticesBucket.empty()) {
        int currentVertex = verticesBucket.front ();
        verticesBucket.pop ();

        std::cout << currentVertex << " ";

       for (int i = 0; i < numVertices; ++i) {
            if (adjMatrix[currentVertex][i] == 1 && !visited[i]) {
                verticesBucket.push (i);
                visited[i] = true;
            }
       }
    }

}
/*=====================================================================================================================================================*/
// BFS the disconnected graph, counting the connected components
// adjacency matrix
void BFS_M_opt (int vertex, vii adjMatrix,  vi& visited) {
    int numVertices = adjMatrix.size ();
    std::queue <int> verticesBucket;
    verticesBucket.push (vertex);
    visited[vertex] = 1;

    while (!verticesBucket.empty()) {
        int currentVertex = verticesBucket.front ();
        verticesBucket.pop ();

        std::cout << currentVertex << " ";

       for (int i = 0; i < numVertices; ++i) {
            if (adjMatrix[currentVertex][i] == 1 && !visited[i]) {
                verticesBucket.push (i);
                visited[i] = 1;
            }
       }
    }

}

void BFS_DIS_GR_Matrix (vii adjMatrix) {
    int numVertices = adjMatrix.size ();
    std::vector <int> visited (numVertices, 0);
    for (int i = 0; i < numVertices; ++i) {
        if (visited[i] == 0) {
            BFS_M_opt (i, adjMatrix, visited); // DFS instead
            std::cout << '\n';
        } 
    }
}


// adjacency list
void BFS_opt (int vertex, vii adjList, vi& visited) {
    std::queue <int> verticesBucket;

    verticesBucket.push (vertex);
    visited[vertex] = 1;

    while (!verticesBucket.empty ()) {
        int currentVertex = verticesBucket.front ();
        verticesBucket.pop ();
        std::cout << currentVertex << " ";
        
        for (auto i : adjList[currentVertex]) {
            if (!visited[i]){
                verticesBucket.push (i);
                visited[i] = 1;
            }
        }
    }   
}

void BFS_DIS_GR_LIST (vii adjList) {
    int numVertices = adjList.size ();
    std::vector <int> visited (numVertices, 0);
    for (int i = 0; i < numVertices; ++i) {
        if (visited[i] == 0) {
            BFS_opt (i, adjList, visited); // DFS instead
            std::cout << '\n';
        } 
    }
}
/*==================================================================================================================================*/
//counting number of connected components in the graph
// implementation for the adjacency list, the adjacency matrix is similar to this way
void BFS__(int s, vii adjList, vi& visited) {
    std::queue <int> bucket;
    bucket.push (s);
    visited[s] = true;
    while (!bucket.empty ()) {
        int u = bucket.front ();
        bucket.pop ();
        
        for (int v : adjList[u]) {
            if (!visited[v]) {
                bucket.push (v);;
                visited[v] = 1;
            }
        }

    }
}
int countingConnectedComponent (vii adjList) {
    int numVertices = adjList.size ();
    int count = 0;
    std::vector <int> visited (numVertices, 0);
    for (int i = 0; i < numVertices; ++i) {
        if (visited[i] == 0) {
            BFS__ (i, adjList, visited); // DFS instead
            ++count;
        } 
    }
    return count;
}

/*==================================================================================================================================*/

// 0 - 1 graph: a graph where every edge has weight as either 0 or 1

// check if there is a path between u and v, call the BFS or DFS then check the visited[u] and visited[v] are equal to true;
// here i use BFS

void BFS_ (int s,vii adjList, vi& visited, vi& parent) {
    std::queue <int> bucket;
    bucket.push (s);
    visited[s] = true;
    while (!bucket.empty ()) {
        int u = bucket.front ();
        bucket.pop ();
        
        for (int v : adjList[u]) {
            if (!visited[v]) {
                parent[v] = u;
                bucket.push (v);;
                visited[v] = 1;
            }
        }

    }
}

void getPath (int u, int v, vii ajdList ) {
    std::vector <int> parent (ajdList.size (), 0);
    std::vector <int> visited  (ajdList.size (), 0);
    BFS_ (u,ajdList, visited, parent);
    if (!visited[v]) std::cout << "not path found";
    else {
        std::vector <int> path;
        while (v != u) {
            path.push_back (v);
            v = parent[v];
        }
        path.push_back (u);
        std::reverse(path.begin (), path.end ());
        for (auto i: path) std::cout << i <<  " ";
    }
}

/*=========================================================================================================================*/

/*
[
    Printing pre and post visited times in DFS of a graph

    Pre-visit and Post-visit numbers are the extra information that can be stored while running a DFS on a graph and which turns out
    to be really useful. Pre-visit number tells the time at which the node gets into the recursion stack and Post-visit number tells the
    time at which the node comes out from recursion stack of DFS.

    application:
        Pre and Post numbers are widely used in graph algorithms. For example, they can be used to find out whether a particular node lies 
        in the sub-tree of another node. 
        To find whether u lies in the sub-tree of v or not we just compare the pre and post number of u and v.
        If pre[u] > pre[v] and post[u] < post[v] then u lies in the sub-tree of v otherwise not.
        
]
*/
void pre_post_Time (int source, vii adjList, vi& pre, vi& post, vi& visited, int Time) {
    pre[source] = Time;
    visited[source] = 1;
    Time++;
    for (auto v : adjList[source]) {
        if (!visited[v]) {
            pre_post_Time (v, adjList, pre, post, visited, Time);
        }
    }
    post[source] = Time;
    Time++;
}

// usage
// for (int i = 1; i < adjList.size (); ++i) {
//     if (!v[i]) {
//         int Time = 1;
//         pre_post_Time(i, adjMatrix, pre, pos, v, Time);
//     }
// }

/*==============================================================================================================*/
/*
[       
    Transitive Closure of a Graph using DFS: check if there is a path from u to v, then mark it = 1
    using     Floyd Warshall Algorithm

    properties:
        adjList
        vii tc where tc[u][v] = 1 if there is a path and otherwise

    step by step
        -Create a matrix tc[V][V] that would finally have transitive closure of the given graph. Initialize all entries of tc[][] as 0.
        -Call DFS for every node of the graph to mark reachable vertices in tc[][]. In recursive calls to DFS, we don’t call DFS for an
         adjacent vertex if it is already marked as reachable in tc[][].
             
    //The code uses adjacency list representation of input graph and builds a matrix tc[V][V] such that tc[u][v] would be true if v is reachable from u.
]
*/
void DFS__(int u, int v, vii adjList, vii& tc) {
    tc[u][v] = 1; // there is a available path from u -> v
    
    for (auto s : adjList[v]) {
        // if there is not a path between u -> s
        //If s is not yet connected to u, explore further
        if (!tc[u][s]) {
            // check 
            DFS__ (u, s, adjList, tc);
        }
    }
    // explain: if there is a path between u and v, so all the adjacency vertex of v can be reached by u
}

//Floyd Warshall Algorithm
void createTransitiveClosure (vii adjList) {
    vii tc (adjList.size (), vi (adjList.size(), 0));
    // all vertex can be reached by its seft and create the TC
    for (int i = 0; i <adjList.size (); ++i) {
        DFS__ (i, i, adjList, tc);
    }
    // printTransitive Closure
    // base on Floyd Warshall Algorithm
    for (int i = 0; i < adjList.size (); ++i){
        for (int j = 0; j < adjList.size (); ++j)
            std::cout << tc[i][j] <<" ";
        std::cout << '\n';
    }
}

/*===========================================================================================================================*/
/*USE ON THE DIRECTED GRAPH*/
/*
[
    Tree, Back, Edge and Cross Edges in DFS of Graph
        Tree Edge: It is an edge which is present in the tree obtained after applying DFS on the graph
        Forward Edge: It is an edge (u, v) such that v is a descendant but not part of the DFS tree. 
        Back edge: It is an edge (u, v) such that v is the ancestor of node u but is not part of the DFS tree. 
        Cross Edge: It is an edge that connects two nodes such that they do not have any ancestor and a descendant relationship between them.


    here i use pre and post time to find all of type of edges
]
*/

void DFS_and_FindEdge (int u, vii adjList, vi& pre, vi& post, vi& visited, int& Time) {
    pre[u] = Time;
    visited[u] = 1;
    Time++;
    for (auto v : adjList[u]) {
        if (!visited[v]){
            std::cout << "tree edge: " << u << "->" << v << '\n';
            DFS_and_FindEdge (v, adjList, pre, post, visited, Time);
        }else {
            // when the parent node is traversed after the neighbour node
            if (pre[u] > pre[v] && post[u] < post[v]) {
                std::cout << "back edge: " << u << "->" << v << '\n';
            }
            // when the neighbour node is a descendant but not a part of tree
            else if (pre[u] < pre[v] && post[u] > post[v]) {
                std::cout << "forward edge: " << u << "->" << v << '\n';
            }else if (pre[u] > pre[v] && post[u] > post[v]) {
                std::cout << "cross edge: " << u << "->" << v << '\n';
            }
        }
    }
    post[u] = Time;
    Time++;
}

void printTypeOfEdges (vii adjList) {
    vi visited (adjList.size (), 0);
    vi pre (adjList.size ());
    vi post (adjList.size ());
    int Time = 0;
    for (int i = 0; i < adjList.size (); ++i) {
        if (!visited[i]) {
            DFS_and_FindEdge (i, adjList, pre, post, visited, Time);
        }
    }

}

/*=======================================================================================================*/
/* GRAPH COLORING*/
/*
[
    Graph coloring refers to the problem of coloring vertices of a graph in such a way that no two adjacent vertices have the same color. 
    This is also called the vertex coloring problem. If coloring is done using at most m colors, it is called m-coloring.


]
*/

/*==========================================================================================================*/
/*KOSARAJU ALGORITHM*/
/*
[
    SCC: strongly connected components
]
*/
/*USING ON THE DRICTED GRAPH*/

//Check if a graph is strongly connected


// driver code
int main () {

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr); 
    std::cout.tie(nullptr);

    std::vector <std::vector <int>> edgeList;
    int m, n;
    while (std::cin >> m >> n) {
        edgeList.push_back ({m, n});
    }
    std::vector <std::vector <int>> adjMatrix = makeAdjList_directed(edgeList);

    int k = 0;
    for (auto i : adjMatrix) {
        std::cout << k++ << ": ";
        for (auto j : i) std::cout << j <<  " ";
        std::cout << '\n';
    }
//     std::vector <int> v (1000, false);
//     //DFS_matrix_NR( 4, adjMatrix);
//     std::cout << '\n';
//     //DFS_NR (2,adjMatrix);
//    // BFS (1, adjMatrix);
//    //BFS_DIS_GR_LIST (adjMatrix);
//   // std::cout << countingConnectedComponent (adjMatrix);
//    getPath (8, 7, adjMatrix);
//    vi pre (adjMatrix.size () , 0);
//    vi pos (adjMatrix.size (), 0);
//    for (int i = 6; i < adjMatrix.size (); ++i) {
//         if (!v[i]) {
//             int Time = 1;
//              pre_post_Time(i, adjMatrix, pre, pos, v, Time);
//         }
//    }
  
//    std::cout << '\n';
//    for (int i : pre) std::cout << i << " ";
//    std::cout << '\n';
//    for (int i : pos) std::cout << i << " ";
//    std::cout << '\n';
//    createTransitiveClosure (adjMatrix);
//    std::cout << '\n';
   printTypeOfEdges (adjMatrix);

    //int a[] = {1,1, 1,1, 1,1, 1,1 , 1, 1, 1};
    vi a (10 ,1);
    int p = 0;
    for (auto&i : a) {
        std::cout << ++i << a[p++];
        a[p-1] = 100;
    }
   

    return 0;
}
