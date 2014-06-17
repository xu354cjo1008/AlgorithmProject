//
//  solve_boxnode.cpp
//  
//
//  Created by steve on 2014/5/26.
//
//

#include "solve_boxnode.h"
#include <algorithm>
using namespace std;

bool boxnode_measurement(box *input)
{
    int node_capacity = 10;
    
    if((input->top.size()-1)>node_capacity||(input->right.size()-1)>node_capacity||(input->buttom.size()-1)>node_capacity||(input->left.size()-1)>node_capacity)
    {
        return false; //任何一邊超過node_capacity
    }

    if(measure_diagonal(input,node_capacity)) //檢查對角線數是否超過node_capacity
    {
        sort_node(input);  //排列兩個ring中的path_node
        return true;
    }else{
        return false;
    }
    
    
}

bool sort_node_cmp (BumpNode *i,BumpNode *j) { return (i->sort_value < j->sort_value); }

void sort_node(box *input)
{
    //-----------first-----------
    if(input->cooridinate == 0) //first_call, 右上角box
    {
        vector<int> right_ref;      //逆時針旋轉
        
        
        for(int i=(input->top.size()-1);i>=0;i--)    //逆時針旋轉
        {
            right_ref.push_back(*input->top[i]->wireId);
        }
        for(int i=(input->left.size()-1);i>=0;i--)
        {
            right_ref.push_back(*input->left[i]->wireId);
        }
        
        //give sort_value & sort BumpNode
        for(int i=0;i<input->right.size();i++)
        {
            int it = find (right_ref.begin(),right_ref.end(),*input->right[i]->wireId) - right_ref.begin();
            input->right[i]->sort_value = it;
        }
        sort(input->right.begin()+1,input->right.end(),sort_node_cmp);
        for(int i=0;i<input->buttom.size();i++)
        {
            int it = find (right_ref.begin(),right_ref.end(),*input->buttom[i]->wireId) - right_ref.begin();
            input->buttom[i]->sort_value = it;
        }
        sort(input->buttom.begin()+1,input->buttom.end(),sort_node_cmp);
    }
    else{
        //-------------第二次以後進來開始往順時針出發--------------
        
        if(!input->top_lock)            //top unlock
        {
            vector<int> top_ref;      //逆時針旋轉
            
            for(int i=(input->left.size()-1);i>=0;i--)    //逆時針旋轉
            {
                top_ref.push_back(*input->left[i]->wireId);
            }
            for(int i=(input->buttom.size()-1);i>=0;i--)
            {
                top_ref.push_back(*input->buttom[i]->wireId);
            }
            for(int i=(input->right.size()-1);i>=0;i--)
            {
                top_ref.push_back(*input->right[i]->wireId);
            }
            for(int i=0;i<input->top.size();i++)
            {
                int it = find (top_ref.begin(),top_ref.end(),*input->top[i]->wireId) - top_ref.begin();
                input->top[i]->sort_value = it;
            }
            sort(input->top.begin()+1,input->top.end(),sort_node_cmp);
            
        }
        else if(!input->right_lock)     //right unlock
        {
            vector<int> right_ref;      //逆時針旋轉
            
            for(int i=input->top.size()-1;i>=0;i--)    //逆時針旋轉
            {
                right_ref.push_back(*input->top[i]->wireId);
            }
            for(int i=input->left.size()-1;i>=0;i--)
            {
                right_ref.push_back(*input->left[i]->wireId);
            }
            for(int i=input->buttom.size()-1;i>=0;i--)
            {
                right_ref.push_back(*input->buttom[i]->wireId);
            }
            for(int i=0;i<input->right.size();i++)
            {
                int it = find (right_ref.begin(),right_ref.end(),*input->right[i]->wireId) - right_ref.begin();
                input->right[i]->sort_value = it;
            }
            sort(input->right.begin()+1,input->right.end(),sort_node_cmp);
            
        }
        else if(!input->buttom_lock)        //buttom unlock
        {
            vector<int> buttom_ref;      //逆時針旋轉
            
            for(int i=input->right.size()-1;i>=0;i--)    //逆時針旋轉
            {
                buttom_ref.push_back(*input->right[i]->wireId);
            }
            for(int i=input->top.size()-1;i>=0;i--)
            {
                buttom_ref.push_back(*input->top[i]->wireId);
            }
            for(int i=input->left.size()-1;i>=0;i--)
            {
                buttom_ref.push_back(*input->left[i]->wireId);
            }
            for(int i=0;i<input->buttom.size();i++)
            {
                int it = find (buttom_ref.begin(),buttom_ref.end(),*input->buttom[i]->wireId) - buttom_ref.begin();
                input->buttom[i]->sort_value = it;
            }
            sort(input->buttom.begin()+1,input->buttom.end(),sort_node_cmp);
        }
        else if(!input->left_lock)          //left unlock
        {
            vector<int> left_ref;      //逆時針旋轉
            
            for(int i=input->buttom.size()-1;i>=0;i--)    //逆時針旋轉
            {
                left_ref.push_back(*input->buttom[i]->wireId);
            }
            for(int i=input->right.size()-1;i>=0;i--)
            {
                left_ref.push_back(*input->right[i]->wireId);
            }
            for(int i=input->top.size()-1;i>=0;i--)
            {
                left_ref.push_back(*input->top[i]->wireId);
            }
            for(int i=0;i<input->left.size();i++)
            {
                int it = find (left_ref.begin(),left_ref.end(),*input->left[i]->wireId) - left_ref.begin();
                input->left[i]->sort_value = it;
            }
            sort(input->left.begin()+1,input->left.end(),sort_node_cmp);
        }
}
    
}

