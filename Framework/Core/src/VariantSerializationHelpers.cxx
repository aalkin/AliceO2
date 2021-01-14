// Copyright CERN and copyright holders of ALICE O2. This software is
// distributed under the terms of the GNU General Public License v3 (GPL
// Version 3), copied verbatim in the file "COPYING".
//
// See http://alice-o2.web.cern.ch/license for full licensing information.
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

#include "VariantSerializationHelpers.h"

using namespace rapidjson;
namespace o2::framework
{
bool VariantHandler::Null()
{
  debug << "Null";
  return true;
}
bool VariantHandler::Bool(bool b)
{
  debug << "Bool(" << b << ")";
  return true;
}
bool VariantHandler::Int(int i)
{
  debug << "Int(" << i << ")";
  return true;
}
bool VariantHandler::Uint(unsigned int i)
{
  debug << "Uint(" << i << ")";
  return true;
}
bool VariantHandler::Int64(int64_t i)
{
  debug << "Int64(" << i << ")";
  return true;
}
bool VariantHandler::Uint64(uint64_t i)
{
  debug << "Uint64(" << i << ")";
  return true;
}
bool VariantHandler::Double(double d)
{
  debug << "Double(" << d << ")";
  return true;
}
bool VariantHandler::RawNumber(const Ch* str, SizeType length, bool copy)
{
  debug << "RawNumber[" << length << "](" << str << "); copy = " << copy;
  return true;
}
bool VariantHandler::String(const Ch* str, SizeType length, bool copy)
{
  debug << "String[" << length << "](" << str << "); copy = " << copy;
  return true;
}
bool VariantHandler::StartObject()
{
  debug << "StartObject";
  return true;
}
bool VariantHandler::Key(const Ch* str, SizeType length, bool copy)
{
  debug << "Key[" << length << "](" << str << "); copy = " << copy;
  return true;
}
bool VariantHandler::EndObject(SizeType memberCount)
{
  debug << "EndObject[" << memberCount << "]";
  return true;
}
bool VariantHandler::StartArray()
{
  debug << "StartArray";
  return true;
}
bool VariantHandler::EndArray(SizeType elementCount)
{
  debug << "EndArray[" << elementCount << "]";
  return true;
}

Variant VariantSerializationHelpers::read(std::istream& s) {}
void VariantSerializationHelpers::write(std::ostream& s, const Variant& value) {}
} // namespace o2::framework
