// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from camera_settings_service:srv/CameraSettingsService.idl
// generated code does not contain a copyright notice
#include "camera_settings_service/srv/detail/camera_settings_service__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

bool
camera_settings_service__srv__CameraSettingsService_Request__init(camera_settings_service__srv__CameraSettingsService_Request * msg)
{
  if (!msg) {
    return false;
  }
  // id
  // xclk_freq_hz
  // milliseconds
  // aec_value
  // mode
  // pin_pwdn
  // pin_reset
  // pin_xclk
  // pin_sccb_sda
  // pin_sccb_scl
  // pin_d7
  // pin_d6
  // pin_d5
  // pin_d4
  // pin_d3
  // pin_d2
  // pin_d1
  // pin_d0
  // pin_vsync
  // pin_href
  // pin_pclk
  // ledc_timer
  // ledc_channel
  // pixel_format
  // frame_size
  // jpeg_quality
  // fb_count
  // fb_location
  // grab_mode
  // conv_mode
  // sccb_i2c_port
  // pixformat
  // framesize
  // quality
  // brightness
  // contrast
  // saturation
  // sharpness
  // denoise
  // special_effect
  // wb_mode
  // awb
  // awb_gain
  // aec
  // aec2
  // ae_level
  // agc
  // agc_gain
  // gainceiling
  // bpc
  // wpc
  // raw_gma
  // lenc
  // hmirror
  // vflip
  // dcw
  // colorbar
  // enable_series_capture
  return true;
}

void
camera_settings_service__srv__CameraSettingsService_Request__fini(camera_settings_service__srv__CameraSettingsService_Request * msg)
{
  if (!msg) {
    return;
  }
  // id
  // xclk_freq_hz
  // milliseconds
  // aec_value
  // mode
  // pin_pwdn
  // pin_reset
  // pin_xclk
  // pin_sccb_sda
  // pin_sccb_scl
  // pin_d7
  // pin_d6
  // pin_d5
  // pin_d4
  // pin_d3
  // pin_d2
  // pin_d1
  // pin_d0
  // pin_vsync
  // pin_href
  // pin_pclk
  // ledc_timer
  // ledc_channel
  // pixel_format
  // frame_size
  // jpeg_quality
  // fb_count
  // fb_location
  // grab_mode
  // conv_mode
  // sccb_i2c_port
  // pixformat
  // framesize
  // quality
  // brightness
  // contrast
  // saturation
  // sharpness
  // denoise
  // special_effect
  // wb_mode
  // awb
  // awb_gain
  // aec
  // aec2
  // ae_level
  // agc
  // agc_gain
  // gainceiling
  // bpc
  // wpc
  // raw_gma
  // lenc
  // hmirror
  // vflip
  // dcw
  // colorbar
  // enable_series_capture
}

