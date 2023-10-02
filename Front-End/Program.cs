using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Text.Json;

class Program {
    static void Main(string[] args) {
        
        try {
            IPAddress ipAddress = IPAddress.Parse("127.0.0.1");
            int port = 8081;

            TcpListener server = new TcpListener(ipAddress, port);

            server.Start();
            Console.WriteLine($"\nServer {ipAddress}:{port} on listening!");

            while (true) {
                Console.WriteLine("\nWaiting For Server!");

                TcpClient client = server.AcceptTcpClient();
                Console.WriteLine("\nClient Connected!\n");

                Console.WriteLine("----------------------------------");

                NetworkStream stream = client.GetStream();

                byte[] data = new byte[1024];
                int bytesRead = stream.Read(data, 0, data.Length);
                string receivedMessage = Encoding.ASCII.GetString(data, 0, bytesRead);
                //Console.WriteLine($"Received Data: {receivedMessage} !");

                JsonDocument jsonDocument = JsonDocument.Parse(receivedMessage);

                foreach (JsonProperty property in jsonDocument.RootElement.EnumerateObject()) {
                    string key = property.Name;
                    JsonElement value = property.Value;
                    Console.WriteLine($"{key}: {value}");
                }

                Console.WriteLine("----------------------------------\n");

                client.Close();
            }
        }
        catch (Exception ex) {
            Console.WriteLine($"[Error] {ex.Message}");
        }
    }
}