import gc
from time import sleep
from picogui.boards import VGM_BOARD_CONFIG
from picogui.draw import Draw, TFT_WHITE, TFT_BLACK
from picogui.textbox import TextBox

# Force garbage collection before starting
gc.collect()
print("Free memory:", gc.mem_free())

# Initialize the display
display = Draw(board_type=VGM_BOARD_CONFIG, palette_count=2, auto_swap=False)

gc.collect()
print("Free memory:", gc.mem_free())

# Set up the palette
display.set_palette(0, TFT_BLACK)
display.set_palette(1, TFT_WHITE)

# Create text for display
text = "Hello World.\n\nWelcome to the PicoGUI library.\n\nThis basic example is of the TextBox module.\n\nYou can test\nreally long texts.\n\nAnd they will draw as intended.\nPlus\nThere is a scroll bar\n\n\nTest\nand have fun creating gui\nwith PicoGUI\n\n:D\nStay tuned\nfor more GUI updates!\n\nList view, Deskstop, Waiting, and more..\n\nAnyways, thanks!\n\n"

gc.collect()
print("Free memory:", gc.mem_free())

# Create the text box
box = TextBox(display, 0, display.size.y, TFT_BLACK, TFT_WHITE)
box.set_text(text)

gc.collect()
print("Free memory:", gc.mem_free())

# Demo scrolling - start at the top and scroll down
sleep(1)  # Pause to see initial state
for i in range(box.total_lines, 0, -1):  # Limit number of scrolls
    print(f"On line {i} now")
    box.set_current_line(i)  # scroll down to the next line
    sleep(0.5)

gc.collect()
print("Free memory:", gc.mem_free())

# Main loop with reduced iterations and memory usage
while True:
    # Define starting line for scroll up
    start_line = min(box.current_line, box.total_lines - 1)

    # Scroll up
    for i in range(box.total_lines, 0, -1):
        print(f"On line {i} now")
        box.scroll_up()  # scroll up to the next line

    # Scroll down
    for i in range(box.total_lines):
        print(f"On line {i} now")
        box.scroll_down()  # scroll down to the next line
