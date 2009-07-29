import Image
import struct
import numpy
import psyco

psyco.full()

MX_PIXELFORMAT_I1 = 1
MX_SURFACE_FLAG_PRESHIFT = 0x1
MX_SURFACE_FLAG_RLE = 0x8
MX_PACK_ALPHA_CHANNEL = (0x1 << 32)

packFile = "../data/images.dat"

BW = MX_PIXELFORMAT_I1
PS = MX_SURFACE_FLAG_PRESHIFT
A = MX_PACK_ALPHA_CHANNEL
C = MX_SURFACE_FLAG_RLE

files = [
    ("../data/intro_cityscape.png", BW, PS),
    ("../data/intro_mac.png", BW, 0),
    ("../data/intro_street.png", BW, PS),
    ("../data/mac_on_street_bg.png", BW, C),
    ("../data/mac_on_street.png", BW, PS),
    ("../data/pc_on_street.png", BW, PS),
    ("../data/macbook_on_street.png", BW, 0),
    ("../data/pc_closeup.png", BW, 0),
    ("../data/mac_closeup.png", BW, 0),
    ("../data/macbook_closeup.png", BW, 0),
    ("../data/pc_screen_bg.png", BW, C),
    ("../data/macbook_screen_bg.png", BW, C),
    ("../data/guys_on_street.png", BW, 0),
    ("../data/pedobear_run_side.png", BW, 0),
    ("../data/pedobear_run_side.png", BW, A),
    ("../data/pedobear_run_front.png", BW, 0),
    ("../data/pedobear_run_front.png", BW, A),
    ("../data/mac_disk_load.png", BW, 0),
    ("../data/mac_disk_fire.png", BW, 0),
    ("../data/disk_impact.png", BW, PS),
    ("../data/pedobear_impact.png", BW, 0),
    ("../data/pedobear_impact.png", BW, A),
]

def log2i(n):
    x = 0
    while (1 << x) < n:
        x += 1
    return x

def isPowerOfTwo(n):
    return (n & (n - 1)) == 0

def packImage(out, image, format, flags):
    assert format == MX_PIXELFORMAT_I1
    assert isPowerOfTwo(image.size[0])

    stride = image.size[0] / 8
    planeSize = stride * image.size[1]
    header = struct.pack("iiiiiiii", 
            image.size[0], image.size[1],
            stride, log2i(stride),
            format,
            flags & 0xffffffff,
            planeSize,
            1)
    data = numpy.zeros(planeSize, dtype = numpy.uint8)
    for y in range(0, image.size[1]):
        for x in range(0, image.size[0]):
            p = image.getpixel((x, y))
            if flags & MX_PACK_ALPHA_CHANNEL:
                c = p[-1]
            else:
                c = not (p[0] | p[1] | p[2])
            if c:
                data[y * stride + (x >> 3)] |= (0x80 >> (x & 0x7))
    out.write(header)
    data.tofile(out)

    return planeSize * (8 if (flags & MX_SURFACE_FLAG_PRESHIFT) else 1)

if __name__ == "__main__":
    out = open(packFile, "wb")
    bytes = 0
    for f, format, flags in files:
        info = []
        if flags & MX_SURFACE_FLAG_PRESHIFT:
            info += ["preshift"]
        if flags & MX_PACK_ALPHA_CHANNEL:
            info += ["mask"]
        image = Image.open(f)
        print f, image.size, "(%s)" % ", ".join(info) if info else ""
        bytes += packImage(out, image, format, flags)
    print ">>> %d bytes (%d on disk)" % (bytes, out.tell())
    out.close()

