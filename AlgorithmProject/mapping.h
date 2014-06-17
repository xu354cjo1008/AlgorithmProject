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
#include <fstream>
#include "readFile.h"
using namespace std;

struct node_side
{
    int direction;
    int node_amount;
};


class mapping
{
public:
    mapping(int row_size,int col_size,int width,int spacing,vector<DriverNode> &d,vector<BumpNode> &b);
    ~mapping();
    void mapping_incircle(box *map);
    void mapping_outcircle(vector<BumpNode *> outCircleSequence);
    void route_output(box *map,string filename,int a,int a1,int a2,int a3);
    
private:
    vector<DriverNode> driver;
    vector<BumpNode> bump;
    vector<BumpNode *> outside_ring_top;
    vector<BumpNode *> outside_ring_right;
    vector<BumpNode *> outside_ring_buttom;
    vector<BumpNode *> outside_ring_left;
    vector<BumpNode *> outside_ring_final;
    int capacity_node;
    int step_width,w,d_to_b_capacity;
    int mapRowNum, mapColNum;
    void find_path_destination(box *map1,int row,int col,int dir,int node_order,int side_length,int row_col_start);
    void trace_route(ofstream &myfile,BumpNode *node_start,int x_previous,int y_previous,bool driver);
    void write_output(int x1r,int y1r,int x2r,int y2r,ofstream &myflie);
    void driver_start_path(ofstream &myfile,box *map);
    void create_node_btw_DB(ofstream &myfile);
    vector<BumpNode *> corner;
    BumpNode *end;
};


bool sort_node_amount (node_side i,node_side j);
bool outside_ring_cmp (BumpNode *i,BumpNode *j);
#endif /* defined(__AlgorithmProject__mapping__) */
