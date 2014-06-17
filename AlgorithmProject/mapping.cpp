//
//  mapping.cpp
//  AlgorithmProject
//
//  Created by steve on 2014/6/5.
//  Copyright (c) 2014年 ntu. All rights reserved.
//

#include "mapping.h"


mapping::mapping(int row_size,int col_size,int width,int spacing,vector<DriverNode> &d, vector<BumpNode> &b)
{
    mapRowNum = row_size;
    mapColNum = col_size;
    step_width = width + spacing;
    w = width;
    driver = d;
    bump = b;
    int x = 0;
    end = new BumpNode(0, &x, UnDirectRoute, false);
}
mapping::~mapping()
{}

bool sort_node_amount (node_side i,node_side j) { return (i.node_amount < j.node_amount); }
bool outside_ring_cmp (BumpNode *i,BumpNode *j) {return (*i->wireId < *j->wireId);}

void mapping::mapping_incircle(box *map)
{
    
    d_to_b_capacity = (driver[0].dbottomY - map[0].top[0]->absolutedY2)/(step_width);
    
    corner.push_back(map[0].top[0]);
    corner.push_back(map[0 * mapRowNum + (mapColNum-1)].right[0]);
    corner.push_back(map[(mapRowNum-1) * mapRowNum + (mapColNum-1)].buttom[0]);
    corner.push_back(map[(mapRowNum-1) * mapRowNum + 0].left[0]);
    
    int col = mapColNum/2 + mapColNum%2;
    int row = col;
    int side_current;
    if(mapColNum%2==0){ //even
        side_current = 2;
        row--;
        col--;
    }else if (mapColNum%2==1){ //odd
        side_current = 1;
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
        vector<BumpNode *>AA = map[2*mapRowNum].right;
        for(int i=0;i<side_current;i++){ // right total box
            for(int j=1;j<map[row * mapRowNum + col].right.size();j++){ //per box total node
                find_path_destination(map,row,col,1,j,side_current,row_col_start);
            }
            row++;
        }
        row--;
        AA = map[2*mapRowNum].right;
        for(int i=0;i<side_current;i++){ //buttom total box
            for(int j=1;j<map[row * mapRowNum + col].buttom.size();j++){ //per box total node
                find_path_destination(map,row,col,2,j,side_current,row_col_start);
            }
            col--;
        }
        col++;
        AA = map[2*mapRowNum].right;
        for(int i=0;i<side_current;i++){ //left total box
            for(int j=1;j<map[row * mapRowNum + col].left.size();j++){ //per box total node
                find_path_destination(map,row,col,3,j,side_current,row_col_start);
            }
            row--;
        }
        row++;
        AA = map[2*mapRowNum].right;
        
        
        
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
                if(map->top[node_order]->absolutedX1==0){
                    map->top[node_order]->absolutedX1 = map->right[0]->absolutedX1 - (step_width*(map->top.size()-node_order+1));
                    map->top[node_order]->absolutedY1 = (map->top[0]->absolutedY1 + map->top[0]->absolutedY2)/2;
                }
                map->right[i]->absolutedX1 = (map->right[0]->absolutedX1 + map->right[0]->absolutedX2)/2;
                map->right[i]->absolutedY1 = map->right[0]->absolutedY1 - (step_width*(map->top.size()-node_order+1));
                
                map->top[node_order]->route_next = map->right[i];
                map->top[node_order]->route_type = 4;
                if(row>=row_col_start && row<=(row_col_start+side_length-1) && col>=row_col_start && col<=(row_col_start+side_length-1)){
                    if(row>=(row_col_start+1) && row<=(row_col_start+side_length-2) && col>=(row_col_start+1) && col<=(row_col_start+side_length-2)){
                        
                    }else{
                        find_path_destination(map1,row,col+1,3,map->right.size()-i,side_length,row_col_start);
                    }
                }
            }
        }
        if(map->top[node_order]->wireId==map->buttom[0]->wireId){                       //type2   straight to bump buttom[0]
            map->top[node_order]->absolutedX1 = map->right[0]->absolutedX1 - (step_width*(map->top.size()-node_order+1));
            map->top[node_order]->absolutedY1 = (map->top[0]->absolutedY1 + map->top[0]->absolutedY2)/2;
            
            if(!map->buttom[0]->isconnected){
                
                map->top[node_order]->route_next = map->buttom[0];
                map->top[node_order]->route_type = 4;
                map->buttom[0]->isconnected = true;
            }
            
            
        }
        for(int i=map->buttom.size()-1;i>=1;i--){
            if(map->top[node_order]->wireId==map->buttom[i]->wireId){                   //type2   straight
                if(map->top[node_order]->absolutedX1==0){
                    map->top[node_order]->absolutedX1 = map->top[0]->absolutedX2 + (step_width*(node_order));
                    map->top[node_order]->absolutedY1 = (map->top[0]->absolutedY1 + map->top[0]->absolutedY2)/2;
                }
                map->buttom[i]->absolutedX1 = map->top[0]->absolutedX2 + (step_width*(node_order));
                map->buttom[i]->absolutedY1 = (map->buttom[0]->absolutedY1 + map->buttom[0]->absolutedY2)/2;
                
                map->top[node_order]->route_next = map->buttom[i];
                map->top[node_order]->route_type = 0;
                if(row>=row_col_start && row<=(row_col_start+side_length-1) && col>=row_col_start && col<=(row_col_start+side_length-1)){
                    if(row>=(row_col_start+1) && row<=(row_col_start+side_length-2) && col>=(row_col_start+1) && col<=(row_col_start+side_length-2)){
                        
                    }else{
                        find_path_destination(map1,row+1,col,0,map->buttom.size()-i,side_length,row_col_start);
                    }
                }
            }
        }
        if(map->top[node_order]->wireId==map->left[0]->wireId){                         //type2   straight to bump left[0]
            map->top[node_order]->absolutedX1 = map->top[0]->absolutedX2 + (step_width*node_order);
            map->top[node_order]->absolutedY1 = (map->top[0]->absolutedY1 + map->top[0]->absolutedY2)/2;
            
            if(!map->left[0]->isconnected){
                
                map->top[node_order]->route_next = map->left[0];
                map->top[node_order]->route_type = 2;
                map->left[0]->isconnected = true;
            }
        }
        for(int i=map->left.size()-1;i>=1;i--){
            if(map->top[node_order]->wireId==map->left[i]->wireId){                     //type3   turn around short distance
                if(map->top[node_order]->absolutedX1==0){
                    map->top[node_order]->absolutedX1 = map->top[0]->absolutedX2 + (step_width*(node_order));
                    map->top[node_order]->absolutedY1 = (map->top[0]->absolutedY1 + map->top[0]->absolutedY2)/2;
                }
                map->left[i]->absolutedX1 = (map->left[0]->absolutedX1 + map->left[0]->absolutedX2)/2;
                map->left[i]->absolutedY1 = map->top[0]->absolutedY1 - (step_width*(node_order));
                
                map->top[node_order]->route_next = map->left[i];
                map->top[node_order]->route_type = 2;
                if(row>=row_col_start && row<=(row_col_start+side_length-1) && col>=row_col_start && col<=(row_col_start+side_length-1)){
                    if(row>=(row_col_start+1) && row<=(row_col_start+side_length-2) && col>=(row_col_start+1) && col<=(row_col_start+side_length-2)){
                        
                    }else{
                        find_path_destination(map1,row,col-1,1,map->left.size()-i,side_length,row_col_start);
                    }
                }
            }
        }
    }else if(dir==1){
        for(int i=1;i<map->buttom.size();i++){                                   //type1  turn around long distance
            if(map->right[node_order]->wireId==map->buttom[i]->wireId){
                if(map->right[node_order]->absolutedX1==0){
                    map->right[node_order]->absolutedX1 = (map->right[0]->absolutedX1 + map->right[0]->absolutedX2)/2;
                    map->right[node_order]->absolutedY1 = map->buttom[0]->absolutedY2 + (step_width*(map->right.size()-node_order+1));
                }
                map->buttom[i]->absolutedX1 = map->buttom[0]->absolutedX1 - (step_width*(map->right.size()-node_order+1));
                map->buttom[i]->absolutedY1 = (map->buttom[0]->absolutedY1 + map->buttom[0]->absolutedY2)/2;
                
                map->right[node_order]->route_next = map->buttom[i];
                map->right[node_order]->route_type = 1;
                if(row>=row_col_start && row<=(row_col_start+side_length-1) && col>=row_col_start && col<=(row_col_start+side_length-1)){
                    if(row>=(row_col_start+1) && row<=(row_col_start+side_length-2) && col>=(row_col_start+1) && col<=(row_col_start+side_length-2)){
                        
                    }else{
                        find_path_destination(map1,row+1,col,0,map->buttom.size()-i,side_length,row_col_start);
                    }
                }
            }
        }
        if(map->right[node_order]->wireId==map->top[0]->wireId){                       //type2   straight to bump top[0]
            map->right[node_order]->absolutedX1 = (map->right[0]->absolutedX1 + map->right[0]->absolutedX2)/2;
            map->right[node_order]->absolutedY1 = map->right[0]->absolutedY1 - (step_width*node_order);
            
            if(!map->top[0]->isconnected){
                
                map->right[node_order]->route_next = map->top[0];
                map->right[node_order]->route_type = 4;
                map->top[0]->isconnected = true;
            }
        }
        for(int i=map->left.size()-1;i>=1;i--){
            if(map->right[node_order]->wireId==map->left[i]->wireId){                   //type2   straight
                if(map->right[node_order]->absolutedX1==0){
                    map->right[node_order]->absolutedX1 = (map->right[0]->absolutedX1 + map->right[0]->absolutedX2)/2;
                    map->right[node_order]->absolutedY1 = (map->right[0]->absolutedY1 - (step_width*node_order));
                }
                map->left[i]->absolutedX1 = (map->left[0]->absolutedX1 + map->left[0]->absolutedX2)/2;
                map->left[i]->absolutedY1 = (map->right[0]->absolutedY1 - (step_width*node_order));
                
                map->right[node_order]->route_next = map->left[i];
                map->right[node_order]->route_type = 0;
                if(row>=row_col_start && row<=(row_col_start+side_length-1) && col>=row_col_start && col<=(row_col_start+side_length-1)){
                    if(row>=(row_col_start+1) && row<=(row_col_start+side_length-2) && col>=(row_col_start+1) && col<=(row_col_start+side_length-2)){
                        
                    }else{
                        find_path_destination(map1,row,col-1,1,map->left.size()-i,side_length,row_col_start);
                    }
                }
            }
        }
        if(map->right[node_order]->wireId==map->left[0]->wireId){                         //type2   straight to bump left[0]
            map->right[node_order]->absolutedX1 = (map->right[0]->absolutedX1 + map->right[0]->absolutedX2)/2;
            map->right[node_order]->absolutedY1 = map->buttom[0]->absolutedY2 + (step_width*(map->right.size()-node_order+1));
            
            if(!map->left[0]->isconnected){
                
                map->right[node_order]->route_next = map->left[0];
                map->right[node_order]->route_type = 1;
                map->left[0]->isconnected = true;
            }
        }
        for(int i=map->top.size()-1;i>=1;i--){
            if(map->right[node_order]->wireId==map->top[i]->wireId){                     //type3   turn around short distance
                if(map->right[node_order]->absolutedX1==0){
                    map->right[node_order]->absolutedX1 = (map->right[0]->absolutedX1 + map->right[0]->absolutedX2)/2;
                    map->right[node_order]->absolutedY1 = map->right[0]->absolutedY1 - (step_width*node_order);
                }
                map->top[i]->absolutedX1 = map->right[0]->absolutedX1 - (step_width*node_order);
                map->top[i]->absolutedY1 = (map->top[0]->absolutedY1 + map->top[0]->absolutedY2)/2;
                
                map->right[node_order]->route_next = map->top[i];
                map->right[node_order]->route_type = 4;
                if(row>=row_col_start && row<=(row_col_start+side_length-1) && col>=row_col_start && col<=(row_col_start+side_length-1)){
                    if(row>=(row_col_start+1) && row<=(row_col_start+side_length-2) && col>=(row_col_start+1) && col<=(row_col_start+side_length-2)){
                        
                    }else{
                        find_path_destination(map1,row-1,col,2,map->top.size()-i,side_length,row_col_start);
                    }
                }
            }
        }
    }else if(dir==2){
        for(int i=1;i<map->left.size();i++){                                   //type1  turn around long distance
            if(map->buttom[node_order]->wireId==map->left[i]->wireId){
                if(map->buttom[node_order]->absolutedX1==0){
                    map->buttom[node_order]->absolutedX1 = map->left[0]->absolutedX2 + (step_width*(map->buttom.size()-node_order+1));
                    map->buttom[node_order]->absolutedY1 = (map->buttom[0]->absolutedY1 + map->buttom[0]->absolutedY2)/2;
                }
                map->left[i]->absolutedX1 = (map->right[0]->absolutedX1 + map->right[0]->absolutedX2)/2;
                map->left[i]->absolutedY1 = map->left[0]->absolutedY2 + (step_width*(map->buttom.size()-node_order+1));
                
                map->buttom[node_order]->route_next = map->left[i];
                map->buttom[node_order]->route_type = 3;
                if(row>=row_col_start && row<=(row_col_start+side_length-1) && col>=row_col_start && col<=(row_col_start+side_length-1)){
                    if(row>=(row_col_start+1) && row<=(row_col_start+side_length-2) && col>=(row_col_start+1) && col<=(row_col_start+side_length-2)){
                        
                    }else{
                        find_path_destination(map1,row,col-1,1,map->left.size()-i,side_length,row_col_start);
                    }
                }
            }
        }
        if(map->buttom[node_order]->wireId==map->top[0]->wireId){                       //type2   straight to bump top[0]
            map->buttom[node_order]->absolutedX1 = map->left[0]->absolutedX2 + (step_width*(map->buttom.size()-node_order+1));
            map->buttom[node_order]->absolutedY1 = (map->buttom[0]->absolutedY1 + map->buttom[0]->absolutedY2)/2;
            
            if(!map->top[0]->isconnected){
                
                map->buttom[node_order]->route_next = map->top[0];
                map->buttom[node_order]->route_type = 3;
                map->top[0]->isconnected =true;
            }
        }
        for(int i=map->top.size()-1;i>=1;i--){
            if(map->buttom[node_order]->wireId==map->top[i]->wireId){                   //type2   straight
                if(map->buttom[node_order]->absolutedX1==0){
                    map->buttom[node_order]->absolutedX1 = map->buttom[0]->absolutedX1 - (step_width*(node_order));
                    map->buttom[node_order]->absolutedY1 = (map->buttom[0]->absolutedY1 + map->buttom[0]->absolutedY2)/2;
                }
                map->top[i]->absolutedX1 = map->buttom[0]->absolutedX1 - (step_width*(node_order));
                map->top[i]->absolutedY1 = (map->top[0]->absolutedY1 + map->top[0]->absolutedY2)/2;
                
                map->buttom[node_order]->route_next = map->top[i];
                map->buttom[node_order]->route_type = 0;
                if(row>=row_col_start && row<=(row_col_start+side_length-1) && col>=row_col_start && col<=(row_col_start+side_length-1)){
                    if(row>=(row_col_start+1) && row<=(row_col_start+side_length-2) && col>=(row_col_start+1) && col<=(row_col_start+side_length-2)){
                        
                    }else{
                        find_path_destination(map1,row-1,col,2,map->top.size()-i,side_length,row_col_start);
                    }
                }
            }
        }
        if(map->buttom[node_order]->wireId==map->right[0]->wireId){                         //type2   straight to bump right[0]
            map->buttom[node_order]->absolutedX1 = map->buttom[0]->absolutedX1 - (step_width*node_order);
            map->buttom[node_order]->absolutedY1 = (map->buttom[0]->absolutedY1 + map->buttom[0]->absolutedY2)/2;
            
            if(!map->right[0]->isconnected){
                map->buttom[node_order]->route_next = map->right[0];
                map->buttom[node_order]->route_type = 1;
                map->right[0]->isconnected = true;
            }
        
        }
        for(int i=map->right.size()-1;i>=1;i--){
            if(map->buttom[node_order]->wireId==map->right[i]->wireId){                     //type3   turn around short distance
                if(map->buttom[node_order]->absolutedX1==0){
                    map->buttom[node_order]->absolutedX1 = map->buttom[0]->absolutedX1 - (step_width*(node_order));
                    map->buttom[node_order]->absolutedY1 = (map->buttom[0]->absolutedY1 + map->buttom[0]->absolutedY2)/2;
                }
                map->right[i]->absolutedX1 = (map->right[0]->absolutedX1 + map->right[0]->absolutedX2)/2;
                map->right[i]->absolutedY1 = map->buttom[0]->absolutedY2 + (step_width*(node_order));
                
                map->buttom[node_order]->route_next = map->right[i];
                map->buttom[node_order]->route_type = 1;
                if(row>=row_col_start && row<=(row_col_start+side_length-1) && col>=row_col_start && col<=(row_col_start+side_length-1)){
                    if(row>=(row_col_start+1) && row<=(row_col_start+side_length-2) && col>=(row_col_start+1) && col<=(row_col_start+side_length-2)){
                        
                    }else{
                        find_path_destination(map1,row,col+1,3,map->right.size()-i,side_length,row_col_start);
                    }
                }
            }
        }
    }else if(dir==3){
        for(int i=1;i<map->top.size();i++){                                   //type1  turn around long distance
            if(map->left[node_order]->wireId==map->top[i]->wireId){
                if(map->left[node_order]->absolutedX1==0){
                    map->left[node_order]->absolutedX1 = (map->left[0]->absolutedX1 + map->left[0]->absolutedX2)/2;
                    map->left[node_order]->absolutedY1 = map->top[0]->absolutedY1 - (step_width*(map->left.size()-node_order+1));
                }
                map->top[i]->absolutedX1 = map->top[0]->absolutedX2 + (step_width*(map->left.size()-node_order+1));
                map->top[i]->absolutedY1 = (map->top[0]->absolutedY1 + map->top[0]->absolutedY2)/2;
                
                map->left[node_order]->route_next = map->top[i];
                map->left[node_order]->route_type = 2;
                if(row>=row_col_start && row<=(row_col_start+side_length-1) && col>=row_col_start && col<=(row_col_start+side_length-1)){
                    if(row>=(row_col_start+1) && row<=(row_col_start+side_length-2) && col>=(row_col_start+1) && col<=(row_col_start+side_length-2)){
                        
                    }else{
                        find_path_destination(map1,row-1,col,2,map->top.size()-i,side_length,row_col_start);
                    }
                }
            }
        }
        if(map->left[node_order]->wireId==map->buttom[0]->wireId){                       //type2   straight to bump buttom[0]
            map->left[node_order]->absolutedX1 = (map->left[0]->absolutedX1 + map->left[0]->absolutedX2)/2;
            map->left[node_order]->absolutedY1 = map->left[0]->absolutedY2 + (step_width*node_order);
            
            if(!map->buttom[0]->isconnected){
                
                map->left[node_order]->route_next = map->buttom[0];
                map->left[node_order]->route_type = 3;
                map->buttom[0]->isconnected = true;
            }
            
        }
        for(int i=map->right.size()-1;i>=1;i--){
            if(map->left[node_order]->wireId==map->right[i]->wireId){                   //type2   straight
                if(map->left[node_order]->absolutedX1==0){
                    map->left[node_order]->absolutedX1 = (map->left[0]->absolutedX1 + map->left[0]->absolutedX2)/2;
                    map->left[node_order]->absolutedY1 = (map->left[0]->absolutedY2 + (step_width*node_order));
                }
                map->right[i]->absolutedX1 = (map->right[0]->absolutedX1 + map->right[0]->absolutedX2)/2;
                map->right[i]->absolutedY1 = (map->left[0]->absolutedY2 + (step_width*node_order));
                
                map->left[node_order]->route_next = map->right[i];
                map->left[node_order]->route_type = 0;
                if(row>=row_col_start && row<=(row_col_start+side_length-1) && col>=row_col_start && col<=(row_col_start+side_length-1)){
                    if(row>=(row_col_start+1) && row<=(row_col_start+side_length-2) && col>=(row_col_start+1) && col<=(row_col_start+side_length-2)){
                        
                    }else{
                        find_path_destination(map1,row,col+1,3,map->right.size()-i,side_length,row_col_start);
                    }
                }
            }
        }
        if(map->left[node_order]->wireId==map->right[0]->wireId){                         //type2   straight to bump right[0]
            map->left[node_order]->absolutedX1 = (map->left[0]->absolutedX1 + map->left[0]->absolutedX2)/2;
            map->left[node_order]->absolutedY1 = map->top[0]->absolutedY1 - (step_width*(map->left.size()-node_order+1));
            
            if(!map->right[0]->isconnected){
               
                map->left[node_order]->route_next = map->right[0];
                map->left[node_order]->route_type = 2;
                map->right[0]->isconnected = true;
            }
        }
        for(int i=map->buttom.size()-1;i>=1;i--){
            if(map->left[node_order]->wireId==map->buttom[i]->wireId){                     //type3   turn around short distance
                if(map->left[node_order]->absolutedX1==0){
                    map->left[node_order]->absolutedX1 = (map->left[0]->absolutedX1 + map->left[0]->absolutedX2)/2;
                    map->left[node_order]->absolutedY1 = map->left[0]->absolutedY2 + (step_width*node_order);
                }
                map->buttom[i]->absolutedX1 = map->left[0]->absolutedX2 + (step_width*node_order);
                map->buttom[i]->absolutedY1 = (map->buttom[0]->absolutedY1 + map->buttom[0]->absolutedY2)/2;
                
                map->left[node_order]->route_next = map->buttom[i];
                map->left[node_order]->route_type = 3;
                if(row>=row_col_start && row<=(row_col_start+side_length-1) && col>=row_col_start && col<=(row_col_start+side_length-1)){
                    if(row>=(row_col_start+1) && row<=(row_col_start+side_length-2) && col>=(row_col_start+1) && col<=(row_col_start+side_length-2)){
                        
                    }else{
                        find_path_destination(map1,row+1,col,0,map->buttom.size()-i,side_length,row_col_start);
                    }
                }
            }
        }
    }
}


