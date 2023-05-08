#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

class KeyPair {
    public:
        KeyPair(std::string filename, std::map<std::string, std::string>& my_map): filename(filename), map(my_map) 
        {
            updateFile();
        }

        // Add new Pair value to the txt file
        void addPair(std::string keyName, std::string value) {
            updateMap();
            map.insert(std::pair<std::string, std::string>(keyName, value));
            updateFile();
        }

        // Edit Pair of values in txt file
        void editPair(std::string keyName, std::string newValue){
            updateMap();
            map[keyName] = newValue;
            updateFile();
        }

        void deletePair(std::string keyName){
            std::cout << "Delete" << std::endl;
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
        
};

int main()
{
    std::map<std::string, std::string> user_map;
    user_map["Key1"] = "Val1";
    user_map["Key2"] = "val2";
    user_map["Key3"] = "val3";

    KeyPair newKeyPair("TestFile.txt", user_map);

    newKeyPair.addPair("Key4", "val4");
    newKeyPair.editPair("Key1", "NewVal1");
}