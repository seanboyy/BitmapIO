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
            Input_TextBox.Text = "Please open a BMP file";
            Input_TextBox.Enabled = false;
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
                stegano = new Stegano(openFileDialog1.FileName, (int)UpandDown.Value);
                // Change the PictureBoxSizeMode
                BMP_PictureBox.SizeMode = PictureBoxSizeMode.AutoSize;
                // Set the image of the PictureBox to the opened file
                BMP_PictureBox.Image = Image.FromFile(openFileDialog1.FileName);

                // Set the Chars Available/Remaining
                Remaing_Char_Box.Text = "Characters Remaining: " + stegano.TextLength;

                Input_TextBox.Enabled = true;
                Input_TextBox.Text = "";

                steganoInit = true;
            }
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                stegano.Bitmap.Save(saveFileDialog1.FileName);
            }
        }

        private void closeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            BMP_PictureBox.Image = null;
            Input_TextBox.Text = "Please open a BMP File";
            Input_TextBox.Enabled = false;
            UpandDown.Value = 1;
            Remaing_Char_Box.Text = "Characters Remaining:";
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        private void Encode_Click(object sender, EventArgs e)
        {
            // This is the Encode Button
            stegano.Encode(Input_TextBox.Text);
        }

        private void Decode_Click(object sender, EventArgs e)
        {
            // This is the Decode Button
            Input_TextBox.Text = stegano.Decode();
        }

        private void TextBox_TextChanged(object sender, EventArgs e)
        {
            updateCharsRemaining();
        }

        private void updateCharsRemaining()
        {
            if (!steganoInit) return;
            int charsRemaining = stegano.TextLength - Input_TextBox.TextLength;
            Remaing_Char_Box.Text = "Characters Remaining: " + charsRemaining;
            if (charsRemaining < 0)
                Encode_Button.Enabled = false;
            else
                Encode_Button.Enabled = true;
        }

        private void depthChanged(object sender, EventArgs e)
        {
            stegano.Depth = (int)UpandDown.Value;
            updateCharsRemaining();
        }

        // I don't know what either of these are, but I can't seem to delete them...
        private void tableLayoutPanel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void tableLayoutPanel2_Paint(object sender, PaintEventArgs e)
        {

        }
    }
}
