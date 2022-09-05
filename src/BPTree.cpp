#include "BPTree.h"


void BPTree::insertInternal(int x, NodeBPT *cursor, NodeBPT *child) {
    if (cursor->size < MAX) {
        int i = 0;
        while (x > cursor->key[i] && i < cursor->size)
            i++;
        for (int j = cursor->size; j > i; j--) {
            cursor->key[j] = cursor->key[j - 1];
        }
        for (int j = cursor->size + 1; j > i + 1; j--) {
            cursor->ptr[j] = cursor->ptr[j - 1];
        }
        cursor->key[i] = x;
        cursor->size++;
        cursor->ptr[i + 1] = child;
    } else {
        NodeBPT *newInternal = new NodeBPT(this->MAX);
        int virtualKey[MAX + 1];
        NodeBPT *virtualPtr[MAX + 2];
        for (int i = 0; i < MAX; i++) {
            virtualKey[i] = cursor->key[i];
        }
        for (int i = 0; i < MAX + 1; i++) {
            virtualPtr[i] = cursor->ptr[i];
        }
        int i = 0, j;
        while (x > virtualKey[i] && i < MAX)
            i++;
        for (int j = MAX + 1; j > i; j--) {
            virtualKey[j] = virtualKey[j - 1];
        }
        virtualKey[i] = x;
        for (int j = MAX + 2; j > i + 1; j--) {
            virtualPtr[j] = virtualPtr[j - 1];
        }
        virtualPtr[i + 1] = child;
        newInternal->IS_LEAF = false;
        cursor->size = (MAX + 1) / 2;
        newInternal->size = MAX - (MAX + 1) / 2;
        for (i = 0, j = cursor->size + 1; i < newInternal->size; i++, j++) {
            newInternal->key[i] = virtualKey[j];
        }
        for (i = 0, j = cursor->size + 1; i < newInternal->size + 1; i++, j++) {
            newInternal->ptr[i] = virtualPtr[j];
        }
        if (cursor == root) {
            NodeBPT *newRoot = new NodeBPT(this->MAX);
            newRoot->key[0] = cursor->key[cursor->size];
            newRoot->ptr[0] = cursor;
            newRoot->ptr[1] = newInternal;
            newRoot->IS_LEAF = false;
            newRoot->size = 1;
            root = newRoot;
        } else {
            insertInternal(cursor->key[cursor->size], findParent(root, cursor), newInternal);
        }
    }
}

