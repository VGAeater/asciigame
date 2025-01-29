import numpy as np
import math

chars = [ ' ', '.', '`', '-', ',', ':', '_', "'", '~', ';', '^', '=', '/', '+', '"', '<', '>', '|',
 '(', ')', 'i', '\\', '%', '{', '}', 'l', 'c', '!', 'I', '*', ']', '[', 'r', '?', 's', 'x',
 't', '1', '7', 'v', 'f', 'z', 'a', 'n', 'e', 'u', 'o', 'J', 'C', 'L', 'j', '░', 'Y', 'T',
 '3', '2', '5', 'w', '4', 'F', '9', 'P', 'S', 'V', 'd', 'm', 'k', 'b', '6', 'Z', 'G', 'h',
 'q', 'p', 'y', 'A', 'X', 'E', '0', 'g', '&', 'U', 'D', '#', 'O', 'K', '$', '8', 'H', '@',
 'R', 'B', 'W', 'M', 'N', 'Q', '▒', '▓', '█' ]
brightness = [0.,        0.03125,   0.046875,  0.0546875, 0.0625,    0.0625,    0.0625,
 0.0625,    0.078125,  0.078125,  0.09375,   0.09375,   0.109375,  0.109375,
 0.109375,  0.140625,  0.140625,  0.15625,   0.15625,   0.15625,   0.1640625,
 0.1640625, 0.171875,  0.1796875, 0.1796875, 0.1796875, 0.1875,    0.1875,
 0.1875,    0.1875,    0.1875,    0.1875,    0.1875,    0.1953125, 0.1953125,
 0.1953125, 0.203125,  0.2109375, 0.2109375, 0.2109375, 0.21875,   0.21875,
 0.21875,   0.2265625, 0.2265625, 0.2265625, 0.234375,  0.234375,  0.234375,
 0.234375,  0.2421875, 0.25,      0.25,      0.25,      0.25,      0.25,
 0.265625,  0.265625,  0.265625,  0.265625,  0.2734375, 0.2734375, 0.2734375,
 0.28125,   0.28125,   0.28125,   0.28125,   0.28125,   0.28125,   0.28125,
 0.2890625, 0.2890625, 0.296875,  0.296875,  0.3046875, 0.3046875, 0.3125,
 0.3125,    0.3125,    0.3125,    0.3203125, 0.3203125, 0.328125,  0.328125,
 0.328125,  0.328125,  0.3359375, 0.3359375, 0.3359375, 0.3359375, 0.34375,
 0.3515625, 0.375,     0.3828125, 0.3828125, 0.390625,  0.5,       0.75,
 1.       ]

def binarySearch(data, val):
    lo, hi = 0, len(data) - 1
    best_ind = lo
    while lo <= hi:
        mid = lo + (hi - lo) // 2
        if data[mid] < val:
            lo = mid + 1
        elif data[mid] > val:
            hi = mid - 1
        else:
            best_ind = mid
            break
        # check if data[mid] is closer to val than data[best_ind] 
        if abs(data[mid] - val) < abs(data[best_ind] - val):
            best_ind = mid
    return best_ind

colors = (
    ( np.array( [ 0, 0, 0 ] ), 30, 40, "Black" ),
    ( np.array( [ 170, 0, 0 ] ), 31, 41, "Red" ),
    ( np.array( [ 0, 170, 0 ] ), 32, 42, "Green" ),
    ( np.array( [ 170, 85, 0 ] ), 33, 43, "Yellow" ),
    ( np.array( [ 0, 0, 170 ] ), 34, 44, "Blue" ),
    ( np.array( [ 170, 0, 170 ] ), 35, 45, "Magenta" ),
    ( np.array( [ 0, 170, 170 ] ), 36, 46, "Cyan" ),
    ( np.array( [ 170, 170, 170 ] ), 37, 47, "White" ),
    ( np.array( [ 85, 85, 85 ] ), 90, 100, "Bright Black" ),
    ( np.array( [ 255, 85, 85 ] ), 91, 101, "Bright Red" ),
    ( np.array( [ 85, 255, 85 ] ), 92, 102, "Bright Green" ),
    ( np.array( [ 255, 255, 85 ] ), 93, 103, "Bright Yellow" ),
    ( np.array( [ 85, 85, 255 ] ), 94, 104, "Bright Blue" ),
    ( np.array( [ 255, 85, 255 ] ), 95, 105, "Bright Magenta" ),
    ( np.array( [ 85, 255, 255 ] ), 96, 106, "Bright Cyan" ),
    ( np.array( [ 255, 255, 255 ] ), 97, 107, "Bright White" )
)

from PIL import Image

im = Image.open( "amideadyet.webp" )
#im = Image.open( "boykisser.png" )

print( im.format, im.size, im.mode )

pixels = im.load()

def approximate_color( c ):
    if len( c ) > 3 and c[3] < 128:
        return 0

    c = c[:3]

    best = 0

    for back in colors[:8]:
        for fore in colors:
            a = back[0]
            b = fore[0]

            bi = b - a
            ci = c - a

            ang = math.atan2( bi[1], bi[0] )
            dist = math.sqrt( bi[0]**2 + bi[1]**2 )
            tdist = math.sqrt( bi[0]**2 + bi[1]**2 + bi[2]**2 )

            zang = math.atan2( bi[2], dist )

            cang = math.atan2( ci[1], ci[0] )
            cdist = math.sqrt( ci[0]**2 + ci[1]**2 )
            ctdist = math.sqrt( ci[0]**2 + ci[1]**2 + ci[2]**2 )

            czang = math.atan2( ci[2], cdist )

            cix = ctdist * math.cos( cang - ang ) * math.cos( czang - zang )
            #ciy = ctdist * math.sin( cang - ang ) * math.cos( czang - zang )
            #ciz = ctdist * math.sin( czang - zang )

            ddist = max( 0, min( cix, dist ) )

            dix = ddist * math.cos( ang ) * math.cos( zang )
            diy = ddist * math.sin( ang ) * math.cos( zang )
            diz = ddist * math.sin( zang )

            di = np.array( [ dix, diy, diz ] )

            di += a

            approx_dist = math.sqrt( np.sum( np.square( di - c ) ) )

            # distance, fore color, back color, percent
            entry = ( approx_dist, fore, back, ddist / dist if dist != 0 else 0 )

            if best == 0 or best[0] > approx_dist:
                best = entry

    return best


ratio = 0.5

text_width = 100

x_step = im.size[0] / text_width
y_step = im.size[1] / ( text_width * ratio )

for i in range( math.floor( text_width * ratio ) ):
    right = 0
    for j in range( text_width ):
        data = approximate_color( pixels[j * x_step + x_step / 2, i * y_step + y_step / 2] )
        if data == 0:
            right += 1
            continue
        elif not right == 0:
            print( "\033[" + str( right ) + "C", end="" )
            right = 0
        char = chars[ binarySearch( brightness, data[3] ) ]
        if char == "█":
            print( "\033[" + str( data[1][1] ) + "m" + char, end="" )
        else:
            print( "\033[" + str( data[1][1] ) + ";" + str( data[2][2] ) + "m" + char, end="" )
    print()

print( "\033[0m" )
