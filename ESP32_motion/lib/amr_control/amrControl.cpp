#include "amrControl.h"

AMRControl &AMRControl::get_instance() {
    static AMRControl instance;
    return instance;
}

AMRControl::AMRControl() {
    mutex_ = xSemaphoreCreateMutex();
    control_queue_ = xQueueCreate(10, sizeof(int));

    amrNode_ = &AMRNode::get_instance();
    motionControl_ = &MotionControl::get_instance();
    mpu6050Control_ = &MPU6050Control::get_instance();
}
AMRControl::~AMRControl() {
}

void AMRControl::init() {
    xTaskCreatePinnedToCore(control_loop, "control_loop", 8192, this, 0, NULL, 1);
}

void AMRControl::start_task() {
    _start_control_timer();
}

void AMRControl::stop_task() {
    stop_move();
    _stop_control_timer();
}

void AMRControl::restart_task() {
    stop_task();
    delay(100);
    start_task();
}

void AMRControl::update() {
    static unsigned long last_time = 0, current_time = 0;
    current_time = millis();
    dt_ = (current_time - last_time) / 1000.0;
    last_time = current_time;

    motionControl_->update(dt_);
    mpu6050Control_->update();

    motionControl_->calculate();
    mpu6050Control_->calculate();

    amrNode_->publish_msgs();

    motionControl_->move();
}

QueueHandle_t &AMRControl::get_control_deque() {
    return control_queue_;
}

void AMRControl::control_loop(void *args) {
    auto control = static_cast<AMRControl *>(args);
    while (1) {
        int msg;
        if (xQueueReceive(control->get_control_deque(), &msg, portMAX_DELAY)) {
            control->update();
        }
    }
    vTaskDelete(NULL);
}

void AMRControl::control_timer_callback(void *args) {
    int trigger = 1;
    xQueueSendFromISR(AMRControl::get_instance().get_control_deque(), &trigger, NULL);
}

void AMRControl::_start_control_timer() {
    if (!control_timer_) {
        esp_timer_create_args_t timer_args = {
            .callback = &control_timer_callback,
            .arg = NULL,
            .name = "control_timer_callback"};
        auto ret = esp_timer_create(&timer_args, &control_timer_);
        if (ret != ESP_OK) {
            serial_print("control timer created failed.");
            Serial.print("Timer creation failed:");
            Serial.println(ret);
            control_timer_ = nullptr;
            return;
        } else {
            serial_print("control timer created success!");
        }
    }
    if (!esp_timer_is_active(control_timer_)) {
        uint64_t period = motionControl_->get_milliseconds() * 1000;
        auto ret = esp_timer_start_periodic(control_timer_, period);
        if (ret != ESP_OK) {
            serial_print("control timer start failed: " + ret);
        } else {
            serial_print("control timer start success!");
        }
    }
}

void AMRControl::_stop_control_timer() {
    stop_move();
    if (control_timer_ && esp_timer_is_active(control_timer_)) {
        esp_timer_stop(control_timer_);
    }
}