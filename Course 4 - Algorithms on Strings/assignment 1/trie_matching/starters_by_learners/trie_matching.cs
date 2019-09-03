using System;
using System.Collections.Generic;
using System.Linq;

namespace trie_matching
{
    class Program
    {
        static void Main(string[] args)
        {
            string text = Console.ReadLine();
            int n = int.Parse(Console.ReadLine());
            List<string> patterns = new List<string>();
            for (int i = 0; i < n; i++)
            {
                string s = Console.ReadLine();
                patterns.Add(s);
            }

            List<int> answers = Solve(text, patterns);
            string answersLine = string.Join(" ", answers);
            Console.WriteLine(answersLine);
        }

        static List<int> Solve(string text, List<string> patterns)
        {
            List<int> ans = new List<int>();
            //write your code here

            return ans;
        }
    }
}