bool
camera_settings_service__srv__CameraSettingsService_Request__are_equal(const camera_settings_service__srv__CameraSettingsService_Request * lhs, const camera_settings_service__srv__CameraSettingsService_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // id
  if (lhs->id != rhs->id) {
    return false;
  }
  // xclk_freq_hz
  if (lhs->xclk_freq_hz != rhs->xclk_freq_hz) {
    return false;
  }
  // milliseconds
  if (lhs->milliseconds != rhs->milliseconds) {
    return false;
  }
  // aec_value
  if (lhs->aec_value != rhs->aec_value) {
    return false;
  }
  // mode
  if (lhs->mode != rhs->mode) {
    return false;
  }
  // pin_pwdn
  if (lhs->pin_pwdn != rhs->pin_pwdn) {
    return false;
  }
  // pin_reset
  if (lhs->pin_reset != rhs->pin_reset) {
    return false;
  }
  // pin_xclk
  if (lhs->pin_xclk != rhs->pin_xclk) {
    return false;
  }
  // pin_sccb_sda
  if (lhs->pin_sccb_sda != rhs->pin_sccb_sda) {
    return false;
  }
  // pin_sccb_scl
  if (lhs->pin_sccb_scl != rhs->pin_sccb_scl) {
    return false;
  }
  // pin_d7
  if (lhs->pin_d7 != rhs->pin_d7) {
    return false;
  }
  // pin_d6
  if (lhs->pin_d6 != rhs->pin_d6) {
    return false;
  }
  // pin_d5
  if (lhs->pin_d5 != rhs->pin_d5) {
    return false;
  }
  // pin_d4
  if (lhs->pin_d4 != rhs->pin_d4) {
    return false;
  }
  // pin_d3
  if (lhs->pin_d3 != rhs->pin_d3) {
    return false;
  }
  // pin_d2
  if (lhs->pin_d2 != rhs->pin_d2) {
    return false;
  }
  // pin_d1
  if (lhs->pin_d1 != rhs->pin_d1) {
    return false;
  }
  // pin_d0
  if (lhs->pin_d0 != rhs->pin_d0) {
    return false;
  }
  // pin_vsync
  if (lhs->pin_vsync != rhs->pin_vsync) {
    return false;
  }
  // pin_href
  if (lhs->pin_href != rhs->pin_href) {
    return false;
  }
  // pin_pclk
  if (lhs->pin_pclk != rhs->pin_pclk) {
    return false;
  }
  // ledc_timer
  if (lhs->ledc_timer != rhs->ledc_timer) {
    return false;
  }
  // ledc_channel
  if (lhs->ledc_channel != rhs->ledc_channel) {
    return false;
  }
  // pixel_format
  if (lhs->pixel_format != rhs->pixel_format) {
    return false;
  }
  // frame_size
  if (lhs->frame_size != rhs->frame_size) {
    return false;
  }
  // jpeg_quality
  if (lhs->jpeg_quality != rhs->jpeg_quality) {
    return false;
  }
  // fb_count
  if (lhs->fb_count != rhs->fb_count) {
    return false;
  }
  // fb_location
  if (lhs->fb_location != rhs->fb_location) {
    return false;
  }
  // grab_mode
  if (lhs->grab_mode != rhs->grab_mode) {
    return false;
  }
  // conv_mode
  if (lhs->conv_mode != rhs->conv_mode) {
    return false;
  }
  // sccb_i2c_port
  if (lhs->sccb_i2c_port != rhs->sccb_i2c_port) {
    return false;
  }
  // pixformat
  if (lhs->pixformat != rhs->pixformat) {
    return false;
  }
  // framesize
  if (lhs->framesize != rhs->framesize) {
    return false;
  }
  // quality
  if (lhs->quality != rhs->quality) {
    return false;
  }
  // brightness
  if (lhs->brightness != rhs->brightness) {
    return false;
  }
  // contrast
  if (lhs->contrast != rhs->contrast) {
    return false;
  }
  // saturation
  if (lhs->saturation != rhs->saturation) {
    return false;
  }
  // sharpness
  if (lhs->sharpness != rhs->sharpness) {
    return false;
  }
  // denoise
  if (lhs->denoise != rhs->denoise) {
    return false;
  }
  // special_effect
  if (lhs->special_effect != rhs->special_effect) {
    return false;
  }
  // wb_mode
  if (lhs->wb_mode != rhs->wb_mode) {
    return false;
  }
  // awb
  if (lhs->awb != rhs->awb) {
    return false;
  }
  // awb_gain
  if (lhs->awb_gain != rhs->awb_gain) {
    return false;
  }
  // aec
  if (lhs->aec != rhs->aec) {
    return false;
  }
  // aec2
  if (lhs->aec2 != rhs->aec2) {
    return false;
  }
  // ae_level
  if (lhs->ae_level != rhs->ae_level) {
    return false;
  }
  // agc
  if (lhs->agc != rhs->agc) {
    return false;
  }
  // agc_gain
  if (lhs->agc_gain != rhs->agc_gain) {
    return false;
  }
  // gainceiling
  if (lhs->gainceiling != rhs->gainceiling) {
    return false;
  }
  // bpc
  if (lhs->bpc != rhs->bpc) {
    return false;
  }
  // wpc
  if (lhs->wpc != rhs->wpc) {
    return false;
  }
  // raw_gma
  if (lhs->raw_gma != rhs->raw_gma) {
    return false;
  }
  // lenc
  if (lhs->lenc != rhs->lenc) {
    return false;
  }
  // hmirror
  if (lhs->hmirror != rhs->hmirror) {
    return false;
  }
  // vflip
  if (lhs->vflip != rhs->vflip) {
    return false;
  }
  // dcw
  if (lhs->dcw != rhs->dcw) {
    return false;
  }
  // colorbar
  if (lhs->colorbar != rhs->colorbar) {
    return false;
  }
  // enable_series_capture
  if (lhs->enable_series_capture != rhs->enable_series_capture) {
    return false;
  }
  return true;
}

