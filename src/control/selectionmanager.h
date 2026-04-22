#ifndef SELECTIONMANAGER_H
#define SELECTIONMANAGER_H

#include <unordered_set>
#include "../view/graphicsobject.h"

class SelectionManager {
private:
    std::unordered_set<GraphicsObject*> m_selected;

public:
    void clear();

    void select(GraphicsObject* obj, bool multiselect);

    bool isSelected(GraphicsObject* obj);
};

#endif // SELECTIONMANAGER_H
