using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace GraphCSharp
{
    class Program
    {
        static void Main(string[] args)
        {
            GraphBuilder graphBuilder = new GraphBuilder();
            Graph graph = graphBuilder.FromFile("Example.csv");

            Console.Write(graph.ToString());

            graph.ClearIngoingRleations(graph.FindNode("B"));
            graph.ClearOutgoingRleations(graph.FindNode("B"));

            graph.ClearRelations(graph.FindNode("A"));

            Node F = new Node("F");
            Node G = new Node("G");

            graph.AddNode(F);
            graph.AddNode(G);

            graph.AddRelation(F, G, 69);

            Console.Write(graph.ToString());

            graphBuilder.ToFile("asd.csv", graph);
        }
    }
}