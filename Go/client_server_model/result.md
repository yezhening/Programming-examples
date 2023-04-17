# 结果

server.go：

```powershell
PS C:\Users\DSHH\Desktop\go_test> go run server.go
RemoteAddr: 127.0.0.1:61915
Read: aaa
Write: aaa
RemoteAddr: 127.0.0.1:61939
Read: bbb
Write: bbb
Read: quit
Read: quit
exit status 0xc000013a
PS C:\Users\DSHH\Desktop\go_test> 
```

client.go：先连接先退出

```powershell
PS C:\Users\DSHH\Desktop\go_test> go run client.go
aaa
Write: aaa
Read: aaa
quit
Write: quit
Read() error: EOF
PS C:\Users\DSHH\Desktop\go_test>
```

client.go：后连接后退出

```powershell
PS C:\Users\DSHH\Desktop\go_test> go run client.go
bbb
Write: bbb
Read: bbb
quit
Write: quit
Read() error: EOF
PS C:\Users\DSHH\Desktop\go_test>
```