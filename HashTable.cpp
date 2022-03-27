//============================================================================
// Name        : HashTable.cpp
// Author      : Jessica Kilbourne, CS 260, 2/6/20, Lab 5-2
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <algorithm>
#include <climits>
#include <iostream>
#include <string> // atoi
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

const unsigned int DEFAULT_SIZE = 179;

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

//============================================================================
// Hash Table class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a hash table with chaining.
 */
class HashTable {

private:
    // FIXME (1): Define structures to hold bids
	struct Node {
		Bid bid;
		unsigned key;  // a key value for our hash (which can't be negative, thus unsigned)
		Node* next;    // a pointer to our next node for implementing chaining

		//default constructor
		Node() {               // a constructor for class Node
			key = UINT_MAX;    // c++ for largest unsigned integer maximum value, (useful to test key to know if its been used or not)
			next = nullptr;    // set next to be our null pointer constant
		}

		//initialize with a bid
		Node(Bid aBid) : Node() {  // now we are going to take a bid, invokes default constructor before loading/storing values
			bid = aBid;
		}

		//initialize with a bid and a key (clean and concise tactic)
		Node(Bid aBid, unsigned aKey) : Node(aBid) {  //call node for 2 parameters: aKey and aBid (initializing values), before executing code inside constructor
			key = aKey;								  //add key to constructor
		}
	};

	vector<Node> nodes;                         // vector that holds nodes

	unsigned tableSize = DEFAULT_SIZE;          // allows change to table size

    unsigned int hash(int key);

public:
    HashTable();               // hash table constructor
    HashTable(unsigned size);  // hash table constructor with parameters
    virtual ~HashTable();      // has table destructor
    void Insert(Bid bid);      // insert method that takes a bid (struct)
    void PrintAll();           // will iterate through bids
    void Remove(string bidId); // remove method
    Bid Search(string bidId);  // search method
};

/**
 * Default constructor
 */
HashTable::HashTable() {
    // FIXME (2): Initialize the structures used to hold bids
	nodes.resize(tableSize);                   // resize table size for hash table nodes
}
HashTable::HashTable(unsigned size) {          // initiate hashtable constructor with size
	this->tableSize = size;                    // save table size
	nodes.resize(tableSize);                   // resize table size for hash table nodes
}

/**
 * Destructor
 */
HashTable::~HashTable() {
    // FIXME (3): Implement logic to free storage when class is destroyed
	nodes.erase(nodes.begin());     // call erase from begin method, erases specified elements from container
}

/**
 * Calculate the hash value of a given key.
 * Note that key is specifically defined as
 * unsigned int to prevent undefined results
 * of a negative list index.
 *
 * @param key The key to hash
 * @return The calculated hash
 */
unsigned int HashTable::hash(int key) {
    // FIXME (4): Implement logic to calculate a hash value
	return key % tableSize;           // return an unsigned integer when has fn is called, modulo division is performed for key value we are going to pass in
}

/**
 * Insert a bid
 *
 * @param bid The bid to insert
 */
void HashTable::Insert(Bid bid) {
    // FIXME (5): Implement logic to insert a bid
	unsigned key = hash(atoi(bid.bidId.c_str()));      // set key to called hash method calculating key for this bid and converts string object to string using C string method atoi
													   // ... take asci string and turn into integer (using built in C+ method atoi)
	// try and retrieve node using the key
	Node* oldNode = &(nodes.at(key));                  // try to look (point) to old node address using index into the vector (calculated key value)

	// if no entry found for this key
	if (oldNode == nullptr) {
		Node* newNode = new Node(bid, key);            // create new instance of node with a bid and new calculated key
		nodes.insert(nodes.begin() + key, (*newNode)); // insert node into the vector, begin with this position plus the offset and pass node's address
	} else {										   // otherwise, if node is found...
		// else node is found
		if (oldNode->key == UINT_MAX) {			   	   // if node has no entries (if not used)... (Note: old node key is UINT_MAX, meaning its not been used)
			oldNode->key = key;						   // assign key we just created to node
			oldNode->bid = bid;						   // assign bid we just created to node
			oldNode->next = nullptr;				   // assign next pointer to null aka initialize node
		} else {
			// otherwise key isn't UINT_MAX- the node has a value in it
			while (oldNode->next != nullptr) {         // conduct chaining by finding next open node: from old node, if the next node is not null...
				oldNode = oldNode->next;			   // go to next node, loop until next IS null
			}
			oldNode->next = new Node(bid, key);		   // create new node instance for null node, make old node point to new node at end of list
		}
	}
}

/**
 * Print all bids
 */
void HashTable::PrintAll() {
    // FIXME (6): Implement logic to print all bids

    for (Node node : nodes) {																	  //iterate through nodes
    	cout << "Key " << node.key << ": " << node.bid.bidId << ": " << node.bid.title << " | "   //print node data
    		 << node.bid.amount << " | " << node.bid.fund << endl;
    }                                                                                             //missing if loop that could include only nodes with elements: if(node.key != nullptr)...
}                                                                                                 //also missing for loop that iterates through bucket-lists to print elements with same bucket

/**
 * Remove a bid
 *
 * @param bidId The bid id to search for
 */
void HashTable::Remove(string bidId) {
    // FIXME (7): Implement logic to remove a bid

	// paas bid into key
	unsigned key = hash(atoi(bidId.c_str()));        // call hash function to get the key
	nodes.erase(nodes.begin() + key);				 // erase key, new offset is the beginning of the nodes plus key index
}

/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid HashTable::Search(string bidId) {
    Bid bid;

    // FIXME (8): Implement logic to search for and return a bid

    //calculate the key for this bid, giving index into vector
	unsigned key = hash(atoi(bidId.c_str()));

	// try and retrieve node using the key, use nodes 'at' fn to grab element, returning address as pointer
	Node* node = &(nodes.at(key));

	//if no entry found
	if (node == nullptr || node->key == UINT_MAX) {     // If node is nullptr or node key equals UINT_MAX (is initialized unused node)
		return bid;    									// then return empty bid
	}

	// if node found that matches key
	if (node != nullptr && node->key != UINT_MAX        // If node isn't nullptr, node key isn't UINT_MAX (isn't newly initialized
			&& node->bid.bidId.compare(bidId) == 0) {   // unused node) and node's bidId is equal to bidId passed
		return node->bid;    							// then return the bid we searched for
	}

	// walk the linked list to find the match
	while (node != nullptr) {													// while key isn't empty (not null)
		if (node->key != UINT_MAX && node->bid.bidId.compare(bidId) == 0) {		// if it matches
			return node->bid;													// return matched key
		}
		node = node->next;														// otherwise try next node, repeat till found or not found
	}
    return bid;																	// return empty bid if match not found
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, HashTable* hashTable) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            hashTable->Insert(bid);
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
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, searchValue;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        searchValue = "98109";
        break;
    case 3:
        csvPath = argv[1];
        searchValue = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        searchValue = "98109";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a hash table to hold all the bids
    HashTable* bidTable;

    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            bidTable = new HashTable();

            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bidTable);

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bidTable->PrintAll();
            break;

        case 3:
            ticks = clock();

            bid = bidTable->Search(searchValue);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
                cout << "Bid Id " << searchValue << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 4:
            bidTable->Remove(searchValue);
            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
