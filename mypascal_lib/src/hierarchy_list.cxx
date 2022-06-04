
#include "hierarchy_list.hxx"

void MyPascal::HList::insert_next(const MyPascal::HString edata) {
	if (head == nullptr) {
		head = new HLink(edata);
		current = head;
		path.push(current);
	}
	else {
		HLink* current_link = current;
		while (current_link->next != nullptr)
			current_link = current_link->next;
		current_link->next = new HLink(edata);
		current = current_link->next;
		if (!path.empty())
			path.pop();
		path.push(current);
	}
}

void MyPascal::HList::insert_down(const HString edata) {
	if (current->down == nullptr) {
		current->down = new HLink(edata);
		path.push(current);
		current = current->down;
	}
	else {
		HLink* current_node = current;
		while (current_node->down != nullptr)
			current_node = current_node->down;
		current_node->down = new HLink(edata);
		path.push(current);
		current = current->down;
	}
}

void MyPascal::HList::pop() {
	path.pop();
	current = path.top();
}
