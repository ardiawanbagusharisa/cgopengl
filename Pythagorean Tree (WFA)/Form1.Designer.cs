namespace pythagorean_tree_fractal
{
    partial class Form1
    {
        /// Required designer variable.
        private System.ComponentModel.IContainer components = null;

        /// Clean up any resources being used.
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

        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        private void InitializeComponent()
        {
            this.nudAlpha = new System.Windows.Forms.NumericUpDown();
            this.label4 = new System.Windows.Forms.Label();
            this.nudLength = new System.Windows.Forms.NumericUpDown();
            this.label2 = new System.Windows.Forms.Label();
            this.nudDepth = new System.Windows.Forms.NumericUpDown();
            this.label1 = new System.Windows.Forms.Label();
            this.picCanvas = new System.Windows.Forms.PictureBox();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.label3 = new System.Windows.Forms.Label();
            this.comboBox2 = new System.Windows.Forms.ComboBox();
            ((System.ComponentModel.ISupportInitialize)(this.nudAlpha)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudLength)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudDepth)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picCanvas)).BeginInit();
            this.SuspendLayout();
            // 
            // nudAlpha
            // 
            this.nudAlpha.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.nudAlpha.Location = new System.Drawing.Point(480, 621);
            this.nudAlpha.Maximum = new decimal(new int[] {
            360,
            0,
            0,
            0});
            this.nudAlpha.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.nudAlpha.Name = "nudAlpha";
            this.nudAlpha.Size = new System.Drawing.Size(42, 22);
            this.nudAlpha.TabIndex = 17;
            this.nudAlpha.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.nudAlpha.Value = new decimal(new int[] {
            60,
            0,
            0,
            0});
            this.nudAlpha.ValueChanged += new System.EventHandler(this.parameter_ValueChanged);
            // 
            // label4
            // 
            this.label4.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(438, 626);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(36, 12);
            this.label4.TabIndex = 16;
            this.label4.Text = "Alpha:";
            // 
            // nudLength
            // 
            this.nudLength.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.nudLength.Location = new System.Drawing.Point(370, 621);
            this.nudLength.Maximum = new decimal(new int[] {
            300,
            0,
            0,
            0});
            this.nudLength.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.nudLength.Name = "nudLength";
            this.nudLength.Size = new System.Drawing.Size(42, 22);
            this.nudLength.TabIndex = 13;
            this.nudLength.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.nudLength.Value = new decimal(new int[] {
            100,
            0,
            0,
            0});
            this.nudLength.ValueChanged += new System.EventHandler(this.parameter_ValueChanged);
            // 
            // label2
            // 
            this.label2.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(323, 626);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(27, 12);
            this.label2.TabIndex = 12;
            this.label2.Text = "Size:";
            // 
            // nudDepth
            // 
            this.nudDepth.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.nudDepth.Location = new System.Drawing.Point(255, 621);
            this.nudDepth.Maximum = new decimal(new int[] {
            15,
            0,
            0,
            0});
            this.nudDepth.Name = "nudDepth";
            this.nudDepth.Size = new System.Drawing.Size(42, 22);
            this.nudDepth.TabIndex = 11;
            this.nudDepth.TextAlign = System.Windows.Forms.HorizontalAlignment.Center;
            this.nudDepth.Value = new decimal(new int[] {
            2,
            0,
            0,
            0});
            this.nudDepth.ValueChanged += new System.EventHandler(this.parameter_ValueChanged);
            // 
            // label1
            // 
            this.label1.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(191, 626);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(60, 12);
            this.label1.TabIndex = 10;
            this.label1.Text = "Rec. Depth:";
            // 
            // picCanvas
            // 
            this.picCanvas.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.picCanvas.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.picCanvas.Location = new System.Drawing.Point(12, 11);
            this.picCanvas.Name = "picCanvas";
            this.picCanvas.Size = new System.Drawing.Size(999, 601);
            this.picCanvas.TabIndex = 9;
            this.picCanvas.TabStop = false;
            this.picCanvas.Paint += new System.Windows.Forms.PaintEventHandler(this.picCanvas_Paint);
            this.picCanvas.Resize += new System.EventHandler(this.picCanvas_Resize);
            // 
            // comboBox1
            // 
            this.comboBox1.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Items.AddRange(new object[] {
            "None",
            "Red",
            "Purple",
            "Blue",
            "Green",
            "Yellow",
            "Orange"});
            this.comboBox1.Location = new System.Drawing.Point(560, 621);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(121, 20);
            this.comboBox1.TabIndex = 19;
            this.comboBox1.Text = "None";
            this.comboBox1.SelectedIndexChanged += new System.EventHandler(this.parameter_ValueChanged);
            // 
            // label3
            // 
            this.label3.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.label3.Location = new System.Drawing.Point(250, 593);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(523, 12);
            this.label3.TabIndex = 20;
            this.label3.Text = "Adjust the depth to crete sub rectangles, adjust the length to change the size, a" +
    "djust the alpha to change the ratio.";
            this.label3.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // comboBox2
            // 
            this.comboBox2.Anchor = System.Windows.Forms.AnchorStyles.Bottom;
            this.comboBox2.FormattingEnabled = true;
            this.comboBox2.Items.AddRange(new object[] {
            "3:4:5",
            "5:12:13",
            "Free"});
            this.comboBox2.Location = new System.Drawing.Point(712, 621);
            this.comboBox2.Name = "comboBox2";
            this.comboBox2.Size = new System.Drawing.Size(121, 20);
            this.comboBox2.TabIndex = 21;
            this.comboBox2.Text = "Free";
            this.comboBox2.SelectedIndexChanged += new System.EventHandler(this.parameter_ValueChanged);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1023, 647);
            this.Controls.Add(this.comboBox2);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.comboBox1);
            this.Controls.Add(this.nudAlpha);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.nudLength);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.nudDepth);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.picCanvas);
            this.Name = "Form1";
            this.Text = "Pythagorean Tree Fractals";
            ((System.ComponentModel.ISupportInitialize)(this.nudAlpha)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudLength)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.nudDepth)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picCanvas)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.NumericUpDown nudAlpha;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.NumericUpDown nudLength;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.NumericUpDown nudDepth;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.PictureBox picCanvas;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.ComboBox comboBox2;
    }
}

