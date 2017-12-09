using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Text.RegularExpressions;
using System.Windows.Forms;

namespace BMPFinalBoss
{
    class Stegano
    {
        Bitmap bitmap;
        int textLen;
        int depth;
        Regex reg = new Regex("[\x20-\x7E\n]");

        public Stegano(string uri, int _depth)
        {
            bitmap = new Bitmap(uri);
            Depth = _depth;
        }

        public void Encode(string text)
        {
            int j = 0;
            for (int i = 0; i <= bitmap.Height * bitmap.Width * 3; ++i)
            {
                if ((i + 1) % (bitmap.Width * 3) == 0) ++j;
            }
        }

        public string Decode(decimal depth)
        {
            int j = 0;
            int carryover = 0;
            int temp2 = 0;
            int temp3 = 0;
            int temp4 = 0;
            byte temp = 0;
            byte mask = 0;
            string ret = "";
            for (int i = 0; i < (int)depth; ++i)
            {
                mask |= 0x01;
                mask <<= 1;
            }
            for (int i = 0; i <= bitmap.Height * bitmap.Width; ++i)
            {
                //does the following 
                //Pixel = RGB: for example 01011101, 11100101, 01010111
                //push that into temp:
                //temp1 = 00000000010111011110010101010111
                //grab <encoding depth> bits from R, G, and B and shift them around to temp2
                //encoding depth = 3
                //temp2 = 00000000000001010000000000000000
                //temp2 = 00000000000000000000000000000101
                //temp2 = 00000000000000000000000101000000
                //temp3 = 00000000000000000000010100000000
                //temp3 = 00000000000000000000000000000101
                //temp3 = 00000000000000000000000000101000
                //temp2 = 00000000000000000000000101101000
                //temp2 = 00000000000000000000000101101111
                //temp4 = 00000000000000000000000111111111
                //pull pixel data into an integer (32 bits)
                int temp1 = (int)bitmap.GetPixel(i, j).R << 16 | (int)bitmap.GetPixel(i, j).G << 8 | (int)bitmap.GetPixel(i, j).B;
                //mask R
                temp2 = temp1 & (mask << 16);
                //shift over
                temp2 >>= 16;
                //shift back
                temp2 <<= ((int)depth * 2);
                //mask G
                temp3 = temp1 & (mask << 8);
                //shift over
                temp3 >>= 8;
                //shift back
                temp3 <<= (int)depth;
                //add to masked data
                temp2 |= temp3;
                //mask B
                temp2 |= temp1 & mask;
                temp4 = (((mask << (int)depth) | mask) << (int)depth) | mask;
                //if (temp3 > 0xFF) /*todo: this*/;
                if ((i + 1) % (bitmap.Width) == 0) ++j;
            }
            return ret;
        }

        public Bitmap Bitmap
        {
            get { return bitmap; }
            set { bitmap = value; }
        }

        public int TextLength
        {
            get { return textLen; }
            set { textLen = value; }
        }

        public int Depth
        {
            get { return depth; }
            set
            {
                depth = value;
                textLen = (bitmap.Width * 3 * bitmap.Height) / (16 / depth);
            }
        }
    }
}
