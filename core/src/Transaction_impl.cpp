module;
#include <fstream>
// nlohmann as of 3.12.0 cannot be used in module interface units
#include <chrono>
#include <nlohmann/json.hpp>
module Transaction;

namespace core {

std::chrono::year_month_day tryParseDate(
    const std::string& input, const std::vector<std::string>& formats) {
  for (const auto& fmt : formats) {
    std::istringstream in{input};
    std::chrono::year_month_day ymd;
    in >> std::chrono::parse(fmt, ymd);
    if (!in.fail()) {
      return ymd;
    }
  }
  throw std::runtime_error("Failed to parse date: " + input);
}

template<typename T>
  requires(std::same_as<T, std::string> || std::same_as<T, unsigned int>)
std::optional<T> tryFirstMatchingColumnValue(
    const std::vector<std::string>& column_names, const storage::CSVRow& row) {
  auto it = std::ranges::find_if(
      column_names, [&](const std::string& key) { return row.contains(key); });

  if (it == column_names.end())
    return std::nullopt;

  const auto& value = row.at(*it);

  if constexpr (std::same_as<T, std::string>) {
    return value;
  } else if constexpr (std::same_as<T, unsigned int>) {
    if (unsigned int result;
        std::from_chars(value.data(), value.data() + value.size(), result).ec
        == std::errc{}) {
      return result;
    }
  }

  return std::nullopt;
}

TransactionMapper::TransactionMapper(
    const std::filesystem::path& map_file_path) {
  std::ifstream file(map_file_path);
  if (!file) {
    throw std::runtime_error("Failed to open file: " + map_file_path.string());
  }

  nlohmann::json json_data;
  file >> json_data;

  date_formats_ = json_data["date_formats"].get<std::vector<std::string>>();

  for (const auto& [key, value] : json_data["mapping"].items()) {
    if (value.is_array()) {
      config_[key] = value.get<std::vector<std::string>>();
    } else {
      throw std::runtime_error("Invalid mapping format in file: "
                               + map_file_path.string());
    }
  }
}

std::vector<Transaction> TransactionMapper::map(
    const std::vector<storage::CSVRow>& rows) {
  std::vector<Transaction> transactions;

  for (const auto& row : rows) {
    auto date_str =
        tryFirstMatchingColumnValue<std::string>(config_["date"], row);
    auto amount =
        tryFirstMatchingColumnValue<unsigned int>(config_["amount"], row);

    if (!date_str.has_value() || !amount.has_value()) {
      throw std::runtime_error("Missing required fields in row: "
                               + nlohmann::json(row).dump());
    }

    auto date = tryParseDate(date_str.value(), date_formats_);
    TransactionBuilder builder{date, amount.value()};

    auto description =
        tryFirstMatchingColumnValue<std::string>(config_["description"], row);
    builder.description(description.value_or(""));

    transactions.push_back(builder.build());
  }

  return transactions;
}

}  // namespace core