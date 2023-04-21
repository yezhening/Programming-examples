// 一、导入http模块
const http_module = require('http')    // HTTP相关
const path_module = require('path') // 字符串路径相关
const fs_module = require('fs')    // 文件系统相关

// 二、创建服务端对象
// 参数：可选项服务端如timeout和keepalive等配置，自动添加到‘request’请求事件的回调函数：当有客户端发起请求时，调用这个回调函数
// 返回值：http.server对象
const server = http_module.createServer()

const host = '127.0.0.1'    // 主机
const port = 8000   // 端口
const request_query_stringing_key = 'key'   // 请求url中，查询字符串的键
const site_root_directory = 'www'   // 网站根目录

// 三、服务端对象绑定‘request’请求事件，监听客户端请求
// emitter.on(eventName, listener)是node.js中的事件绑定方法
// 当有客户端发起请求时，调用这个回调函数：传入http.IncomingMessage请求对象和http.ServerResponse响应对象
server.on('request', (request, response) => {
    // 1. 获取http请求信息
    // http请求有3部分：请求行，请求头和请求体
    // 请求行有3部分：方法，url，http版本
    // （1）获取方法：“GET”，这里不需要
    // const request_method = request.method
    // （1）获取url：“/index.html?key=value”
    const request_url = request.url
    // （1）获取版本：“1.1”，这里不需要
    // const request_version = request.httpVersion   
    // （2）获取请求头，返回键值对object，这里不需要
    // const request_headers = request.headers 
    // （3）获取请求体，返回string。GET方法请求体一般为空，这里不需要
    // let request_body = ''
    // request.on('data', (chunk) => { // 请求绑定‘data’事件，数据按流传输，有数据时读取chunk为Buffer对象，自动转换为string
    //     request_body += chunk
    // })
    // request.on('end', () => { // 请求绑定‘end’事件，数据传输完成时触发
    //     console.log(request_body)
    // })

    //  2. 处理url。如http://127.0.0.1:8000/index.html?key=value
    // url有4部分：协议“http://”，地址主机名和端口“127.0.0.1:8000”，路径“/index.html”，查询字符串“?key=value”
    // (1）获取协议http，这里不需要
    // (2) 获取地址，这里不需要
    const absolute_url = 'http://' + host + ':' + port + request_url    // 获取请求的绝对url。如http://127.0.0.1:8000/index.html?key=value
    const request_path_query_string = new URL(absolute_url)  // 解析绝对url，获取路径和查询字符串。如：/index.html?key=value
    // （3）获取路径。如：/index.html
    const request_path = request_path_query_string.pathname
    // （4）获取查询字符串。返回object如：{'key' => 'value'}
    const request_query_string = request_path_query_string.searchParams
    const request_query_string_value = request_query_string.get(request_query_stringing_key)    // 获取查询字符串的值。如：通过'key'获取'value'

    // 3. 结合网络路径和查询字符串，映射为本地文件系统中的路径
    let fs_path = ""
    if (request_path === '/') {
        fs_path = path_module.join(__dirname, site_root_directory, "index.html")
        // 对于url为'/'的网络路径，映射为服务端js文件所在当前目录下，网站根目录下的index.html文件路径
        // 如：C:\Users\DSHH\Desktop\simple_Web_server\www\index.html
    } else if (request_path === '/index.html' && request_query_string_value === 'value') {
        fs_path = path_module.join(__dirname, site_root_directory, "value.html")
        // 对于url为'/index.html'的网络路径，查询字符串值为'value'，映射为服务端js文件所在当前目录下，网站根目录下的value.html文件路径
        // 如：C:\Users\DSHH\Desktop\simple_Web_server\www\value.html
    } else {
        fs_path = path_module.join(__dirname, site_root_directory, request_path)
        // 对于其他网络路径，映射为服务端js文件当前目录下，网站根目录下的资源文件路径
        // 如url为：'/other.html'，则本地路径为：如：C:\Users\DSHH\Desktop\simple_Web_server\www\other.html
        // 注意：对于其他资源如css、js、ico等请求，全都走这个分支
        // 如：C:\Users\DSHH\Desktop\simple_Web_server\www\index.css、C:\Users\DSHH\Desktop\simple_Web_server\www\favicon.ico
        // 注意：浏览器除了请求路径中的页面，可能会自动请求favicon.ico作为网页的图标，可不管
    }

    // 4. 读取本地文件系统相应的文件，设置http响应信息
    // http响应有3部分：响应行，响应头和响应体
    // 响应行有3部分：http版本，状态码，状态描述
    //（1) http版本，无需设置
    // (2) 状态码在下面读取文件时设置
    // (3) 状态描述无需设置，一般与状态码匹配
    // response.statusMessage = 'This is status message'
    // (4) 响应头
    // 注意：
    // 只需要依据文档类型设置mime类型让浏览器可以解析html、css和js文档
    // 否则当html、css、js分文件编写时，请求html会再次请求css和js文档，再次进入这个回调函数
    // 若mime类型为text/html，则无法解析css文档，css无法渲染
    // 设置编码为utf8支持中文显示不乱码
    const fs_path_ext_name = path_module.extname(fs_path) // 获取本地路径文件的扩展名，如：.css
    const fs_path_mime_type = fs_path_ext_name.slice(1)   // 获取mime类型中，text类型下的子类型名，如：css
    response.setHeader('content-type', `text/${fs_path_mime_type};charset=utf-8`)   // 拼接为：text/css;charset=utf-8
    // (5) 响应体，在下面读取文件时设置

    // 参数：文件路径和编码等可选项，回调函数
    // 当读取完成时，调用这个回调函数：传入错误Error和数据string对象
    fs_module.readFile(fs_path, 'utf8', (error, data) => {
        // 如果有错误，返回404资源不存在状态码和状态信息
        // 没有错误，返回读取的文件数据
        if (error) {
            response.statusCode = 404   // （2）设置状态码
            // 参数：流数据，可选项编码和回调函数
            // 返回值：bool，不需要
            response.write('<h1>404 未找到</h1>')   // （5）设置响应体
            // 参数：数据、编码和回调函数等可选项
            // 返回值：this，即end()的调用者response对象
            // 对每个响应可以调用多次write()写入数据，必须调用一次end()返回响应
            response.end()
        } else {
            response.statusCode = 200   // （2）设置状态码
            response.write(data)    // （5）设置响应体
            response.end()
        }
    })
})

// 四、启动服务端监听
// 参数：对于TCP，使用端口、地址、半连接和全连接队列和回调函数可选项
server.listen(port, host, () => {
    console.log(`Wen服务端运行在: http://${host}:${port}`)
})