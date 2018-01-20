using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GraphCSharp
{
    class Relation
    {
        public Node From { get; }
        public Node To { get; }
        public float Weight { get; }

        public Relation(Node from, Node to, float weight)
        {
            From = from;
            To = to;
            Weight = weight;
        }
    }
}