/*
Author: Liliana Pacheco
Name: LinkedList.cpp
Purpose: to create a fully functioning Linked List using Nodes. It is also a templated class Linked List to allow use with different DataTypes
*/
#include "LinkedList.h"
#include <iostream>

using namespace std;

/*
Name: ListNode
input: a Node data type and a List Node pointer
Purpose: This is the ListNode constructor, its purpose is to create a new node with the given DataType value and to set the next pointer of the node to the given ListNode Pointer
*/
template <class DataType>
List<DataType>::ListNode::ListNode (const DataType& nodeData, ListNode* nextPtr)
{
	dataItem = nodeData;
	next = nextPtr;
}

/*
Name: List
Input: takes in an integer that is ignored
Purpose: To create an empty List despite the integer input
*/
template <class DataType>
List<DataType>::List (int ignore)
{
	head = NULL;
	cursor = head;
}

/*
Name: List
Input: Takes in a Constant List item
Purpose: The purpose of this functino is to take in a list item and create an exact copy of it
*/
template <class DataType>
List<DataType>::List (const List& other)
{
	other.gotoBeginning(); //place  the "other" cursor at the start of the list (just in case)

	while(other.cursor != NULL)
	{
		insert(cursor-> dataItem);  //insert will create a node in the list with the appropriate data
		other.gotoNext(); //move cursor to the next node
	}

}

/*
Name: operator=
Input: Constant List item
Purpose: For the calling item to copy over the input item List to in a sense make a copy of the input item
*/
template <class DataType>  
List<DataType>& List<DataType>::operator=(const List& other)
{
	if(this == &other)
	{
		return; // if calling object is other object then nothing needs to be done important because we would delete the data of the object other wise
	}

	clear(); //delete pre-existing data of calling object
	other.gotoBeginning(); //place  the "other" cursor at the start of the list (just in case)

	while(other.cursor != NULL)
	{
		insert(cursor -> dataItem);  //insert will create a node in the list with the appropriate data
		other.gotoNext(); //move cursor to the next node
	}
}

/*
Name: ~List
Input: None
Purpose: This is the List destructor and it takes care of deallocating the memory of the nodes of the list when the object is destroyed
*/
template <class DataType>
List<DataType>::~List()
{
	clear();//just use clear cause im lazzy it will take care of memory deallocation which is the important part
}

/*
Name: insert
Input: A constant data type or new value that is used to create a new node for the Linked List
Purpose: This function creates a new node and inserts it at the end of the list if there are no items in the list then the new item becomes the head of the list
*/
template <class DataType>
void List<DataType>::insert(const DataType& newDataItem) throw (logic_error)
{
	ListNode *new_node_ptr = new ListNode(newDataItem, 0); //make new node object

	if(isEmpty()) // if the list is empty then make the newly created node the head and set the cursor
	{
		head = new_node_ptr;
		cursor = head;
	}
	else if ((cursor -> next) == NULL)        // if the list is not empty then we must link the newly created node to the existing list
	{
		cursor -> next = new_node_ptr; 
		cursor = new_node_ptr; //set cursor to the new node
	}
	else if (!isEmpty())
	{
		ListNode *temp_node_ptr;
	
		temp_node_ptr = cursor;
		
		gotoNext();

		temp_node_ptr -> next = new_node_ptr;
		new_node_ptr -> next = cursor;
		cursor = new_node_ptr;					
		
	}

}

/*
Name: remove
Input: None
Purpose: This function removes the node pointed to by the cursor and places the cursor in the following item
*/
template <class DataType>
void List<DataType>::remove() throw (logic_error)
{
	if(isEmpty())//list is empty so nothing needs to be done
	{
		return;
	}
	else if (cursor == head) //in case the node to be removed is the first item on the list
	{	
		head = head -> next; //place head on the second item of the list before the first item is deleted
		delete cursor;
		cursor = head;
	}
	else if (cursor -> next == NULL) //in case the node to be removed is the last item on the list
	{	
		ListNode *temp_node_ptr = cursor; //save the address of the node that is to be deleted
		gotoPrior(); 							 //move curser to prior node and set that item to null (now the last item of the list)
		cursor -> next = NULL;
		delete temp_node_ptr;  				//finaly delete the remove/delete the node

		gotoBeginning(); // because the item deleted is the last item of the list the curser is set to the first item of the list
	}
	else if (!isEmpty()) //last possible case is that the item to be removed is somewhere in the middle of the list
	{
		ListNode *temp_node_ptr, *prior_node, *following_node;		
 
		temp_node_ptr = cursor; //save the initial position of the cursor

		gotoPrior();
		prior_node = cursor; // save position of the node before the one that is to be deleted

		gotoNext();				
		gotoNext();
		following_node = cursor; //save the position of the following node (next to the one that will be deleted)

		prior_node -> next = following_node;
		delete temp_node_ptr;		
	}
}

/*
Name: replace
Input: A constant data type item or new value for a node that is to be replaced
Purpose: This function takes in a new value to be assigned to the node pointed to by the cursor
*/
template <class DataType>
void List<DataType>::replace(const DataType& newDataItem) throw (logic_error)
{	

	if (isEmpty())
	{
		return; //because List is empty nothing can or will be replaced	
	}
	else
	{
		cursor -> dataItem = newDataItem; //change the value of selected data type
	}
}