void mapping::route_output(box *map,string file_name,int a,int a1,int a2,int a3)
{
    //vector<BumpNode *>::iterator it;
    //讀入最外層ring的所有virtual node
    int col=0,row=0;
    int side_current = mapColNum;
    
    for(int i=0;i<side_current;i++){ // top total box
        for(int j=0;j<map[row * mapRowNum + col].top.size();j++){ //per box total node
            if(j==0 && *map[row * mapRowNum + col].top[j]->wireId == (*map[row * mapRowNum + col].top[j+1]->wireId)-1){
                map[row * mapRowNum + col].top[j]->outside_ring_direction = 1;
                outside_ring_top.push_back(map[row * mapRowNum + col].top[j]);
            }else if(j>0){
                map[row * mapRowNum + col].top[j]->outside_ring_direction = 1;
                outside_ring_top.push_back(map[row * mapRowNum + col].top[j]);
            }
        }
        col++;
    }
    col--;
    for(int i=0;i<side_current;i++){ // right total box
        for(int j=0;j<map[row * mapRowNum + col].right.size();j++){ //per box total node
            if(j==0 && *map[row * mapRowNum + col].right[j]->wireId == (*map[row * mapRowNum + col].right[j+1]->wireId)-1){
                map[row * mapRowNum + col].right[j]->outside_ring_direction = 1;
                outside_ring_right.push_back(map[row * mapRowNum + col].right[j]);
            }else if(j>0){
                map[row * mapRowNum + col].right[j]->outside_ring_direction = 1;
                outside_ring_right.push_back(map[row * mapRowNum + col].right[j]);
            }
        }
        row++;
    }
    row--;
    for(int i=0;i<side_current;i++){ //buttom total box
        for(int j=0;j<map[row * mapRowNum + col].buttom.size();j++){ //per box total node
            if(j==0 && *map[row * mapRowNum + col].buttom[j]->wireId == (*map[row * mapRowNum + col].buttom[j+1]->wireId)-1){
                map[row * mapRowNum + col].buttom[j]->outside_ring_direction = 1;
                outside_ring_buttom.push_back(map[row * mapRowNum + col].buttom[j]);
            }else if(j>0){
                map[row * mapRowNum + col].buttom[j]->outside_ring_direction = 1;
                outside_ring_buttom.push_back(map[row * mapRowNum + col].buttom[j]);
            }
        }
        col--;
    }
    col++;
    for(int i=0;i<side_current;i++){ //left total box
        for(int j=0;j<map[row * mapRowNum + col].left.size();j++){ //per box total node
            if(j==0 && *map[row * mapRowNum + col].left[j]->wireId == (*map[row * mapRowNum + col].left[j+1]->wireId)-1){
                map[row * mapRowNum + col].left[j]->outside_ring_direction = 1;
                outside_ring_left.push_back(map[row * mapRowNum + col].left[j]);
            }else if(j>0){
                map[row * mapRowNum + col].left[j]->outside_ring_direction = 1;
                outside_ring_left.push_back(map[row * mapRowNum + col].left[j]);
            }
        }
        row--;
    }
    row++;

    
    ofstream myfile(file_name);
    if (myfile.is_open())
    {
        myfile << "designBoundary " << a << " " << a1 << " " << a2 << " " << a3 << "\n";
        myfile << "width " << w << "\n";
        myfile << "spacing " << step_width-w << "\n";
        myfile << "driver " << driver.size() << "\n";
        for(int i=0;i<driver.size();i++){
            myfile << driver[i].did << " " << driver[i].dleftX << " " << driver[i].dbottomY << " " << driver[i].drightX << " " << driver[i].dtopY << "\n";
        }
        myfile << "bump " << bump.size() << "\n";
        for(int i=0;i<bump.size();i++){
            myfile << bump[i].id << " " << bump[i].absolutedX1 << " " << bump[i].absolutedY1 << " " << bump[i].absolutedX2 << " " << bump[i].absolutedY2 << "\n";
        }
        create_node_btw_DB(myfile);
        sort(outside_ring_final.begin(),outside_ring_final.end(),outside_ring_cmp);
        
        myfile << "net " << outside_ring_final.size() << "\n";
        for(int i=0;i<outside_ring_final.size();i++){
            myfile << "netid " << *outside_ring_final[i]->wireId << "\n";
            trace_route(myfile, outside_ring_final[i], (driver[i].dleftX+driver[i].drightX)/2, (driver[i].dtopY), 1);
        }
        myfile.close();
    }
    

}

