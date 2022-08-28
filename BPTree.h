#ifndef DATA_BASE_MANAGEMENT_SYSTEM_BPTREE_H
#define DATA_BASE_MANAGEMENT_SYSTEM_BPTREE_H


#include "NodeBPT.h"

class BPTree {
private:
    NodeBPT *root;
    void insertInternal(int, NodeBPT *, NodeBPT *);
    void removeInternal(int, NodeBPT *, NodeBPT *);
    NodeBPT *findParent(NodeBPT *, NodeBPT *);
    int MAX;

    std::list<int> indexation;
public:
    BPTree(int);
    void search(int);
    void insert(int);
    void remove(int);
    void display(NodeBPT *);
    NodeBPT *getRoot();

    std::list<int> &getIndexation() ;
    void clearIndexation();
};


#endif //DATA_BASE_MANAGEMENT_SYSTEM_BPTREE_H
