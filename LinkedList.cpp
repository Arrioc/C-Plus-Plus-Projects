//============================================================================
// Name        : LinkedList.cpp
// Author      : Jessica Kilbourne, CS 260, 1/26/20, Lab 3-2
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Lab 3-3 Lists and Searching
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

#include <cstddef>
using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);


// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {        //** constructor- automatically called when you create an new instance. Sets amount to 0.
        amount = 0.0;
    }
};

//============================================================================
// Linked-List class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a linked-list.
 */
class LinkedList {

private:
    // FIXME (1): Internal structure for list entries, housekeeping variables
	struct Node {   //** store subitems: (data type, member name)
		Bid bid;    //** create struct subitems/data member Bid and Node*
		Node* next; //** node pointer

		// default constructor, for creation of a Node instance
		Node() {
			next = nullptr;      //** automatically next initializes next pointer to nullptr (0 or empty)
		}

		// Initialize a node with a bid
		Node(Bid abid) {
			bid = abid;          // save bid
			next = nullptr;      //** initializes 'next' pointer to nullptr or 0 (empty)
		}
	};

	Node* head;                  //** pointer points to head
	Node* tail;                  //** pointer points to tail
	int size = 0;                //** assign and initialize local integer variable called size (allowing me to ++, -- size)

public:
    LinkedList();
    virtual ~LinkedList();
    void Append(Bid bid);
    void Prepend(Bid bid);
    void PrintList();
    void Remove(string bidId);
    Bid Search(string bidId);
    int Size();
};

/**
 * Default constructor
 */
LinkedList::LinkedList() {
    // FIXME (2): Initialize housekeeping variables
	head = tail = nullptr;  //** have head and tail point to nullptr (which is 0)
}

/**
 * Destructor
 */
LinkedList::~LinkedList() {
}

/**
 * Append a new bid to the end of the list
 */
void LinkedList::Append(Bid bid) {     //** when called, append method takes the bid and creates new node instance with
                                       // bid and points to it, for 2 cases empty list or not
    // FIXME (3): Implement append logic
	Node* node = new Node(bid); //** New node instance pointer allocates memory for heap, returning address to object

	if (head == nullptr) {      //** if there's nothing there yet...
		head = tail = node;     //** appoint new node instance as head and tail
	}
	else {
		if (tail != nullptr) {  //** If the list has a tail with data in it...
			tail->next = node;  //** Get last node where next pointer is null and have it point to new node
		}
	}
	// **new node is always the tail
	tail = node; // **point tail to new node
	size++;
}

/**
 * Prepend a new bid to the start of the list
 */
void LinkedList::Prepend(Bid bid) {
    // FIXME (4): Implement prepend logic
	Node* node = new Node(bid);  //** Create a node from our bid that was passed in

	if (head != nullptr) {       //** If the list has a head with data in it...
		node->next = head;       //** Next pointer points to what was already in original head
	}
	head = node;                 //** Assign new node as head
	size++;                      //** Increase list count
}

/**
 * Simple output of all bids in the list
 */
void LinkedList::PrintList() {
    // FIXME (5): Implement print logic
	Node* current = head;         //** Create node pointer called current, set to be head

	// loop over each node looking for a match                                  //** loop initialises memory for access
	while (current != nullptr) {                                                //** while current is not null.. (for if we dont yet have any entries in list)
		cout << current->bid.bidId << ": " << current->bid.title << " | "       //** go to bid being pointed to and print out node data
			 << current->bid.amount << " | " << current->bid.fund << endl;
		current = current->next;                                                //** Set current pointer to point at next node
	}
}

/**
 * Remove a specified bid
 *
 * @param bidId The bid id to remove from the list
 */
void LinkedList::Remove(string bidId) {
    // FIXME (6): Implement remove logic
	if (head != nullptr) {                         //** If head is not nullptr (0)..and..
		if (head->bid.bidId.compare(bidId) == 0) { //** If head's the only one in list, next pointer is nullptr, if it points to something and matches...
			Node* tempNode = head->next;           //** Make tempNode point to the node beyond the node to be removed
			delete head;                           //** Delete the head

			head = tempNode;                       //** Make the new head pointed to the one that was beyond removed head
		}
	}

	Node* current = head;                          //** Create node pointer called current, set to be head

	// **loop over each node looking for a match
	while (current->next != nullptr) {                     //** While the next pointer isn't null (not at end of list)
		if (current->next->bid.bidId.compare(bidId) == 0){ //** Then check the next pointed to node's bid
			Node* tempNode = current->next;   //** If it matches, save the next node (the one to be removed)
			current->next = tempNode->next;   //** Make current node point beyond the next node (to be removed)
			delete tempNode;                  //** Now delete temp node

			size--;                           //** Reduce list count

			return;
		}
			current = current->next;          //** Otherwise make current pointer go to next bid and repeat loop
	}
}

/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid LinkedList::Search(string bidId) {
    // FIXME (7): Implement search logic
	Node* current = head;

	// **loop over each node looking for a match
	while (current != nullptr) {                     //** Initializes current pointer to head, while its not null
		if (current->bid.bidId.compare(bidId) == 0){ //** If current pointer's bidId = the one we are searching for
			return current->bid;                     //** Then return that bid
		}
		current = current->next;                     //** Otherwise make current pointer go to next bid and repeat (loop)
	}
	return Bid();                                    //** Once end is reached and no match found, return Bid() which
}                                                    //** gets sent to case 4 'else' branch.

/**
 * Returns the current size (number of elements) in the list
 */
int LinkedList::Size() {
    return size;
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount
         << " | " << bid.fund << endl;
    return;
}

/**
 * Prompt user for bid information
 *
 * @return Bid struct containing the bid info
 */
Bid getBid() {
    Bid bid;

    cout << "Enter Id: ";
    cin.ignore();
    getline(cin, bid.bidId);

    cout << "Enter title: ";
    getline(cin, bid.title);

    cout << "Enter fund: ";
    cin >> bid.fund;

    cout << "Enter amount: ";
    cin.ignore();
    string strAmount;
    getline(cin, strAmount);
    bid.amount = strToDouble(strAmount, '$');

    return bid;
}

/**
 * Load a CSV file containing bids into a LinkedList
 *
 * @return a LinkedList containing all the bids read
 */
void loadBids(string csvPath, LinkedList *list) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // initialize a bid using data from current row (i)
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            // cout << bid.bidId << ": " << bid.title << " | " << bid.fund << " | " << bid.amount << endl;

            // add this bid to the end
            list->Append(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 *
 * @param arg[1] path to CSV file to load from (optional)
 * @param arg[2] the bid Id to use when searching the list (optional)
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98109";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        bidKey = "98109";
    }

    clock_t ticks;

    LinkedList bidList;

    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Enter a Bid" << endl;
        cout << "  2. Load Bids" << endl;
        cout << "  3. Display All Bids" << endl;
        cout << "  4. Find Bid" << endl;
        cout << "  5. Remove Bid" << endl;
        /*cout << "  6. Prepend Bid" << endl;*/  //** used to test prepend, can be removed
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            bid = getBid();
            bidList.Append(bid);
            displayBid(bid);

            break;

        case 2:
            ticks = clock();

            loadBids(csvPath, &bidList);

            cout << bidList.Size() << " bids read" << endl;

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 3:
            bidList.PrintList();

            break;

        case 4:
            ticks = clock();

            bid = bidList.Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
            	cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 5:
            bidList.Remove(bidKey);

            break;

        /*case 6:                 // **added for testing prepend, was successful, remove?
            bid = getBid();
            bidList.Prepend(bid);
            displayBid(bid);

            break; */
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
