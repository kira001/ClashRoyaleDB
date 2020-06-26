#include "myexception.h"

MyException::MyException(string msg):msg(msg){}

const string MyException::getMsgException()const{
    return msg;
}
