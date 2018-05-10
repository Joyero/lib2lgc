/*
 *    Copyright 2018 LE GARREC Vincent
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file gdb.h
 * @brief Class that run gdb for various purpose.
 */

#ifndef SOFTWARE_GDB_GDB_SERVER_H_
#define SOFTWARE_GDB_GDB_SERVER_H_

#include <2lgc/compatibility/visual_studio.h>
#include <2lgc/pattern/singleton/singleton.h>
#include <string>

/**
 * @brief Namespace for the pattern publisher.
 */
namespace llgc::pattern::publisher
{
template <typename T>
class PublisherDirect;
}

/**
 * @brief List of Protobuf for software.
 */
namespace llgc::protobuf::software
{
class Gdb;
}

/**
 * @brief Contains all classes to run and manipulate files generated by GDB.
 */
namespace llgc::software::gdb
{
/**
 * @brief Class to run gdb for various purpose.
 */
class GdbServer : public llgc::pattern::singleton::Local<
                      llgc::pattern::publisher::PublisherDirect<
                          llgc::protobuf::software::Gdb>>
{
 public:
  /**
   * @brief Send the message to all subscribers.
   *
   * @param[in] message The message to send.
   *
   * @return true if no problem.
   */
  bool Forward(const std::string& message) CHK;
};

}  // namespace llgc::software::gdb

#endif  // SOFTWARE_GDB_GDB_SERVER_H_

/* vim:set shiftwidth=2 softtabstop=2 expandtab: */
