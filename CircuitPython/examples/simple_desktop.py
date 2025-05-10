import gc
from picogui.boards import VGM_BOARD_CONFIG
from picogui.draw import Draw, TFT_WHITE, TFT_BLACK
from picogui.desktop import Desktop
from picogui.vector import Vector

# Force garbage collection before starting
gc.collect()
print("Free memory:", gc.mem_free())

# Initialize the display
display = Draw(board_type=VGM_BOARD_CONFIG, palette_count=2, auto_swap=False)

gc.collect()
print("Free memory:", gc.mem_free())

desktop = Desktop(display, TFT_BLACK, TFT_WHITE)
next_frame = 1
max_frame = 4
direction = 1

gc.collect()
print("Free memory:", gc.mem_free())


while True:
    desktop.draw_with_bmp_on_disk(f"frame_{next_frame}.bmp")
    next_frame += direction
    if next_frame == max_frame:
        direction = -1
    if next_frame == 1:
        direction = 1
