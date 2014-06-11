//
//  solve_boxnode.h
//  
//
//  Created by steve on 2014/5/26.
//
//

#ifndef ____solve_boxnode__
#define ____solve_boxnode__

#include <iostream>
#include "bump_node.h"
#include <algorithm>
#include <vector>
using namespace std;

struct box
{
    vector<BumpNode *> top;
    vector<BumpNode *> right;
    vector<BumpNode *> buttom;
    vector<BumpNode *> left;
    bool top_lock;
    bool right_lock;
    bool buttom_lock;
    bool left_lock;
    bool routed;
    int cooridinate;
    int path_for_outcircle; 
};

bool boxnode_measurement(box *input);
bool sort_node_cmp (BumpNode *i,BumpNode *j);
bool measure_diagonal(box *input,int node_capacity);
void sort_node(box *input);



#endif /* defined(____solve_boxnode__) */
