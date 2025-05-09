import gc
import terminalio
import board, displayio, picodvi, framebufferio

from adafruit_display_text import (
    label,
)  # https://circuitpython.org/libraries - add to the /lib folder

from .boards import (
    Board,
    BOARD_TYPE_VGM,
    BOARD_TYPE_PICO_CALC,
    BOARD_TYPE_JBLANKED,
)  # https://github.com/jblanked/RaspberryPi/blob/main/Pico%20W/Libraries/CircuitPython/Board.py - add to the /lib folder

from .vector import (
    Vector,
)  # https://github.com/jblanked/RaspberryPi/blob/main/Pico%20W/Libraries/CircuitPython/Vector.py - add to the /lib folder


TFT_WHITE = 0xFFFFFF
TFT_BLACK = 0x000000


class Draw:
    """A class to handle drawing on a display using the CircuitPython displayio library."""

    def __init__(self, board_type: Board, palette_count: int = 2):
        """Initialize the display with the specified board type."""
        gc.collect()
        displayio.release_displays()

        self.board = board_type
        self.size = Vector(board_type.width, board_type.height)

        self.frame_buffer = None
        self.display = None
        self.title_grid = None

        self.palette = displayio.Palette(2)
        self.palette[0] = TFT_BLACK
        self.palette[1] = TFT_WHITE
        self.palette_count = palette_count

        self.is_ready = False

        self.bg_group = displayio.Group()
        self.text_group = displayio.Group()
        self.group = displayio.Group()
        self.group.append(self.bg_group)
        self.group.append(self.text_group)

        if self.board.board_type == BOARD_TYPE_VGM:
            try:
                self.frame_buffer = picodvi.Framebuffer(
                    320,
                    240,
                    clk_dp=board.GP9,
                    clk_dn=board.GP8,
                    red_dp=board.GP15,
                    red_dn=board.GP14,
                    green_dp=board.GP13,
                    green_dn=board.GP12,
                    blue_dp=board.GP11,
                    blue_dn=board.GP10,
                    color_depth=8,
                )
                fb_display = framebufferio.FramebufferDisplay(
                    self.frame_buffer, auto_refresh=True
                )

                self.display = displayio.Bitmap(
                    self.size.x, self.size.y, self.palette_count
                )
                self.solid = []
                for idx in range(self.palette_count):
                    bmp = displayio.Bitmap(self.size.x, self.size.y, self.palette_count)
                    bmp.fill(idx)
                    self.solid.append(bmp)

                self.title_grid = displayio.TileGrid(
                    self.display, pixel_shader=self.palette
                )
                self.bg_group.append(self.title_grid)

                fb_display.root_group = self.group
                self.is_ready = True

                gc.collect()

            except Exception as e:
                raise RuntimeError(
                    "Failed to initialize display. Is the Video Game Module connected?"
                ) from e

    def deinit(self):
        """Deinitialize the display and free up resources."""
        if self.frame_buffer:
            self.frame_buffer.deinit()
        displayio.release_displays()
        gc.collect()

    def _color_to_palette_index(self, color: int) -> int:
        """Map a color to the nearest palette index."""
        if not self.is_ready:
            raise RuntimeError("Display not initialized.")
        if 0 <= color < self.palette_count:
            return color
        for i in range(self.palette_count):
            if self.palette[i] == color:
                return i
        if color <= 0xFF:
            r_in = g_in = b_in = color
        else:
            r5 = (color >> 11) & 0x1F
            g6 = (color >> 5) & 0x3F
            b5 = color & 0x1F
            r_in = (r5 << 3) | (r5 >> 2)
            g_in = (g6 << 2) | (g6 >> 4)
            b_in = (b5 << 3) | (b5 >> 2)
        best_i = 0
        best_dist = float("inf")
        for i in range(self.palette_count):
            pal = self.palette[i]
            r_p = (pal >> 16) & 0xFF
            g_p = (pal >> 8) & 0xFF
            b_p = pal & 0xFF
            dist = (r_in - r_p) ** 2 + (g_in - g_p) ** 2 + (b_in - b_p) ** 2
            if dist < best_dist:
                best_dist = dist
                best_i = i
        return best_i

    def _ensure_draw_bitmap(self):
        '''Ensure the display bitmap is set correctly."""'''
        if self.title_grid.bitmap is not self.display:
            self.title_grid.bitmap = self.display
            if self.title_grid.bitmap is self.solid[0]:
                self.display.fill(0)
            else:
                self.display.fill(1)

    def fill(self, color: int):
        """Fill the display with a color."""
        if not self.is_ready:
            raise RuntimeError("Display not initialized.")
        pidx = self._color_to_palette_index(color)
        self.display.fill(pidx)
        self.title_grid.bitmap = self.solid[pidx]

    def clear(self, color: int = TFT_BLACK):
        """Clear the display with a color."""
        if not self.is_ready:
            raise RuntimeError("Display not initialized.")
        self.text_group = displayio.Group()
        self.group[1] = self.text_group
        self.fill(color)

    def char(self, position: Vector, ch: str, color: int):
        """Print a character at the specified position."""
        if not self.is_ready:
            raise RuntimeError("Display not initialized.")
        glyph = label.Label(
            terminalio.FONT, text=ch, color=color, x=position.x, y=position.y
        )
        self.text_group.append(glyph)

    def image_bitmap(self, position: Vector, bitmap: displayio.Bitmap):
        """Print a bitmap at the specified position."""
        if not self.is_ready:
            raise RuntimeError("Display not initialized.")
        tile_grid = displayio.TileGrid(
            bitmap, pixel_shader=self.palette, x=position.x, y=position.y
        )
        self.text_group.append(tile_grid)

    def image_bytearray(self, position: Vector, byte_array: bytearray, img_width: int):
        """Draw a byte array into the bitmap."""
        if not self.is_ready:
            raise RuntimeError("Display not initialized.")
        # derive height from length
        total_pixels = len(byte_array) // 2
        img_height = total_pixels // img_width
        for row in range(img_height):
            for col in range(img_width):
                idx = row * img_width + col
                color = (byte_array[2 * idx] << 8) | byte_array[2 * idx + 1]
                pidx = self._color_to_palette_index(color)
                self.pixel(Vector(position.x + col, position.y + row), pidx)

    def line(self, position: Vector, size: Vector, color: int):
        """Draw a line from (x1, y1) to (x2, y2) with the specified color."""
        self._ensure_draw_bitmap()
        x1, y1 = position.x, position.y
        x2, y2 = size.x, size.y
        dx = abs(x2 - x1)
        dy = abs(y2 - y1)
        sx = 1 if x1 < x2 else -1
        sy = 1 if y1 < y2 else -1
        err = dx - dy
        while True:
            self.pixel(Vector(x1, y1), color)
            if x1 == x2 and y1 == y2:
                break
            e2 = err * 2
            if e2 > -dy:
                err -= dy
                x1 += sx
            if e2 < dx:
                err += dx
                y1 += sy

    def pixel(self, position: Vector, color: int):
        """Set the pixel at (x, y) to the specified color."""
        if not self.is_ready:
            raise RuntimeError("Display not initialized.")
        if (
            position.x < 0
            or position.x >= self.size.x
            or position.y < 0
            or position.y >= self.size.y
        ):
            return
        pidx = self._color_to_palette_index(color)
        self._ensure_draw_bitmap()
        self.display[position.x, position.y] = pidx

    def rect(self, position: Vector, size: Vector, color: int):
        """Draw a rectangle at (x, y) with width w and height h."""
        self._ensure_draw_bitmap()
        self.line(position, Vector(position.x + size.x - 1, position.y), color)
        self.line(
            Vector(position.x + size.x - 1, position.y),
            Vector(position.x + size.x - 1, position.y + size.y - 1),
            color,
        )
        self.line(
            Vector(position.x + size.x - 1, position.y + size.y - 1),
            Vector(position.x, position.y + size.y - 1),
            color,
        )
        self.line(
            Vector(position.x, position.y + size.y - 1),
            Vector(position.x, position.y),
            color,
        )

    def set_palette(self, index: int, color: int):
        """Set the color of a palette index."""
        if not self.is_ready:
            raise RuntimeError("Display not initialized.")
        if index < 0 or index >= self.palette_count:
            raise ValueError(f"Palette index {index} out of range")
        self.palette[index] = color

    def text(self, position: Vector, txt: str, color: int):
        """Print a string at the specified position."""
        if not self.is_ready:
            raise RuntimeError("Display not initialized.")
        t = label.Label(
            terminalio.FONT, text=txt, color=color, x=position.x, y=position.y
        )
        self.text_group.append(t)
