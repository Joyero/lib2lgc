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

#ifndef FILESYSTEM_FILES_H_
#define FILESYSTEM_FILES_H_

#include <2lgc/compatibility/visual_studio.h>
#include <string>
#include <vector>

namespace llgc::filesystem
{
/**
 * @brief Class that manipulate the filesystem.
 */
class Files
{
 public:
  /**
   * @brief List all files from a folder.
   *
   * @param[in] folder The root folder.
   * @param[in] regex The regex in javascript regex.
   * @param[out] files All the files. files is not clear if not empty.
   *
   * @return true if no problem.
   */
  static bool SearchRecursiveFiles(const std::string& folder,
                                   const std::string& regex,
                                   std::vector<std::string>* files) CHK;
};

}  // namespace llgc::filesystem

#endif  // FILESYSTEM_FILES_H_

/* vim:set shiftwidth=2 softtabstop=2 expandtab: */
