module;
#include <filesystem>
#include <stdexcept>
export module Exceptions;

namespace utils {

export class FailedToOpenFile : public std::runtime_error {
 public:
  explicit FailedToOpenFile(const std::filesystem::path& path,
                            const std::string& error = "")
      : std::runtime_error("Failed to open file: " + path.string()
                           + "; Error: " + error) {}
};

export class FailedToParseJson : public std::runtime_error {
 public:
  explicit FailedToParseJson(const std::filesystem::path& path,
                             const std::string& error)
      : std::runtime_error("Failed to parse JSON file " + path.string()
                           + "; Error: " + error) {}
};

}  // namespace utils