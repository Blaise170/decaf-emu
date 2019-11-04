#pragma once
#include "cafe_ghs_enum.h"
#include <libcpu/be2_struct.h>

namespace cafe::ghs
{

struct BaseTypeDescriptor;
struct TypeDescriptor;
struct VirtualTable;
using TypeIDStorage = uint32_t;

struct BaseTypeDescriptor
{
   be2_virt_ptr<TypeDescriptor> typeDescriptor;
   be2_val<uint32_t> flags;
};
CHECK_OFFSET(BaseTypeDescriptor, 0x00, typeDescriptor);
CHECK_OFFSET(BaseTypeDescriptor, 0x04, flags);
CHECK_SIZE(BaseTypeDescriptor, 0x08);

struct TypeDescriptor
{
   //! Pointer to virtual table for std::typeinfo
   be2_virt_ptr<VirtualTable> typeInfoVTable;

   //! Name of this type
   be2_virt_ptr<const char> name;

   //! Unique ID for this type
   be2_val<uint32_t> typeID;

   //! Pointer to a list of base types, the last base type has flags=0x1600
   be2_virt_ptr<BaseTypeDescriptor> baseTypes;
};
CHECK_OFFSET(TypeDescriptor, 0x00, typeInfoVTable);
CHECK_OFFSET(TypeDescriptor, 0x04, name);
CHECK_OFFSET(TypeDescriptor, 0x08, typeID);
CHECK_OFFSET(TypeDescriptor, 0x0C, baseTypes);
CHECK_SIZE(TypeDescriptor, 0x10);

struct VirtualTable
{
   be2_val<uint32_t> flags;
   be2_virt_ptr<void> ptr;
};
CHECK_OFFSET(VirtualTable, 0x00, flags);
CHECK_OFFSET(VirtualTable, 0x04, ptr);
CHECK_SIZE(VirtualTable, 0x08);

void
std_typeinfo_Destructor(virt_ptr<void> self,
                        ghs::DestructorFlags flags);

void
pure_virtual_called();

} // namespace cafe::ghs
