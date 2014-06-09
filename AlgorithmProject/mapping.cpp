//
//  mapping.cpp
//  AlgorithmProject
//
//  Created by steve on 2014/6/5.
//  Copyright (c) 2014年 ntu. All rights reserved.
//

#include "mapping.h"


mapping::mapping(int row_size,int col_size,int width,int spacing)
{
    mapRowNum = row_size;
    mapColNum = col_size;
    step_width = width+spacing;
    w = width;
}
mapping::~mapping()
{}

bool sort_node_amount (node_side i,node_side j) { return (i.node_amount < j.node_amount); }

void mapping::mapping_incircle(box *map)
{
    
    
    int col = mapColNum/2 + mapColNum%2;
    int row = col;
    int side_current;
    if(mapColNum%2==0){ //even
        side_current = 2;
    }else if (mapColNum%2==1){ //odd
        side_current = 3;
        row--;
        col--;
    }
    
    
    while(side_current<=mapColNum){
        
        int row_col_start = row;
        
        for(int i=0;i<side_current;i++){ // top total box
            for(int j=1;j<map[row * mapRowNum + col].top.size();j++){ //per box total node
                find_path_destination(map,row,col,0,j,side_current,row_col_start);
            }
            col++;
        }
        col--;
        for(int i=0;i<side_current;i++){ // right total box
            for(int j=1;j<map[row * mapRowNum + col].right.size();j++){ //per box total node
                find_path_destination(map,row,col,1,j,side_current,row_col_start);
            }
            row++;
        }
        row--;
        for(int i=0;i<side_current;i++){ //buttom total box
            for(int j=1;j<map[row * mapRowNum + col].buttom.size();j++){ //per box total node
                find_path_destination(map,row,col,2,j,side_current,row_col_start);
            }
            col--;
        }
        col++;
        for(int i=0;i<side_current;i++){ //left total box
            for(int j=1;j<map[row * mapRowNum + col].left.size();j++){ //per box total node
                find_path_destination(map,row,col,3,j,side_current,row_col_start);
            }
            row--;
        }
        row++;
        
        
        
        
        side_current=side_current+2;
        row--;
        col--;  //move to outside layer
        
    }
    
}

