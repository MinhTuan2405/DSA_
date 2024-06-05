#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class BTreeNode {
public:
    vector<int> keys;  // A vector to store keys in the node
    vector<BTreeNode*> children;  // A vector to store child pointers
    bool leaf;  // Boolean value to check if the node is a leaf or not
    int maxDegree;  // Maximum degree (defines the range for number of keys)

    BTreeNode(int maxDegree, bool leaf);

    void insertNonFull(int key);
    void splitChild(int i, BTreeNode* y);
    void traverse();

    BTreeNode* search(int key);
    void remove(int key);
    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);
    int getPred(int idx);
    int getSucc(int idx);
    void fill(int idx);
    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);
    void merge(int idx);

    friend class BTree;
};

BTreeNode::BTreeNode(int maxDegree, bool leaf) {
    this->maxDegree = maxDegree;
    this->leaf = leaf;
}

void BTreeNode::insertNonFull(int key) {
    int i = keys.size() - 1;

    if (leaf) {
        keys.push_back(0);

        while (i >= 0 && keys[i] > key) {
            keys[i + 1] = keys[i];
            i--;
        }
        keys[i + 1] = key;
    } else {
        while (i >= 0 && keys[i] > key) {
            i--;
        }

        if (children[i + 1]->keys.size() == maxDegree - 1) {
            splitChild(i + 1, children[i + 1]);

            if (keys[i + 1] < key) {
                i++;
            }
        }
        children[i + 1]->insertNonFull(key);
    }
}

void BTreeNode::splitChild(int i, BTreeNode* y) {
    int t = ceil((float)maxDegree / 2);
    BTreeNode* z = new BTreeNode(y->maxDegree, y->leaf);
    z->keys.resize(t - 1);

    for (int j = 0; j < t - 1; j++) {
        z->keys[j] = y->keys[j + t];
    }

    if (!y->leaf) {
        z->children.resize(t);
        for (int j = 0; j < t; j++) {
            z->children[j] = y->children[j + t];
        }
    }

    y->keys.resize(t - 1);
    children.insert(children.begin() + i + 1, z);
    keys.insert(keys.begin() + i, y->keys[t - 1]);
}

void BTreeNode::traverse() {
    int i;
    for (i = 0; i < keys.size(); i++) {
        if (!leaf) {
            children[i]->traverse();
        }
        cout << " " << keys[i];
    }
    if (!leaf) {
        children[i]->traverse();
    }
}

BTreeNode* BTreeNode::search(int key) {
    int i = 0;
    while (i < keys.size() && key > keys[i]) {
        i++;
    }

    if (i < keys.size() && keys[i] == key) {
        return this;
    }

    if (leaf) {
        return nullptr;
    }

    return children[i]->search(key);
}

void BTreeNode::remove(int key) {
    int idx = 0;
    while (idx < keys.size() && keys[idx] < key) {
        ++idx;
    }

    if (idx < keys.size() && keys[idx] == key) {
        if (leaf) {
            removeFromLeaf(idx);
        } else {
            removeFromNonLeaf(idx);
        }
    } else {
        if (leaf) {
            cout << "The key " << key << " is not present in the tree\n";
            return;
        }

        bool flag = (idx == keys.size());
        if (children[idx]->keys.size() < ceil((float)maxDegree / 2)) {
            fill(idx);
        }

        if (flag && idx > keys.size()) {
            children[idx - 1]->remove(key);
        } else {
            children[idx]->remove(key);
        }
    }
}

void BTreeNode::removeFromLeaf(int idx) {
    keys.erase(keys.begin() + idx);
}

void BTreeNode::removeFromNonLeaf(int idx) {
    int key = keys[idx];

    if (children[idx]->keys.size() >= ceil((float)maxDegree / 2)) {
        int pred = getPred(idx);
        keys[idx] = pred;
        children[idx]->remove(pred);
    } else if (children[idx + 1]->keys.size() >= ceil((float)maxDegree / 2)) {
        int succ = getSucc(idx);
        keys[idx] = succ;
        children[idx + 1]->remove(succ);
    } else {
        merge(idx);
        children[idx]->remove(key);
    }
}

int BTreeNode::getPred(int idx) {
    BTreeNode* cur = children[idx];
    while (!cur->leaf) {
        cur = cur->children[cur->keys.size()];
    }
    return cur->keys[cur->keys.size() - 1];
}

int BTreeNode::getSucc(int idx) {
    BTreeNode* cur = children[idx + 1];
    while (!cur->leaf) {
        cur = cur->children[0];
    }
    return cur->keys[0];
}

