//
//  routing_map.cpp
//  MPCS2
//
//  Created by 李勁璋 on 2014/5/28.
//  Copyright (c) 2014年 Li,Ching-Chang. All rights reserved.
//

#include "routing_map.h"


RoutingMap::RoutingMap(int rowNum, int colNum) 
{
    map = new box[rowNum * colNum];
    mapRowNum = rowNum;
    mapColNum = colNum;
  //  for (int i = 0; i < mapRowNum; ++i) {
      //  &map[i * mapRowNum].buttom = &map[i * mapRowNum].top;
   // }
}

RoutingMap::~RoutingMap()
{
    delete [] map;
    printf("routing map delloc\n");
}
void RoutingMap::mapInsertNode(int rowPos, int colPos, edges side, BumpNode *node)
{
    switch (side) {
        case topSide:
            map[rowPos * mapRowNum + colPos].top.push_back(node);
            break;
        case rightSide:
            map[rowPos * mapRowNum + colPos].right.push_back(node);
            break;
        case bottomSide:
            map[rowPos * mapRowNum + colPos].buttom.push_back(node);
            break;
        case leftSide:
            map[rowPos * mapRowNum + colPos].left.push_back(node);
            break;
        default:
            break;
    }
}
void RoutingMap::nodeInserttoMap(int nodeRow, int nodeCol, BumpNode *node)
{
    if (nodeRow == 0) {
        if (nodeCol == 0) {
            mapInsertNode(nodeRow, nodeCol, topSide, node);
        } else if(nodeCol == mapColNum) {
            mapInsertNode(nodeRow, nodeCol - 1, rightSide, node);
        } else {
            mapInsertNode(nodeRow, nodeCol, topSide, node);
            mapInsertNode(nodeRow, nodeCol - 1, rightSide, node);
        }
    } else if(nodeRow == mapRowNum) {
        if (nodeCol == 0) {
            mapInsertNode(nodeRow - 1, nodeCol, leftSide, node);
        } else if(nodeCol == mapColNum) {
            mapInsertNode(nodeRow - 1, nodeCol - 1, bottomSide, node);
        } else {
            mapInsertNode(nodeRow - 1, nodeCol, leftSide, node);
            mapInsertNode(nodeRow - 1, nodeCol - 1, bottomSide, node);
        }
    } else {
        if (nodeCol == 0) {
            mapInsertNode(nodeRow - 1, nodeCol, leftSide, node);
            mapInsertNode(nodeRow, 0, topSide, node);
        } else if(nodeCol == mapColNum) {
            mapInsertNode(nodeRow - 1, nodeCol - 1, bottomSide, node);
            mapInsertNode(nodeRow, nodeCol - 1, rightSide, node);
        } else {
            mapInsertNode(nodeRow - 1, nodeCol, leftSide, node);
            mapInsertNode(nodeRow - 1, nodeCol - 1, bottomSide, node);
            mapInsertNode(nodeRow, nodeCol, topSide, node);
            mapInsertNode(nodeRow, nodeCol - 1, rightSide, node);
        }
    }
}
void RoutingMap::vnodeInserttoBox(int rowNum, int colNum, edges side, BumpNode *node)
{
    if (side == topSide) {
        if (rowNum == 0) {
            map[rowNum * mapColNum + colNum].top.push_back(node);
        } else {
            map[rowNum * mapColNum + colNum].top.push_back(node);
            map[(rowNum - 1) * mapColNum + colNum].buttom.insert(map[(rowNum - 1) * mapColNum + colNum].buttom.begin(), node);
        }
    } else if(side == rightSide) {
        if (colNum == mapColNum - 1) {
            map[rowNum * mapColNum + colNum].right.push_back(node);
        } else {
            map[rowNum * mapColNum + colNum].right.push_back(node);
            map[rowNum * mapColNum + colNum + 1].right.insert(map[rowNum * mapColNum + colNum + 1].right.begin(), node);
        }
    } else if(side == bottomSide) {
        if (rowNum == mapRowNum - 1) {
            map[rowNum * mapColNum + colNum].top.push_back(node);
        } else {
            map[rowNum * mapColNum + colNum].top.push_back(node);
            map[(rowNum + 1) * mapColNum + colNum].buttom.insert(map[(rowNum + 1) * mapColNum + colNum].buttom.begin(), node);
        }
    } else if(side == leftSide) {
        if (colNum == 0) {
            map[rowNum * mapColNum + colNum].left.push_back(node);
        } else {
            map[rowNum * mapColNum + colNum].left.push_back(node);
            map[rowNum * mapColNum + colNum - 1].right.insert(map[rowNum * mapColNum + colNum - 1].right.begin(), node);
        }
    }
}


