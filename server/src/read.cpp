#include "constant.h"
       #include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h>

#include <iostream>      
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

void * read_sect(int sect_num) {

    void *block = malloc(SECTOR_SIZE);
    //cout<<"Implementation of the File Handler Read Method..."<<endl;
	int l;
    int f = open("/dev/loop0", O_RDWR);
    if(f < 0)
    {
        cout<<"Error In Opening the HardDisk File Retuning Error..."<<endl;
        return NULL;
    }
	
    //Read One Block of Data to Buffer
    if(lseek(f, sect_num, SEEK_SET) != sect_num)
    {
          perror("Couldn't seek");
          close(f);
          return NULL;
    }
    if ((l = read(f, block, SECTOR_SIZE)) <= 0) {
		cout << "error";
		return NULL;
	}
    close(f);
    /* Do something with the data */
    /*cout<<"Length : "<<length<<endl;
	cout << block;*/

    return block;
}
/*
int main() {
	void * block;
	cout << "sadfsa";
	block = read_sect(44);
	//cout << *(char*)block;
	return 0;
}*/
