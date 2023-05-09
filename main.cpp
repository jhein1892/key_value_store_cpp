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
                return map.insert(std::pair<std::string, std::string>(keyName, value)).first;
            };
            my_decorator(insert_function);
        }

        // Edit Pair of values in txt file
        void editPair(std::string keyName, std::string newValue){
            auto edit_function = [this, keyName, newValue](){
                return map[keyName] = newValue;
            }; 
            my_decorator(edit_function);
        }

        // Delete Pair
        void deletePair(std::string keyName){
            auto delete_function = [this, keyName]() {
                return map.erase(keyName);
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

int main()
{
    using namespace std;
    while(true){
        // Are you wanting to open a new File, or update an existing file?
        string response;
        cout << "Are you wanting to open a new File or update and existing File? ";
        cin >> response;

        if(response == "new"){
            string fileName;
            map<string, string> user_map;
            
            cout << "Ok, so a new File then. What would you like to call it? ";
            cin >> fileName;
            cout << "Ok, lets start adding Key-Value Pairs" << endl;
            while(true){
                string keyName;
                string value;

                string addPair;

                cout << "Key: ";
                cin.ignore();
                getline(cin, keyName);

                cout << "Value: ";
                cin.ignore();
                getline(cin, value);

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
            std::cout << "Ah, so an existing File" << std::endl;
            break;
        }

    };

    std::cout << "Thank you for using my Storage System" << std::endl;


    // std::map<std::string, std::string> user_map;
    // user_map["Key1"] = "Val1";
    // user_map["Key2"] = "val2";
    // user_map["Key3"] = "val3";

    // KeyPair newKeyPair("TestFile.txt", user_map);
    // KeyPair newKeyPair("TestFile.txt");

    // newKeyPair.addPair("Key4", "val4");
    // newKeyPair.editPair("Key1", "NewVal1");
    // newKeyPair.deletePair("Key3");
}