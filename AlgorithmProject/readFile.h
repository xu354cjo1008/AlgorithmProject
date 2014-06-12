//
//  readFile.h
//  AlgorithmProject
//
//  Created by 李勁璋 on 2014/6/9.
//  Copyright (c) 2014年 ntu. All rights reserved.
//

#ifndef __AlgorithmProject__readFile__
#define __AlgorithmProject__readFile__

#include <iostream>
#include <vector>
#include "bump_node.h"
using namespace std;

class Boundary{
public:
    int leftX, rightX, bottomY, topY;
};

class DriverNode{
public:
    int did, dleftX, drightX, dbottomY, dtopY;
};


class lcs_bump{
public:
    int cs;
    int *prev;
};

class ReadFile
{
public:
    ReadFile();
    ~ReadFile();
    void LCS(vector<DriverNode> *driver_vec, vector<BumpNode>*bump_vec, int num_driver, int n);
    void alignment(int bumpNum);
    vector<BumpNode> *bvec; //create n vectors to store rings
    vector<DriverNode> driver;
    vector<BumpNode> bump;
    void label_LCS(int i, int j, vector<BumpNode>*bump_vec);
    lcs_bump **dpary;
    int numBvec;
    int w;
    int s;
private:

};

int MaxY2(vector<BumpNode>*bump_dup);
int MaxX2(vector<BumpNode>*bump_dup);
int MinY1(vector<BumpNode>*bump_dup);
int MinX1(vector<BumpNode>*bump_dup);
    
#endif /* defined(__AlgorithmProject__readFile__) */
