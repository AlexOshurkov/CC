using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Compression;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Security.Cryptography;


namespace RMSCrypt
{
//  Class for simple crypting/descrypting data
    class LightCrypt
    {
        private byte[] passkey    = null;

        public LightCrypt(String pass)
        {
            Password = pass;
        }

        public string Password
        {
            set
            {
                passkey = new SHA1Managed().ComputeHash(System.Text.Encoding.Default.GetBytes(value));
            }
        }

        public void Encrypt(byte[] msg)
        {
            if (msg == null)
                return;

            if (msg.Length == 0)
                return;

            for (int i = 0; i < msg.Length; i++)
                msg[i] = (byte)(msg[i] ^ passkey[i % passkey.Length] ^ (i + 1));
        }

        public void Decrypt(byte[] arr)
        {
            Encrypt(arr);
        }
    }

//  Gzip compressing/decompressing
    class Compressor
    {
        public static byte[] Compress(byte[] buff)
        {
            MemoryStream ms = new MemoryStream();
            GZipStream zip = new GZipStream(ms, CompressionMode.Compress, true);
            zip.Write(buff, 0, buff.Length);
            zip.Close();
            ms.Position = 0;

            byte[] compressed = new byte[ms.Length];
            ms.Read(compressed, 0, compressed.Length);

            byte[] gzBuff = new byte[compressed.Length + 4];
            Buffer.BlockCopy(compressed, 0, gzBuff, 4, compressed.Length);
            Buffer.BlockCopy(BitConverter.GetBytes(buff.Length), 0, gzBuff, 0, 4);
            return gzBuff;
        }

        public static byte[] Decompress(byte[] buff)
        {
            MemoryStream ms = new MemoryStream();
            int msgLength = BitConverter.ToInt32(buff, 0);
            ms.Write(buff, 4, buff.Length - 4);

            byte[] buffer = new byte[msgLength];

            ms.Position = 0;
            GZipStream zip = new GZipStream(ms, CompressionMode.Decompress);
            zip.Read(buffer, 0, buffer.Length);

            return buffer;
        }
    }
}
