using System;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Text.Json;

class Program {
    static void Main(string[] args) {
        
        TcpListener server = null;
        
        try {
            IPAddress ipAddress = IPAddress.Parse("127.0.0.1");
            int port = 8081;

            server = new TcpListener(ipAddress, port);

            server.Start();
            Console.WriteLine($"Server {ipAddress}:{port} on listening!");

            while (true) {
                Console.WriteLine("Waiting For Server !");
                TcpClient client = server.AcceptTcpClient();
                Console.WriteLine("Client Connected !");

                NetworkStream stream = client.GetStream();

                byte[] data = new byte[1024];
                int bytesRead = stream.Read(data, 0, data.Length);
                string receivedMessage = Encoding.ASCII.GetString(data, 0, bytesRead);
                Console.WriteLine($"Received Data: {receivedMessage} !");

                JsonDocument jsonDocument = JsonDocument.Parse(receivedMessage);

                foreach (JsonProperty property in jsonDocument.RootElement.EnumerateObject()) {
                    string key = property.Name;
                    JsonElement value = property.Value;
                    Console.WriteLine($"{key}: {value}");
                }

                client.Close();
            }
        }
        catch (Exception ex) {
            Console.WriteLine($"[Error] {ex.Message}");
        }
        finally {
            server?.Stop();
        }
    }
}
