import time
import sys

# Define the ASCII art for each letter and their corresponding colors
ascii_art = {
    'Y': {
        'art': r"""
 __     __  
 \ \   / /  
  \ \_/ /__ 
   \   / __|
    | | (__ 
    |_|\___|
""",
        'color': '\x1b[93m',  # ANSI escape code for yellow color
    },
    'O': {
        'art': r"""
   _____  
  / ____| 
 | |  | |
 | |  | |
 | |__| |
  \____/  
""",
        'color': '\x1b[91m',  # ANSI escape code for red color
    },
    'U': {
        'art': r"""
  _    _ 
 | |  | |
 | |  | |
 | |  | |
 | |__| |
  \____/ 
""",
        'color': '\x1b[92m',  # ANSI escape code for green color
    },
    'C': {
        'art': r"""
   _____  
  / ____| 
 | |      
 | |      
 | |____  
  \_____| 
""",
        'color': '\x1b[96m',  # ANSI escape code for cyan color
    },
    'D': {
        'art': r"""
  _____  
 |  __ \ 
 | |  | |
 | |  | |
 | |__| |
 |_____/ 
""",
        'color': '\x1b[94m',  # ANSI escape code for blue color
    },
    'E': {
        'art': r"""
  ______ 
 |  ____|
 | |__   
 |  __|  
 | |____ 
 |______|
""",
        'color': '\x1b[95m',  # ANSI escape code for magenta color
    },
}

def display_text_vertically(text):
    max_lines = max(len(ascii_art[letter]['art'].split('\n')) for letter in text)
    for line_number in range(1, max_lines + 1):
        for letter in text:
            lines = ascii_art[letter]['art'].split('\n')
            if len(lines) > line_number:
                colored_letter = ascii_art[letter]['color'] + lines[line_number] + '\x1b[0m'
                sys.stdout.write(colored_letter)
            else:
                sys.stdout.write(" " * len(lines[0]))  # Fill with spaces if no more lines
        sys.stdout.write("\n")
        time.sleep(1)  # Pause for 1 second between lines

if __name__ == "__main__":
    message = "YOUCODE"
    display_text_vertically(message)