void BPTree::removeInternal(int x, NodeBPT *cursor, NodeBPT *child) {
    if (cursor == root) {
        if (cursor->size == 1) {
            if (cursor->ptr[1] == child) {
                delete[] child->key;
                delete[] child->ptr;
                delete child;
                root = cursor->ptr[0];
                delete[] cursor->key;
                delete[] cursor->ptr;
                delete cursor;
                std::cout << "Changed root node\n";
                return;
            } else if (cursor->ptr[0] == child) {
                delete[] child->key;
                delete[] child->ptr;
                delete child;
                root = cursor->ptr[1];
                delete[] cursor->key;
                delete[] cursor->ptr;
                delete cursor;
                std::cout << "Changed root node\n";
                return;
            }
        }
    }
    int pos;
    for (pos = 0; pos < cursor->size; pos++) {
        if (cursor->key[pos] == x) {
            break;
        }
    }
    for (int i = pos; i < cursor->size; i++) {
        cursor->key[i] = cursor->key[i + 1];
    }
    for (pos = 0; pos < cursor->size + 1; pos++) {
        if (cursor->ptr[pos] == child) {
            break;
        }
    }
    for (int i = pos; i < cursor->size + 1; i++) {
        cursor->ptr[i] = cursor->ptr[i + 1];
    }
    cursor->size--;
    if (cursor->size >= (MAX + 1) / 2 - 1) {
        return;
    }
    if (cursor == root)
        return;
    NodeBPT *parent = findParent(root, cursor);
    int leftSibling, rightSibling;
    for (pos = 0; pos < parent->size + 1; pos++) {
        if (parent->ptr[pos] == cursor) {
            leftSibling = pos - 1;
            rightSibling = pos + 1;
            break;
        }
    }
    if (leftSibling >= 0) {
        NodeBPT *leftNode = parent->ptr[leftSibling];
        if (leftNode->size >= (MAX + 1) / 2) {
            for (int i = cursor->size; i > 0; i--) {
                cursor->key[i] = cursor->key[i - 1];
            }
            cursor->key[0] = parent->key[leftSibling];
            parent->key[leftSibling] = leftNode->key[leftNode->size - 1];
            for (int i = cursor->size + 1; i > 0; i--) {
                cursor->ptr[i] = cursor->ptr[i - 1];
            }
            cursor->ptr[0] = leftNode->ptr[leftNode->size];
            cursor->size++;
            leftNode->size--;
            return;
        }
    }
    if (rightSibling <= parent->size) {
        NodeBPT *rightNode = parent->ptr[rightSibling];
        if (rightNode->size >= (MAX + 1) / 2) {
            cursor->key[cursor->size] = parent->key[pos];
            parent->key[pos] = rightNode->key[0];
            for (int i = 0; i < rightNode->size - 1; i++) {
                rightNode->key[i] = rightNode->key[i + 1];
            }
            cursor->ptr[cursor->size + 1] = rightNode->ptr[0];
            for (int i = 0; i < rightNode->size; ++i) {
                rightNode->ptr[i] = rightNode->ptr[i + 1];
            }
            cursor->size++;
            rightNode->size--;
            return;
        }
    }
    if (leftSibling >= 0) {
        NodeBPT *leftNode = parent->ptr[leftSibling];
        leftNode->key[leftNode->size] = parent->key[leftSibling];
        for (int i = leftNode->size + 1, j = 0; j < cursor->size; j++) {
            leftNode->key[i] = cursor->key[j];
        }
        for (int i = leftNode->size + 1, j = 0; j < cursor->size + 1; j++) {
            leftNode->ptr[i] = cursor->ptr[j];
            cursor->ptr[j] = nullptr;
        }
        leftNode->size += cursor->size + 1;
        cursor->size = 0;
        removeInternal(parent->key[leftSibling], parent, cursor);
    } else if (rightSibling <= parent->size) {
        NodeBPT *rightNode = parent->ptr[rightSibling];
        cursor->key[cursor->size] = parent->key[rightSibling - 1];
        for (int i = cursor->size + 1, j = 0; j < rightNode->size; j++) {
            cursor->key[i] = rightNode->key[j];
        }
        for (int i = cursor->size + 1, j = 0; j < rightNode->size + 1; j++) {
            cursor->ptr[i] = rightNode->ptr[j];
            rightNode->ptr[j] = nullptr;
        }
        cursor->size += rightNode->size + 1;
        rightNode->size = 0;
        removeInternal(parent->key[rightSibling - 1], parent, rightNode);
    }
}

NodeBPT *BPTree::findParent(NodeBPT *cursor, NodeBPT *child) {
    NodeBPT *parent;
    if (cursor->IS_LEAF || (cursor->ptr[0])->IS_LEAF) {
        return nullptr;
    }
    for (int i = 0; i < cursor->size + 1; i++) {
        if (cursor->ptr[i] == child) {
            parent = cursor;
            return parent;
        } else {
            parent = findParent(cursor->ptr[i], child);
            if (parent != nullptr)
                return parent;
        }
    }
    return parent;
}

BPTree::BPTree(int _MAX) {
    this->root = nullptr;
    this->MAX = _MAX;
}

void BPTree::search(int x) { // O(longn) - Complejidad Algoritmica search
    if (root == nullptr) {
        std::cout << "Tree is empty\n";
    } else {
        NodeBPT *cursor = root;
        while (!cursor->IS_LEAF) {
            for (int i = 0; i < cursor->size; i++) {
                if (x < cursor->key[i]) {
                    cursor = cursor->ptr[i];
                    break;
                }
                if (i == cursor->size - 1) {
                    cursor = cursor->ptr[i + 1];
                    break;
                }
            }
        }
        for (int i = 0; i < cursor->size; i++) {
            if (cursor->key[i] == x) {
                std::cout << "Found\n";
                return;
            }
        }
        std::cout << "Not found\n";
    }
}

