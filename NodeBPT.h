#ifndef DATA_BASE_MANAGEMENT_SYSTEM_NODEBPT_H
#define DATA_BASE_MANAGEMENT_SYSTEM_NODEBPT_H


#include <bits/stdc++.h>

class NodeBPT {
private:
    bool IS_LEAF;
    int *key, size;
    NodeBPT **ptr;
    friend class BPTree;
public:
    NodeBPT(int);
};



#endif //DATA_BASE_MANAGEMENT_SYSTEM_NODEBPT_H
