namespace BMPFinalBoss
{
    partial class Steganography
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.closeToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.BMP_PictureBox = new System.Windows.Forms.PictureBox();
            this.tableLayoutPanel2 = new System.Windows.Forms.TableLayoutPanel();
            this.Encode_Button = new System.Windows.Forms.Button();
            this.Decode_Button = new System.Windows.Forms.Button();
            this.Encoding_DepthBox = new System.Windows.Forms.Label();
            this.Remaing_Char_Box = new System.Windows.Forms.Label();
            this.UpandDown = new System.Windows.Forms.NumericUpDown();
            this.Input_TextBox = new System.Windows.Forms.TextBox();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.menuStrip1.SuspendLayout();
            this.tableLayoutPanel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.BMP_PictureBox)).BeginInit();
            this.tableLayoutPanel2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.UpandDown)).BeginInit();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(24, 24);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(544, 24);
            this.menuStrip1.TabIndex = 0;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.openToolStripMenuItem,
            this.saveToolStripMenuItem,
            this.toolStripSeparator1,
            this.closeToolStripMenuItem,
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // openToolStripMenuItem
            // 
            this.openToolStripMenuItem.Name = "openToolStripMenuItem";
            this.openToolStripMenuItem.Size = new System.Drawing.Size(112, 22);
            this.openToolStripMenuItem.Text = "Open...";
            this.openToolStripMenuItem.Click += new System.EventHandler(this.openToolStripMenuItem_Click);
            // 
            // saveToolStripMenuItem
            // 
            this.saveToolStripMenuItem.Name = "saveToolStripMenuItem";
            this.saveToolStripMenuItem.Size = new System.Drawing.Size(112, 22);
            this.saveToolStripMenuItem.Text = "Save...";
            this.saveToolStripMenuItem.Click += new System.EventHandler(this.saveToolStripMenuItem_Click);
            // 
            // toolStripSeparator1
            // 
            this.toolStripSeparator1.Name = "toolStripSeparator1";
            this.toolStripSeparator1.Size = new System.Drawing.Size(109, 6);
            // 
            // closeToolStripMenuItem
            // 
            this.closeToolStripMenuItem.Name = "closeToolStripMenuItem";
            this.closeToolStripMenuItem.Size = new System.Drawing.Size(112, 22);
            this.closeToolStripMenuItem.Text = "Close";
            this.closeToolStripMenuItem.Click += new System.EventHandler(this.closeToolStripMenuItem_Click);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(112, 22);
            this.exitToolStripMenuItem.Text = "Exit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.exitToolStripMenuItem_Click);
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.Anchor = ((System.Windows.Forms.AnchorStyles)(((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.tableLayoutPanel1.ColumnCount = 1;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Controls.Add(this.BMP_PictureBox, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.tableLayoutPanel2, 0, 2);
            this.tableLayoutPanel1.Controls.Add(this.Input_TextBox, 0, 1);
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 27);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 3;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 70F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 30F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 35F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(544, 435);
            this.tableLayoutPanel1.TabIndex = 1;
            this.tableLayoutPanel1.Paint += new System.Windows.Forms.PaintEventHandler(this.tableLayoutPanel1_Paint);
            // 
            // BMP_PictureBox
            // 
            this.BMP_PictureBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.BMP_PictureBox.Location = new System.Drawing.Point(3, 3);
            this.BMP_PictureBox.Name = "BMP_PictureBox";
            this.BMP_PictureBox.Size = new System.Drawing.Size(538, 274);
            this.BMP_PictureBox.TabIndex = 2;
            this.BMP_PictureBox.TabStop = false;
            this.BMP_PictureBox.Click += new System.EventHandler(this.pictureBox_Click);
            // 
            // tableLayoutPanel2
            // 
            this.tableLayoutPanel2.ColumnCount = 5;
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 110F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 93F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 35F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel2.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 110F));
            this.tableLayoutPanel2.Controls.Add(this.Encode_Button, 0, 0);
            this.tableLayoutPanel2.Controls.Add(this.Decode_Button, 4, 0);
            this.tableLayoutPanel2.Controls.Add(this.Encoding_DepthBox, 1, 0);
            this.tableLayoutPanel2.Controls.Add(this.Remaing_Char_Box, 3, 0);
            this.tableLayoutPanel2.Controls.Add(this.UpandDown, 2, 0);
            this.tableLayoutPanel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel2.Location = new System.Drawing.Point(3, 403);
            this.tableLayoutPanel2.Name = "tableLayoutPanel2";
            this.tableLayoutPanel2.RowCount = 1;
            this.tableLayoutPanel2.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel2.Size = new System.Drawing.Size(538, 29);
            this.tableLayoutPanel2.TabIndex = 0;
            this.tableLayoutPanel2.Paint += new System.Windows.Forms.PaintEventHandler(this.tableLayoutPanel2_Paint);
            // 
            // Encode_Button
            // 
            this.Encode_Button.Dock = System.Windows.Forms.DockStyle.Fill;
            this.Encode_Button.Location = new System.Drawing.Point(3, 3);
            this.Encode_Button.Name = "Encode_Button";
            this.Encode_Button.Size = new System.Drawing.Size(104, 23);
            this.Encode_Button.TabIndex = 0;
            this.Encode_Button.Text = "Encode";
            this.Encode_Button.UseVisualStyleBackColor = true;
            this.Encode_Button.Click += new System.EventHandler(this.Encode_Click);
            // 
            // Decode_Button
            // 
            this.Decode_Button.Dock = System.Windows.Forms.DockStyle.Fill;
            this.Decode_Button.Location = new System.Drawing.Point(431, 3);
            this.Decode_Button.Name = "Decode_Button";
            this.Decode_Button.Size = new System.Drawing.Size(104, 23);
            this.Decode_Button.TabIndex = 1;
            this.Decode_Button.Text = "Decode";
            this.Decode_Button.UseVisualStyleBackColor = true;
            this.Decode_Button.Click += new System.EventHandler(this.Decode_Click);
            // 
            // Encoding_DepthBox
            // 
            this.Encoding_DepthBox.AutoSize = true;
            this.Encoding_DepthBox.Dock = System.Windows.Forms.DockStyle.Right;
            this.Encoding_DepthBox.Location = new System.Drawing.Point(116, 0);
            this.Encoding_DepthBox.Name = "Encoding_DepthBox";
            this.Encoding_DepthBox.Size = new System.Drawing.Size(84, 29);
            this.Encoding_DepthBox.TabIndex = 2;
            this.Encoding_DepthBox.Text = "Encoding Depth";
            this.Encoding_DepthBox.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
            // 
            // Remaing_Char_Box
            // 
            this.Remaing_Char_Box.AutoSize = true;
            this.Remaing_Char_Box.Dock = System.Windows.Forms.DockStyle.Fill;
            this.Remaing_Char_Box.Location = new System.Drawing.Point(241, 0);
            this.Remaing_Char_Box.Name = "Remaing_Char_Box";
            this.Remaing_Char_Box.Size = new System.Drawing.Size(184, 29);
            this.Remaing_Char_Box.TabIndex = 3;
            this.Remaing_Char_Box.Text = "Characters Remaining: ";
            this.Remaing_Char_Box.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // UpandDown
            // 
            this.UpandDown.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Left | System.Windows.Forms.AnchorStyles.Right)));
            this.UpandDown.Location = new System.Drawing.Point(206, 4);
            this.UpandDown.Maximum = new decimal(new int[] {
            8,
            0,
            0,
            0});
            this.UpandDown.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.UpandDown.Name = "UpandDown";
            this.UpandDown.Size = new System.Drawing.Size(29, 20);
            this.UpandDown.TabIndex = 4;
            this.UpandDown.Value = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.UpandDown.ValueChanged += new System.EventHandler(this.depthChanged);
            // 
            // Input_TextBox
            // 
            this.Input_TextBox.Dock = System.Windows.Forms.DockStyle.Fill;
            this.Input_TextBox.Location = new System.Drawing.Point(3, 283);
            this.Input_TextBox.Multiline = true;
            this.Input_TextBox.Name = "Input_TextBox";
            this.Input_TextBox.Size = new System.Drawing.Size(538, 114);
            this.Input_TextBox.TabIndex = 1;
            this.Input_TextBox.TextChanged += new System.EventHandler(this.TextBox_TextChanged);
            // 
            // statusStrip1
            // 
            this.statusStrip1.ImageScalingSize = new System.Drawing.Size(24, 24);
            this.statusStrip1.Location = new System.Drawing.Point(0, 460);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.Size = new System.Drawing.Size(544, 22);
            this.statusStrip1.TabIndex = 2;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.FileName = "openFileDialog1";
            this.openFileDialog1.FileOk += new System.ComponentModel.CancelEventHandler(this.openFileDialog1_FileOk);
            // 
            // saveFileDialog1
            // 
            this.saveFileDialog1.FileOk += new System.ComponentModel.CancelEventHandler(this.saveFileDialog1_FileOk);
            // 
            // Steganography
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(544, 482);
            this.Controls.Add(this.statusStrip1);
            this.Controls.Add(this.tableLayoutPanel1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Steganography";
            this.Text = "Steganography";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.BMP_PictureBox)).EndInit();
            this.tableLayoutPanel2.ResumeLayout(false);
            this.tableLayoutPanel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.UpandDown)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveToolStripMenuItem;
        private System.Windows.Forms.ToolStripSeparator toolStripSeparator1;
        private System.Windows.Forms.ToolStripMenuItem closeToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel2;
        private System.Windows.Forms.TextBox Input_TextBox;
        private System.Windows.Forms.PictureBox BMP_PictureBox;
        private System.Windows.Forms.Button Encode_Button;
        private System.Windows.Forms.Button Decode_Button;
        private System.Windows.Forms.Label Encoding_DepthBox;
        private System.Windows.Forms.Label Remaing_Char_Box;
        private System.Windows.Forms.NumericUpDown UpandDown;
    }
}