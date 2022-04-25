#include "Set.h"
#include "SetITerator.h"

//
// For the time complexity analysis, let n be the number of elements in the set.
//

/*
* Time Complexity Analysis
*	Total Time Complexity: θ(1)
*/
Set::Set() {
	sl_list.head = nullptr;
	length = 0;
}

/*
* Time Complexity Analysis
*	BC: θ(1) - when the element is already in the set, being the head of the SLL => only one iteration for the while loop, then return false
*	WC: θ(n) - when the element is not in the set, hence we have n iterations of the while loop
*	AC: O(n)
*	Total Time Complexity: O(n)
*/
bool Set::add(TElem elem) {
	auto current = sl_list.head;
	while (current != nullptr && current->info != elem)
		current = current->next;
	if (current != nullptr) return false;  // this means the element has already been added to the set

	SLLNode* new_node = new SLLNode;
	new_node->next = sl_list.head;
	new_node->info = elem;
	sl_list.head = new_node;
	length++;
	return true;
}

/*
* Time Complexity Analysis
*	BC: θ(1) - when the element is found in the set, on the first position in the SLL (hence, it is the head of the SLL) => only one iteration for the while loop
*	WC: θ(n) - when the element is not in the set, hence we have n iterations of the while loop
*	AC: O(n)
*	Total Time Complexity: O(n)
*/
bool Set::remove(TElem elem) {
	SLLNode* current_node = sl_list.head;
	SLLNode* previous_node = nullptr;

	while (current_node != nullptr && current_node->info != elem) {
		previous_node = current_node;
		current_node = current_node->next;
	}

	if (current_node == nullptr) return false;  // the element was not found in the set

	// the head is deleted
	if (current_node != nullptr && previous_node == nullptr) {
		auto previous_head = sl_list.head;
		sl_list.head = sl_list.head->next;
		delete previous_head;
		length--;
	}  // another element (not the head) is deleted
	else if (current_node != nullptr) {
		previous_node->next = current_node->next;
		delete current_node;
		length--;
	}
	return true;
}

/*
* Time Complexity Analysis
*	Total Time Complexity: θ(n) - we iterate through all the elements no matter what
*/
void Set::filter(Condition cond)
{
	SLLNode* current_node = sl_list.head;
	SLLNode* previous_node = nullptr;

	while (current_node != nullptr) {
		auto next_node = current_node->next;
		if (!cond(current_node->info)) {
			// remove the element
			if (previous_node == nullptr) {
				auto previous_head = sl_list.head;
				sl_list.head = sl_list.head->next;
				delete previous_head;
				length--;
			}
			else {
				previous_node->next = current_node->next;
				delete current_node;
				length--;
			}
		} // don't remove the element => must update the previous element
		else previous_node = current_node;
		current_node = next_node;
	}
}

/*
* Time Complexity Analysis
*	BC: θ(1) - when the element is found in the set, on the first position in the SLL (hence, it is the head of the SLL) => only one iteration for the while loop
*	WC: θ(n) - when the element is not in the set, hence we have n iterations of the while loop
*	AC: O(n)
*	Total Time Complexity: O(n)
*/
bool Set::search(TElem elem) const {
	auto current = sl_list.head;
	while (current != nullptr && current->info != elem)
		current = current->next;
	return current != nullptr;
}

/*
* Time Complexity Analysis
*	Total Time Complexity: θ(1)
*/
int Set::size() const {
	return length;
}

/*
* Time Complexity Analysis
*	Total Time Complexity: θ(1)
*/
bool Set::isEmpty() const {
	return sl_list.head == nullptr;
}

/*
* Time Complexity Analysis
*	Total Time Complexity: θ(n) - we have to delete all the elements of the set
*/
Set::~Set() {
	while (sl_list.head != nullptr) {
		auto current_head = sl_list.head;
		sl_list.head = sl_list.head->next;
		delete current_head;
	}
}

/*
* Time Complexity Analysis
*	Total Time Complexity: θ(1)
*/
SetIterator Set::iterator() const {
	return SetIterator(*this);
}


