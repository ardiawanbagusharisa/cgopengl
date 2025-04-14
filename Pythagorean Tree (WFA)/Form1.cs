using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Drawing.Drawing2D;

namespace pythagorean_tree_fractal
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        // Main drawing call. 
        private void picCanvas_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.Clear(picCanvas.BackColor);
            e.Graphics.SmoothingMode = SmoothingMode.AntiAlias;

            try
            {
                // Free aspect ratio default
                float oriAlpha = (float)nudAlpha.Value;

                if (comboBox2.Text == "3:4:5")
                {
                    oriAlpha = 60;
                    nudAlpha.Value = 60;
                }
                else if (comboBox2.Text == "5:12:13")
                {
                    oriAlpha = 67.4f;
                    nudAlpha.Value = 67;
                }

                int recDepth = (int)nudDepth.Value;
                int length = (int)nudLength.Value;
                float alpha = (float)((double)oriAlpha * Math.PI / 180.0);  //(float)((double)nudAlpha.Value * Math.PI / 180.0);
                float root_x = picCanvas.ClientSize.Width / 2;
                float root_y = picCanvas.ClientSize.Height * 0.9f;
                VectorF v_base = new VectorF(length, 0);
                PointF ll_corner = new PointF(root_x, root_y) - v_base / 2;

                DrawBranch(e.Graphics, Pens.Black, recDepth, recDepth,
                            ll_corner, v_base, alpha, v_base.Length);

            }
            catch
            {
            }
        }

        // Redraw.
        private void parameter_ValueChanged(object sender, EventArgs e)
        {
            picCanvas.Refresh();
        }

        private void picCanvas_Resize(object sender, EventArgs e)
        {
            picCanvas.Refresh();
        }

        // Get brush color.
        private Brush GetBrushByDepth(string selectedColor, int depth, int maxDepth)
        {
            double fade = depth / (double)maxDepth;
            int a = 255;
            int r = 0, g = 0, b = 0;

            switch (selectedColor)
            {
                case "Red":
                    r = (int)(255 * fade);
                    break;

                case "Purple":
                    r = (int)(128 * fade);
                    b = (int)(128 * fade);
                    break;

                case "Blue":
                    b = (int)(255 * fade);
                    break;

                case "Green":
                    g = (int)(255 * fade);
                    break;

                case "Yellow":
                    r = (int)(255 * fade);
                    g = (int)(255 * fade);
                    break;

                case "Orange":
                    r = (int)(255 * fade);
                    g = (int)(165 * fade);
                    break;

                default:
                    return null;
            }

            return new SolidBrush(Color.FromArgb(a, r, g, b));
        }

        // Recursive drawing function. 
        private void DrawBranch(Graphics gr, Pen pen, int depth, int maxDepth,
            PointF ll_corner, VectorF v_base, float alpha, float initialLength)
        {
            // Compute corners
            VectorF v_height = v_base.PerpendicularCCW();
            PointF[] points =
            {
                ll_corner,
                ll_corner + v_base,
                ll_corner + v_base + v_height,
                ll_corner + v_height,
            };

            // Draw rectangle
            Brush brush = GetBrushByDepth(comboBox1.SelectedItem?.ToString(), depth, maxDepth);
            if (brush != null || comboBox1.SelectedItem?.ToString() != "None")
            { 
                gr.FillPolygon(brush, points); 
            }    
            gr.DrawPolygon(pen, points);
            
            if (depth > 0)
            {
                // LEFT BRANCH
                double w1 = v_base.Length * Math.Cos(alpha);
                float wb1 = (float)(w1 * Math.Cos(alpha));
                float wh1 = (float)(w1 * Math.Sin(alpha));
                VectorF v_base1 = v_base.Scale(wb1) + v_height.Scale(wh1);
                PointF ll_corner1 = ll_corner + v_height;

                DrawBranch(gr, pen, depth - 1, maxDepth, ll_corner1, v_base1, alpha, initialLength);

                // RIGHT BRANCH
                double beta = Math.PI / 2.0 - alpha;
                double w2 = v_base.Length * Math.Sin(alpha);
                float wb2 = (float)(w2 * Math.Cos(beta));
                float wh2 = (float)(w2 * Math.Sin(beta));
                VectorF v_base2 = v_base.Scale(wb2) - v_height.Scale(wh2);
                PointF ll_corner2 = ll_corner1 + v_base1;

                DrawBranch(gr, pen, depth - 1, maxDepth, ll_corner2, v_base2, alpha, initialLength);
            }
        }

    }
}
