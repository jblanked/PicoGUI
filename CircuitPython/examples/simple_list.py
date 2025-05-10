from picogui.boards import VGM_BOARD_CONFIG
from picogui.draw import Draw
from picogui.list import List
import gc

gc.collect()

TFT_WHITE = 0xFFFFFF
TFT_BLACK = 0x000000
TFT_RED = 0x0000FF


# Initialize the display
display = Draw(board_type=VGM_BOARD_CONFIG, palette_count=3, auto_swap=False)

gc.collect()
print(f"Draw init... Heap Free: {gc.mem_free()}")

# Set up the palette
display.set_palette(0, TFT_BLACK)
display.set_palette(1, TFT_WHITE)
display.set_palette(2, TFT_RED)

# Initialize the list
list_view = List(
    display,  # draw instance
    0,  # y
    VGM_BOARD_CONFIG.height,  # height
    TFT_BLACK,  # text color
    TFT_WHITE,  # background color
    TFT_RED,  # selected color
    TFT_BLACK,  # border/separator color
    2,  # border/separator width
)

gc.collect()
print(f"List init... Heap Free: {gc.mem_free()}")

list_view.add_item("Hello")
list_view.add_item("World")
list_view.add_item("Welcome to the PicoGUI library.")
list_view.add_item("This is a simple list example.")
list_view.add_item("You can add items to the list.")
list_view.add_item("You can remove items from the list.")
list_view.add_item("You can scroll through the list.")
list_view.add_item("You can select items in the list.")

for i in range(8):
    list_view.add_item(f"Item {i + 1}")


gc.collect()
list_view.draw()
gc.collect()

print(f"Ready to go... Heap Free: {gc.mem_free()}")


while True:
    for i in range(16):
        print(f"On item {i + 1}")
        list_view.set_selected(i)
    for i in range(14, 0, -1):
        print(f"On item {i + 1}")
        list_view.set_selected(i)
