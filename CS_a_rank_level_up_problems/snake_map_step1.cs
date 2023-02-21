using System;

class Program
{
    static void Main()
    {
        string[] line = Console.ReadLine().Trim().Split(' ');
        int[] data = new int[3];
        for (var i = 0; i < 3; i++)
        {
            data[i] = int.Parse(line[i]);
        }

        // index 0 -> Hy, 1 -> Wx, 2 -> N
        char[,] map = new char[data[0], data[1]];
        for (var y = 0; y < data[0]; y++) // y
        {
            String strings = Console.ReadLine().Trim();

            for (var x = 0; x < data[1]; x++) // x
            {
                map[y,x] = strings[x];
            }
        }

        // 表示する座標を取得して表示
        for (var i = 0; i < data[2]; i++ )
        {
            line = Console.ReadLine().Trim().Split(' ');
            int y = int.Parse(line[0]);
            int x = int.Parse(line[1]);
            Console.WriteLine(map[y, x]);
        }

    }
}