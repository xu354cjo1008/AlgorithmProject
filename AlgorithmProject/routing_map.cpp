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
void RoutingMap::vnodeInserttoBox(int rowNum, int colNum, edges side, BumpNode *node, bool toBegin)
{
    if (toBegin) {
        if (side == topSide) {
            if (rowNum == 0) {
                if (map[rowNum * mapColNum + colNum].top.size() > 1) {
                    map[rowNum * mapColNum + colNum].top.insert(map[rowNum * mapColNum + colNum].top.begin() + 1, node);
                } else {
                    map[rowNum * mapColNum + colNum].top.push_back(node);
                }
            } else {
                if (map[rowNum * mapColNum + colNum].top.size() > 1) {
                    map[rowNum * mapColNum + colNum].top.insert(map[rowNum * mapColNum + colNum].top.begin() + 1, node);
                } else {
                    map[rowNum * mapColNum + colNum].top.push_back(node);
                }
                map[(rowNum - 1) * mapColNum + colNum].buttom.push_back(node);
            }
        } else if(side == rightSide) {
            if (colNum == mapColNum - 1) {
                if (map[rowNum * mapColNum + colNum].right.size() > 1) {
                    map[rowNum * mapColNum + colNum].right.insert(map[rowNum * mapColNum + colNum].right.begin() + 1, node);
                } else {
                    map[rowNum * mapColNum + colNum].right.push_back(node);
                }
            } else {
                if (map[rowNum * mapColNum + colNum].right.size() > 1) {
                    map[rowNum * mapColNum + colNum].right.insert(map[rowNum * mapColNum + colNum].right.begin() + 1, node);
                } else {
                    map[rowNum * mapColNum + colNum].right.push_back(node);
                }
                map[rowNum * mapColNum + colNum + 1].left.push_back(node);
            }
        } else if(side == bottomSide) {
            if (rowNum == mapRowNum - 1) {
                if (map[rowNum * mapColNum + colNum].buttom.size() > 1) {
                    map[rowNum * mapColNum + colNum].buttom.insert(map[rowNum * mapColNum + colNum].top.begin() + 1, node);
                } else {
                    map[rowNum * mapColNum + colNum].buttom.push_back(node);
                }
            } else {
                if (map[rowNum * mapColNum + colNum].buttom.size() > 1) {
                    map[rowNum * mapColNum + colNum].buttom.insert(map[rowNum * mapColNum + colNum].top.begin() + 1, node);
                } else {
                    map[rowNum * mapColNum + colNum].buttom.push_back(node);
                }
                map[(rowNum + 1) * mapColNum + colNum].top.push_back(node);
            }
        } else if(side == leftSide) {
            if (colNum == 0) {
                if (map[rowNum * mapColNum + colNum].left.size() > 1) {
                    map[rowNum * mapColNum + colNum].left.insert(map[rowNum * mapColNum + colNum].left.begin() + 1, node);
                } else {
                    map[rowNum * mapColNum + colNum].left.push_back(node);
                }
            } else {
                if (map[rowNum * mapColNum + colNum].left.size() > 1) {
                    map[rowNum * mapColNum + colNum].left.insert(map[rowNum * mapColNum + colNum].left.begin() + 1, node);
                } else {
                    map[rowNum * mapColNum + colNum].left.push_back(node);
                }
                map[rowNum * mapColNum + colNum - 1].right.push_back(node);
            }
        }
    } else {
        if (side == topSide) {
            if (rowNum == 0) {
                map[rowNum * mapColNum + colNum].top.push_back(node);
            } else {
                map[rowNum * mapColNum + colNum].top.push_back(node);
                if (map[(rowNum - 1) * mapColNum + colNum].buttom.size() > 1) {
                    map[(rowNum - 1) * mapColNum + colNum].buttom.insert(map[(rowNum - 1) * mapColNum + colNum].buttom.begin() + 1, node);
                } else {
                    map[(rowNum - 1) * mapColNum + colNum].buttom.push_back(node);
                }
            }
        } else if(side == rightSide) {
            if (colNum == mapColNum - 1) {
                map[rowNum * mapColNum + colNum].right.push_back(node);
            } else {
                map[rowNum * mapColNum + colNum].right.push_back(node);
                if (map[rowNum * mapColNum + colNum + 1].left.size() > 1) {
                    map[rowNum * mapColNum + colNum + 1].left.insert(map[rowNum * mapColNum + colNum + 1].right.begin() + 1, node);
                } else {
                    map[rowNum * mapColNum + colNum + 1].left.push_back(node);
                }
            }
        } else if(side == bottomSide) {
            if (rowNum == mapRowNum - 1) {
                map[rowNum * mapColNum + colNum].buttom.push_back(node);
            } else {
                map[rowNum * mapColNum + colNum].buttom.push_back(node);
                if (map[rowNum * mapColNum + colNum + 1].top.size() > 1) {
                    map[(rowNum + 1) * mapColNum + colNum].top.insert(map[(rowNum + 1) * mapColNum + colNum].buttom.begin() + 1, node);

                } else {
                    map[(rowNum + 1) * mapColNum + colNum].top.push_back(node);
                }
            }
        } else if(side == leftSide) {
            if (colNum == 0) {
                map[rowNum * mapColNum + colNum].left.push_back(node);
            } else {
                map[rowNum * mapColNum + colNum].left.push_back(node);
                if (map[rowNum * mapColNum + colNum + 1].right.size() > 1) {
                    map[rowNum * mapColNum + colNum - 1].right.insert(map[rowNum * mapColNum + colNum - 1].right.begin() + 1, node);
                } else {
                    map[rowNum * mapColNum + colNum - 1].right.push_back(node);
                }
            }
        }
    }
}
void RoutingMap::eraseVnode(int rowNum, int colNum, edges side, int pointer)
{
    if (side == topSide) {
        if (rowNum == 0) {
            if (map[rowNum * mapColNum + colNum].top.size() > 1) {
                map[rowNum * mapColNum + colNum].top.erase(map[rowNum * mapColNum + colNum].top.begin() + pointer);
            }
        } else {
            if (map[rowNum * mapColNum + colNum].top.size() > 1) {
                map[rowNum * mapColNum + colNum].top.erase(map[rowNum * mapColNum + colNum].top.begin() + pointer);
                map[(rowNum - 1) * mapColNum + colNum].buttom.erase(map[rowNum * mapColNum + colNum].buttom.begin() + map[rowNum * mapColNum + colNum].buttom.size() - pointer);
            }
        }
    } else if(side == rightSide) {
        if (colNum == mapColNum - 1) {
            if (map[rowNum * mapColNum + colNum].right.size() > 1) {
                map[rowNum * mapColNum + colNum].right.erase(map[rowNum * mapColNum + colNum].right.begin() + pointer);
            }
        } else {
            if (map[rowNum * mapColNum + colNum].right.size() > 1) {
                map[rowNum * mapColNum + colNum].right.erase(map[rowNum * mapColNum + colNum].right.begin() + pointer);
                map[rowNum * mapColNum + colNum + 1].left.erase(map[rowNum * mapColNum + colNum + 1].left.begin() + map[rowNum * mapColNum + colNum + 1].left.size() - pointer);
            }
        }
    } else if(side == bottomSide) {
        if (rowNum == mapRowNum - 1) {
            if (map[rowNum * mapColNum + colNum].buttom.size() > 1) {
                map[rowNum * mapColNum + colNum].buttom.erase(map[rowNum * mapColNum + colNum].buttom.begin() + pointer);
            }
        } else {
            if (map[rowNum * mapColNum + colNum].buttom.size() > 1) {
                map[rowNum * mapColNum + colNum].buttom.erase(map[rowNum * mapColNum + colNum].buttom.begin() + pointer);
                map[(rowNum + 1) * mapColNum + colNum].top.erase(map[(rowNum + 1) * mapColNum + colNum].top.begin() + map[(rowNum + 1) * mapColNum + colNum].top.size() - pointer);
            }
        }
    } else if(side == leftSide) {
        if (colNum == 0) {
            if (map[rowNum * mapColNum + colNum].left.size() > 1) {
                map[rowNum * mapColNum + colNum].left.erase(map[rowNum * mapColNum + colNum].left.begin() + pointer);
            }
        } else {
            if (map[rowNum * mapColNum + colNum].left.size() > 1) {
                map[rowNum * mapColNum + colNum].left.erase(map[rowNum * mapColNum + colNum].left.begin() + pointer);
                map[rowNum * mapColNum + colNum - 1].right.erase(map[rowNum * mapColNum + colNum - 1].right.begin() + map[rowNum * mapColNum + colNum - 1].right.size() - pointer);
            }
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
            vnodeInserttoBox(row, col, side, currentSeq[i], false);
        }
    }
    for (int i = 0; i < firstBumpPos; ++i) {
        vnodeInserttoBox(layerRowNum, layerColNum, leftSide, currentSeq[i], false);
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
        } else if(pointer >= 2 * colSize + rowSize - 3 && pointer < 2 * (rowSize + colSize) - 4) {
            *rowNum = startRowNum + rowSize - 1 - (pointer + 3 - 2 * colSize - rowSize);
            *colNum = startColNum;
        } else if(pointer == 2* (rowSize + colSize) - 4) {
            *rowNum = startRowNum;
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
    } else if(seqPointer >= 2 * colSize + rowSize && seqPointer < 2 * (colSize + rowSize) - 1) {
        layerPointer = seqPointer - 3;
    } else if (seqPointer == 2 * (colSize + rowSize) - 1) {
        layerPointer = 0;
    }
    return layerPointer;
}
edges RoutingMap::witchSide(int layer, int startRowNum, int startColNum, int pointer)
{
    int rowSize = 2 * layer + 1;
    int colSize = 2 * layer + 1;
    edges result;
    if (pointer == 0) {
        result = topAngle;
    } else if(pointer > 0 && pointer < colSize - 1) {
        result = topSide;
    } else if(pointer == colSize - 1) {
        result = rightAngle;
    } else if(pointer > colSize - 1 && pointer < colSize + rowSize - 2) {
        result = rightSide;
    } else if(pointer == colSize + rowSize - 2) {
        result = bottomAngle;
    } else if(pointer > colSize + rowSize - 2 && pointer < 2 * colSize + rowSize - 3) {
        result = bottomSide;
    } else if(pointer == 2 * colSize + rowSize - 3) {
        result = leftAngle;
    } else if(pointer > 2 * colSize + rowSize - 3 && pointer < 2 * (colSize + rowSize) - 4) {
        result = leftSide;
    } else if (pointer == 2 * (colSize + rowSize) - 4) {
        result = topAngle;
    }
    return result;
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
    for (int i = 0; i < sequenceNum - 4; ++i) {
        layertoMap(layer, startRowNum, startColNum, i, &row0, &col0);
        edges xWitchSide = witchSide(layer, startRowNum, startColNum, i);
        switch (xWitchSide) {
            case topAngle:
                if (map[row0 * mapColNum + col0].top[0]->wireId && map[row0 * mapColNum + col0].top[0]->mpscType == outCircle) {
                    outCircleSequence.push_back(map[row0 * mapColNum + col0].top[0]);
                }
                if (map[row0 * mapColNum + col0].left[0]->wireId && map[row0 * mapColNum + col0].left[0]->mpscType == outCircle) {
                    outCircleSequence.push_back(map[row0 * mapColNum + col0].left[0]);
                }
                break;
            case rightAngle:
                if (map[row0 * mapColNum + col0].top[0]->wireId && map[row0 * mapColNum + col0].top[0]->mpscType == outCircle) {
                    outCircleSequence.push_back(map[row0 * mapColNum + col0].top[0]);
                }
                if (map[row0 * mapColNum + col0].right[0]->wireId && map[row0 * mapColNum + col0].right[0]->mpscType == outCircle) {
                    outCircleSequence.push_back(map[row0 * mapColNum + col0].right[0]);
                }
                break;
            case bottomAngle:
                if (map[row0 * mapColNum + col0].right[0]->wireId && map[row0 * mapColNum + col0].right[0]->mpscType == outCircle) {
                    outCircleSequence.push_back(map[row0 * mapColNum + col0].right[0]);
                }
                if (map[row0 * mapColNum + col0].buttom[0]->wireId && map[row0 * mapColNum + col0].buttom[0]->mpscType == outCircle) {
                    outCircleSequence.push_back(map[row0 * mapColNum + col0].buttom[0]);
                }
                break;
            case leftAngle:
                if (map[row0 * mapColNum + col0].buttom[0]->wireId && map[row0 * mapColNum + col0].buttom[0]->mpscType == outCircle) {
                    outCircleSequence.push_back(map[row0 * mapColNum + col0].buttom[0]);
                }
                if (map[row0 * mapColNum + col0].left[0]->wireId && map[row0 * mapColNum + col0].left[0]->mpscType == outCircle) {
                    outCircleSequence.push_back(map[row0 * mapColNum + col0].left[0]);
                }
                break;
            case topSide:
                if (map[row0 * mapColNum + col0].top[0]->wireId && map[row0 * mapColNum + col0].top[0]->mpscType == outCircle) {
                    outCircleSequence.push_back(map[row0 * mapColNum + col0].top[0]);
                }
                break;
            case rightSide:
                if (map[row0 * mapColNum + col0].right[0]->wireId && map[row0 * mapColNum + col0].right[0]->mpscType == outCircle) {
                    outCircleSequence.push_back(map[row0 * mapColNum + col0].right[0]);
                }
                break;
            case bottomSide:
                if (map[row0 * mapColNum + col0].buttom[0]->wireId && map[row0 * mapColNum + col0].buttom[0]->mpscType == outCircle) {
                    outCircleSequence.push_back(map[row0 * mapColNum + col0].buttom[0]);
                }
                break;
            case leftSide:
                if (map[row0 * mapColNum + col0].left[0]->wireId && map[row0 * mapColNum + col0].left[0]->mpscType == outCircle) {
                    outCircleSequence.push_back(map[row0 * mapColNum + col0].left[0]);
                }
                break;
                
            default:
                break;
        }
        for (int j = 0; j < sequenceNum; ++j) {
            seqtoMap(layer, startRowNum, startColNum, j, &row1, &col1, &side1);
            int pointerTmp = seqPointertoLayerPointer(layer, j);
            if (side1 == topSide) {
                for (int k = 1; k < map[row1 * mapColNum + col1].top.size(); ++k) {
                    if (map[row0 * mapColNum + col0].top[0]->wireId && map[row0 * mapColNum + col0].top[0]->mpscType == inCircle && map[row0 * mapColNum + col0].top[0]->nextNode == map[row1 * mapColNum + col1].top[k]) {
                        insertNodetoPath(layer, startRowNum, startColNum, i, topAngle, pointerTmp, topSide, map[row0 * mapColNum + col0].top[0]);
                    } else if(map[row0 * mapColNum + col0].right[0]->wireId && map[row0 * mapColNum + col0].right[0]->mpscType == inCircle && map[row0 * mapColNum + col0].right[0]->nextNode == map[row1 * mapColNum + col1].top[k]) {
                        insertNodetoPath(layer, startRowNum, startColNum, i, rightAngle, pointerTmp, topSide, map[row0 * mapColNum + col0].right[0]);
                    } else if(map[row0 * mapColNum + col0].buttom[0]->wireId && map[row0 * mapColNum + col0].buttom[0]->mpscType == inCircle && map[row0 * mapColNum + col0].buttom[0]->nextNode == map[row1 * mapColNum + col1].top[k]) {
                        insertNodetoPath(layer, startRowNum, startColNum, i, bottomAngle, pointerTmp, topSide, map[row0 * mapColNum + col0].buttom[0]);
                    } else if(map[row0 * mapColNum + col0].left[0]->wireId && map[row0 * mapColNum + col0].left[0]->mpscType == inCircle && map[row0 * mapColNum + col0].left[0]->nextNode == map[row1 * mapColNum + col1].top[k]) {
                        insertNodetoPath(layer, startRowNum, startColNum, i, leftAngle, pointerTmp, topSide, map[row0 * mapColNum + col0].left[0]);
                    }
                }
            } else if(side1 == rightSide){
                for (int k = 1; k < map[row1 * mapColNum + col1].right.size(); ++k) {
                    if (map[row0 * mapColNum + col0].top[0]->wireId && map[row0 * mapColNum + col0].top[0]->mpscType == inCircle && map[row0 * mapColNum + col0].top[0]->nextNode == map[row1 * mapColNum + col1].right[k]) {
                        insertNodetoPath(layer, startRowNum, startColNum, i, topAngle, pointerTmp, rightSide, map[row0 * mapColNum + col0].top[0]);
                    } else if(map[row0 * mapColNum + col0].right[0]->wireId && map[row0 * mapColNum + col0].right[0]->mpscType == inCircle && map[row0 * mapColNum + col0].right[0]->nextNode == map[row1 * mapColNum + col1].right[k]) {
                        insertNodetoPath(layer, startRowNum, startColNum, i, rightAngle, pointerTmp, rightSide, map[row0 * mapColNum + col0].right[0]);
                    } else if(map[row0 * mapColNum + col0].buttom[0]->wireId && map[row0 * mapColNum + col0].buttom[0]->mpscType == inCircle && map[row0 * mapColNum + col0].buttom[0]->nextNode == map[row1 * mapColNum + col1].right[k]) {
                        insertNodetoPath(layer, startRowNum, startColNum, i, bottomAngle, pointerTmp, rightSide, map[row0 * mapColNum + col0].buttom[0]);
                    } else if(map[row0 * mapColNum + col0].left[0]->wireId && map[row0 * mapColNum + col0].left[0]->mpscType == inCircle && map[row0 * mapColNum + col0].left[0]->nextNode == map[row1 * mapColNum + col1].right[k]) {
                        insertNodetoPath(layer, startRowNum, startColNum, i, leftAngle, pointerTmp, rightSide, map[row0 * mapColNum + col0].left[0]);
                    }
                }
            } else if(side1 == bottomSide){
                for (int k = 1; k < map[row1 * mapColNum + col1].buttom.size(); ++k) {
                    if (map[row0 * mapColNum + col0].top[0]->wireId && map[row0 * mapColNum + col0].top[0]->mpscType == inCircle && map[row0 * mapColNum + col0].top[0]->nextNode == map[row1 * mapColNum + col1].buttom[k]) {
                        insertNodetoPath(layer, startRowNum, startColNum, i, topAngle, pointerTmp, bottomSide, map[row0 * mapColNum + col0].top[0]);
                    } else if(map[row0 * mapColNum + col0].right[0]->wireId && map[row0 * mapColNum + col0].right[0]->mpscType == inCircle && map[row0 * mapColNum + col0].right[0]->nextNode == map[row1 * mapColNum + col1].top[k]) {
                        insertNodetoPath(layer, startRowNum, startColNum, i, rightAngle, pointerTmp, bottomSide, map[row0 * mapColNum + col0].right[0]);
                    } else if(map[row0 * mapColNum + col0].buttom[0]->wireId && map[row0 * mapColNum + col0].buttom[0]->mpscType == inCircle && map[row0 * mapColNum + col0].buttom[0]->nextNode == map[row1 * mapColNum + col1].top[k]) {
                        insertNodetoPath(layer, startRowNum, startColNum, i, bottomAngle, pointerTmp, bottomSide, map[row0 * mapColNum + col0].buttom[0]);
                    } else if(map[row0 * mapColNum + col0].left[0]->wireId && map[row0 * mapColNum + col0].left[0]->mpscType == inCircle && map[row0 * mapColNum + col0].left[0]->nextNode == map[row1 * mapColNum + col1].top[k]) {
                        insertNodetoPath(layer, startRowNum, startColNum, i, leftAngle, pointerTmp, bottomSide, map[row0 * mapColNum + col0].left[0]);
                    }
                }
            } else if(side1 == leftSide){
                for (int k = 1; k < map[row1 * mapColNum + col1].left.size(); ++k) {
                    if (map[row0 * mapColNum + col0].top[0]->wireId && map[row0 * mapColNum + col0].top[0]->mpscType == inCircle && map[row0 * mapColNum + col0].top[0]->nextNode == map[row1 * mapColNum + col1].left[k]) {
                        insertNodetoPath(layer, startRowNum, startColNum, i, topAngle, pointerTmp, leftSide, map[row0 * mapColNum + col0].top[0]);
                    } else if(map[row0 * mapColNum + col0].right[0]->wireId && map[row0 * mapColNum + col0].right[0]->mpscType == inCircle && map[row0 * mapColNum + col0].right[0]->nextNode == map[row1 * mapColNum + col1].left[k]) {
                        insertNodetoPath(layer, startRowNum, startColNum, i, rightAngle, pointerTmp, leftSide, map[row0 * mapColNum + col0].right[0]);
                    } else if(map[row0 * mapColNum + col0].buttom[0]->wireId && map[row0 * mapColNum + col0].buttom[0]->mpscType == inCircle && map[row0 * mapColNum + col0].buttom[0]->nextNode == map[row1 * mapColNum + col1].left[k]) {
                        insertNodetoPath(layer, startRowNum, startColNum, i, bottomAngle, pointerTmp, leftSide, map[row0 * mapColNum + col0].buttom[0]);
                    } else if(map[row0 * mapColNum + col0].left[0]->wireId && map[row0 * mapColNum + col0].left[0]->mpscType == inCircle && map[row0 * mapColNum + col0].left[0]->nextNode == map[row1 * mapColNum + col1].left[k]) {
                        insertNodetoPath(layer, startRowNum, startColNum, i, leftAngle, pointerTmp, leftSide, map[row0 * mapColNum + col0].left[0]);
                    }
                }
            }
        }
    }
    int checkCount = 0;
    bool routeOK;
    for (int i = 0; i < sequenceNum - 4; ++i) {
        layertoMap(layer, startRowNum, startColNum, i, &row0, &col0);
        edges boxSide = witchSide(layer, startRowNum, startColNum, i);
        switch (boxSide) {
            case topAngle:
                map[row0 * mapColNum + col0].right_lock = false;
                map[row0 * mapColNum + col0].top_lock = true;
                map[row0 * mapColNum + col0].left_lock = true;
                break;
            case topSide:
                map[row0 * mapColNum + col0].right_lock = false;
                map[row0 * mapColNum + col0].top_lock = true;
                map[row0 * mapColNum + col0].buttom_lock = true;
                map[row0 * mapColNum + col0].left_lock = true;
                break;
            case rightAngle:
                map[row0 * mapColNum + col0].buttom_lock = false;
                map[row0 * mapColNum + col0].top_lock = true;
                map[row0 * mapColNum + col0].left_lock = true;
                map[row0 * mapColNum + col0].right_lock = true;
                break;
            case rightSide:
                map[row0 * mapColNum + col0].buttom_lock = false;
                map[row0 * mapColNum + col0].top_lock = true;
                map[row0 * mapColNum + col0].left_lock = true;
                map[row0 * mapColNum + col0].right_lock = true;
                break;
            case bottomAngle:
                map[row0 * mapColNum + col0].left_lock = false;
                map[row0 * mapColNum + col0].top_lock = true;
                map[row0 * mapColNum + col0].buttom_lock = true;
                map[row0 * mapColNum + col0].right_lock = true;
                break;
            case bottomSide:
                map[row0 * mapColNum + col0].left_lock = false;
                map[row0 * mapColNum + col0].top_lock = true;
                map[row0 * mapColNum + col0].buttom_lock = true;
                map[row0 * mapColNum + col0].right_lock = true;
                break;
            case leftAngle:
                map[row0 * mapColNum + col0].top_lock = false;
                map[row0 * mapColNum + col0].left_lock = true;
                map[row0 * mapColNum + col0].buttom_lock = true;
                map[row0 * mapColNum + col0].right_lock = true;
                break;
            case leftSide:
                map[row0 * mapColNum + col0].top_lock = false;
                map[row0 * mapColNum + col0].left_lock = true;
                map[row0 * mapColNum + col0].buttom_lock = true;
                map[row0 * mapColNum + col0].right_lock = true;
                break;
                
            default:
                break;
        }
        routeOK = boxnode_measurement(&map[row0 * mapColNum + col0]);
        if (!routeOK) {
            printf("route fail\n");
            refineBoxRoute(layer, startRowNum, startColNum, i);
            checkCount ++;
            if (checkCount > 3) {
                ++i;
                checkCount = 0;
            }
            --i;
        }
    }
}

