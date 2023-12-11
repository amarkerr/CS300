/***********************************************************************************
**                                                                                **
** Student Name: Amanda Kerr                                                      **
** Project Name: CS300Project2.cpp                                                **
** Course: CS300                                                                  **
** Date: 10 December 2023                                                         **
** Description: Data storage for ABCU CS course library                           **
**                                                                                **
***********************************************************************************/




#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>

using namespace std;




/**********************
 *                    *
 * Global definitions * 
 *                    *
 *********************/

//Define a structure to hold course information
struct Course {
	string courseID; //Unique identifier
	string CourseTitle;
	string coursePrereqs;

	Course() {
	}
};

//Internal structure for tree node
struct Node {
	Course course;
	Node* left;
	Node* right;

	//Default constructor
	Node() {
		left = nullptr;
		right = nullptr;
	}

	//Initialize with a course
	Node(Course aCourse) :
		Node() {
		course = aCourse;
	}
};

//Define vector to hold course ID list (to avoid duplicate courses added to bst)
vector<string> courseList;




/*************************
 *                       *
 *  Binary Search Tree   *
 * Class and Definitions *
 *                       *
 ************************/

class BinarySearchTree {

private:
	Node* root;

	void addNode(Node* node, Course course);
	void inOrder(Node* node);
	Node* removeNode(Node* node, string courseID);

public:
	BinarySearchTree();
	virtual ~BinarySearchTree();
	void InOrder();
	void Insert(Course course);
	void Remove(string courseID);
	Course Search(string courseID);
};

//Default constructor
BinarySearchTree::BinarySearchTree() {
	root = nullptr;
}

//Destructor, currently unused
BinarySearchTree::~BinarySearchTree() {

	//If tree is empty
	if (this->root == nullptr) {
		return;
	}

	//Start from root
	Node* current = this->root;


	//Traverse from left to right
	while (current->left != nullptr || current->right != nullptr) {
		if (current->left != nullptr) {
			current == current->left;
		}
		else {
			current = current->right;
		}
	}

	//Delete leaf
	delete current;

	//Repeat until empty
	this->~BinarySearchTree();
}

//Traverse the tree in order
void BinarySearchTree::InOrder() {
	inOrder(root);

}

//Insert a course
void BinarySearchTree::Insert(Course course) {

	//Create new node
	Node* newNode = new Node(course);

	//Determine start
	Node* current = this->root;

	//If root is null, start new tree
	if (this->root == nullptr) {
		this->root = newNode;
		return;
	}

	//Traverse through tree
	while (current != nullptr) {
		if (course.courseID <= current->course.courseID) {
			if (current->left == nullptr) {
				current->left = newNode;
				return;
			}
			else {
				current = current->left;
			}
		}
		else {
			if (current->right == nullptr) {
				current->right = newNode;
				return;
			}
			else {
				current = current->right;
			}
		}
	}
}

//Remove a course, currently unused
void BinarySearchTree::Remove(string courseID) {

	//Determine start
	Node* parent = nullptr;
	Node* current = this->root;

	while (current != nullptr) {

		//Found node
		if (current->course.courseID == courseID) {
			if (current->left == nullptr && current->right == nullptr) {
				if (parent == nullptr) {
					delete this->root;
				}
				else if (parent->left->course.courseID == current->course.courseID) {
					delete parent->left;
				}
				else {
					delete parent->right;
				}
			}
			else if (current->right == nullptr) {
				if (parent == nullptr) {
					this->root = current->left;
				}
				else if (parent->left->course.courseID == current->course.courseID) {
					parent->left = current->left;
					delete current;
				}
				else {
					parent->right = current->left;
					delete current;
				}
			}
			else if (current->left == nullptr) {
				if (parent == nullptr) {
					this->root = current->right;
				}
				else if (parent->left->course.courseID == current->course.courseID) {
					parent->left = current->right;
					delete current;
				}
				else {
					parent->right = current->right;
					delete current;
				}
			}
			else {

				Node* successor = current->right;
				while (successor->left != nullptr) {
					successor = successor->left;
				}
				Node successorCopy = *successor;
				this->Remove(successor->course.courseID);
				current = &successorCopy;
			}
			return;
		}

		//Search right
		else if (current->course.courseID < courseID) {
			parent = current;
			current = current->right;
		}

		//Search left
		else {
			parent = current;
			current = current->left;
		}
	}

	//Node not found
	return;
}

