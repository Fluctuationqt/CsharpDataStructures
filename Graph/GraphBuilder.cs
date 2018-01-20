using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GraphCSharp
{
    class GraphBuilder
    {
        public Graph FromFile(string path)
        {
            Graph graph = new Graph();

            using (var reader = new StreamReader(@path))
            {
                // read entire file and create nodes
                while (!reader.EndOfStream)
                {
                    var line = reader.ReadLine();
                    var values = line.Split(',');
                    string nodeName = values[0];
                    Node node = new Node(nodeName);
                    graph.AddNode(node);
                }

                // reset stream reader
                reader.DiscardBufferedData();
                reader.BaseStream.Seek(0, System.IO.SeekOrigin.Begin);

                // read file again and create relations
                while (!reader.EndOfStream)
                {
                    var line = reader.ReadLine();
                    var values = line.Split(',');
                    var nodeFrom = graph.FindNode(values[0]);
                    float weight;

                    for (int i = 1; i < values.Length; i += 2)
                    {
                        float.TryParse(values[i], out weight);
                        var nodeTo = graph.FindNode(values[i + 1]);
                        Relation rel = new Relation(nodeFrom, nodeTo, weight);
                        nodeFrom.AddRelation(rel);
                        nodeTo.AddRelation(rel);
                    }

                }
            }
            return graph;
        }

        public void ToFile(string path, Graph graph)
        {
            var csv = new StringBuilder();
            foreach (Node node in graph.GetNodes())
            {
                string name = node.Data;
                string relationsString = "";

                foreach (Relation rel in node.GetOutgoingRelations())
                {
                    relationsString += "," + rel.Weight + "," + rel.To.Data;
                    rel.To.RemoveRelation(rel);
                }

                var newLine = string.Format("{0}{1}", name, relationsString);
                csv.AppendLine(newLine);
            }
            File.WriteAllText(path, csv.ToString());
        }
    }

}