bool
camera_settings_service__srv__CameraSettingsService_Request__copy(
  const camera_settings_service__srv__CameraSettingsService_Request * input,
  camera_settings_service__srv__CameraSettingsService_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // id
  output->id = input->id;
  // xclk_freq_hz
  output->xclk_freq_hz = input->xclk_freq_hz;
  // milliseconds
  output->milliseconds = input->milliseconds;
  // aec_value
  output->aec_value = input->aec_value;
  // mode
  output->mode = input->mode;
  // pin_pwdn
  output->pin_pwdn = input->pin_pwdn;
  // pin_reset
  output->pin_reset = input->pin_reset;
  // pin_xclk
  output->pin_xclk = input->pin_xclk;
  // pin_sccb_sda
  output->pin_sccb_sda = input->pin_sccb_sda;
  // pin_sccb_scl
  output->pin_sccb_scl = input->pin_sccb_scl;
  // pin_d7
  output->pin_d7 = input->pin_d7;
  // pin_d6
  output->pin_d6 = input->pin_d6;
  // pin_d5
  output->pin_d5 = input->pin_d5;
  // pin_d4
  output->pin_d4 = input->pin_d4;
  // pin_d3
  output->pin_d3 = input->pin_d3;
  // pin_d2
  output->pin_d2 = input->pin_d2;
  // pin_d1
  output->pin_d1 = input->pin_d1;
  // pin_d0
  output->pin_d0 = input->pin_d0;
  // pin_vsync
  output->pin_vsync = input->pin_vsync;
  // pin_href
  output->pin_href = input->pin_href;
  // pin_pclk
  output->pin_pclk = input->pin_pclk;
  // ledc_timer
  output->ledc_timer = input->ledc_timer;
  // ledc_channel
  output->ledc_channel = input->ledc_channel;
  // pixel_format
  output->pixel_format = input->pixel_format;
  // frame_size
  output->frame_size = input->frame_size;
  // jpeg_quality
  output->jpeg_quality = input->jpeg_quality;
  // fb_count
  output->fb_count = input->fb_count;
  // fb_location
  output->fb_location = input->fb_location;
  // grab_mode
  output->grab_mode = input->grab_mode;
  // conv_mode
  output->conv_mode = input->conv_mode;
  // sccb_i2c_port
  output->sccb_i2c_port = input->sccb_i2c_port;
  // pixformat
  output->pixformat = input->pixformat;
  // framesize
  output->framesize = input->framesize;
  // quality
  output->quality = input->quality;
  // brightness
  output->brightness = input->brightness;
  // contrast
  output->contrast = input->contrast;
  // saturation
  output->saturation = input->saturation;
  // sharpness
  output->sharpness = input->sharpness;
  // denoise
  output->denoise = input->denoise;
  // special_effect
  output->special_effect = input->special_effect;
  // wb_mode
  output->wb_mode = input->wb_mode;
  // awb
  output->awb = input->awb;
  // awb_gain
  output->awb_gain = input->awb_gain;
  // aec
  output->aec = input->aec;
  // aec2
  output->aec2 = input->aec2;
  // ae_level
  output->ae_level = input->ae_level;
  // agc
  output->agc = input->agc;
  // agc_gain
  output->agc_gain = input->agc_gain;
  // gainceiling
  output->gainceiling = input->gainceiling;
  // bpc
  output->bpc = input->bpc;
  // wpc
  output->wpc = input->wpc;
  // raw_gma
  output->raw_gma = input->raw_gma;
  // lenc
  output->lenc = input->lenc;
  // hmirror
  output->hmirror = input->hmirror;
  // vflip
  output->vflip = input->vflip;
  // dcw
  output->dcw = input->dcw;
  // colorbar
  output->colorbar = input->colorbar;
  // enable_series_capture
  output->enable_series_capture = input->enable_series_capture;
  return true;
}

