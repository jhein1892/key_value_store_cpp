#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

class KeyPair {
    public:
        KeyPair(std::string filename, std::map<std::string, std::string>& my_map): filename(filename), map(my_map) 
        {
            // When we start a new KeyPair class, we are going to automatically insert the map into a file.
            std::ofstream file(filename);
            if (!file.is_open()){
                std::cerr << "Error could not open file " << filename << std::endl;
                return;                
            }
            
            for (const auto& p : my_map){
                file << p.first << ":" << p.second << std::endl;
            }

            file.close();
        }

        // Add new Pair value to the txt file
        void addPair(std::string keyName, std::string value) {
            std::ofstream outfile(filename, std::ios::app);
            if(outfile.is_open()){
                outfile << keyName << "," << value << std::endl;
                outfile.close();
            } else {
                std::cerr << "Error: could not open file for reading" << std::endl;
            }
        }

        void editPair(std::string keyName, std::string newValue){
            std::ifstream inFile(filename);
            std::string line;
            int lineNum = 0;

            while(std::getline(inFile, line)){
                lineNum += 1;
                std::size_t pos = line.find(":");
                if(pos != std::string::npos){
                    std::string key = line.substr(0, pos);
                    std::string value = line.substr(pos + 1);
                    if(key == keyName){
                        std::cout << key << ": " << value << lineNum << std::endl;
                        map[key] = newValue;
                    } else {
                        map[key] = value;
                    }
                }
            }
            inFile.close();

            std::ofstream outFile(filename);
            for (const auto& p : map){
                outFile << p.first << ":" << p.second << std::endl;
            }

            outFile.close();
        }
    private:
        std::string filename;
        std::map<std::string, std::string> map;
};

int main()
{
    std::map<std::string, std::string> user_map;
    user_map["Key1"] = "Val1";
    user_map["Key2"] = "val2";
    user_map["Key3"] = "val3";

    KeyPair newKeyPair("TestFile.txt", user_map);

    // newKeyPair.addPair("Key4", "val4");
    newKeyPair.editPair("Key1", "NewVal1");
}