bool measure_diagonal(box *input,int node_capacity)
{
    int left_slash=0;
    int right_slash=0;
    
    input->left.push_back(input->top.front());
    input->right.push_back(input->buttom.front());
    input->top.push_back(input->right.front());
    input->buttom.push_back(input->left.front());
    
    for(int i=0;i<input->left.size();i++)
        for(int j=0;j<input->right.size();j++)
            if(*input->left[i]->wireId==*input->right[j]->wireId){
                if(input->left[i]->nextNode == input->right[j] || input->right[j]->nextNode == input->left[i] ){
                    left_slash++;
                    right_slash++;
                }
            }
    for(int i=0;i<input->top.size();i++)
        for(int j=0;j<input->buttom.size();j++)
            if(*input->top[i]->wireId==*input->buttom[j]->wireId){
                if(input->top[i]->nextNode == input->buttom[j] || input->buttom[j]->nextNode == input->top[i] ){
                    left_slash++;
                    right_slash++;
                }
            }
    
    input->left.pop_back();
    for(int i=0;i<input->left.size();i++)
        for(int j=0;j<input->top.size();j++)
            if(*input->left[i]->wireId==*input->top[j]->wireId)
                if(input->left[i]->nextNode == input->top[j] || input->top[j]->nextNode == input->left[i])
                    left_slash++;
        
    input->right.pop_back();
    for(int i=0;i<input->right.size();i++)
        for(int j=0;j<input->buttom.size();j++)
            if(*input->right[i]->wireId==*input->buttom[j]->wireId)
                if(input->right[i]->nextNode == input->buttom[j] || input->buttom[j]->nextNode == input->right[i])
                    left_slash++;
    
    input->left.push_back(input->top.front());
    input->right.push_back(input->buttom.front());
    
    input->top.pop_back();
    for(int i=0;i<input->top.size();i++)
        for(int j=0;j<input->right.size();j++)
            if(*input->top[i]->wireId==*input->right[j]->wireId)
                if(input->top[i]->nextNode == input->right[j] || input->right[j]->nextNode == input->top[i])
                    right_slash++;
    
    input->buttom.pop_back();
    for(int i=0;i<input->buttom.size();i++)
        for(int j=0;j<input->left.size();j++)
            if(*input->buttom[i]->wireId==*input->left[j]->wireId)
                if(input->buttom[i]->nextNode == input->left[j] || input->left[j]->nextNode == input->buttom[i])
                right_slash++;
    
    input->left.pop_back();
    input->right.pop_back();

    
    
    if(left_slash > node_capacity || right_slash > node_capacity)
    {
        return false;
    }else{
        return true;
    }
}