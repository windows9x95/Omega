#include <ion.h>
#include <assert.h>

#ifndef PATCH_LEVEL
#error This file expects PATCH_LEVEL to be defined
#endif

#ifndef EPSILON_VERSION
#error This file expects EPSILON_VERSION to be defined
#endif

#ifndef EPSILON_CUSTOM_VERSION
#error This file expects EPSILON_CUSTOM_VERSION to be defined
#endif

#ifndef HEADER_SECTION
#define HEADER_SECTION
#endif

namespace Ion {
extern char staticStorageArea[];
}
constexpr void * storageAddress = &(Ion::staticStorageArea);

class PlatformInfo {
public:
  constexpr PlatformInfo() :
    m_header(Magic),
    m_version{EPSILON_VERSION},
    m_patchLevel{PATCH_LEVEL},
    m_storageAddress(storageAddress),
    m_storageSize(Ion::Storage::k_storageSize),
    m_footer(Magic),
    m_ohm_header(OmegaMagic),
    m_customVersion{EPSILON_CUSTOM_VERSION},
#ifdef USERNAME
    m_username{USERNAME},
#else
    m_username{"\0"},
#endif
    m_ohm_footer(OmegaMagic) { }
  const char * version() const {
    assert(m_storageAddress != nullptr);
    assert(m_storageSize != 0);
    assert(m_header == Magic);
    assert(m_footer == Magic);
    assert(m_ohm_header == OmegaMagic);
    assert(m_ohm_footer == OmegaMagic);
    return m_version;
  }
  const char * customVersion() const {
    assert(m_storageAddress != nullptr);
    assert(m_storageSize != 0);
    assert(m_header == Magic);
    assert(m_footer == Magic);
    assert(m_ohm_header == OmegaMagic);
    assert(m_ohm_footer == OmegaMagic);
    return m_customVersion;
  }
#ifdef USERNAME
  const char * username() const {
    assert(m_storageAddress != nullptr);
    assert(m_storageSize != 0);
    assert(m_header == Magic);
    assert(m_footer == Magic);
    assert(m_ohm_header == OmegaMagic);
    assert(m_ohm_footer == OmegaMagic);
    return m_username;
  }
#endif
  const char * patchLevel() const {
    assert(m_storageAddress != nullptr);
    assert(m_storageSize != 0);
    assert(m_header == Magic);
    assert(m_footer == Magic);
    assert(m_ohm_header == OmegaMagic);
    assert(m_ohm_footer == OmegaMagic);
    return m_patchLevel;
  }
private:
  constexpr static uint32_t Magic = 0xDEC00DF0;
  constexpr static uint32_t OmegaMagic = 0xEFBEADDE;
  uint32_t m_header;
  const char m_version[8];
  const char m_patchLevel[8];
  void * m_storageAddress;
  size_t m_storageSize;
  uint32_t m_footer;
  uint32_t m_ohm_header;
  const char m_customVersion[16];
  const char m_username[16];
  uint32_t m_ohm_footer;
};

constexpr PlatformInfo HEADER_SECTION platform_infos;

const char * Ion::softwareVersion() {
  return platform_infos.version();
}

const char * Ion::customSoftwareVersion() {
  return platform_infos.customVersion();
}

#ifdef USERNAME
const char * Ion::username() {
  return platform_infos.username();
}
#endif

const char * Ion::patchLevel() {
  return platform_infos.patchLevel();
}
