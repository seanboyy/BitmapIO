﻿using System;
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
            textBox1.Text = "Please select a BMP file";
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
                stegano = new Stegano(openFileDialog1.FileName);
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
                stegano.Bitmap.Save(saveFileDialog1.FileName);
            }
        }

        private void closeToolStripMenuItem_Click(object sender, EventArgs e)
        {
            pictureBox1.Image = pictureBox1.InitialImage;
            textBox1.Text = "Please select a BMP File";
            textBox1.Enabled = false;
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
        }

        private void button2_Click(object sender, EventArgs e)
        {
            // This is the Decode Button
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            if (!steganoInit) return;
            label2.Text = "Characters Remaining: " + (stegano.TextLength - textBox1.TextLength);
        }
    }
}
