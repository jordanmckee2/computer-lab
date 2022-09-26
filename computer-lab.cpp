/*
    COPYRIGHT (C) 2021 Jordan McKee (jwm109) All rights reserved.
    Author. Jordan McKee
            jwm109@uakron.edu
    Version. 20.03-r11983
    Purpose: Write a program that has a practical relevance
*/
#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include <cstdlib>
#include <ctime>

// Global Constants
// Number of computer labs
const int NUMLABS = 8;
// Number of computers in each lab
const int LABSIZES[NUMLABS] = {19, 15, 24, 33, 61, 17, 55, 37};
// Names of university of each lab
const std::string UNIVERSITYNAMES[NUMLABS] = { "The University of Michigan", "The University of Pittsburgh", "Stanford University",
                                              "Arizona State University", "North Texas State University", "The University of Alabama, Huntsville", 
                                              "Princeton University", "Duquesne University" };

const int SIMULATELOGIN = 1;
const int SIMULATELOGOFF = 2;
const int SEARCHOPTION = 3;
const int DISPLAYLAB = 4;
const int QUIT = 5;

// creating a computer station struct that we will duplicate based on the amount of computer stations available throughout the universities
struct Computer
{
   int userIDs = {-1};
   std::string names = {""};
   int timeUsed = {-1};
};

// dynamic jagged array containing an array of Computers which will contain the memory of every person logged on across all computer labs
Computer *cLabs[NUMLABS] = {nullptr};

// Function Prototypes
void displayUniversities();
int geoMenu();
void simulateLogin();
void simulateLogoff();
void searching();
void display();
bool validateInput(int, int, int, std::string);
int getLab();
int getComputerStation(int);
int generateID();
std::string getName();
bool checkName(std::string);
int getTime();

int main()
{
   // creating the size of the jagged array of Computer structs, one for each computer station
   for (int i = 0; i < NUMLABS; ++i)
   {
      cLabs[i] = new Computer[LABSIZES[i]];
   }
   displayUniversities();
   while (true)
   {
      int choice = geoMenu();
      
      switch (choice)
      {
      case SIMULATELOGIN:
         simulateLogin();
         break;

      case SIMULATELOGOFF:
         simulateLogoff();
         break;

      case SEARCHOPTION:
         searching();
         break;

      case DISPLAYLAB:
         display();
         break;

      case QUIT:
         std::cout << "Program ending...";
         return 0;
      }
      std::cin.get();
   }
}

void displayUniversities()
{
   std::cout << "     Welcome - here is our list of available labs\n";
   std::cout << "Lab # 1 for The University of Michigan\n";
   std::cout << "Lab # 2 for The University of Pittsburgh\n";
   std::cout << "Lab # 3 for Stanford University\n";
   std::cout << "Lab # 4 for Arizona State University\n";
   std::cout << "Lab # 5 for North Texas State University\n";
   std::cout << "Lab # 6 for The University off Alabama, Huntsville\n";
   std::cout << "Lab # 7 for Princeton University\n";
   std::cout << "Lab # 8 for Duquesne University\n";
   std::cout << std::endl;
}

int geoMenu()
{
   int choice;
   bool loopFlag = true;
   std::cout << " _______________________________________________ " << std::endl;
   std::cout << "|-----------------------------------------------|" << std::endl;
   std::cout << "|            Jordan McKee Incorporated          |" << std::endl;
   std::cout << "|               Computer Lab System             |" << std::endl;
   std::cout << "|_______________________________________________|" << std::endl;
   std::cout << "|                    MAIN MENU                  |" << std::endl;
   std::cout << "|               1) Simulate Login               |" << std::endl;
   std::cout << "|               2) Simulate Logoff              |" << std::endl;
   std::cout << "|               3) Search                       |" << std::endl;
   std::cout << "|               4) Display a Lab                |" << std::endl;
   std::cout << "|               5) Quit                         |" << std::endl;
   std::cout << "|_______________________________________________|" << std::endl;
   std::string msg = "Please enter a valid option.\n";
   do
   {
      std::cout << "Enter your choice (1-5): ";
      std::cin >> choice;
      loopFlag = validateInput(choice, 1, 5, msg);
   } while (loopFlag);
   return choice;
}

