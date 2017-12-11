using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace BMPFinalBoss
{
    public partial class Steganography : Form
    {
        // Member Variables
        private Stegano stegano;
        private bool steganoInit = false;

        public Steganography()
        {
            InitializeComponent();
            InitializeOpenFileDialog();
            InitializeSaveFileDialog();
            textBox1.Text = "Please open a BMP file";
            textBox1.Enabled = false;
        }

        private void InitializeOpenFileDialog()
        {
            openFileDialog1 = new OpenFileDialog();
            openFileDialog1.Multiselect = false;
            openFileDialog1.Filter = "Bitmap Images(*.bmp)|*.bmp";
            openFileDialog1.Title = "Open Image";
        }

        private void InitializeSaveFileDialog()
        {
            saveFileDialog1 = new SaveFileDialog();
            saveFileDialog1.AddExtension = true;
            saveFileDialog1.Filter = "Bitmap Images(*.bmp)|*.bmp";
            saveFileDialog1.Title = "Save Image";
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                // Initialize the Stegano File
                stegano = new Stegano(openFileDialog1.FileName, (int)numericUpDown1.Value);
                // Change the PictureBoxSizeMode
                pictureBox1.SizeMode = PictureBoxSizeMode.AutoSize;
                // Set the image of the PictureBox to the opened file
                pictureBox1.Image = Image.FromFile(openFileDialog1.FileName);

                // Set the Chars Available/Remaining
                label2.Text = "Characters Remaining: " + stegano.TextLength;

                textBox1.Enabled = true;
                textBox1.Text = "";

                steganoInit = true;
            }
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                try
                {

                    //System.IO.FileStream fs = (System.IO.FileStream)saveFileDialog1.OpenFile();
                    //stegano.Bitmap.Save(fs, System.Drawing.Imaging.ImageFormat.Bmp);
                    stegano.Bitmap.Save(saveFileDialog1.FileName);
                } catch (Exception exception) {
                    int x = 1;
                }

            }
        }

        private void closeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            pictureBox1.Image = null;
            textBox1.Text = "Please open a BMP File";
            textBox1.Enabled = false;
            numericUpDown1.Value = 1;
            label2.Text = "Characters Remaining:";
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void openFileDialog1_FileOk(object sender, CancelEventArgs e)
        {
            // What is this?
        }

        private void saveFileDialog1_FileOk(object sender, CancelEventArgs e)
        {
            // Seriously, what is it?
        }

        private void button1_Click(object sender, EventArgs e)
        {
            // This is the Encode Button
            stegano.Encode(textBox1.Text);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            // This is the Decode Button
            textBox1.Text = stegano.Decode();
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            updateCharsRemaining();
        }

        private void updateCharsRemaining()
        {
            if (!steganoInit) return;
            int charsRemaining = stegano.TextLength - textBox1.TextLength;
            label2.Text = "Characters Remaining: " + charsRemaining;
            if (charsRemaining < 0)
                button1.Enabled = false;
            else
                button1.Enabled = true;
        }

        private void depthChanged(object sender, EventArgs e)
        {
            stegano.Depth = (int)numericUpDown1.Value;
            updateCharsRemaining();
        }
    }
}
