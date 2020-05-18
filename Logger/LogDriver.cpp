//
//  Logger.cpp
//
//  Created by Nordstrom, Steve (Faculty - nordstrosg) on 9/5/19.
//  Updated on 1/15/2020.
//  Copyright © 20202 Nordstrom, Steve (Faculty - nordstrosg). All rights reserved.
//

#include <iostream>

#include "Logger.hpp"

int main() {
    
    // Instantiate a class which provides ILogger functionality...
    Logger logger("test.txt");
    
    //Logger has by default console on, file off, and memory always
    logger.Log("Test... 1, 2, 3...");
    
    logger.EnableFileLogging();
    logger.Log("Test... 4, 5, 6...");

    logger.DisableFileLogging();
    logger.Log("You should not see this line in the file!");

    logger.DisableConsoleLogging();
    logger.Log("You should not see this line until memory is purged!");

    logger.EnableConsoleLogging();
    logger.Log("You should not see this line in the file either.");

    logger.EnableFileLogging();
    logger.Log("This should not be the only line in your log file!");

    logger.DisableConsoleLogging();
    logger.Log("You should only see this line in the file!");
    logger.EnableConsoleLogging();
    logger.Log("You should see this line in both.");
    
    // write your own tests below here...
    logger.DisableConsoleLogging();
    for(int i = 0; i < 530; i++){
        logger.Log(" ");
    }
    
    logger.PurgeMemoryLog();
    return 0;
}
