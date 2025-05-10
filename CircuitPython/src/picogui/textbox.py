from gc import collect as free
from .boards import BOARD_TYPE_VGM, BOARD_TYPE_JBLANKED, BOARD_TYPE_PICO_CALC
from .draw import Draw
from .vector import Vector
from .scrollbar import ScrollBar


class TextBox:
    def __init__(
        self,
        draw: Draw,
        y: int,
        height: int,
        foreground_color: int,
        background_color: int,
    ):
        self.display = draw
        self.foreground_color = foreground_color
        self.background_color = background_color
        self.characters_per_line = 0
        self.lines_per_screen = 0
        self.total_lines = 0
        self.current_line = -1
        #
        self.current_text = ""
        self.position = Vector(0, y)
        self.size = Vector(self.display.size.x, height)
        self.display.clear(self.position, self.size, self.background_color)

        # Line state tracking for memory optimization
        self.line_buffer = []  # Stores line contents - only visible lines
        self.line_positions = []  # Stores positions of all lines for quick scrolling

        self.scrollbar = ScrollBar(
            self.display,
            Vector(0, 0),
            Vector(0, 0),
            self.foreground_color,
            self.background_color,
        )

        board_type = self.display.board.board_type
        if board_type in (BOARD_TYPE_VGM, BOARD_TYPE_JBLANKED):
            self.characters_per_line = 52  # width is 320
            self.lines_per_screen = 20  # height is 240
        elif board_type == BOARD_TYPE_PICO_CALC:
            self.characters_per_line = 52  # width is 320
            self.lines_per_screen = 26  # height is 320

        self.display.swap()

    def clear(self):
        """Clear the text box and reset the scrollbar."""
        self.display.clear(self.position, self.size, self.background_color)
        self.display.clear_text_objects()  # Clear text objects to free memory
        self.line_buffer = []
        self.line_positions = []
        self.scrollbar.clear()
        self.total_lines = 0
        self.set_scrollbar_size()
        self.set_scrollbar_position()
        self.display.swap()

    def get_text_height(self) -> int:
        """Get the height of the text box based on the number of lines and font size."""
        return (
            0 if self.total_lines == 0 else (self.total_lines - 1) * 12
        )  # 12 pixel spacing for 6x6 pixel font

    def set_current_line(self, line: int):
        """Set the current line to the specified line number."""
        if self.total_lines == 0 or line < 0 or line > (self.total_lines - 1):
            return

        self.current_line = line

        # Reset text display and redraw with new scroll position
        self.display_visible_lines()

        # Update scrollbar
        self.set_scrollbar_position()
        self.scrollbar.draw()
        self.display.swap()

    def set_scrollbar_position(self):
        """Set the position of the scrollbar based on the current line."""
        # Calculate the proper scroll position based on current line and total lines
        scroll_ratio = 0.0
        if self.total_lines > self.lines_per_screen and self.total_lines > 0:
            # Ensure we don't start scrolling until after self.lines_per_screen
            if self.current_line <= self.lines_per_screen:
                scroll_ratio = 0.0
            else:
                scroll_ratio = float(self.current_line - self.lines_per_screen) / float(
                    self.total_lines - self.lines_per_screen
                )

        # maximum vertical movement for scrollbar thumb
        max_offset = self.size.y - self.scrollbar.size.y - 2
        # Account for padding
        bar_offset_y = scroll_ratio * max_offset

        bar_x = self.position.x + self.size.x - self.scrollbar.size.x - 1
        # 1 pixel padding
        bar_y = self.position.y + bar_offset_y + 1
        # 1 pixel padding

        self.scrollbar.position = Vector(bar_x, bar_y)

    def set_scrollbar_size(self):
        """Set the size of the scrollbar based on the number of lines."""
        content_height = self.get_text_height()
        view_height = self.size.y
        bar_height = 0.0

        if content_height <= view_height or content_height <= 0.0:
            bar_height = view_height - 2
            # 1 pixel padding (+1 pixel for the scrollbar)
        else:
            bar_height = view_height * (view_height / content_height)

        # enforce minimum scrollbar height
        min_bar_height = 12.0
        bar_height = max(bar_height, min_bar_height)

        self.scrollbar.size = Vector(6.0, bar_height)

    def display_visible_lines(self):
        """Display only the lines that are currently visible."""
        # Clear current display
        self.display.clear(self.position, self.size, self.background_color)
        self.display.clear_text_objects()

        # Calculate first visible line
        first_visible_line = 0
        if self.current_line > self.lines_per_screen:
            first_visible_line = self.current_line - self.lines_per_screen

        # Determine which lines to display
        visible_range = range(
            first_visible_line,
            min(first_visible_line + self.lines_per_screen, len(self.line_positions)),
        )

        # Display only the lines in view
        for i, line_idx in enumerate(visible_range):
            if line_idx < len(self.line_positions):
                line_info = self.line_positions[line_idx]
                start_idx, length = line_info

                if start_idx + length <= len(self.current_text):
                    line_text = self.current_text[
                        start_idx : start_idx + length
                    ].rstrip()
                    y_pos = (
                        self.position.y + 5 + (i * 12)
                    )  # Position based on line number within view
                    self.display.text(
                        Vector(self.position.x + 1, y_pos),
                        line_text,
                        self.foreground_color,
                    )

        # Force garbage collection
        free()

    def set_text(self, text: str):
        """Set the text in the text box and update the scrollbar accordingly."""
        self.current_text = text

        # Clear display
        self.display.clear(self.position, self.size, self.background_color)
        self.display.clear_text_objects()
        self.scrollbar.clear()

        str_len = len(text)
        if str_len == 0:
            self.total_lines = 0
            self.line_positions = []
            self.set_scrollbar_size()
            self.set_scrollbar_position()
            return

        # First pass: Calculate line positions and count total lines
        line_start = 0  # Start index of current line
        line_length = 0  # Current length of line
        word_start = 0  # Start index of current word
        word_length = 0  # Length of current word
        i = 0  # Current position in text
        self.total_lines = 1  # Start with one line
        self.line_positions = []  # Reset line positions

        # First loop: Calculate line positions and count total lines
        while i < str_len:
            # Check for newline character first
            if text[i] == "\n":
                # Store current line position and length
                self.line_positions.append((line_start, line_length))

                self.total_lines += 1
                line_start = i + 1  # Start after the newline
                line_length = 0
                i += 1  # Move past the newline
                continue

            # Skip leading spaces at beginning of a line
            if line_length == 0:
                while i < str_len and text[i] == " ":
                    i += 1
                line_start = i

            # Find the length of the current word
            word_start = i
            word_length = 0
            while i < str_len and text[i] != " " and text[i] != "\n":
                word_length += 1
                i += 1

            # Check if this word will fit on the current line
            if line_length + word_length > self.characters_per_line and line_length > 0:
                # Word doesn't fit, store current line and start a new one
                self.line_positions.append((line_start, line_length))

                self.total_lines += 1
                line_start = word_start
                line_length = 0

                # Count the word on the new line
                line_length += word_length
            else:
                # Word fits, add it to the current line
                line_length += word_length

                # Add space after word (if not at the end of text)
                if i < str_len and text[i] == " ":
                    line_length += 1
                    i += 1  # Move past the space

                word_length = 0  # Reset for next word

        # Add the last line if it has content
        if line_length > 0:
            self.line_positions.append((line_start, line_length))

        # Initialize current line if not set
        if self.current_line == -1 or self.current_line >= self.total_lines:
            self.current_line = min(self.total_lines - 1, self.lines_per_screen)

        # Update scrollbar
        self.set_scrollbar_size()
        self.set_scrollbar_position()

        # Display the visible lines
        self.display_visible_lines()

        # Draw scrollbar and update display
        self.scrollbar.draw()
        self.display.swap()

        # Force garbage collection
        free()
