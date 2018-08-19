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

#include <2lgc/error/show.h>
#include <2lgc/net/linux.h>
#include <2lgc/pattern/publisher/connector_interface.h>
#include <2lgc/pattern/publisher/connector_subscriber_tcp.h>
#include <cassert>
#include <iostream>
#include <string>

template <typename T>
llgc::pattern::publisher::ConnectorSubscriberTcp<T>::ConnectorSubscriberTcp(
    std::shared_ptr<SubscriberInterface<T>> subscriber, int socket_fd)
    : ConnectorInterface<T>(subscriber), socket_(socket_fd)
{
}

template <typename T>
llgc::pattern::publisher::ConnectorSubscriberTcp<T>::~ConnectorSubscriberTcp() =
    default;

template <typename T>
bool llgc::pattern::publisher::ConnectorSubscriberTcp<T>::Equals(
    const ConnectorInterface<T> &connector) const
{
  const auto *connector_direct =
      dynamic_cast<const ConnectorSubscriberTcp<T> *>(&connector);

  if (connector_direct == nullptr)
  {
    return false;
  }

  return this->subscriber_->Equals(*connector.GetSubscriber());
}

template <typename T>
bool llgc::pattern::publisher::ConnectorSubscriberTcp<T>::AddSubscriber(
    uint32_t /*id_message*/)
{
  // Can't append.
  assert(false);
}

template <typename T>
bool llgc::pattern::publisher::ConnectorSubscriberTcp<T>::Send(const T &message)
{
  std::string message_in_string;
  BUGLIB(std::cout, message.SerializeToString(&message_in_string), false,
         "protobuf");
  BUGCONT(std::cout, llgc::net::Linux::Send(socket_, message_in_string), false);
  return true;
}

template <typename T>
bool llgc::pattern::publisher::ConnectorSubscriberTcp<T>::RemoveSubscriber(
    uint32_t /*id_message*/)
{
  // Can't append.
  assert(false);
}

/* vim:set shiftwidth=2 softtabstop=2 expandtab: */
