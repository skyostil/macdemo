import Image
import struct
import numpy
import psyco

psyco.full()

MX_PIXELFORMAT_I1 = 1
MX_SURFACE_FLAG_PRESHIFT = 0x1
MX_SURFACE_FLAG_RLE = 0x8
MX_PACK_ALPHA_CHANNEL = (0x1 << 32)

packFile = "../images.dat"

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
    ("../data/pc_closeup_bluescreen.png", BW, 0),
    ("../data/pc_closeup_bluescreen.png", BW, A),
    ("../data/mac_closeup.png", BW, 0),
    ("../data/pc_screen_bg.png", BW, C),
    ("../data/macbook_screen_bg.png", BW, C),
    ("../data/guys_on_street.png", BW, 0),
    ("../data/pedobear_run_side.png", BW, 0),
    ("../data/pedobear_run_side.png", BW, A),
    ("../data/pedobear_run_front.png", BW, 0),
    ("../data/pedobear_run_front.png", BW, A),
    ("../data/mac_disk_load.png", BW, 0),
    ("../data/mac_disk_fire.png", BW, 0),
    ("../data/disk_impact.png", BW, 0),
    ("../data/disk_impact.png", BW, A),
    ("../data/pedobear_impact.png", BW, 0),
    ("../data/pedobear_impact.png", BW, A),
    ("../data/text_title.png", BW, 0),
    ("../data/text_title.png", BW, A),
    ("../data/note1.png", BW, 0),
    ("../data/note2.png", BW, 0),
    ("../data/text_hey.png", BW, 0),
    ("../data/text_hey.png", BW, A),
    ("../data/text_look.png", BW, 0),
    ("../data/text_look.png", BW, A),
    ("../data/text_its.png", BW, 0),
    ("../data/text_its.png", BW, A),
    ("../data/text_grandpa.png", BW, 0),
    ("../data/text_grandpa.png", BW, A),
    ("../data/text_run.png", BW, 0),
    ("../data/text_run.png", BW, A),
    ("../data/text_any.png", BW, 0),
    ("../data/text_any.png", BW, A),
    ("../data/text_demos.png", BW, 0),
    ("../data/text_demos.png", BW, A),
    ("../data/text_lately.png", BW, 0),
    ("../data/text_lately.png", BW, A),
    ("../data/text_well_no.png", BW, 0),
    ("../data/text_well_no.png", BW, A),
    ("../data/text_ha.png", BW, 0),
    ("../data/text_ha.png", BW, A),
    ("../data/text_check.png", BW, 0),
    ("../data/text_check.png", BW, A),
    ("../data/text_this.png", BW, 0),
    ("../data/text_this.png", BW, A),
    ("../data/text_out.png", BW, 0),
    ("../data/text_out.png", BW, A),
    ("../data/text_yeah.png", BW, 0),
    ("../data/text_yeah.png", BW, A),
    ("../data/text_get_a.png", BW, 0),
    ("../data/text_get_a.png", BW, A),
    ("../data/text_load_of.png", BW, 0),
    ("../data/text_load_of.png", BW, A),
    ("../data/text_lets_see.png", BW, 0),
    ("../data/text_lets_see.png", BW, A),
    ("../data/text_okay.png", BW, 0),
    ("../data/text_okay.png", BW, A),
    ("../data/text_lol.png", BW, 0),
    ("../data/text_lol.png", BW, A),
    ("../data/text_help.png", BW, 0),
    ("../data/text_help.png", BW, A),
    ("../data/text_quick.png", BW, 0),
    ("../data/text_quick.png", BW, A),
    ("../data/text_call_the.png", BW, 0),
    ("../data/text_call_the.png", BW, A),
    ("../data/text_cops.png", BW, 0),
    ("../data/text_cops.png", BW, A),
    ("../data/text_sure_thing.png", BW, 0),
    ("../data/text_sure_thing.png", BW, A),
    ("../data/text_i.png", BW, 0),
    ("../data/text_i.png", BW, A),
    ("../data/text_oh_no.png", BW, 0),
    ("../data/text_oh_no.png", BW, A),
    ("../data/text_step_aside.png", BW, 0),
    ("../data/text_step_aside.png", BW, A),
    ("../data/text_kids.png", BW, 0),
    ("../data/text_kids.png", BW, A),
    ("../data/face_mac_happy.png", BW, PS),
    ("../data/face_mac_huh.png", BW, 0),
    ("../data/face_pc_idle.png", BW, PS),
    ("../data/face_pc_notice_mac.png", BW, 0),
    ("../data/face_macbook_notice_mac.png", BW, 0),
    ("../data/face_macbook_notice_mac_talk.png", BW, 0),
    ("../data/face_macbook_talk.png", BW, 0),
    ("../data/face_pc_talk.png", BW, 0),
]

def packImage(out, image, format, flags):
    assert format == MX_PIXELFORMAT_I1
    assert (image.size[0] % 8) == 0

    stride = image.size[0] / 8
    planeSize = stride * image.size[1]
    header = struct.pack("iiiiiii",
            image.size[0], image.size[1],
            stride,
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

