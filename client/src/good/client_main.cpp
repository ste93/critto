#include "cli.cpp"
//#include "bpt.cpp"
#include "header_cli.h"
#include <map>
#include <list>	
#include <cctype>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <stdio.h>
#include <iostream>

void *retrieveDataFake(int socketfd, uint32_t sector){
	std::list<uint32_t> nodes_to_retrieve;
	std::list<uint32_t>::const_iterator it_list;
	uint32_t list_to_put, old = 0;
	void * sec;
	int i, flag = 0;
	std::map<uint32_t, void*>::const_iterator it = nodes_in_memory.find(sector);
	if (it!=nodes_in_memory.end())
		return nodes_in_memory[sector];

	nodes_to_retrieve.push_back(sector);
	last_sect_used = retr->last_sect_used;
	for (i=0;i<2;i++) { //this is not working very well, can be better
		//std::cout << i << "in for\n";
		while (1)
		{
			list_to_put = (rand() % last_sect_used) + 1;
			//std::cout << list_to_put << "\n";
			if(((nodes_in_memory.size() == last_sect_used + 1 )&& i==0) || ((nodes_in_memory.size() == last_sect_used)&& i==1) ) {
				flag = 1;
				break;
			}
			if(nodes_in_memory.find(list_to_put) == nodes_in_memory.end() && list_to_put != sector) {
				//std::cout << i << " " << list_to_put << " " << old << "\n";
				if (i==1 && list_to_put != old) {						
					flag = 2;
					break;
				}
				else if(i == 0){
					flag = 2;
					break;
				}					
			}
			
		}
		//std::cout << list_to_put << "\n";
		if (flag == 2) {
			if (i == 0)
				old = list_to_put;
			nodes_to_retrieve.push_back(list_to_put);
		}
	}
	//std::cout << "retrieving via socket\n";
	nodes_to_retrieve.sort();
	for(it_list=nodes_to_retrieve.begin();it_list!=nodes_to_retrieve.end(); ++it_list) {
		sec = retrieveData(socketfd, *it_list);
		nodes_in_memory[*it_list] = sec;
		//std::cout << "retrieved " << *it_list << "\n";
	}
	return nodes_in_memory[sector];
}

	
	
void * retrieveRoot(void) {
	node * root;
	retr = (info *)retrieveData(socketfd, 0);
	//std::cout << retr->root_sect << " " << retr->last_sect_used << "\n";
	//std::cout << "retrievedInfo\n";
	root = (node *)retrieveDataFake(socketfd, retr->root_sect);
	//std::cout << "retrievedRoot\n";
	return root;
}
	
int sendTree (void * root) {
	
}


	
int main(int argc, char *argv[]) {
	node * root;
	srand (time(NULL));
	serverConnectionInit(argv[1], argv[2], &socketfd);
	if((root = (node *)retrieveRoot()) == NULL)
		exit (1);
	//here I have to implement the queries
}