//Search for a course
Course BinarySearchTree::Search(string courseID) {

	//Determine start
	Node* current = this->root;

	//Traverse through tree
	while (current != nullptr) {
		if (current->course.courseID == courseID) {
			return current->course; // Node found
		}
		else if (courseID < current->course.courseID) {
			current = current->left;
		}
		else {
			current = current->right;
		}
	}
	Course course;
	return course;

}

//Add a course to some node (recursive), currently unused
void BinarySearchTree::addNode(Node* node, Course course) {

	//Left node
	if (node->course.courseID > course.courseID) {
		if (node->left == nullptr) {
			node->left = new Node(course);
		}
		else {// else recurse down the left node
			addNode(node->left, course);
		}
	}

	//Right node
	else {
		if (node->right == nullptr) {
			node->right = new Node(course);
		}
		else {
			addNode(node->right, course);
		}
	}
}




/**********************
 *                    *
 *   Course Output    *
 *                    *
 *********************/

void BinarySearchTree::inOrder(Node* node) {

	if (node == nullptr) {
		return;
	}

	inOrder(node->left);
	cout << node->course.courseID << ": " << node->course.CourseTitle << "\n || Prerequisites: " << node->course.coursePrereqs << endl;
	inOrder(node->right);
}

void displayCourse(Course course){

	cout << course.courseID << " : " << course.CourseTitle << "\n || Prerequisites: " << course.coursePrereqs << endl;

	return;
}




/**********************
 *                    *
 *   Main Methods     *
 *  and Variables     *
 *                    *
 *********************/

//Variables
bool run = true;
string userChoice; 
int userChoiceNum = 0;
string searchChoice;
string filename;

//Method to welcome the user
void Welcome() {
	for (int i = 0; i < 30; ++i) {
		cout << "=";
	}
	cout << "\n|";
	for (int i = 0; i < 28; ++i) {
		cout << " ";
	}
	cout << "|" << endl;
	cout << "|      Welcome to ABCU       |" << endl;
	cout << "|   Comp Sci Course Library  |" << endl;
	cout << "|";
	for (int i = 0; i < 28; ++i) {
		cout << " ";
	}
	cout << "|" << endl;
	for (int i = 0; i < 30; ++i) {
		cout << "=";
	}
	cout << endl;
}

//Method to display the menu
void Menu() {
	cout << endl;
	for (int i = 0; i < 30; ++i) {
		cout << "=";
	}
	cout << "\n|";
	for (int i = 0; i < 28; ++i) {
		cout << " ";
	}
	cout << "|" << endl;
	cout << "|     Select an option:      |" << endl;
	cout << "|";
	for (int i = 0; i < 28; ++i) {
		cout << " ";
	}
	cout << "|" << endl;
	cout << "| [1] - Load Library Data    |" << endl;
	cout << "| [2] - Print Course Library |" << endl;
	cout << "| [3] - Search Course        |" << endl;
	cout << "| [4] - Exit                 |" << endl;
	cout << "|";
	for (int i = 0; i < 28; ++i) {
		cout << " ";
	}
	cout << "|" << endl;
	for (int i = 0; i < 30; ++i) {
		cout << "=";
	}
	cout << endl;
}

