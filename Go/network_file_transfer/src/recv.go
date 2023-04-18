package main

import (
	"fmt"
	"io" // 文件相关
	"net"
	"os" // 操作系统/文件相关
)

// 五、接收文件内容
func recv_file(file_name string, conn net.Conn) {
	file, create_error := os.Create(file_name) // 在当前路径下创建文件
	// 返回值：File结构体
	if create_error != nil {
		fmt.Println("os.Create():", create_error)
		return
	}

	defer file.Close() // 延迟关闭文件

	buffer := make([]byte, 1024)
	// 循环处理
	for {
		read_count, read_error := conn.Read(buffer) // 网络读取文件，按字节
		if read_error != nil {
			// 注意：读取完成时，会读取到EOF文件结束标志，错误标志置位为“EOF”，需要进行额外判断
			if read_error == io.EOF {
				fmt.Println("接收完成:", read_error)
			} else {
				fmt.Println("net.Read():", read_error)
			}

			return // 注意：接收完成和出现错误两种情况，函数返回，其他情况持续向本地写入文件
		}
		// if n == 0 { //对端断开，出问题
		// 	fmt.Println("接收完毕2")
		// 	break
		// }
		file.Write(buffer[:read_count]) // 本地写入文件，按字节
	}
}

func main() {
	// 一、监听连接请求
	listener, listen_error := net.Listen("tcp4", "127.0.0.1:8000")
	if listen_error != nil {
		fmt.Println("net.Listen():", listen_error)
		return
	}

	// 六、2.关闭连接
	defer listener.Close()

	// 二、接受连接请求
	conn, accept_error := listener.Accept()
	if accept_error != nil {
		fmt.Println("net.Accept():", accept_error)
		return
	}

	// 六、1.关闭连接
	defer conn.Close()

	// 三、接收文件名
	buffer := make([]byte, 1024)
	read_count, read_error := conn.Read(buffer)
	if read_error != nil {
		fmt.Println("net.Read():", read_error)
		return
	}

	file_name := string(buffer[:read_count]) // 获取文件名
	// 注意：网络字节转换为字符串

	// 四、发送，接收到文件名后的响应信息
	conn.Write([]byte("ok"))

	// 五、接收文件内容
	recv_file(file_name, conn)
}
