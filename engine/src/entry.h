#pragma once
#include "core/application.h"
#include "core/logger.h"
#include "games_type.h"

extern b8 create_game(game* out_game);

/**
 * the main entry point of the application.
 */
int main(void) {
    game game_inst;
    if (!create_game(&game_inst)) {
        KFATAL("Could not create game");
        return -1;
        }

    // Ensure the function pointers exists.
    if (!game_inst.render || !game_inst.update || !game_inst.initialize || !game_inst.on_resize) {
        KFATAL("The game's function pointers must be initalized");
        return -2;
    }

    // Initialization
    if (!application_create(&game_inst)) {
        KINFO("Application failed to create!.");
        return 1;
    };

    // Begin the game loop
    if (!application_run()) {
        KINFO("Application did not shutdown gracefully.");
        return 2;
    };

    return 0;
}
