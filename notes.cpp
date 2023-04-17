valgrind-- tool = memcheck./ run

                                 Leaf *currLeaf = front;
Leaf *prevLeaf = nullptr;
bool foundFlag = false;

while (currLeaf != nullptr)
{
  if (currLeaf->value == target)
  {
    foundFlag = true;
    break;
  }
  prevLeaf = currLeaf;
  currLeaf = currLeaf->next;
}

if (foundFlag == true)
{
  if (currLeaf->count > 1)
  { // if theres more than 1 then decriment by 1
    currLeaf->count -= 1;
    frequency -= 1;
    return true;
  }
  else
  { // if theres only 1 count of leaf
    if (currLeaf == front)
    { // if its in front
      if (currLeaf == back)
      { // if its the only one
        front == nullptr;
        back == nullptr;
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
    { // if its in back
      back = prevLeaf;
      back->next = nullptr;
      delete currLeaf;
      frequency -= 1;
      return true;
    }
    else
    { // if its in the middle
      prevLeaf->next = currLeaf->next;
      delete currLeaf;
      frequency -= 1;
      return true;
    }
  }
}
else
{
  return false;
}