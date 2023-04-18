package main

import (
	"fmt"
	"io" // 文件相关
	"net"
	"os" // 操作系统/文件相关
)

// 五、发送文件内容
func send_file(file_path string, conn net.Conn) {
	file, open_error := os.Open(file_path) // 打开文件
	// 返回值：File结构体
	if open_error != nil {
		fmt.Println("os.Open():", open_error)
		return
	}

	defer file.Close() // 延迟关闭文件

	buffer := make([]byte, 1024)
	// 循环处理
	for {
		read_count, read_error := file.Read(buffer) // 本地读取文件，按字节
		if read_error != nil {
			// 注意：读取完成时，会读取到EOF文件结束标志，错误标志置位为“EOF”，需要进行额外判断
			if read_error == io.EOF {
				fmt.Println("发送完成:", read_error)
			} else {
				fmt.Println("os.Read()", read_error)
			}

			return // 注意：发送完成和出现错误两种情况，函数返回，其他情况持续向网络写入文件
		}

		conn.Write(buffer[:read_count]) // 网络写入文件，按字节
	}
}

func main() {
	// 一、1.接收用户输入，获取完整文件路径。如：C:\Users\DSHH\Desktop\temp.txt
	fmt.Print("请输入完整文件路径：")
	var file_path string
	fmt.Scan(&file_path)

	// 一、2.提取文件信息
	file_info, stat_error := os.Stat(file_path)
	// 返回值：FileInfo = fs.FileInfo接口类型
	if stat_error != nil {
		fmt.Println("os.Stat():", stat_error)
		return
	}

	// 二、发送连接请求
	conn, dial_error := net.Dial("tcp4", "127.0.0.1:8000")
	if dial_error != nil {
		fmt.Println("net.Dial():", dial_error)
		return
	}

	// 六、关闭连接
	defer conn.Close()

	//  三、发送文件名
	_, write_error := conn.Write([]byte(file_info.Name()))
	// Name()返回string，如：temp.txt，转换为byte切片在网络中传输
	if write_error != nil {
		fmt.Println("net.Write():", write_error)
		return
	}

	// 四、接收，接收方接收到文件名后的响应信息
	buffer := make([]byte, 1024)
	read_count, read_error := conn.Read(buffer)
	if read_error != nil {
		fmt.Println("net.Read():", read_error)
		return
	}

	// 五、发送文件内容
	if string(buffer[:read_count]) == "ok" { // 注意：网络接收为byte字节序列，需要转换为string类型才能作比较
		send_file(file_path, conn)
		// 注意，参数使用完整文件路径而不是文件名，因为后续需要在指定路径打开文件
	}
}
