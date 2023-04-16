package main // 一个工程只有一个main包

// 导入路径
import "fmt" // 用于输出

// 生产者
// 参数：数据管道，单向只写；标志管道，单向只读
func producer(data_channel chan<- int, flag_channel <-chan bool) {
	// 循环处理，接收到消费者标志后才退出循环和函数
	data := 0 //生产者生产的数据

	for {
		// select{}语句监听输入/输出（I/O）操作
		select {
		case data_channel <- data: //有数据写
			data++
		case flag := <-flag_channel: //有标志读
			fmt.Println("生产者读标志：", flag, "结束生产")
			return
		}
	}
}

// 消费者
// 参数：数据管道，单向只读；标志管道，单向只写
func consumer(data_channel <-chan int, flag_channel chan<- bool) {
	// 约定循环5次后，消费者停止消费，向生产者发送停止生产标志
	for i := 0; i < 5; i++ {
		data := <-data_channel //读数据
		fmt.Println("消费者读数据：", data)
	}

	flag_channel <- true //写标志

	return
}

// 一个工程只有一个main()函数，是程序的唯一入口
func main() {
	data_channel := make(chan int, 0)
	// 数据管道，生产者向消费者传输数据
	// 传输int类型数据，0：无缓冲，双向
	flag_channel := make(chan bool, 0)
	// 标志管道，消费者向生产者传输标志，消费者不再消费，让生产者停止生产
	// 传输bool类型数据，0：无缓冲，双向

	go consumer(data_channel, flag_channel) //go关键字开启goroutine处理消费者任务

	producer(data_channel, flag_channel) // main()中是主goroutine，处理生产者任务
}