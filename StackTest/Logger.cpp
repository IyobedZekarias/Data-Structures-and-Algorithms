//
//  Logger.cpp
//
//  Created by Nordstrom, Steve (Faculty - nordstrosg) on 9/5/19.
//  Updated on 1/15/2020.
//  Copyright © 2020 Nordstrom, Steve (Faculty - nordstrosg). All rights reserved.
//

#include "Logger.hpp"
#include <sstream> 

/// <summary>
/// Constructor to start a logger using a specified file name
/// </summary>
/// <param name="fileName">A string containing path for file</param>
Logger::Logger(std::string fileName)
{
    //Start the current location
    currentLocMemory = 0;
    //Store the name of the file for later
    logFileName = fileName;

    //turn the console on by default
    consoleEnabled = true;

    //No need to open file yet
    fileEnabled = false;
    
}

/// <summary>
/// Destructor to tear down a logger
/// </summary>
Logger::~Logger()
{
    //Close the file if it is open
    if(!fileEnabled)
    {
        myFile.close();
    }
}

/// <summary>
/// Method to log some string data
/// </summary>
/// <param name="line">A string to put as a line of text in the log</param>
/// <returns>True if line was logged properly, false otherwise</returns>
bool Logger::Log(std::string line)
{
    //Save which number of log the line is 
    std::stringstream loc;
    loc << currentLocMemory;
    std::string location = loc.str();
    std::string memLine = location + ": " + line;

    //put the line along with the timestamp into memory
    memory.at(currentLocMemory % 100) = memLine;
    currentLocMemory++;

    //Log to each target if enabled
    if(consoleEnabled)
    {
        std::cout << line << std::endl;
        if(!fileEnabled){
            return true;
        }
    }
    if(fileEnabled)
    {
        myFile << line << std::endl;
        return true;
    }
    return false;
}

/// <summary>
/// Control method to turn on file-based logging
/// </summary>
void Logger::EnableFileLogging()
{
    //Check if the file is already open and open it if not
    if(!myFile.is_open())
    {   
        myFile.open(logFileName);
        //Only set fileEnabled if the file is for sure open
        if(myFile.is_open())
        {
            fileEnabled = true;
        }   
    }
    // This is for any time EnableFileLogging() has already been run and is being run again
    if(myFile.is_open())
    {
        fileEnabled = true;
    }

}

/// <summary>
/// Control method to turn off file-based logging
/// </summary>
void Logger::DisableFileLogging()
{
    //We don't need to close the file will do that at the end
    fileEnabled = false;
}

/// <summary>
/// Control method to turn on console-based logging
/// </summary>
void Logger::EnableConsoleLogging()
{
    //Console logging just needs to be true/false for it to work 
    consoleEnabled = true;
}

/// <summary>
/// Control method to turn off console-based logging
/// </summary>
void Logger::DisableConsoleLogging()
{
    //Console logging just needs to be true/false for it to work 
    consoleEnabled = false;
}

/// <summary>
/// String property to view details of the implementation
/// </summary>
std::string Logger::GetInfo()
{
    // return the version number of your Logger
    return "0.0.1";
}

/// <summary>
/// Boolean property which reflects if the log is currently logging to a file
/// </summary>
bool Logger::IsFileLogEnabled()
{
    return fileEnabled;
}

/// <summary>
/// Boolean property which reflects if the log is currently logging to the console
/// </summary>
bool Logger::IsConsoleLogEnabled()
{
    return consoleEnabled;
}

/// <summary>
/// returns everything currently stored in the memory which should be everything that has been logged thus far
/// </summary>
void Logger::PurgeMemoryLog()
{
    // If the last location where data was stored is greater than 100 then print everything in the array 
    // If the last location where data was stored is less than 100 then just print everything up to that point
    if(currentLocMemory > 100)
    {
        for (int i=0; i < 100; i++)
        {
            std::cout << memory.at(i) << std::endl;
            memory.at(i) = "";
        }
    }
    else
    {
        for (int i=0; i < currentLocMemory; i++)
        {
            std::cout << memory.at(i) << std::endl;
            memory.at(i) = "";
        }
    }
    currentLocMemory = 0;
}
