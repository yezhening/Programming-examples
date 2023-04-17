package main

import (
	"fmt"
	"net" // 网络处理
	"os"  // 操作系统相关，这里用于接收用户输入
)

func main() {
	// 一、发送连接请求
	conn, dial_error := net.Dial("tcp4", "127.0.0.1:8000")
	// 参数：连接TCP，IPv4，本机IP地址127.0.0.1，端口号8000
	// 返回值：Conn接口（类似套接字文件描述符），error接口
	if dial_error != nil {
		fmt.Println("Dial() error:", dial_error)
		return // 注意：退出main()
	}

	// 三、关闭连接
	defer conn.Close() // main()结束前关闭连接。注意：Close()有返回值为error接口，使用defer后这里不再处理错误

	// 二、发送和接收数据
	// 开启goroutine并发处理用户终端输入数据，发送数据
	go func() {
		data_buffer := make([]byte, 16)
		// 数据缓冲区，切片类型，网络中以二进制/字节传输，后面Read()和Write()参数也是字节类型，16字节大小
		for {
			read_count, read_error := os.Stdin.Read(data_buffer) //从标准输入读取用户输入
			// 返回值：接收的字节数量int，error接口
			if read_error != nil {
				fmt.Println("Stdin.Read() error:", read_error)
				return // 注意：退出协程
			}

			conn.Write(data_buffer[:read_count-2]) //写入数据
			fmt.Println("Write:", string(data_buffer[:read_count-2]))
			// Windows会将\r\n写入，先-2再写入
			// 输出写入的数据，从[0,scan_count-2)的切片数据，byte需要转换为string类型
		}
	}()

	// 主协程处理接收的数据
	data_buffer := make([]byte, 16)
	for {
		read_count, read_error := conn.Read(data_buffer)
		if read_error != nil {
			fmt.Println("Read() error:", read_error)
			return // 注意：退出main()
		}

		fmt.Println("Read:", string(data_buffer[:read_count])) // 同理输出读取的数据
	}
}