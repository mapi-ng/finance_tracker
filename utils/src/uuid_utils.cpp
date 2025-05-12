module;
#include <uuid.h>

#include <algorithm>
export module Utils;

namespace utils {

export uuids::uuid generateUuidFromData(std::string_view data_string) {
  constexpr std::hash<std::string> hasher;
  const auto hash = hasher(std::string(data_string));

  std::array<uint8_t, 16> bytes{};
  std::memcpy(bytes.data(), &hash,
              std::min(sizeof(hash), static_cast<size_t>(16)));

  return {bytes};
}

export uuids::uuid generateUuid() {
  std::random_device rd;
  auto seed_data = std::array<int, std::mt19937::state_size>{};
  std::ranges::generate(seed_data, std::ref(rd));
  std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
  std::mt19937 generator(seq);
  uuids::uuid_random_generator gen{generator};
  return gen();
}

export inline uuids::uuid generateUuid(std::string_view str) {
  return uuids::uuid::from_string(str).value_or(uuids::uuid{});
}

}  // namespace utils