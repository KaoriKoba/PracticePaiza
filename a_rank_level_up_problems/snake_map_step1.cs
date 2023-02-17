using System;

class Program
{
    static void Main()
    {
        string[] line = Console.ReadLine().Trim().Split(' ');
        int[] data = new int[3];
        for (var i = 0; i < 3; i++)
        {
            data[i] = int.Parse(line[0]);
        }

        char[,] map = new char[data[1], data[2]];
        for (var y = 0; y < data[1]; y++) // y
        {
            String[] strings = Console.ReadLine().Trim().Split(' ');

            for (var x = 0; x < data[2]; x++) // x
            {
                map[y,x] = char.Parse(strings[x]);
            }
        }

        // 表示する座標を取得する
        for (var i = 0; )


        /*
        var line1 = Console.ReadLine().Trim();
        var N = int.Parse(line1);
        for (var y = 0; y < N; y++)
        {
            string[] stArrayData = Console.ReadLine().Trim().Split(' ');
            Console.WriteLine("hello = {0} , world = {1}", stArrayData[0], stArrayData[1]);
        }
        */

        Console.WriteLine(data[0]);
        Console.WriteLine("XXXXXX");
    }
}
