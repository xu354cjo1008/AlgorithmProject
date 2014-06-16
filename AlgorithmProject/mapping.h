//
//  mapping.h
//  AlgorithmProject
//
//  Created by steve on 2014/6/5.
//  Copyright (c) 2014年 ntu. All rights reserved.
//

#ifndef __AlgorithmProject__mapping__
#define __AlgorithmProject__mapping__

#include <iostream>
#include "routing_map.h"
#include <algorithm>
#include <vector>

struct node_side
{
    int direction;
    int node_amount;
};

class mapping
{
public:
    mapping(int row_size,int col_size,int width,int spacing);
    ~mapping();
    void mapping_incircle(box *map);
    void mapping_outcircle(box *map);
    void route_output(box *map);
private:
    int capacity_node;
    int step_width,w;
    int mapRowNum, mapColNum;
    void find_path_destination(box *map1,int row,int col,int dir,int node_order,int side_length,int row_col_start);
    void trace_route(BumpNode *node_start,int x_previous,int y_previous);
    void write_output(int x1r,int y1r,int x2r,int y2r);
};


bool sort_node_amount (node_side i,node_side j);

#endif /* defined(__AlgorithmProject__mapping__) */
