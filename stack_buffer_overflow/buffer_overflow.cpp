// for input upto 16 bytes, things work fine. For more than that, the program crashes

#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;


/*
    * The thing is that when > 8 byte input is given to buffer_two, it will 
    * still report it's contents as 1234567890. However, the 890 are the part of
    * buffer_one. Note a 8 byte length buffer is actually 7 characters with an extra
    * \0 as the eighth byte.
*/

int main(int argc, char* argv[]){
    int value = 0;
    char buffer_one[8], buffer_two[8];
    

    printf("Buffer 1 is at %p \n", buffer_one);
    printf("Buffer 2 is at %p \n", buffer_two);
    
    strcpy(buffer_one, "one");
    strcpy(buffer_two, "two");
    
    printf("Buffer 1 is at %p and contains %s \n", buffer_one, buffer_one);
    printf("Buffer 2 is at %p and contains %s \n", buffer_two, buffer_two);
    printf("Value is at %p and contains %x", &value, value);

    cout << "\n";
    strcpy(buffer_two, argv[1]);

    printf("Buffer 1 is at %p and contains %s \n", buffer_one, buffer_one);
    printf("Buffer 2 is at %p and contains %s \n", buffer_two, buffer_two);
    printf("Value is at %p and contains %x", &value, value);
}