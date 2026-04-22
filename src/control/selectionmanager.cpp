#include "selectionmanager.h"

void SelectionManager::clear() {
    for (auto obj : m_selected) {
        obj->setSelectedVisual(false);
    }

    m_selected.clear();
}

void SelectionManager::select(GraphicsObject* obj, bool multiselect) {
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

bool SelectionManager::isSelected(GraphicsObject* obj) {
    return m_selected.contains(obj);
}