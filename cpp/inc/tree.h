#include "MKL26Z4.h"
#include "list.h"
#include "tbutton.h"

#ifndef TREE_H
#define TREE_H

class Tree {
public:
	//enum class action {act, back, home};
struct Item
{
	List * object;
	Tbutton * buttons;
	Item * parent;
	Item * brother;
	Item * son;
	Item (List *o, Tbutton * but, Item * p = nullptr, Item * b = nullptr, Item * s = nullptr);
};
private:
	//uint16_t count;
public:
	Item * root;
	Item * currentItem;

public:
	Tree(List *o, Tbutton * but);
	~Tree();
	void addItem (List *, Tbutton * but, Item *);
	void addSon (List *o, Tbutton * but);
	void addBrother (List *o, Tbutton * but);
	void setCurrent (List *);

	void treeAction ();

	void getBack ();
	void getForward (uint16_t val);
	void getRoot ();
	void useCurrent ();

	friend void getForward (Tree &);
	friend void getForward (Tree &, uint16_t val);
	friend void getBack (Tree &);
	friend void getRoot (Tree &);
};

void getForward (Tree &);
void getForward (Tree &, uint16_t val);
void getBack (Tree &);
void getRoot (Tree &);


#endif /* LIST_H_ */
