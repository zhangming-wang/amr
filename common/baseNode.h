#pragma once

#if defined(ARDUINO_ARCH_ESP32)

#include "baseTask.h"
#include "rclc/rclc.h"
#include "rosidl_runtime_c/primitives_sequence_functions.h"
#include "settings.h"
#include "soc/rtc_cntl_reg.h" // disable brownout problems
#include "soc/soc.h"          // disable brownout problems
#include "system.h"
#include <Arduino.h>
#include <WiFi.h>
#include <atomic>
#include <builtin_interfaces/msg/time.h>
#include <micro_ros_platformio.h>
#include <micro_ros_utilities/string_utilities.h>
#include <micro_ros_utilities/type_utilities.h>
#include <rcl/error_handling.h>
#include <rcl/rcl.h>
#include <rcl/time.h>
#include <rclc/executor.h>
#include <rclc/rclc.h>
#include <rcutils/error_handling.h>
#include <rosidl_runtime_c/string_functions.h>
#include <std_msgs/msg/empty.h>
#include <std_msgs/msg/int32.h>
#include <std_msgs/msg/string.h>
#include <string>

template <typename T>
class BaseNode : public BaseTaskSingleton<T> {

    friend class Singleton<T>;

protected:
    std::string node_name_, node_namespace_;
    std::string ip_;
    uint16_t port_, num_handles_ = 1;
    rcl_allocator_t allocator_;
    rclc_support_t support_;
    rcl_node_t node_;
    micro_ros_agent_locator locator_;
    rclc_executor_t executor_;
    rcl_time_point_value_t now_ns_;
    rcl_publisher_t serial_msg_publisher_, heartbeat_publisher_;
    rcl_timer_t heartbeat_timer_;
    bool support_initialized_ = false;
    bool node_initialized_ = false;
    bool executor_initialized_ = false;
    bool serial_msg_publisher_initialized_ = false;
    bool heartbeat_timer_initialized_ = false;
    bool heartbeat_publisher_initialized_ = false;
    std::atomic<bool> connected_{false};

    bool enable_heartbeat_{true};

    unsigned long check_connect_time_ = 0, last_check_connect_time_ = 0;

    std::string serial_msg_topic_name_, heartbeat_topic_name_;

protected:
    BaseNode() {
        ip_ = wifi_IP;
        port_ = micro_ros_port;

        this->task_name_ = "base_node_task";
        this->core_id_ = 0;
        this->priority_ = 9;
        this->stack_size_ = 16384;

        allocator_ = rcl_get_default_allocator();
        IPAddress agent_ip;
        agent_ip.fromString(String(ip_.c_str()));
        locator_.address = agent_ip;
        locator_.port = port_;

        check_connect_time_ = millis();
        last_check_connect_time_ = check_connect_time_;
    }

    virtual bool init_micro_ros() { return true; }
    virtual void clean_micro_ros() {}

    uint64_t get_now_ns() {
        rcl_ret_t ret = rcl_clock_get_now(&support_.clock, &now_ns_);
        if (ret != RCL_RET_OK) {
            Serial.printf("rcl_clock_get_now error: %d\n", ret);
            now_ns_ = 0;
        }
        return static_cast<uint64_t>(now_ns_);
    }

public:
    void update() override {
        if (connected_.load()) {
            check_connect_time_ = millis();
            if (check_connect_time_ - last_check_connect_time_ > 3000) {
                if (rmw_uros_ping_agent(10, 10) != RCL_RET_OK) {
                    Serial.println("ping agent failed, reconnecting...");
                    connected_.store(false);
                }
                if (monitor_wifi() == false) {
                    connected_.store(false);
                }
                last_check_connect_time_ = check_connect_time_;

                if (!connected_.load()) {
                    vTaskDelay(pdMS_TO_TICKS(500));
                    return;
                }
            }
            if (rclc_executor_spin_some(&executor_, RCL_MS_TO_NS(5)) != RCL_RET_OK) {
                Serial.println("rclc_executor_spin_some error");
                connected_.store(false);
                vTaskDelay(pdMS_TO_TICKS(500));
            } else {
                vTaskDelay(pdMS_TO_TICKS(5));
            }
        } else {
            if (monitor_wifi()) {
                Serial.println("\nWiFi connected, initializing micro_ros...");
                if (_init_micro_ros()) {
                    connected_.store(true);
                    check_connect_time_ = millis();
                    last_check_connect_time_ = check_connect_time_;
                    Serial.println("microRos node task is running...");
                } else {
                    Serial.println("microRos node init failed, try again...");
                    vTaskDelay(pdMS_TO_TICKS(500));
                    return;
                }
            } else {
                Serial.printf(".");
                vTaskDelay(pdMS_TO_TICKS(500));
            }
        }
    }

