using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace BMPFinalBoss
{
    class Stegano
    {
        Bitmap bitmap;
        int textLen;
        public void Encode(Bitmap bitmap, string text, decimal depth)
        {
            textLen = (bitmap.Width * 3 * bitmap.Height) / 8 - ((int)depth - 1);
            int j = 0;
            for(int i = 0; i <= bitmap.Height * bitmap.Width * 3; ++i)
            {
                if ((i + 1) % (bitmap.Width * 3) == 0) ++j;
            }
        }

        public string Decode(Bitmap bitmap, decimal depth)
        {
            int j = 0;
            byte temp = 0;
            for (int i = 0; i <= bitmap.Height * bitmap.Width * 3; ++i)
            {
                for(int k = 0; k < depth; ++k)
                {

                }
                if ((i + 1) % (bitmap.Width * 3) == 0) ++j;
            }
            return "";
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
