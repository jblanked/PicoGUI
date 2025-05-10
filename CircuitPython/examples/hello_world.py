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
box = TextBox(display, 0, display.size.y, TFT_WHITE, TFT_BLACK)
box.set_text(text)

gc.collect()
print("Free memory:", gc.mem_free())

# Demo scrolling - start at the top and scroll down
sleep(1)  # Pause to see initial state
for i in range(min(box.total_lines - 1, 7)):  # Limit number of scrolls
    print(f"On line {i} now")
    box.set_current_line(i)  # scroll down to the next line
    sleep(0.5)

gc.collect()
print("Free memory:", gc.mem_free())

# Reduced loop iterations to conserve memory
scroll_range = min(5, box.total_lines - 1)  # Limit scrolling range

# Main loop with reduced iterations and memory usage
while True:
    # Define starting line for scroll up
    start_line = min(box.current_line, box.total_lines - 1)

    # Scroll up
    for i in range(scroll_range):
        if start_line - i < 0:
            break
        print(f"On line {start_line - i} now")
        box.set_current_line(start_line - i)
        sleep(0.5)
        gc.collect()  # Clean up after each scroll operation

    # Scroll down
    current_line = box.current_line
    for i in range(scroll_range):
        if current_line + i >= box.total_lines:
            break
        print(f"On line {current_line + i} now")
        box.set_current_line(current_line + i)
        sleep(0.5)
        gc.collect()  # Clean up after each scroll operation
