
#ifndef _NNDEPLOY_DEVICE_DEVICE_H_
#define _NNDEPLOY_DEVICE_DEVICE_H_

#include "nndeploy/base/common.h"
#include "nndeploy/base/glic_stl_include.h"
#include "nndeploy/base/log.h"
#include "nndeploy/base/macro.h"
#include "nndeploy/base/object.h"
#include "nndeploy/base/status.h"
#include "nndeploy/device/type.h"

namespace nndeploy {
namespace device {

class Device;
class Buffer;

struct NNDEPLOY_CC_API DeviceInfo {
  base::DeviceType device_type_;
  bool is_support_fp16_ = false;
};

/**
 * @brief The Architecture class
 * @note 一般通过getArchitecture获取
 *
 */
class NNDEPLOY_CC_API Architecture : public base::NonCopyable {
 public:
  explicit Architecture(base::DeviceTypeCode device_type_code);

  virtual ~Architecture();

  virtual base::Status checkDevice(int device_id = 0,
                                   void *command_queue = nullptr,
                                   std::string library_path = "") = 0;

  virtual base::Status enableDevice(int device_id = 0,
                                    void *command_queue = nullptr,
                                    std::string library_path = "") = 0;

  virtual Device *getDevice(int device_id) = 0;

  virtual std::vector<DeviceInfo> getDeviceInfo(
      std::string library_path = "") = 0;

  base::DeviceTypeCode getDeviceTypeCode();

 protected:
  std::mutex mutex_;
  /**
   * @brief device_id -> device
   *
   */
  std::map<int, Device *> devices_;

 private:
  base::DeviceTypeCode device_type_code_;
};

std::map<base::DeviceTypeCode, std::shared_ptr<Architecture>> &
getArchitectureMap();

template <typename T>
class TypeArchitectureRegister {
 public:
  explicit TypeArchitectureRegister(base::DeviceTypeCode type) {
    auto &architecture_map = getArchitectureMap();
    if (architecture_map.find(type) == architecture_map.end()) {
      architecture_map[type] = std::shared_ptr<T>(new T(type));
    }
  }
};

/**
 * @brief
 *
 */
class NNDEPLOY_CC_API Device : public base::NonCopyable {
  friend class Architecture;

 public:
  virtual BufferDesc toBufferDesc(const TensorDesc &desc,
                                  const base::IntVector &config) = 0;

  virtual void *allocate(size_t size) = 0;
  virtual void *allocate(const BufferDesc &desc) = 0;

  virtual void deallocate(void *ptr) = 0;

  virtual base::Status copy(void *src, void *dst, size_t size,
                            int index = 0) = 0;
  virtual base::Status download(void *src, void *dst, size_t size,
                                int index = 0) = 0;
  virtual base::Status upload(void *src, void *dst, size_t size,
                              int index = 0) = 0;

  virtual base::Status copy(Buffer *src, Buffer *dst, int index = 0) = 0;
  virtual base::Status download(Buffer *src, Buffer *dst, int index = 0) = 0;
  virtual base::Status upload(Buffer *src, Buffer *dst, int index = 0) = 0;

  // TODO: map/unmap
  // virtual Buffer* map(Buffer* src);
  // virtual base::Status unmap(Buffer* src, Buffer* dst);
  // TODO: share? opencl / vpu / hvx?
  // virtual Buffer* share(Buffer* src);
  // virtual base::Status unshare(Buffer* src, Buffer* dst);

  virtual void *getContext();

  virtual base::Status newCommandQueue();
  virtual base::Status deleteCommandQueue(int index = -1);
  virtual base::Status deleteCommandQueue(void *command_queue);
  virtual base::Status setCommandQueue(void *command_queue);

  virtual void *getCommandQueue(int index = 0);

  virtual base::Status synchronize(int index = 0);

  base::DeviceType getDeviceType();

 protected:
  Device(base::DeviceType device_type, void *command_queue = nullptr,
         std::string library_path = "")
      : device_type_(device_type){};
  virtual ~Device(){};

  virtual base::Status init() = 0;
  virtual base::Status deinit() = 0;

 protected:
  base::DeviceType device_type_;
};

extern NNDEPLOY_CC_API Architecture *getArchitecture(base::DeviceTypeCode type);

extern NNDEPLOY_CC_API base::DeviceType getDefaultHostDeviceType();

extern NNDEPLOY_CC_API Device *getDefaultHostDevice();

extern NNDEPLOY_CC_API bool isHostDeviceType(base::DeviceType device_type);

extern NNDEPLOY_CC_API base::Status checkDevice(base::DeviceType device_type,
                                                void *command_queue,
                                                std::string library_path);

extern NNDEPLOY_CC_API base::Status enableDevice(base::DeviceType device_type,
                                                 void *command_queue,
                                                 std::string library_path);

extern NNDEPLOY_CC_API Device *getDevice(base::DeviceType device_type);

extern NNDEPLOY_CC_API std::vector<DeviceInfo> getDeviceInfo(
    base::DeviceTypeCode type, std::string library_path);

}  // namespace device
}  // namespace nndeploy

#endif