#pragma once

#include <string>

typedef void (*RELAUNCHER)(std::string& cmdLine);

class CommandSetup
{
public:
    CommandSetup();
    virtual ~CommandSetup();
    
    static CommandSetup* getInstance();
    
    void setRelauncher(RELAUNCHER cb);
    void setEngineRootPath(std::string root);
    void parseCommand(int argc, char *argv[]);
    std::string makeCommand(void);
    void setupEngine(void);

private:
    void init(void);

    bool _logToFile;
    int _scale;
    int _width;
    int _height;
    std::string _writePath;
    std::string _gameRootPath;
    std::string _engineRootPath;
    RELAUNCHER _relauncher;  
};
