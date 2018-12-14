// Copyright (c) 2018 Intel Corporation
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <memory>
#include <string>
#include <chrono>
#include "rclcpp/rclcpp.hpp"

using namespace std;

int main(int argc, char ** argv)
{
	for (int i = 0; i < 100; i++)
	{
		auto node = rclcpp::Node::make_shared("param_client_test");
	  auto param_client = std::make_shared<rclcpp::SyncParametersClient>(node, "/test_node");
    param_client->list_parameters();
    param_client->get_parameters();
    delete node;
    delete param_client;
	}



  return 0;
}
