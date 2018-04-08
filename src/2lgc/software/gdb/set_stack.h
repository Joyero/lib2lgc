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

/**
 * @file set_stack.h
 * @brief Store and sort all stacks. Criterea of sort must be defined on
 * creation.
 */

#ifndef SOFTWARE_GDB_SET_STACK_H_
#define SOFTWARE_GDB_SET_STACK_H_

#include <2lgc/compatibility/visual_studio.h>
#include <2lgc/pattern/singleton/singleton_local.h>
#include <2lgc/software/gdb/stack.h>
#include <sys/types.h>
#include <cstddef>
#include <memory>
#include <mutex>
#include <set>
#include <string>
#include <vector>

namespace llgc::pattern::publisher
{
template <typename M>
class PublisherRemote;
}

/**
 * @brief Poco for software.
 */
namespace msg::software
{
class Gdbs;
}

/**
 * @brief Contains all classes to run and manipulate files generated by GDB.
 */
namespace llgc::software::gdb
{
class Backtrace;

/**
 * @brief Store and sort all stacks.
 *
 * @details Criterea of sort must be defined on creation.
 */
class SetStack
{
 public:
  /**
   * @brief Server publisher.
   */
  llgc::pattern::singleton::Local<
      llgc::pattern::publisher::PublisherRemote<msg::software::Gdbs>>
      server_;

  /**
   * @brief Default constructor.
   *
   * @param[in] with_source_only Ignore backtrace where source file is unknown.
   * @param[in] top_frame Number of frames from the top that must be identical
   * so two stacks are the same. Internally, this number can not exceeded the
   * number of frames.
   * @param[in] bottom_frame Number of frames from the bottom that must be
   * identical so two stacks are the same. Internally, this number can not
   * exceeded the number of frames.
   * @param[in] print_one_by_group Keep only one identical backtrace.
   */
  SetStack(bool with_source_only, size_t top_frame, size_t bottom_frame,
           bool print_one_by_group);

  /**
   * @brief Add a new stack. The file must contains only the full backtrace from
   * GDB.
   *
   * @param[in] filename The file to add.
   *
   * @return True if the file is a valid backtrace.
   */
  bool Add(const std::string& filename) CHK;

  /**
   * @brief Add new stacks based on files from a folder. All files must contains
   * only the full backtrace from GDB.
   *
   * @param[in] folder The folder where all *.btfull files are.
   * @param[in] nthread The number of threads if parallel is allowed.
   * @param[in] regex Regex that match file to read. If empty, all files will be
   * read.
   *
   * @return true if no problem.
   */
  bool AddRecursive(const std::string& folder, unsigned int nthread,
                    const std::string& regex) CHK;

  /**
   * @brief Add new stacks based on files from a list. All files must contains
   * only the full backtrace from GDB.
   *
   * @param[in] list The folder where all *.btfull files are.
   * @param[in] nthread The number of threads if parallel is allowed.
   *
   * @return true if no problem.
   */
  bool AddList(const std::string& list, unsigned int nthread) CHK;

  /**
   * @brief Get the number of stack.
   *
   * @return The number of stack.
   */
  size_t Count() const;

  /**
   * @brief Show all stacks grouped by condition passed with the constructor.
   */
  void Print();

  /**
   * @brief A local class that compare to stack and says if two stack looks to
   * be the same.
   */
  struct LocalCompare
  {
    /**
     * @brief Constructor with parameter of comparaison.
     *
     * @param[in] with_source_only Ignore backtrace where source file is
     * unknown.
     * @param[in] top_frame Number of frames from the top that must be identical
     * so two stacks are the same. Internally, this number can not exceeded the
     * number of frames.
     * @param[in] bottom_frame Number of frames from the bottom that must be
     * identical so two stacks are the same. Internally, this number can not
     * exceeded the number of frames.
     */
    LocalCompare(bool with_source_only, size_t top_frame, size_t bottom_frame);

    /**
     * @brief Function that compare two stacks.
     *
     * @param[in] i The first stack.
     * @param[in] j The second stack.
     *
     * @return If i < j based on argument from constructor.
     */
    bool operator()(const std::unique_ptr<Stack>& i,
                    const std::unique_ptr<Stack>& j);

    /**
     * @brief Prototype to get the backtrace from the top or from the bottom.
     *
     * @param[in] i The n-th backtrace.
     *
     * @return The backtrace. Throw an exception if out of boundary.
     */
    typedef const Backtrace& (Stack::*FunctionGetBacktrace)(size_t i) const;

    /**
     * @brief Helper to operator(). Compare two stacks from the top or from the
     * bottom.
     *
     * @param[in] nb_max_frames Number maximum of backtraces to compare.
     * @param[in] get_backtraces Compare from the top or from the bottom.
     * @param[in] i The first stack.
     * @param[in] j The second stack.
     *
     * @return -1 if i < j, 0 if i == j and -1 if i > j.
     */
    ssize_t CompareFrom(const size_t nb_max_frames,
                        FunctionGetBacktrace get_backtraces,
                        const std::unique_ptr<Stack>& i,
                        const std::unique_ptr<Stack>& j);

    /**
     * @brief Ignore backtrace where source file is unknown.
     */
    bool with_source_only_;

    /**
     * @brief Number of frames from the top that must be identical so two stacks
     * are the same. Internally, this number can not exceeded the number of
     * frames.
     */
    size_t top_frame_;

    /**
     * @brief Number of frames from the bottom that must be identical so two
     * stacks are the same. Internally, this number can not exceeded the number
     * of frames.
     */
    size_t bottom_frame_;
  };

  /**
   * @brief Get the nth stack of the set.
   *
   * @param[in] i the nth stack. First is at 0.
   *
   * @return A reference to the stack. The ith stack must exists.
   */
  const Stack& Get(size_t i) const;

  /**
   * @brief Return of the top stack.
   *
   * @return Begin of the const iterator.
   */
  Stack::Iter begin() const  // NS
  {
    return Stack::Iter(*this, 0);
  }

  /**
   * @brief Return after of the last stack.
   *
   * @return End of the const iterator.
   */
  Stack::Iter end() const  // NS
  {
    return Stack::Iter(*this, stack_.size());
  }

 private:
  /**
   * @brief Storage of all stacks sorted with parameter given by the
   * constructor.
   */
  std::multiset<std::unique_ptr<Stack>, LocalCompare> stack_;

  /**
   * @brief A internal mutex to use stack_ thread-safe.
   */
  mutable std::mutex mutex_stack_;

  /**
   * @brief Add the file only if no equivalent already added.
   */

  bool print_one_by_group_;
  /**
   * @brief Read in parallel a list of files that contains gdb backtraces.
   *
   * @param[in] all_files The list of files that contains gdb backtraces.
   * @param[in] nthread The number of threads with a maximum of
   * std::thread::hardware_concurrency()
   *
   * @return true if no problem.
   */
  bool ParallelAdd(const std::vector<std::string>& all_files,
                   unsigned int nthread) CHK;

  /**
   * @brief Set a message throw the server to tell that this file is invalid.
   *
   * @param[in] filename The filename that failed to be read.
   */
  void TellError(const std::string& filename);

  /**
   * @brief Send the message to all subscribers.
   *
   * @param[in] message The message to send.
   */
  void Forward(const std::shared_ptr<const std::string>& message);
};

}  // namespace llgc::software::gdb

#endif  // SOFTWARE_GDB_SET_STACK_H_

/* vim:set shiftwidth=2 softtabstop=2 expandtab: */