void simulateLogin()
{
   int labNumber, labStation, userID, time;
   std::string name;
   labNumber = getLab();
   // determines whether this lab is full or not
   for (int i = 0; i < LABSIZES[labNumber - 1]; ++i)
   {
      if (cLabs[labNumber - 1][i].userIDs == -1)
      {
         break;
      }
      if (i == LABSIZES[labNumber - 1] - 1 && cLabs[labNumber - 1][i].userIDs != -1)
      {
         std::cout << "Sorry, this lab is full.\n";
         return;
      }
   }
   labStation = getComputerStation(labNumber);
   // determine if someone else is at this station
   if (cLabs[labNumber - 1][labStation - 1].userIDs != -1)
   {
      std::cout << "sorry, this station is in use. Try again later.\n";
      return;
   }
   // generate random 5-digit ID for user
   userID = generateID();
   std::cout << std::endl
             << "User id: " << std::setw(5) << std::setfill('0') << userID << std::setfill(' ') << std::endl;
   name = getName();
   time = getTime();
   std::cout << "User " << std::setw(5) << std::setfill('0') << userID << std::setfill(' ') << " successfully logged in for " << time << " minutes.\n";
   cLabs[labNumber - 1][labStation - 1].userIDs = userID;
   cLabs[labNumber - 1][labStation - 1].names = name;
   cLabs[labNumber - 1][labStation - 1].timeUsed = time;
}

void simulateLogoff()
{
   int labNumber, labStation;
   labNumber = getLab();
   labStation = getComputerStation(labNumber);
   // check if someone is even in that lab station
   if (cLabs[labNumber - 1][labStation - 1].userIDs == -1)
   {
      std::cout << "No user currently logged in on this station.\n";
   }
   else
   {
      std::cout << "User " << std::setw(5) << std::setfill('0') << cLabs[labNumber - 1][labStation - 1].userIDs << std::setfill(' ') << " successfully logged off.\n";
      cLabs[labNumber - 1][labStation - 1].userIDs = -1;
      cLabs[labNumber - 1][labStation - 1].names = "";
      cLabs[labNumber - 1][labStation - 1].timeUsed = -1;
   }
}

void searching()
{
   int ID;
   bool loopFlag = true, found = false;
   std::string msg = "make sure you enter a valid ID number.\n";
   do
   {
      std::cout << "Enter the 5 digit ID number of the user to find: ";
      std::cin >> ID;
      loopFlag = validateInput(ID, 0, 99999, msg);
   } while (loopFlag);
   for (int i = 0; i < NUMLABS; ++i)
   {
      for (int j = 0; j < LABSIZES[i]; ++j)
      {
         if (cLabs[i][j].userIDs == ID)
         {
            std::cout << "User " << std::setw(5) << std::setfill('0') << ID << std::setfill(' ') << ", " << cLabs[i][j].names << ", is in lab "
                      << i + 1 << " at " << UNIVERSITYNAMES[i] << ", on computer " << j + 1 << " for " << cLabs[i][j].timeUsed << " minutes." << std::endl;
            found = true;
            break;
         }
      }
   }
   if (found == false)
   {
      std::cout << "User is not currently logged in.\n";
   }
}

