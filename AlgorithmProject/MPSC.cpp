//
//  MPSC.cpp
//  MPSC
//
//  Created by 李勁璋 on 2014/5/16.
//  Copyright (c) 2014年 Li,Ching-Chang. All rights reserved.
//

#include "MPSC.h"

MIS::MIS(int rowSize, int columnSize)
{
    tRowSize = rowSize;
    tColSize = columnSize;
    table = new chord[tRowSize * tColSize];
    for (int i = 0; i < tRowSize * tColSize; ++i) {
        table[i].left = NULL;
        table[i].right = NULL;
        table[i].total = 0;

    }
}
MIS::~MIS()
{
    delete [] table;
    printf("mis delloc\n");

}
chord *MIS::chordsinMIS(int row, int column)
{
    return &table[row * tRowSize + column];
}
void MIS::putChordsInMIS(int row, int column, chord *leftChord, chord *rightChord, chord* newChord)
{
    if (newChord) {
        table[row * tRowSize + column].node1 = newChord->node1;
        table[row * tRowSize + column].node2 = newChord->node2;
        table[row * tRowSize + column].left = leftChord;
        table[row * tRowSize + column].right = rightChord;
        table[row * tRowSize + column].total = leftChord->total + rightChord->total + 1;
    } else {
        table[row * tRowSize + column].total = leftChord->total;
        table[row * tRowSize + column].left = leftChord;
    }
}
void printa(chord x)
{
    if (x.left) {
        chord left = *x.left;
        printa(left);
    }
    if (x.right) {
        chord right = *x.right;
        printa(right);
    }
    if (x.node1 != x.node2) {
        printf("%d -- %d\n", x.node1, x.node2);
    }
    
}
void MIS::printMaxSeq()
{
    int maxPos = 0;
    for (int i = 0; i < tRowSize * tColSize; ++i) {
        if (table[i].total > table[maxPos].total) {
            maxPos = i;
        }
    }
    printa(table[maxPos]);
}

void traceChordTree(chord x, vector<chord>*maxSeq)
{
    if (x.left) {
        chord left = *x.left;
        traceChordTree(left, maxSeq);
    }
    if (x.right) {
        chord right = *x.right;
        traceChordTree(right, maxSeq);
    }
    if (x.node1 != x.node2) {
        maxSeq->push_back(x);
    }
}

void MIS::maxSeq(vector<chord>*outSeq)
{
    int maxPos = 0;
    for (int i = 0; i < tRowSize * tColSize; ++i) {
        if (table[i].total > table[maxPos].total) {
            maxPos = i;
        }
    }
    traceChordTree(table[maxPos], outSeq);
}



MPSC::MPSC(vector<BumpNode *>*previousSeq, vector<BumpNode *>*currentLCS)
{
    previousSequence = previousSeq;
    currentSequence = currentLCS;
}


MPSC::~MPSC()
{
    previousSequence = NULL;
    currentSequence = NULL;
    printf("mpsc delloc\n");
    delete mis;
}

