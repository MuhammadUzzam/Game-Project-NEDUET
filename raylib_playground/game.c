#include <stdio.h>
#include <tiny2d/tiny2d.h>  // Include the tiny2d library header

int main() {
    // Initialize the tiny2d window
    if (!t2d_init_window("Tiny2D Test", 800, 600)) {
        printf("Failed to initialize window.\n");
        return -1;
    }

    // Set the background color (black)
    t2d_clear_color(0.0f, 0.0f, 0.0f);

    // Create a rectangle (position x, position y, width, height)
    t2d_rectangle rect = t2d_create_rectangle(100, 100, 200, 150);
    t2d_set_color(rect, 0.0f, 1.0f, 0.0f);  // Green color

    // Main loop to keep the window open and render the rectangle
    while (t2d_is_window_open()) {
        // Clear the screen
        t2d_clear();

        // Draw the rectangle
        t2d_draw_rectangle(rect);

        // Poll for events like window closing or key presses
        if (t2d_is_key_pressed(T2D_KEY_ESCAPE)) {
            break;  // Exit the loop if ESC is pressed
        }

        // Update the screen
        t2d_display();
    }

    // Cleanup and close the window
    t2d_close();
    return 0;
}