void mapping::find_path_destination(box *map1,int row,int col,int dir,int node_order,int side_length,int row_col_start)
{
    box *map = &map1[row * mapRowNum + col];
    if(dir==0){
        for(int i=1;i<map->right.size();i++){                                   //type1  turn around long distance
            if(map->top[node_order]->wireId==map->right[i]->wireId){
                map->top[node_order]->absolutedX1 = map->right[0]->absolutedX1 - (step_width*(map->top.size()-node_order+1));
                map->top[node_order]->absolutedY1 = (map->top[0]->absolutedY1 + map->top[0]->absolutedY2)/2;
                map->right[i]->absolutedX1 = (map->right[0]->absolutedX1 + map->right[0]->absolutedX2)/2;
                map->right[i]->absolutedY1 = map->right[0]->absolutedY2 + (step_width*(map->top.size()-node_order+1));
                
                map->top[node_order]->route_next = map->right[i];
                map->top[node_order]->route_type = 4;
                if(row>=row_col_start && row<=(row_col_start+side_length-1) && col>=row_col_start && col<=(row_col_start+side_length-1)){
                    if(row>=(row_col_start+1) && row<=(row_col_start+side_length-2) && col>=(row_col_start+1) && col<=(row_col_start+side_length-2)){
                        
                    }else{
                        find_path_destination(map1,row,col++,3,map->right.size()-i,side_length,row_col_start);
                    }
                }
            }
        }
        if(map->top[node_order]->wireId==map->buttom[0]->wireId){                       //type2   straight to bump buttom[0]
            map->top[node_order]->absolutedX1 = map->right[0]->absolutedX1 - (step_width*(map->top.size()-node_order+1));
            map->top[node_order]->absolutedY1 = (map->top[0]->absolutedY1 + map->top[0]->absolutedY2)/2;
            
            map->top[node_order]->route_next = map->buttom[0];
            map->top[node_order]->route_type = 4;
        }
        for(int i=map->buttom.size()-1;i<=1;i++){
            if(map->top[node_order]->wireId==map->buttom[i]->wireId){                   //type2   straight
                map->top[node_order]->absolutedX1 = map->top[0]->absolutedX2 + (step_width*(node_order));
                map->top[node_order]->absolutedY1 = (map->top[0]->absolutedY1 + map->top[0]->absolutedY2)/2;
                map->buttom[i]->absolutedX1 = map->top[0]->absolutedX2 + (step_width*(node_order));
                map->buttom[i]->absolutedY1 = (map->buttom[0]->absolutedY1 + map->buttom[0]->absolutedY2)/2;
                
                map->top[node_order]->route_next = map->buttom[i];
                map->top[node_order]->route_type = 0;
                if(row>=row_col_start && row<=(row_col_start+side_length-1) && col>=row_col_start && col<=(row_col_start+side_length-1)){
                    if(row>=(row_col_start+1) && row<=(row_col_start+side_length-2) && col>=(row_col_start+1) && col<=(row_col_start+side_length-2)){
                        
                    }else{
                        find_path_destination(map1,row++,col,0,map->buttom.size()-i,side_length,row_col_start);
                    }
                }
            }
        }
        if(map->top[node_order]->wireId==map->left[0]->wireId){                         //type2   straight to bump left[0]
            map->top[node_order]->absolutedX1 = map->top[0]->absolutedX2 + (step_width*node_order);
            map->top[node_order]->absolutedY1 = (map->top[0]->absolutedY1 + map->top[0]->absolutedY2)/2;
            
            map->top[node_order]->route_next = map->left[0];
            map->top[node_order]->route_type = 2;
        }
        for(int i=map->left.size()-1;i<=1;i++){
            if(map->top[node_order]->wireId==map->left[i]->wireId){                     //type3   turn around short distance
                map->top[node_order]->absolutedX1 = map->top[0]->absolutedX2 + (step_width*(node_order));
                map->top[node_order]->absolutedY1 = (map->top[0]->absolutedY1 + map->top[0]->absolutedY2)/2;
                map->left[i]->absolutedX1 = (map->left[0]->absolutedX1 + map->left[0]->absolutedX2)/2;
                map->left[i]->absolutedY1 = map->top[0]->absolutedY2 + (step_width*(node_order));
                
                map->top[node_order]->route_next = map->left[i];
                map->top[node_order]->route_type = 2;
                if(row>=row_col_start && row<=(row_col_start+side_length-1) && col>=row_col_start && col<=(row_col_start+side_length-1)){
                    if(row>=(row_col_start+1) && row<=(row_col_start+side_length-2) && col>=(row_col_start+1) && col<=(row_col_start+side_length-2)){
                        
                    }else{
                        find_path_destination(map1,row,col--,1,map->left.size()-i,side_length,row_col_start);
                    }
                }
            }
        }
    }else if(dir==1){
        for(int i=1;i<map->buttom.size();i++){                                   //type1  turn around long distance
            if(map->right[node_order]->wireId==map->buttom[i]->wireId){
                map->right[node_order]->absolutedX1 = (map->right[0]->absolutedX1 + map->right[0]->absolutedX2)/2;
                map->right[node_order]->absolutedY1 = map->buttom[0]->absolutedY1 - (step_width*(map->right.size()-node_order+1));
                map->buttom[i]->absolutedX1 = map->buttom[0]->absolutedX1 - (step_width*(map->right.size()-node_order+1));
                map->buttom[i]->absolutedY1 = (map->buttom[0]->absolutedY1 + map->buttom[0]->absolutedY2)/2;
                
                map->right[node_order]->route_next = map->buttom[i];
                map->right[node_order]->route_type = 1;
                if(row>=row_col_start && row<=(row_col_start+side_length-1) && col>=row_col_start && col<=(row_col_start+side_length-1)){
                    if(row>=(row_col_start+1) && row<=(row_col_start+side_length-2) && col>=(row_col_start+1) && col<=(row_col_start+side_length-2)){
                        
                    }else{
                        find_path_destination(map1,row++,col,3,map->buttom.size()-i,side_length,row_col_start);
                    }
                }
            }
        }
        if(map->right[node_order]->wireId==map->top[0]->wireId){                       //type2   straight to bump top[0]
            map->right[node_order]->absolutedX1 = (map->right[0]->absolutedX1 + map->right[0]->absolutedX2)/2;
            map->right[node_order]->absolutedY1 = map->right[0]->absolutedY2 + (step_width*node_order);
            
            map->right[node_order]->route_next = map->top[0];
            map->right[node_order]->route_type = 4;
        }
        for(int i=map->left.size()-1;i<=1;i++){
            if(map->right[node_order]->wireId==map->left[i]->wireId){                   //type2   straight
                map->right[node_order]->absolutedX1 = (map->right[0]->absolutedX1 + map->right[0]->absolutedX2)/2;
                map->right[node_order]->absolutedY1 = (map->right[0]->absolutedY2 + (step_width*node_order));
                map->left[i]->absolutedX1 = (map->left[0]->absolutedX1 + map->left[0]->absolutedX2)/2;
                map->left[i]->absolutedY1 = (map->right[0]->absolutedY2 + (step_width*node_order));
                
                map->right[node_order]->route_next = map->left[i];
                map->right[node_order]->route_type = 0;
                if(row>=row_col_start && row<=(row_col_start+side_length-1) && col>=row_col_start && col<=(row_col_start+side_length-1)){
                    if(row>=(row_col_start+1) && row<=(row_col_start+side_length-2) && col>=(row_col_start+1) && col<=(row_col_start+side_length-2)){
                        
                    }else{
                        find_path_destination(map1,row,col--,0,map->left.size()-i,side_length,row_col_start);
                    }
                }
            }
        }
        if(map->right[node_order]->wireId==map->left[0]->wireId){                         //type2   straight to bump left[0]
            map->right[node_order]->absolutedX1 = (map->right[0]->absolutedX1 + map->right[0]->absolutedX2)/2;
            map->right[node_order]->absolutedY1 = map->buttom[0]->absolutedY1 - (step_width*(map->right.size()-node_order+1));
            
            map->right[node_order]->route_next = map->left[0];
            map->right[node_order]->route_type = 1;
        }
        for(int i=map->top.size()-1;i<=1;i++){
            if(map->right[node_order]->wireId==map->top[i]->wireId){                     //type3   turn around short distance
                map->right[node_order]->absolutedX1 = (map->right[0]->absolutedX1 + map->right[0]->absolutedX2)/2;
                map->right[node_order]->absolutedY1 = map->right[0]->absolutedY2 + (step_width*node_order);
                map->top[i]->absolutedX1 = map->right[0]->absolutedX1 - (step_width*node_order);
                map->top[i]->absolutedY1 = (map->top[0]->absolutedY1 + map->top[0]->absolutedY2)/2;
                
                map->right[node_order]->route_next = map->top[i];
                map->right[node_order]->route_type = 4;
                if(row>=row_col_start && row<=(row_col_start+side_length-1) && col>=row_col_start && col<=(row_col_start+side_length-1)){
                    if(row>=(row_col_start+1) && row<=(row_col_start+side_length-2) && col>=(row_col_start+1) && col<=(row_col_start+side_length-2)){
                        
                    }else{
                        find_path_destination(map1,row++,col,1,map->left.size()-i,side_length,row_col_start);
                    }
                }
            }
        }
    }else if(dir==2){
        for(int i=1;i<map->left.size();i++){                                   //type1  turn around long distance
            if(map->buttom[node_order]->wireId==map->left[i]->wireId){
                map->buttom[node_order]->absolutedX1 = map->left[0]->absolutedX2 + (step_width*(map->buttom.size()-node_order+1));
                map->buttom[node_order]->absolutedY1 = (map->buttom[0]->absolutedY1 + map->buttom[0]->absolutedY2)/2;
                map->left[i]->absolutedX1 = (map->right[0]->absolutedX1 + map->right[0]->absolutedX2)/2;
                map->left[i]->absolutedY1 = map->left[0]->absolutedY1 - (step_width*(map->buttom.size()-node_order+1));
                
                map->buttom[node_order]->route_next = map->left[i];
                map->buttom[node_order]->route_type = 3;
                if(row>=row_col_start && row<=(row_col_start+side_length-1) && col>=row_col_start && col<=(row_col_start+side_length-1)){
                    if(row>=(row_col_start+1) && row<=(row_col_start+side_length-2) && col>=(row_col_start+1) && col<=(row_col_start+side_length-2)){
                        
                    }else{
                        find_path_destination(map1,row,col--,1,map->left.size()-i,side_length,row_col_start);
                    }
                }
            }
        }
        if(map->buttom[node_order]->wireId==map->top[0]->wireId){                       //type2   straight to bump top[0]
            map->buttom[node_order]->absolutedX1 = map->left[0]->absolutedX2 + (step_width*(map->buttom.size()-node_order+1));
            map->buttom[node_order]->absolutedY1 = (map->buttom[0]->absolutedY1 + map->buttom[0]->absolutedY2)/2;
            
            map->buttom[node_order]->route_next = map->top[0];
            map->buttom[node_order]->route_type = 3;
        }
        for(int i=map->top.size()-1;i<=1;i++){
            if(map->buttom[node_order]->wireId==map->top[i]->wireId){                   //type2   straight
                map->buttom[node_order]->absolutedX1 = map->buttom[0]->absolutedX1 - (step_width*(node_order));
                map->buttom[node_order]->absolutedY1 = (map->buttom[0]->absolutedY1 + map->buttom[0]->absolutedY2)/2;
                map->top[i]->absolutedX1 = map->buttom[0]->absolutedX1 - (step_width*(node_order));
                map->top[i]->absolutedY1 = (map->top[0]->absolutedY1 + map->top[0]->absolutedY2)/2;
                
                map->buttom[node_order]->route_next = map->top[i];
                map->buttom[node_order]->route_type = 0;
                if(row>=row_col_start && row<=(row_col_start+side_length-1) && col>=row_col_start && col<=(row_col_start+side_length-1)){
                    if(row>=(row_col_start+1) && row<=(row_col_start+side_length-2) && col>=(row_col_start+1) && col<=(row_col_start+side_length-2)){
                        
                    }else{
                        find_path_destination(map1,row--,col,1,map->top.size()-i,side_length,row_col_start);
                    }
                }
            }
        }
        if(map->buttom[node_order]->wireId==map->right[0]->wireId){                         //type2   straight to bump right[0]
            map->buttom[node_order]->absolutedX1 = map->buttom[0]->absolutedX1 - (step_width*node_order);
            map->buttom[node_order]->absolutedY1 = (map->buttom[0]->absolutedY1 + map->buttom[0]->absolutedY2)/2;
            
            map->buttom[node_order]->route_next = map->right[0];
            map->buttom[node_order]->route_type = 1;
        }
        for(int i=map->right.size()-1;i<=1;i++){
            if(map->buttom[node_order]->wireId==map->right[i]->wireId){                     //type3   turn around short distance
                map->buttom[node_order]->absolutedX1 = map->buttom[0]->absolutedX1 - (step_width*(node_order));
                map->buttom[node_order]->absolutedY1 = (map->buttom[0]->absolutedY1 + map->buttom[0]->absolutedY2)/2;
                map->right[i]->absolutedX1 = (map->right[0]->absolutedX1 + map->right[0]->absolutedX2)/2;
                map->right[i]->absolutedY1 = map->buttom[0]->absolutedY1 - (step_width*(node_order));
                
                map->buttom[node_order]->route_next = map->right[i];
                map->buttom[node_order]->route_type = 1;
                if(row>=row_col_start && row<=(row_col_start+side_length-1) && col>=row_col_start && col<=(row_col_start+side_length-1)){
                    if(row>=(row_col_start+1) && row<=(row_col_start+side_length-2) && col>=(row_col_start+1) && col<=(row_col_start+side_length-2)){
                        
                    }else{
                        find_path_destination(map1,row,col++,1,map->top.size()-i,side_length,row_col_start);
                    }
                }
            }
        }
    }else if(dir==3){
        for(int i=1;i<map->top.size();i++){                                   //type1  turn around long distance
            if(map->left[node_order]->wireId==map->top[i]->wireId){
                map->left[node_order]->absolutedX1 = (map->left[0]->absolutedX1 + map->left[0]->absolutedX2)/2;
                map->left[node_order]->absolutedY1 = map->top[0]->absolutedY2 + (step_width*(map->left.size()-node_order+1));
                map->top[i]->absolutedX1 = map->top[0]->absolutedX2 + (step_width*(map->left.size()-node_order+1));
                map->top[i]->absolutedY1 = (map->top[0]->absolutedY1 + map->top[0]->absolutedY2)/2;
                
                map->left[node_order]->route_next = map->top[i];
                map->left[node_order]->route_type = 2;
                if(row>=row_col_start && row<=(row_col_start+side_length-1) && col>=row_col_start && col<=(row_col_start+side_length-1)){
                    if(row>=(row_col_start+1) && row<=(row_col_start+side_length-2) && col>=(row_col_start+1) && col<=(row_col_start+side_length-2)){
                        
                    }else{
                        find_path_destination(map1,row--,col,1,map->top.size()-i,side_length,row_col_start);
                    }
                }
            }
        }
        if(map->left[node_order]->wireId==map->buttom[0]->wireId){                       //type2   straight to bump buttom[0]
            map->left[node_order]->absolutedX1 = (map->left[0]->absolutedX1 + map->left[0]->absolutedX2)/2;
            map->left[node_order]->absolutedY1 = map->left[0]->absolutedY1 - (step_width*node_order);
            
            map->left[node_order]->route_next = map->buttom[0];
            map->left[node_order]->route_type = 2;
        }
        for(int i=map->right.size()-1;i<=1;i++){
            if(map->left[node_order]->wireId==map->right[i]->wireId){                   //type2   straight
                map->left[node_order]->absolutedX1 = (map->left[0]->absolutedX1 + map->left[0]->absolutedX2)/2;
                map->left[node_order]->absolutedY1 = (map->left[0]->absolutedY1 - (step_width*node_order));
                map->right[i]->absolutedX1 = (map->right[0]->absolutedX1 + map->right[0]->absolutedX2)/2;
                map->right[i]->absolutedY1 = (map->left[0]->absolutedY1 - (step_width*node_order));
                
                map->left[node_order]->route_next = map->right[i];
                map->left[node_order]->route_type = 0;
                if(row>=row_col_start && row<=(row_col_start+side_length-1) && col>=row_col_start && col<=(row_col_start+side_length-1)){
                    if(row>=(row_col_start+1) && row<=(row_col_start+side_length-2) && col>=(row_col_start+1) && col<=(row_col_start+side_length-2)){
                        
                    }else{
                        find_path_destination(map1,row,col++,1,map->top.size()-i,side_length,row_col_start);
                    }
                }
            }
        }
        if(map->left[node_order]->wireId==map->right[0]->wireId){                         //type2   straight to bump right[0]
            map->left[node_order]->absolutedX1 = (map->left[0]->absolutedX1 + map->left[0]->absolutedX2)/2;
            map->left[node_order]->absolutedY1 = map->top[0]->absolutedY2 + (step_width*(map->left.size()-node_order+1));
            
            map->left[node_order]->route_next = map->right[0];
            map->left[node_order]->route_type = 3;
        }
        for(int i=map->buttom.size()-1;i<=1;i++){
            if(map->left[node_order]->wireId==map->buttom[i]->wireId){                     //type3   turn around short distance
                map->left[node_order]->absolutedX1 = (map->left[0]->absolutedX1 + map->left[0]->absolutedX2)/2;
                map->left[node_order]->absolutedY1 = map->left[0]->absolutedY1 - (step_width*node_order);
                map->buttom[i]->absolutedX1 = map->left[0]->absolutedX2 + (step_width*node_order);
                map->buttom[i]->absolutedY1 = (map->buttom[0]->absolutedY1 + map->buttom[0]->absolutedY2)/2;
                
                map->left[node_order]->route_next = map->buttom[i];
                map->left[node_order]->route_type = 3;
                if(row>=row_col_start && row<=(row_col_start+side_length-1) && col>=row_col_start && col<=(row_col_start+side_length-1)){
                    if(row>=(row_col_start+1) && row<=(row_col_start+side_length-2) && col>=(row_col_start+1) && col<=(row_col_start+side_length-2)){
                        
                    }else{
                        find_path_destination(map1,row++,col,1,map->top.size()-i,side_length,row_col_start);
                    }
                }
            }
        }
    }
}


