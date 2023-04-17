#include <iostream>
#include "Leaf.h"
#include "Stem.h"

Stem::Stem()
{
  value = 0;
  front = nullptr;
  back = nullptr;
  frequency = 0;
}

Stem::~Stem()
{
  Leaf *currLeafptr = front;
  while (currLeafptr != nullptr)
  {
    Leaf *temp = currLeafptr;
    currLeafptr = currLeafptr->next;
    delete temp;
  }
}

bool Stem::insert(int value)
{
  if (front == nullptr)
  { // no leaves in stem
    Leaf *newLeaf = new Leaf();
    newLeaf->value = value;
    newLeaf->count = 1;
    newLeaf->next = nullptr;
    front = newLeaf;
    back = newLeaf;
    frequency += 1;
    return true;
  }
  else
  {
    Leaf *currLeaf = front;

    bool foundFlag = false;
    while (currLeaf != nullptr)
    {
      if (currLeaf->value == value)
      {
        foundFlag = true;
        break;
      }
      currLeaf = currLeaf->next;
    }
    if (foundFlag == true)
    { // if there already is leaf ++ count
      currLeaf->count += 1;
      frequency += 1;
      return true;
    }
    else
    {
      Leaf *newLeaf = new Leaf();
      newLeaf->value = value;
      newLeaf->count = 1;
      newLeaf->next = nullptr;
      currLeaf = front;

      while (currLeaf != nullptr)
      {
        if (currLeaf == front && currLeaf->value > value)
        { // case 1: in front
          newLeaf->next = front;
          front = newLeaf;
          frequency += 1;
          return true;
        }
        else if (currLeaf == back && currLeaf->value < value)
        { // case 2: in back
          back->next = newLeaf;
          newLeaf->next = nullptr;
          back = newLeaf;
          frequency += 1;
          return true;
        }
        else if (currLeaf->value < value && currLeaf->next->value > value)
        { // case 3: in middle
          newLeaf->next = currLeaf->next;
          currLeaf->next = newLeaf;
          frequency += 1;
          return true;
        }
        currLeaf = currLeaf->next;
      }
    }
  }
  return false;
}

// return true is a leaf is deleted
bool Stem::remove(int target) // update to check for count for > 1 and then decriment count, otherwise remove leaf, also update frequency
{
  Leaf *currLeaf = front;
  Leaf *prevLeaf = nullptr;
  while (currLeaf != nullptr && currLeaf->value != target)
  {
    prevLeaf = currLeaf;
    currLeaf = currLeaf->next;
  }

  if (currLeaf == nullptr)
  { // target not found in this stem
    return false;
  }
  else if (currLeaf->count > 1)
  {
    currLeaf->count -= 1;
    frequency -= 1;
    return true;
  }
  else if (prevLeaf == nullptr)
  { // target is in first leaf
    if (front == back)
    { // target is only leaf
      front = nullptr;
      back = nullptr;
    }
    else
    {
      front = front->next;
    }
    delete currLeaf;
    frequency -= 1;
    return true;
  }
  else if (currLeaf == back)
  { // target is in last leaf
    back = prevLeaf;
    prevLeaf->next = nullptr;
    delete currLeaf;
    frequency -= 1;
    return true;
  }
  else
  { // target is in middle
    prevLeaf->next = currLeaf->next;
    delete currLeaf;
    frequency -= 1;
    return true;
  }
  return true;
}

// Don't modify
std::ostream &operator<<(std::ostream &out, const Stem &x)
{
  out << x.value << " | ";
  Leaf *CURLEAF_ptr = x.front;

  while (CURLEAF_ptr != nullptr)
  {
    out << *CURLEAF_ptr << " ";
    CURLEAF_ptr = CURLEAF_ptr->next;
  }
  out << std::endl;

  return out;
}
