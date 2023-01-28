#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"
#include <iostream>

ULListStr::ULListStr()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr()
{
  clear();
}

size_t ULListStr::size() const
{
  return size_;
}

bool ULListStr::empty() const
{
  return size_ == 0;
}


// WRITE YOUR CODE HERE
void ULListStr::push_back(const std::string& val)
{
  //start at end of list
  Item* temp = tail_;

  //1. if empty list
  if(head_ == nullptr)
  {
    std::cout << "pushback: emptylist adding a node" << std::endl;

    // Make the new node the head
    Item* newNode = new Item();

    // set the given value to be the first elem in the array
    newNode->val[newNode->first] = val;

    // last is equal to 0 so we only need to increment it
    newNode->last++;

    //set head
    head_ = newNode;

    //set tail
    tail_ = newNode;

    //update size
    size_++;

  }
  //2. last index of tail filled
  else if( tail_->last == ARRSIZE ) {
    std::cout << "pushback: need new node at end of array" << std::endl;

    // Make a new node that will be at the back
    Item* newNode = new Item();

    //set newNode's prev to the prev tail
    newNode->prev = tail_;

    //set old tail's next to new item
    tail_->next = newNode;

    // make the new node the tail
    tail_ = newNode;    

    // set the given value to be the first elem in the new string array
    // and increment last
    newNode->val[newNode->first] = val;
    newNode->last++;

    //update size
    size_++;

    std::cout << val << std::endl;


  }
    else {
      std::cout << "pushback: still room in array --> appending to back" << std::endl;

      // we still have room in the array so we will add our val 
      // to our value array at the last position and 
      tail_->val[tail_->last] = val;

      //increment last
      tail_->last++;

      //increment size
      size_++;

      std::cout << val << std::endl;
    }

}

void ULListStr::pop_back()
{
  Item* temp = tail_;

  //1. emptylist
  if(head_ == nullptr)
  {
    std::cout << "popback: emptylist --> doing nothing" << std::endl;
    return;
  }
  //2. only one item left --> reset to empty list
  else if (size_ == 1)
    {
      std::cout << "popback: one item left --> deleting node" << std::endl;
      delete temp;

      head_ = nullptr;
      tail_ = nullptr;

      //decrement size
      size_--;
    }
  //3. tail only has one item (at the front)
   else if (temp->last-1==0)
   {
    std::cout << "popback: multiple items but tail has one item in front --> removing tail node " << std::endl;

    //set tail to prev item
    tail_ = temp->prev;

    //set new tail's next to nullptr
    tail_->next = nullptr;

    //delete last node
    delete temp;

    //decrement size
    size_--;
   }
  //4. tail has more than one items
  else {
    std::cout << "popback: normal behavior --> removing front item" << std::endl;

    //set to empty string
    tail_->val[tail_->last-1] = "";

    //decrement last
    tail_->last--;

    //decrement size
    size_--;

  }

  
}

void ULListStr::push_front(const std::string& val)
{
  //start at front of list
  Item* temp = head_;

  //if empty list
  if (head_ == nullptr) {
    // Make the new node the head
    Item* newNode = new Item();

    // set the given value to be the first elem in the array
    newNode->val[newNode->first] = val;

    // last is equal to 0 so we only need to increment it
    newNode->last++;

    //set head
    head_ = newNode;

    //set tail
    tail_ = newNode;

    //update size
    size_++;
  }
  else if(temp->first==0) //add node at front end of ULL (if item at front)
  {
    //make new node in front
    Item* newNode = new Item();

    //set newNode's next to be prev head
    newNode->next = head_;

    //set old tail's prev to be new item
    head_->prev = newNode;

    //make the new node the head
    head_ = newNode;
    
    //set the given value to be the last element of the new array
    newNode->val[ARRSIZE-1] = val;

    //set last to ARRSIZE
    newNode->last = ARRSIZE;
    
    //set newNode's first to last item
    newNode->first = ARRSIZE-1;

    //update size
    size_++;
  } 
  else
  {
    //still have room in array at front
    temp->val[temp->first-1] = val;

    //set at first-1 and decrement first
    temp->first--;

    //increment size
    size_++;
  }

}

void ULListStr::pop_front()
{
  Item* temp = head_;

  //1. empty list
  if (head_ == nullptr)
  {
    std::cout << "popfront: emptylist --> doing nothing" << std::endl;
    return;
  }
  //2. only one item left --> reset to empty list
  else if (size_ == 1)
    {
      std::cout << "popfront: one item left --> deleting node" << std::endl;

      delete temp;

      head_ = nullptr;
      tail_ = nullptr;

      //decrement size
      size_--;
    }
  //3. one element in head node (at back)
  else if (temp->first==ARRSIZE-1)
  {
  std::cout << "popfront: multiple items but head has one item in back --> removing head node " << std::endl;

    //set head to next item
    head_ = temp->next;

    //set new head's prev to null
    head_->prev = nullptr;

    //delete front item 
    delete temp;

    //decrement size
    size_--;
  }
  //4. more than one items at head node
  else {
    std::cout << "popfront: normal behavior --> removing front item" << std::endl;

    //set to empty string
    head_->val[head_->first] == "";

    //increment first
    head_->first++;

    //decrement size
    size_--;
  }

}

std::string const & ULListStr::back() const
{
  //go to tails last item
  return tail_->val[tail_->last-1];
}


std::string const & ULListStr::front() const
{
  //go to heads first item
  return head_->val[head_->first];
}



void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == nullptr){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == nullptr){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == nullptr){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{

  while(head_ != nullptr){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = nullptr;
  size_ = 0;
}

//returns pointer to the item at ith value in the entire list
// if loc id valid, NULL otherwise
std::string* ULListStr::getValAtLoc(size_t loc) const
{
  //invalid location
  if ( (loc < 0) || (loc > size_))
  {
    return nullptr;
  }

  Item* temp = head_;
  size_t currentIndex;
  currentIndex = temp->first;

  //count towards loc
  for (size_t i = 0; i < loc; i++)
  {
    //jump to next node
    if (currentIndex == ARRSIZE-1) //at end
    {
      temp = temp->next;
      currentIndex = temp->first;
    }
    else { //if no jump needed just increment current index
      //currentIndex of temp
      currentIndex++;
    }
    
  }
  std::cout << temp->val[currentIndex] << std::endl;
  std::cout << currentIndex << std::endl;
  return &(temp->val[currentIndex]);

}
