#include "constant.h"
#include <iostream>
#include <stdio.h>

using namespace std;

int main()
{

    char block[SECTOR_SIZE] = "this is a try for write sector";
	int length=0;
    cout<<"Implementation of the File Handler Read Method..."<<endl;

    FILE *f = fopen(DISK, "w");
    if(f == NULL)
    {
        cout<<"Error In Opening the HardDisk File Retuning Error..."<<endl;
        return -1;
    }

    //Read One Block of Data to Buffer
    length = fwrite(block, 1, sizeof(block), f);

    /* Do something with the data */
    cout<<"Length : "<<length<<endl;
	cout << block;

    return 0;
}
