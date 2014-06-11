//
//  routing_map.h
//  MPCS2
//
//  Created by 李勁璋 on 2014/5/28.
//  Copyright (c) 2014年 Li,Ching-Chang. All rights reserved.
//

#ifndef __MPCS2__routing_map__
#define __MPCS2__routing_map__

#include <iostream>
#include "solve_boxnode.h"
#include "bump_node.h"

using namespace std;

typedef enum
{
    topSide,
    rightSide,
    bottomSide,
    leftSide,
    topAngle,
    rightAngle,
    bottomAngle,
    leftAngle,
}edges;

class RoutingMap
{
public:
    RoutingMap(int rowNum, int colNum);              //假設bump排列為方形
    ~RoutingMap();
    void mapInsertNode(int rowPos, int colPos, edges side, BumpNode *node);
    void nodeInserttoMap(int nodeRow, int nodeCol, BumpNode *node);
    void initMapinLayer(int layer, int layerRowNum, int layerColNum, vector<BumpNode*>currentSeq);
    void routeinLayer(int layerNum);
    void printBox(int layerRowNum, int layerColNum);
    
    void ringMaping(int layer, int startRowNum, int startColNum);
    box *map;
    int mapRowNum, mapColNum;

private:
    
    vector<BumpNode *>outCircleSequence;
    void boxMaping(int mapRow, int mapCol);
    
    void vnodeInserttoBox(int rowNum, int colNum, edges side, BumpNode *node, bool toBegin);
    void eraseVnode(int rowNum, int colNum, edges side, int pointer);
    void seqtoMap(int layer, int startRowNym, int startColNum, int pointer, int *rowNum, int *colNum, edges *side);
    void layertoMap(int layer, int startRowNum, int startColNum, int pointer, int *rowNum, int *colNum);
    int seqPointertoLayerPointer(int layer, int seqPointer);
    edges witchSide(int layer, int startRowNum, int startColNum, int pointer);
    void insertNodetoPath(int layer, int startRow, int startCol, int startPoint, edges startSide, int endPoint, edges endSide, BumpNode *node);
    void moveNode(int fromRow, int fromCol, edges fromSide, int fromPointer, int toRow, int toCol, edges toSide, bool seqLeft);
    void refineBoxRoute(int layer, int startRowNum, int startColNum, int pointer);
};

#endif /* defined(__MPCS2__routing_map__) */
