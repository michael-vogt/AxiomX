#include "tool.h"

Tool::Tool(SnapManager* sm) {
    m_snap = sm;
}

bool Tool::currentlyWorking() {
    return m_currentlyWorking;
}