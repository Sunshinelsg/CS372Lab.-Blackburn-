//
// File:   receiptbag.hpp
// Author: Your Glorious Instructor
// Purpose:
// Implement the Bag ADT with receipts.
//
#pragma once
#include <iostream>

#include <vector>

template <typename Thing>
class ReceiptBag {
private:
  std::vector<Thing> bagContents;
  std::vector<int> bagReceipts; 
public:
  int insert(Thing aThing) {
    int index = 0;
    int receipt = 0;
    int numberItemsInBag = bagReceipts.size();
    while ((index < numberItemsInBag - 1) && (bagReceipts[index] != 0)) {
      index++;
    }
    if (index == numberItemsInBag - 1) {
      bagContents.push_back(aThing);
      // Just use the index of the thing as receipt
      receipt = numberItemsInBag - 1;
      bagReceipts.push_back(receipt);
    }
    else {
      bagContents[index] = aThing;
      receipt = index;
    }
    return receipt;
  }
  
  Thing & pop() {
    int itemsInBag = bagContents.size();
    Thing theThingBeingPopped = bagContents[itemsInBag - 1];
    bagReceipts[itemsInBag - 1] = 0;
  }

  Thing & pop(int receipt) {
    Thing  theThingBeingPopped;  //TODO: address initialization               )
    int i = bagContents.size();
    while ((i > 0) && (bagReceipts[i] != receipt)) {
        if (bagReceipts[i] == receipt) {
          theThingBeingPopped = bagContents[i];
          bagReceipts[i] = 0;
        }
    }
    return theThingBeingPopped;
  }

  int size() {
    return bagContents.capacity();
  }

  int count() {
    return bagContents.size();
  }

  int count(Thing theThing) {
    return std::count(bagContents.begin(), bagContents.end(), theThing);
  }
};
