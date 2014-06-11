//
//  MPSC.cpp
//  MPSC
//
//  Created by 李勁璋 on 2014/5/16.
//  Copyright (c) 2014年 Li,Ching-Chang. All rights reserved.
//

#include "MPSC.h"

/*
int** ary = new int*[sizeX];
for(int i = 0; i < sizeX; ++i)
    ary[i] = new int[sizeY];

*/
MIS::MIS(int rowSize, int columnSize)
{
    tRowSize = rowSize;
    tColSize = columnSize;
//    table = new chord*[rowSize];
//    for (int i = 0; i < rowSize; ++i)
//    {
//        table[i] = new chord[columnSize];
//    }
    
    table = new chord[tRowSize * tColSize];
}
MIS::~MIS()
{
//    for (int i = 0; i < tRowSize; ++i)
//    {
//        delete [] table[i];
//    }
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
    buildCircle();
    buildMis();
    refreshSequence();
}
// compute the possible routing path
void MPSC::buildCircle()
{
    // build virtual nodes of undirected route nodes and insert those to current sequence
    for (int i = 0; i < currentSequence->size(); ++i)
    {
        if ((*currentSequence)[i]->wireId) {
            if ((*currentSequence)[i]->lcsType == UnDirectRoute)
            {
                int tmp;
                if ((*currentSequence)[0]->wireId) {
                    tmp = *(*currentSequence)[0]->wireId;
                } else {
                    int k = 0;
                    while (k < currentSequence->size() && !(*currentSequence)[k]->wireId) {
                        ++k;
                    }
                    if (k < currentSequence->size()) {
                        tmp = *(*currentSequence)[k]->wireId;
                    } else {
                        tmp = 2147483647;
                    }
                }
                if (*(*currentSequence)[i]->wireId < tmp)
                {
                    BumpNode *node = new BumpNode((*currentSequence)[i]->id, (*currentSequence)[i]->wireId,(*currentSequence)[i]->lcsType,true);
                    (*currentSequence)[i]->nextNode = node;
                    currentSequence->insert(currentSequence->begin(), node);
                    ++i;
                }
                for (int j = 0; j < currentSequence->size() - 1; ++j)
                {
                    int tmp0, tmp1, tmp2;
                    if ((*currentSequence)[i]->wireId) {
                        tmp0 = *(*currentSequence)[i]->wireId;
                    } else {
                        tmp0 = -5;
                    }
                    if ((*currentSequence)[j]->wireId) {
                        tmp1 = *(*currentSequence)[j]->wireId;
                    } else {
                        int k = j;
                        while (k >=0 && !(*currentSequence)[k]->wireId) {
                            --k;
                        }
                        if (k >= 0) {
                            tmp1 = *(*currentSequence)[k]->wireId;
                        } else {
                            tmp1 = -1;
                        }
                    }
                    if ((*currentSequence)[j+1]->wireId) {
                        tmp2 = *(*currentSequence)[j+1]->wireId;
                    } else {
                        int k = j+1;
                        while (k < currentSequence->size() && !(*currentSequence)[k]->wireId) {
                            ++k;
                        }
                        if (k < currentSequence->size()) {
                            tmp2 = *(*currentSequence)[k]->wireId;
                        } else {
                            tmp2 = 2147483647;
                        }
                    }
                    if (tmp0 > tmp1 && tmp0 < tmp2)
                    {
                        BumpNode *node = new BumpNode((*currentSequence)[i]->id, (*currentSequence)[i]->wireId,(*currentSequence)[i]->lcsType,true);
                        (*currentSequence)[i]->nextNode = node;
                        currentSequence->insert(currentSequence->begin() + j + 1, node);
                        ++j;
                        if (i >= j) {
                            ++i;
                        }

                    }
                }
                int tmp3 = 0;
                if ((*currentSequence).back()->wireId) {
                    tmp3 = *(*currentSequence).back()->wireId;
                } else {
                    int k = currentSequence->size() - 1;
                    while (k >=0 && !(*currentSequence)[k]->wireId) {
                        --k;
                    }
                    if (k >= 0) {
                        tmp3 = *(*currentSequence)[k]->wireId;
                    } else {
                        tmp3 = -1;
                    }
                }
                if ((*currentSequence)[i]->wireId && *(*currentSequence)[i]->wireId > tmp3)
                {
                    BumpNode *node = new BumpNode((*currentSequence)[i]->id, (*currentSequence)[i]->wireId,(*currentSequence)[i]->lcsType,true);
                    (*currentSequence)[i]->nextNode = node;
                    currentSequence->insert(currentSequence->end(), node);
                }
            }
        }
    }
    // build virtual nodes of previous nodes and insert those to current sequence
    for (int j = 0; j < previousSequence->size(); ++j)
    {
        int tmp;
        if ((*currentSequence)[0]->wireId) {
            tmp = *(*currentSequence)[0]->wireId;
        } else {
            int k = 0;
            while (k < currentSequence->size() && !(*currentSequence)[k]->wireId) {
                ++k;
            }
            if (k < currentSequence->size()) {
                tmp = *(*currentSequence)[k]->wireId;
            } else {
                tmp = 2147483647;
            }
        }
        if ((*previousSequence)[j]->wireId) {
            if (*(*previousSequence)[j]->wireId < tmp)
            {
                BumpNode *node = new BumpNode((*previousSequence)[j]->id, (*previousSequence)[j]->wireId,(*previousSequence)[j]->lcsType,true);
                (*previousSequence)[j]->nextNode = node;
                currentSequence->insert(currentSequence->begin(), node);
            }
        }
    }
    for (int i = 0; i < currentSequence->size() -1 ; ++i)
    {
        if ((*currentSequence)[i]->wireId) {
            for (int j = 0; j < previousSequence->size(); ++j)
            {
                if ((*previousSequence)[j]->wireId) {
                    int tmp1, tmp2;
                    if ((*currentSequence)[i]->wireId) {
                        tmp1 = *(*currentSequence)[i]->wireId;
                    } else {
                        int k = i;
                        while (k >=0 && !(*currentSequence)[k]->wireId) {
                            --k;
                        }
                        if (k >= 0) {
                            tmp1 = *(*currentSequence)[k]->wireId;
                        } else {
                            tmp1 = -1;
                        }
                    }
                    if ((*currentSequence)[i+1]->wireId) {
                        tmp2 = *(*currentSequence)[i+1]->wireId;
                    } else {
                        int k = i + 1;
                        while (k < currentSequence->size() && !(*currentSequence)[k]->wireId) {
                            ++k;
                        }
                        if (k < currentSequence->size()) {
                            tmp2 = *(*currentSequence)[k]->wireId;
                        } else {
                            tmp2 = 2147483647;
                        }
                    }
                    if (*(*previousSequence)[j]->wireId > tmp1 && *(*previousSequence)[j]->wireId < tmp2)
                    {
                        BumpNode *node = new BumpNode((*previousSequence)[j]->id, (*previousSequence)[j]->wireId,(*previousSequence)[j]->lcsType,true);
                        (*previousSequence)[j]->nextNode = node;
                        currentSequence->insert(currentSequence->begin() + i + 1, node);
                        ++i;

                    }
                }
            }
        }
    }
    for (int j = 0; j < previousSequence->size(); ++j)
    {
        int tmp3 = 0;
        if ((*currentSequence).back()->wireId) {
            tmp3 = *(*currentSequence).back()->wireId;
        } else {
            int k = currentSequence->size() - 1;
            while (k >=0 && !(*currentSequence)[k]->wireId) {
                --k;
            }
            if (k >= 0) {
                tmp3 = *(*currentSequence)[k]->wireId;
            } else {
                tmp3 = -1;
            }
        }
        if ((*previousSequence)[j]->wireId) {
            if (*(*previousSequence)[j]->wireId > tmp3)
            {
                BumpNode *node = new BumpNode((*previousSequence)[j]->id, (*previousSequence)[j]->wireId,(*previousSequence)[j]->lcsType,true);
                (*previousSequence)[j]->nextNode = node;
                currentSequence->push_back(node);
            }
        }
    }
    //build chords
    for (int i = 0; i < currentSequence->size(); ++i) {
        for (int j = i + 1; j < currentSequence->size(); ++j) {
            if ((*currentSequence)[i]->wireId && (*currentSequence)[j]->wireId) {
                if (*(*currentSequence)[i]->wireId == *(*currentSequence)[j]->wireId) {
                    chord x;
                    x.node1 = i;
                    x.node2 = j;
                    x.left = NULL;
                    x.right = NULL;
                    x.total = 1;
                    circle.push_back(x);
                }
            }
        }
        for (int j = previousSequence->size() - 1; j >= 0; --j) {
            if ((*currentSequence)[i]->wireId && (*previousSequence)[j]->wireId) {
                if (*(*currentSequence)[i]->wireId == *(*previousSequence)[j]->wireId) {
                    chord x;
                    x.node1 = i;
                    x.node2 = (*previousSequence).size() - j + (*currentSequence).size() - 1;
                    x.left = NULL;
                    x.right = NULL;
                    x.total = 1;
                    circle.push_back(x);
                }
            }
        }
    }
}
void MPSC::buildMis()
{
    mis = new MIS(previousSequence->size()+currentSequence->size(), previousSequence->size()+currentSequence->size());

    vector<chord> tmpChords;
    for (int j = 0; j < previousSequence->size() + currentSequence->size(); ++j) {
        for (int i = 0; i < currentSequence->size(); ++i) {
            if (circle[i].node2 == j) {
                tmpChords.push_back(circle[i]);
            }
            if (circle[i].node1 >= j) {
                break;
            }
        }
        for (int i = 0; i < j; ++i) {
            for (int k = 0; k < tmpChords.size(); ++k) {
                if (tmpChords[k].node1 >= i && tmpChords[k].node1 <= j) {
                    if ((mis->chordsinMIS(i, tmpChords[k].node1 - 1))->total + 1 + (mis->chordsinMIS(tmpChords[k].node1 + 1, j - 1))->total > (mis->chordsinMIS(i, j - 1))->total) {
                        mis->putChordsInMIS(i, j, mis->chordsinMIS(i, tmpChords[k].node1 - 1), mis->chordsinMIS(tmpChords[k].node1 + 1, j - 1), &tmpChords[k]);
                    } else {
                        mis->putChordsInMIS(i, j, mis->chordsinMIS(i, j - 1), NULL, NULL);
                    }
                }
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


