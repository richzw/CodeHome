While we're on the subject of structures, we might as well look at bitfields. They can only be declared inside a
structure or a union, and allow you to specify some very small objects of a given number of bits in length. Their
usefulness is limited and they aren't seen in many programs, but we'll deal with them anyway. This example should
help to make things clear:

struct {
      /* field 4 bits wide */
      unsigned field1 :4;
      /*
       * unnamed 3 bit field
       * unnamed fields allow for padding
       */
      unsigned        :3;
      /*
       * one-bit field
       * can only be 0 or -1 in two's complement!
       */
      signed field2   :1;
      /* align next field on a storage unit */
      unsigned        :0;
      unsigned field3 :6;
}full_of_fields;

Each field is accessed and manipulated as if it were an ordinary member of a structure. The keywords signed and
unsigned mean what you would expect, except that it is interesting to note that a 1-bit signed field on a two's
complement machine can only take the values 0 or -1. The declarations are permitted to include the const and
volatile qualifiers.
The main use of bitfields is either to allow tight packing of data or to be able to specify the fields within some
externally produced data files. C gives no guarantee of the ordering of fields within machine words, so if you do
use them for the latter reason, you program will not only be non-portable, it will be compiler-dependent too. The
Standard says that fields are packed into ‘storage units’, which are typically machine words. The packing order, and
whether or not a bitfield may cross a storage unit boundary, are implementation defined. To force alignment to a
storage unit boundary, a zero width field is used before the one that you want to have aligned.
Be careful using them. It can require a surprising amount of run-time code to manipulate these things and you can
end up using more space than they save.
Bit fields do not have addresses—you can't have pointers to them or arrays of them.