void RoutingMap::initMapinLayer(int layer, int layerRowNum, int layerColNum, vector<BumpNode*>currentSeq)
{
  //  int rowSize = 2 * layer + 1;
  //  int colSize = 2 * layer + 1;
    int mapPointer = -1;
    int firstBumpPos = 0;
    int row = 0;
    int col = 0;
    edges side = topSide;
    for (int i = 0; i < currentSeq.size(); ++i) {
        if (!currentSeq[i]->isVirtual) {
            if (mapPointer == -1) {
                firstBumpPos = i;
            }
            mapPointer ++;
            seqtoMap(layer, layerRowNum, layerColNum, mapPointer, &row, &col, &side);
        } else {
            vnodeInserttoBox(row, col, side, currentSeq[i]);
      /*      if (mapPointer >= 0) {
                if (mapPointer < rowSize) {
                    vnodeInserttoBox(layerRowNum, layerColNum + mapPointer, topSide, currentSeq[i]);
                } else if(mapPointer >= rowSize && mapPointer < rowSize + colSize) {
                    vnodeInserttoBox(layerRowNum + mapPointer - colSize, layerColNum + colSize - 1, rightSide, currentSeq[i]);
                } else if(mapPointer >= colSize + rowSize && mapPointer < 2 * colSize + rowSize) {
                    vnodeInserttoBox(layerRowNum + rowSize - 1, layerColNum + colSize - 1 - (mapPointer - rowSize - colSize), bottomSide, currentSeq[i]);
                } else if(mapPointer >= 2 * colSize + rowSize && mapPointer < 2 * (rowSize + colSize)) {
                    vnodeInserttoBox(layerRowNum + rowSize - 1 - (mapPointer - 2 * colSize -rowSize), layerColNum, leftSide, currentSeq[i]);
                } else if(mapPointer >= 2 * (rowSize + colSize)) {
                    vnodeInserttoBox(layerRowNum, layerColNum, leftSide, currentSeq[i]);
                }
            }*/
        }
    }
    for (int i = 0; i < firstBumpPos; ++i) {
        vnodeInserttoBox(layerRowNum, layerColNum, leftSide, currentSeq[i]);
    }
}
void RoutingMap::seqtoMap(int layer, int startRowNym, int startColNum, int pointer, int *rowNum, int *colNum, edges *side)
{
    int rowSize = 2 * layer + 1;
    int colSize = 2 * layer + 1;
    if (pointer >= 0) {
        if (pointer < rowSize) {
            *rowNum = startRowNym;
            *colNum = startColNum + pointer;
            *side = topSide;
        } else if(pointer >= rowSize && pointer < rowSize + colSize) {
            *rowNum = startRowNym + pointer - colSize;
            *colNum = startColNum + colSize - 1;
            *side = rightSide;
        } else if(pointer >= colSize + rowSize && pointer < 2 * colSize + rowSize) {
            *rowNum = startRowNym + rowSize - 1;
            *colNum = startColNum + colSize - 1 - (pointer - rowSize - colSize);
            *side = bottomSide;
        } else if(pointer >= 2 * colSize + rowSize && pointer < 2 * (rowSize + colSize)) {
            *rowNum = startRowNym + rowSize - 1 - (pointer - 2 * colSize - rowSize);
            *colNum = startColNum;
            *side = leftSide;
        } else if(pointer >= 2 * (rowSize + colSize)) {
            *rowNum = startRowNym;
            *colNum = startColNum;
            *side = leftSide;
        }
    } else if(pointer == -1) {
        *rowNum = startRowNym;
        *colNum = startColNum;
        *side = leftSide;
    }
}
void RoutingMap::layertoMap(int layer, int startRowNum, int startColNum, int pointer, int *rowNum, int *colNum)
{
    int rowSize = 2 * layer + 1;
    int colSize = 2 * layer + 1;
    if (pointer >= 0) {
        if (pointer < rowSize - 1) {
            *rowNum = startRowNum;
            *colNum = startColNum + pointer;
        } else if(pointer >= rowSize - 1 && pointer < rowSize + colSize - 2) {
            *rowNum = startRowNum + pointer + 1 - colSize;
            *colNum = startColNum + colSize - 1;
        } else if(pointer >= colSize + rowSize - 2 && pointer < 2 * colSize + rowSize - 3) {
            *rowNum = startRowNum + rowSize - 1;
            *colNum = startColNum + colSize - 1 - (pointer + 2 - rowSize - colSize);
        } else if(pointer >= 2 * colSize + rowSize - 3 && pointer < 2 * (rowSize + colSize) - 5) {
            *rowNum = startRowNum + rowSize - 1 - (pointer + 3 - 2 * colSize - rowSize);
            *colNum = startColNum;
        }
    }
}
int RoutingMap::seqPointertoLayerPointer(int layer, int seqPointer)
{
    int layerPointer = 0;
    int rowSize = 2 * layer + 1;
    int colSize = 2 * layer + 1;
    
    if (seqPointer < colSize) {
        layerPointer = seqPointer;
    } else if(seqPointer >= colSize && seqPointer < colSize + rowSize) {
        layerPointer = seqPointer - 1;
    } else if(seqPointer >= colSize + rowSize && seqPointer < 2 * colSize + rowSize) {
        layerPointer = seqPointer - 2;
    } else if(seqPointer >= 2 * colSize + rowSize && seqPointer < 2 * (colSize + rowSize)) {
        layerPointer = seqPointer - 3;
    }
    return layerPointer;
}

