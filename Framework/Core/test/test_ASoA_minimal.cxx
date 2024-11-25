// Copyright 2019-2020 CERN and copyright holders of ALICE O2.
// See https://alice-o2.web.cern.ch/copyright for details of the copyright holders.
// All rights not expressly granted are reserved.
//
// This software is distributed under the terms of the GNU General Public
// License v3 (GPL Version 3), copied verbatim in the file "COPYING".
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

#include "Mocking.h"
#include "TestClasses.h"
#include "Framework/AnalysisTask.h"
#include "Framework/AnalysisDataModel.h"

#include <catch_amalgamated.hpp>

using namespace o2;
using namespace o2::framework;

namespace o2::aod
{
O2HASH("TestA/0");
namespace test
{
DECLARE_SOA_COLUMN(X, x, float);
DECLARE_SOA_COLUMN(Y, y, float);
} // namespace test
} // namespace o2::aod

TEST_CASE("TestMinimal")
{
  TableBuilder builderA;
  auto rowWriterA = builderA.persist<float, float>({"fX", "fY"});
  rowWriterA(0, 0.0f, 8.0f);
  rowWriterA(0, 1.0f, 9.0f);
  rowWriterA(0, 2.0f, 10.0f);
  rowWriterA(0, 3.0f, 11.0f);
  rowWriterA(0, 4.0f, 12.0f);
  rowWriterA(0, 5.0f, 13.0f);
  rowWriterA(0, 6.0f, 14.0f);
  rowWriterA(0, 7.0f, 15.0f);
  auto tableA = builderA.finalize();
  CHECK(tableA->num_rows() == 8);

  using TestA = soa::InPlaceTable<"TestA/0"_h, o2::soa::Index<>, aod::test::X, aod::test::Y>;
  using FilteredTest = o2::soa::Filtered<TestA>;
  using PartitionTest = Partition<TestA>;
  using PartitionFilteredTest = Partition<o2::soa::Filtered<TestA>>;
  using PartitionNestedFilteredTest = Partition<o2::soa::Filtered<o2::soa::Filtered<TestA>>>;
  using namespace o2::framework;

  TestA testA{tableA};
  auto i = 0;
  for (auto& p : testA) {
    CHECK(i == p.index());
    CHECK(i == p.x());
    CHECK(i == p.y() - 8);
    ++i;
  }

  PartitionTest p1 = aod::test::x < 4.0f;
  p1.bindTable(testA);
  CHECK(4 == p1.size());
  CHECK(p1.begin() != p1.end());
  i = 0;
  for (auto& p : p1) {
    CHECK(i == p.x());
    CHECK(i + 8 == p.y());
    CHECK(i == p.index());
    i++;
  }
  CHECK(i == 4);

  expressions::Filter f1 = aod::test::x < 4.0f;
  auto selection = expressions::createSelection(testA.asArrowTable(), f1);
  FilteredTest filtered{{testA.asArrowTable()}, o2::soa::selectionToVector(selection)};
  PartitionFilteredTest p2 = aod::test::y > 9.0f;
  p2.bindTable(filtered);

  CHECK(2 == p2.size());
  i = 0;
  for (auto& p : p2) {
    CHECK(i + 2 == p.x());
    CHECK(i + 10 == p.y());
    CHECK(i + 2 == p.index());
    i++;
  }
  CHECK(i == 2);

  PartitionNestedFilteredTest p3 = aod::test::x < 3.0f;
  p3.bindTable(*(p2.mFiltered));
  CHECK(1 == p3.size());
  i = 0;
  for (auto& p : p3) {
    CHECK(i + 2 == p.x());
    CHECK(i + 10 == p.y());
    CHECK(i + 2 == p.index());
    i++;
  }
  CHECK(i == 1);
}
