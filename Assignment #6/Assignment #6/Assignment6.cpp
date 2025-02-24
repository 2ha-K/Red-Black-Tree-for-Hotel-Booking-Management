//************************************************************************
// ASU CSE310 Assignment #6 Fall 2024
// Author: PO-YI, LIN
// ASU ID: 1228434521
// Description: this is the main program that reads input from keyboard,
// it then execute various red-black tree operations which is given in the input.
//**************************************************************************

#include "RedBlackTree.h"
#include <iostream>
#include <iomanip>

using namespace std;

//This function used to get the info. of a HotelBooking object
void getBookingInfo(string oneLine, string& hotelName, string& arrivalDate, int& confirmNum);

int main()
{
    string hotelName, arrivalDate;
    int confirmNum;
    string command, oneLine;
    string delimiter = ",";

    int pos = 0;

    //Create a RedBlackTree object here, use it throughout the program
    //----

    RedBlackTree rbt;

    do
    {
        getline(cin, oneLine);
        pos = oneLine.find(delimiter);
        command = oneLine.substr(0, pos);
        oneLine.erase(0, pos + delimiter.length());

        if (command.compare("quit") == 0)
        {
            cout << "\nCommand: quit" << endl;
            //call the relevant function on the red black tree
            break;//delete will use at end auto
        }
        else if (command.compare("tree_preorder") == 0)
        {
            cout << "\nCommand: tree_preorder" << endl;
            //call the relevant function on the red black tree
            //----
            rbt.treePreorder();
        }
        else if (command.compare("tree_inorder") == 0)
        {
            cout << "\nCommand: tree_inorder" << endl;
            //call the relevant function on the red black tree
            //----
            rbt.treeInorder();
        }
        else if (command.compare("tree_postorder") == 0)
        {
            cout << "\nCommand: tree_postorder" << endl;
            //call the relevant function on the red black tree
            //----
            rbt.treePostorder();
        }
        else if (command.compare("tree_minimum") == 0)
        {
            cout << "\nCommand: tree_minimum" << endl;
            //call the relevant function on the red black tree
            //----
            rbt.treeMinimum();
        }
        else if (command.compare("tree_maximum") == 0)
        {
            cout << "\nCommand: tree_maximum" << endl;
            //call the relevant function on the red black tree
            //----
            rbt.treeMaximum();
        }
        else if (command.compare("tree_predecessor") == 0)
        {
            //call the relevant function to get the HotelBooking info. first
            //----
            cout << "\nCommand: tree_predecessor" << endl;
            //call the relevant function on the red black tree
            //----
            getBookingInfo(oneLine, hotelName, arrivalDate, confirmNum);
            rbt.treePredecessor(hotelName, arrivalDate, confirmNum);
        }
        else if (command.compare("tree_successor") == 0)
        {
            //call the relevant function to get the HotelBooking info. first
            //----
            cout << "\nCommand: tree_successor" << endl;
            //call the relevant function on the red black tree
            //----
            getBookingInfo(oneLine, hotelName, arrivalDate, confirmNum);
            rbt.treeSucessor(hotelName, arrivalDate, confirmNum);
        }
        else if (command.compare("tree_search") == 0)
        {
            //call the relevant function to get the HotelBooking info. first
            //----
            cout << "\nCommand: tree_search" << endl;
            //call the relevant function on the red black tree
            //----
            getBookingInfo(oneLine, hotelName, arrivalDate, confirmNum);
            rbt.treeSearch(hotelName, arrivalDate, confirmNum);
        }
        else if (command.compare("tree_insert") == 0)
        {
            //call the relevant function to get the HotelBooking info. first
            //----
            cout << "\nCommand: tree_insert" << endl;
            getBookingInfo(oneLine, hotelName, arrivalDate, confirmNum);
            cout << left;
            cout << setw(18) << hotelName
                << setw(12) << arrivalDate
                << setw(8) << confirmNum << endl;
            //call the relevant function on the red black tree
            //----
            rbt.treeInsert(hotelName, arrivalDate, confirmNum);
        }
    } while (true);  //continue until 'quit'
    return 0;
}

//************************************************************************************
//This function from one line, extracts the hotelName, arrivalDate and confirmNum of a HotelBooking
void getBookingInfo(string oneLine, string& hotelName, string& arrivalDate, int& confirmNum)
{
    //Design your own code here
    //----
    string delimiter = ",";
    int pos = 0;

    pos = oneLine.find(delimiter);// Find the position of the first delimiter (",") in the line
    hotelName = oneLine.substr(0, pos);//Extract the substring from the start of the line up to the delimiter, which contains the hotel name
    oneLine.erase(0, pos + delimiter.length());//// Remove the extracted part, along with the delimiter, from the line

    pos = oneLine.find(delimiter);//
    arrivalDate = oneLine.substr(0, pos);
    oneLine.erase(0, pos + delimiter.length());

    confirmNum = stoi(oneLine);//Convert the remaining part of the line, which should be the confirmation number, to an integer
}
