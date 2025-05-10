import gc

gc.collect()
print(f"Starting... Heap Free: {gc.mem_free()}")

from picogui.boards import VGM_BOARD_CONFIG
from picogui.draw import Draw

TFT_WHITE = 0xFFFFFF
TFT_BLACK = 0x000000
TFT_RED = 0x0000FF

gc.collect()
print(f"Loading draw... Heap Free: {gc.mem_free()}")


# Initialize the display
display = Draw(board_type=VGM_BOARD_CONFIG, palette_count=3, auto_swap=False)


# Set up the palette
display.set_palette(0, TFT_BLACK)
display.set_palette(1, TFT_WHITE)
display.set_palette(2, TFT_RED)

gc.collect()
print(f"Draw init... Heap Free: {gc.mem_free()}")

from picogui.menu import Menu

gc.collect()
print(f"Menu imported... Heap Free: {gc.mem_free()}")

# Initialize the menu
menu_view = Menu(
    display,  # draw instance
    "Menu",  # title
    0,  # y
    VGM_BOARD_CONFIG.height,  # height
    TFT_BLACK,  # text color
    TFT_WHITE,  # background color
    TFT_RED,  # selected color
    TFT_BLACK,  # border/separator color
    2,  # border/separator width
)

gc.collect()
print(f"Menu init... Heap Free: {gc.mem_free()}")

menu_view.add_item("Hello")
menu_view.add_item("World")
menu_view.add_item("Welcome to the PicoGUI library.")
menu_view.add_item("This is a simple menu example.")
menu_view.add_item("You can add items to the menu.")
menu_view.add_item("You can remove items from the menu.")
menu_view.add_item("You can scroll through the menu.")
menu_view.add_item("You can select items in the menu.")

for i in range(8):
    menu_view.add_item(f"Item {i + 1}")

gc.collect()
menu_view.draw()
gc.collect()

print(f"Ready to go... Heap Free: {gc.mem_free()}")


while True:
    for i in range(16):
        print(f"On item {i + 1}")
        menu_view.scroll_down()
    for i in range(14, 0, -1):
        print(f"On item {i + 1}")
        menu_view.scroll_up()
