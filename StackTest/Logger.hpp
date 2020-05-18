//
//  Logger.hpp
//
//  Created by Nordstrom, Steve (Faculty - nordstrosg) on 9/5/19.
//  Updated on 1/15/2020.
//  Copyright © 2020 Nordstrom, Steve (Faculty - nordstrosg). All rights reserved.
//

#ifndef Logger_hpp
#define Logger_hpp

#include <string>
#include <iostream>
#include <fstream>
#include <array>

class Logger {
    
private:
    std::string logFileName;
    bool consoleEnabled;
    bool fileEnabled;
    std::ofstream myFile;
    std::array<std::string, 100> memory;
    int currentLocMemory;
    
public:
    

    /// <summary>
    /// Constructor to start a logger using a specified file name
    /// </summary>
    /// <param name="fileName">A string containing path for file</param>
    Logger(std::string fileName);
    
    /// <summary>
    /// Destructor to tear down a logger
    /// </summary>
    
    ~Logger();
    
    /// <summary>
    /// Method to log some string data
    /// </summary>
    /// <param name="line">A string to put as a line of text in the log</param>
    /// <returns>True if line was logged properly, false otherwise</returns>
    bool Log(std::string line);
    
    /// <summary>
    /// Control method to turn on file-based logging
    /// </summary>
    void EnableFileLogging();
    
    /// <summary>
    /// Control method to turn off file-based logging
    /// </summary>
    void DisableFileLogging();
    
    /// <summary>
    /// Control method to turn on console-based logging
    /// </summary>
    void EnableConsoleLogging();
    
    /// <summary>
    /// Control method to turn off console-based logging
    /// </summary>
    void DisableConsoleLogging();
    
    /// <summary>
    /// Control method to purge the memory log of all messages.
    /// Should honor the destination(s) enabled for log messages
    /// </summary>
    void PurgeMemoryLog();
    
    /// <summary>
    /// String property to view details of the implementation
    /// </summary>
    std::string GetInfo();
    
    /// <summary>
    /// Boolean property which reflects if the log is currently logging to a file
    /// </summary>
    bool IsFileLogEnabled();
    
    /// <summary>
    /// Boolean property which reflects if the log is currently logging to the console
    /// </summary>
    bool IsConsoleLogEnabled();
    

};

#endif /* Logger_hpp */
