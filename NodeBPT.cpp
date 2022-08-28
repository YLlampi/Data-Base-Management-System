#include "NodeBPT.h"

NodeBPT::NodeBPT(int MAX) {
    key = new int[MAX];
    ptr = new NodeBPT *[MAX + 1];
}