camera_settings_service__srv__CameraSettingsService_Request *
camera_settings_service__srv__CameraSettingsService_Request__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  camera_settings_service__srv__CameraSettingsService_Request * msg = (camera_settings_service__srv__CameraSettingsService_Request *)allocator.allocate(sizeof(camera_settings_service__srv__CameraSettingsService_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(camera_settings_service__srv__CameraSettingsService_Request));
  bool success = camera_settings_service__srv__CameraSettingsService_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
camera_settings_service__srv__CameraSettingsService_Request__destroy(camera_settings_service__srv__CameraSettingsService_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    camera_settings_service__srv__CameraSettingsService_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
camera_settings_service__srv__CameraSettingsService_Request__Sequence__init(camera_settings_service__srv__CameraSettingsService_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  camera_settings_service__srv__CameraSettingsService_Request * data = NULL;

  if (size) {
    data = (camera_settings_service__srv__CameraSettingsService_Request *)allocator.zero_allocate(size, sizeof(camera_settings_service__srv__CameraSettingsService_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = camera_settings_service__srv__CameraSettingsService_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        camera_settings_service__srv__CameraSettingsService_Request__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
camera_settings_service__srv__CameraSettingsService_Request__Sequence__fini(camera_settings_service__srv__CameraSettingsService_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      camera_settings_service__srv__CameraSettingsService_Request__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

camera_settings_service__srv__CameraSettingsService_Request__Sequence *
camera_settings_service__srv__CameraSettingsService_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  camera_settings_service__srv__CameraSettingsService_Request__Sequence * array = (camera_settings_service__srv__CameraSettingsService_Request__Sequence *)allocator.allocate(sizeof(camera_settings_service__srv__CameraSettingsService_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = camera_settings_service__srv__CameraSettingsService_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
camera_settings_service__srv__CameraSettingsService_Request__Sequence__destroy(camera_settings_service__srv__CameraSettingsService_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    camera_settings_service__srv__CameraSettingsService_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
camera_settings_service__srv__CameraSettingsService_Request__Sequence__are_equal(const camera_settings_service__srv__CameraSettingsService_Request__Sequence * lhs, const camera_settings_service__srv__CameraSettingsService_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!camera_settings_service__srv__CameraSettingsService_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
camera_settings_service__srv__CameraSettingsService_Request__Sequence__copy(
  const camera_settings_service__srv__CameraSettingsService_Request__Sequence * input,
  camera_settings_service__srv__CameraSettingsService_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(camera_settings_service__srv__CameraSettingsService_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    camera_settings_service__srv__CameraSettingsService_Request * data =
      (camera_settings_service__srv__CameraSettingsService_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!camera_settings_service__srv__CameraSettingsService_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          camera_settings_service__srv__CameraSettingsService_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!camera_settings_service__srv__CameraSettingsService_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


bool
camera_settings_service__srv__CameraSettingsService_Response__init(camera_settings_service__srv__CameraSettingsService_Response * msg)
{
  if (!msg) {
    return false;
  }
  // id
  // xclk_freq_hz
  // milliseconds
  // aec_value
  // state
  // pin_pwdn
  // pin_reset
  // pin_xclk
  // pin_sccb_sda
  // pin_sccb_scl
  // pin_d7
  // pin_d6
  // pin_d5
  // pin_d4
  // pin_d3
  // pin_d2
  // pin_d1
  // pin_d0
  // pin_vsync
  // pin_href
  // pin_pclk
  // ledc_timer
  // ledc_channel
  // pixel_format
  // frame_size
  // jpeg_quality
  // fb_count
  // fb_location
  // grab_mode
  // conv_mode
  // sccb_i2c_port
  // pixformat
  // framesize
  // quality
  // brightness
  // contrast
  // saturation
  // sharpness
  // denoise
  // special_effect
  // wb_mode
  // awb
  // awb_gain
  // aec
  // aec2
  // ae_level
  // agc
  // agc_gain
  // gainceiling
  // bpc
  // wpc
  // raw_gma
  // lenc
  // hmirror
  // vflip
  // dcw
  // colorbar
  // enable_series_capture
  return true;
}

void
camera_settings_service__srv__CameraSettingsService_Response__fini(camera_settings_service__srv__CameraSettingsService_Response * msg)
{
  if (!msg) {
    return;
  }
  // id
  // xclk_freq_hz
  // milliseconds
  // aec_value
  // state
  // pin_pwdn
  // pin_reset
  // pin_xclk
  // pin_sccb_sda
  // pin_sccb_scl
  // pin_d7
  // pin_d6
  // pin_d5
  // pin_d4
  // pin_d3
  // pin_d2
  // pin_d1
  // pin_d0
  // pin_vsync
  // pin_href
  // pin_pclk
  // ledc_timer
  // ledc_channel
  // pixel_format
  // frame_size
  // jpeg_quality
  // fb_count
  // fb_location
  // grab_mode
  // conv_mode
  // sccb_i2c_port
  // pixformat
  // framesize
  // quality
  // brightness
  // contrast
  // saturation
  // sharpness
  // denoise
  // special_effect
  // wb_mode
  // awb
  // awb_gain
  // aec
  // aec2
  // ae_level
  // agc
  // agc_gain
  // gainceiling
  // bpc
  // wpc
  // raw_gma
  // lenc
  // hmirror
  // vflip
  // dcw
  // colorbar
  // enable_series_capture
}

bool
camera_settings_service__srv__CameraSettingsService_Response__are_equal(const camera_settings_service__srv__CameraSettingsService_Response * lhs, const camera_settings_service__srv__CameraSettingsService_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // id
  if (lhs->id != rhs->id) {
    return false;
  }
  // xclk_freq_hz
  if (lhs->xclk_freq_hz != rhs->xclk_freq_hz) {
    return false;
  }
  // milliseconds
  if (lhs->milliseconds != rhs->milliseconds) {
    return false;
  }
  // aec_value
  if (lhs->aec_value != rhs->aec_value) {
    return false;
  }
  // state
  if (lhs->state != rhs->state) {
    return false;
  }
  // pin_pwdn
  if (lhs->pin_pwdn != rhs->pin_pwdn) {
    return false;
  }
  // pin_reset
  if (lhs->pin_reset != rhs->pin_reset) {
    return false;
  }
  // pin_xclk
  if (lhs->pin_xclk != rhs->pin_xclk) {
    return false;
  }
  // pin_sccb_sda
  if (lhs->pin_sccb_sda != rhs->pin_sccb_sda) {
    return false;
  }
  // pin_sccb_scl
  if (lhs->pin_sccb_scl != rhs->pin_sccb_scl) {
    return false;
  }
  // pin_d7
  if (lhs->pin_d7 != rhs->pin_d7) {
    return false;
  }
  // pin_d6
  if (lhs->pin_d6 != rhs->pin_d6) {
    return false;
  }
  // pin_d5
  if (lhs->pin_d5 != rhs->pin_d5) {
    return false;
  }
  // pin_d4
  if (lhs->pin_d4 != rhs->pin_d4) {
    return false;
  }
  // pin_d3
  if (lhs->pin_d3 != rhs->pin_d3) {
    return false;
  }
  // pin_d2
  if (lhs->pin_d2 != rhs->pin_d2) {
    return false;
  }
  // pin_d1
  if (lhs->pin_d1 != rhs->pin_d1) {
    return false;
  }
  // pin_d0
  if (lhs->pin_d0 != rhs->pin_d0) {
    return false;
  }
  // pin_vsync
  if (lhs->pin_vsync != rhs->pin_vsync) {
    return false;
  }
  // pin_href
  if (lhs->pin_href != rhs->pin_href) {
    return false;
  }
  // pin_pclk
  if (lhs->pin_pclk != rhs->pin_pclk) {
    return false;
  }
  // ledc_timer
  if (lhs->ledc_timer != rhs->ledc_timer) {
    return false;
  }
  // ledc_channel
  if (lhs->ledc_channel != rhs->ledc_channel) {
    return false;
  }
  // pixel_format
  if (lhs->pixel_format != rhs->pixel_format) {
    return false;
  }
  // frame_size
  if (lhs->frame_size != rhs->frame_size) {
    return false;
  }
  // jpeg_quality
  if (lhs->jpeg_quality != rhs->jpeg_quality) {
    return false;
  }
  // fb_count
  if (lhs->fb_count != rhs->fb_count) {
    return false;
  }
  // fb_location
  if (lhs->fb_location != rhs->fb_location) {
    return false;
  }
  // grab_mode
  if (lhs->grab_mode != rhs->grab_mode) {
    return false;
  }
  // conv_mode
  if (lhs->conv_mode != rhs->conv_mode) {
    return false;
  }
  // sccb_i2c_port
  if (lhs->sccb_i2c_port != rhs->sccb_i2c_port) {
    return false;
  }
  // pixformat
  if (lhs->pixformat != rhs->pixformat) {
    return false;
  }
  // framesize
  if (lhs->framesize != rhs->framesize) {
    return false;
  }
  // quality
  if (lhs->quality != rhs->quality) {
    return false;
  }
  // brightness
  if (lhs->brightness != rhs->brightness) {
    return false;
  }
  // contrast
  if (lhs->contrast != rhs->contrast) {
    return false;
  }
  // saturation
  if (lhs->saturation != rhs->saturation) {
    return false;
  }
  // sharpness
  if (lhs->sharpness != rhs->sharpness) {
    return false;
  }
  // denoise
  if (lhs->denoise != rhs->denoise) {
    return false;
  }
  // special_effect
  if (lhs->special_effect != rhs->special_effect) {
    return false;
  }
  // wb_mode
  if (lhs->wb_mode != rhs->wb_mode) {
    return false;
  }
  // awb
  if (lhs->awb != rhs->awb) {
    return false;
  }
  // awb_gain
  if (lhs->awb_gain != rhs->awb_gain) {
    return false;
  }
  // aec
  if (lhs->aec != rhs->aec) {
    return false;
  }
  // aec2
  if (lhs->aec2 != rhs->aec2) {
    return false;
  }
  // ae_level
  if (lhs->ae_level != rhs->ae_level) {
    return false;
  }
  // agc
  if (lhs->agc != rhs->agc) {
    return false;
  }
  // agc_gain
  if (lhs->agc_gain != rhs->agc_gain) {
    return false;
  }
  // gainceiling
  if (lhs->gainceiling != rhs->gainceiling) {
    return false;
  }
  // bpc
  if (lhs->bpc != rhs->bpc) {
    return false;
  }
  // wpc
  if (lhs->wpc != rhs->wpc) {
    return false;
  }
  // raw_gma
  if (lhs->raw_gma != rhs->raw_gma) {
    return false;
  }
  // lenc
  if (lhs->lenc != rhs->lenc) {
    return false;
  }
  // hmirror
  if (lhs->hmirror != rhs->hmirror) {
    return false;
  }
  // vflip
  if (lhs->vflip != rhs->vflip) {
    return false;
  }
  // dcw
  if (lhs->dcw != rhs->dcw) {
    return false;
  }
  // colorbar
  if (lhs->colorbar != rhs->colorbar) {
    return false;
  }
  // enable_series_capture
  if (lhs->enable_series_capture != rhs->enable_series_capture) {
    return false;
  }
  return true;
}

bool
camera_settings_service__srv__CameraSettingsService_Response__copy(
  const camera_settings_service__srv__CameraSettingsService_Response * input,
  camera_settings_service__srv__CameraSettingsService_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // id
  output->id = input->id;
  // xclk_freq_hz
  output->xclk_freq_hz = input->xclk_freq_hz;
  // milliseconds
  output->milliseconds = input->milliseconds;
  // aec_value
  output->aec_value = input->aec_value;
  // state
  output->state = input->state;
  // pin_pwdn
  output->pin_pwdn = input->pin_pwdn;
  // pin_reset
  output->pin_reset = input->pin_reset;
  // pin_xclk
  output->pin_xclk = input->pin_xclk;
  // pin_sccb_sda
  output->pin_sccb_sda = input->pin_sccb_sda;
  // pin_sccb_scl
  output->pin_sccb_scl = input->pin_sccb_scl;
  // pin_d7
  output->pin_d7 = input->pin_d7;
  // pin_d6
  output->pin_d6 = input->pin_d6;
  // pin_d5
  output->pin_d5 = input->pin_d5;
  // pin_d4
  output->pin_d4 = input->pin_d4;
  // pin_d3
  output->pin_d3 = input->pin_d3;
  // pin_d2
  output->pin_d2 = input->pin_d2;
  // pin_d1
  output->pin_d1 = input->pin_d1;
  // pin_d0
  output->pin_d0 = input->pin_d0;
  // pin_vsync
  output->pin_vsync = input->pin_vsync;
  // pin_href
  output->pin_href = input->pin_href;
  // pin_pclk
  output->pin_pclk = input->pin_pclk;
  // ledc_timer
  output->ledc_timer = input->ledc_timer;
  // ledc_channel
  output->ledc_channel = input->ledc_channel;
  // pixel_format
  output->pixel_format = input->pixel_format;
  // frame_size
  output->frame_size = input->frame_size;
  // jpeg_quality
  output->jpeg_quality = input->jpeg_quality;
  // fb_count
  output->fb_count = input->fb_count;
  // fb_location
  output->fb_location = input->fb_location;
  // grab_mode
  output->grab_mode = input->grab_mode;
  // conv_mode
  output->conv_mode = input->conv_mode;
  // sccb_i2c_port
  output->sccb_i2c_port = input->sccb_i2c_port;
  // pixformat
  output->pixformat = input->pixformat;
  // framesize
  output->framesize = input->framesize;
  // quality
  output->quality = input->quality;
  // brightness
  output->brightness = input->brightness;
  // contrast
  output->contrast = input->contrast;
  // saturation
  output->saturation = input->saturation;
  // sharpness
  output->sharpness = input->sharpness;
  // denoise
  output->denoise = input->denoise;
  // special_effect
  output->special_effect = input->special_effect;
  // wb_mode
  output->wb_mode = input->wb_mode;
  // awb
  output->awb = input->awb;
  // awb_gain
  output->awb_gain = input->awb_gain;
  // aec
  output->aec = input->aec;
  // aec2
  output->aec2 = input->aec2;
  // ae_level
  output->ae_level = input->ae_level;
  // agc
  output->agc = input->agc;
  // agc_gain
  output->agc_gain = input->agc_gain;
  // gainceiling
  output->gainceiling = input->gainceiling;
  // bpc
  output->bpc = input->bpc;
  // wpc
  output->wpc = input->wpc;
  // raw_gma
  output->raw_gma = input->raw_gma;
  // lenc
  output->lenc = input->lenc;
  // hmirror
  output->hmirror = input->hmirror;
  // vflip
  output->vflip = input->vflip;
  // dcw
  output->dcw = input->dcw;
  // colorbar
  output->colorbar = input->colorbar;
  // enable_series_capture
  output->enable_series_capture = input->enable_series_capture;
  return true;
}

camera_settings_service__srv__CameraSettingsService_Response *
camera_settings_service__srv__CameraSettingsService_Response__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  camera_settings_service__srv__CameraSettingsService_Response * msg = (camera_settings_service__srv__CameraSettingsService_Response *)allocator.allocate(sizeof(camera_settings_service__srv__CameraSettingsService_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(camera_settings_service__srv__CameraSettingsService_Response));
  bool success = camera_settings_service__srv__CameraSettingsService_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
camera_settings_service__srv__CameraSettingsService_Response__destroy(camera_settings_service__srv__CameraSettingsService_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    camera_settings_service__srv__CameraSettingsService_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
camera_settings_service__srv__CameraSettingsService_Response__Sequence__init(camera_settings_service__srv__CameraSettingsService_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  camera_settings_service__srv__CameraSettingsService_Response * data = NULL;

  if (size) {
    data = (camera_settings_service__srv__CameraSettingsService_Response *)allocator.zero_allocate(size, sizeof(camera_settings_service__srv__CameraSettingsService_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = camera_settings_service__srv__CameraSettingsService_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        camera_settings_service__srv__CameraSettingsService_Response__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
camera_settings_service__srv__CameraSettingsService_Response__Sequence__fini(camera_settings_service__srv__CameraSettingsService_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      camera_settings_service__srv__CameraSettingsService_Response__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

camera_settings_service__srv__CameraSettingsService_Response__Sequence *
camera_settings_service__srv__CameraSettingsService_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  camera_settings_service__srv__CameraSettingsService_Response__Sequence * array = (camera_settings_service__srv__CameraSettingsService_Response__Sequence *)allocator.allocate(sizeof(camera_settings_service__srv__CameraSettingsService_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = camera_settings_service__srv__CameraSettingsService_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
camera_settings_service__srv__CameraSettingsService_Response__Sequence__destroy(camera_settings_service__srv__CameraSettingsService_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    camera_settings_service__srv__CameraSettingsService_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
camera_settings_service__srv__CameraSettingsService_Response__Sequence__are_equal(const camera_settings_service__srv__CameraSettingsService_Response__Sequence * lhs, const camera_settings_service__srv__CameraSettingsService_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!camera_settings_service__srv__CameraSettingsService_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
camera_settings_service__srv__CameraSettingsService_Response__Sequence__copy(
  const camera_settings_service__srv__CameraSettingsService_Response__Sequence * input,
  camera_settings_service__srv__CameraSettingsService_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(camera_settings_service__srv__CameraSettingsService_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    camera_settings_service__srv__CameraSettingsService_Response * data =
      (camera_settings_service__srv__CameraSettingsService_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!camera_settings_service__srv__CameraSettingsService_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          camera_settings_service__srv__CameraSettingsService_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!camera_settings_service__srv__CameraSettingsService_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
