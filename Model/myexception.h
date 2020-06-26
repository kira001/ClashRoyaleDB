#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H

#include <string>
#include <exception>

using std::string;

class MyException : public std::exception {
    const string msg;
public:
    MyException(string msg);
    const string getMsgException() const;
};

#endif // MYEXCEPTION_H