void mapping::trace_route(ofstream &myfile, BumpNode *node_start,int x_previous,int y_previous,bool driver)
{
    if(!driver){ //進入bump zone
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
                    if(x<x_destination && y<y_destination){ // start at buttom
                        x_destination = node_next->absolutedX1;
                        y_destination = (node_next->absolutedY1 + node_next->absolutedY2)/2;
                    }else{ //start at right
                        y_destination = node_next->absolutedY2;
                        x_destination = (node_next->absolutedX1 + node_next->absolutedX2)/2;
                    }
                    break;
                case 2: // _|
                    if(x<x_destination && y<y_destination){ // start at left
                        y_destination = node_next->absolutedY1;
                        x_destination = (node_next->absolutedX1 + node_next->absolutedX2)/2;
                    }else{ //start at top
                        x_destination = node_next->absolutedX2;
                        y_destination = (node_next->absolutedY1 + node_next->absolutedY2)/2;
                    }
                    break;
                case 3: // -|
                    if(x<x_destination && y>y_destination){ // start at left
                        y_destination = node_next->absolutedY2;
                        x_destination = (node_next->absolutedX1 + node_next->absolutedX2)/2;
                    }else{ //start at buttom
                        x_destination = node_next->absolutedX2;
                        y_destination = (node_next->absolutedY1 + node_next->absolutedY2)/2;
                    }
                    break;
                case 4: // |_
                    if(x<x_destination && y>y_destination){ // start at top
                        x_destination = node_next->absolutedX1;
                        y_destination = (node_next->absolutedY1 + node_next->absolutedY2)/2;
                    }else{ //start at right
                        y_destination = node_next->absolutedY1;
                        x_destination = (node_next->absolutedX1 + node_next->absolutedX2)/2;
                    }
                    break;
                default:
                    break;
            }
        }
        
        switch (routetype) {
            case 0: // straight:|
                
                trace_route(myfile,node_next,x_previous,y_previous,0);
                break;
                
            case 1: // |-
                
                if(x<x_destination && y<y_destination){ // start at buttom
                    write_output(x_previous-w/2,y_previous,x_previous+w/2,y_destination,myfile);
                    if(node_next->isVirtual && !(node_next->route_next==end))
                        trace_route(myfile,node_next,x,y_destination,0);
                    else
                        write_output(x_previous,y_destination-w/2,x_destination,y_destination+w/2,myfile);
                }else{ //start at right
                    write_output(x_previous,y_previous-w/2,x_destination,y_previous+w/2,myfile);
                    if(node_next->isVirtual && !(node_next->route_next==end))
                    trace_route(myfile,node_next,x_destination,y,0);
                    else
                        write_output(x_destination-w/2,y_destination,x_destination+w/2,y_previous,myfile);
                }
                break;
                
            case 2: // _|
                
                if(x<x_destination && y<y_destination){ // start at left
                    write_output(x_previous,y_previous-w/2,x_destination,y_previous+w/2,myfile);
                    if(node_next->isVirtual && !(node_next->route_next==end))
                    trace_route(myfile,node_next,x_destination,y,0);
                    else
                        write_output(x_destination-w/2,y_previous,x_destination+w/2,y_destination,myfile);
                }else{ //start at top
                    write_output(x_previous-w/2,y_previous,x_previous+w/2,y_destination,myfile);
                    if(node_next->isVirtual && !(node_next->route_next==end))
                    trace_route(myfile,node_next,x,y_destination,0);
                    else
                        write_output(x_previous,y_destination-w/2,x_destination,y_destination+w/2,myfile);
                }
                break;
                
            case 3: // -|
                
                if(x<x_destination && y>y_destination){ // start at left
                    write_output(x_previous,y_previous-w/2,x_destination,y_previous+w/2,myfile);
                    if(node_next->isVirtual && !(node_next->route_next==end))
                        trace_route(myfile,node_next,x_destination,y,0);
                    else
                        write_output(x_destination-w/2,y_destination,x_destination+w/2,y_previous,myfile);
                }else{ //start at buttom
                    write_output(x_previous-w/2,y_previous,x_previous+w/2,y_destination,myfile);
                    if(node_next->isVirtual && !(node_next->route_next==end))
                    trace_route(myfile,node_next,x,y_destination,0);
                    else
                        write_output(x_destination,y_destination-w/2,x_previous,y_destination+w/2,myfile);
                }
                break;
                
            case 4: // |_
                
                if(x<x_destination && y>y_destination){ // start at top
                    write_output(x_previous-w/2,y_previous,x_previous+w/2,y_destination,myfile);
                    if(node_next->isVirtual && !(node_next->route_next==end))
                    trace_route(myfile,node_next,x,y_destination,0);
                    else
                        write_output(x_previous,y_destination-w/2,x_destination,y_destination+w/2,myfile);
                }else{ //start at right
                    write_output(x_previous,y_previous-w/2,x_destination,y_previous+w/2,myfile);
                    if(node_next->isVirtual && !(node_next->route_next==end))
                    trace_route(myfile,node_next,x_destination,y,0);
                    else
                        write_output(x_destination-w/2,y_previous,x_destination+w/2,y_destination,myfile);
                }
                break;
                
            default:
                break;
        }
        
        
    }else{ //第一次進入:driver to bump or virtual node
        
        int X = node_start->absolutedX1;
        int Y = node_start->absolutedY1;
        int X_bump = node_start->route_next->absolutedX1;
        int Y_bump = node_start->route_next->absolutedY1;
        if(!node_start->route_next->isVirtual){
            X_bump = (node_start->route_next->absolutedX1+node_start->route_next->absolutedX2)/2;
            Y_bump = (node_start->route_next->absolutedY1+node_start->route_next->absolutedY2)/2;
        }
        
        
        if(node_start->outside_ring_direction==1){
            write_output(x_previous-w/2,Y,x_previous+w/2,y_previous,myfile);
            if(x_previous!=X)
                write_output(x_previous,Y-w/2,X,Y+w/2,myfile);
            if(node_start->route_next->isOutsideZone){
                write_output(X-w/2,node_start->route_next->absolutedY1,X+w/2,Y,myfile);
                trace_route(myfile,node_start->route_next,node_start->route_next->absolutedX1,node_start->route_next->absolutedY1,0);
            }else{
                trace_route(myfile,node_start,node_start->absolutedX1,node_start->absolutedY1,0);
            }
        }else if(node_start->outside_ring_direction==2){
            write_output(X,y_previous-w/2,x_previous,y_previous+w/2,myfile);
            if(y_previous!=Y)
                write_output(X-w/2,Y,X+w/2,y_previous,myfile);
            if(node_start->route_next->isOutsideZone){
                write_output(node_start->route_next->absolutedX1,Y-w/2,X,Y+w/2,myfile);
                trace_route(myfile,node_start->route_next,node_start->route_next->absolutedX1,node_start->route_next->absolutedY1,0);
            }else{
                trace_route(myfile,node_start,node_start->absolutedX1,node_start->absolutedY1,0);
            }
        }else if(node_start->outside_ring_direction==3){
            write_output(x_previous-w/2,y_previous,x_previous+w/2,Y,myfile);
            if(x_previous!=X)
                write_output(X,Y-w/2,x_previous,Y+w/2,myfile);
            if(node_start->route_next->isOutsideZone){
                write_output(X-w/2,Y,X+w/2,node_start->route_next->absolutedY1,myfile);
                trace_route(myfile,node_start->route_next,node_start->route_next->absolutedX1,node_start->route_next->absolutedY1,0);
            }else{
                trace_route(myfile,node_start,node_start->absolutedX1,node_start->absolutedY1,0);
            }
        }else if(node_start->outside_ring_direction==4){
            write_output(x_previous,y_previous-w/2,X,y_previous+w/2,myfile);
            if(y_previous!=Y)
                write_output(X-w/2,y_previous,X+w/2,Y,myfile);
            if(node_start->route_next->isOutsideZone){
                write_output(X,Y-w/2,node_start->route_next->absolutedX1,Y+w/2,myfile);
                trace_route(myfile,node_start->route_next,node_start->route_next->absolutedX1,node_start->route_next->absolutedY1,0);
            }else{
                trace_route(myfile,node_start,node_start->absolutedX1,node_start->absolutedY1,0);
            }
        }
        /*
        switch (node_start->outside_ring_direction) {
            case 1:
                write_output(x_previous-w/2,y_previous,x_previous+w/2,Y,myfile);
                if(x_previous!=X)
                    write_output(x_previous,Y-w/2,X,Y+w/2,myfile);
                
                
                    trace_route(myfile,node_start,X,Y,0);
                break;
            case 2:
                write_output(X,Y-w/2,x_previous,Y+w/2,myfile);
                if(node_start)
                trace_route(myfile,node_start,X,y_previous,0);
                break;
            case 3:
                write_output(X-w/2,Y,X+w/2,y_previous,myfile);
                if(node_start)
                trace_route(myfile,node_start,x_previous,Y,0);
                break;
            case 4:
                write_output(x_previous,Y-w/2,X,Y+w/2,myfile);
                if(node_start)
                trace_route(myfile,node_start,X,y_previous,0);
                break;
                
            default:
                break;
        }
        */
        
    }
    
}

