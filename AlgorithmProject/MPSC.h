//
//  MPSC.h
//  MPSC
//
//  Created by 李勁璋 on 2014/5/16.
//  Copyright (c) 2014年 Li,Ching-Chang. All rights reserved.
//

#ifndef __MPSC__MPSC__
#define __MPSC__MPSC__

#include <iostream>
#include "bump_node.h"
#include <vector>

using namespace std;
struct chord
{
    int node1;
    int node2;
    chord *left;
    chord *right;
    int total;
};
class MIS
{
public:
	MIS(int rowSize, int columnSize);
	~MIS();
	chord *chordsinMIS(int row, int column);
    void putChordsInMIS(int row, int column, chord *leftChord, chord *rightChord, chord* newChord);
    
    void printMaxSeq();
    void maxSeq(vector<chord>*outSeq);


private:
    int tRowSize;
    int tColSize;
    chord* table;
};

class MPSC
{
public:
    MPSC(vector<BumpNode *>*previousSeq, vector<BumpNode *>*currentLCS);
    ~MPSC();
    void compute();
    
private:
	vector<BumpNode*> *previousSequence;
	vector<BumpNode*> *currentSequence;
    void buildCircle();
    void buildMis();
    vector<chord> circle;
    MIS *mis;
    void refreshSequence();
};

#endif /* defined(__MPSC__MPSC__) */
