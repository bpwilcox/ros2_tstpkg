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
#include <thread>       
#include <chrono>
#include "rclcpp/rclcpp.hpp"

using namespace std;

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  int list_fails = 0;
  int get_fails = 0;

	for (int i = 1; i < 1000; i++) {
		auto node = rclcpp::Node::make_shared("param_client_test");
    if (i % 100 == 0) {
      RCLCPP_INFO(node->get_logger(), "Attempt: %d", i);
    }
    int attempts = 0;
    bool successful = false;

    while (!successful && attempts < 5) {
      auto parameters_client = std::make_shared<rclcpp::AsyncParametersClient>(node, "/param_client_remote_node");
      
      if (!parameters_client->wait_for_service(100ms)) {
        RCLCPP_INFO(node->get_logger(), "Node Service Unavailable");
      continue;
      }

      auto parameter_list_future = parameters_client->list_parameters({}, 10);
      auto parameter_get_future = parameters_client->get_parameters({"foo"});

      if (rclcpp::spin_until_future_complete(node, parameter_list_future, std::chrono::duration<int64_t, std::milli>(100)) !=
        rclcpp::executor::FutureReturnCode::SUCCESS) {
        RCLCPP_ERROR(node->get_logger(), "Attempt: %d, list service call failed", i);
        attempts++;
        list_fails++;
        continue;
      } else {
        successful = true;
      }

      if (rclcpp::spin_until_future_complete(node, parameter_get_future, std::chrono::duration<int64_t, std::milli>(100)) !=
        rclcpp::executor::FutureReturnCode::SUCCESS)
      {
        RCLCPP_ERROR(node->get_logger(), "Attempt: %d, get service call failed", i);
        get_fails++;
        attempts++;
        continue;
      } else {
        successful = true;
        if (i % 100 ==0) {
          for (auto & parameter : parameter_get_future.get()) {
            RCLCPP_INFO(node->get_logger(), "foo is %f", parameter.get_value<double>());
          }
        }
      }
    }
  }


/* 	for (int i = 0; i < 100; i++)
	{
		auto node = rclcpp::Node::make_shared("param_client_test");
    RCLCPP_INFO(node->get_logger(), "Attempt: %d", i);
	  auto param_client = std::make_shared<rclcpp::SyncParametersClient>(node, "/param_client_remote_node");
    if (param_client->wait_for_service(100ms)) {
      auto param_list = param_client->list_parameters({}, 1);
      //param_client->get_parameters(param_list.names);
      param_client->get_parameters({"foo"});

    } else {
      RCLCPP_INFO(node->get_logger(), "Node Service Unavailable");
    }
	} */

  RCLCPP_INFO(rclcpp::get_logger("param_client_test"), "List_parameter fails: %d,  Get_parameter fails: %d", list_fails, get_fails);
  return 0;
}
