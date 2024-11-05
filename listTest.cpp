/**
 *  \file listTest.cpp
 *  \brief     Test case for class LinkedList
 *  \author    J. Wuebbelmann
 *  \version   1.0
 *  \date      2019-09-04
 *  \pre       Class LinkedList must be implemented!
 *  \copyright Hochschule Osnabrueck
 * 
 */

#include "linkedlist.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>

const int fileElements = 10;

// Type definitions:
enum class ExecState
{
    ok,
    nok,
    exit
};

typedef void (* testFnc)(ExecState& status);

struct Menu
{
    char         item;
    std::string  menuText;
    testFnc      fnc;
};


// Static functions:

/**
 *  \brief Prints content of LinkedList
 *  
 *  \param [in] list list to print
 *  \return void
 *  
 */
static void printList(const LinkedList& list)
{
    for (std::size_t i = 0; i < list.size(); ++i)
    {
        std::cout << list.at(i) << " ";
    }
    std::cout << std::endl << "Sum: " << sum(list) << std::endl;
}

/**
 *  \brief test random list
 *  
 *  \param [out] s Status of function
 *  \return void
 *  
 *  \details Creates a list with random entries and a list with sorted entries\n. 
 *           The lists are printed.
 */
static void randomTest(ExecState& s)
{
    s = ExecState::ok;
    std::cout << __func__ << std::endl;
    LinkedList myListUnsorted;
	LinkedList myListSorted;
	unsigned int divider = RAND_MAX / 200;
    for (std::size_t i = 0; i < 10 ; ++i)
    {
		int rValue = rand() / divider -  RAND_MAX/2/divider;
        myListUnsorted.append(rValue);
		myListSorted.sortAppend(rValue);
    }
    std::cout << "List unsorted: " << std::endl;
    printList(myListUnsorted);

    std::cout << "List sorted: " << std::endl;
    printList(myListSorted);
}

/**
 *  \brief reads data from file and sorts it.
 *  
 *  \param [out] s Status of function
 *  \return void
 *  
 *  \details Reads a list from file and sorts it\n. 
 *           The list is printed before and after sorting.
 */
static void fileTest(ExecState& s)
{
    std::cout << __func__ << std::endl;
    std::ifstream file("listdata.dat");
    if(!file)
    {
        s = ExecState::nok;
        return;
    }
    LinkedList myListUnsorted;
	LinkedList myListSorted;
    while(!file.eof())
    {
        int v;
        file >> v;
        if (file.good())
        {
            myListUnsorted.append(v);
			myListSorted.sortAppend(v);
        }
    }
    std::cout << "List unsorted: " << std::endl;
    printList(myListUnsorted);

    std::cout << "List sorted: " << std::endl;
    printList(myListSorted);
    s = ExecState::ok;
}

//Funktion um eine zufällige Dateu zu erstellen
void generateFile(ExecState& s) {

    // Datei öffnen und leeren
    std::ofstream outputFile("listdata.dat", std::ios::trunc);

    // Prüfen ob die datei geöffnet wurde
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file." << std::endl;
        s = ExecState::nok;  // ExecState updaten
        return;
    }

    // Seed für rand()
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    unsigned int divider = RAND_MAX / 200;
    // Zufällige int in datei schreiben
    for (int i = 0; i < fileElements; ++i) {
        int randomInt = rand() / divider - RAND_MAX / 2 / divider;
        outputFile << randomInt << '\n';
    }

    // Datei schließen
    outputFile.close();

    s = ExecState::ok;

    std::cout << "File 'listdata.dat' created successfully with random integers." << std::endl;
}

/**
 *  \brief returns exit status.
 *  
 *  \param [out] s exit
 *  \return void
 *  
 *  \details just indicates that program might exit.
 */
static void exit(ExecState& s)
{
    std::cout << __func__ << std::endl;
    s = ExecState::exit;
}


// Data definitions:
const Menu mMenu[]
{
    {'0', "Random Test", randomTest},
    {'1', "File Test",   fileTest},
    {'2', "Create random File", generateFile},
    {'9', "Exit",        exit}
};

// Main Program:
int main()
{
    ExecState s(ExecState::ok);
    srand(time(0));

    do
    {
        char command;
        std::cout << "*** LIST SORTER ***" << std::endl;
        for(std::size_t i = 0; i < sizeof(mMenu)/ sizeof(Menu); ++i)
        {
            std::cout << "[" << mMenu[i].item << "] " << mMenu[i].menuText
                      << std::endl;
        }
        std::cin  >> command;
        for(std::size_t i = 0; i < sizeof(mMenu)/ sizeof(Menu); ++i)
        {
            if(command == mMenu[i].item && mMenu[i].fnc)
            {
                mMenu[i].fnc(s);
            }
        }
    }
    while(s != ExecState::exit);
    return 0;
}
