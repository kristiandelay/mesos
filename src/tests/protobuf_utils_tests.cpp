// Licensed to the Apache Software Foundation (ASF) under one
// or more contributor license agreements.  See the NOTICE file
// distributed with this work for additional information
// regarding copyright ownership.  The ASF licenses this file
// to you under the Apache License, Version 2.0 (the
// "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <gtest/gtest.h>

#include <set>
#include <string>

#include <mesos/mesos.hpp>

#include "common/protobuf_utils.hpp"

using std::set;
using std::string;

namespace mesos {
namespace internal {
namespace tests {

// This tests that helper function `getRoles` can correctly
// get roles from multi-role FrameworkInfo and role from
// single-role FrameworkInfo.
TEST(ProtobufUtilTest, GetRoles)
{
  // Get roles from a multi-role framework.
  {
    FrameworkInfo frameworkInfo;
    frameworkInfo.add_capabilities()->set_type(
        FrameworkInfo::Capability::MULTI_ROLE);
    frameworkInfo.add_roles("bar");
    frameworkInfo.add_roles("qux");

    set<string> roles = protobuf::framework::getRoles(frameworkInfo);

    EXPECT_EQ(roles, set<string>({"qux", "bar"}));
  }

  // Get role from a single-role framework.
  {
    FrameworkInfo frameworkInfo;
    frameworkInfo.set_role("foo");

    set<string> roles = protobuf::framework::getRoles(frameworkInfo);

    EXPECT_EQ(roles, set<string>({"foo"}));
  }
}


} // namespace tests {
} // namespace internal {
} // namespace mesos {
