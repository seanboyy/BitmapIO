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
        Regex reg = new Regex("[\x20-\x7E\n]");

        public Stegano(string uri)
        {
            bitmap = new Bitmap(uri);
        }

        public void Encode(string text, decimal depth)
        {
            textLen = (bitmap.Width * 3 * bitmap.Height) / 8 - ((int)depth - 1);
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
                int temp1 = (int)bitmap.GetPixel(i, j).R << 16 | (int)bitmap.GetPixel(i, j).G << 8 | (int)bitmap.GetPixel(i, j).B;
                temp2 = temp1 & (mask << 16);
                temp2 >>= 16;
                temp2 <<= (int)depth;
                temp3 = temp1 & (mask << 8);
                temp3 >>= 8;
                temp3 <<= (int)depth;
                temp2 |= temp3;
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
    }
}
