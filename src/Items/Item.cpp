#include "Item.h"

std::ostream& operator<<(std::ostream& out, Item const* item) {
	item->print(out);
	return out;
}