#include "constant.h"
       #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>

#include <iostream>      
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
int write_sect(void * cont, int sect_num) {

    //cout<<"Implementation of the File Handler Read Method..."<<endl;
	int l;
    int f = open("/dev/loop0", O_RDWR);
    if(f < 0)
    {
        cout<<"Error In Opening the HardDisk File Retuning Error..."<<endl;
        return -1;
    }
	
    //Read One Block of Data to Buffer
    if(lseek(f, sect_num, SEEK_SET) != sect_num)
    {
          perror("Couldn't seek");
          close(f);
          return -1;
    }
    if ((l = write(f, cont, SECTOR_SIZE)) <= 0) {
		cout << "error";
		return -1;
	}
    close(f);
    /* Do something with the data */
    /*cout<<"Length : "<<length<<endl;
	cout << block;*/
    return 1;
}
/*
int main() {
	char block[SECTOR_SIZE] = "0000000000";
	write_sect((void *)block, 44);
	return 0;
}
* */

