#ifndef LOGGER_H
#define LOGGER_H

class Logger{
public:
    void log(char *) const;
    void read_log(char *);
private:
    char const fileName[10] = "input.log"; 
};

#endif
