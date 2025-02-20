import numpy as np
import math

from PIL import Image

im = Image.open( "images/amideadyet.webp" )
#im = Image.open( "boykisser.png" )
#im = Image.open( "lol.jpg" )
#im = Image.open( "eye.png" )

print( im.format, im.size, im.mode )

pixels = im.load()

ratio = 1 * ( im.height / im.width )

text_width = 48

x_step = im.size[0] / text_width
y_step = im.size[1] / ( text_width * ratio )

for i in range( math.floor( text_width * ratio ) ):
    for j in range( text_width ):
        datafore = pixels[j * x_step + x_step / 2, i * y_step + y_step / 2]
        print( f"\033[38;2;{datafore[0]};{datafore[1]};{datafore[2]}m██", end="" )
    print()

print( "\033[0m" )
