import Image
import struct
import numpy

MX_PIXELFORMAT_I1 = 1
MX_SURFACE_FLAG_PRESHIFT = 0x1
MX_PACK_ALPHA_CHANNEL = (0x1 << 32)

packFile = "../data/images.dat"

files = [
    ("../data/star.png", MX_PIXELFORMAT_I1, MX_SURFACE_FLAG_PRESHIFT),
    ("../data/star.png", MX_PIXELFORMAT_I1, MX_SURFACE_FLAG_PRESHIFT | MX_PACK_ALPHA_CHANNEL),
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
                c = p[0] | p[1] | p[2]
            if c:
                data[y * stride + (x >> 3)] |= (0x80 >> (x & 0x7))
    out.write(header)
    data.tofile(out)

if __name__ == "__main__":
    out = open(packFile, "wb")
    for f, format, flags in files:
        print f, "(mask)" if (flags & MX_PACK_ALPHA_CHANNEL) else ""
        image = Image.open(f)
        packImage(out, image, format, flags)
    out.close()