/*
 * parametro: int x : indice del registro que esta almacenado en el disco
 * inserta x:indice de registro
 * O(logn) - Complejidad Algoritmica
 */
void BPTree::insert(int x) {
    /*
     * Si no existe datos en la estructura
     */
    if (root == nullptr) {
        root = new NodeBPT(this->MAX);
        root->key[0] = x;
        root->IS_LEAF = true;
        root->size = 1;
    } else {
        NodeBPT *cursor = root;
        NodeBPT *parent;
        while (!cursor->IS_LEAF) {
            parent = cursor;
            for (int i = 0; i < cursor->size; i++) {
                if (x < cursor->key[i]) {
                    cursor = cursor->ptr[i];
                    break;
                }
                if (i == cursor->size - 1) {
                    cursor = cursor->ptr[i + 1];
                    break;
                }
            }
        }
        if (cursor->size < MAX) {
            int i = 0;
            while (x > cursor->key[i] && i < cursor->size)
                i++;
            for (int j = cursor->size; j > i; j--) {
                cursor->key[j] = cursor->key[j - 1];
            }
            cursor->key[i] = x;
            cursor->size++;
            cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1];
            cursor->ptr[cursor->size - 1] = nullptr;
        } else {
            NodeBPT *newLeaf = new NodeBPT(this->MAX);
            int virtualNode[MAX + 1];
            for (int i = 0; i < MAX; i++) {
                virtualNode[i] = cursor->key[i];
            }
            int i = 0, j;
            while (x > virtualNode[i] && i < MAX)
                i++;
            for (int j = MAX + 1; j > i; j--) {
                virtualNode[j] = virtualNode[j - 1];
            }
            virtualNode[i] = x;
            newLeaf->IS_LEAF = true;
            cursor->size = (MAX + 1) / 2;
            newLeaf->size = MAX + 1 - (MAX + 1) / 2;
            cursor->ptr[cursor->size] = newLeaf;
            newLeaf->ptr[newLeaf->size] = cursor->ptr[MAX];
            cursor->ptr[MAX] = nullptr;
            for (i = 0; i < cursor->size; i++) {
                cursor->key[i] = virtualNode[i];
            }
            for (i = 0, j = cursor->size; i < newLeaf->size; i++, j++) {
                newLeaf->key[i] = virtualNode[j];
            }
            if (cursor == root) {
                NodeBPT *newRoot = new NodeBPT(this->MAX);
                newRoot->key[0] = newLeaf->key[0];
                newRoot->ptr[0] = cursor;
                newRoot->ptr[1] = newLeaf;
                newRoot->IS_LEAF = false;
                newRoot->size = 1;
                root = newRoot;
            } else {
                insertInternal(newLeaf->key[0], parent, newLeaf);
            }
        }
    }
}

/*
 * O(longn): Complejidad Algoritmica
 */
