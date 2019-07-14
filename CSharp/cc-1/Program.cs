using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;


namespace cc_1
{
	static class NativeMethods
	{
		[DllImport("kernel32.dll")]
		public static extern IntPtr LoadLibrary(string dllToLoad);

		[DllImport("kernel32.dll")]
		public static extern IntPtr GetProcAddress(IntPtr hModule, string procedureName);

		[DllImport("kernel32.dll")]
		public static extern bool FreeLibrary(IntPtr hModule);
	}

	class Program
	{

		[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
		private delegate double plus(double n1, double n2);

		[UnmanagedFunctionPointer(CallingConvention.Cdecl)]
		private delegate string plusstr(string str);

		static void Main(string[] args)
		{
			IntPtr pDll = NativeMethods.LoadLibrary(@"..\..\Release\Win32Project1.dll");
			if (pDll == IntPtr.Zero)
			{
				Console.WriteLine("error load dll");
				return;
			}

			IntPtr adr1 = NativeMethods.GetProcAddress(pDll, "plus");
			IntPtr adr2 = NativeMethods.GetProcAddress(pDll, "plusstr");
			//oh dear, error handling here

			if(adr1 == IntPtr.Zero || adr2 == IntPtr.Zero)
			{
				Console.WriteLine("error get pointer");
				return;
			}

			plus plusf = (plus)Marshal.GetDelegateForFunctionPointer(adr1,typeof(plus));
			plusstr plusstrf = (plusstr)Marshal.GetDelegateForFunctionPointer(adr2, typeof(plusstr));

			double theResult = plusf(1.123, 2.345);
			string s = plusstrf(@"abc\x40");

			bool result = NativeMethods.FreeLibrary(pDll);
			//remaining code here

			Console.ReadKey();
		}
	}
}