/*
Name: clear
Input: None
Pupose: This function clears all the existing nodes of the list and deallocates the memory of those nodes
*/
template <class DataType>
void List<DataType>::clear()
{
	ListNode * temp;

	while(!isEmpty())
	{
		temp = head;	 //save adress of current head pointer
		head = head -> next;	//set head to the following node because it will be deleted soon
		delete temp;	//delete first node and continue deleting process
	}

	//set head and cursor to NULL (head is automaticly set to null by previous loop)
	cursor = head;	
}


/*
Name: isEmpty
Input: none
Purpose: This functino checks if there is any items in the list if there are then it returns false and true other wise
*/
template <class DataType>
bool List<DataType>::isEmpty() const
{
	if(head == NULL)
		return true;
	else
		return false;
}

/*
Name: isFull
Input: None
Purpose: None for this particular code we will not pay attention to the size of the list and assume for it to never be full
*/
template <class DataType>
bool List<DataType>::isFull() const
{
	return false;
}

/*
Name: gotoBeginning
Input: None
Purpose: This function takes the cursor to the beginning of the list
*/
template <class DataType>
void List<DataType>::gotoBeginning() throw (logic_error)
{
	cursor = head;
}

/*
Name: gotoEnd
Input: None
Purpose: This function takes the cursor to the end of the list
*/
template <class DataType>
void List<DataType>::gotoEnd() throw (logic_error)
{
	if(isEmpty())//if empty do nothing 
		return;

	while(cursor -> next != NULL)
	{
		gotoNext();
	}
}

/*
Name: gotoNext
Input: None
Purpose: This function moves the cursor to the following item on the List
*/
template <class DataType>
bool List<DataType>::gotoNext() throw (logic_error)
{
	if (isEmpty())//if empty do nothing 
		return false;
	else if (cursor -> next == NULL) //because cursor is on the last node of the list you can't go to a following node
		return false;
	else
	{
		cursor = cursor -> next;
		return true;	
	}		
}

/*
Name: gotoPrior
Input: None
Purpose: This function moves the cursor to the item of the list right before the pointed item
*/
template <class DataType>
bool List<DataType>::gotoPrior() throw (logic_error)
{
	if(isEmpty())//if empty do nothing 
		return false;
	else if (cursor == head) //because cursor is pointing to the first node of the list you can't go to a prior node
		return false;
	else
	{
		ListNode *temp_node_ptr = cursor; //save the initial position of the cursor
		gotoBeginning();
		
		while (cursor -> next != temp_node_ptr)
		{
			gotoNext();
		}
		return true;
	}
}

template <class DataType>
DataType List<DataType>::getCursor() const throw (logic_error)
{
return cursor -> dataItem;
}

/*
Name: moveToBeginning
Input: None
Purpose: This function moves the node pointed to by the cursor to the beginning of the Linked List
*/
template <class DataType>
void List<DataType>::moveToBeginning () throw (logic_error)
{
	if(isEmpty())//if empty do nothing 
		return;
	else if (cursor == head) // if node pointed by the curser is already the first node of the list then do nothing
		return;
	else if (cursor -> next == NULL) //in case curser points to the last item of the list
	{
		ListNode * temp_node_ptr = cursor;
		
		cursor -> next = head;
		gotoPrior();
		cursor -> next = NULL;
		head = temp_node_ptr;
		gotoBeginning();
	}
	else if (!isEmpty()) // in case curser pints to a node in the middle of the list
	{
		ListNode * temp_node_ptr, * prior_ptr, * next_ptr;
		
		temp_node_ptr = cursor;
		
		gotoPrior();
		prior_ptr = cursor;

		gotoNext();
		gotoNext();
		next_ptr = cursor;
		
		prior_ptr -> next = next_ptr;
		temp_node_ptr -> next = head;
		head = temp_node_ptr;
		cursor = temp_node_ptr;
	}
}

/*
Name: insertBefore
Input: This function takes in a Data Type item to create a new node
Purpose: The purpose of this function is to inster a new node between the prior node pointed by the cursor and the cursor pointed node
*/
template <class DataType>
void List<DataType>::insertBefore(const DataType& newDataItem) throw (logic_error)
{
	ListNode * new_node_ptr = new ListNode(newDataItem, 0); //make a new node with the given  data
	new_node_ptr -> dataItem = newDataItem;
	
	if (isEmpty())
	{
		insert(newDataItem);
		delete new_node_ptr;	
	}	
	else if (cursor == head)
	{
		new_node_ptr -> next = head;
		head = new_node_ptr;
		cursor = new_node_ptr;
	}
	else if (!isEmpty())
	{
		ListNode * temp_node_ptr, * prior_ptr;
		
		temp_node_ptr = cursor;
		
		gotoPrior();
		prior_ptr = cursor;

		prior_ptr -> next = new_node_ptr;
		new_node_ptr -> next = temp_node_ptr;
		cursor = new_node_ptr;
	}
}

//--------------------------------------------------------------------
// show5.cpp: includes implementation of showStructure
//--------------------------------------------------------------------

template <typename DataType>
void List<DataType>::showStructure() const

// Outputs the items in a list. If the list is empty, outputs
// "Empty list". This operation is intended for testing and
// debugging purposes only.

{
    if ( isEmpty() )
    {
       cout << "Empty list" << endl;
    } 
    else
    {
	for (ListNode* temp = head; temp != 0; temp = temp->next) {
	    if (temp == cursor) {
		cout << "[";
	    }

	    // Assumes that dataItem can be printed via << because
	    // is is either primitive or operator<< is overloaded.
	    cout << temp->dataItem;	

	    if (temp == cursor) {
		cout << "]";
	    }
	    cout << " ";
	}
	cout << endl;
    }
}





