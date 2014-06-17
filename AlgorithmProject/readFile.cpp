//
//  readFile.cpp
//  AlgorithmProject
//
//  Created by 李勁璋 on 2014/6/9.
//  Copyright (c) 2014年 ntu. All rights reserved.
//

#include "readFile.h"
#include <fstream>
#include <math.h>
#include <algorithm>
//for alignment
bool smaller_absolutedX1 (BumpNode i,BumpNode j) { return (i.absolutedX1 < j.absolutedX1); }
bool greater_absolutedY1 (BumpNode i,BumpNode j) { return (i.absolutedY1 > j.absolutedY1); }
bool greater_absolutedX1 (BumpNode i,BumpNode j) { return (i.absolutedX1 > j.absolutedX1); }
bool smaller_absolutedY1 (BumpNode i,BumpNode j) { return (i.absolutedY1 < j.absolutedY1); }

ReadFile::ReadFile()
{
  //  char buffer[200];
    fstream infile("test16.txt");
    //fstream infile;
   // infile.open("test144.in", ios::in); //read test file
    if (!infile.is_open()) {
        printf("read file error");
    }
    
    
    int width, spacing, num_driver, num_bump;
    string junk1, junk2, junk3, junk4, junk5;
    
    
    
    infile >> junk1 >> bound.leftX >> bound.bottomY >> bound.rightX >> bound.topY;
    infile >> junk2 >> width;
    infile >> junk3 >> spacing;
    infile >> junk4 >> num_driver;
    w = width;
    s = spacing;
   // dsize = new vector<Dsize>[num_driver - 1];
  //  bsize(num_bump-1);

   // vector<int> num_d(num_driver-1);
   // vector<int*> num_b(num_bump-1);
    DriverNode input_d;
    int id, left, right, bottom, top;
    
    while (infile >> id >> left >> bottom >> right >> top){
        input_d.did = id;
        input_d.dleftX = left;
        input_d.drightX = right;
        input_d.dbottomY = bottom;
        input_d.dtopY = top;
        driver.push_back(input_d);
        
        if (input_d.did == num_driver)
            break;
    } // end of reading the layout of drivers
    infile >> junk5 >> num_bump;
    
    while(infile >> id >> left >> bottom >> right >> top){
        BumpNode *input_b = new BumpNode(0, 0, UnDirectRoute, false);
        input_b->wireId = &driver[id-1].did;
        input_b->absolutedX1 = left;
        input_b->absolutedY1 = bottom;
        input_b->absolutedX2 = right;
        input_b->absolutedY2 = top;
        bump.push_back(*input_b);
    } //end of reading the layout of bumps
    infile.close();
    
    alignment(num_bump);
}
void ReadFile::alignment(int bumpNum)
{
    
    vector<BumpNode>bump_dup = bump;
    int x = MaxY2(&bump_dup);
    maxRowNum = 0;
    for (int i = 0; i < bump_dup.size(); ++i) {
        if (bump_dup[i].absolutedY2 == x) {
            maxRowNum++;
        }
    }
    int n = maxRowNum / 2;
    if (maxRowNum%2) {
        n++;
    }
    numBvec = n;
    bvec = new vector<BumpNode>[n]; //create n vectors to store rings
    
    
    //if indicator id true:
    for( int j = n-1 ; j >= 0; j--){
    	int m = MaxY2(&bump_dup);
        for(int i = 0; i < bump_dup.size(); i++){
            if(bump_dup[i].absolutedY2 == m){
            	bvec[j].push_back(bump_dup[i]);
            	bump_dup.erase(bump_dup.begin() + i);
                i--;
            }
            
        }
        vector<BumpNode>*aaaa = &bvec[j];
        sort(bvec[j].begin(), bvec[j].end(), smaller_absolutedX1);
        int q = bvec[j].size();
        // end of reading the upper edge of bump square 
        m = MaxX2(&bump_dup);
        for(int i = 0; i < bump_dup.size(); i++){
            if(bump_dup[i].absolutedX2 == m){
            	bvec[j].push_back(bump_dup[i]);  
                bump_dup.erase(bump_dup.begin() + i);
                i--;
            }
        }
        sort(bvec[j].begin() + q, bvec[j].end(), greater_absolutedY1);
        q = bvec[j].size();
	 //end of mapping the right edge 
        m = MinY1(&bump_dup);
        for(int i = 0; i < bump_dup.size(); i++){
            if(bump_dup[i].absolutedY1 == m){
                bvec[j].push_back(bump_dup[i]); 
                bump_dup.erase(bump_dup.begin() + i);
                i--;
            }
         }
         sort(bvec[j].begin() + q, bvec[j].end(), greater_absolutedX1);
         q = bvec[j].size();
  	  // end of mapping the lower edge
         m = MinX1(&bump_dup);
         for(int i = 0; i < bump_dup.size(); i++){
             if(bump_dup[i].absolutedX1 == m){
                bvec[j].push_back(bump_dup[i]);  
                bump_dup.erase(bump_dup.begin() + i);
                 i--;
              }
          }
	 sort(bvec[j].begin() + q, bvec[j].end(), smaller_absolutedY1);
	 //end of mapping the left edge
    } //run LCS algorithms with all bvec
}
int MaxY2(vector<BumpNode>*bump_dup){
	int max = (*bump_dup)[0].absolutedY2;
	for(int i =0; i < bump_dup->size(); i++){
		if((*bump_dup)[i].absolutedY2 > max)
		   max = (*bump_dup)[i].absolutedY2;
	}
    return max;
}
int MaxX2(vector<BumpNode>*bump_dup){
	int max = (*bump_dup)[0].absolutedX2;
	for(int i =0; i < bump_dup->size(); i++){
		if((*bump_dup)[i].absolutedX2 > max)
		   max = (*bump_dup)[i].absolutedX2;
	}
    return max;
}
int MinY1(vector<BumpNode>*bump_dup){
	int min = (*bump_dup)[0].absolutedY1;
	for(int i =0; i < bump_dup->size(); i++){
		if((*bump_dup)[i].absolutedY1 < min)
		   min =(*bump_dup)[i].absolutedY1;
	}
    return min;
}
int MinX1(vector<BumpNode>*bump_dup){
	int min = (*bump_dup)[0].absolutedX1;
	for(int i =0; i < bump_dup->size(); i++){
		if((*bump_dup)[i].absolutedX1 < min)
		min = (*bump_dup)[i].absolutedX1;
	}
    return min;
}
void ReadFile::LCS(vector<DriverNode> *driver_vec, vector<BumpNode>*bump_vec, int num_driver, int n){
    //lcs_bump dpary[num_driver][n];//DP table
    dpary = new lcs_bump*[num_driver+1];
    for (int i = 0; i < num_driver+1; ++i) {
        dpary[i] = new lcs_bump[n+1];
    }
    for(int i = 0; i <= num_driver; i++)
        dpary[i][0].cs = 0;
    for(int i = 0; i <= n; i++)
        dpary[0][i].cs = 0;
    
    for(int i = 1; i <= num_driver; i++){
        for(int j = 1; j <= n; j++){
            if((*driver_vec)[i-1].did == *(*bump_vec)[j-1].wireId)
            {
                dpary[i][j].cs = dpary[i-1][j-1].cs + 1;
                dpary[i][j].prev = &dpary[i-1][j-1].cs;
            }
            else
            {
                if(dpary[i-1][j].cs < dpary[i][j-1].cs)
                {
                    dpary[i][j].cs = dpary[i][j-1].cs;
                    dpary[i][j].prev = &dpary[i][j-1].cs;
                    
                }
                else
                {
                    dpary[i][j].cs = dpary[i-1][j].cs;
                    dpary[i][j].prev = &dpary[i-1][j].cs;
                    
                }
            }
        }
    }
    label_LCS(driver_vec->size(),bump_vec->size(), bump_vec);
//    if( driver_vec.size() == 0 || bump_vec.size() == 0)
//        return;
//    if(dpary[i][j].prev == *dpary[i-1][j-1].cs)
//        label_LCS(i-1,j-1);
//    bump_vec[j].lcsType = DirectRoute;
//    else if(dpary[i][j].prev == *dpary[i-1][j].cs)
//        label_LCS(i-1,j);
//    else if(dpary[i][j].prev == *dpary[i][j-1].cs)
//        label_LCS(i,j-1);
//	for(int u = 0; u < j; u++){
//		if(bump_vec[u].lcsType != DirectRoute)
//			bump_vec[u].lcsType = UnDirectRoute;
//	}
}


void ReadFile::label_LCS(int i, int j, vector<BumpNode>*bump_vec)
{
    if(i < 0 || j < 0)
        return;
    if(i == 0 && j == 0)
        return;
    if(dpary[i][j].prev == &dpary[i-1][j-1].cs){
        label_LCS(i-1,j-1,bump_vec);
        (*bump_vec)[j-1].lcsType = DirectRoute;
    }else if(dpary[i][j].prev == &dpary[i-1][j].cs)
        label_LCS(i-1,j, bump_vec);
    else if(dpary[i][j].prev == &dpary[i][j-1].cs)
        label_LCS(i,j-1, bump_vec);
//	for(int u = 0; u < j; u++){
//		if((*bump_vec)[u].lcsType != DirectRoute)
//			(*bump_vec)[u].lcsType = UnDirectRoute;
//	}
}