void BPTree::remove(int x) {
    if (root == nullptr) {
        std::cout << "Tree empty\n";
    } else {
        NodeBPT *cursor = root;
        NodeBPT *parent;
        int leftSibling, rightSibling;
        while (!cursor->IS_LEAF) {
            for (int i = 0; i < cursor->size; i++) {
                parent = cursor;
                leftSibling = i - 1;
                rightSibling = i + 1;
                if (x < cursor->key[i]) {
                    cursor = cursor->ptr[i];
                    break;
                }
                if (i == cursor->size - 1) {
                    leftSibling = i;
                    rightSibling = i + 2;
                    cursor = cursor->ptr[i + 1];
                    break;
                }
            }
        }
        bool found = false;
        int pos;
        for (pos = 0; pos < cursor->size; pos++) {
            if (cursor->key[pos] == x) {
                found = true;
                break;
            }
        }
        if (!found) {
            std::cout << "Not found\n";
            return;
        }
        for (int i = pos; i < cursor->size; i++) {
            cursor->key[i] = cursor->key[i + 1];
        }
        cursor->size--;
        if (cursor == root) {
            for (int i = 0; i < MAX + 1; i++) {
                cursor->ptr[i] = nullptr;
            }
            if (cursor->size == 0) {
                std::cout << "Tree died\n";
                delete[] cursor->key;
                delete[] cursor->ptr;
                delete cursor;
                root = nullptr;
            }
            return;
        }
        cursor->ptr[cursor->size] = cursor->ptr[cursor->size + 1];
        cursor->ptr[cursor->size + 1] = nullptr;
        if (cursor->size >= (MAX + 1) / 2) {
            return;
        }
        if (leftSibling >= 0) {
            NodeBPT *leftNode = parent->ptr[leftSibling];
            if (leftNode->size >= (MAX + 1) / 2 + 1) {
                for (int i = cursor->size; i > 0; i--) {
                    cursor->key[i] = cursor->key[i - 1];
                }
                cursor->size++;
                cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1];
                cursor->ptr[cursor->size - 1] = nullptr;
                cursor->key[0] = leftNode->key[leftNode->size - 1];
                leftNode->size--;
                leftNode->ptr[leftNode->size] = cursor;
                leftNode->ptr[leftNode->size + 1] = nullptr;
                parent->key[leftSibling] = cursor->key[0];
                return;
            }
        }
        if (rightSibling <= parent->size) {
            NodeBPT *rightNode = parent->ptr[rightSibling];
            if (rightNode->size >= (MAX + 1) / 2 + 1) {
                cursor->size++;
                cursor->ptr[cursor->size] = cursor->ptr[cursor->size - 1];
                cursor->ptr[cursor->size - 1] = nullptr;
                cursor->key[cursor->size - 1] = rightNode->key[0];
                rightNode->size--;
                rightNode->ptr[rightNode->size] = rightNode->ptr[rightNode->size + 1];
                rightNode->ptr[rightNode->size + 1] = nullptr;
                for (int i = 0; i < rightNode->size; i++) {
                    rightNode->key[i] = rightNode->key[i + 1];
                }
                parent->key[rightSibling - 1] = rightNode->key[0];
                return;
            }
        }
        if (leftSibling >= 0) {
            NodeBPT *leftNode = parent->ptr[leftSibling];
            for (int i = leftNode->size, j = 0; j < cursor->size; i++, j++) {
                leftNode->key[i] = cursor->key[j];
            }
            leftNode->ptr[leftNode->size] = nullptr;
            leftNode->size += cursor->size;
            leftNode->ptr[leftNode->size] = cursor->ptr[cursor->size];
            removeInternal(parent->key[leftSibling], parent, cursor);
            delete[] cursor->key;
            delete[] cursor->ptr;
            delete cursor;
        } else if (rightSibling <= parent->size) {
            NodeBPT *rightNode = parent->ptr[rightSibling];
            for (int i = cursor->size, j = 0; j < rightNode->size; i++, j++) {
                cursor->key[i] = rightNode->key[j];
            }
            cursor->ptr[cursor->size] = nullptr;
            cursor->size += rightNode->size;
            cursor->ptr[cursor->size] = rightNode->ptr[rightNode->size];
            std::cout << "Merging two leaf nodes\n";
            removeInternal(parent->key[rightSibling - 1], parent, rightNode);
            delete[] rightNode->key;
            delete[] rightNode->ptr;
            delete rightNode;
        }
    }
}

void BPTree::display(NodeBPT *cursor) {
    if (cursor != nullptr) {
        for (int i = 0; i < cursor->size and cursor->IS_LEAF; i++) {
            //std::cout << cursor->key[i] << " ";
            this->indexation.push_back(cursor->key[i]);
        }

        if (!cursor->IS_LEAF) {
            for (int i = 0; i < cursor->size + 1; i++) {
                display(cursor->ptr[i]);
            }
        }
    }
}

NodeBPT *BPTree::getRoot() {
    return this->root;
}

std::list<int> &BPTree::getIndexation() {
    return this->indexation;
}

void BPTree::clearIndexation() {
    this->indexation.clear();
}
