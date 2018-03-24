/* Copyright 2018 LE GARREC Vincent
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <2lgc/pattern/publisher/connector_interface.h>
#include <2lgc/pattern/publisher/publisher_base.h>
#include <2lgc/pattern/publisher/publisher_remote.h>
#include <cstdint>
#include <memory>
#include <type_traits>
#include <utility>

template <typename M>
pattern::publisher::PublisherRemote<M>::PublisherRemote()
    : PublisherBase<M>(), port_(0)
{
}

template <typename M>
pattern::publisher::PublisherRemote<M>::~PublisherRemote() = default;

// Do not fail if subscriber is already subscribed in the same id_message.
template <typename M>
bool pattern::publisher::PublisherRemote<M>::AddSubscriber(
    uint32_t id_message, std::shared_ptr<ConnectorInterface> subscriber)
{
  if (options_.add_fail_if_already_subscribed)
  {
    std::pair<SubscriberMap::const_iterator, SubscriberMap::const_iterator>
        iterpair = subscribers_.equal_range(id_message);

    auto it = iterpair.first;
    for (; it != iterpair.second; ++it)
    {
      if (it->second->Equals(subscriber.get()))
      {
        return false;
      }
    }
  }

  subscribers_.insert(std::pair<uint32_t, std::shared_ptr<ConnectorInterface>>(
      id_message, subscriber));

  return true;
}

template <typename M>
bool pattern::publisher::PublisherRemote<M>::RemoveSubscriber(
    uint32_t id_message, const std::shared_ptr<ConnectorInterface> &subscriber)
{
  // Check if Subscriber is already subscribed.
  std::pair<SubscriberMap::const_iterator, SubscriberMap::const_iterator>
      iterpair = subscribers_.equal_range(id_message);

  auto it = iterpair.first;
  for (; it != iterpair.second; ++it)
  {
    if (it->second.get()->Equals(subscriber.get()))
    {
      subscribers_.erase(it);
      return true;
    }
  }

  return false;
}

/* vim:set shiftwidth=2 softtabstop=2 expandtab: */