void BTreeNode::fill(int idx) {
    if (idx != 0 && children[idx - 1]->keys.size() >= ceil((float)maxDegree / 2)) {
        borrowFromPrev(idx);
    } else if (idx != keys.size() && children[idx + 1]->keys.size() >= ceil((float)maxDegree / 2)) {
        borrowFromNext(idx);
    } else {
        if (idx != keys.size()) {
            merge(idx);
        } else {
            merge(idx - 1);
        }
    }
}

void BTreeNode::borrowFromPrev(int idx) {
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx - 1];

    for (int i = child->keys.size() - 1; i >= 0; --i) {
        child->keys[i + 1] = child->keys[i];
    }

    if (!child->leaf) {
        for (int i = child->children.size() - 1; i >= 0; --i) {
            child->children[i + 1] = child->children[i];
        }
    }

    child->keys[0] = keys[idx - 1];
    if (!child->leaf) {
        child->children[0] = sibling->children[sibling->keys.size()];
    }

    keys[idx - 1] = sibling->keys[sibling->keys.size() - 1];
    sibling->keys.pop_back();
    child->keys.insert(child->keys.begin(), sibling->keys.back());
    sibling->keys.pop_back();
}

void BTreeNode::borrowFromNext(int idx) {
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx + 1];

    child->keys.push_back(keys[idx]);
    if (!child->leaf) {
        child->children.push_back(sibling->children[0]);
    }

    keys[idx] = sibling->keys[0];
    sibling->keys.erase(sibling->keys.begin());
    if (!sibling->leaf) {
        sibling->children.erase(sibling->children.begin());
    }
}

void BTreeNode::merge(int idx) {
    BTreeNode* child = children[idx];
    BTreeNode* sibling = children[idx + 1];

    child->keys.push_back(keys[idx]);
    for (int i = 0; i < sibling->keys.size(); ++i) {
        child->keys.push_back(sibling->keys[i]);
    }

    if (!child->leaf) {
        for (int i = 0; i <= sibling->keys.size(); ++i) {
            child->children.push_back(sibling->children[i]);
        }
    }

    keys.erase(keys.begin() + idx);
    children.erase(children.begin() + idx + 1);
    delete sibling;
}

class BTree {
public:
    BTreeNode* root;
    int maxDegree;

    BTree(int maxDegree);

    void traverse() {
        if (root != nullptr) {
            root->traverse();
        }
    }

    BTreeNode* search(int key) {
        return (root == nullptr) ? nullptr : root->search(key);
    }

    void insert(int key);
    void remove(int key);
};

BTree::BTree(int maxDegree) {
    root = nullptr;
    this->maxDegree = maxDegree;
}

void BTree::insert(int key) {
    if (root == nullptr) {
        root = new BTreeNode(maxDegree, true);
        root->keys.push_back(key);
    } else {
        if (root->keys.size() == maxDegree - 1) {
            BTreeNode* s = new BTreeNode(maxDegree, false);
            s->children.push_back(root);
            s->splitChild(0, root);
            int i = 0;
            if (s->keys[0] < key) {
                i++;
            }
            s->children[i]->insertNonFull(key);
            root = s;
        } else {
            root->insertNonFull(key);
        }
    }
}

void BTree::remove(int key) {
    if (!root) {
        cout << "The tree is empty\n";
        return;
    }

    root->remove(key);

    if (root->keys.size() == 0) {
        BTreeNode* tmp = root;
        if (root->leaf) {
            root = nullptr;
        } else {
            root = root->children[0];
        }
        delete tmp;
    }
}

int main() {
    int maxDegree = 4;  // Example maximum degree
    BTree t(maxDegree);

    t.insert(10);
    t.insert(20);
    t.insert(5);
    t.insert(6);
    t.insert(12);
    t.insert(30);
    t.insert(7);
    t.insert(17);

    cout << "Traversal of the constructed tree is ";
    t.traverse();
    cout << endl;

    int k = 6;
    t.remove(k);
    cout << "Traversal of the tree after removing " << k << " is ";
    t.traverse();
    cout << endl;

    k = 13;
    t.remove(k);
    cout << "Traversal of the tree after removing " << k << " is ";
    t.traverse();
    cout << endl;

    k = 7;
    t.remove(k);
    cout << "Traversal of the tree after removing " << k << " is ";
    t.traverse();
    cout << endl;

    k = 4;
    t.remove(k);
    cout << "Traversal of the tree after removing " << k << " is ";
    t.traverse();
    cout << endl;

    k = 2;
    t.remove(k);
    cout << "Traversal of the tree after removing " << k << " is ";
    t.traverse();
    cout << endl;

    k = 16;
    t.remove(k);
    cout << "Traversal of the tree after removing " << k << " is ";
    t.traverse();
    cout << endl;

    return 0;
}
