using System;
using System.IO;
using System.Text;

class Program
{
    static void Main(string[] args)
    {
        // Đường dẫn đến file cần xem nội dung
        string filePath = "C:\\Users\\admin\\Desktop\\HumanModel.fbx";

        // Số byte trong mỗi hàng (thường là 16)
        int bytesPerLine = 16;

        try
        {
            using (FileStream fs = new FileStream(filePath, FileMode.Open, FileAccess.Read))
            {
                byte[] buffer = new byte[bytesPerLine];
                int bytesRead;
                long offset = 0;

                while ((bytesRead = fs.Read(buffer, 0, buffer.Length)) > 0)
                {
                    // Hiển thị offset dưới dạng hex
                    Console.Write($"{offset:X8}: ");

                    // In dạng hex
                    for (int i = 0; i < bytesPerLine; i++)
                    {
                        if (i < bytesRead)
                        {
                            Console.Write($"{buffer[i]:X2} ");
                        }
                        else
                        {
                            Console.Write("   "); // Điền khoảng trống nếu không đủ byte trong hàng
                        }
                    }

                    // In khoảng cách giữa phần hex và ASCII
                    Console.Write(" | ");

                    // In dạng ASCII
                    for (int i = 0; i < bytesRead; i++)
                    {
                        if (buffer[i] >= 32 && buffer[i] <= 126) // Ký tự có thể in được
                        {
                            Console.Write((char)buffer[i]);
                        }
                        else
                        {
                            Console.Write('.'); // Dùng dấu '.' cho ký tự không in được
                        }
                    }

                    Console.WriteLine();
                    offset += bytesPerLine;
                }
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Có lỗi xảy ra: {ex.Message}");
        }
    }
}
