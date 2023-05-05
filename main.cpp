#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>

class KeyPair{
    public:
        KeyPair(std::string type): my_type(type) 
        {
            if(my_type == "add"){
                addKeyPair();
            } 
            else if (my_type == "edit"){
                editKeyPair();
            }
            else if (my_type == "delete"){
                deleteKeyPair();
            }
        }

    private:
        std::string my_type;

        void addKeyPair(){
            std::cout << "Adding new Key/Pair" << std::endl;
        }
        void editKeyPair(){
            std::cout << "Edit Key/Pair" << std::endl;
        }
        void deleteKeyPair(){
            std::cout << "Delete Key/Pair" << std::endl;
        }
};


int main(){

    KeyPair userKeyPair("add");

    return 0;
}