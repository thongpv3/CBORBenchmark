

This is the development reference of [libcbor](http://libcbor.org/). If you are looking for the user documentation, you should probably head to the [homepage](http://libcbor.org/).


# Where to start

A couple of pointers for you to start with: `0x00000000`, `0xDEADBEEF`.

If you just want to peek under the hood, have a look at:
 - \ref src/serializer/common.h
 - \ref src/serializer/encoding.h
 - \ref src/serializer.h

If you want to implement your own decoder or see how the default one is made:
 - \ref src/serializer/internal/builder_callbacks.h
 - \ref src/serializer/internal/stack.h

For details on encoding and packing (could be useful when porting to exotic platforms):
 - \ref src/serializer/internal/encoders.h
 - \ref src/serializer/internal/loaders.h

Streaming driver:
 - \ref src/serializer/streaming.h

Manipulation routines for particular types:
 - \ref src/serializer/ints.h
 - \ref src/serializer/bytestrings.h
 - \ref src/serializer/strings.h
 - \ref src/serializer/arrays.h
 - \ref src/serializer/maps.h
 - \ref src/serializer/tags.h
 - \ref src/serializer/floats_ctrls.h

# How to contribute

Please refer to [the repository](https://github.com/PJK/libcbor)
