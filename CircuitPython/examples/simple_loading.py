import time
from picogui.boards import VGM_BOARD_CONFIG
from picogui.draw import Draw, TFT_WHITE, TFT_BLACK
from picogui.loading import Loading


# Initialize the display
display = Draw(board_type=VGM_BOARD_CONFIG, palette_count=2, auto_swap=False)

# Set up the palette
display.set_palette(0, TFT_BLACK)
display.set_palette(1, TFT_WHITE)

# Initialize the loading animation
loading = Loading(display, TFT_BLACK, TFT_WHITE)

# Animation loop
while True:
    i = 0
    while i < 500:
        loading.animate()  # This now handles the buffer swap internally
        i += 1

    loading.stop()  # This also handles the final buffer swap
    time.sleep(2)
