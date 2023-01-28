/*
CSCI 104: Homework 1 Problem 1

Write a recursive function to split a sorted singly-linked
list into two sorted linked lists, where one has the even 
numbers and the other contains the odd numbers. Students 
will receive no credit for non-recursive solutions. 
To test your program write a separate .cpp file and #include
split.h.  **Do NOT add main() to this file**.  When you submit
the function below should be the only one in this file.
*/

#include "split.h"
// #include <unistd.h> //so I can type NULL

/* Add a prototype for a helper function here if you need */

void split(Node*& in, Node*& odds, Node*& evens)
{
  /* Add code here */
  // WRITE YOUR CODE HERE

  //1. list is empty - base case (do nothing / stop recursing)
  if (in == nullptr)
  {
    return;
  }

  //2. iterate and recurse through (tail recursion)
  split(in->next, odds, evens);


  //3. list is not empty --> check value of node
  if( ((in->value) % 2) == 0)
  {
    //even value + attach it to next node

    if(evens == nullptr) //empty evens list
    {
      evens = in;
    }
    else {
      in->next = evens; //set current node next to point to rest of evens
      evens = in; //set as head of evens
    }
    
  }
  else {
    //odd value + attached it to next node

    if(odds == nullptr) //empty odds list
    {
      odds = in;
    }
    else {
      in->next = odds; //set current node next to point to rest of odds
      odds = in; //set as head of odds
    }
  }

  in = nullptr; //after using up the node --> use as nullptr

  //TESTING GIT

}

/* If you needed a helper function, write it here */