//Method to load and parse data
void LoadAndParse(BinarySearchTree* bst, string libtitle) {
	ifstream inFS(libtitle);
	string line;
	string courseID, title, prereqs;

	//Check if the file is open
	if (!inFS.is_open()) {
		cout << "Error loading library.\nMake sure to use the correct file name." << endl;
		return;
	}

	//Read each line from the file
	while (getline(inFS, line)) {
		stringstream ss(line);

		//Parse the line by commas
		getline(ss, courseID, ',');
		getline(ss, title, ',');

		//Check if there are prerequisites listed
		if (!getline(ss, prereqs) || prereqs.empty()) {
			prereqs = "None"; //Assign "none" if no prerequisites are found
		}

		//If prerequisites are listed
		else {
			getline(ss, prereqs);

			//Adds space after comma for multiple prerequisites (improves visuals)
			for (size_t i = 0; i < prereqs.length(); ++i) {
				if (prereqs[i] == ',') {

					// Insert a space after the comma
					prereqs.insert(i + 1, " ");
					++i;  // Increment i to skip the newly inserted space
				}
			}
			
		}

		//Search for course ID in course list
		bool found = false; 
		for (auto& item : courseList) {
			if (item == courseID) {
				found = true;
				break; 
			}
		}

		//Output course already exists
		if (found == true) {
			cout << "Course " << courseID << " already in course library. \nIt will not be added." << endl;
		}

		//Create a Course object
		else {
			courseList.push_back(courseID);
			Course newCourse;
			newCourse.courseID = courseID;
			newCourse.CourseTitle = title;
			newCourse.coursePrereqs = prereqs;

			//Insert the course into the tree
			bst->Insert(newCourse);
		}
	}

	//Confirm file loaded correctly
	cout << "Library loaded successfully" << endl;

	//Close file
	inFS.close();
}

//Method allows for clearing the input to assist with input validation
void InputClear() {
	cin.clear();
	cin.ignore(1000, '\n');  //This ignores up to 1000 extra characters or newlines
}

//Method makes string all caps for search ease
void makeStringUppercase(string& str) {

	//Loop through individual string characters
	for (char& c : str) {

		//If character is alpha, make upper
		if (std::isalpha(c)) {
			c = toupper(c);
		}
	}
}

//Method to ensure int is entered
bool isValidInteger(const string& str) {
	if (str.empty() || ((!isdigit(str[0])) && (str[0] != '-') && (str[0] != '+'))) return false;

	char* p;
	strtol(str.c_str(), &p, 10);
	return (*p == 0);
}




/**********************
 *                    *
 *        Main        *
 *                    *
 *********************/

int main() {

	// Define a binary search tree to hold all bids
	BinarySearchTree* bst;
	bst = new BinarySearchTree();
	Course course;

	Welcome();

	while (run) {

		//Display menu
		Menu();

		//Obtain menu option and account for accidental alpha char
		while (true) {
			getline(cin, userChoice);

			if (isValidInteger(userChoice)) {
				userChoiceNum = stoi(userChoice);
				break;
			}

			else{
				userChoiceNum = 0;
				break;
			}
		}

		switch (userChoiceNum) {

		//Load library 
		case 1:
			cout << endl;
			cout << "What is the library file title?\n[Hint: current file is called \"CSLib.txt\"]" << endl;
			getline(cin, filename);
			cout << "Loading library..." << endl;
			LoadAndParse(bst, filename);
			cout << endl;
			break; 

		//Print entire course library in order
		case 2:
			cout << endl;
			cout << "Now printing library...\n" << endl;
			bst->InOrder();
			cout << endl;
			break;

		//Search for specific course
		case 3:
			cout << "\nWhat is the course ID?: ";

			//Obtain course ID from user
			cin >> searchChoice;
			cout << "\nSearching...\n" << endl;

			//Allow for lowercase letter input
			makeStringUppercase(searchChoice);

			//Call search method
			course = bst->Search(searchChoice);

			//If course is found, display course information
			if (!course.courseID.empty()){
				displayCourse(course);
			}

			//Else, advise course not found
			else {
				cout << "Course " << searchChoice << " not found." << endl;
			}

			cout << endl;

			//Clear input to ensure no errors
			InputClear();
			break;

		case 4:
			cout << endl;
			cout << "Closing program...\n";

			//Set while loop bool to false
			run = false;
			break;

		//Default if menu choice is not 1-4
		default:
			cout << endl;
			cout << "[" << userChoice << "] is not an option" << endl;
			cout << "Please select an option: [1], [2], [3], or [4]" << endl;
			cout << endl;
			break;
		}

	}
	cout << endl;
	cout << "Thank you for using our services." << endl;
	cout << "Goodbye." << endl;

	return 0;
}
