#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

class KeyPair {
    public:
        KeyPair(std::string filename, const std::map<std::string, std::string>& my_map = std::map<std::string, std::string>{}): filename(filename), map(my_map)  
        {
            if(map.empty()){
                std::cout << "NULL VAL" << std::endl;
                updateMap();
            } else {
                updateFile();
            }
        }

        // Add new Pair value to the txt file
        void addPair(std::string keyName, std::string value) {
            auto insert_function = [this, keyName, value]() {
                try{
                    if(map.count(keyName) == 0){
                        map.insert(std::pair<std::string, std::string>(keyName, value));
                    } else {
                        throw (keyName);
                    }
                } catch(std::string duplicateKey){
                    std::cout << "I'm sorry, there already exists a key with the name " << duplicateKey << std::endl;
                    return 1;
                }
                return 0;
            };
            my_decorator(insert_function);
        }

        // Edit Pair of values in txt file
        void editPair(std::string keyName, std::string newValue){
            auto edit_function = [this, keyName, newValue](){
                try{
                    if(map.count(keyName) != 0){
                        map[keyName] = newValue;
                    } else {
                        throw (keyName);
                    }
                }
                catch (std::string wrongKeyName) {
                    std::cout << "I'm sorry, there doesn't appear to be a key called " << wrongKeyName << std::endl;
                    return 1;
                }
                return 0;
            }; 
            my_decorator(edit_function);
        }

        // Delete Pair
        void deletePair(std::string keyName){
            auto delete_function = [this, keyName]() {
                try {
                    if(map.count(keyName) != 0){
                        map.erase(keyName);
                    } else {
                        throw (keyName);
                    }
                } catch(std::string nullKey){
                    std::cout << "Sorry, there doesn't appear to be any keys called " << nullKey << std::endl;
                }
            };
            my_decorator(delete_function);
        }
        
    private:
        std::string filename;
        std::map<std::string, std::string> map;

        // Reads File, and updates local map to reflect contents
        void updateMap(){
            std::ifstream inFile(filename);
            std::string line;

            if(!inFile.is_open()){
                std::cerr << "Error: Could not open file " << filename << std::endl;
                return;
            }

            while(std::getline(inFile, line)){
                std::size_t pos = line.find(":");
                if(pos != std::string::npos){
                    std::string key = line.substr(0, pos);
                    std::string value = line.substr(pos + 1);
                    map[key] = value;
                }
            }
            inFile.close();
        };

        void updateFile(){
            std::ofstream outFile(filename);
            if(!outFile.is_open()){
                std::cerr << "Error: Could not open File " << filename << std::endl;
                return;
            }
            for (const auto& p : map){
                outFile << p.first << ":" << p.second << std::endl;
            }
            outFile.close();
        };
        
        template <typename Func>
        void my_decorator(Func f) {
            auto new_f = [f, this]() {
                this->updateMap();
                f();
                this->updateFile();
            };

            new_f();
        }
};

void getKey(std::string *keyName){      // Takes in Pointer
    std::cout << "Key: ";
    std::cin.ignore();
    std::getline(std::cin, *keyName);   // Dereference to assign to memory?
};

void getValue(std::string *value){  // Takes in Pointer
    std::cout << "Value: ";
    std::getline(std::cin, *value); // Dereferenes to assign to memory
};

int main()
{
    using namespace std;
    while(true){
        // Are you wanting to open a new File, or update an existing file?
        string keyName;
        string value;

        string response;
        cout << "Are you wanting to open a new File or update and existing File? ";
        cin >> response;
        string fileName;

        if(response == "new"){
            map<string, string> user_map;
            
            cout << "Ok, so a new File then. What would you like to call it? ";
            cin >> fileName;
            cout << "Ok, lets start adding Key-Value Pairs" << endl;
            while(true){
                string addPair;

                getKey(&keyName);   // Pass in Address
                getValue(&value);   // Pass in Address

                user_map[keyName] = value;
                
                cout << "Notha one?(y/n) ";
                cin >> addPair;

                if(addPair != "y"){
                    break;
                }
            }
            KeyPair newKeyPair(fileName, user_map);
            break;
        } else {
            cout << "Ah, so an existing File" << endl;
            cout << "What's the name of the file? ";
            cin >> fileName;
            KeyPair newKeyPair(fileName);
            while(true){
                cout << "Would you like add a new pair ('a'), edit and existing pair ('e'), or remove a pair ('del')? ";
                string userDirection;
                cin >> userDirection;
                if (userDirection == "a"){
                    getKey(&keyName);
                    getValue(&value);
                    newKeyPair.addPair(keyName, value);
                } else if (userDirection == "e"){
                    getKey(&keyName);
                    getValue(&value);
                    newKeyPair.editPair(keyName, value);
                } else if (userDirection == "del"){
                    getKey(&keyName);
                    newKeyPair.deletePair(keyName);
                } else if (userDirection == "q") {
                    break;
                } else {
                    cout << "Sorry, I don't recognize this direction. Please try again" << endl;
                }
            }
            break;
        }
    };

    std::cout << "Thank you for using my Storage System" << std::endl;
}