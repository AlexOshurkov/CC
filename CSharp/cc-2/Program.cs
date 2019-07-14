using System;

namespace cc_2
{
	class Program
	{
		static bool is_kaprekar(ulong n)
		{
			ulong sq  = n * n;
			ulong tst = sq;
			uint  dig = 0;  //  count of digits

			while (tst > 0)
			{
				dig++;
				tst /= 10;
			}

			tst = sq;
			ulong sl = 0;
			ulong sr = 0;
			ulong lm = 1;
			ulong rm = 1;

			for (uint i = 0; i < dig; i++)
			{
				if ((dig % 2 != 0) && (i <= dig >> 1) ||
					(dig % 2 == 0) && (i <  dig >> 1))
				{
					sr += (tst % 10) * rm;
					rm *= 10;
				}
				else
				{
					sl += (tst % 10) * lm;
					lm *= 10;
				}

				tst /= 10;
			}


			return sr > 0 && n == (sr + sl);
		}

		static void Main(string[] args)
		{
			uint beg   = uint.Parse(Console.ReadLine());
			uint end   = uint.Parse(Console.ReadLine());
			bool exist = false;

			for (uint i = beg; i <= end; i++)
				if (is_kaprekar(i))
				{
					Console.Write((exist ? " " : "") + i.ToString());
					exist = true;
				}

			Console.WriteLine(exist ? "" : "INVALID RANGE");
			Console.ReadKey();
		}
	}
}
