#include <utils/interfaces/IWithUserData.h>

namespace utils {
    IWithUserData::IWithUserData() : m_userData(nullptr) {
    }

    IWithUserData::~IWithUserData() {
        m_userData = nullptr;
    }
};