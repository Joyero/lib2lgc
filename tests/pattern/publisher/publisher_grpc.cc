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

// Test gRPC publisher

#include <2lgc/pattern/publisher/connector_interface.h>
#include <2lgc/pattern/publisher/connector_publisher_grpc.h>
#include <2lgc/pattern/publisher/connector_subscriber.h>
#include <2lgc/pattern/publisher/connector_subscriber_grpc.h>
#include <2lgc/pattern/publisher/publisher_grpc.h>
#include <2lgc/pattern/publisher/publisher_interface.h>
#include <2lgc/pattern/publisher/publisher_ip.h>
#include <2lgc/pattern/publisher/subscriber_local.h>
#include <2lgc/pattern/publisher/subscriber_server_grpc.h>
#include <2lgc/utils/count_lock.h>
#include <google/protobuf/stubs/common.h>
#include <grpcpp/impl/codegen/status.h>
#include <cassert>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <map>
#include <memory>
#include <thread>
#include "rpc.grpc.pb.h"
#include "rpc.pb.h"

#include <2lgc/pattern/publisher/connector_interface.cc>
#include <2lgc/pattern/publisher/connector_publisher_grpc.cc>
#include <2lgc/pattern/publisher/connector_subscriber.cc>
#include <2lgc/pattern/publisher/connector_subscriber_grpc.cc>
#include <2lgc/pattern/publisher/publisher_grpc.cc>
#include <2lgc/pattern/publisher/publisher_interface.cc>
#include <2lgc/pattern/publisher/publisher_ip.cc>
#include <2lgc/pattern/publisher/subscriber_local.cc>
#include <2lgc/pattern/publisher/subscriber_server_grpc.cc>

template class llgc::pattern::publisher::ConnectorInterface<
    llgc::protobuf::test::Rpc>;
template class llgc::pattern::publisher::ConnectorPublisherGrpc<
    llgc::protobuf::test::Rpc, llgc::protobuf::test::Greeter>;
template class llgc::pattern::publisher::ConnectorSubscriber<
    llgc::protobuf::test::Rpc>;
template class llgc::pattern::publisher::ConnectorSubscriberGrpc<
    llgc::protobuf::test::Rpc>;
template class llgc::pattern::publisher::PublisherInterface<
    llgc::protobuf::test::Rpc,
    std::shared_ptr<llgc::pattern::publisher::ConnectorInterface<
        llgc::protobuf::test::Rpc>>>;
template class llgc::pattern::publisher::PublisherIp<llgc::protobuf::test::Rpc>;
template class llgc::pattern::publisher::PublisherGrpc<
    llgc::protobuf::test::Rpc, llgc::protobuf::test::Greeter::Service>;
template class llgc::pattern::publisher::SubscriberLocal<
    llgc::protobuf::test::Rpc>;
template class llgc::pattern::publisher::SubscriberServerGrpc<
    llgc::protobuf::test::Rpc>;

/**
 * @brief Implementation of the subscriber.
 */
class Subscriber final : public llgc::pattern::publisher::SubscriberLocal<
                             llgc::protobuf::test::Rpc>
{
 public:
  explicit Subscriber(uint32_t id) : SubscriberLocal(id), value(0) {}
  ~Subscriber() override = default;
  Subscriber(Subscriber&& other) = delete;
  Subscriber(Subscriber const& other) = delete;
  Subscriber& operator=(Subscriber&& other) & = delete;
  Subscriber& operator=(Subscriber const& other) & = delete;

  bool Listen(const llgc::protobuf::test::Rpc& messages) override
  {
    for (int i = 0; i < messages.msg_size(); i++)
    {
      const auto& message = messages.msg(i);

      switch (message.data_case())
      {
        case llgc::protobuf::test::Rpc_Msg::DataCase::kTest:
        {
          value++;
          break;
        }
        case llgc::protobuf::test::Rpc_Msg::DataCase::DATA_NOT_SET:
        case llgc::protobuf::test::Rpc_Msg::DataCase::kAddSubscriber:
        case llgc::protobuf::test::Rpc_Msg::DataCase::kRemoveSubscriber:
        default:
          assert(false);
      }
    }
    return true;
  }
  size_t value;
};

static void WaitUpToTenSecond(const std::function<bool()>& test)
{
  std::chrono::time_point<std::chrono::system_clock> start, end;
  start = std::chrono::system_clock::now();
  do
  {
    end = std::chrono::system_clock::now();
    assert(
        static_cast<size_t>(
            std::chrono::duration_cast<std::chrono::milliseconds>(end - start)
                .count()) < 10000);
  } while (!test());
}