void display()
{
   int labNumber;
   bool loopFlag = true;
   std::string msg = "Enter a valid number.", userID = "empty";
   labNumber = getLab();
   std::cout << std::endl
             << "LAB STATUS\n";
   std::cout << "Lab # " << labNumber << " for " << UNIVERSITYNAMES[labNumber - 1] << std::endl;
   std::cout << "Computer Stations\n";
   for (int i = 0; i < LABSIZES[labNumber - 1]; ++i)
   {
      std::cout << i + 1 << " : ";
      if (cLabs[labNumber - 1][i].userIDs == -1)
      {
         std::cout << userID;
      }
      else
      {
         std::cout << std::setw(5) << std::setfill('0') << cLabs[labNumber - 1][i].userIDs << std::setfill(' ');
      }
      std::cout << "  ";
      if ((i + 1) % 5 == 0)
      {
         std::cout << std::endl;
      }
   }
}

bool validateInput(int userChoice, int range1, int range2, std::string message)
{
   bool goodOrNot = false;
   if ((std::cin.fail()) || ((userChoice < range1) || (userChoice > range2)))
   {
      std::cout << message << std::endl;
      goodOrNot = true;
   }
   std::cin.clear();
   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
   return goodOrNot;
}

int getLab()
{
   int labNumber = 0;
   bool loopFlag = true;
   std::string msg = "Your choice must be a valid lab number.";
   std::cout << "                 Your Choice: 1\n";
   do
   {
      std::cout << "Enter the number of the lab (1-" << NUMLABS << "): ";
      std::cin >> labNumber;
      loopFlag = validateInput(labNumber, 1, NUMLABS, msg);
   } while (loopFlag);
   return labNumber;
}

int getComputerStation(int labNumber)
{
   int labStation = 0;
   bool loopFlag = true;
   std::string msg = "Make sure you entered a valid work station";
   do
   {
      std::cout << "Enter the number of the computer station (1-" << LABSIZES[labNumber - 1] << "): ";
      std::cin >> labStation;
      loopFlag = validateInput(labStation, 1, LABSIZES[labNumber - 1], msg);
   } while (loopFlag);
   return labStation;
}

int generateID()
{
   bool loopFlag = true, repeated = false;
   int userID;
   do
   {
      srand((unsigned)std::time(0));
      userID = (rand() % 99999);
      for (int i = 0; i < NUMLABS; ++i)
      {
         for (int j = 0; j < LABSIZES[i]; ++j)
         {
            if (cLabs[i][j].userIDs == userID)
            {
               repeated = true;
            }
         }
      }
      if (repeated == false)
      {
         loopFlag = false;
      }
   } while (loopFlag);
   return userID;
}

std::string getName()
{
   bool loopFlag = true, goodName = false;
   std::string name;
   do
   {
      std::cout << "Please enter the name of this user: ";
      getline(std::cin, name);
      goodName = checkName(name);
      // verify that name is valid name and is less than 35 characters
      if (std::cin.fail() || goodName == false)
      {
         std::cout << "name must be less than 35 characters and made up of letters.";
         std::cin.clear();
         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
      else
      {
         loopFlag = false;
      }
   } while (loopFlag);
   return name;
}

bool checkName(std::string name)
{
   char sChar;
   // check if name > 35 characters first
   if (name.size() > 35)
   {
      return false;
   }
   // check if all characters are letters or spaces
   for (int i = 0; i < name.size(); ++i)
   {
      sChar = name[i];
      if ((!isalpha(sChar)) && (sChar != ' '))
      {
         return false;
      }
   }
   // check if name is empty spaces
   for (int i = 0; i < name.size(); ++i)
   {
      sChar = name[i];
      if (isalpha(sChar))
      {
         return true;
      }
   }
   return false;
}

int getTime()
{
   bool loopFlag = true;
   int time;
   do
   {
      std::cout << "Please enter the minutes of use for the work station (15/30/45/60): ";
      std::cin >> time;
      loopFlag = validateInput(time, 15, 60, "enter either 15, 30, 45, or 60.");
      if (time == 15 || time == 30 || time == 45 || time == 60)
      {
         loopFlag = false;
      }
      else
      {
         loopFlag = true;
      }
   } while (loopFlag);
   return time;
}
