/** Author: Jesse White
 *  Date Created: 10/18/2021
 *  Input is done through command line.
 *  File will take in alphanumeric characters in the range
 *  and output cyrillic characters in the range specified after being randomized.
 */
#include <iostream>
#include <ctime>

using namespace std;

int wrapNumber(int, int, int);

int main(int argc, char **argv) {
    srand(time(0));
    int seed = rand() % 94 + 1;
    //alphanumeric range
    int alphaMinIdx = 33;
    int alphaMaxIdx = 127;
    //cyrillic character range
    int minCyrillicIdx = 1024;
    int maxCyrillicIdx = 1279;

    if(argc > 0){
        string str = argv[1];
        int strLen = str.length();
        string out = new char[strLen];
        char dictionary[strLen][2];

        /** iterate through string and store and convert to cyrillic,
         *  storing results in dictionary.
         */
        for(int i = 0; i < strLen; i++){
            char currChar = str.at(i);
            int charInt = (int)str.at(i);
            //check if input character is an alpha numeric
            if(charInt >= alphaMinIdx && charInt <= alphaMaxIdx ){
                dictionary[i][0] = currChar;
                //we use the seed as an encryption tool, as it will be randomized each time.
                dictionary[i][1] = (char) wrapNumber(charInt+seed, minCyrillicIdx, maxCyrillicIdx);
                out.push_back(dictionary[i][1]);
            }else if(isspace(currChar)){
                //this if statement is used to maintain whitespace
                out.push_back(currChar);
            }
        }

        printf("Seed: %d\n", seed);
        printf("Input: \n %s\n", str.c_str());
        printf("Output:\n %s\n[", out.c_str());
        for(int i = 0; i < strLen; i++) {
            printf("{ %c : %c }, ", dictionary[i][0], dictionary[i][1]);
        }
        printf("]", seed);
    }
    return 0;
}

/** using modulo algebra to wrap the input between the specified range
 **/
int wrapNumber(int input, int minRange, int maxRange){
    int distance = maxRange - minRange;
    return input == maxRange ? input : ((input - minRange) % distance + distance) % distance + minRange;
}
