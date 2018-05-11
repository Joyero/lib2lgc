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

#ifndef PATTERN_COMMAND_UNDOMANAGER_H_
#define PATTERN_COMMAND_UNDOMANAGER_H_

#include <chrono>
#include <string>
#include <vector>

/**
 * @brief Namespace for the pattern command.
 */
namespace llgc::pattern::command
{
/**
 * @brief Interface that define command stored in class.
 */
template <typename T>
class Undomanager
{
 public:
  /**
   * @brief Default constructor.
   */
  Undomanager();

  /**
   * @brief Default destructor. Virtual because command is abstract.
   */
  virtual ~Undomanager() = default;

  /**
   * @brief Execute the command.
   *
   * @return true if no problem.
   */
  virtual bool Do() = 0;

  /**
   * @brief Undo the command.
   *
   * @return true if command change the model.
   */
  virtual bool Undo() = 0;

  /**
   * @brief Repeat the command.
   *
   * @return true if command change the model.
   */
  virtual bool Redo() = 0;

  /**
   * @brief Tell if the command change the model or just the gui (and should
   * not notify others instances).
   *
   * @return true if command change the model.
   */
  virtual bool ChangeModel() = 0;

  /**
   * @brief Return the description of the command.
   *
   * @return The description.
   */
  virtual const std::string& GetDescription() const = 0;

  /**
   * @brief Convert the command to a protobuf serialization.
   *
   * @return The protobuf string.
   */
  virtual const std::string& ToProtobuf() const = 0;

  /**
   * @brief
   *
   * @return List of element modifyed by type and description. To
   * UI undo description.
   */
  virtual std::vector<size_t> GetType() const = 0;

  /**
   * @brief
   *
   * @param[in,out] i
   *
   * @return
   */
  virtual std::vector<T> FindByZone(int i) const = 0;

 protected:
  /**
   * @brief Time of the execution of the command.
   */
  std::chrono::time_point<std::chrono::system_clock> time_start_;

  /**
   * @brief Duration of the execution of the command.
   */
  std::chrono::duration<double> duration_start_;
};

}  // namespace llgc::pattern::command

#endif  // PATTERN_COMMAND_UNDOMANAGER_H_

/* vim:set shiftwidth=2 softtabstop=2 expandtab: */