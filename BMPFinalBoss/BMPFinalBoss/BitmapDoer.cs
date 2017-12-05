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
        private int width;
        private int height;

        public int Width
        {
            get { return width; }
            set { width = value; }
        }

        public int Height
        {
            get { return height; }
            set { height = value; }
        }
    }
}
