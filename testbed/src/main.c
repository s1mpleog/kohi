#include <core/logger.h>
#include <core/asserts.h>

// TODO: test
#include <platform/platform.h>

int main(void) {
    KFATAL("A test Message: %f", 3.14f);
    KERROR("A test Message: %f", 3.14f);
    KWARN("A test Message: %f", 3.14f);
    KINFO("A test Message: %f", 3.14f);
    KDEBUG("A test Message: %f", 3.14f);
    KTRACE("A test Message: %f", 3.14f);

    platform_state state;
    if (platform_startup(&state, "Kohi Engine Testbed", 100, 100, 1200, 720)) {
        while (TRUE) {
            platform_pump_messages(&state);
        }
    }
    platform_shutdown(&state);

    return 0;
}
