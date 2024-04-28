#include "application.h"
#include <core/logger.h>
#include "platform/platform.h"

typedef struct application_state {
    b8 is_running;
    b8 is_suspended;
    platform_state platform;
    i16 width;
    i16 height;
    f64 last_time;
} application_state;

static b8 initilized = FALSE;
static application_state app_state;

b8 application_create(application_config* config) {
    if (initilized) {
        KERROR("application_create called more than once.");
        return FALSE;
    }
    // Initialize subsystem
    initialize_logging();

    // TODO: remove this later
    KFATAL("A test Message: %f", 3.14f);
    KERROR("A test Message: %f", 3.14f);
    KWARN("A test Message: %f", 3.14f);
    KINFO("A test Message: %f", 3.14f);
    KDEBUG("A test Message: %f", 3.14f);
    KTRACE("A test Message: %f", 3.14f);

    app_state.is_running = TRUE;
    app_state.is_suspended = FALSE;

    if (!platform_startup(&app_state.platform, config->name, config->start_pos_x,
                          config->start_pos_y, config->start_width, config->start_height)) {
        return FALSE;
    }
    initilized = TRUE;

    return TRUE;
};

b8 application_run() {
    while (app_state.is_running) {
        if (!platform_pump_messages(&app_state.platform)) {
            app_state.is_running = FALSE;
        }
    }
    platform_shutdown(&app_state.platform);
};