void mapping::route_output(box *map)
{
    int row=0,col=0,side_current=mapColNum;
    
    for(int i=0;i<side_current;i++){ // top total box
        for(int j=1;j<map[row * mapRowNum + col].top.size();j++){ //per box total node
            trace_route(map[row * mapRowNum + col].top[j],map[row * mapRowNum + col].top[j]->absolutedX1,map[row * mapRowNum + col].top[j]->absolutedY1);
        }
        col++;
    }
    col--;
    for(int i=0;i<side_current;i++){ // right total box
        for(int j=1;j<map[row * mapRowNum + col].right.size();j++){ //per box total node
            trace_route(map[row * mapRowNum + col].right[j],map[row * mapRowNum + col].right[j]->absolutedX1,map[row * mapRowNum + col].right[j]->absolutedY1);
        }
        row++;
    }
    row--;
    for(int i=0;i<side_current;i++){ //buttom total box
        for(int j=1;j<map[row * mapRowNum + col].buttom.size();j++){ //per box total node
            trace_route(map[row * mapRowNum + col].buttom[j],map[row * mapRowNum + col].buttom[j]->absolutedX1,map[row * mapRowNum + col].buttom[j]->absolutedY1);
        }
        col--;
    }
    col++;
    for(int i=0;i<side_current;i++){ //left total box
        for(int j=1;j<map[row * mapRowNum + col].left.size();j++){ //per box total node
            trace_route(map[row * mapRowNum + col].left[j],map[row * mapRowNum + col].left[j]->absolutedX1,map[row * mapRowNum + col].left[j]->absolutedY1);
        }
        row--;
    }
    row++;

}

