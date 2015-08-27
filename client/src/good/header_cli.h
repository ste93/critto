#ifndef HEADERS_CLIENT
#define HEADERS_CLIENT
#include <map>
int socketfd;
std::map<uint32_t, void*> nodes_in_memory;
//std::map<int, uint32_t> sectors_retrieved;
std::map<uint32_t, uint32_t> old_and_new_sector;
#define SOCKET_ERROR   ((int)-1)
#define INPSIZE 100
#define DISK "/dev/loop0"
#define SECTOR_SIZE 512

// Default order is 4.
#define DEFAULT_ORDER 4
int order = DEFAULT_ORDER;
#define NUM_VALUES 3
#define LEN_VALUES 15
// Minimum order is necessarily 3.  We set the maximum
// order arbitrarily.  You may change the maximum order.
#define MIN_ORDER 3
#define MAX_ORDER 20

// Constants for printing part or all of the GPL license.
#define LICENSE_FILE "LICENSE.txt"
#define LICENSE_WARRANTEE 0
#define LICENSE_WARRANTEE_START 592
#define LICENSE_WARRANTEE_END 624
#define LICENSE_CONDITIONS 1
#define LICENSE_CONDITIONS_START 70
#define LICENSE_CONDITIONS_END 625

typedef uint32_t sect_type;




typedef struct info {
	sect_type root_sect;
	sect_type last_sect_used;
} info;

/* Type representing a node in the B+ tree.
 * This type is general enough to serve for both
 * the leaf and the internal node.
 * The heart of the node is the array
 * of keys and the array of corresponding
 * pointers.  The relation between keys
 * and pointers differs between leaves and
 * internal nodes.  In a leaf, the index
 * of each key equals the index of its corresponding
 * pointer, with a maximum of order - 1 key-pointer
 * pairs.  The last pointer points to the
 * leaf to the right (or NULL in the case
 * of the rightmost leaf).
 * In an internal node, the first pointer
 * refers to lower nodes with keys less than
 * the smallest key in the keys array.  Then,
 * with indices i starting at 0, the pointer
 * at i + 1 points to the subtree with keys
 * greater than or equal to the key in this
 * node at index i.
 * The num_keys field is used to keep
 * track of the number of valid keys.
 * In an internal node, the number of valid
 * pointers is always num_keys + 1.
 * In a leaf, the number of valid pointers
 * to data is always num_keys.  The
 * last leaf pointer points to the next leaf.
 */
typedef struct node {
	void * pointers[DEFAULT_ORDER];
	int keys[DEFAULT_ORDER];
	uint32_t sectors[DEFAULT_ORDER];
	struct node * parent;
	uint32_t sector_parent;
	bool is_leaf;
	int num_keys;
	struct node * next; // Used for queue.
	uint32_t sector_next;
	uint32_t sector;
} node;



// TYPES.

/* Type representing the record
 * to which a given key refers.
 * In a real B+ tree system, the
 * record would hold data (in a database)
 * or a file (in an operating system)
 * or some other information.
 * Users can rewrite this part of the code
 * to change the type and content
 * of the value field.
 */

typedef struct record {
	int key;
	char values[NUM_VALUES][LEN_VALUES];
	node * parent;
	uint32_t parent_sect;
	struct record * next;
	uint32_t next_sect;
	struct record * prev;
	uint32_t prev_sect;
	uint32_t sector;
} record;


// GLOBALS.

/* The order determines the maximum and minimum
 * number of entries (keys and pointers) in any
 * node.  Every node has at most order - 1 keys and
 * at least (roughly speaking) half that number.
 * Every leaf has as many pointers to data as keys,
 * and every internal node has one more pointer
 * to a subtree than the number of keys.
 * This global variable is initialized to the
 * default value.
 */

/* The queue is used to print the tree in
 * level order, starting from the root
 * printing each entire rank on a separate
 * line, finishing with the leaves.
 */
node * queue = NULL;

/* The user can toggle on and off the "verbose"
 * property, which causes the pointer addresses
 * to be printed out in hexadecimal notation
 * next to their corresponding keys.
 */
bool verbose_output = false;


info * retr;
sect_type last_sect_used;

#endif
