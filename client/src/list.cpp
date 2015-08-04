#include <\string>

typedef struct element {
	int pos;
	string value;
	struct element *next;
} element;

int delete_list(element * list_first) {
	element *tmp = list_first, *succ;
	while(tmp!=NULL) {
		succ = tmp->next;
		delete(tmp);
		tmp = succ;
	}
	return 0;
}

element * insert_element(element ** list_ptr, int index, string value) {
	element ** root, * tmp, *tmp2;
	if (*root == NULL || (root != NULL && index < *root->pos)){
		tmp = new element;
		tmp->pos = index;
		value.copy(tmp->value, 0, value.size());
		tmp->next = *root;
		root = tmp;
	}
	else {
		tmp = * root;
		while (tmp->next->pos < index) {
			tmp = tmp->next;
		}
		tmp2 = new element;
		tmp2->next = tmp->next;
		tmp->next = tmp2;
		tmp2->pos = index;
		value.copy(tmp2->value, 0, value.size());
	}
	return root;
}

void print(element * list_ptr){
	while(list_ptr != NULL){
		cout << list_ptr->pos << " ; " << list_ptr->value << "\n";
	}
}


int main() {
	element * root = NULL;
	int x;
	string y;
	while(1){
		cin >> x;
		cin >> y;
		insert_element(&root, x, y)
	}
}
		