void mapping::trace_route(BumpNode *node_start,int x_previous,int y_previous)
{
    BumpNode *node_next;
    node_next = node_start->route_next;
    int routetype = node_start->route_type;
    
    int x = node_start->absolutedX1;
    int y = node_start->absolutedY1;
    int x_destination = node_next->absolutedX1;
    int y_destination = node_next->absolutedY1;
    
    if(!node_next->isVirtual){ // connect to bump
        switch (routetype) {
            case 1: // |-
                if(x<x_destination && y>y_destination){ // start at buttom
                    x_destination = node_next->absolutedX1;
                    y_destination = (node_next->absolutedY1 + node_next->absolutedY2)/2;
                }else{ //start at right
                    y_destination = node_next->absolutedY1;
                    x_destination = (node_next->absolutedX1 + node_next->absolutedX2)/2;
                }
                break;
            case 2: // _|
                if(x<x_destination && y>y_destination){ // start at left
                    y_destination = node_next->absolutedY2;
                    x_destination = (node_next->absolutedX1 + node_next->absolutedX2)/2;
                }else{ //start at top
                    x_destination = node_next->absolutedX2;
                    y_destination = (node_next->absolutedY1 + node_next->absolutedY2)/2;
                }
                break;
            case 3: // -|
                if(x<x_destination && y<y_destination){ // start at left
                    y_destination = node_next->absolutedY1;
                    x_destination = (node_next->absolutedX1 + node_next->absolutedX2)/2;
                }else{ //start at buttom
                    x_destination = node_next->absolutedX2;
                    y_destination = (node_next->absolutedY1 + node_next->absolutedY2)/2;
                }
                break;
            case 4: // |_
                if(x<x_destination && y<y_destination){ // start at top
                    x_destination = node_next->absolutedX1;
                    y_destination = (node_next->absolutedY1 + node_next->absolutedY2)/2;
                }else{ //start at right
                    y_destination = node_next->absolutedY2;
                    x_destination = (node_next->absolutedX1 + node_next->absolutedX2)/2;
                }
                break;
            default:
                break;
        }
    }
    
    switch (routetype) {
        case 0: // straight:|
            
            trace_route(node_next->route_next,x_previous,y_previous);
            break;
            
        case 1: // |-
            
            if(x<x_destination && y>y_destination){ // start at buttom
                write_output(x_previous-w/2,y_previous,x_previous+w/2,y_destination);
                trace_route(node_next->route_next,x,y_destination);
            }else{ //start at right
                write_output(x_previous,y_previous-w/2,x_destination,y_previous+w/2);
                trace_route(node_next->route_next,x_destination,y);
            }
            break;
            
        case 2: // _|
            
            if(x<x_destination && y>y_destination){ // start at left
                write_output(x_previous,y_previous-w/2,x_destination,y_previous+w/2);
                trace_route(node_next->route_next,x_destination,y);
            }else{ //start at top
                write_output(x_previous-w/2,y_previous,x_previous+w/2,y_destination);
                trace_route(node_next->route_next,x,y_destination);
            }
            break;
            
        case 3: // -|
            
            if(x<x_destination && y<y_destination){ // start at left
                write_output(x_previous,y_previous-w/2,x_destination,y_previous+w/2);
                trace_route(node_next->route_next,x_destination,y);
            }else{ //start at buttom
                write_output(x_previous-w/2,y_previous,x_previous+w/2,y_destination);
                trace_route(node_next->route_next,x,y_destination);
            }
            break;
            
        case 4: // |_
            
            if(x<x_destination && y<y_destination){ // start at top
                write_output(x_previous-w/2,y_previous,x_previous+w/2,y_destination);
                trace_route(node_next->route_next,x,y_destination);
            }else{ //start at right
                write_output(x_previous,y_previous-w/2,x_destination,y_previous+w/2);
                trace_route(node_next->route_next,x_destination,y);
            }
            break;
            
        default:
            break;
    }
    
}

void mapping::write_output(int x1r,int y1r,int x2r,int y2r)
{
    cout << x1r << "," << y1r << "," << x2r << "," << y2r << endl;
}