void MPSC::compute()
{
    computePath();
    buildCircle();
    buildMis();
    refreshSequence();
}
// compute the possible routing path
void MPSC::computePath()
{
    int leftPointer, rightPointer;
    int leftBound, rightBound;
    int currentPointer, currentPointerWireID;
    //insert the left and right limit
    int virLeftLimit , virRightLimit;
    virLeftLimit = -2147483647;
    virRightLimit = 2147483647;
    BumpNode *virLeftLimitNode = new BumpNode(0, &virLeftLimit, DirectRoute, true);
    BumpNode *virRightLimitNode = new BumpNode(0, &virRightLimit, DirectRoute, true);
    currentSequence->insert(currentSequence->begin(), virLeftLimitNode);
    currentSequence->push_back(virRightLimitNode);
    
    //find previous layer to current layer path
    for (currentPointer = 0; currentPointer < previousSequence->size(); ++currentPointer) {
        if ((*previousSequence)[currentPointer]->lcsType == DirectRoute) {
            currentPointerWireID = *(*previousSequence)[currentPointer]->wireId;
            for (leftPointer = 0; leftPointer < currentSequence->size(); ++leftPointer) {
                //search left bound and right bound
                while (leftPointer < currentSequence->size() && (*currentSequence)[leftPointer]->lcsType == UnDirectRoute) {
                    ++leftPointer;
                }
                leftBound = *(*currentSequence)[leftPointer]->wireId;
                rightPointer = leftPointer;
                ++rightPointer;
                while (rightPointer < currentSequence->size() && (*currentSequence)[rightPointer]->lcsType == UnDirectRoute) {
                    ++rightPointer;
                }
                rightBound = *(*currentSequence)[rightPointer]->wireId;
                //insert node to the right of left bound
                if (currentPointerWireID > leftBound && currentPointerWireID < rightBound) {
                    BumpNode *newVirNode = new BumpNode((*previousSequence)[currentPointer]);
                    newVirNode->lcsType = DirectRoute;
                    if (leftPointer == currentSequence->size() - 1) {
                        currentSequence->push_back(newVirNode);
                    } else {
                        currentSequence->insert(currentSequence->begin() + leftPointer + 1, newVirNode);
                    }
                    break;
                }
            }
        }
    }
    
    //find current layer to current layer
    for (currentPointer = 1; currentPointer < currentSequence->size() - 1; ++currentPointer) {
        if ((*currentSequence)[currentPointer]->lcsType == UnDirectRoute) {
            currentPointerWireID = *(*currentSequence)[currentPointer]->wireId;
            for (leftPointer = 0; leftPointer < currentSequence->size() - 1; ++leftPointer) {
                //search left bound and right bound
                while (leftPointer < currentSequence->size() - 2 && (*currentSequence)[leftPointer]->lcsType == UnDirectRoute) {
                    ++leftPointer;
                }
                leftBound = *(*currentSequence)[leftPointer]->wireId;
                rightPointer = leftPointer;
                ++rightPointer;
                while (rightPointer < currentSequence->size() - 1 && (*currentSequence)[rightPointer]->lcsType == UnDirectRoute) {
                    ++rightPointer;
                }
                rightBound = *(*currentSequence)[rightPointer]->wireId;
                //insert node to the right of left bound
                if (currentPointerWireID > leftBound && currentPointerWireID < rightBound) {
                    BumpNode *newVirNode = new BumpNode((*currentSequence)[currentPointer]);
                    newVirNode->lcsType = DirectRoute;
                    if (leftPointer == currentSequence->size() - 1) {
                        currentSequence->push_back(newVirNode);
                    } else {
                        currentSequence->insert(currentSequence->begin() + leftPointer + 1, newVirNode);
                        if (leftPointer < currentPointer) {
                            ++currentPointer;
                        }
                    }
                    break;
                }
            }
        }
    }

    //delet the virtual limit node
    currentSequence->erase(currentSequence->begin() + currentSequence->size() - 1);
    currentSequence->erase(currentSequence->begin());

}
// search the direct routing node
vector<BumpNode*> MPSC::serchDirectRout(vector<BumpNode*>*nodeSequence)
{
    vector<BumpNode*> output;
    for (int i = 0; i < nodeSequence->size(); ++i) {
        if ((*nodeSequence)[i]->lcsType == DirectRoute) {
            output.push_back((*nodeSequence)[i]);
        }
    }
    return output;
}
void MPSC::buildCircle()
{
    int leftPointer, rightPointer;
    BumpNode *leftPointNode, *rightPointNode;
    bool isTrace[currentSequence->size()];
    for (int i = 0; i < currentSequence->size(); ++i) {
        isTrace[i] = false;
    }
    for (leftPointer = 0; leftPointer < currentSequence->size(); ++leftPointer) {
        leftPointNode = (*currentSequence)[leftPointer];
        if ((!leftPointNode->isVirtual && leftPointNode->lcsType != UnDirectRoute) || isTrace[leftPointer] == true) {
            continue;
        }
        for (rightPointer = leftPointer + 1; rightPointer < currentSequence->size(); ++rightPointer) {
            rightPointNode = (*currentSequence)[rightPointer];
            if (leftPointNode->wireId == rightPointNode->wireId) {
                chord newChord;
                newChord.node1 = leftPointer;
                newChord.node2 = rightPointer;
                newChord.left = NULL;
                newChord.right = NULL;
                newChord.total = 1;
                circle.push_back(newChord);
                isTrace[leftPointer] = true;
            }
        }
        for (rightPointer = previousSequence->size() - 1; rightPointer >=0; --rightPointer) {
            rightPointNode = (*previousSequence)[rightPointer];
            if (rightPointNode->lcsType == UnDirectRoute) {
                continue;
            }
            if (leftPointNode->wireId == rightPointNode->wireId) {
                chord newChord;
                newChord.node1 = leftPointer;
                newChord.node2 = previousSequence->size() - 1 - rightPointer + currentSequence->size();
                newChord.left = NULL;
                newChord.right = NULL;
                newChord.total = 1;
                circle.push_back(newChord);
                isTrace[leftPointer] = true;
            }
        }
    }
}

void MPSC::buildMis()
{
    mis = new MIS(previousSequence->size()+currentSequence->size(), previousSequence->size()+currentSequence->size());

    vector<chord> tmpChords;
    for (int j = 0; j < previousSequence->size() + currentSequence->size(); ++j) {
        for (int i = 0; i < circle.size(); ++i) {
            if (circle[i].node2 == j) {
                tmpChords.push_back(circle[i]);
            }
        }
        for (int i = 0; i < j; ++i) {
            if (tmpChords.size() > 0) {
                for (int k = 0; k < tmpChords.size(); ++k) {
                    if (tmpChords[k].node1 >= i && tmpChords[k].node1 < j) {
                        if ((mis->chordsinMIS(i, tmpChords[k].node1 - 1))->total + 1 + (mis->chordsinMIS(tmpChords[k].node1 + 1, j - 1))->total > (mis->chordsinMIS(i, j - 1))->total) {
                            mis->putChordsInMIS(i, j, mis->chordsinMIS(i, tmpChords[k].node1 - 1), mis->chordsinMIS(tmpChords[k].node1 + 1, j - 1), &tmpChords[k]);
                        } else {
                            mis->putChordsInMIS(i, j, mis->chordsinMIS(i, j - 1), NULL, NULL);
                        }
                    } else {
                        mis->putChordsInMIS(i, j, mis->chordsinMIS(i, j - 1), NULL, NULL);
                    }
                }
            } else {
                mis->putChordsInMIS(i, j, mis->chordsinMIS(i, j - 1), NULL, NULL);
            }
        
        }
        tmpChords.clear();
    }
    return ;
}

void MPSC::refreshSequence()
{
    vector<chord>outSequence;
    mis->maxSeq(&outSequence);
    for (int i = 0; i < outSequence.size(); ++i) {
        if (outSequence[i].node2 < currentSequence->size()) {
            (*currentSequence)[outSequence[i].node1]->mpscType = inCircle;
            (*currentSequence)[outSequence[i].node2]->mpscType = inCircle;
        } else {
            (*currentSequence)[outSequence[i].node1]->mpscType = inCircle;
            (*previousSequence)[previousSequence->size() - (outSequence[i].node2 - currentSequence->size() + 1)]->mpscType = inCircle;
        }
    }

}


