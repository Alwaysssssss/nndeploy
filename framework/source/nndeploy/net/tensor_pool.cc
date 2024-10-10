

#include "nndeploy/net/tensor_pool.h"

namespace nndeploy {
namespace net {

TensorPool::TensorPool(device::Device *device,
                       std::vector<TensorWrapper *> &tensor_repository,
                       std::vector<OpWrapper *> &op_repository)
    : device_(device),
      tensor_repository_(tensor_repository),
      op_repository(op_repository) {}

TensorPool::~TensorPool() {}

std::vector<int> getOpOrderIndex(std::vector<OpWrapper *> &producers,
                                 std::vector<OpWrapper *> &consumers,
                                 std::vector<OpWrapper *> &op_repository) {
  std::vector<int> order_index;

  for (size_t i = 0; i < op_repository.size(); i++) {
    for (size_t j = 0; j < producers.size(); j++) {
      if (op_repository[i] == producers[j]) {
        order_index.push_back(i);
        break;
      }
    }

    for (size_t j = 0; j < consumers.size(); j++) {
      if (op_repository[i] == consumers[j]) {
        order_index.push_back(i);
        break;
      }
    }
  }

  return order_index;
}

bool isInterval(std::array<int, 2> &interval,
                std::vector<std::array<int, 2>> &intervals) {
  for (size_t i = 0; i < intervals.size(); i++) {
    if (interval[0] >= intervals[i][0] && interval[0] <= intervals[i][1]) {
      return true;
    }
    if (interval[1] >= intervals[i][0] && interval[1] <= intervals[i][1]) {
      return true;
    }
  }
  return false;
}

void tensorUsageRecordPrint(
    const std::vector<std::shared_ptr<TensorUsageRecord>>
        &tensor_usage_records) {
  // 统计tensor的个数，并累加大小
  size_t total_tensor_count = 0;
  size_t total_memory_size = 0;
  for (const auto &tensor_usage_record : tensor_usage_records) {
    total_tensor_count++;
    total_memory_size += tensor_usage_record->size_;
  }
  NNDEPLOY_LOGE("Total tensor count: %zu\n", total_tensor_count);
  NNDEPLOY_LOGE("Total memory size: %zu\n", total_memory_size);
}

void chunkPrint(const std::vector<std::shared_ptr<Chunk>> &chunks) {
  // 统计chunk的个数，并累加大小
  size_t total_chunk_count = 0;
  size_t total_chunk_size = 0;
  for (const auto &chunk : chunks) {
    total_chunk_count++;
    total_chunk_size += chunk->buffer_->getSize();
  }
  NNDEPLOY_LOGE("Total chunk count: %zu\n", total_chunk_count);
  NNDEPLOY_LOGE("Total chunk size: %zu\n", total_chunk_size);
}

}  // namespace net
}  // namespace nndeploy
