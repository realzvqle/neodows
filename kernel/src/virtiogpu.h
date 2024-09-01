#ifndef VIRTIOGPU_H_INCLUDED
#define VIRTIOGPU_H_INCLUDED



#include <stdint.h>



struct virtio_gpu_config {
    uint32_t events_read;
    uint32_t events_clear;
    uint32_t num_scanouts;
    uint32_t num_capsets;
};

enum virtio_gpu_shm_id {
    VIRTIO_GPU_SHM_ID_UNDEFINED = 0,
    VIRTIO_GPU_SHM_ID_HOST_VISIBLE = 1,
};


uint32_t get_framebuffer_info();
void set_pixel(int x, int y, uint32_t color, int screen_width);
void clear_screen(uint32_t color, int screen_width, int screen_height);
void virtio_gpu_init();
#endif