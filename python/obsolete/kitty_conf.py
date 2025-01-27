import numpy as np
import math

chars = " `.-':_,^=;><+!rc*/z?sLTv)J7(|Fi{C}fI31tlu[neoZ5Yxjya]2ESwqkP6h9d4VpOGbUAKXHm8RD#$Bg0MNWQ%&@"
brightness = (0, 0.0751, 0.0829, 0.0848, 0.1227, 0.1403, 0.1559, 0.185, 0.2183, 0.2417, 0.2571, 0.2852, 0.2902, 0.2919, 0.3099, 0.3192, 0.3232, 0.3294, 0.3384, 0.3609, 0.3619, 0.3667, 0.3737, 0.3747, 0.3838, 0.3921, 0.396, 0.3984, 0.3993, 0.4075, 0.4091, 0.4101, 0.42, 0.423, 0.4247, 0.4274, 0.4293, 0.4328, 0.4382, 0.4385, 0.442, 0.4473, 0.4477, 0.4503, 0.4562, 0.458, 0.461, 0.4638, 0.4667, 0.4686, 0.4693, 0.4703, 0.4833, 0.4881, 0.4944, 0.4953, 0.4992, 0.5509, 0.5567, 0.5569, 0.5591, 0.5602, 0.5602, 0.565, 0.5776, 0.5777, 0.5818, 0.587, 0.5972, 0.5999, 0.6043, 0.6049, 0.6093, 0.6099, 0.6465, 0.6561, 0.6595, 0.6631, 0.6714, 0.6759, 0.6809, 0.6816, 0.6925, 0.7039, 0.7086, 0.7235, 0.7302, 0.7332, 0.7602, 0.7834, 0.8037, 0.9999)

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
    ( np.array( [ 255, 0, 85 ] ), 31, 41, "Red" ),
    ( np.array( [ 0, 149, 80 ] ), 32, 42, "Green" ),
    ( np.array( [ 244, 239, 0 ] ), 33, 43, "Yellow" ),
    ( np.array( [ 103, 102, 179 ] ), 34, 44, "Blue" ),
    ( np.array( [ 213, 123, 255 ] ), 35, 45, "Magenta" ),
    ( np.array( [ 13, 205, 205 ] ), 36, 46, "Cyan" ),
    ( np.array( [ 238, 255, 255 ] ), 37, 47, "White" ),
    ( np.array( [ 119, 199, 199 ] ), 90, 100, "Bright Black" ),
    ( np.array( [ 255, 64, 129 ] ), 91, 101, "Bright Red" ),
    ( np.array( [ 0, 255, 156 ] ), 92, 102, "Bright Green" ),
    ( np.array( [ 255, 252, 88 ] ), 93, 103, "Bright Yellow" ),
    ( np.array( [ 118, 193, 255 ] ), 94, 104, "Bright Blue" ),
    ( np.array( [ 197, 146, 255 ] ), 95, 105, "Bright Magenta" ),
    ( np.array( [ 0, 255, 200 ] ), 96, 106, "Bright Cyan" ),
    ( np.array( [ 255, 255, 255 ] ), 97, 107, "Bright White" )
)

from PIL import Image

im = Image.open( "amideadyet.webp" )

print( im.format, im.size, im.mode )

pixels = im.load()

def approximate_color( c ):
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

            # distance, fore color, back color, percent between them, final color
            entry = ( approx_dist, fore, back, ddist / dist if dist != 0 else 0, di )

            if best == 0 or best[0] > approx_dist:
                best = entry

    return best


ratio = 0.5

text_width = 100

x_step = im.size[0] / text_width
y_step = im.size[1] / ( text_width * ratio )

for i in range( math.floor( text_width * ratio ) ):
    for j in range( text_width ):
        data = approximate_color( pixels[j * x_step, i * y_step] )
        print( "\033[" + str( data[1][1] ) + ";" + str( data[2][2] ) + "m" + chars[ binarySearch( brightness, data[3] ) ], end="" )
    print()

print( "\033[0m" )