void mapping::write_output(int x1r,int y1r,int x2r,int y2r,ofstream &myfile)
{
    cout << x1r << "," << y1r << "," << x2r << "," << y2r << endl;

    myfile << "wire " << x1r << " " << y1r << " " << x2r << " " << y2r << "\n";
}

void mapping::create_node_btw_DB(ofstream &myfile)
{
    for(int i=0;i<outside_ring_top.size();i++){
    BumpNode *A = new BumpNode(0, outside_ring_top[i]->wireId, UnDirectRoute, true);
    BumpNode *B = new BumpNode(0, A->wireId, UnDirectRoute, true);
        A->isOutsideZone = true;
        B->isOutsideZone = true;
    if(outside_ring_top[i]->absolutedX1!=0)
        A->route_next = outside_ring_top[i];
    else
        A->route_next = end;
    switch (outside_ring_top[i]->outside_ring_direction) {
        case 1: // to top
            A->absolutedY1 = corner[0]->absolutedY2 + (i+1)*step_width;
            A->absolutedX1 = (driver[*A->wireId-1].dleftX+driver[*A->wireId-1].drightX)/2;
            A->route_type = 3; //-|
            A->outside_ring_direction = 1;
            outside_ring_final.push_back(A);
            break;
        case 2: // to right
            A->absolutedX1 = corner[1]->absolutedX2 + (outside_ring_top.size()-i)*step_width;
            A->absolutedY1 = corner[1]->absolutedY2 + (outside_ring_top.size()-i)*step_width;
            A->route_type = 1; //|-
            A->outside_ring_direction = 2;
            outside_ring_final.push_back(A);
            break;
        case 3: // to buttom
            A->absolutedX1 = corner[0]->absolutedX1 - (outside_ring_left.size()+i+1)*step_width;
            A->absolutedY1 = corner[0]->absolutedY2 + (i+1)*step_width;
            A->route_type = 3; //-|
            B->route_next = A;
            B->absolutedX1 = A->absolutedX1;
            B->absolutedY1 = corner[3]->absolutedY1 - (outside_ring_left.size()+i+1)*step_width;
            B->route_type = 0; //|
            B->outside_ring_direction = 3;
            outside_ring_final.push_back(B);
            break;
        case 4: // to left
            A->absolutedX1 = corner[0]->absolutedX1 - (i+1)*step_width;
            A->absolutedY1 = corner[0]->absolutedY2 + (i+1)*step_width;
            A->route_type = 3; //-|
            A->outside_ring_direction = 4;
            outside_ring_final.push_back(A);
            break;
        default:
            break;
    }
}
    for(int i=0;i<outside_ring_right.size();i++){
        BumpNode *A = new BumpNode(0, outside_ring_right[i]->wireId, UnDirectRoute, false);
        BumpNode *B = new BumpNode(0, A->wireId, UnDirectRoute, false);
        A->isOutsideZone = true;
        B->isOutsideZone = true;
        if(outside_ring_right[i]->absolutedX1!=0)
            A->route_next = outside_ring_right[i];
        else
            A->route_next = end;
        switch (outside_ring_right[i]->outside_ring_direction) {
            case 1: // to top
                A->absolutedX1 = corner[1]->absolutedX2 + (i+1)*step_width;
                A->absolutedY1 = corner[1]->absolutedY2 + (outside_ring_top.size()+i+1)*step_width;
                A->route_type = 2; //_|
                A->outside_ring_direction = 1;
                outside_ring_final.push_back(A);
                break;
            case 2: // to right
                A->absolutedX1 = corner[1]->absolutedX2 + (i+1)*step_width;
                A->absolutedY1 = (driver[*A->wireId-1].dtopY+driver[*A->wireId-1].dbottomY)/2;
                A->route_type = 2; //_|
                A->outside_ring_direction = 2;
                outside_ring_final.push_back(A);
                break;
            case 3: // to buttom
                A->absolutedX1 = corner[2]->absolutedX2 + (outside_ring_right.size()-i)*step_width;
                A->absolutedY1 = corner[2]->absolutedY1 - (outside_ring_right.size()-i)*step_width;
                A->route_type = 3; //-|
                A->outside_ring_direction = 3;
                outside_ring_final.push_back(A);
                break;
            case 4: // to left
                A->absolutedX1 = corner[1]->absolutedX2 + (i+1)*step_width;
                A->absolutedY1 = corner[1]->absolutedY2 + (outside_ring_top.size()+i+1)*step_width;
                A->route_type = 2; //_|
                B->route_next = A;
                B->absolutedX1 = corner[0]->absolutedX1 - (outside_ring_top.size()+i+1)*step_width;
                B->absolutedY1 = A->absolutedY1;
                B->route_type = 0; //|
                B->outside_ring_direction = 4;
                outside_ring_final.push_back(B);
                break;
            default:
                break;
        }
    }
    for(int i=0;i<outside_ring_buttom.size();i++){
        BumpNode *A = new BumpNode(0, outside_ring_buttom[i]->wireId, UnDirectRoute, false);
        BumpNode *B = new BumpNode(0, A->wireId, UnDirectRoute, false);
        A->isOutsideZone = true;
        B->isOutsideZone = true;
        if(outside_ring_buttom[i]->absolutedX1!=0)
            A->route_next = outside_ring_buttom[i];
        else
            A->route_next = end;
        switch (outside_ring_buttom[i]->outside_ring_direction) {
            case 1: // to top
                A->absolutedX1 = corner[2]->absolutedX2 + (outside_ring_right.size()+i+1)*step_width;
                A->absolutedY1 = corner[2]->absolutedY1 - (i+1)*step_width;
                A->route_type = 4; //|_
                B->route_next = A;
                B->absolutedX1 = A->absolutedX1;
                B->absolutedY1 = corner[1]->absolutedY2 + (outside_ring_top.size()+outside_ring_right.size()+i+1)*step_width;
                B->route_type = 0; //|
                B->outside_ring_direction = 1;
                outside_ring_final.push_back(B);
                break;
            case 2: // to right
                A->absolutedX1 = corner[2]->absolutedX2 + (i+1)*step_width;
                A->absolutedY1 = corner[2]->absolutedY1 - (i+1)*step_width;
                A->route_type = 2; //|_
                A->outside_ring_direction = 2;
                outside_ring_final.push_back(A);

                break;
            case 3: // to buttom
                A->absolutedY1 = corner[2]->absolutedY1 - (i+1)*step_width;
                A->absolutedX1 = (driver[*A->wireId-1].dleftX+driver[*A->wireId-1].drightX)/2;
                A->route_type = 4; //|_
                A->outside_ring_direction = 3;
                outside_ring_final.push_back(A);
                break;
            case 4: // to left
                A->absolutedX1 = corner[3]->absolutedX1 - (outside_ring_buttom.size()-i)*step_width;
                A->absolutedY1 = corner[3]->absolutedY1 - (outside_ring_buttom.size()-i)*step_width;
                A->route_type = 2; //_|
                A->outside_ring_direction = 4;
                outside_ring_final.push_back(A);
                break;
            default:
                break;
        }
    }
    for(int i=0;i<outside_ring_left.size();i++){
        BumpNode *A = new BumpNode(0, outside_ring_left[i]->wireId, UnDirectRoute, false);
        BumpNode *B = new BumpNode(0, A->wireId, UnDirectRoute, false);
        A->isOutsideZone = true;
        B->isOutsideZone = true;
        if(outside_ring_left[i]->absolutedX1!=0)
            A->route_next = outside_ring_left[i];
        else
            A->route_next = end;
        switch (outside_ring_left[i]->outside_ring_direction) {
            case 1: // to top
                A->absolutedX1 = corner[0]->absolutedX1 - (outside_ring_left.size()-i)*step_width;
                A->absolutedY1 = corner[0]->absolutedY2 + (outside_ring_left.size()-i)*step_width;
                A->route_type = 4; //|_
                A->outside_ring_direction = 1;
                outside_ring_final.push_back(A);
                break;
            case 2: // to right
                A->absolutedX1 = corner[3]->absolutedX1 - (i+1)*step_width;
                A->absolutedY1 = corner[3]->absolutedY1 - (outside_ring_buttom.size()+i+1)*step_width;
                A->route_type = 1; //|-
                B->route_next = A;
                A->outside_ring_direction = 2;
                B->absolutedX1 = corner[2]->absolutedX2 + (outside_ring_buttom.size()+i+1)*step_width;
                B->absolutedY1 = A->absolutedY1;
                B->route_type = 0; //|
                outside_ring_final.push_back(B);
                break;
            case 3: // to buttom
                A->absolutedX1 = corner[3]->absolutedX1 - (i+1)*step_width;
                A->absolutedY1 = corner[3]->absolutedY1 - (i+1)*step_width;
                A->route_type = 1; //|-
                A->outside_ring_direction = 3;
                outside_ring_final.push_back(A);
                break;
            case 4: // to left
                A->absolutedX1 = corner[3]->absolutedX1 - (i+1)*step_width;
                A->absolutedY1 = (driver[*A->wireId-1].dtopY+driver[*A->wireId-1].dbottomY)/2;
                A->route_type = 1; //|-
                A->outside_ring_direction = 4;
                outside_ring_final.push_back(A);
                break;
            default:
                break;
        }
    }
    
}


void mapping::mapping_outcircle(vector<BumpNode *> outCircleSequence)
{
    for(int i=0;i<outCircleSequence.size();i++){
        outCircleSequence[i]->route_next = end;
    }
}























