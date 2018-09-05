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

#ifndef PATTERN_PUBLISHER_PUBLISHER_GRPC_H_
#define PATTERN_PUBLISHER_PUBLISHER_GRPC_H_

#include <2lgc/compat.h>
#include <2lgc/pattern/publisher/publisher_ip.h>
#include <grpcpp/impl/codegen/status.h>
#include <cstdint>
#include <memory>
#include <type_traits>

namespace grpc
{
class Server;
class ServerContext;

template <class W, class R>
class ServerReaderWriter;
}  // namespace grpc

namespace google::protobuf
{
class Message;
}

namespace llgc::pattern::publisher
{
template <typename T, typename S>
class PublisherGrpc : public PublisherIp<T>, public S
{
  static_assert(std::is_base_of<::google::protobuf::Message, T>::value,
                "T must be a descendant of ::google::protobuf::Message.");

 public:
  explicit PublisherGrpc(uint16_t port);
#ifndef SWIG
  PublisherGrpc(PublisherGrpc&& other) = delete;
  PublisherGrpc(PublisherGrpc const& other) = delete;
  PublisherGrpc& operator=(PublisherGrpc&& other) = delete;
  PublisherGrpc& operator=(PublisherGrpc const& other) = delete;
#endif  // !SWIG
  ~PublisherGrpc() override;

  grpc::Status Talk(grpc::ServerContext* context,
                    grpc::ServerReaderWriter<T, T>* stream) override CHK;
  bool Listen() override CHK;
  bool Wait() override CHK;
  void Stop() override;

 private:
  std::unique_ptr<grpc::Server> server_;
};

}  // namespace llgc::pattern::publisher

#ifndef TEMPLATE_CLASS
#include <2lgc/pattern/publisher/publisher_grpc.cc>
#endif

#endif  // PATTERN_PUBLISHER_PUBLISHER_GRPC_H_

/* vim:set shiftwidth=2 softtabstop=2 expandtab: */
