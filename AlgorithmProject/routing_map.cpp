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
    int mapPointer = -1;
    int firstBumpPos = 0;
    int row = 0;
    int col = 0;
    edges side = topSide;
    
    edges tmpSide = topSide;
    int x = 0;
    for (int i = 0; i < currentSeq.size(); ++i) {
        if (!currentSeq[i]->isVirtual) {
            if (mapPointer == -1) {
                firstBumpPos = i;
            }
            mapPointer ++;
            seqtoMap(layer, layerRowNum, layerColNum, mapPointer, &row, &col, &side);
            if (tmpSide != side) {
                x++;
            }
            tmpSide = side;

            switch (x) {
                case 0:
                    nodeInserttoMap(row, col, currentSeq[i]);
                    break;
                case 1:
                    nodeInserttoMap(row, col + 1, currentSeq[i]);
                    break;
                case 2:
                    nodeInserttoMap(row + 1, col + 1, currentSeq[i]);
                    break;
                case 3:
                    nodeInserttoMap(row + 1 , col, currentSeq[i]);
                    break;
                    
                default:
                    break;
            }
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

void RoutingMap::printBoxinLayer(int layer, int startRowNum, int startColNum)
{
    int p;
    int row,col;
    int layerBoxSize = layer * 8;
    if (layerBoxSize <= 0) {
        layerBoxSize = 1;
    }
    printf("/***********************************************************************************************************/\n");
    for (int i = 0; i < layerBoxSize; ++i) {
        layertoMap(layer, startRowNum, startColNum, p + i, &row, &col);
        printBox(row, col);
    }
    printf("/***********************************************************************************************************/\n");
}
void RoutingMap::ringMaping(int layer, int startRowNum, int startColNum)
{
    int currentSequenceNum = 8 * layer + 4;
    int preSequenceNum = (layer > 0)? 8 * (layer - 1) + 4: 0;
    int startSeqPointer = 0;
    int startBoxRow = 0;
    int startBoxCol = 0;
    edges startBoxSide = topSide;

    int endSeqPointer = 0;
    int endBoxRow = 0;
    int endBoxCol = 0;
    edges endBoxSide = topSide;


    int searchStartPointer = 0;
    int searchEndPointer = 0;
    if (layer > 0) {
        //previous layer to current path node insert
        for (startSeqPointer = 0; startSeqPointer < preSequenceNum; ++startSeqPointer) {
            seqtoMap(layer - 1, startRowNum + 1, startColNum + 1, startSeqPointer, &startBoxRow, &startBoxCol, &startBoxSide);
            switch (startBoxSide) {
                case topSide:
                    for (searchStartPointer = 0; searchStartPointer < map[startBoxRow * mapColNum +startBoxCol].top.size(); ++searchStartPointer) {
                        if (map[startBoxRow * mapColNum +startBoxCol].top[searchStartPointer]->lcsType == UnDirectRoute || (map[startBoxRow * mapColNum +startBoxCol].top[searchStartPointer]->lcsType == DirectRoute && map[startBoxRow * mapColNum +startBoxCol].top[searchStartPointer]->mpscType == outCircle)) {
                            continue;
                        }
                        bool searchFinish = false;
                        for (endSeqPointer = 0; endSeqPointer < currentSequenceNum; ++endSeqPointer) {
                            seqtoMap(layer, startRowNum, startColNum, endSeqPointer, &endBoxRow, &endBoxCol, &endBoxSide);
                            switch (endBoxSide) {
                                case topSide:
                                    for (searchEndPointer = 1; searchEndPointer < map[endBoxRow * mapColNum +endBoxCol].top.size(); ++searchEndPointer) {
                                        if (map[startBoxRow * mapColNum +startBoxCol].top[searchStartPointer]->nextNode == map[endBoxRow * mapColNum +endBoxCol].top[searchEndPointer]) {
                                            int startLayerPointer = seqPointertoLayerPointer(layer - 1, startSeqPointer);
                                            int endLayerPointer = seqPointertoLayerPointer(layer, endSeqPointer);
                                            insertNodetoPath(layer, startRowNum, startColNum, startLayerPointer, startBoxSide, layer - 1, startRowNum + 1, startColNum + 1,endLayerPointer, endBoxSide, map[startBoxRow * mapColNum +startBoxCol].top[searchStartPointer], map[endBoxRow * mapColNum +endBoxCol].top[searchEndPointer]);
                                            searchFinish = true;
                                            break;
                                        }
                                    }
                                    break;
                                case rightSide:
                                    for (searchEndPointer = 1; searchEndPointer < map[endBoxRow * mapColNum +endBoxCol].right.size(); ++searchEndPointer) {
                                        if (map[startBoxRow * mapColNum +startBoxCol].top[searchStartPointer]->nextNode == map[endBoxRow * mapColNum +endBoxCol].right[searchEndPointer]) {
                                            int startLayerPointer = seqPointertoLayerPointer(layer - 1, startSeqPointer);
                                            int endLayerPointer = seqPointertoLayerPointer(layer, endSeqPointer);
                                            insertNodetoPath(layer, startRowNum, startColNum, startLayerPointer, startBoxSide, layer - 1, startRowNum + 1, startColNum + 1,endLayerPointer, endBoxSide, map[startBoxRow * mapColNum +startBoxCol].top[searchStartPointer], map[endBoxRow * mapColNum +endBoxCol].right[searchEndPointer]);
                                            searchFinish = true;
                                            break;
                                        }
                                    }
                                    break;
                                case bottomSide:
                                    for (searchEndPointer = 1; searchEndPointer < map[endBoxRow * mapColNum +endBoxCol].buttom.size(); ++searchEndPointer) {
                                        if (map[startBoxRow * mapColNum +startBoxCol].top[searchStartPointer]->nextNode == map[endBoxRow * mapColNum +endBoxCol].buttom[searchEndPointer]) {
                                            int startLayerPointer = seqPointertoLayerPointer(layer - 1, startSeqPointer);
                                            int endLayerPointer = seqPointertoLayerPointer(layer, endSeqPointer);
                                            insertNodetoPath(layer, startRowNum, startColNum, startLayerPointer, startBoxSide, layer - 1, startRowNum + 1, startColNum + 1,endLayerPointer, endBoxSide, map[startBoxRow * mapColNum +startBoxCol].top[searchStartPointer], map[endBoxRow * mapColNum +endBoxCol].buttom[searchEndPointer]);
                                            searchFinish = true;
                                            break;
                                        }
                                    }
                                    break;
                                case leftSide:
                                    for (searchEndPointer = 1; searchEndPointer < map[endBoxRow * mapColNum +endBoxCol].left.size(); ++searchEndPointer) {
                                        if (map[startBoxRow * mapColNum +startBoxCol].top[searchStartPointer]->nextNode == map[endBoxRow * mapColNum +endBoxCol].left[searchEndPointer]) {
                                            int startLayerPointer = seqPointertoLayerPointer(layer - 1, startSeqPointer);
                                            int endLayerPointer = seqPointertoLayerPointer(layer, endSeqPointer);
                                            insertNodetoPath(layer, startRowNum, startColNum, startLayerPointer, startBoxSide, layer - 1, startRowNum + 1, startColNum + 1,endLayerPointer, endBoxSide, map[startBoxRow * mapColNum +startBoxCol].top[searchStartPointer], map[endBoxRow * mapColNum +endBoxCol].left[searchEndPointer]);
                                            searchFinish = true;
                                            break;
                                        }
                                    }
                                    break;
                                default:
                                    break;
                            }
                            if (searchFinish) {
                                break;
                            }
                        }
                    }
                    break;
                case rightSide:
                    for (searchStartPointer = 0; searchStartPointer < map[startBoxRow * mapColNum +startBoxCol].right.size(); ++searchStartPointer) {
                        if (map[startBoxRow * mapColNum +startBoxCol].right[searchStartPointer]->lcsType == UnDirectRoute || (map[startBoxRow * mapColNum +startBoxCol].right[searchStartPointer]->lcsType == DirectRoute && map[startBoxRow * mapColNum +startBoxCol].right[searchStartPointer]->mpscType == outCircle)) {
                            continue;
                        }
                        bool searchFinish = false;
                        for (endSeqPointer = 0; endSeqPointer < currentSequenceNum; ++endSeqPointer) {
                            seqtoMap(layer, startRowNum, startColNum, endSeqPointer, &endBoxRow, &endBoxCol, &endBoxSide);
                            switch (endBoxSide) {
                                case topSide:
                                    for (searchEndPointer = 1; searchEndPointer < map[endBoxRow * mapColNum +endBoxCol].top.size(); ++searchEndPointer) {
                                        if (map[startBoxRow * mapColNum +startBoxCol].right[searchStartPointer]->nextNode == map[endBoxRow * mapColNum +endBoxCol].top[searchEndPointer]) {
                                            int startLayerPointer = seqPointertoLayerPointer(layer - 1, startSeqPointer);
                                            int endLayerPointer = seqPointertoLayerPointer(layer, endSeqPointer);
                                            insertNodetoPath(layer, startRowNum, startColNum, startLayerPointer, startBoxSide, layer - 1, startRowNum + 1, startColNum + 1,endLayerPointer, endBoxSide, map[startBoxRow * mapColNum +startBoxCol].right[searchStartPointer], map[endBoxRow * mapColNum +endBoxCol].top[searchEndPointer]);
                                            searchFinish = true;
                                            break;
                                        }
                                    }
                                    break;
                                case rightSide:
                                    for (searchEndPointer = 1; searchEndPointer < map[endBoxRow * mapColNum +endBoxCol].right.size(); ++searchEndPointer) {
                                        if (map[startBoxRow * mapColNum +startBoxCol].right[searchStartPointer]->nextNode == map[endBoxRow * mapColNum +endBoxCol].right[searchEndPointer]) {
                                            int startLayerPointer = seqPointertoLayerPointer(layer - 1, startSeqPointer);
                                            int endLayerPointer = seqPointertoLayerPointer(layer, endSeqPointer);
                                            insertNodetoPath(layer, startRowNum, startColNum, startLayerPointer, startBoxSide, layer - 1, startRowNum + 1, startColNum + 1,endLayerPointer, endBoxSide, map[startBoxRow * mapColNum +startBoxCol].right[searchStartPointer], map[endBoxRow * mapColNum +endBoxCol].right[searchEndPointer]);
                                            searchFinish = true;
                                            break;
                                        }
                                    }
                                    break;
                                case bottomSide:
                                    for (searchEndPointer = 1; searchEndPointer < map[endBoxRow * mapColNum +endBoxCol].buttom.size(); ++searchEndPointer) {
                                        if (map[startBoxRow * mapColNum +startBoxCol].right[searchStartPointer]->nextNode == map[endBoxRow * mapColNum +endBoxCol].buttom[searchEndPointer]) {
                                            int startLayerPointer = seqPointertoLayerPointer(layer - 1, startSeqPointer);
                                            int endLayerPointer = seqPointertoLayerPointer(layer, endSeqPointer);
                                            insertNodetoPath(layer, startRowNum, startColNum, startLayerPointer, startBoxSide, layer - 1, startRowNum + 1, startColNum + 1,endLayerPointer, endBoxSide, map[startBoxRow * mapColNum +startBoxCol].right[searchStartPointer], map[endBoxRow * mapColNum +endBoxCol].buttom[searchEndPointer]);
                                            searchFinish = true;
                                            break;
                                        }
                                    }
                                    break;
                                case leftSide:
                                    for (searchEndPointer = 1; searchEndPointer < map[endBoxRow * mapColNum +endBoxCol].left.size(); ++searchEndPointer) {
                                        if (map[startBoxRow * mapColNum +startBoxCol].right[searchStartPointer]->nextNode == map[endBoxRow * mapColNum +endBoxCol].left[searchEndPointer]) {
                                            int startLayerPointer = seqPointertoLayerPointer(layer - 1, startSeqPointer);
                                            int endLayerPointer = seqPointertoLayerPointer(layer, endSeqPointer);
                                            insertNodetoPath(layer, startRowNum, startColNum, startLayerPointer, startBoxSide, layer - 1, startRowNum + 1, startColNum + 1,endLayerPointer, endBoxSide, map[startBoxRow * mapColNum +startBoxCol].right[searchStartPointer], map[endBoxRow * mapColNum +endBoxCol].left[searchEndPointer]);
                                            searchFinish = true;
                                            break;
                                        }
                                    }
                                    break;
                                default:
                                    break;
                            }
                            if (searchFinish) {
                                break;
                            }
                        }
                    }
                    break;
                case bottomSide:
                    for (searchStartPointer = 0; searchStartPointer < map[startBoxRow * mapColNum +startBoxCol].buttom.size(); ++searchStartPointer) {
                        if (map[startBoxRow * mapColNum +startBoxCol].buttom[searchStartPointer]->lcsType == UnDirectRoute || (map[startBoxRow * mapColNum +startBoxCol].buttom[searchStartPointer]->lcsType == DirectRoute && map[startBoxRow * mapColNum +startBoxCol].buttom[searchStartPointer]->mpscType == outCircle)) {
                            continue;
                        }
                        bool searchFinish = false;
                        for (endSeqPointer = 0; endSeqPointer < currentSequenceNum; ++endSeqPointer) {
                            seqtoMap(layer, startRowNum, startColNum, endSeqPointer, &endBoxRow, &endBoxCol, &endBoxSide);
                            switch (endBoxSide) {
                                case topSide:
                                    for (searchEndPointer = 1; searchEndPointer < map[endBoxRow * mapColNum +endBoxCol].top.size(); ++searchEndPointer) {
                                        if (map[startBoxRow * mapColNum +startBoxCol].buttom[searchStartPointer]->nextNode == map[endBoxRow * mapColNum +endBoxCol].top[searchEndPointer]) {
                                            int startLayerPointer = seqPointertoLayerPointer(layer - 1, startSeqPointer);
                                            int endLayerPointer = seqPointertoLayerPointer(layer, endSeqPointer);
                                            insertNodetoPath(layer, startRowNum, startColNum, startLayerPointer, startBoxSide, layer - 1, startRowNum + 1, startColNum + 1,endLayerPointer, endBoxSide, map[startBoxRow * mapColNum +startBoxCol].buttom[searchStartPointer], map[endBoxRow * mapColNum +endBoxCol].top[searchEndPointer]);
                                            searchFinish = true;
                                            break;
                                        }
                                    }
                                    break;
                                case rightSide:
                                    for (searchEndPointer = 1; searchEndPointer < map[endBoxRow * mapColNum +endBoxCol].right.size(); ++searchEndPointer) {
                                        if (map[startBoxRow * mapColNum +startBoxCol].buttom[searchStartPointer]->nextNode == map[endBoxRow * mapColNum +endBoxCol].right[searchEndPointer]) {
                                            int startLayerPointer = seqPointertoLayerPointer(layer - 1, startSeqPointer);
                                            int endLayerPointer = seqPointertoLayerPointer(layer, endSeqPointer);
                                            insertNodetoPath(layer, startRowNum, startColNum, startLayerPointer, startBoxSide, layer - 1, startRowNum + 1, startColNum + 1,endLayerPointer, endBoxSide, map[startBoxRow * mapColNum +startBoxCol].buttom[searchStartPointer], map[endBoxRow * mapColNum +endBoxCol].right[searchEndPointer]);
                                            searchFinish = true;
                                            break;
                                        }
                                    }
                                    break;
                                case bottomSide:
                                    for (searchEndPointer = 1; searchEndPointer < map[endBoxRow * mapColNum +endBoxCol].buttom.size(); ++searchEndPointer) {
                                        if (map[startBoxRow * mapColNum +startBoxCol].buttom[searchStartPointer]->nextNode == map[endBoxRow * mapColNum +endBoxCol].buttom[searchEndPointer]) {
                                            int startLayerPointer = seqPointertoLayerPointer(layer - 1, startSeqPointer);
                                            int endLayerPointer = seqPointertoLayerPointer(layer, endSeqPointer);
                                            insertNodetoPath(layer, startRowNum, startColNum, startLayerPointer, startBoxSide, layer - 1, startRowNum + 1, startColNum + 1,endLayerPointer, endBoxSide, map[startBoxRow * mapColNum +startBoxCol].buttom[searchStartPointer], map[endBoxRow * mapColNum +endBoxCol].buttom[searchEndPointer]);
                                            searchFinish = true;
                                            break;
                                        }
                                    }
                                    break;
                                case leftSide:
                                    for (searchEndPointer = 1; searchEndPointer < map[endBoxRow * mapColNum +endBoxCol].left.size(); ++searchEndPointer) {
                                        if (map[startBoxRow * mapColNum +startBoxCol].buttom[searchStartPointer]->nextNode == map[endBoxRow * mapColNum +endBoxCol].left[searchEndPointer]) {
                                            int startLayerPointer = seqPointertoLayerPointer(layer - 1, startSeqPointer);
                                            int endLayerPointer = seqPointertoLayerPointer(layer, endSeqPointer);
                                            insertNodetoPath(layer, startRowNum, startColNum, startLayerPointer, startBoxSide, layer - 1, startRowNum + 1, startColNum + 1,endLayerPointer, endBoxSide, map[startBoxRow * mapColNum +startBoxCol].buttom[searchStartPointer], map[endBoxRow * mapColNum +endBoxCol].left[searchEndPointer]);
                                            searchFinish = true;
                                            break;
                                        }
                                    }
                                    break;
                                default:
                                    break;
                            }
                            if (searchFinish) {
                                break;
                            }
                        }
                    }
                    break;
                case leftSide:
                    for (searchStartPointer = 0; searchStartPointer < map[startBoxRow * mapColNum +startBoxCol].left.size(); ++searchStartPointer) {
                        if (map[startBoxRow * mapColNum +startBoxCol].left[searchStartPointer]->lcsType == UnDirectRoute || (map[startBoxRow * mapColNum +startBoxCol].left[searchStartPointer]->lcsType == DirectRoute && map[startBoxRow * mapColNum +startBoxCol].left[searchStartPointer]->mpscType == outCircle)) {
                            continue;
                        }
                        bool searchFinish = false;
                        for (endSeqPointer = 0; endSeqPointer < currentSequenceNum; ++endSeqPointer) {
                            seqtoMap(layer, startRowNum, startColNum, endSeqPointer, &endBoxRow, &endBoxCol, &endBoxSide);
                            switch (endBoxSide) {
                                case topSide:
                                    for (searchEndPointer = 1; searchEndPointer < map[endBoxRow * mapColNum +endBoxCol].top.size(); ++searchEndPointer) {
                                        if (map[startBoxRow * mapColNum +startBoxCol].left[searchStartPointer]->nextNode == map[endBoxRow * mapColNum +endBoxCol].top[searchEndPointer]) {
                                            int startLayerPointer = seqPointertoLayerPointer(layer - 1, startSeqPointer);
                                            int endLayerPointer = seqPointertoLayerPointer(layer, endSeqPointer);
                                            insertNodetoPath(layer, startRowNum, startColNum, startLayerPointer, startBoxSide, layer - 1, startRowNum + 1, startColNum + 1,endLayerPointer, endBoxSide, map[startBoxRow * mapColNum +startBoxCol].left[searchStartPointer], map[endBoxRow * mapColNum +endBoxCol].top[searchEndPointer]);
                                            searchFinish = true;
                                            break;
                                        }
                                    }
                                    break;
                                case rightSide:
                                    for (searchEndPointer = 1; searchEndPointer < map[endBoxRow * mapColNum +endBoxCol].right.size(); ++searchEndPointer) {
                                        if (map[startBoxRow * mapColNum +startBoxCol].left[searchStartPointer]->nextNode == map[endBoxRow * mapColNum +endBoxCol].right[searchEndPointer]) {
                                            int startLayerPointer = seqPointertoLayerPointer(layer - 1, startSeqPointer);
                                            int endLayerPointer = seqPointertoLayerPointer(layer, endSeqPointer);
                                            insertNodetoPath(layer, startRowNum, startColNum, startLayerPointer, startBoxSide, layer - 1, startRowNum + 1, startColNum + 1,endLayerPointer, endBoxSide, map[startBoxRow * mapColNum +startBoxCol].left[searchStartPointer], map[endBoxRow * mapColNum +endBoxCol].right[searchEndPointer]);
                                            searchFinish = true;
                                            break;
                                        }
                                    }
                                    break;
                                case bottomSide:
                                    for (searchEndPointer = 1; searchEndPointer < map[endBoxRow * mapColNum +endBoxCol].buttom.size(); ++searchEndPointer) {
                                        if (map[startBoxRow * mapColNum +startBoxCol].left[searchStartPointer]->nextNode == map[endBoxRow * mapColNum +endBoxCol].buttom[searchEndPointer]) {
                                            int startLayerPointer = seqPointertoLayerPointer(layer - 1, startSeqPointer);
                                            int endLayerPointer = seqPointertoLayerPointer(layer, endSeqPointer);
                                            insertNodetoPath(layer, startRowNum, startColNum, startLayerPointer, startBoxSide, layer - 1, startRowNum + 1, startColNum + 1,endLayerPointer, endBoxSide, map[startBoxRow * mapColNum +startBoxCol].left[searchStartPointer], map[endBoxRow * mapColNum +endBoxCol].buttom[searchEndPointer]);
                                            searchFinish = true;
                                            break;
                                        }
                                    }
                                    break;
                                case leftSide:
                                    for (searchEndPointer = 1; searchEndPointer < map[endBoxRow * mapColNum +endBoxCol].left.size(); ++searchEndPointer) {
                                        if (map[startBoxRow * mapColNum +startBoxCol].left[searchStartPointer]->nextNode == map[endBoxRow * mapColNum +endBoxCol].left[searchEndPointer]) {
                                            int startLayerPointer = seqPointertoLayerPointer(layer - 1, startSeqPointer);
                                            int endLayerPointer = seqPointertoLayerPointer(layer, endSeqPointer);
                                            insertNodetoPath(layer, startRowNum, startColNum, startLayerPointer, startBoxSide, layer - 1, startRowNum + 1, startColNum + 1,endLayerPointer, endBoxSide, map[startBoxRow * mapColNum +startBoxCol].left[searchStartPointer], map[endBoxRow * mapColNum +endBoxCol].left[searchEndPointer]);
                                            searchFinish = true;
                                            break;
                                        }
                                    }
                                    break;
                                default:
                                    break;
                            }
                            if (searchFinish) {
                                break;
                            }
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    }
    // current layer to current path node insert
    for (startSeqPointer = 0; startSeqPointer < currentSequenceNum; ++startSeqPointer) {
        seqtoMap(layer, startRowNum, startColNum, startSeqPointer, &startBoxRow, &startBoxCol, &startBoxSide);
        switch (startBoxSide) {
            case topSide:
                for (searchStartPointer = 0; searchStartPointer < map[startBoxRow * mapColNum +startBoxCol].top.size(); ++searchStartPointer) {
                    if (map[startBoxRow * mapColNum +startBoxCol].top[searchStartPointer]->lcsType == DirectRoute || (map[startBoxRow * mapColNum +startBoxCol].top[searchStartPointer]->lcsType == UnDirectRoute && map[startBoxRow * mapColNum +startBoxCol].top[searchStartPointer]->mpscType == outCircle)) {
                        continue;
                    }
                    bool searchFinish = false;
                    for (endSeqPointer = 0; endSeqPointer < currentSequenceNum; ++endSeqPointer) {
                        seqtoMap(layer, startRowNum, startColNum, endSeqPointer, &endBoxRow, &endBoxCol, &endBoxSide);
                        switch (endBoxSide) {
                            case topSide:
                                for (searchEndPointer = 1; searchEndPointer < map[endBoxRow * mapColNum +endBoxCol].top.size(); ++searchEndPointer) {
                                    if (map[startBoxRow * mapColNum +startBoxCol].top[searchStartPointer]->nextNode == map[endBoxRow * mapColNum +endBoxCol].top[searchEndPointer]) {
                                        int startLayerPointer = seqPointertoLayerPointer(layer, startSeqPointer);
                                        int endLayerPointer = seqPointertoLayerPointer(layer, endSeqPointer);
                                        insertNodetoPath(layer, startRowNum, startColNum, startLayerPointer, startBoxSide, layer, startRowNum, startColNum, endLayerPointer, endBoxSide, map[startBoxRow * mapColNum +startBoxCol].top[searchStartPointer], map[endBoxRow * mapColNum +endBoxCol].top[searchEndPointer]);
                                        searchFinish = true;
                                        break;
                                    }
                                }
                                break;
                            case rightSide:
                                for (searchEndPointer = 1; searchEndPointer < map[endBoxRow * mapColNum +endBoxCol].right.size(); ++searchEndPointer) {
                                    if (map[startBoxRow * mapColNum +startBoxCol].top[searchStartPointer]->nextNode == map[endBoxRow * mapColNum +endBoxCol].right[searchEndPointer]) {
                                        int startLayerPointer = seqPointertoLayerPointer(layer, startSeqPointer);
                                        int endLayerPointer = seqPointertoLayerPointer(layer, endSeqPointer);
                                        insertNodetoPath(layer, startRowNum, startColNum, startLayerPointer, startBoxSide, layer, startRowNum, startColNum, endLayerPointer, endBoxSide, map[startBoxRow * mapColNum +startBoxCol].top[searchStartPointer], map[endBoxRow * mapColNum +endBoxCol].right[searchEndPointer]);
                                        searchFinish = true;
                                        break;
                                    }
                                }
                                break;
                            case bottomSide:
                                for (searchEndPointer = 1; searchEndPointer < map[endBoxRow * mapColNum +endBoxCol].buttom.size(); ++searchEndPointer) {
                                    if (map[startBoxRow * mapColNum +startBoxCol].top[searchStartPointer]->nextNode == map[endBoxRow * mapColNum +endBoxCol].buttom[searchEndPointer]) {
                                        int startLayerPointer = seqPointertoLayerPointer(layer, startSeqPointer);
                                        int endLayerPointer = seqPointertoLayerPointer(layer, endSeqPointer);
                                        insertNodetoPath(layer, startRowNum, startColNum, startLayerPointer, startBoxSide, layer, startRowNum, startColNum, endLayerPointer, endBoxSide, map[startBoxRow * mapColNum +startBoxCol].top[searchStartPointer], map[endBoxRow * mapColNum +endBoxCol].buttom[searchEndPointer]);
                                        searchFinish = true;
                                        break;
                                    }
                                }
                                break;
                            case leftSide:
                                for (searchEndPointer = 1; searchEndPointer < map[endBoxRow * mapColNum +endBoxCol].left.size(); ++searchEndPointer) {
                                    if (map[startBoxRow * mapColNum +startBoxCol].top[searchStartPointer]->nextNode == map[endBoxRow * mapColNum +endBoxCol].left[searchEndPointer]) {
                                        int startLayerPointer = seqPointertoLayerPointer(layer, startSeqPointer);
                                        int endLayerPointer = seqPointertoLayerPointer(layer, endSeqPointer);
                                        insertNodetoPath(layer, startRowNum, startColNum, startLayerPointer, startBoxSide, layer, startRowNum, startColNum, endLayerPointer, endBoxSide, map[startBoxRow * mapColNum +startBoxCol].top[searchStartPointer], map[endBoxRow * mapColNum +endBoxCol].left[searchEndPointer]);
                                        searchFinish = true;
                                        break;
                                    }
                                }
                                break;
                            default:
                                break;
                        }
                        if (searchFinish) {
                            break;
                        }
                    }
                }
                break;
            case rightSide:
                for (searchStartPointer = 0; searchStartPointer < map[startBoxRow * mapColNum +startBoxCol].right.size(); ++searchStartPointer) {
                    if (map[startBoxRow * mapColNum +startBoxCol].right[searchStartPointer]->lcsType == DirectRoute || (map[startBoxRow * mapColNum +startBoxCol].right[searchStartPointer]->lcsType == UnDirectRoute && map[startBoxRow * mapColNum +startBoxCol].right[searchStartPointer]->mpscType == outCircle)) {
                        continue;
                    }
                    bool searchFinish = false;
                    for (endSeqPointer = 0; endSeqPointer < currentSequenceNum; ++endSeqPointer) {
                        seqtoMap(layer, startRowNum, startColNum, endSeqPointer, &endBoxRow, &endBoxCol, &endBoxSide);
                        switch (endBoxSide) {
                            case topSide:
                                for (searchEndPointer = 1; searchEndPointer < map[endBoxRow * mapColNum +endBoxCol].top.size(); ++searchEndPointer) {
                                    if (map[startBoxRow * mapColNum +startBoxCol].right[searchStartPointer]->nextNode == map[endBoxRow * mapColNum +endBoxCol].top[searchEndPointer]) {
                                        int startLayerPointer = seqPointertoLayerPointer(layer, startSeqPointer);
                                        int endLayerPointer = seqPointertoLayerPointer(layer, endSeqPointer);
                                        insertNodetoPath(layer, startRowNum, startColNum, startLayerPointer, startBoxSide, layer, startRowNum, startColNum, endLayerPointer, endBoxSide, map[startBoxRow * mapColNum +startBoxCol].right[searchStartPointer], map[endBoxRow * mapColNum +endBoxCol].top[searchEndPointer]);
                                        searchFinish = true;
                                        break;
                                    }
                                }
                                break;
                            case rightSide:
                                for (searchEndPointer = 1; searchEndPointer < map[endBoxRow * mapColNum +endBoxCol].right.size(); ++searchEndPointer) {
                                    if (map[startBoxRow * mapColNum +startBoxCol].right[searchStartPointer]->nextNode == map[endBoxRow * mapColNum +endBoxCol].right[searchEndPointer]) {
                                        int startLayerPointer = seqPointertoLayerPointer(layer, startSeqPointer);
                                        int endLayerPointer = seqPointertoLayerPointer(layer, endSeqPointer);
                                        insertNodetoPath(layer, startRowNum, startColNum, startLayerPointer, startBoxSide, layer, startRowNum, startColNum, endLayerPointer, endBoxSide, map[startBoxRow * mapColNum +startBoxCol].right[searchStartPointer], map[endBoxRow * mapColNum +endBoxCol].right[searchEndPointer]);
                                        searchFinish = true;
                                        break;
                                    }
                                }
                                break;
                            case bottomSide:
                                for (searchEndPointer = 1; searchEndPointer < map[endBoxRow * mapColNum +endBoxCol].buttom.size(); ++searchEndPointer) {
                                    if (map[startBoxRow * mapColNum +startBoxCol].right[searchStartPointer]->nextNode == map[endBoxRow * mapColNum +endBoxCol].buttom[searchEndPointer]) {
                                        int startLayerPointer = seqPointertoLayerPointer(layer, startSeqPointer);
                                        int endLayerPointer = seqPointertoLayerPointer(layer, endSeqPointer);
                                        insertNodetoPath(layer, startRowNum, startColNum, startLayerPointer, startBoxSide, layer, startRowNum, startColNum, endLayerPointer, endBoxSide, map[startBoxRow * mapColNum +startBoxCol].right[searchStartPointer], map[endBoxRow * mapColNum +endBoxCol].buttom[searchEndPointer]);
                                        searchFinish = true;
                                        break;
                                    }
                                }
                                break;
                            case leftSide:
                                for (searchEndPointer = 1; searchEndPointer < map[endBoxRow * mapColNum +endBoxCol].left.size(); ++searchEndPointer) {
                                    if (map[startBoxRow * mapColNum +startBoxCol].right[searchStartPointer]->nextNode == map[endBoxRow * mapColNum +endBoxCol].left[searchEndPointer]) {
                                        int startLayerPointer = seqPointertoLayerPointer(layer, startSeqPointer);
                                        int endLayerPointer = seqPointertoLayerPointer(layer, endSeqPointer);
                                        insertNodetoPath(layer, startRowNum, startColNum, startLayerPointer, startBoxSide, layer, startRowNum, startColNum, endLayerPointer, endBoxSide, map[startBoxRow * mapColNum +startBoxCol].right[searchStartPointer], map[endBoxRow * mapColNum +endBoxCol].left[searchEndPointer]);
                                        searchFinish = true;
                                        break;
                                    }
                                }
                                break;
                            default:
                                break;
                        }
                        if (searchFinish) {
                            break;
                        }
                    }
                }
                break;
            case bottomSide:
                for (searchStartPointer = 0; searchStartPointer < map[startBoxRow * mapColNum +startBoxCol].buttom.size(); ++searchStartPointer) {
                    if (map[startBoxRow * mapColNum +startBoxCol].buttom[searchStartPointer]->lcsType == DirectRoute || (map[startBoxRow * mapColNum +startBoxCol].buttom[searchStartPointer]->lcsType == UnDirectRoute && map[startBoxRow * mapColNum +startBoxCol].buttom[searchStartPointer]->mpscType == outCircle)) {
                        continue;
                    }
                    bool searchFinish = false;
                    for (endSeqPointer = 0; endSeqPointer < currentSequenceNum; ++endSeqPointer) {
                        seqtoMap(layer, startRowNum, startColNum, endSeqPointer, &endBoxRow, &endBoxCol, &endBoxSide);
                        switch (endBoxSide) {
                            case topSide:
                                for (searchEndPointer = 1; searchEndPointer < map[endBoxRow * mapColNum +endBoxCol].top.size(); ++searchEndPointer) {
                                    if (map[startBoxRow * mapColNum +startBoxCol].buttom[searchStartPointer]->nextNode == map[endBoxRow * mapColNum +endBoxCol].top[searchEndPointer]) {
                                        int startLayerPointer = seqPointertoLayerPointer(layer, startSeqPointer);
                                        int endLayerPointer = seqPointertoLayerPointer(layer, endSeqPointer);
                                        insertNodetoPath(layer, startRowNum, startColNum, startLayerPointer, startBoxSide, layer, startRowNum, startColNum, endLayerPointer, endBoxSide, map[startBoxRow * mapColNum +startBoxCol].buttom[searchStartPointer], map[endBoxRow * mapColNum +endBoxCol].top[searchEndPointer]);
                                        searchFinish = true;
                                        break;
                                    }
                                }
                                break;
                            case rightSide:
                                for (searchEndPointer = 1; searchEndPointer < map[endBoxRow * mapColNum +endBoxCol].right.size(); ++searchEndPointer) {
                                    if (map[startBoxRow * mapColNum +startBoxCol].buttom[searchStartPointer]->nextNode == map[endBoxRow * mapColNum +endBoxCol].right[searchEndPointer]) {
                                        int startLayerPointer = seqPointertoLayerPointer(layer, startSeqPointer);
                                        int endLayerPointer = seqPointertoLayerPointer(layer, endSeqPointer);
                                        insertNodetoPath(layer, startRowNum, startColNum, startLayerPointer, startBoxSide, layer, startRowNum, startColNum, endLayerPointer, endBoxSide, map[startBoxRow * mapColNum +startBoxCol].buttom[searchStartPointer], map[endBoxRow * mapColNum +endBoxCol].right[searchEndPointer]);
                                        searchFinish = true;
                                        break;
                                    }
                                }
                                break;
                            case bottomSide:
                                for (searchEndPointer = 1; searchEndPointer < map[endBoxRow * mapColNum +endBoxCol].buttom.size(); ++searchEndPointer) {
                                    if (map[startBoxRow * mapColNum +startBoxCol].buttom[searchStartPointer]->nextNode == map[endBoxRow * mapColNum +endBoxCol].buttom[searchEndPointer]) {
                                        int startLayerPointer = seqPointertoLayerPointer(layer, startSeqPointer);
                                        int endLayerPointer = seqPointertoLayerPointer(layer, endSeqPointer);
                                        insertNodetoPath(layer, startRowNum, startColNum, startLayerPointer, startBoxSide, layer, startRowNum, startColNum, endLayerPointer, endBoxSide, map[startBoxRow * mapColNum +startBoxCol].buttom[searchStartPointer], map[endBoxRow * mapColNum +endBoxCol].buttom[searchEndPointer]);
                                        searchFinish = true;
                                        break;
                                    }
                                }
                                break;
                            case leftSide:
                                for (searchEndPointer = 1; searchEndPointer < map[endBoxRow * mapColNum +endBoxCol].left.size(); ++searchEndPointer) {
                                    if (map[startBoxRow * mapColNum +startBoxCol].buttom[searchStartPointer]->nextNode == map[endBoxRow * mapColNum +endBoxCol].left[searchEndPointer]) {
                                        int startLayerPointer = seqPointertoLayerPointer(layer, startSeqPointer);
                                        int endLayerPointer = seqPointertoLayerPointer(layer, endSeqPointer);
                                        insertNodetoPath(layer, startRowNum, startColNum, startLayerPointer, startBoxSide, layer, startRowNum, startColNum, endLayerPointer, endBoxSide, map[startBoxRow * mapColNum +startBoxCol].buttom[searchStartPointer], map[endBoxRow * mapColNum +endBoxCol].left[searchEndPointer]);
                                        searchFinish = true;
                                        break;
                                    }
                                }
                                break;
                            default:
                                break;
                        }
                        if (searchFinish) {
                            break;
                        }
                    }
                }
                break;
            case leftSide:
                for (searchStartPointer = 0; searchStartPointer < map[startBoxRow * mapColNum +startBoxCol].left.size(); ++searchStartPointer) {
                    if (map[startBoxRow * mapColNum +startBoxCol].left[searchStartPointer]->lcsType == DirectRoute || (map[startBoxRow * mapColNum +startBoxCol].left[searchStartPointer]->lcsType == UnDirectRoute && map[startBoxRow * mapColNum +startBoxCol].left[searchStartPointer]->mpscType == outCircle)) {
                        continue;
                    }
                    bool searchFinish = false;
                    for (endSeqPointer = 0; endSeqPointer < currentSequenceNum; ++endSeqPointer) {
                        seqtoMap(layer, startRowNum, startColNum, endSeqPointer, &endBoxRow, &endBoxCol, &endBoxSide);
                        switch (endBoxSide) {
                            case topSide:
                                for (searchEndPointer = 1; searchEndPointer < map[endBoxRow * mapColNum +endBoxCol].top.size(); ++searchEndPointer) {
                                    if (map[startBoxRow * mapColNum +startBoxCol].left[searchStartPointer]->nextNode == map[endBoxRow * mapColNum +endBoxCol].top[searchEndPointer]) {
                                        int startLayerPointer = seqPointertoLayerPointer(layer, startSeqPointer);
                                        int endLayerPointer = seqPointertoLayerPointer(layer, endSeqPointer);
                                        insertNodetoPath(layer, startRowNum, startColNum, startLayerPointer, startBoxSide, layer, startRowNum, startColNum, endLayerPointer, endBoxSide, map[startBoxRow * mapColNum +startBoxCol].left[searchStartPointer], map[endBoxRow * mapColNum +endBoxCol].top[searchEndPointer]);
                                        searchFinish = true;
                                        break;
                                    }
                                }
                                break;
                            case rightSide:
                                for (searchEndPointer = 1; searchEndPointer < map[endBoxRow * mapColNum +endBoxCol].right.size(); ++searchEndPointer) {
                                    if (map[startBoxRow * mapColNum +startBoxCol].left[searchStartPointer]->nextNode == map[endBoxRow * mapColNum +endBoxCol].right[searchEndPointer]) {
                                        int startLayerPointer = seqPointertoLayerPointer(layer, startSeqPointer);
                                        int endLayerPointer = seqPointertoLayerPointer(layer, endSeqPointer);
                                        insertNodetoPath(layer, startRowNum, startColNum, startLayerPointer, startBoxSide, layer, startRowNum, startColNum, endLayerPointer, endBoxSide, map[startBoxRow * mapColNum +startBoxCol].left[searchStartPointer], map[endBoxRow * mapColNum +endBoxCol].right[searchEndPointer]);
                                        searchFinish = true;
                                        break;
                                    }
                                }
                                break;
                            case bottomSide:
                                for (searchEndPointer = 1; searchEndPointer < map[endBoxRow * mapColNum +endBoxCol].buttom.size(); ++searchEndPointer) {
                                    if (map[startBoxRow * mapColNum +startBoxCol].left[searchStartPointer]->nextNode == map[endBoxRow * mapColNum +endBoxCol].buttom[searchEndPointer]) {
                                        int startLayerPointer = seqPointertoLayerPointer(layer, startSeqPointer);
                                        int endLayerPointer = seqPointertoLayerPointer(layer, endSeqPointer);
                                        insertNodetoPath(layer, startRowNum, startColNum, startLayerPointer, startBoxSide, layer, startRowNum, startColNum, endLayerPointer, endBoxSide, map[startBoxRow * mapColNum +startBoxCol].left[searchStartPointer], map[endBoxRow * mapColNum +endBoxCol].buttom[searchEndPointer]);
                                        searchFinish = true;
                                        break;
                                    }
                                }
                                break;
                            case leftSide:
                                for (searchEndPointer = 1; searchEndPointer < map[endBoxRow * mapColNum +endBoxCol].left.size(); ++searchEndPointer) {
                                    if (map[startBoxRow * mapColNum +startBoxCol].left[searchStartPointer]->nextNode == map[endBoxRow * mapColNum +endBoxCol].left[searchEndPointer]) {
                                        int startLayerPointer = seqPointertoLayerPointer(layer, startSeqPointer);
                                        int endLayerPointer = seqPointertoLayerPointer(layer, endSeqPointer);
                                        insertNodetoPath(layer, startRowNum, startColNum, startLayerPointer, startBoxSide, layer, startRowNum, startColNum, endLayerPointer, endBoxSide, map[startBoxRow * mapColNum +startBoxCol].left[searchStartPointer], map[endBoxRow * mapColNum +endBoxCol].left[searchEndPointer]);
                                        searchFinish = true;
                                        break;
                                    }
                                }
                                break;
                            default:
                                break;
                        }
                        if (searchFinish) {
                            break;
                        }
                    }
                }
                break;
            default:
                break;
        }
    }
    layerPathMaping(layer, startRowNum, startColNum);
}

void RoutingMap::insertNodetoPath(int layer, int startRow, int startCol, int startSeqPoint, edges startNodeSide, int endLayer, int endStartRow, int endStartCol, int endSeqPoint, edges endNodeSide, BumpNode *startNode, BumpNode *endNode)
{
    //find start node and end node side
    switch (startNodeSide) {
        case topSide:
            if (startNode->isVirtual == false) {
                startNodeSide = topAngle;
            }
            break;
        case rightSide:
            if (startNode->isVirtual == false) {
                startNodeSide = rightAngle;
            }
            break;
        case bottomSide:
            if (startNode->isVirtual == false) {
                startNodeSide = bottomAngle;
            }
            break;
        case leftSide:
            if (startNode->isVirtual == false) {
                startNodeSide = leftAngle;
            }
            break;
        default:
            break;
    }
    switch (endNodeSide) {
        case topSide:
            if (endNode->isVirtual == false) {
                endNodeSide = topAngle;
            }
            break;
        case rightSide:
            if (endNode->isVirtual == false) {
                endNodeSide = rightAngle;
            }
            break;
        case bottomSide:
            if (endNode->isVirtual == false) {
                endNodeSide = bottomAngle;
            }
            break;
        case leftSide:
            if (endNode->isVirtual == false) {
                endNodeSide = leftAngle;
            }
            break;
        default:
            break;
    }
    //change previous layer to current layer
    if (layer != endLayer) {
        switch (startNodeSide) {
            case topAngle:
                startNodeSide = leftAngle;
                startSeqPoint = startSeqPoint + 1;
                break;
            case rightAngle:
                startNodeSide = topAngle;
                startSeqPoint = startSeqPoint + 3;
                break;
            case bottomAngle:
                startNodeSide = rightAngle;
                startSeqPoint = startSeqPoint + 5;
                break;
            case leftAngle:
                startNodeSide = bottomAngle;
                startSeqPoint = startSeqPoint + 7;
                break;
            case topSide:
                startNodeSide = bottomSide;
                startSeqPoint = startSeqPoint + 1;
                break;
            case rightSide:
                startNodeSide = leftSide;
                startSeqPoint = startSeqPoint + 3;
                break;
            case bottomSide:
                startNodeSide = topSide;
                startSeqPoint = startSeqPoint + 5;
                break;
            case leftSide:
                startNodeSide = rightSide;
                startSeqPoint = startSeqPoint + 7;
                break;
            default:
                break;
        }
    }
    int searchPointer = 0;
    edges startNodeinMapEdges = witchSide(layer, startRow, startCol, startSeqPoint);
    edges endNodeinMapEdges = witchSide(layer, startRow, startCol, endSeqPoint);
    if (endSeqPoint > startSeqPoint) {
        //search path clockwise
        //假如startnode在下一格與現在的邊邊上 則startNode Pointer + 1
        switch (startNodeinMapEdges) {
            case topAngle:
                if (startNodeSide == rightAngle || startNodeSide == rightSide || startNodeSide == bottomAngle) {
                    ++startSeqPoint;
                }
                break;
            case rightAngle:
                if (startNodeSide == bottomAngle || startNodeSide == bottomSide || startNodeSide == leftAngle) {
                    ++startSeqPoint;
                }
                break;
            case bottomAngle:
                if (startNodeSide == leftAngle || startNodeSide == leftSide || startNodeSide == topAngle) {
                    ++startSeqPoint;
                }
                break;
            case leftAngle:
                if (startNodeSide == topAngle || startNodeSide == topSide || startNodeSide == rightAngle) {
                    ++startSeqPoint;
                }
                break;
            case topSide:
                if (startNodeSide == rightAngle || startNodeSide == rightSide || startNodeSide == bottomAngle) {
                    ++startSeqPoint;
                }
                if (witchSide(layer, startRow, startCol, startSeqPoint) == rightAngle) {
                    ++startSeqPoint;
                }
                break;
            case rightSide:
                if (startNodeSide == bottomAngle || startNodeSide == bottomSide || startNodeSide == leftAngle) {
                    ++startSeqPoint;
                }
                if (witchSide(layer, startRow, startCol, startSeqPoint) == bottomAngle) {
                    ++startSeqPoint;
                }
                break;
            case bottomSide:
                if (startNodeSide == leftAngle || startNodeSide == leftSide || startNodeSide == topAngle) {
                    ++startSeqPoint;
                }
                if (witchSide(layer, startRow, startCol, startSeqPoint) == leftAngle) {
                    ++startSeqPoint;
                }
                break;
            case leftSide:
                if (startNodeSide == topAngle || startNodeSide == topSide || startNodeSide == rightAngle) {
                    ++startSeqPoint;
                }
                if (witchSide(layer, startRow, startCol, startSeqPoint) == topAngle) {
                    ++startSeqPoint;
                }
                break;
            default:
                break;
        }
        //假如endnode在前一格與現在的邊邊上 則endNode Pointer - 1
        switch (endNodeinMapEdges) {
            case topAngle:
                if (endNodeSide == bottomAngle || endNodeSide == bottomSide || endNodeSide == leftAngle) {
                    --endSeqPoint;
                }
                break;
            case rightAngle:
                if (endNodeSide == leftAngle || endNodeSide == leftSide || endNodeSide == topAngle) {
                    --endSeqPoint;
                }
                break;
            case bottomAngle:
                if (endNodeSide == topAngle || endNodeSide == topSide || endNodeSide == rightAngle) {
                    --endSeqPoint;
                }
                break;
            case leftAngle:
                if (endNodeSide == rightAngle || endNodeSide == rightSide || endNodeSide == bottomAngle) {
                    --endSeqPoint;
                }
                break;
            case topSide:
                if (endNodeSide == leftAngle || endNodeSide == leftSide || endNodeSide == topAngle) {
                    --endSeqPoint;
                }
                if (witchSide(layer, startRow, startCol, endSeqPoint) == topAngle) {
                    --endSeqPoint;
                }
                break;
            case rightSide:
                if (endNodeSide == topAngle || endNodeSide == topSide || endNodeSide == rightAngle) {
                    --endSeqPoint;
                }
                if (witchSide(layer, startRow, startCol, endSeqPoint) == rightAngle) {
                    --endSeqPoint;
                }
                break;
            case bottomSide:
                if (endNodeSide == rightAngle || endNodeSide == rightSide || endNodeSide == bottomAngle) {
                    --endSeqPoint;
                }
                if (witchSide(layer, startRow, startCol, endSeqPoint) == bottomAngle) {
                    --endSeqPoint;
                }
                break;
            case leftSide:
                if (endNodeSide == bottomAngle || endNodeSide == bottomSide || endNodeSide == leftAngle) {
                    --endSeqPoint;
                }
                if (witchSide(layer, startRow, startCol, endSeqPoint) == leftAngle) {
                    --endSeqPoint;
                }
                break;
                
            default:
                break;
        }
        //begin to insert path
        int insertBoxRow, insertBoxCol;
        BumpNode *previousNode = startNode;
        for (searchPointer = startSeqPoint; searchPointer < endSeqPoint; ++searchPointer) {
            edges searchBoxinMapEdges = witchSide(layer, startRow, startCol, searchPointer);
            layertoMap(layer, startRow, startCol, searchPointer, &insertBoxRow, &insertBoxCol);
            if (searchBoxinMapEdges == topAngle || searchBoxinMapEdges == topSide) {
                BumpNode *newNode = new BumpNode(previousNode);
                newNode->nextNode = endNode;
                vnodeInserttoBox(insertBoxRow, insertBoxCol, rightSide, newNode, true);
                previousNode = newNode;
            } else if (searchBoxinMapEdges == rightAngle || searchBoxinMapEdges == rightSide) {
                BumpNode *newNode = new BumpNode(previousNode);
                newNode->nextNode = endNode;
                vnodeInserttoBox(insertBoxRow, insertBoxCol, bottomSide, newNode, true);
                previousNode = newNode;
            } else if (searchBoxinMapEdges == bottomAngle || searchBoxinMapEdges == bottomSide) {
                BumpNode *newNode = new BumpNode(previousNode);
                newNode->nextNode = endNode;
                vnodeInserttoBox(insertBoxRow, insertBoxCol, leftSide, newNode, true);
                previousNode = newNode;
            } else if (searchBoxinMapEdges == leftAngle || searchBoxinMapEdges == leftSide) {
                BumpNode *newNode = new BumpNode(previousNode);
                newNode->nextNode = endNode;
                vnodeInserttoBox(insertBoxRow, insertBoxCol, topSide, newNode, true);
                previousNode = newNode;
            }
        }
    } else if(endSeqPoint < startSeqPoint) {
        //search path counterclockwise
        //假如startnode在下一格與現在的邊邊上 則startNode Pointer - 1
        switch (startNodeinMapEdges) {
            case topAngle:
                if (startNodeSide == bottomAngle || startNodeSide == bottomSide || startNodeSide == leftAngle) {
                    --startSeqPoint;
                }
                break;
            case rightAngle:
                if (startNodeSide == leftAngle || startNodeSide == leftSide || startNodeSide == topAngle) {
                    --startSeqPoint;
                }
                break;
            case bottomAngle:
                if (startNodeSide == topAngle || startNodeSide == topSide || startNodeSide == rightAngle) {
                    --startSeqPoint;
                }
                break;
            case leftAngle:
                if (startNodeSide == rightAngle || startNodeSide == rightSide || startNodeSide == bottomAngle) {
                    --startSeqPoint;
                }
                break;
            case topSide:
                if (startNodeSide == leftAngle || startNodeSide == leftSide || startNodeSide == topAngle) {
                    --startSeqPoint;
                }
                if (witchSide(layer, startRow, startCol, startSeqPoint) == topAngle) {
                    --startSeqPoint;
                }
                break;
            case rightSide:
                if (startNodeSide == topAngle || startNodeSide == topSide || startNodeSide == rightAngle) {
                    --startSeqPoint;
                }
                if (witchSide(layer, startRow, startCol, startSeqPoint) == rightAngle) {
                    --startSeqPoint;
                }
                break;
            case bottomSide:
                if (startNodeSide == rightAngle || startNodeSide == rightSide || startNodeSide == bottomAngle) {
                    --startSeqPoint;
                }
                if (witchSide(layer, startRow, startCol, startSeqPoint) == bottomAngle) {
                    --startSeqPoint;
                }
                break;
            case leftSide:
                if (startNodeSide == bottomAngle || startNodeSide == bottomSide || startNodeSide == leftAngle) {
                    --startSeqPoint;
                }
                if (witchSide(layer, startRow, startCol, startSeqPoint) == leftAngle) {
                    --startSeqPoint;
                }
                break;
                
            default:
                break;
        }
        //假如endnode在前一格與現在的邊邊上 則endNode Pointer + 1
        switch (endNodeinMapEdges) {
            case topAngle:
                if (endNodeSide == rightAngle || endNodeSide == rightSide || endNodeSide == bottomAngle) {
                    ++endSeqPoint;
                }
                break;
            case rightAngle:
                if (endNodeSide == bottomAngle || endNodeSide == bottomSide || endNodeSide == leftAngle) {
                    ++endSeqPoint;
                }
                break;
            case bottomAngle:
                if (endNodeSide == leftAngle || endNodeSide == leftSide || endNodeSide == topAngle) {
                    ++endSeqPoint;
                }
                break;
            case leftAngle:
                if (endNodeSide == topAngle || endNodeSide == topSide || endNodeSide == rightAngle) {
                    ++endSeqPoint;
                }
                break;
            case topSide:
                if (endNodeSide == rightAngle || endNodeSide == rightSide || endNodeSide == bottomAngle) {
                    ++endSeqPoint;
                }
                if (witchSide(layer, startRow, startCol, startSeqPoint) == rightAngle) {
                    ++endSeqPoint;
                }
                break;
            case rightSide:
                if (endNodeSide == bottomAngle || endNodeSide == bottomSide || endNodeSide == leftAngle) {
                    ++endSeqPoint;
                }
                if (witchSide(layer, startRow, startCol, startSeqPoint) == bottomAngle) {
                    ++endSeqPoint;
                }
                break;
            case bottomSide:
                if (endNodeSide == leftAngle || endNodeSide == leftSide || endNodeSide == topAngle) {
                    ++endSeqPoint;
                }
                if (witchSide(layer, startRow, startCol, startSeqPoint) == leftAngle) {
                    ++endSeqPoint;
                }
                break;
            case leftSide:
                if (endNodeSide == topAngle || endNodeSide == topSide || endNodeSide == rightAngle) {
                    ++endSeqPoint;
                }
                if (witchSide(layer, startRow, startCol, startSeqPoint) == topAngle) {
                    ++endSeqPoint;
                }
                break;
                
            default:
                break;
        }
        //begin to insert path
        int insertBoxRow, insertBoxCol;
        BumpNode *previousNode = startNode;
        for (searchPointer = startSeqPoint; searchPointer > endSeqPoint; --searchPointer) {
            edges searchBoxinMapEdges = witchSide(layer, startRow, startCol, searchPointer);
            layertoMap(layer, startRow, startCol, searchPointer, &insertBoxRow, &insertBoxCol);
            if (searchBoxinMapEdges == rightAngle || searchBoxinMapEdges == topSide) {
                BumpNode *newNode = new BumpNode(previousNode);
                newNode->nextNode = endNode;
                vnodeInserttoBox(insertBoxRow, insertBoxCol, leftSide, newNode, true);
                previousNode = newNode;
            } else if (searchBoxinMapEdges == bottomAngle || searchBoxinMapEdges == rightSide) {
                BumpNode *newNode = new BumpNode(previousNode);
                newNode->nextNode = endNode;
                vnodeInserttoBox(insertBoxRow, insertBoxCol, topSide, newNode, true);
                previousNode = newNode;
            } else if (searchBoxinMapEdges == leftAngle || searchBoxinMapEdges == bottomSide) {
                BumpNode *newNode = new BumpNode(previousNode);
                newNode->nextNode = endNode;
                vnodeInserttoBox(insertBoxRow, insertBoxCol, rightSide, newNode, true);
                previousNode = newNode;
            } else if (searchBoxinMapEdges == topAngle || searchBoxinMapEdges == leftSide) {
                BumpNode *newNode = new BumpNode(previousNode);
                newNode->nextNode = endNode;
                vnodeInserttoBox(insertBoxRow, insertBoxCol, bottomSide, newNode, true);
                previousNode = newNode;
            }
        }
    }

}
int RoutingMap::layerPathMaping(int layer, int startRow, int startCol)
{
    int pathMapingState = 1;
    int mapingPointer = 0;
    int layerBoxNum = (layer)?layer * 8 : 1;
    int mapingBoxRow, mapingBoxCol;
    int routingFailCounter = 0;
    for (mapingPointer = 0; mapingPointer < layerBoxNum; ++mapingPointer) {
        layertoMap(layer, startRow, startCol, mapingPointer, &mapingBoxRow, &mapingBoxCol);
        edges boxSide = witchSide(layer, startRow, startCol, mapingPointer);
        box *mapingBox = &map[mapingBoxRow * mapColNum + mapingBoxCol];
        if (mapingPointer == 0) {
            mapingBox->cooridinate = 0;
        } else {
            mapingBox->cooridinate = 1;
        }
        switch (boxSide) {
            case topAngle:
                mapingBox->left_lock = true;
                mapingBox->top_lock = true;
                mapingBox->right_lock = false;
                mapingBox->buttom_lock = false;
                break;
            case rightAngle:
                mapingBox->left_lock = true;
                mapingBox->top_lock = true;
                mapingBox->right_lock = true;
                mapingBox->buttom_lock = false;
                break;
            case bottomAngle:
                mapingBox->top_lock = true;
                mapingBox->right_lock = true;
                mapingBox->buttom_lock = true;
                mapingBox->left_lock = false;
                break;
            case leftAngle:
                mapingBox->right_lock = true;
                mapingBox->buttom_lock = true;
                mapingBox->left_lock = true;
                mapingBox->top_lock = false;
                break;
            case topSide:
                mapingBox->buttom_lock = true;
                mapingBox->left_lock = true;
                mapingBox->top_lock = true;
                mapingBox->right_lock = false;
                break;
            case rightSide:
                mapingBox->left_lock = true;
                mapingBox->top_lock = true;
                mapingBox->right_lock = true;
                mapingBox->buttom_lock = false;
                break;
            case bottomSide:
                mapingBox->top_lock = true;
                mapingBox->right_lock = true;
                mapingBox->buttom_lock = true;
                mapingBox->left_lock = false;
                break;
            case leftSide:
                mapingBox->right_lock = true;
                mapingBox->buttom_lock = true;
                mapingBox->left_lock = true;
                mapingBox->top_lock = false;
                break;
            default:
                break;
        }
        if (layer == 0) {
            mapingBox->right_lock = false;
            mapingBox->buttom_lock =false;
            mapingBox->left_lock = false;
            mapingBox->top_lock = false;
        }
        bool mapingSuccess = boxnode_measurement(mapingBox);
        if (!mapingSuccess) {
            printf("%d : %d maping fail\n", mapingBoxRow, mapingBoxCol);
            refineBoxRoute(layer, startRow, startCol, mapingPointer);
            --mapingPointer;
            ++routingFailCounter;
#define maxFail 5
            if (routingFailCounter >= maxFail) {
                ++mapingPointer;
                pathMapingState = 0;
                printf("%d : %d can not be refine\n", mapingBoxRow, mapingBoxCol);
            }
        } else {
            if (mapingBox->top_lock == false) {
                for (int i = map[mapingBoxRow * mapColNum + mapingBoxCol].top.size() - 1; i > 0; --i) {
                    map[(mapingBoxRow - 1) * mapColNum + mapingBoxCol].buttom.erase(map[(mapingBoxRow - 1) * mapColNum + mapingBoxCol].buttom.begin() + i);
                }
                for (int i = 1; i < mapingBox->top.size(); ++i) {
                    map[(mapingBoxRow - 1) * mapColNum + mapingBoxCol].buttom.insert(map[(mapingBoxRow - 1) * mapColNum + mapingBoxCol].buttom.begin() + 1, mapingBox->top[i]);
                }
            }
            if (mapingBox->right_lock == false) {
                for (int i = map[mapingBoxRow * mapColNum + mapingBoxCol + 1].left.size() - 1; i > 0; --i) {
                    map[mapingBoxRow * mapColNum + mapingBoxCol + 1].left.erase(map[mapingBoxRow * mapColNum + mapingBoxCol + 1].left.begin() + i);
                }
                for (int i = 1; i < mapingBox->right.size(); ++i) {
                    map[mapingBoxRow * mapColNum + mapingBoxCol + 1].left.insert(map[mapingBoxRow * mapColNum + mapingBoxCol + 1].left.begin() + 1, mapingBox->right[i]);
                }
            }
            if (mapingBox->buttom_lock == false) {
                for (int i = map[(mapingBoxRow + 1) * mapColNum + mapingBoxCol].top.size() - 1; i > 0; --i) {
                    map[(mapingBoxRow + 1) * mapColNum + mapingBoxCol].top.erase(map[(mapingBoxRow + 1) * mapColNum + mapingBoxCol].top.begin() + i);
                }
                for (int i = 1; i < mapingBox->buttom.size(); ++i) {
                    map[(mapingBoxRow + 1) * mapColNum + mapingBoxCol].top.insert(map[(mapingBoxRow + 1) * mapColNum + mapingBoxCol].top.begin() + 1, mapingBox->buttom[i]);
                }
            }
            if (mapingBox->left_lock == false) {
                for (int i = map[mapingBoxRow * mapColNum + mapingBoxCol - 1].right.size() - 1; i > 0; --i) {
                    map[mapingBoxRow * mapColNum + mapingBoxCol - 1].right.erase(map[mapingBoxRow * mapColNum + mapingBoxCol - 1].right.begin() + i);
                }
                for (int i = 1; i < mapingBox->left.size(); ++i) {
                    map[mapingBoxRow * mapColNum + mapingBoxCol - 1].right.insert(map[mapingBoxRow * mapColNum + mapingBoxCol - 1].right.begin() + 1, mapingBox->left[i]);
                }
            }
            routingFailCounter = 0;
        }
    }
    
    return pathMapingState;
}
edges RoutingMap::directionDetect(int startNodeRow, int startNodeCol, int endNodeRow, int endNodeCol)
{
    edges direction;
    if (endNodeRow < startNodeRow && endNodeCol < startNodeCol) {
        direction = topAngle;
    } else if (endNodeRow < startNodeRow && endNodeCol == startNodeCol){
        direction = topSide;
    } else if (endNodeRow < startNodeRow && endNodeCol > startNodeCol){
        direction = rightAngle;
    } else if (endNodeRow == startNodeRow && endNodeCol < startNodeCol){
        direction = leftSide;
    } else if (endNodeRow == startNodeRow && endNodeCol == startNodeCol){
        direction = center;
    } else if (endNodeRow == startNodeRow && endNodeCol > startNodeCol) {
        direction = rightSide;
    } else if (endNodeRow > startNodeRow && endNodeCol < startNodeCol) {
        direction = leftAngle;
    } else if (endNodeRow > startNodeRow && endNodeCol == startNodeCol) {
        direction = bottomSide;
    } else if (endNodeRow > startNodeRow && endNodeCol > startNodeCol) {
        direction = bottomAngle;
    }
    return direction;
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
            } else {
                vnodeInserttoBox(toRow, toCol, topSide, node, false);
            }
            break;
        case rightSide:
            if (seqLeft) {
                vnodeInserttoBox(toRow, toCol, rightSide, node, true);
            } else {
                vnodeInserttoBox(toRow, toCol, rightSide, node, false);
            }
            break;
        case bottomSide:
            if (seqLeft) {
                vnodeInserttoBox(toRow, toCol, bottomSide, node, true);
            } else {
                vnodeInserttoBox(toRow, toCol, bottomSide, node, false);
            }
            break;
        case leftSide:
            if (seqLeft) {
                vnodeInserttoBox(toRow, toCol, leftSide, node, true);
            } else {
                vnodeInserttoBox(toRow, toCol, leftSide, node, false);
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
                if (map[row * mapColNum + col].top[0]->lcsType == UnDirectRoute) {
                    if (map[row * mapColNum + col].left.size() > map[row * mapColNum + col].top.size() + 1) {
                        layertoMap(layer, startRowNum, startColNum, pointer, &nextRow, &nextCol);
                        moveNode(row, col, leftSide, (int)(map[row * mapColNum + col].left.size()-1), nextRow, nextCol, topSide, true);
                    } else if(map[row * mapColNum + col].left.size() + 1 < map[row * mapColNum + col].top.size()) {
                        layertoMap(layer, startRowNum, startColNum, pointer, &nextRow, &nextCol);
                        moveNode(row, col, topSide, 1, nextRow, nextCol, leftSide, false);
                    }
                    break;
                }
                if (map[row * mapColNum + col].right[0]->lcsType == UnDirectRoute) {
                    layertoMap(layer, startRowNum, startColNum, pointer + 1, &nextRow, &nextCol);
                    for (int i = 1; i < map[row * mapColNum + col].right.size(); ++i) {
                        if (map[row * mapColNum + col].right[i]->wireId == map[row * mapColNum + col].top.back()->wireId) {
                            eraseVnode(row, col, rightSide, i);
                        } else {
                            BumpNode *node = new BumpNode(map[row * mapColNum + col].top.back()->id, map[row * mapColNum + col].top.back()->wireId, map[row * mapColNum + col].top.back()->lcsType, true);
                            vnodeInserttoBox(row, col, rightSide, node, false);
                        }
                    }
                    moveNode(row, col, topSide, (int)(map[row * mapColNum + col].top.size()-1), nextRow, nextCol, topSide, true);
                    break;
                }
            }
            else if(pointer == 8 * layer) {
                if (map[row * mapColNum + col].top[0]->lcsType == UnDirectRoute) {
                    if (map[row * mapColNum + col].left.size() > map[row * mapColNum + col].top.size() + 1) {
                        layertoMap(layer, startRowNum, startColNum, pointer, &nextRow, &nextCol);
                        moveNode(row, col, leftSide, (int)(map[row * mapColNum + col].left.end() - map[row * mapColNum + col].left.begin()), nextRow, nextCol, topSide, true);
                    } else if(map[row * mapColNum + col].left.size() + 1 < map[row * mapColNum + col].top.size()) {
                        layertoMap(layer, startRowNum, startColNum, pointer, &nextRow, &nextCol);
                        moveNode(row, col, topSide, 1, nextRow, nextCol, leftSide, false);
                    }
                    break;
                }
                if (map[row * mapColNum + col].left[0]->lcsType == UnDirectRoute) {
                    layertoMap(layer, startRowNum, startColNum, pointer - 1, &nextRow, &nextCol);
                    for (int i = 1; i < map[row * mapColNum + col].buttom.size(); ++i) {
                        if (map[row * mapColNum + col].buttom[i]->wireId == map[row * mapColNum + col].left[1]->wireId) {
                            eraseVnode(row, col, bottomSide, i);
                        } else {
                            BumpNode *node = new BumpNode(map[row * mapColNum + col].left[1]->id, map[row * mapColNum + col].left[1]->wireId, map[row * mapColNum + col].left[1]->lcsType, true);
                            vnodeInserttoBox(row, col, bottomSide, node, false);
                        }
                    }
                    moveNode(row, col, leftSide, 1, nextRow, nextCol, leftSide, false);
                    break;
                }
            }
            break;
        case topSide:
            if (map[row * mapColNum + col].right[0]->lcsType == UnDirectRoute) {
                layertoMap(layer, startRowNum, startColNum, pointer + 1, &nextRow, &nextCol);
                for (int i = 1; i < map[row * mapColNum + col].right.size(); ++i) {
                    if (map[row * mapColNum + col].right[i]->wireId == map[row * mapColNum + col].top.back()->wireId) {
                        eraseVnode(row, col, rightSide, i);
                    } else {
                        BumpNode *node = new BumpNode(map[row * mapColNum + col].top.back()->id, map[row * mapColNum + col].top.back()->wireId, map[row * mapColNum + col].top.back()->lcsType, true);
                        vnodeInserttoBox(row, col, rightSide, node, false);
                    }
                }
                moveNode(row, col, topSide, (int)(map[row * mapColNum + col].top.size() - 1), nextRow, nextCol, topSide, true);
                break;
            }
            break;
        case rightAngle:
            if (map[row * mapColNum + col].right[0]->lcsType == UnDirectRoute) {
                layertoMap(layer, startRowNum, startColNum, pointer, &nextRow, &nextCol);
                moveNode(row, col, topSide, (int)(map[row * mapColNum + col].top.size()-1), nextRow, nextCol, rightSide, true);
                break;
            }
            if (map[row * mapColNum + col].buttom[0]->lcsType == UnDirectRoute) {
                layertoMap(layer, startRowNum, startColNum, pointer + 1, &nextRow, &nextCol);
                for (int i = 1; i < map[row * mapColNum + col].buttom.size(); ++i) {
                    if (map[row * mapColNum + col].buttom[i]->wireId == map[row * mapColNum + col].right.back()->wireId) {
                        eraseVnode(row, col, bottomSide, i);
                    } else {
                        BumpNode *node = new BumpNode(map[row * mapColNum + col].right.back()->id, map[row * mapColNum + col].right.back()->wireId, map[row * mapColNum + col].right.back()->lcsType, true);
                        vnodeInserttoBox(row, col, bottomSide, node, false);
                    }
                }
                moveNode(row, col, rightSide, (int)(map[row * mapColNum + col].right.size()-1), nextRow, nextCol, rightSide, true);
            }
            break;
        case rightSide:
            if (map[row * mapColNum + col].buttom[0]->lcsType == UnDirectRoute) {
                layertoMap(layer, startRowNum, startColNum, pointer + 1, &nextRow, &nextCol);
                for (int i = 1; i < map[row * mapColNum + col].buttom.size(); ++i) {
                    if (map[row * mapColNum + col].buttom[i]->wireId == map[row * mapColNum + col].right.back()->wireId) {
                        eraseVnode(row, col, bottomSide, i);
                    } else {
                        BumpNode *node = new BumpNode(map[row * mapColNum + col].right.back()->id, map[row * mapColNum + col].right.back()->wireId, map[row * mapColNum + col].right.back()->lcsType, true);
                        vnodeInserttoBox(row, col, bottomSide, node, false);
                    }
                }
                moveNode(row, col, rightSide, (int)(map[row * mapColNum + col].right.size() - 1), nextRow, nextCol, rightSide, true);
                break;
            }
            break;
        case bottomAngle:
            if (map[row * mapColNum + col].buttom[0]->lcsType == UnDirectRoute) {
                layertoMap(layer, startRowNum, startColNum, pointer, &nextRow, &nextCol);
                moveNode(row, col, rightSide, (int)(map[row * mapColNum + col].right.size() - 1), nextRow, nextCol, bottomSide, true);
                break;
            }
            if (map[row * mapColNum + col].left[0]->lcsType == UnDirectRoute) {
                layertoMap(layer, startRowNum, startColNum, pointer + 1, &nextRow, &nextCol);
                for (int i = 1; i < map[row * mapColNum + col].left.size(); ++i) {
                    if (map[row * mapColNum + col].left[i]->wireId == map[row * mapColNum + col].buttom.back()->wireId) {
                        eraseVnode(row, col, leftSide, i);
                    } else {
                        BumpNode *node = new BumpNode(map[row * mapColNum + col].buttom.back()->id, map[row * mapColNum + col].buttom.back()->wireId, map[row * mapColNum + col].buttom.back()->lcsType, true);
                        vnodeInserttoBox(row, col, leftSide, node, false);
                    }
                }
                moveNode(row, col, bottomSide, (int)(map[row * mapColNum + col].buttom.size() - 1), nextRow, nextCol, bottomSide, true);
                break;
            }
            break;
        case bottomSide:
            if (map[row * mapColNum + col].left[0]->lcsType == UnDirectRoute) {
                layertoMap(layer, startRowNum, startColNum, pointer + 1, &nextRow, &nextCol);
                for (int i = 1; i < map[row * mapColNum + col].left.size(); ++i) {
                    if (map[row * mapColNum + col].left[i]->wireId == map[row * mapColNum + col].buttom.back()->wireId) {
                        eraseVnode(row, col, leftSide, i);
                    } else {
                        BumpNode *node = new BumpNode(map[row * mapColNum + col].buttom.back()->id, map[row * mapColNum + col].buttom.back()->wireId, map[row * mapColNum + col].buttom.back()->lcsType, true);
                        vnodeInserttoBox(row, col, leftSide, node, false);
                    }
                }
                moveNode(row, col, bottomSide, (int)(map[row * mapColNum + col].buttom.size() - 1), nextRow, nextCol, bottomSide, true);
                break;
            }
            break;
        case leftAngle:
            if (map[row * mapColNum + col].left[0]->lcsType == UnDirectRoute) {
                layertoMap(layer, startRowNum, startColNum, pointer, &nextRow, &nextCol);
                moveNode(row, col, bottomSide, (int)(map[row * mapColNum + col].buttom.size() - 1), nextRow, nextCol, leftSide, true);
                break;
            }
            if (map[row * mapColNum + col].top[0]->lcsType == UnDirectRoute) {
                layertoMap(layer, startRowNum, startColNum, pointer + 1, &nextRow, &nextCol);
                for (int i = 1; i < map[row * mapColNum + col].top.size(); ++i) {
                    if (map[row * mapColNum + col].top[i]->wireId == map[row * mapColNum + col].left.back()->wireId) {
                        eraseVnode(row, col, topSide, i);
                    } else {
                        BumpNode *node = new BumpNode(map[row * mapColNum + col].left.back()->id, map[row * mapColNum + col].left.back()->wireId, map[row * mapColNum + col].left.back()->lcsType, true);
                        vnodeInserttoBox(row, col, topSide, node, false);
                    }
                }
                moveNode(row, col, leftSide, (int)(map[row * mapColNum + col].left.size() - 1), nextRow, nextCol, leftSide, true);
                break;
            }
            break;
        case leftSide:
            if (map[row * mapColNum + col].top[0]->lcsType == UnDirectRoute) {
                layertoMap(layer, startRowNum, startColNum, pointer + 1, &nextRow, &nextCol);
                for (int i = 1; i < map[row * mapColNum + col].top.size(); ++i) {
                    if (map[row * mapColNum + col].top[i]->wireId == map[row * mapColNum + col].left.back()->wireId) {
                        eraseVnode(row, col, topSide, i);
                    } else {
                        BumpNode *node = new BumpNode(map[row * mapColNum + col].left.back()->id, map[row * mapColNum + col].left.back()->wireId, map[row * mapColNum + col].left.back()->lcsType, true);
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
    printf("%d : %d refine \n",row, col);
}


