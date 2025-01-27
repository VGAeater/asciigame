import numpy as np
import math

chars = " !\"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~░▒▓█"
brightness = []

from PIL import Image

im = Image.open( "imagecrop.png" )

print( im.format, im.size, im.mode )

pixels = im.load()

for i in range( len( chars ) ):
    light = 0
    for x in range( 8 ):
        for y in range( 16 ):
            if pixels[i * 8 + x, y][0] > 100:
                light += 1
    brightness.append( light / 128 )

print( brightness )

idx_sort = np.array( brightness ).argsort()
chars_np = np.array( list( chars ) )
brightness_np = np.array( brightness )
print( chars_np[ idx_sort[::] ] )
print( brightness_np[ idx_sort[::] ] )
