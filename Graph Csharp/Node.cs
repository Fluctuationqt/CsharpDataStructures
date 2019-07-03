using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GraphCSharp
{
    class Node
    {
        public string Data { get; }
        private List<Relation> Relations;

        public Node(string data)
        {
            Data = data;
            Relations = new List<Relation>();
        }

        public void AddRelation(Relation relation)
        {
            if (relation == null)
            {
                throw new Exception("Argument is empty");
            }

            Relations.Add(relation);
        }

        public void RemoveRelation(Node from, Node to)
        {
            if (from == null || to == null)
            {
                throw new Exception("Argument is empty");
            }

            Relations =
                Relations.Where(rel => rel.From != from || rel.To != to).ToList();
        }

        public void RemoveRelation(Relation relation)
        {
            if (relation == null)
                throw new Exception("Argument is empty");

            Relations =
                Relations.Where(rel => rel != relation).ToList();
        }

        public IEnumerable<Relation> GetRelations()
        {
            foreach (var rel in Relations)
            {
                yield return rel;
            }
        }

        public IEnumerable<Relation> GetIngoingRelations()
        {
            foreach (var rel in Relations)
            {
                if (rel.To == this)
                {
                    yield return rel;
                }
            }
        }

        public IEnumerable<Relation> GetOutgoingRelations()
        {
            foreach (var rel in Relations)
            {
                if (rel.From == this)
                {
                    yield return rel;
                }
            }
        }

        public override string ToString()
        {
            StringBuilder sb = new StringBuilder();

            sb.Append("Node ");
            sb.Append(Data);
            sb.Append(System.Environment.NewLine);
            foreach (Relation rel in Relations)
            {
                // outgoing
                if (rel.From == this)
                {
                    sb.Append(rel.From.Data);
                    sb.Append("---");
                    sb.Append(rel.Weight);
                    sb.Append("-->");
                    sb.Append(rel.To.Data);
                }

                // ingoing
                if (rel.To == this)
                {
                    sb.Append(rel.To.Data);
                    sb.Append("<--");
                    sb.Append(rel.Weight);
                    sb.Append("---");
                    sb.Append(rel.From.Data);
                }
                sb.Append(System.Environment.NewLine);
            }

            return sb.ToString();
        }
    }
}