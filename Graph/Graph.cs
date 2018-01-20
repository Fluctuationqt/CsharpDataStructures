using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GraphCSharp
{
    class Graph
    {
        private List<Node> Nodes;

        public Graph()
        {
            Nodes = new List<Node>();
        }

        public void AddNode(Node n)
        {
            if (n == null)
            {
                throw new Exception("Cannot add empty object as node!");
            }

            Nodes.Add(n);
        }

        public void AddRelation(Node from, Node to, float weight)
        {
            if (from == to || from == null || to == null)
            {
                throw new Exception("Argument is empty or relates to itself");
            }

            Relation relation = new Relation(from, to, weight);
            from.AddRelation(relation);
            to.AddRelation(relation);
        }

        public IEnumerable<Node> GetNodes()
        {
            foreach (var node in Nodes)
            {
                yield return node;
            }
        }

        public Node FindNode(string data)
        {
            foreach (Node node in Nodes)
            {
                if (node.Data == data)
                    return node;
            }
            return null;
        }

        public void ClearOutgoingRleations(Node forClear)
        {
            if (forClear == null)
            {
                throw new Exception("Argument is empty");
            }

            foreach (Relation rel in forClear.GetOutgoingRelations())
            {
                forClear.RemoveRelation(rel);
                rel.To.RemoveRelation(rel);
            }
        }

        public void ClearIngoingRleations(Node forClear)
        {
            if (forClear == null)
            {
                throw new Exception("Argument is empty");
            }

            foreach (Relation rel in forClear.GetIngoingRelations())
            {
                forClear.RemoveRelation(rel);
                rel.From.RemoveRelation(rel);
            }
        }

        public void ClearRelations(Node forRemoval)
        {
            ClearIngoingRleations(forRemoval);
            ClearOutgoingRleations(forRemoval);
        }

        public void RemoveNode(Node forRemoval)
        {
            if (forRemoval == null)
            {
                throw new Exception("Cannot remove empty object");
            }

            Nodes = Nodes.Where(node => node != forRemoval).ToList();
            ClearRelations(forRemoval);
        }

        public void RemoveRelation(Node from, Node to)
        {
            if (from == to || from == null || from == null)
            {
                throw new Exception("Argument is empty or relates to itself");
            }

            from.RemoveRelation(from, to);
            to.RemoveRelation(from, to);
        }

        public override string ToString()
        {
            StringBuilder sb = new StringBuilder();

            sb.Append("#### Graph ####");
            sb.Append(System.Environment.NewLine);
            foreach (Node node in Nodes)
            {
                sb.Append(node.ToString());
                sb.Append(System.Environment.NewLine);
            }

            return sb.ToString();
        }
    }
}