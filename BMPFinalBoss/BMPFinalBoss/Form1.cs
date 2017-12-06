using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace BMPFinalBoss
{
    public partial class Form1 : Form
    {
        Stegano stegano = new Stegano();
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            stegano.Encode(stegano.Bitmap, richTextBox1.Text, numericUpDown1.Value);
        }

        private void richTextBox1_TextChanged(object sender, EventArgs e)
        {
            if (richTextBox1.Text.Length <= stegano.TextLength) label2.Text = richTextBox1.Text.Length + "/" + stegano.TextLength;
            else label2.Text = "TOO MANY";
        }

        private void button2_Click(object sender, EventArgs e)
        {
            stegano.Decode(stegano.Bitmap, numericUpDown1.Value);
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            openFileDialog1.ShowDialog();
        }

        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            saveFileDialog1.ShowDialog();
        }

        private void closeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            pictureBox1.Image = null;
            stegano.Bitmap = null;
        }

        private void exitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Close();
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            openFileDialog1 = new OpenFileDialog();
            openFileDialog1.Filter = "Image Files(*.bmp)|*.bmp";
            openFileDialog1.AddExtension = true;
            openFileDialog1.Multiselect = false;
            openFileDialog1.Title = "Open...";
            saveFileDialog1 = new SaveFileDialog();
            saveFileDialog1.Filter = "Image Files(*.bmp)|*.bmp";
            saveFileDialog1.AddExtension = true;
            saveFileDialog1.Title = "Save...";
            pictureBox1 = new PictureBox();
            pictureBox1.SizeMode = PictureBoxSizeMode.StretchImage;
        }

        private void openFileDialog1_FileOk(object sender, CancelEventArgs e)
        {
            FileInfo info = new FileInfo(openFileDialog1.FileName);
            FileStream stream = info.OpenRead();
            pictureBox1.Image = Image.FromStream(stream);
            stegano.Bitmap = new Bitmap(stream);
            stream.Close();
        }

        private void saveFileDialog1_FileOk(object sender, CancelEventArgs e)
        {
            if(stegano.Bitmap != null)
            {
                stegano.Bitmap.Save(saveFileDialog1.FileName);
            }
        }

        private void numericUpDown1_ValueChanged(object sender, EventArgs e)
        {

        }

        private void menuStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }
    }
}
