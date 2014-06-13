//
//  bump_node.h
//  bump_node
//
//  Created by 李勁璋 on 2014/5/19.
//  Copyright (c) 2014年 Li,Ching-Chang. All rights reserved.
//

#ifndef __MPSC__bump_node__
#define __MPSC__bump_node__
typedef enum
{
    DirectRoute,
    UnDirectRoute,
}LCSType;

typedef enum
{    
	inCircle,
    outCircle,
}MPSCType;

typedef enum
{
	leftDir,
    straightforwardDir,
    rightDir,
}Direction;

class BumpNode
{
public:
    BumpNode(int node_id, int *wire_id, LCSType LCS_type, bool is_virtual, int absoluted_X1, int absoluted_Y1, int absoluted_X2, int absoluted_Y2, int relative_X, int relative_Y);
    BumpNode(int node_id, int *wire_id, LCSType LCS_type, bool is_virtual);
	~BumpNode();
	int id;
	int *wireId;//which driver
	LCSType lcsType;
    MPSCType mpscType;
	bool isVirtual;
    int sort_value;
    int absolutedX1, absolutedY1, absolutedX2, absolutedY2;
    int relativeX, relativeY;
    
    int route_type; //0:straight   |1/2|  |4\3|
    
    
    BumpNode *route_next;
    BumpNode *nextNode;
    BumpNode *previousNode;
    Direction nextDirection;

private:
};

#endif /* defined(__MPSC__bump_node__) */
