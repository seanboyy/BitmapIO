using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Drawing;

namespace BMPFinalBoss
{
    class BitmapDoer
    {
        private Bitmap bitmap;
        private int length;
        private byte depth;

        public BitmapDoer(string file)
        {
            bitmap = new Bitmap(file);
            length = bitmap.Width * 3 * bitmap.Height;
        }

        public int Width
        {
            get { return bitmap.Width; }
        }

        public int Height
        {
            get { return bitmap.Height; }
        }

        public Bitmap Bitmap
        {
            get { return bitmap; }
        }

        public int Length
        {
            get { return length; }
        }

        public byte Depth
        {
            get { return depth; }
            set { depth = value; }
        }
    }
}