void RoutingMap::routeinLayer(int layerNum)
{
    
}

void RoutingMap::printBox(int layerRowNum, int layerColNum)
{
    printf("box at %d:%d\n", layerRowNum, layerColNum);
    for (int i = 0; i < map[layerRowNum * mapRowNum + layerColNum].top.size(); ++i) {
        if(!map[layerRowNum * mapRowNum + layerColNum].top[i]->isVirtual) {
            if (map[layerRowNum * mapRowNum + layerColNum].top[i]->wireId) {
                printf("%d ", *map[layerRowNum * mapRowNum + layerColNum].top[i]->wireId);
            } else {
                printf("x ");
            }
        } else {
            if (map[layerRowNum * mapRowNum + layerColNum].top[i]->wireId) {
                printf("%d' ", *map[layerRowNum * mapRowNum + layerColNum].top[i]->wireId);
            } else {
                printf("x ");
            }
        }
    }
    printf("| ");
    for (int i = 0; i < map[layerRowNum * mapRowNum + layerColNum].right.size(); ++i) {
        if(!map[layerRowNum * mapRowNum + layerColNum].right[i]->isVirtual) {
            if (map[layerRowNum * mapRowNum + layerColNum].right[i]->wireId) {
                printf("%d ", *map[layerRowNum * mapRowNum + layerColNum].right[i]->wireId);
            } else {
                printf("x ");
            }
        } else {
            if (map[layerRowNum * mapRowNum + layerColNum].right[i]->wireId) {
                printf("%d' ", *map[layerRowNum * mapRowNum + layerColNum].right[i]->wireId);
            } else {
                printf("x ");
            }
        }
    }
    printf("| ");
    for (int i = 0; i < map[layerRowNum * mapRowNum + layerColNum].buttom.size(); ++i) {
        if(!map[layerRowNum * mapRowNum + layerColNum].buttom[i]->isVirtual) {
            if (map[layerRowNum * mapRowNum + layerColNum].buttom[i]->wireId) {
                printf("%d ", *map[layerRowNum * mapRowNum + layerColNum].buttom[i]->wireId);
            } else {
                printf("x ");
            }
        } else {
            if (map[layerRowNum * mapRowNum + layerColNum].buttom[i]->wireId) {
                printf("%d' ", *map[layerRowNum * mapRowNum + layerColNum].buttom[i]->wireId);
            } else {
                printf("x ");
            }
        }
    }
    printf("| ");
    for (int i = 0; i < map[layerRowNum * mapRowNum + layerColNum].left.size(); ++i) {
        if(!map[layerRowNum * mapRowNum + layerColNum].left[i]->isVirtual) {
            if (map[layerRowNum * mapRowNum + layerColNum].left[i]->wireId) {
                printf("%d ", *map[layerRowNum * mapRowNum + layerColNum].left[i]->wireId);
            } else {
                printf("x ");
            }
        } else {
            if (map[layerRowNum * mapRowNum + layerColNum].left[i]->wireId) {
                printf("%d' ", *map[layerRowNum * mapRowNum + layerColNum].left[i]->wireId);
            } else {
                printf("x ");
            }
        }
    }
    printf("\n");
}
void RoutingMap::ringMaping(int layer, int startRowNum, int startColNum)
{
    int sequenceNum = 8 * layer + 4;
    int row0 = 0;
    int col0 = 0;
    int row1 = 0;
    int col1 = 0;
    edges side1 = topSide;
    for (int i = 0; i <= sequenceNum - 3; ++i) {
        layertoMap(layer, startRowNum, startColNum, i, &row0, &col0);
        for (int j = 0; j < sequenceNum; ++j) {
            seqtoMap(layer, startRowNum, startColNum, j, &row1, &col1, &side1);
            if (side1 == topSide) {
                for (int k = 1; map[row1 * mapColNum + col1].top.size(); ++k) {
                    if (map[row0 * mapColNum + col0].top[0] == map[row1 * mapColNum + col1].top[k]) {
                        map[row0 * mapColNum + col0].right.push_back(map[row1 * mapColNum + col1].top[k]);
                    }
                }
            } else if(side1 == rightSide){
                for (int k = 1; map[row1 * mapColNum + col1].right.size(); ++k) {
                    if (map[row0 * mapColNum + col0].top[0] == map[row1 * mapColNum + col1].right[k]) {
                        map[row0 * mapColNum + col0].right.push_back(map[row1 * mapColNum + col1].right[k]);
                    }
                }
            } else if(side1 == bottomSide){
                for (int k = 1; map[row1 * mapColNum + col1].buttom.size(); ++k) {
                    if (map[row0 * mapColNum + col0].top[0] == map[row1 * mapColNum + col1].buttom[k]) {
                        map[row0 * mapColNum + col0].right.push_back(map[row1 * mapColNum + col1].buttom[k]);
                    }
                }
            } else if(side1 == leftSide){
                for (int k = 1; map[row1 * mapColNum + col1].left.size(); ++k) {
                    if (map[row0 * mapColNum + col0].top[0] == map[row1 * mapColNum + col1].left[k]) {
                        map[row0 * mapColNum + col0].right.push_back(map[row1 * mapColNum + col1].left[k]);
                    }
                }
            }
        }
    }
}

void RoutingMap::insertNodetoPath(int layer, int startRow, int startCol, int startPoint, int endPoint)
{
    int rowSize = 2 * layer + 1;
    int colSize = 2 * layer + 1;

}