void RoutingMap::insertNodetoPath(int layer, int startRow, int startCol, int startPoint, edges startSide, int endPoint, edges endSide, BumpNode *node)
{
    int rowSize = 2 * layer + 1;
    int colSize = 2 * layer + 1;
    int row0 = 0;
    int col0 = 0;
    int row1 = 0;
    int col1 = 0;
    if (endPoint == 0) {
        if (startPoint >= 3 * (rowSize - 1) && startPoint < 4 * (rowSize - 1)) {
            endPoint = 4 * (rowSize - 1);
        }
    }
    layertoMap(layer, startRow, startCol, endPoint, &row1, &col1);
    if (endPoint > startPoint) {
        if (endPoint > 0 && endPoint <= colSize - 1) {   //top side
            if (endSide == leftSide) {
                endPoint --;
            }
        } else if(endPoint > colSize && endPoint <= colSize + rowSize - 2) {   //right side
            if (endSide == topSide) {
                endPoint --;
            }
        } else if(endPoint > colSize + rowSize - 2 && endPoint <= 2 * colSize + rowSize - 3) {
            if (endSide == rightSide) {
                endPoint --;
            }
        } else if(endPoint > 2 * colSize + rowSize - 3 && endPoint <= 2 * (rowSize + colSize) - 5) {
            if (endSide == bottomSide) {
                endPoint --;
            }
        }
        for (int i = startPoint; i < endPoint; ++i) {
            layertoMap(layer, startRow, startCol, i, &row0, &col0);
            if (i < colSize - 1) {   //top side
                if (startSide == topAngle || startSide == leftAngle) {
                    BumpNode *vnode = new BumpNode(node->id, node->wireId, node->lcsType, true);
                    vnodeInserttoBox(row0, col0, rightSide, vnode, false);
                }
            } else if(i >= colSize - 1 && i < colSize + rowSize - 2) {   //right side
                if (startSide == topAngle || startSide == rightAngle) {
                    BumpNode *vnode = new BumpNode(node->id, node->wireId, node->lcsType, true);
                    vnodeInserttoBox(row0, col0, bottomSide, vnode, false);
                }
            } else if(i >= colSize + rowSize - 2 && i < 2 * colSize + rowSize - 3) {
                if (startSide == rightAngle || startSide == bottomAngle) {
                    BumpNode *vnode = new BumpNode(node->id, node->wireId, node->lcsType, true);
                    vnodeInserttoBox(row0, col0, leftSide, vnode, false);
                }
            } else if(i >= 2 * colSize + rowSize - 3 && i < 2 * (rowSize + colSize) - 5) {
                if (startSide == bottomAngle || startSide == leftAngle) {
                    BumpNode *vnode = new BumpNode(node->id, node->wireId, node->lcsType, true);
                    vnodeInserttoBox(row0, col0, topSide, vnode, false);
                }
            }
        }
    } else if(endPoint < startPoint){
        if (endPoint >= 0 && endPoint < colSize - 1) {   //top side
            if (endSide == rightSide) {
                endPoint ++;
            }
        } else if(endPoint >= colSize && endPoint < colSize + rowSize - 2) {   //right side
            if (endSide == bottomSide) {
                endPoint ++;
            }
        } else if(endPoint >= colSize + rowSize - 2 && endPoint < 2 * colSize + rowSize - 3) {
            if (endSide == leftSide) {
                endPoint ++;
            }
        } else if(endPoint >= 2 * colSize + rowSize - 3 && endPoint < 2 * (rowSize + colSize) - 5) {
            if (endSide == topSide) {
                endPoint ++;
            }
        }
        for (int i = startPoint; i > endPoint; --i) {
            layertoMap(layer, startRow, startCol, i, &row0, &col0);
            if (i <= colSize - 1) {   //top side
                if (startSide == rightAngle || startSide == bottomAngle) {
                    BumpNode *vnode = new BumpNode(node->id, node->wireId, node->lcsType, true);
                    vnodeInserttoBox(row0, col0, leftSide, vnode, false);
                }
            } else if(i > colSize - 1 && i <= colSize + rowSize - 2) {   //right side
                if (startSide == bottomAngle || startSide == leftAngle) {
                    BumpNode *vnode = new BumpNode(node->id, node->wireId, node->lcsType, true);
                    vnodeInserttoBox(row0, col0, topSide, vnode, false);
                }
            } else if(i > colSize + rowSize - 2 && i <= 2 * colSize + rowSize - 3) {
                if (startSide == leftAngle || startSide == topAngle) {
                    BumpNode *vnode = new BumpNode(node->id, node->wireId, node->lcsType, true);
                    vnodeInserttoBox(row0, col0, rightSide, vnode, false);
                }
            } else if(i > 2 * colSize + rowSize - 3 && i <= 2 * (rowSize + colSize) - 5) {
                if (startSide == topAngle || startSide == rightAngle) {
                    BumpNode *vnode = new BumpNode(node->id, node->wireId, node->lcsType, true);
                    vnodeInserttoBox(row0, col0, bottomSide, vnode, false);
                }
            }
        }
    }
}
void RoutingMap::moveNode(int fromRow, int fromCol, edges fromSide, int fromPointer, int toRow, int toCol, edges toSide, bool seqLeft)
{
    BumpNode *node = nullptr;
    switch (fromSide) {
        case topSide:
            node = map[fromRow * mapColNum + fromCol].top[fromPointer];
            eraseVnode(fromRow, fromCol, topSide, fromPointer);
            break;
        case rightSide:
            node = map[fromRow * mapColNum + fromCol].right[fromPointer];
            eraseVnode(fromRow, fromCol, rightSide, fromPointer);
            break;
        case bottomSide:
            node = map[fromRow * mapColNum + fromCol].buttom[fromPointer];
            eraseVnode(fromRow, fromCol, bottomSide, fromPointer);
            break;
        case leftSide:
            node = map[fromRow * mapColNum + fromCol].left[fromPointer];
            eraseVnode(fromRow, fromCol, leftSide, fromPointer);
            break;
        default:
            break;
    }
    switch (toSide) {
        case topSide:
            if (seqLeft) {
                vnodeInserttoBox(toRow, toCol, topSide, node, true);
              //  map[toRow * mapColNum + toCol].top.insert(map[toRow * mapColNum + toCol].top.begin() + 1, node);
            } else {
               // map[toRow * mapColNum + toCol].top.push_back(node);
                vnodeInserttoBox(toRow, toCol, topSide, node, false);
            }
            break;
        case rightSide:
            if (seqLeft) {
                vnodeInserttoBox(toRow, toCol, rightSide, node, true);
               // map[toRow * mapColNum + toCol].right.insert(map[toRow * mapColNum + toCol].right.begin() + 1, node);
            } else {
                vnodeInserttoBox(toRow, toCol, rightSide, node, false);
               // map[toRow * mapColNum + toCol].right.push_back(node);
            }
            break;
        case bottomSide:
            if (seqLeft) {
                vnodeInserttoBox(toRow, toCol, bottomSide, node, true);
            //    map[toRow * mapColNum + toCol].buttom.insert(map[toRow * mapColNum + toCol].buttom.begin() + 1, node);
            } else {
                vnodeInserttoBox(toRow, toCol, bottomSide, node, false);
            //    map[toRow * mapColNum + toCol].buttom.push_back(node);
            }
            break;
        case leftSide:
            if (seqLeft) {
                vnodeInserttoBox(toRow, toCol, leftSide, node, true);
          //      map[toRow * mapColNum + toCol].left.insert(map[toRow * mapColNum + toCol].left.begin() + 1, node);
            } else {
                vnodeInserttoBox(toRow, toCol, leftSide, node, false);
           //     map[toRow * mapColNum + toCol].left.push_back(node);
            }
            break;
            
        default:
            break;
    }
}
void RoutingMap::refineBoxRoute(int layer, int startRowNum, int startColNum, int pointer)
{
    int row = 0;
    int col = 0;
    int nextRow = 0;
    int nextCol = 0;
    layertoMap(layer, startRowNum, startColNum, pointer, &row, &col);
    edges boxSide = witchSide(layer, startRowNum, startColNum, pointer);
    switch (boxSide) {
        case topAngle:
            if (pointer == 0) {
                if (map[row * mapColNum + col].top[0]->wireId == nullptr) {
                    if (map[row * mapColNum + col].left.size() > map[row * mapColNum + col].top.size() + 1) {
                        layertoMap(layer, startRowNum, startColNum, pointer, &nextRow, &nextCol);
                        moveNode(row, col, leftSide, (int)(map[row * mapColNum + col].left.size()-1), nextRow, nextCol, topSide, true);
                    } else if(map[row * mapColNum + col].left.size() + 1 < map[row * mapColNum + col].top.size()) {
                        layertoMap(layer, startRowNum, startColNum, pointer, &nextRow, &nextCol);
                        moveNode(row, col, topSide, 1, nextRow, nextCol, leftSide, false);
                    }
                    break;
                }
                if (map[row * mapColNum + col].right[0]->wireId == nullptr) {
                    layertoMap(layer, startRowNum, startColNum, pointer + 1, &nextRow, &nextCol);
                    for (int i = 1; i < map[row * mapColNum + col].right.size(); ++i) {
                        if (map[row * mapColNum + col].right[i]->wireId == map[row * mapColNum + col].top.back()->wireId) {
                          //  map[row * mapColNum + col].right.erase(map[row * mapColNum + col].right.begin() + i);
                            eraseVnode(row, col, rightSide, i);
                        } else {
                            BumpNode *node = new BumpNode(map[row * mapColNum + col].top.back()->id, map[row * mapColNum + col].top.back()->wireId, map[row * mapColNum + col].top.back()->lcsType, true);
                           // map[row * mapColNum + col].right.push_back(node);
                            vnodeInserttoBox(row, col, rightSide, node, false);
                        }
                    }
                    moveNode(row, col, topSide, (int)(map[row * mapColNum + col].top.size()-1), nextRow, nextCol, topSide, true);
                    break;
                }
            }
            else if(pointer == 8 * layer) {
                if (map[row * mapColNum + col].top[0]->wireId == nullptr) {
                    if (map[row * mapColNum + col].left.size() > map[row * mapColNum + col].top.size() + 1) {
                        layertoMap(layer, startRowNum, startColNum, pointer, &nextRow, &nextCol);
                        moveNode(row, col, leftSide, (int)(map[row * mapColNum + col].left.end() - map[row * mapColNum + col].left.begin()), nextRow, nextCol, topSide, true);
                    } else if(map[row * mapColNum + col].left.size() + 1 < map[row * mapColNum + col].top.size()) {
                        layertoMap(layer, startRowNum, startColNum, pointer, &nextRow, &nextCol);
                        moveNode(row, col, topSide, 1, nextRow, nextCol, leftSide, false);
                    }
                    break;
                }
                if (map[row * mapColNum + col].left[0]->wireId == nullptr) {
                    layertoMap(layer, startRowNum, startColNum, pointer - 1, &nextRow, &nextCol);
                    for (int i = 1; i < map[row * mapColNum + col].buttom.size(); ++i) {
                        if (map[row * mapColNum + col].buttom[i]->wireId == map[row * mapColNum + col].left[1]->wireId) {
                         //   map[row * mapColNum + col].buttom.erase(map[row * mapColNum + col].buttom.begin() + i);
                            eraseVnode(row, col, bottomSide, i);
                        } else {
                            BumpNode *node = new BumpNode(map[row * mapColNum + col].left[1]->id, map[row * mapColNum + col].left[1]->wireId, map[row * mapColNum + col].left[1]->lcsType, true);
                          //  map[row * mapColNum + col].buttom.push_back(node);
                            vnodeInserttoBox(row, col, bottomSide, node, false);
                        }
                    }
                    moveNode(row, col, leftSide, 1, nextRow, nextCol, leftSide, false);
                    break;
                }
            }
            break;
        case topSide:
            if (map[row * mapColNum + col].right[0]->wireId == nullptr) {
                layertoMap(layer, startRowNum, startColNum, pointer + 1, &nextRow, &nextCol);
                for (int i = 1; i < map[row * mapColNum + col].right.size(); ++i) {
                    if (map[row * mapColNum + col].right[i]->wireId == map[row * mapColNum + col].top.back()->wireId) {
                       // map[row * mapColNum + col].right.erase(map[row * mapColNum + col].right.begin() + i);
                        eraseVnode(row, col, rightSide, i);
                    } else {
                        BumpNode *node = new BumpNode(map[row * mapColNum + col].top.back()->id, map[row * mapColNum + col].top.back()->wireId, map[row * mapColNum + col].top.back()->lcsType, true);
                       // map[row * mapColNum + col].right.push_back(node);
                        vnodeInserttoBox(row, col, rightSide, node, false);
                    }
                }
                moveNode(row, col, topSide, (int)(map[row * mapColNum + col].top.size() - 1), nextRow, nextCol, topSide, true);
                break;
            }
            break;
        case rightAngle:
            if (map[row * mapColNum + col].right[0]->wireId == nullptr) {
                layertoMap(layer, startRowNum, startColNum, pointer, &nextRow, &nextCol);
                moveNode(row, col, topSide, (int)(map[row * mapColNum + col].top.size()-1), nextRow, nextCol, rightSide, true);
                break;
            }
            if (map[row * mapColNum + col].buttom[0]->wireId == nullptr) {
                layertoMap(layer, startRowNum, startColNum, pointer + 1, &nextRow, &nextCol);
                for (int i = 1; i < map[row * mapColNum + col].buttom.size(); ++i) {
                    if (map[row * mapColNum + col].buttom[i]->wireId == map[row * mapColNum + col].right.back()->wireId) {
                   //     map[row * mapColNum + col].buttom.erase(map[row * mapColNum + col].buttom.begin() + i);
                        eraseVnode(row, col, bottomSide, i);
                    } else {
                        BumpNode *node = new BumpNode(map[row * mapColNum + col].right.back()->id, map[row * mapColNum + col].right.back()->wireId, map[row * mapColNum + col].right.back()->lcsType, true);
                     //   map[row * mapColNum + col].buttom.push_back(node);
                        vnodeInserttoBox(row, col, bottomSide, node, false);
                    }
                }
                moveNode(row, col, rightSide, (int)(map[row * mapColNum + col].right.size()-1), nextRow, nextCol, rightSide, true);
            }
            break;
        case rightSide:
            if (map[row * mapColNum + col].buttom[0]->wireId == nullptr) {
                layertoMap(layer, startRowNum, startColNum, pointer + 1, &nextRow, &nextCol);
                for (int i = 1; i < map[row * mapColNum + col].buttom.size(); ++i) {
                    if (map[row * mapColNum + col].buttom[i]->wireId == map[row * mapColNum + col].right.back()->wireId) {
                     //   map[row * mapColNum + col].buttom.erase(map[row * mapColNum + col].buttom.begin() + i);
                        eraseVnode(row, col, bottomSide, i);
                    } else {
                        BumpNode *node = new BumpNode(map[row * mapColNum + col].right.back()->id, map[row * mapColNum + col].right.back()->wireId, map[row * mapColNum + col].right.back()->lcsType, true);
                     //   map[row * mapColNum + col].buttom.push_back(node);
                        vnodeInserttoBox(row, col, bottomSide, node, false);
                    }
                }
                moveNode(row, col, rightSide, (int)(map[row * mapColNum + col].right.size() - 1), nextRow, nextCol, rightSide, true);
                break;
            }
            break;
        case bottomAngle:
            if (map[row * mapColNum + col].buttom[0]->wireId == nullptr) {
                layertoMap(layer, startRowNum, startColNum, pointer, &nextRow, &nextCol);
                moveNode(row, col, rightSide, (int)(map[row * mapColNum + col].right.size() - 1), nextRow, nextCol, bottomSide, true);
                break;
            }
            if (map[row * mapColNum + col].left[0]->wireId == nullptr) {
                layertoMap(layer, startRowNum, startColNum, pointer + 1, &nextRow, &nextCol);
                for (int i = 1; i < map[row * mapColNum + col].left.size(); ++i) {
                    if (map[row * mapColNum + col].left[i]->wireId == map[row * mapColNum + col].buttom.back()->wireId) {
                     //   map[row * mapColNum + col].left.erase(map[row * mapColNum + col].left.begin() + i);
                        eraseVnode(row, col, leftSide, i);
                    } else {
                        BumpNode *node = new BumpNode(map[row * mapColNum + col].buttom.back()->id, map[row * mapColNum + col].buttom.back()->wireId, map[row * mapColNum + col].buttom.back()->lcsType, true);
                    //    map[row * mapColNum + col].left.push_back(node);
                        vnodeInserttoBox(row, col, leftSide, node, false);
                    }
                }
                moveNode(row, col, bottomSide, (int)(map[row * mapColNum + col].buttom.size() - 1), nextRow, nextCol, bottomSide, true);
                break;
            }
            break;
        case bottomSide:
            if (map[row * mapColNum + col].left[0]->wireId == nullptr) {
                layertoMap(layer, startRowNum, startColNum, pointer + 1, &nextRow, &nextCol);
                for (int i = 1; i < map[row * mapColNum + col].left.size(); ++i) {
                    if (map[row * mapColNum + col].left[i]->wireId == map[row * mapColNum + col].buttom.back()->wireId) {
                      //  map[row * mapColNum + col].left.erase(map[row * mapColNum + col].left.begin() + i);
                        eraseVnode(row, col, leftSide, i);
                    } else {
                        BumpNode *node = new BumpNode(map[row * mapColNum + col].buttom.back()->id, map[row * mapColNum + col].buttom.back()->wireId, map[row * mapColNum + col].buttom.back()->lcsType, true);
                       // map[row * mapColNum + col].left.push_back(node);
                        vnodeInserttoBox(row, col, leftSide, node, false);
                    }
                }
                moveNode(row, col, bottomSide, (int)(map[row * mapColNum + col].buttom.size() - 1), nextRow, nextCol, bottomSide, true);
                break;
            }
            break;
        case leftAngle:
            if (map[row * mapColNum + col].left[0]->wireId == nullptr) {
                layertoMap(layer, startRowNum, startColNum, pointer, &nextRow, &nextCol);
                moveNode(row, col, bottomSide, (int)(map[row * mapColNum + col].buttom.size() - 1), nextRow, nextCol, leftSide, true);
                break;
            }
            if (map[row * mapColNum + col].top[0]->wireId == nullptr) {
                layertoMap(layer, startRowNum, startColNum, pointer + 1, &nextRow, &nextCol);
                for (int i = 1; i < map[row * mapColNum + col].top.size(); ++i) {
                    if (map[row * mapColNum + col].top[i]->wireId == map[row * mapColNum + col].left.back()->wireId) {
                  //      map[row * mapColNum + col].top.erase(map[row * mapColNum + col].top.begin() + i);
                        eraseVnode(row, col, topSide, i);
                    } else {
                        BumpNode *node = new BumpNode(map[row * mapColNum + col].left.back()->id, map[row * mapColNum + col].left.back()->wireId, map[row * mapColNum + col].left.back()->lcsType, true);
                     //   map[row * mapColNum + col].top.push_back(node);
                        vnodeInserttoBox(row, col, topSide, node, false);
                    }
                }
                moveNode(row, col, leftSide, (int)(map[row * mapColNum + col].left.size() - 1), nextRow, nextCol, leftSide, true);
                break;
            }
            break;
        case leftSide:
            if (map[row * mapColNum + col].top[0]->wireId == nullptr) {
                layertoMap(layer, startRowNum, startColNum, pointer + 1, &nextRow, &nextCol);
                for (int i = 1; i < map[row * mapColNum + col].top.size(); ++i) {
                    if (map[row * mapColNum + col].top[i]->wireId == map[row * mapColNum + col].left.back()->wireId) {
                      //  map[row * mapColNum + col].top.erase(map[row * mapColNum + col].top.begin() + i);
                        eraseVnode(row, col, topSide, i);
                    } else {
                        BumpNode *node = new BumpNode(map[row * mapColNum + col].left.back()->id, map[row * mapColNum + col].left.back()->wireId, map[row * mapColNum + col].left.back()->lcsType, true);
                      //  map[row * mapColNum + col].top.push_back(node);
                        vnodeInserttoBox(row, col, topSide, node, false);
                    }
                }
                moveNode(row, col, leftSide, (int)(map[row * mapColNum + col].left.size() - 1), nextRow, nextCol, leftSide, true);
                break;
            }
            break;
        default:
            break;
    }
}


