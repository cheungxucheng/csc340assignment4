//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** ADT bag: Link-based implementation.
	 @file LinkedBag.cpp */

#include "LinkedBag.h"
#include "Node.h"
#include <cstddef>
#include <type_traits>

//   SORTING ----------------------------------------------------
template<class ItemType>
void LinkedBag<ItemType>::sort(int method){
	if (itemCount <= 1)
		return;
	
	if (method == 0){
		// update function call if you change the prototype. 
		mergeSort(headPtr);
	}else{
		// for EXTRA CREDIT, update function call if you change the prototype.
		// If you do NOT implement quickSort, NO action needed here
		quickSort(headPtr); 
	}
}

//TO DO: implement merge sort and change its prototype if you need to.

// get middle of list
template<class ItemType>
Node<ItemType>* LinkedBag<ItemType>::findMiddle(Node<ItemType>* head) {
	Node<ItemType>* slow = head;
	Node<ItemType>* fast = head;

	// slow moves half as fast as fast
	while (fast != nullptr && fast->getNext() != nullptr && fast->getNext()->getNext() != nullptr) {
		slow = slow->getNext();
		fast = fast->getNext()->getNext();
	}

	return slow;
}

template<class ItemType>
Node<ItemType>* LinkedBag<ItemType>::mergeLists(Node<ItemType>* left, Node<ItemType>* right) {
	// base cases
	if (left == nullptr) {
		return right;
	}

	if (right == nullptr) {
		return left;
	}

	// add one
	if (left->getItem() < right->getItem()) {
		left->setNext(mergeLists(left->getNext(), right));
		return left;
	} else {
		right->setNext(mergeLists(left, right->getNext()));
		return right;
	}
}

template<class ItemType>
Node<ItemType>* LinkedBag<ItemType>::mergeSort(Node<ItemType>* head) {
	// Base case (0 or 1 elements)
	if (head == nullptr || head->getNext() == nullptr) {
		return head;
	}

	Node<ItemType>* mid = findMiddle(head);

	// split list in two at midpoint
	Node<ItemType>* leftHead = head;
	Node<ItemType>* rightHead = mid->getNext();
	mid->setNext(nullptr);

	// recurse
	leftHead = mergeSort(leftHead);
	rightHead = mergeSort(rightHead);

	// merge
	return mergeLists(leftHead, rightHead);
}

//Extra Credit -- TO DO: implement quick sort and change its prototype 
//                       if you need to.
template<class ItemType>
Node<ItemType>* LinkedBag<ItemType>::quickSort(Node<ItemType>* head) {
	// Base case (0 or 1 elements)
	if (head == nullptr || head->getNext() == nullptr) {
		return head;
	}

	// find last node
	Node<ItemType>* pivot = head;
	while (pivot->getNext() != nullptr) {
		pivot = pivot->getNext();
	}

	// don't know if the current head is less than or greater than the pivot,
	// so need to choose a new head
	Node<ItemType>* newHead = nullptr;

	// partition list
	Node<ItemType>* cur = head;
	Node<ItemType>* prev = nullptr;
	Node<ItemType>* end = pivot;
	while (cur != pivot) {
		if (cur->getItem() < pivot->getItem()) {
			if (newHead == nullptr) {
				newHead = cur;
			}

			prev = cur;
			cur = cur->getNext();
		} else {
			// remove cur from list
			if (prev != nullptr) {
				prev->setNext(cur->getNext());
			}

			Node<ItemType>* next = cur->getNext();

			// add to end
			cur->setNext(nullptr);
			end->setNext(cur);
			end = cur;
			cur = next;
		}
	}

	// case where everything was bigger than the pivot
	if (newHead == nullptr) {
		newHead = pivot;
	}

	// list is now newHead to end
	// split list before pivot
	Node<ItemType>* split = newHead;
	while (split->getNext() != pivot) {
		split = split->getNext();
	}

	split->setNext(nullptr);

	// sort both sides
	newHead = quickSort(newHead);
	pivot = quickSort(pivot);

	// connect lists again
	cur = newHead;
	while (cur->getNext() != nullptr) {
		cur = cur->getNext();
	}
	cur->setNext(pivot);

	return newHead;
}
// --------------------------------------------------------------

template<class ItemType>
LinkedBag<ItemType>::LinkedBag() : headPtr(nullptr), itemCount(0){
}  // end default constructor

template<class ItemType>
LinkedBag<ItemType>::LinkedBag(const LinkedBag<ItemType>& aBag){
	itemCount = aBag.itemCount;
	Node<ItemType>* origChainPtr = aBag.headPtr;  // Points to nodes in original chain
	
	if (origChainPtr == nullptr)
		headPtr = nullptr;  // Original bag is empty
	else
	{
		// Copy first node
		headPtr = new Node<ItemType>();
		headPtr->setItem(origChainPtr->getItem());
		
		// Copy remaining nodes
		Node<ItemType>* newChainPtr = headPtr;		// Points to last node in new chain
		origChainPtr = origChainPtr->getNext();	  // Advance original-chain pointer
		
		while (origChainPtr != nullptr)
		{
			// Get next item from original chain
			ItemType nextItem = origChainPtr->getItem();
				  
			// Create a new node containing the next item
			Node<ItemType>* newNodePtr = new Node<ItemType>(nextItem);
			
			// Link new node to end of new chain
			newChainPtr->setNext(newNodePtr);
			
			// Advance pointer to new last node
			newChainPtr = newChainPtr->getNext();

			// Advance original-chain pointer
			origChainPtr = origChainPtr->getNext();
		}  // end while
		
		newChainPtr->setNext(nullptr);				  // Flag end of chain
	}  // end if
}  // end copy constructor

