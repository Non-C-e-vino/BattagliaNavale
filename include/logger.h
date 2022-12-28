#ifndef LOGGER_H
#define LOGGER_H

class Logger{
public:
    void log(char *) const;
    void read_log(char *);
private:
    int cursor = 0; 
    char const fileName[10] = "input.log"; 
};

#endif