    static inline void serial_print(const std::string &msg) {
        Serial.println(msg.c_str());
        auto &instance = BaseNode<T>::instance();
        if (instance.connected() && instance.serial_msg_publisher_initialized_) {
            std_msgs__msg__String ros_msg;
            rosidl_runtime_c__String__init(&ros_msg.data);
            rosidl_runtime_c__String__assign(&ros_msg.data, msg.c_str());

            rcl_ret_t ret;
            ret = rcl_publish(&instance.serial_msg_publisher_, &ros_msg, NULL);
            if (ret != RCL_RET_OK) {
                Serial.printf("error: pub serial msg failed: %d\n", ret);
            }
        }
    }

    static inline void heartbeat_timer_callback(rcl_timer_t *timer, int64_t last_call_time) {
        auto &instance = BaseNode<T>::instance();
        if (instance.connected() && instance.heartbeat_publisher_initialized_) {
            std_msgs__msg__Empty msg;
            rcl_ret_t ret = rcl_publish(&instance.heartbeat_publisher_, &msg, NULL);
            if (ret != RCL_RET_OK) {
                Serial.printf("error: pub heartbeat msg failed: %d\n", ret);
            }
        }
    }

    bool connected() { return connected_.load(); }

private:
    bool _init_micro_ros() {
        if (WiFi.status() != WL_CONNECTED) {
            return false;
        }

        _clean_micro_ros();

        auto status = rmw_uros_set_custom_transport(
            false,
            (void *)&locator_,
            platformio_transport_open,
            platformio_transport_close,
            platformio_transport_write,
            platformio_transport_read);

        if (status != 0) {
            Serial.printf("rmw_uros_set_custom_transport error: %d\n", status);
            return false;
        }

        // set_microros_wifi_transports(const_cast<char *>(wifi_name_.c_str()), const_cast<char *>(wifi_passward_.c_str()), agent_ip, port_);

        if (rmw_uros_ping_agent(100, 10) != RCL_RET_OK) {
            Serial.println("ping agent failed!");
            return false;
        }

        rcl_ret_t ret;
        if (!support_initialized_) {
            ret = rclc_support_init(&support_, 0, NULL, &allocator_);
            if (ret != RCL_RET_OK) {
                Serial.printf("rclc_support_init error: %d\n", ret);
                return false;
            }
            support_initialized_ = true;
        }

        if (rmw_uros_sync_session(1000) != RMW_RET_OK) {
            Serial.println("rmw_uros_sync_session failed!");
            return false;
        } else {
            if (!rmw_uros_epoch_synchronized()) {
                Serial.println("time sync failed!");
                return false;
            }
        }

        if (!node_initialized_) {
            node_ = rcl_get_zero_initialized_node();
            ret = rclc_node_init_default(&node_, node_name_.c_str(), node_namespace_.c_str(), &support_);
            if (ret != RCL_RET_OK) {
                Serial.printf("rclc_node_init_default error: %d\n", ret);
                return false;
            }
            node_initialized_ = true;
        }
        if (!executor_initialized_) {
            ret = rclc_executor_init(&executor_, &support_.context, num_handles_, &allocator_);
            if (ret != RCL_RET_OK) {
                Serial.printf("rclc_executor_init error: %d\n", ret);
                return false;
            }
            executor_initialized_ = true;
        }
        if (!serial_msg_publisher_initialized_) {
            ret = rclc_publisher_init_default(&serial_msg_publisher_, &node_, ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, String), serial_msg_topic_name_.c_str());
            if (ret != RCL_RET_OK) {
                Serial.printf("serial_msg_publisher_:rclc_publisher_init_default error: %d\n", ret);
                return false;
            }
            serial_msg_publisher_initialized_ = true;
        }
        if (!heartbeat_publisher_initialized_) {
            ret = rclc_publisher_init_default(&heartbeat_publisher_, &node_, ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Empty), heartbeat_topic_name_.c_str());
            if (ret != RCL_RET_OK) {
                Serial.printf("heartbeat_publisher_:rclc_publisher_init_default error: %d\n", ret);
                return false;
            }
            heartbeat_publisher_initialized_ = true;
        }
        if (enable_heartbeat_) {
            if (!heartbeat_timer_initialized_) {
                ret = rclc_timer_init_default(&heartbeat_timer_, &support_, RCL_MS_TO_NS(1000), heartbeat_timer_callback);
                if (ret != RCL_RET_OK) {
                    Serial.printf("heartbeat_timer_: rclc_timer_init_default error: %d\n", ret);
                    return false;
                }
                ret = rclc_executor_add_timer(&executor_, &heartbeat_timer_);
                if (ret != RCL_RET_OK) {
                    ret = rcl_timer_fini(&heartbeat_timer_);
                    Serial.printf("heartbeat_timer_: rclc_executor_add_timer error: %d\n", ret);
                    return false;
                }
                heartbeat_timer_initialized_ = true;
            }
        }

        return init_micro_ros();
    }
    void _clean_micro_ros() {
        clean_micro_ros();

        rcl_ret_t ret;
        if (enable_heartbeat_) {
            if (heartbeat_timer_initialized_) {
                ret = rcl_timer_fini(&heartbeat_timer_);
                if (ret != RCL_RET_OK) {
                    Serial.printf("heartbeat_timer_: rcl_timer_fini error: %d\n", ret);
                }
                heartbeat_timer_initialized_ = false;
            }
        }
        if (heartbeat_publisher_initialized_) {
            ret = rcl_publisher_fini(&heartbeat_publisher_, &node_);
            if (ret != RCL_RET_OK) {
                Serial.printf("heartbeat_publisher_:rcl_publisher_fini error: %d\n", ret);
            }
            heartbeat_publisher_initialized_ = false;
        }
        if (serial_msg_publisher_initialized_) {
            ret = rcl_publisher_fini(&serial_msg_publisher_, &node_);
            if (ret != RCL_RET_OK) {
                Serial.printf("serial_msg_publisher_:rcl_publisher_fini error: %d\n", ret);
            }
            serial_msg_publisher_initialized_ = false;
        }
        if (executor_initialized_) {
            ret = rclc_executor_fini(&executor_);
            if (ret != RCL_RET_OK) {
                Serial.printf("executor_initialized_ error: %d\n", ret);
            }
            executor_initialized_ = false;
        }
        if (node_initialized_) {
            ret = rcl_node_fini(&node_);
            if (ret != RCL_RET_OK) {
                Serial.printf("rcl_node_fini error: %d\n", ret);
            }
            node_initialized_ = false;
        }
        if (support_initialized_) {
            ret = rclc_support_fini(&support_);
            if (ret != RCL_RET_OK) {
                Serial.printf("rclc_support_fini error: %d\n", ret);
            }
            support_initialized_ = false;
        }
    }
};

#endif // ARDUINO_ARCH_ESP32