//
//  main.cpp
//  MPCS2
//
//  Created by 李勁璋 on 2014/5/27.
//  Copyright (c) 2014年 Li,Ching-Chang. All rights reserved.
//

#include <iostream>
#include "MPSC.h"
#include "routing_map.h"
#include "readFile.h"
#include "mapping.h"
int main(int argc, const char * argv[])
{

////  test data///////////////////////////////////////////
//    int d[10];
//    for (int i= 1; i <=9 ; ++i) {
//        d[i] = i;
//    }
//      vector<BumpNode*>previousSeq, currentSeq;
//    BumpNode *node1 = new BumpNode(1, &d[1], DirectRoute, false);
//    previousSeq.push_back(node1);
//    BumpNode *node2 = new BumpNode(2, &d[4], DirectRoute, false);
//    previousSeq.push_back(node2);
//    BumpNode *node3 = new BumpNode(3, &d[5], DirectRoute, false);
//    previousSeq.push_back(node3);
//    BumpNode *node7 = new BumpNode(7, &d[7], DirectRoute, false);
//    previousSeq.push_back(node7);
// 
//    
//
//  
//    BumpNode *node8 = new BumpNode(8, nullptr, DirectRoute, false);
//    currentSeq.push_back(node8);
//
//    
//    BumpNode *node4 = new BumpNode(4, &d[3], UnDirectRoute, false);
//    currentSeq.push_back(node4);
//    BumpNode* node5 = new BumpNode(5, &d[2], DirectRoute, false);
//    currentSeq.push_back(node5);
//
//    BumpNode *node12 = new BumpNode(12, nullptr, DirectRoute, false);
//    currentSeq.push_back(node12);
//    BumpNode *node13 = new BumpNode(13, nullptr, DirectRoute, false);
//    currentSeq.push_back(node13);
//    BumpNode *node14 = new BumpNode(14, nullptr, DirectRoute, false);
//    currentSeq.push_back(node14);
//    BumpNode *node15 = new BumpNode(15, nullptr, DirectRoute, false);
//    currentSeq.push_back(node15);
//    BumpNode *node16 = new BumpNode(16, nullptr, DirectRoute, false);
//    currentSeq.push_back(node16);
//    
//    BumpNode* node6 = new BumpNode(6, &d[9], DirectRoute, false);
//    currentSeq.push_back(node6);
//    BumpNode *node11 = new BumpNode(11, nullptr, DirectRoute, false);
//    currentSeq.push_back(node11);
//    BumpNode *node10 = new BumpNode(10, nullptr, DirectRoute, false);
//    currentSeq.push_back(node10);
//    
//    
//    BumpNode *node9 = new BumpNode(9, nullptr, DirectRoute, false);
//    currentSeq.push_back(node9);
//
//
//    
//    node4->relativeX = 1;
//    node4->relativeY = 0;
//    node5->relativeX = 2;
//    node5->relativeY = 0;
//    node6->relativeX = 1;
//    node6->relativeY = 3;
//    node1->relativeX = 1;
//    node1->relativeY = 1;
//    node2->relativeX = 2;
//    node2->relativeY = 1;
//    node3->relativeX = 2;
//    node3->relativeY = 2;
//    
//      RoutingMap *routingMap = new RoutingMap(4,4);
//
//    routingMap->nodeInserttoMap(1, 1, node8);
//    routingMap->nodeInserttoMap(1, 2, node4);
//    routingMap->nodeInserttoMap(1, 3, node5);
//    routingMap->nodeInserttoMap(1, 4, node12);
//    routingMap->nodeInserttoMap(2, 1, node9);
//    routingMap->nodeInserttoMap(2, 2, node1);
//    routingMap->nodeInserttoMap(2, 3, node2);
//    routingMap->nodeInserttoMap(2, 4, node13);
//    routingMap->nodeInserttoMap(3, 1, node10);
//    routingMap->nodeInserttoMap(3, 2, node7);
//    routingMap->nodeInserttoMap(3, 3, node3);
//    routingMap->nodeInserttoMap(3, 4, node14);
//    routingMap->nodeInserttoMap(4, 1, node11);
//    routingMap->nodeInserttoMap(4, 2, node6);
//    routingMap->nodeInserttoMap(4, 3, node16);
//    routingMap->nodeInserttoMap(4, 4, node15);

//read file
    vector<BumpNode*>previousSeq;
    ReadFile *readFile = new ReadFile();
    RoutingMap *routingMap = new RoutingMap(2*(readFile->numBvec-1)+1,2*(readFile->numBvec-1)+1);
    int k = 0;
    while (k < readFile->numBvec) {
        readFile->LCS(&readFile->driver, &readFile->bvec[k], readFile->driver.size(), readFile->bvec[k].size());
        vector<BumpNode*>currentSeq;
        for (int i = 0; i < readFile->bvec[k].size(); ++i) {
            currentSeq.push_back(&readFile->bvec[k][i]);
        }
        printf("LCS Sequence result : ");
        for (int i = 0; i < currentSeq.size(); ++i) {
            if (currentSeq[i]->wireId) {
                if (currentSeq[i]->isVirtual) {
                    printf("%d' ", *currentSeq[i]->wireId);
                } else {
                    printf("%d ", *currentSeq[i]->wireId);
                }
            } else {
                printf("x ");
            }
        }
        printf("\n");
        MPSC *mpsc = new MPSC(&previousSeq, &currentSeq);
        mpsc->compute();
        delete mpsc;
        printf("MPSC Sequence result : ");
        for (int i = 0; i < currentSeq.size(); ++i) {
            if (currentSeq[i]->wireId) {
                if (currentSeq[i]->isVirtual) {
                    printf("%d' ", *currentSeq[i]->wireId);
                } else {
                    printf("%d ", *currentSeq[i]->wireId);
                }
            } else {
                printf("x ");
            }
        }
        printf("\n");
        
        routingMap->initMapinLayer(k , readFile->numBvec - k - 1, readFile->numBvec - k - 1, currentSeq);
        printf("before mapping\n");
        routingMap->printBoxinLayer(k, readFile->numBvec - k - 1, readFile->numBvec - k - 1);

        routingMap->ringMaping(k, readFile->numBvec - k - 1, readFile->numBvec - k - 1);
        printf("after mapping\n");

        routingMap->printBoxinLayer(k, readFile->numBvec - k - 1, readFile->numBvec - k - 1);
        
     //   routingMap->printBox(1, 1);
     //   routingMap->printBox(1, 2);
        //routingMap->printBox(1, 3);
        // routingMap->printBox(0, 3);
     //   routingMap->printBox(2, 1);
     //   routingMap->printBox(2, 2);
        //routingMap->printBox(2, 3);
        // routingMap->printBox(1, 3);
       // routingMap->printBox(3, 1);
       // routingMap->printBox(3, 2);
        //routingMap->printBox(3, 3);
        
        //       mapping *maping = new mapping(routingMap->mapRowNum, routingMap->mapColNum, readFile->w, readFile->s);
        //       maping->mapping_incircle(routingMap->map);
        //  maping->mapping_outcircle(routingMap->map);
        //      maping->route_output(routingMap->map);
        
        previousSeq = currentSeq;

        k++;
    }
    
////  algorithm /////////////////////////////////////////
//    MPSC *mpsc = new MPSC(&previousSeq, &currentSeq);
//    mpsc->compute();
//    delete mpsc;
//    routingMap->initMapinLayer(0, 2, 2, previousSeq);
//    routingMap->initMapinLayer(1, 1, 1, currentSeq);
//// print the result//////////////////////////////////
//    printf("current Sequence : ");
//    for (int i = 0; i < currentSeq.size(); ++i) {
//        if (currentSeq[i]->wireId) {
//            if (currentSeq[i]->isVirtual) {
//                printf("%d' ", *currentSeq[i]->wireId);
//            } else {
//                printf("%d ", *currentSeq[i]->wireId);
//            }
//        } else {
//            printf("x ");
//        }
//    }
//    printf("\n");
//    printf("previous Sequence : ");
//    for (int i = 0; i < previousSeq.size(); ++i) {
//        if (previousSeq[i]->wireId) {
//            if (previousSeq[i]->isVirtual) {
//                printf("%d' ", *previousSeq[i]->wireId);
//            } else {
//                printf("%d ", *previousSeq[i]->wireId);
//            }
//        } else {
//            printf("x ");
//        }
//    }
//    printf("\n");
    
    //routingMap->ringMaping(1, 1, 1);
    routingMap->printBox(1, 1);
    routingMap->printBox(1, 2);
    routingMap->printBox(1, 3);
   // routingMap->printBox(0, 3);
    routingMap->printBox(2, 1);
    routingMap->printBox(2, 2);
    routingMap->printBox(2, 3);
   // routingMap->printBox(1, 3);
    routingMap->printBox(3, 1);
    routingMap->printBox(3, 2);
    routingMap->printBox(3, 3);

    ////////////////////////////////////////////////////////
    delete routingMap;
    return 0;
}

