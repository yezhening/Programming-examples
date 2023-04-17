package main

import (
	"fmt"
	"net" // 网络处理
)

// 处理连接请求
func handle(conn net.Conn) { // 注意：conn的类型Conn是net包中的接口，需要引用
	// 四、1关闭连接
	defer conn.Close() // handle()结束前关闭连接。注意：Close()有返回值为error接口，使用defer后这里不再处理错误

	// 获取连接请求的地址
	addr := conn.RemoteAddr().String()
	// RemoteAddr()返回值为Addr接口，Addr接口实现了String()，String()返回值为string类型
	fmt.Println("RemoteAddr:", addr)

	// 三、接收和发送数据
	data_buffer := make([]byte, 16)
	// 数据缓冲区，切片类型，网络中以二进制/字节传输，后面Read()和Write()参数也是字节类型，16字节大小

	// 接收并原封不动发送回所接收的数据
	// 循环处理，只有在接收“quit”时，才退出handle()协程
	for {
		// 读取数据
		read_count, read_error := conn.Read(data_buffer)
		// 返回值：接收的字节数量int，error接口
		if read_error != nil {
			fmt.Println("Read() error:", read_error)
			return // 注意：异常退出handle(）协程
		}
		fmt.Println("Read:", string(data_buffer[:read_count]))
		// 输出读取的数据，从[0,read_count-2)的切片数据，byte需要转换为string类型
		// 注意：Windows会多传输\r\n两个字符，所以要-2

		// 如果是“quit”，退出handle()协程
		if string(data_buffer[:read_count]) == "quit" {
			return // 注意：正常退出handle(）协程
		}

		// 写入数据，直接写字节数组
		_, write_error := conn.Write(data_buffer[:read_count])
		// 返回值：写入的字节数量不需要，error接口
		if write_error != nil {
			fmt.Println("Write() error:", write_error)
			return // 注意：异常退出handle(）协程
		}
		fmt.Println("Write:", string(data_buffer[:read_count])) // 同理输出写入数据
	}
}

func main() {
	// 一、监听连接请求
	listener, listen_error := net.Listen("tcp4", "127.0.0.1:8000")
	// 参数：使用TCP，IPv4，本机IP地址127.0.0.1，端口号8000
	// 返回值：Listener接口（类似监听套接字文件描述符），error接口
	if listen_error != nil {
		fmt.Println("Listen() error:", listen_error) // Println()有返回值，不再处理
		return                                       // 注意：退出main()
	}

	// 四、2关闭连接
	defer listener.Close() // main()结束前关闭连接。注意：Close()有返回值为error接口，使用defer后这里不再处理错误

	for {
		// 二、循环接受连接请求
		conn, accept_error := listener.Accept()
		// 返回值：Conn接口（类似连接套接字文件描述符），error接口
		if accept_error != nil {
			fmt.Println("Accept() error:", accept_error)
			continue // 注意：继续for{}循环接受连接请求，而不是return退出main()
		}

		// 开启goroutine并发处理多客户端请求，一个conn代表一个客户端
		go handle(conn)
	}
}