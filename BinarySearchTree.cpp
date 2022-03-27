//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Jessica Kilbourne, CS 260, 2/23/2020, Project 6-2 (binary search trees)
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Binary Search Tree in C++, Ansi-style
//============================================================================

#include <iostream>
#include <time.h>
#include <string>
#include "CSVparser.hpp"
#include <algorithm>
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
    Bid() {
        amount = 0.0;
    }
};

// FIXME (1): Internal structure for tree node
struct Node {
	Bid bid;				// variable to hold bid for node
	Node* left;				// node pointer for left nodes in the left subtrees
	Node* right;			// node pointer for right nodes in the right subtrees

	Node() {				// default constructor, whenever a node is constructed, initialize:
		left = nullptr;		// set left node to null pointer
		right = nullptr;	// set right node to null pointer
	}

	Node(Bid aBid) : Node() {	// constructor initialized with bid
		this->bid = aBid;		// referring to the current instance, construct node initialized with a bid
	}
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Bid bid);
    void inOrder(Node* node);
    Node* removeNode(Node* node, string bidId);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void Insert(Bid bid);
    void Remove(string bidId);
    Bid Search(string bidId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // initialize housekeeping variables (root)
	root = nullptr;		// initialize root node to null pointer
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
	this->inOrder(root);			// call inOrder passing it root
}
/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid bid) {
    // FIXME (2a) Implement inserting a bid into the tree
	if (root == nullptr) {			// if there's nothing in the tree
		root = new Node(bid);		// assign root to be a new node, which calls construct passing it a bid
	}
	else {							// else there is a existing root node
		this->addNode(root, bid);	// add node to root passing given bid to recursive addNode construct
	}
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string bidId) {
    // FIXME (4a) Implement removing a bid from the tree
	this->removeNode(root, bidId);
}

/**
 * Search for a bid
 */
Bid BinarySearchTree::Search(string bidId) {
    // FIXME (3) Implement searching the tree for a bid
	Node* current = root;						// make root node the current node pointer, and start searching from the root

	// keep looping downwards until bottom reached or bid is found
	while (current != nullptr) {
		// if current node matched, return it
		if (current->bid.bidId.compare(bidId) == 0) {
			return current->bid;				// return current node's bid
		}
		// if bid is smaller than current then traverse left
		if (bidId.compare(current->bid.bidId) < 0) {
			current = current->left;			// traverse left until bid is found or not found
		}
		// else its larger
		else {
			current = current->right;			// traverse right until bid is found or not found
		}
	}
	Bid bid;  		// create an initialized bid instance
    return bid;		// return empty bid
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(Node* node, Bid bid) {
    // FIXME (2b) Implement inserting a bid into the tree
	if (node->bid.bidId.compare(bid.bidId) > 0) {		// if new node bidId is larger than bidId, add to left subtree
		if (node->left == nullptr) {   					// if nodes left pointer is null
			node->left = new Node(bid);					// insert new node which becomes the left pointer
		}
		else {
			this->addNode(node->left, bid);				// traverse to next left node (repeat till at bottom left node)
		}
	}
	else {		// add to right subtree
		if (node->right == nullptr) {   					// if nodes right pointer is null
			node->right = new Node(bid);					// instert new node which becomes the right pointer
		}
		else {
			this->addNode(node->right, bid);				// traverse to next right node (repeat till at bottom right node)
		}
	}
}
void BinarySearchTree::inOrder(Node* node) {				// print with inOrder traversal starting at the root passed in
	if (node != nullptr) {									// if node isn't null
		inOrder(node->left);								// traverse left side recursively printing nodes
	    cout << node->bid.bidId << ": "
	    	 << node->bid.title << " | "
			 << node->bid.amount << " | "
	         << node->bid.fund << endl;						// prints center node first before printing the rest of the right side
		inOrder(node->right);								// traverse right side recursively printing nodes
	}
}

Node* BinarySearchTree::removeNode(Node* node, string bidId) {
	// if this node is null then return (avoid crashing)
	if (node == nullptr) {
		return node;
	}
	// recurse down left or right subtree
	if (bidId.compare(node->bid.bidId) < 0) {  				// if string bid given is smaller than the bid,
		node->left = removeNode(node->left, bidId);			// go down left side
	} else if (bidId.compare(node->bid.bidId) > 0) {		// if string given is larger than the bid,
		node->right = removeNode(node->right, bidId);		// go down right side
	} else {															// else no children (we're on leaf node)
		if (node->left == nullptr && node->right == nullptr) {			// if this node's left and right is null,
			delete node;												// then delete node
			node = nullptr;												// initialize node to null
		}
		// case where one child to the left, copy/delete old left node
		else if  (node->left != nullptr && node->right == nullptr) {	// otherwise, if this node's left isn't null, and its right is null
			Node* temp = node;											// copy this node to be adopted by new parent
			node = node->left;											// set node to be left node of new parent
			delete temp;												// delete temp copy
		}
		// case where one child to the right, copy/delete old right node
		else if  (node->right != nullptr && node->left == nullptr) {	// otherwise, if this node's right isn't null, and its left is null
			Node* temp = node;											// copy this node to be adopted by new parent
			node = node->right;											// set node to be right node of new parent
			delete temp;												// delete temp copy
		}
		// case where two children
		else {
			Node* temp = node->right;									// else create temp node pointer to point to node's right
			while (temp->left != nullptr) {								// while left node is not null
				temp = temp->left;										// use temp to go left branch until you find removal node
			}
			node->bid = temp->bid;										// copy bid to temp node pointer, storing bid for left node
			node->right = removeNode(node->right, temp->bid.bidId);		// remove successor from to right subtree, pull up right ...
		}																// node (to become parent with successors) using temp copy
	}
	return node;														// return this node
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
void loadBids(string csvPath, BinarySearchTree* bst) {
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
            bst->Insert(bid);
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

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst;

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
            bst = new BinarySearchTree();

            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bst);

            //cout << bst->Size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bst->InOrder();
            break;

        case 3:
            ticks = clock();

            bid = bst->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
            	cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 4:
            bst->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

	return 0;
}
