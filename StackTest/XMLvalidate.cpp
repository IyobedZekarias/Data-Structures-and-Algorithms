//Iyobed Zekarias
//2/12/2020
//Directions were gotten by talking with classmates 
//All code was hand written 

#include <iostream>
#include <string>
#include <fstream>
#include "Logger.hpp"
#include "LStack.hpp"

LStack<std::string> stack;

bool CheckLine(std::string line)
{
    //Pop off the stack check if line is equal to what is popped off 
    //If they are not equal return false 
    bool check = false; 
    std::string stackLine = stack.Pop();
    if(stackLine == line)
    {
        check = true;
    }
    return check;
}

int main()
{
    //Create a while loop to check multiple files 
    bool end = false;
    //Instantiate Logger
    Logger logger("XML_Log.txt");
    logger.EnableConsoleLogging();
    int LineNumber = 0;
    while(!end)
    {
        std::string fileName;
        //LineNumber will be 0 if an error is encountered
        if(LineNumber > 0)
        {
            logger.Log("Your xml file did not have any errors.\n");
        }
        logger.Log("Enter the name of the xml file followed by .xml that you want to read from");
        logger.Log("Enter exit if you want to quit");
        std::cin >> fileName;
        //Reset lineNumber to zero for new file check
        LineNumber = 0;
        stack.Empty();
        

        if(fileName.compare("exit") != 0)
        {
            std::string line = "";
            std::ifstream myFile (fileName);
            
            //Check if the file is open 
            if(myFile.is_open())
            {
                while(getline(myFile, line))
                {
                    LineNumber++;
                    //Find the location of the < 
                    //Find the location of the >
                    //The middle should be the text 
                    std::size_t findLeft = line.find('<');
                    std::size_t findRight = line.find('>');
                    std::size_t length = findRight - findLeft;
                    //The length will be zero if it is just text
                    if(length > 0)
                    {   
                        //create a pusline variable that is the central text of the tags
                        std::string pushline = line.substr((findLeft + 1), (length -1));
                        //Only push opening tags onto the stack 
                        if(pushline.at(0) != '?' && pushline.at(0) != '/')
                        {
                            stack.Push(pushline);
                        }
                        //Chcek closing tags
                        //All closing tags will start with /
                        else if(pushline.at(0) == '/')
                        {
                            //CheckLine(string) will return false if the closing tag is wrong 
                            bool check = CheckLine(pushline.substr(1));
                            if(!check)
                            {   
                                //If its wrong break out and print to the console where the error with what the tag is 
                                logger.Log("Error on line "  + std::to_string(LineNumber) + ": " + line.substr(findLeft, length + 1) + "\n");
                                LineNumber = 0;
                                break;
                            }
                        }
                    }
                }
            myFile.close();
            }

        }
        else
        {
            end = true;
        }
        
    }

}