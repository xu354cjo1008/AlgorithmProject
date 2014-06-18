//
//  bump_node.cpp
//  bump_node
//
//  Created by 李勁璋 on 2014/5/19.
//  Copyright (c) 2014年 Li,Ching-Chang. All rights reserved.
//

#include "bump_node.h"

BumpNode::BumpNode(int node_id, int *wire_id, LCSType LCS_type, bool is_virtual, int absoluted_X1, int absoluted_Y1, int absoluted_X2, int absoluted_Y2, int relative_X, int relative_Y)
{
    id = node_id;
    wireId = wire_id;
    lcsType = LCS_type;
    mpscType = outCircle;
    isVirtual = is_virtual;
    absolutedX1 = absoluted_X1;
    absolutedY1 = absoluted_Y1;
    absolutedX2 = absoluted_X2;
    absolutedY2 = absoluted_Y2;
    relativeX = relative_X;
    relativeY = relative_Y;
}
BumpNode::BumpNode(int node_id, int *wire_id, LCSType LCS_type, bool is_virtual)
{
    id = node_id;
    wireId = wire_id;
    lcsType = LCS_type;
    mpscType = outCircle;
    isVirtual = is_virtual;
}
BumpNode::BumpNode(BumpNode *copyFormNode)
{
    id = copyFormNode->id;
    wireId = copyFormNode->wireId;
    lcsType = copyFormNode->lcsType;
    mpscType = copyFormNode->mpscType;
    outside_ring_direction = copyFormNode->outside_ring_direction;
    isVirtual = true;
    copyFormNode->nextNode = this;
    previousNode = copyFormNode;
}


BumpNode::~BumpNode()
{
    wireId = nullptr;
}
