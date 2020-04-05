#include <iostream>
#include <vector>
using namespace std;

class STUDENTI{
public:
    virtual~STUDENTI();
    std::string nome;
    STUDENTI(std::string n):nome(n){}
    virtual void F()=0;
};

class UNIVERSITARIO: public STUDENTI{
public:
     UNIVERSITARIO(std::string n):STUDENTI(n){}

    virtual void F(){
    std::cout<<"sona uno studente universitario"; }
};

class SUPERIORI: public STUDENTI{
public:
  SUPERIORI(std::string n):STUDENTI(n){}
    virtual void F(){
    std::cout<<"sona uno studente delle superiori"; }
};

class INSEGNANTE{


public:
string nome;
     INSEGNANTE(std::string n):nome(n){}

        virtual void F()=0;
    };




class INSUNI: public INSEGNANTE{

public:
    INSUNI(std::string n):INSEGNANTE(n){}

        virtual void F(){std::cout<<"sona uno studente delle superiori";}

};



class PERSONA: public STUDENTI,public INSEGNANTE
{
 public:
 vector<STDUENTI*>
 PERSONA()


};


int main()
{
   UNIVERSITARIO A("pippo");

   return 0;
}
