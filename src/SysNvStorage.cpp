#include <cstdlib>
#include <sysPlatform/SysNvStorage.h>

namespace SysPlatform {

const size_t NVSTORAGE_SIZE_BYTES = 4096;
NvStorage sysNvStorage;

struct NvStorage::_impl {
    uint8_t* data;
};

NvStorage::NvStorage()
: m_pimpl(std::make_unique<_impl>())
{
    m_pimpl->data = (uint8_t*)malloc(NVSTORAGE_SIZE_BYTES);
}

NvStorage::~NvStorage()
{
    if (m_pimpl->data) free(m_pimpl->data);
}

uint8_t NvStorage::read( int idx ) {
    return m_pimpl->data[idx];
}

void NvStorage::write( int idx, uint8_t val ) {
    m_pimpl->data[idx] = val;
}

void NvStorage::update( int idx, uint8_t in) {
    write(idx, in);
}

}
