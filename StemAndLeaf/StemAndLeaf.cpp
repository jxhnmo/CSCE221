#include <iostream>
#include "StemAndLeaf.h"

int StemAndLeaf::getLeafUnit() const
{
  return leafUnit;
}

void StemAndLeaf::setLeafUnit(int leafUnit)
{
  this->leafUnit = leafUnit;
}

int StemAndLeaf::getStemUnit() const
{
  return stemUnit;
}

void StemAndLeaf::setStemUnit(int stemUnit)
{
  this->stemUnit = stemUnit;
}

StemAndLeaf::StemAndLeaf()
{
  head = nullptr;
  leafUnit = 1;
  stemUnit = 10; // check these
}

StemAndLeaf::~StemAndLeaf()
{ // deletes each stem node
  Stem *currStem = head;
  while (currStem != nullptr)
  {
    Stem *temp = currStem;
    currStem = currStem->next;
    delete temp;
  }
}

void StemAndLeaf::addTerm(int term)
{
  int stem = term / stemUnit;
  int leaf = term % stemUnit;

  // check to see if new stem is needed infront of head
  if (head == nullptr || head->value > stem)
  {
    Stem *newStem = new Stem();
    newStem->value = stem;
    newStem->insert(leaf);
    newStem->next = head;
    head = newStem;

    // std::cout << "deez" << std::endl;
  }
  else
  {
    Stem *currStem = head;
    while (currStem->next != nullptr && currStem->next->value <= stem)
    {
      currStem = currStem->next;
    }

    if (currStem->value == stem)
    {
      // std::cout << "inserting 6\n"; // TESTING TESTING TESTING
      currStem->insert(leaf);
      // std::cout << "post insert\n"; // TESTING TESTING TESTING
    }
    else
    {
      Stem *newStem = new Stem();
      newStem->value = stem;
      newStem->insert(leaf);
      newStem->next = currStem->next;
      currStem->next = newStem;
    }
    // std::cout << "wam" << std::endl;
  }
}

bool StemAndLeaf::removeTerm(int term)
{
  int stem = term / getStemUnit();
  int leaf = term % getStemUnit();

  // looks for stem that contains current stem value
  Stem *currStem = head;
  Stem *prevStem = nullptr;

  while (currStem != nullptr && currStem->value < stem)
  {
    prevStem = currStem;
    currStem = currStem->next;
  }

  // if stem is not found, return false
  if (currStem == nullptr || currStem->value != stem)
  {
    return false;
  }

  bool removed = currStem->remove(leaf);

  // if stem node's leaf list is empty, remove stem node
  if (currStem->frequency == 0)
  {
    if (prevStem == nullptr)
    {
      head = currStem->next;
    }
    else
    {
      prevStem->next = currStem->next;
    }

    if (currStem == tail)
    {
      tail = prevStem;
    }

    delete currStem;
  }

  return removed;
}

// Don't modify
std::ostream &operator<<(std::ostream &out, const StemAndLeaf &x)
{
  // needs to go through the StemAndLeaf, one stem, then all leaves, then back to the next stem and it's leaves, and continue
  Stem *CURSTEM_ptr = x.head;
  while (CURSTEM_ptr != nullptr)
  {
    out << *CURSTEM_ptr;
    CURSTEM_ptr = CURSTEM_ptr->next;
  }

  return out;
}
