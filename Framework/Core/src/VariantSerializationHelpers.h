// Copyright CERN and copyright holders of ALICE O2. This software is
// distributed under the terms of the GNU General Public License v3 (GPL
// Version 3), copied verbatim in the file "COPYING".
//
// See http://alice-o2.web.cern.ch/license for full licensing information.
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

#include "Framework/Variant.h"
#include <ios>
#include <rapidjson/reader.h>
#include <rapidjson/prettywriter.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/ostreamwrapper.h>
#include <iosfwd>
#include <string>
#include <sstream>
#include <algorithm>
#include <memory>

namespace o2::framework
{
class VariantHandler : public rapidjson::BaseReaderHandler<rapidjson::UTF8<>, VariantHandler>
{
 public:
  bool Null();
  bool Bool(bool b);
  bool Int(int i);
  bool Uint(unsigned i);
  bool Int64(int64_t i);
  bool Uint64(uint64_t i);
  bool Double(double d);
  bool RawNumber(const Ch* str, rapidjson::SizeType length, bool copy);
  bool String(const Ch* str, rapidjson::SizeType length, bool copy);
  bool StartObject();
  bool Key(const Ch* str, rapidjson::SizeType length, bool copy);
  bool EndObject(rapidjson::SizeType memberCount);
  bool StartArray();
  bool EndArray(rapidjson::SizeType elementCount);

 private:
  enum State {
    ARRAY,
    ARRAY_2D
  } state_;

  Variant value;
  std::stringstream debug;
};

struct VariantSerializationHelpers {
  static Variant read(std::istream& s);
  static void write(std::ostream& s,
                    Variant const& value);
};

} // namespace o2::framework
