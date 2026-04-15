#ifndef SELECTIONMANAGER_H
#define SELECTIONMANAGER_H

#include <unordered_set>
#include "../view/graphicsobject.h"

class SelectionManager {
private:
    std::unordered_set<GraphicsObject*> m_selected;

public:
    void clear() {
        for (auto obj : m_selected) {
            obj->setSelectedVisual(false);
        }

        m_selected.clear();
    }

    void select(GraphicsObject* obj, bool multiselect) {
        if (!multiselect) {
            clear();
        }

        if (m_selected.contains(obj)) {
            obj->setSelectedVisual(false);
            m_selected.erase(obj);
        } else {
            obj->setSelectedVisual(true);
            m_selected.insert(obj);
        }
    }

    bool isSelected(GraphicsObject* obj) {
        return m_selected.contains(obj);
    }
};

#endif // SELECTIONMANAGER_H