template<class ItemType>
LinkedBag<ItemType>::~LinkedBag(){
	clear();
}  // end destructor

template<class ItemType>
bool LinkedBag<ItemType>::isEmpty() const{
	return itemCount == 0;
}  // end isEmpty

template<class ItemType>
int LinkedBag<ItemType>::getCurrentSize() const{
	return itemCount;
}  // end getCurrentSize

template<class ItemType>
bool LinkedBag<ItemType>::add(const ItemType& newEntry){
	// Add to beginning of chain: new node references rest of chain;
	// (headPtr is null if chain is empty)		  
	Node<ItemType>* nextNodePtr = new Node<ItemType>();

	nextNodePtr->setItem(newEntry);
	nextNodePtr->setNext(headPtr);  // New node points to chain
	headPtr = nextNodePtr;			 // New node is now first node
	itemCount++;
	
	return true;
}  // end add

template<class ItemType>
std::vector<ItemType> LinkedBag<ItemType>::toVector() const{
	std::vector<ItemType> bagContents;
	Node<ItemType>* curPtr = headPtr;
	int counter = 0;
	while ((curPtr != nullptr) && (counter < itemCount))
	{
		bagContents.push_back(curPtr->getItem());
		curPtr = curPtr->getNext();
		counter++;
	}  // end while
	
	return bagContents;
}  // end toVector

template<class ItemType>
bool LinkedBag<ItemType>::remove(const ItemType& anEntry){
	Node<ItemType>* entryNodePtr = getPointerTo(anEntry);
	bool canRemoveItem = !isEmpty() && (entryNodePtr != nullptr);
	if (canRemoveItem){
		// Copy data from first node to located node
		entryNodePtr->setItem(headPtr->getItem());
		
		// Delete first node
		Node<ItemType>* nodeToDeletePtr = headPtr;
		headPtr = headPtr->getNext();
		
		// Return node to the system
		nodeToDeletePtr->setNext(nullptr);
		delete nodeToDeletePtr;
		nodeToDeletePtr = nullptr;
		
		itemCount--;
	} // end if
	
	return canRemoveItem;
}  // end remove

template<class ItemType>
bool LinkedBag<ItemType>::removeAlt(const ItemType& anEntry){
	Node<ItemType>* prev = headPtr;
	Node<ItemType>* cur = headPtr;
	bool found = false;

	while((cur != nullptr) && !found){
		found = (*(cur->getItem()) == *anEntry);
		if (!found){
			prev = cur;
			cur = cur->getNext();
		}
	}

	if (found){
		prev->setNext(cur->getNext());
		// delete cur->getItem();
		delete cur;
		cur = nullptr;
		itemCount--;
	}

	return found;

}  // end remove

template<class ItemType>
void LinkedBag<ItemType>::clear(){
	Node<ItemType>* nodeToDeletePtr = headPtr;
	while (headPtr != nullptr){
		headPtr = headPtr->getNext();

		// Return node to the system
		nodeToDeletePtr->setNext(nullptr);

		// delete nodeToDeletePtr->getItem(); 
		delete nodeToDeletePtr;
		
		nodeToDeletePtr = headPtr;
	}  // end while
	// headPtr is nullptr; nodeToDeletePtr is nullptr
	
	itemCount = 0;
}  // end clear

template<class ItemType>
int LinkedBag<ItemType>::getFrequencyOf(const ItemType& anEntry) const{
	int frequency = 0;
	int counter = 0;
	Node<ItemType>* curPtr = headPtr;
	while ((curPtr != nullptr) && (counter < itemCount))
	{
		if (anEntry == curPtr->getItem())
		{
			frequency++;
		} // end if
		
		counter++;
		curPtr = curPtr->getNext();
	} // end while
	
	return frequency;
}  // end getFrequencyOf

template<class ItemType>
bool LinkedBag<ItemType>::contains(const ItemType& anEntry) const{
	return (getPointerTo(anEntry) != nullptr);
}  // end contains


// private
// Returns either a pointer to the node containing a given entry 
// or the null pointer if the entry is not in the bag.
template<class ItemType>
Node<ItemType>* LinkedBag<ItemType>::getPointerTo(const ItemType& anEntry) const{
	bool found = false;
	Node<ItemType>* curPtr = headPtr;
	
	while (!found && (curPtr != nullptr))
	{
		if (anEntry == curPtr->getItem())
			found = true;
		else
			curPtr = curPtr->getNext();
	} // end while
	
	return curPtr;
} // end getPointerTo