int main(int /* argc */, char* /* argv */ [])  // NS
{
  constexpr size_t delay = 30;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  auto server = std::make_unique<llgc::pattern::publisher::PublisherGrpc<
      llgc::protobuf::test::Rpc, llgc::protobuf::test::Greeter::Service>>(8890);
  assert(server->Listen());
  assert(server->Wait());
  std::this_thread::sleep_for(std::chrono::milliseconds(delay));

  auto subscriber = std::make_shared<Subscriber>(1);
  auto connector =
      std::make_shared<llgc::pattern::publisher::ConnectorPublisherGrpc<
          llgc::protobuf::test::Rpc, llgc::protobuf::test::Greeter>>(
          subscriber, "127.0.0.1", 8890);

  assert(
      connector->AddSubscriber(llgc::protobuf::test::Rpc_Msg::DataCase::kTest));
  std::this_thread::sleep_for(std::chrono::milliseconds(delay));

  assert(subscriber->value == 0);

  // Check first message.
  llgc::protobuf::test::Rpc messages;
  auto message = messages.add_msg();
  auto message_test = std::make_unique<llgc::protobuf::test::Rpc_Msg_Test>();
  message->set_allocated_test(message_test.release());
  assert(connector->Send(messages));
  WaitUpToTenSecond([&subscriber]() { return subscriber->value == 1; });

  // Test lock forward.
  subscriber->value = 0;
  {
    llgc::utils::thread::CountLock<size_t> lock = server->LockForward();
    assert(connector->Send(messages));
    // Wait one second to be sure that the message is not send.
    std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    assert(subscriber->value == 0);
  }
  WaitUpToTenSecond([&subscriber]() { return subscriber->value == 1; });

  // Remove the first subscriber.
  subscriber->value = 0;
  assert(connector->RemoveSubscriber(
      llgc::protobuf::test::Rpc_Msg::DataCase::kTest));
  std::this_thread::sleep_for(std::chrono::milliseconds(delay));
  assert(connector->Send(messages));
  std::this_thread::sleep_for(std::chrono::milliseconds(delay));
  assert(subscriber->value == 0);

  // Double insert
  assert(
      connector->AddSubscriber(llgc::protobuf::test::Rpc_Msg::DataCase::kTest));
  std::this_thread::sleep_for(std::chrono::milliseconds(delay));
  assert(
      connector->AddSubscriber(llgc::protobuf::test::Rpc_Msg::DataCase::kTest));
  std::this_thread::sleep_for(std::chrono::milliseconds(delay));
  assert(connector->Send(messages));
  assert(connector->RemoveSubscriber(
  WaitUpToTenSecond([&subscriber]() { return subscriber->value == 2; });
      llgc::protobuf::test::Rpc_Msg::DataCase::kTest));
  std::this_thread::sleep_for(std::chrono::milliseconds(delay));
  assert(connector->Send(messages));
  assert(connector->RemoveSubscriber(
  WaitUpToTenSecond([&subscriber]() { return subscriber->value == 3; });
      llgc::protobuf::test::Rpc_Msg::DataCase::kTest));
  std::this_thread::sleep_for(std::chrono::milliseconds(delay));
  assert(connector->Send(messages));
  std::this_thread::sleep_for(std::chrono::milliseconds(delay));
  assert(subscriber->value == 3);
  assert(!server->GetOptionFailAlreadySubscribed());
  server->SetOptionFailAlreadySubscribed(true);
  assert(
      connector->AddSubscriber(llgc::protobuf::test::Rpc_Msg::DataCase::kTest));
  std::this_thread::sleep_for(std::chrono::milliseconds(delay));
  // Here, AddSubscriber will not failed because the TCP server can't return a
  // value.
  assert(
      connector->AddSubscriber(llgc::protobuf::test::Rpc_Msg::DataCase::kTest));
  std::this_thread::sleep_for(std::chrono::milliseconds(delay));
  assert(connector->Send(messages));
  std::this_thread::sleep_for(std::chrono::milliseconds(delay));
  assert(subscriber->value == 4);

  connector.reset();
  server->Stop();
  server->JoinWait();

  google::protobuf::ShutdownProtobufLibrary();

  return 0;
}

/* vim:set shiftwidth=2 softtabstop=2 expandtab: */
