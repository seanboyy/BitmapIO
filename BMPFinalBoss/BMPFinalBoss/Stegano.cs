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
            // Create a queue to contain the bit sequence of the text to be encoded
            Queue<bool> bitStream = new Queue<bool>();
            // convert message to boolean values in a queue
            foreach (char c in text)
                addChar(bitStream, c);
            // add a null terminator so we know when to stop reading
            addChar(bitStream, '\u0000');
            // Now all the text has been converted to bits and added to bit stream

            // The location of the current pixel in its row
            int pixelIdxW = 0;
            // The location of the current pixel in its column
            int pixelIdxH = 0;
            // The current bit of the color 
            int bitIdx = 0;

            while (bitStream.Count != 0)
            {
                // Get the value of the current pixel
                Color col = bitmap.GetPixel(pixelIdxW, pixelIdxH);
                // Determine whether to use Red, Green, or Blue
                byte modifyThis;
                switch(bitIdx / depth)
                {
                    // modify the red bit
                    case 0:
                        modifyThis = col.R;
                        break;
                    // modify the green bit
                    case 1:
                        modifyThis = col.G;
                        break;
                    // modify the blue bit
                    default:
                        modifyThis = col.B;
                        break;
                }

                // This is our actual functioning index for the value we want to modify, now we know which color we want
                // -1 because if we're dealing with the first character, we don't want to bit shift at all
                int bIdx = (depth - (bitIdx % depth))-1;

                // Find the value of the current bit there. This returns true if the bit is 0; otherwise returns false
                bool currentBit = !((char)(modifyThis & ('\u0001' << bIdx)) == '\u0000');

                // Get the next bit to encode
                bool bit = bitStream.Dequeue();

                // If the current bit is 1 and needs to be set to 1, do nothing.
                // the current bit is 1 and needs to be set to 0 - |
                if (currentBit && !bit)
                {
                    modifyThis = (byte)(modifyThis | ('\u0001' << bIdx));
                }
                // If the current bit is 0 and needs to be set to 0, do nothing.
                // The current bit is 0 and needs to be set to 1 - ^
                else if (!currentBit && bit)
                {
                    modifyThis = (byte)(modifyThis ^ ('\u0001' << bIdx));
                }

                // We've now modified the value appropriately.
                // All that's left is to put the modified color val back into the original color and reset
                // the pixel color. And then update all our indexes....

                Color returnCol;

                switch (bitIdx / depth)
                {
                    // modify the red bit
                    case 0:
                        returnCol = Color.FromArgb(col.A, modifyThis, col.G, col.B);
                        break;
                    // modify the green bit
                    case 1:
                        returnCol = Color.FromArgb(col.A, col.R, modifyThis, col.B);
                        break;
                    // modify the blue bit
                    default:
                        returnCol = Color.FromArgb(col.A, col.R, col.G, modifyThis);
                        break;
                }

                bitmap.SetPixel(pixelIdxW, pixelIdxH, returnCol);

                // next, we update all the indexes
                bitIdx++;
                // we've changed all the bits in this pixel we can. Move to the next pixel
                if (bitIdx >= depth * 3)
                {
                    bitIdx = 0;
                    pixelIdxW++; 
                    // we've changed all the pixels in this row that we can. Move to the next row. 
                    if (pixelIdxW >= bitmap.Width)
                    {
                        pixelIdxW = 0;
                        pixelIdxH++;
                    }
                }
            }
        }

        private void addChar(Queue<bool> q, char c)
        {
            for (int i = 0; i < 16; i++)
            {
                // determine the ith bit of c
                char val = (char)(c & ('\u0001'<<(15-i)));
                // add false to q if val is equal to \u0000 - value was a 0
                if (val == '\u0000')
                    q.Enqueue(false);
                else    // add true to q if val is not equal to \u0000 - value was a 1
                    q.Enqueue(true);
            }
        }

        // returns true if bit is 1; false if bit is 0
        bool ReadBitAtPos(byte data, int pos)
        {
            return !((data & '\u0001'<<pos) == '\u0000');
        }

        public string Decode()
        {
            // Create a bitStream
            Queue<bool> bitStream = new Queue<bool>();
            // Get all the data from the bitmap until 16 0's are read
            // The number of consecutive zeros that have been read
            int zeroCount = 0;
            // The location of the current pixel in its row
            int pixelIdxW = 0;
            // The location of the current pixel in its column
            int pixelIdxH = 0;
            // The current bit of the color 
            int bitIdx = 0;


            while (zeroCount < 16)
            {
                // Get the current pixel
                Color col = bitmap.GetPixel(pixelIdxW, pixelIdxH);
                // Get the next bit to read
                int bIdx = (depth - (bitIdx % depth)) - 1;
                bool bit = false;
                switch (bitIdx / depth)
                {
                    // read from the red color
                    case 0:
                        bit = ReadBitAtPos(col.R, bIdx);
                        break;
                    // read from the green color
                    case 1:
                        bit = (ReadBitAtPos(col.G, bIdx);
                        break;
                    // raed from the blue color
                    default:
                        bit = ReadBitAtPos(col.B, bIdx);
                        break;
                }

                // check to see if val is a zero
                if (!bit)
                    zeroCount++;
                else
                    zeroCount = 0;
                bitStream.Enqueue(bit);


                // next, we update all the indexes
                bitIdx++;
                // we've changed all the bits in this pixel we can. Move to the next pixel
                if (bitIdx >= depth * 3)
                {
                    bitIdx = 0;
                    pixelIdxW++;
                    // we've changed all the pixels in this row that we can. Move to the next row. 
                    if (pixelIdxW >= bitmap.Width)
                    {
                        pixelIdxW = 0;
                        pixelIdxH++;
                    }
                }
            }

            int debugVal = bitStream.Count % 16;

            // bitStream is now populated with 1's and 0's. Time to turn that into a string
            string returnVal = "";
            
            while (bitStream.Count != 0)
            {
                char c = '\u0000';
                for (int i=0; i<16; i++)
                {
                    if (bitStream.Dequeue())
                    {
                        c = (char)(c & '\u0001');
                    }
                    c <<= 1;
                }

                c >>= 1;
                returnVal += c;
            }

            return returnVal;
            //int j = 0;
            //int carryover = 0;
            //int temp2 = 0;
            //int temp3 = 0;
            //int temp4 = 0;
            //byte temp = 0;
            //byte mask = 0;
            //string ret = "";
            //for (int i = 0; i < (int)depth; ++i)
            //{
            //    mask |= 0x01;
            //    mask <<= 1;
            //}
            //for (int i = 0; i <= bitmap.Height * bitmap.Width; ++i)
            //{
            //    //does the following 
            //    //Pixel = RGB: for example 01011101, 11100101, 01010111
            //    //push that into temp:
            //    //temp1 = 00000000010111011110010101010111
            //    //grab <encoding depth> bits from R, G, and B and shift them around to temp2
            //    //encoding depth = 3
            //    //temp2 = 00000000000001010000000000000000
            //    //temp2 = 00000000000000000000000000000101
            //    //temp2 = 00000000000000000000000101000000
            //    //temp3 = 00000000000000000000010100000000
            //    //temp3 = 00000000000000000000000000000101
            //    //temp3 = 00000000000000000000000000101000
            //    //temp2 = 00000000000000000000000101101000
            //    //temp2 = 00000000000000000000000101101111
            //    //temp4 = 00000000000000000000000111111111
            //    //pull pixel data into an integer (32 bits)
            //    int temp1 = (int)bitmap.GetPixel(i, j).R << 16 | (int)bitmap.GetPixel(i, j).G << 8 | (int)bitmap.GetPixel(i, j).B;
            //    //mask R
            //    temp2 = temp1 & (mask << 16);
            //    //shift over
            //    temp2 >>= 16;
            //    //shift back
            //    temp2 <<= ((int)depth * 2);
            //    //mask G
            //    temp3 = temp1 & (mask << 8);
            //    //shift over
            //    temp3 >>= 8;
            //    //shift back
            //    temp3 <<= (int)depth;
            //    //add to masked data
            //    temp2 |= temp3;
            //    //mask B
            //    temp2 |= temp1 & mask;
            //    temp4 = (((mask << (int)depth) | mask) << (int)depth) | mask;
            //    //if (temp3 > 0xFF) /*todo: this*/;
            //    if ((i + 1) % (bitmap.Width) == 0) ++j;
            //}
            //return ret;
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
