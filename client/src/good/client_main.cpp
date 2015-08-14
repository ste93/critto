#include "cli.cpp"
//#include "bpt.cpp"
#include "header_cli.h"
#include <map>
#include <list>	
#include <cctype>
#include <iostream>

void *retrieveDataFake(int socketfd, uint32_t sector){
	std::list<uint32_t> nodes_to_retrieve;
	std::list<uint32_t>::const_iterator it_list;
	uint32_t list_to_put;
	void * sec;
	int i;
	std::map<uint32_t, void*>::const_iterator it = nodes_in_memory.find(sector);
	if (it!=nodes_in_memory.end())
		return nodes_in_memory[sector];

	nodes_to_retrieve.push_back(sector);
	std::cout << "before for\n" ;
	for (i=0;i<2;i++) { //this is not working very well, can be better
		std::cout << i << "in for\n";
		while (nodes_in_memory.find(list_to_put = (rand() % (last_sect_used - 1)) + 1) != nodes_in_memory.end())// && nodes_in_memory.size() != last_sect_used + 1) 
		{
			std::cout << "in while\n";
		}
		std::cout << list_to_put << "\n";
		nodes_to_retrieve.push_back(list_to_put);
	}
	std::cout << "retrieving via socket\n";
	nodes_to_retrieve.sort();
	for(it_list=nodes_to_retrieve.begin();it_list!=nodes_to_retrieve.end(); ++it_list) {
		sec = retrieveData(socketfd, *it_list);
		nodes_in_memory[*it_list] = sec;
		std::cout << "retrieved " << *it_list << "\n";
	}
	return nodes_in_memory[sector];
}

	
	
void * retrieveRoot(void) {
	node * root;
	retr = (info *)retrieveData(socketfd, 0);
	std::cout << retr->root_sect << " " << retr->last_sect_used << "\n";
	std::cout << "retrievedInfo\n";
	root = (node *)retrieveDataFake(socketfd, retr->root_sect);
	std::cout << "retrievedRoot\n";
	return root;
}
	
int sendTree (void * root) {
}


	
int main(int argc, char *argv[]) {
	node * root;
	info * in = new info;
	std::cout << sizeof(info) << "\n";
	in->root_sect = 10;
	in->last_sect_used = 20;
	last_sect_used = 20;
	serverConnectionInit(argv[1], argv[2], &socketfd);
	std::cout << "asdf\n";
	
	if((root = (node *)retrieveRoot()) == NULL)
		exit (1);
	//here I have to implement the queries
}
