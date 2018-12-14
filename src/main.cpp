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
#include <thread>
#include <iostream>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/empty.hpp"

using namespace std;
using std_msgs::msg::Empty;
using std::placeholders::_1;

void callback(Empty::UniquePtr /*msg*/, int foo){
  cout << "Received a msg and foo = " << foo << "\n";
}

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("bind_test");
  auto sub = node->create_subscription<Empty>("blind_test", [] (Empty::UniquePtr msg) {callback(move(msg), 7);});
  // auto sub = node->create_subscription<Empty>("bind_test", bind(callback, _1, 7));
  rclcpp::spin(node);
  rclcpp::shutdown();


  return 0;
}
