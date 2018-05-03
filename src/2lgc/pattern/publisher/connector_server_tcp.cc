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
#include <2lgc/pattern/publisher/connector_server_tcp.h>
#include <2lgc/poco/net.pb.h>
#include <poll.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cerrno>
#include <cstddef>
#include <iostream>
#include <memory>
#include <type_traits>
#include <utility>

template <typename T>
llgc::pattern::publisher::ConnectorServerTcp<T>::ConnectorServerTcp(
    std::shared_ptr<SubscriberInterface<T>> subscriber, std::string ip,
    uint16_t port)
    : ConnectorInterface<T>(subscriber),
      ip_(std::move(ip)),
      port_(port),
      socket_(-1),
      disposing_(false)
{
}

template <typename T>
llgc::pattern::publisher::ConnectorServerTcp<T>::~ConnectorServerTcp()
{
  // Properly stop recv and close file descriptor.
  disposing_ = true;
  receiver_.join();
}

template <typename T>
bool llgc::pattern::publisher::ConnectorServerTcp<T>::Equals(
    const ConnectorInterface<T> &connector) const
{
  const auto *connector_direct =
      dynamic_cast<const ConnectorServerTcp<T> *>(&connector);

  if (connector_direct == nullptr)
  {
    return false;
  }

  return this->subscriber_->Equals(*connector.GetSubscriber());
}

template <typename T>
bool llgc::pattern::publisher::ConnectorServerTcp<T>::AddSubscriber(
    uint32_t id_message)
{
  if (!Connect())
  {
    return false;
  }

  T actions;
  decltype(std::declval<T>().add_action()) action = actions.add_action();
  std::unique_ptr<msg::net::AddSubscriber> action_add =
      std::make_unique<msg::net::AddSubscriber>();
  action_add->set_id_message(id_message);
  action->set_allocated_add_subscriber(action_add.release());
  std::string action_in_string;
  if (!actions.SerializeToString(&action_in_string))
  {
    return false;
  }
  if (!Send(action_in_string))
  {
    return false;
  }
  return true;
}

template <typename T>
bool llgc::pattern::publisher::ConnectorServerTcp<T>::Send(
    const std::string &message)
{
  std::cout << "ConnectorServerTcp<T>::Send" << std::endl;
  ssize_t sendi = send(socket_, message.c_str(), message.length(), 0);
  if (sendi == -1)
  {
    std::cout << "errno" << errno << std::endl;
  }
  auto meslen = static_cast<ssize_t>(message.length());
  std::cout << "Client " << socket_ << " -> serveur A" << sendi << "B" << meslen
            << std::endl;
  return sendi == meslen;
}

template <typename T>
bool llgc::pattern::publisher::ConnectorServerTcp<T>::RemoveSubscriber(
    uint32_t id_message)
{
  if (!Connect())
  {
    return false;
  }

  T actions;
  decltype(std::declval<T>().add_action()) action = actions.add_action();
  std::unique_ptr<msg::net::RemoveSubscriber> action_add =
      std::make_unique<msg::net::RemoveSubscriber>();
  action_add->set_id_message(id_message);
  action->set_allocated_remove_subscriber(action_add.release());
  std::string action_in_string;
  if (!actions.SerializeToString(&action_in_string))
  {
    return false;
  }
  if (!Send(action_in_string))
  {
    return false;
  }
  return true;
}

template <typename T>
void llgc::pattern::publisher::ConnectorServerTcp<T>::Receiver()
{
  // NOLINTNEXTLINE(cppcoreguidelines-pro-type-member-init)
  struct pollfd fd;  // NOLINT(hicpp-member-init)
  fd.fd = socket_;
  fd.events = POLLIN;
  int retval;  // NS

  std::cout << "Client " << socket_ << " Start" << std::endl;

  do
  {
    retval = poll(&fd, 1, 50);

    // Problem: stop the thread.
    if (retval == -1)
    {
      std::cout << "Client " << socket_ << " Stop" << std::endl;
      disposing_ = true;
    }
    else if (retval == 0)
    {
      std::cout << "Client " << socket_ << " Nothing to read" << std::endl;
    }
    else if (retval != 0)
    {
      char client_message[1500];

      std::cout << "Client " << socket_ << " Waiting" << std::endl;
      ssize_t read_size =
          recv(socket_, client_message, sizeof(client_message), 0);
      if (read_size == -1 || read_size == 0)
      {
        std::cout << "Client " << socket_ << " Stop" << std::endl;
        disposing_ = true;
      }
      else
      {
        std::cout << "Client " << socket_ << " recv" << std::endl;
        T message;

        std::string client_string(client_message,
                                  static_cast<size_t>(read_size));
        if (!message.ParseFromString(client_string))
        {
          disposing_ = true;
        }
        else
        {
          this->subscriber_->Listen(message);
        }
      }
    }
  } while (!disposing_);

  close(socket_);
  socket_ = -1;

  std::cout << "Client " << socket_ << " End" << std::endl;
}

/* vim:set shiftwidth=2 softtabstop=2 expandtab: */