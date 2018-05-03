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

#ifndef PATTERN_PUBLISHER_CONNECTOR_SERVER_TCP_IPV4_H_
#define PATTERN_PUBLISHER_CONNECTOR_SERVER_TCP_IPV4_H_

#include <2lgc/compatibility/visual_studio.h>
#include <2lgc/pattern/publisher/connector_server_tcp.h>
#include <cstdint>
#include <memory>
#include <string>

/**
 * @brief Namespace for the pattern publisher.
 */
namespace llgc::pattern::publisher
{
template <typename T>
class SubscriberInterface;

/**
 * @brief IPV4 of ConnectorServerTcp.
 */
template <typename T>
class ConnectorServerTcpIpv4 : public ConnectorServerTcp<T>
{
 public:
  /**
   * @brief Default constructor.
   *
   * @param[in] subscriber The subscriber.
   * @param[in] ip The IP of the server.
   * @param[in] port The port of the server.
   */
  ConnectorServerTcpIpv4(std::shared_ptr<SubscriberInterface<T>> subscriber,
                         const std::string ip, uint16_t port);

  /**
   * @brief Default virtual destructor.
   */
  virtual ~ConnectorServerTcpIpv4();

  /**
   * @brief Delete copy constructor.
   *
   * @param[in] other The original.
   */
  ConnectorServerTcpIpv4(ConnectorServerTcpIpv4 &&other) = delete;

  /**
   * @brief Delete copy constructor.
   *
   * @param[in] other The original.
   */
  ConnectorServerTcpIpv4(ConnectorServerTcpIpv4 const &other) = delete;

  /**
   * @brief Delete the copy operator.
   *
   * @param[in] other The original.
   *
   * @return Delete function.
   */
  ConnectorServerTcpIpv4 &operator=(ConnectorServerTcpIpv4 &&other) = delete;

  /**
   * @brief Delete the copy operator.
   *
   * @param[in] other The original.
   *
   * @return Delete function.
   */
  ConnectorServerTcpIpv4 &operator=(ConnectorServerTcpIpv4 const &other) & =
      delete;

 protected:
  /**
   * @brief Start connection with server.
   *
   * @return true if no problem.
   */
  bool Connect() CHK;
};

}  // namespace llgc::pattern::publisher

#endif  // PATTERN_PUBLISHER_CONNECTOR_SERVER_TCP_IPV4_H_

/* vim:set shiftwidth=2 softtabstop=2 expandtab: */