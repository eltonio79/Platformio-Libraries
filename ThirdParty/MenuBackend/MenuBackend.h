#ifndef MenuBackend_h
#define MenuBackend_h

class MenuItem
{
public:
	MenuItem(const __FlashStringHelper* itemName, char shortKey = '\0' ) : name(itemName), shortkey(shortKey) {
		before = right = after = left = NULL;
	}

	//void use(){} //update some internal data / statistics
	inline const __FlashStringHelper* getName() const { return name; }
	inline const char getShortkey() const { return shortkey; }
	inline const bool hasShortkey() const { return (shortkey != '\0'); }
	inline void setBack(MenuItem *b) { back = b; }
	inline MenuItem* getBack() const { return back; }
	inline MenuItem* getBefore() const { return before; }
	inline MenuItem* getRight() const { return right; }
	inline MenuItem* getAfter() const { return after; }
	inline MenuItem* getLeft() const { return left; }

	MenuItem *moveBack() { return back; }

	MenuItem *moveUp() { 
		if (before) { before->back = this; }
		return before; 
	}

	MenuItem *moveDown() { 
		if (after) { after->back = this; }
		return after; 
	}

	MenuItem *moveLeft() { 
		if (left) { left->back = this; }
		return left; 
	}

	MenuItem *moveRight() { 
		if (right) { right->back = this; }
		return right; 
	}

	//default vertical menu
	MenuItem &add(MenuItem &mi) { return addAfter(mi); }

	MenuItem &addBefore(MenuItem &mi) {
		mi.after = this;
		before = &mi;
		if ( !mi.back ) mi.back = back;
		return mi;
	}
	MenuItem &addRight(MenuItem &mi) {
		mi.left = this;
		right = &mi;
		if ( !mi.back ) mi.back = back;
		return mi;
	}
	MenuItem &addAfter(MenuItem &mi) {
		mi.before = this;
		after = &mi;
		if ( !mi.back ) mi.back = back;
		return mi;
	}
	MenuItem &addLeft(MenuItem &mi) {
		mi.right = this;
		left = &mi;
		if ( !mi.back ) mi.back = back;
		return mi;
	}

protected:
	const __FlashStringHelper* name;
	const char shortkey;

	MenuItem *before;
	MenuItem *right;
	MenuItem *after;
	MenuItem *left;
	MenuItem *back;
};

/*
bool menuTestStrings(const char *a, const char *b) {
	while (*a) { if (*a != *b) { return false; } b++; a++; }
	return true;
}
bool operator==(MenuItem &lhs, char* test) {
	return menuTestStrings(lhs.getName(),test);
}
*/
bool operator==(const MenuItem &lhs, MenuItem &rhs) {
    return &lhs == &rhs;
}
bool operator!=(const MenuItem &lhs, MenuItem &rhs) {
    return &lhs != &rhs;
}

struct MenuChangeEvent
{
	const MenuItem &from;
	const MenuItem &to;
};

struct MenuUseEvent
{
	const MenuItem &item;
};

typedef void (*cb_change)(MenuChangeEvent);
typedef void (*cb_use)(MenuUseEvent);

class MenuBackend
{
public:
	MenuBackend(cb_use menuUse, cb_change menuChange = NULL) : root(F("MenuRoot")) {
		current = &root;
		cb_menuChange = menuChange;
		cb_menuUse = menuUse;
	}

	MenuItem &getRoot() {
		return root;
	}
	MenuItem &getCurrent() {
		return *current;
	}

	void moveBack() {
		setCurrent(current->getBack());
	}

	void moveUp() {
		setCurrent(current->moveUp());
	}

	void moveDown() {
		setCurrent(current->moveDown());
	}

	void moveLeft() {
		setCurrent(current->moveLeft());
	}

	void moveRight() {
		setCurrent(current->moveRight());
	}

	void use(char shortkey)
	{
		recursiveSearch(shortkey,&root);
		use();
	}
	
	void use() {
		//current->use();
		if (cb_menuUse) {
			MenuUseEvent mue = { *current };
			cb_menuUse(mue);
		}
	}

	void setCurrent(MenuItem *next) {
		if (next) {
			if (cb_menuChange) {
				MenuChangeEvent mce = { *current, *next };
				cb_menuChange(mce);
			}
			current = next;
		}
	}

private:
	void foundShortkeyItem(MenuItem *mi) {
		mi->setBack(current);
		current = mi;
	}
	char canSearch(const char shortkey, MenuItem *m) {
		if (m==0) { return 0; }
		else  {
			if (m->getShortkey()==shortkey) {
				foundShortkeyItem(m);
				return 1;
			}
			return -1;
		}
	}
	void rSAfter(const char shortkey, MenuItem *m) {
		if (canSearch(shortkey,m)!=1) {
			rSAfter(shortkey, m->getAfter());
			rSRight(shortkey, m->getRight());
			rSLeft(shortkey, m->getLeft());
		}
	}
	void rSRight(const char shortkey, MenuItem *m) {
		if (canSearch(shortkey,m)!=1) {
			rSAfter(shortkey, m->getAfter());
			rSRight(shortkey, m->getRight());
			rSBefore(shortkey, m->getBefore());
		}
	}
	void rSLeft(const char shortkey, MenuItem *m) {
		if (canSearch(shortkey,m)!=1) {
			rSAfter(shortkey, m->getAfter());
			rSLeft(shortkey, m->getLeft());
			rSBefore(shortkey, m->getBefore());
		}
	}
	void rSBefore(const char shortkey, MenuItem *m) {
		if (canSearch(shortkey,m)!=1) {
			rSRight(shortkey, m->getRight());
			rSLeft(shortkey, m->getLeft());
			rSBefore(shortkey, m->getBefore());
		}
	}
	void recursiveSearch(const char shortkey, MenuItem *m) {
		if (canSearch(shortkey,m)!=1) {
			rSAfter(shortkey, m->getAfter());
			rSRight(shortkey, m->getRight());
			rSLeft(shortkey, m->getLeft());
			rSBefore(shortkey, m->getBefore());
		}
	}
	
	MenuItem root;
	MenuItem *current;

	cb_change cb_menuChange;
	cb_use cb_menuUse;
};

#endif