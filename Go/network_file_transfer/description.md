# 说明

## 流程

发送方：客户端

1. 接收用户输入，获取完整文件路径并提取文件信息：fmt.Scan()、os.Stat()
2. 发送连接请求：net.Dial()
3. 发送文件名：net.Write()
4. 接收，接收方接收到文件名后的响应信息：net.Read()
5. 发送文件内容：os.Open()、os.Read()、net.Write()、os.Close()
6. 关闭连接：net.Close()

接收方：服务端

1. 监听连接请求：net.Listen(）
2. 接受连接请求：net.Accept()
3. 接收文件名：net.Read()
4. 发送，接收到文件名后的响应信息：net.Write()
5. 接收文件内容：os.Create()、net.Read()、os.Write()、os.Close()
6. 关闭连接：net.Close()

---

