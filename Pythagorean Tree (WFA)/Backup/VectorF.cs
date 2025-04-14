using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Drawing;

namespace howto_pythagorean_tree
{
    public class VectorF
    {
        public float X, Y;

        public VectorF(float x, float y)
        {
            X = x;
            Y = y;
        }
        public VectorF(PointF point1, PointF point2)
        {
            X = point2.X - point1.X;
            Y = point2.Y - point1.Y;
        }
        public VectorF(VectorF v)
        {
            X = v.X;
            Y = v.Y;
        }

        public static VectorF operator +(VectorF v1, VectorF v2)
        {
            return new VectorF(v1.X + v2.X, v1.Y + v2.Y);
        }

        public static VectorF operator -(VectorF v1, VectorF v2)
        {
            return new VectorF(v1.X - v2.X, v1.Y - v2.Y);
        }

        public static PointF operator +(PointF point, VectorF vector)
        {
            return new PointF(point.X + vector.X, point.Y + vector.Y);
        }

        public static PointF operator -(PointF point, VectorF vector)
        {
            return new PointF(point.X - vector.X, point.Y - vector.Y);
        }

        public static VectorF operator -(VectorF vector)
        {
            return -1 * vector;
        }

        public static VectorF operator *(VectorF vector, float scale)
        {
            return new VectorF(vector.X * scale, vector.Y * scale);
        }
        public static VectorF operator *(float scale, VectorF vector)
        {
            return vector * scale;
        }

        public static VectorF operator /(VectorF vector, float scale)
        {
            return new VectorF(vector.X / scale, vector.Y / scale);
        }

        public float Length
        {
            get
            {
                return (float)Math.Sqrt(X * X + Y * Y);
            }
            set
            {
                float scale = value / Length;
                X *= scale;
                Y *= scale;
            }
        }

        // Return a scaled version of the vector.
        public VectorF Scale(float scale)
        {
            return this * scale / Length;
        }

        // Make the vector unit length.
        public void Normalize()
        {
            Length = 1;
        }

        // Find the perpendicular vector in the counterclockwise direction.
        public VectorF PerpendicularCCW()
        {
            return new VectorF(Y, -X);
        }

        // Find the perpendicular vector in the clockwise direction.
        public VectorF PerpendicularCW()
        {
            return new VectorF(-Y, X);
        }
    }
}
